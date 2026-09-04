/******************************************************************************************
 * Copyright (c) 2015 eProsima. All rights reserved.
 *
 * This copy of eProsima Non-Intrusive DDS Recorder is licensed to you
 * under the terms described in the DDSRECORDER_LICENSE file included in this distribution.
 *
 *****************************************************************************************/
#include "database/CaptureDB.h"
#include "database/MonitorDB.h"
#include "log/eProsimaLog.h"

#include <string.h>

#ifdef SQLITE_PREPARE_V2
#define SQLITE_PREPARE sqlite3_prepare_v2
#else
#define SQLITE_PREPARE sqlite3_prepare
#endif // ifdef SQLITE_PREPARE_V2

using namespace eprosima;
using namespace std;

static const char* const CLASS_NAME = "CaptureDB";

/*
 * The GUID of an endpoint is spelled exactly as Messages.writer_guid spells a writer, so a join
 * between the two needs no conversion.
 */
static const char* const TABLE_ENDPOINTS_CREATE =
        "CREATE TABLE IF NOT EXISTS Endpoints ("
        "guid TEXT PRIMARY KEY NOT NULL,"
        "kind TEXT NOT NULL,"
        "topic TEXT NOT NULL,"
        "type TEXT NOT NULL,"
        "FOREIGN KEY(topic, type) REFERENCES Topics(name, type))";

/*
 * One row per SEDP announcement the capture holds, not per endpoint: an endpoint announced
 * repeatedly, or announced to several destinations, produced several packets.
 *
 * The announcing participant is the one that owns the endpoint, so its GuidPrefix is the prefix
 * half of endpoint_guid and is not repeated in a column of its own.
 */
static const char* const TABLE_DISCOVERYMESSAGES_CREATE =
        "CREATE TABLE IF NOT EXISTS DiscoveryMessages ("
        "packet_id INTEGER PRIMARY KEY,"
        "log_time DATETIME NOT NULL,"
        "publish_time DATETIME NOT NULL,"
        "ip_src TEXT NOT NULL,"
        "ip_dst TEXT NOT NULL,"
        "dst_guid_prefix TEXT,"
        "endpoint_guid TEXT NOT NULL,"
        "kind TEXT NOT NULL,"
        "FOREIGN KEY(endpoint_guid) REFERENCES Endpoints(guid))";

static const char* const TABLE_MESSAGESCAPTURE_CREATE =
        "CREATE TABLE IF NOT EXISTS MessagesCapture ("
        "packet_id INTEGER PRIMARY KEY,"
        "writer_guid TEXT NOT NULL,"
        "sequence_number INTEGER NOT NULL,"
        "log_time DATETIME NOT NULL,"
        "ip_src TEXT NOT NULL,"
        "ip_dst TEXT NOT NULL,"
        "dst_guid_prefix TEXT,"
        "FOREIGN KEY(writer_guid, sequence_number) "
        "REFERENCES Messages(writer_guid, sequence_number))";

/* Finding every packet that carried one sample is the query this table exists for. */
static const char* const INDEX_MESSAGESCAPTURE_CREATE =
        "CREATE INDEX IF NOT EXISTS MessagesCapture_message "
        "ON MessagesCapture(writer_guid, sequence_number)";

static const char* const TABLES_DROP[] =
{
    "DROP INDEX IF EXISTS MessagesCapture_message",
    "DROP TABLE IF EXISTS MessagesCapture",
    "DROP TABLE IF EXISTS DiscoveryMessages",
    "DROP TABLE IF EXISTS Endpoints",
    NULL
};

static const char* const ENDPOINT_ADD =
        "INSERT OR IGNORE INTO Endpoints (guid, kind, topic, type) VALUES (?, ?, ?, ?)";

static const char* const DISCOVERY_ADD =
        "INSERT OR IGNORE INTO DiscoveryMessages (packet_id, log_time, publish_time, ip_src, "
        "ip_dst, dst_guid_prefix, endpoint_guid, kind) VALUES (?, ?, ?, ?, ?, ?, ?, ?)";

static const char* const CAPTURE_ADD =
        "INSERT OR IGNORE INTO MessagesCapture (packet_id, writer_guid, sequence_number, "
        "log_time, ip_src, ip_dst, dst_guid_prefix) VALUES (?, ?, ?, ?, ?, ?, ?)";

static const char* const WRITER_KIND = "DataWriter";
static const char* const READER_KIND = "DataReader";

CaptureDB::CaptureDB(
        eProsimaLog& log,
        sqlite3 * databaseH)
    : log_(log)
    , database_(databaseH)
{
    const char* const METHOD_NAME = "CaptureDB";

    if (database_ == NULL)
    {
        logError(log_, "Bad parameters");
        return;
    }

    if (!create_schema())
    {
        return;
    }

    if (SQLITE_OK != SQLITE_PREPARE(database_, ENDPOINT_ADD, (int)strlen(ENDPOINT_ADD),
            &add_endpoint_stmt_, NULL) ||
            SQLITE_OK != SQLITE_PREPARE(database_, DISCOVERY_ADD, (int)strlen(DISCOVERY_ADD),
            &add_discovery_stmt_, NULL) ||
            SQLITE_OK != SQLITE_PREPARE(database_, CAPTURE_ADD, (int)strlen(CAPTURE_ADD),
            &add_capture_stmt_, NULL))
    {
        logError(log_, "Cannot prepare the statements: %s", sqlite3_errmsg(database_));
        return;
    }

    ready_ = true;
}

CaptureDB::~CaptureDB()
{
    if (add_endpoint_stmt_ != NULL)
    {
        sqlite3_finalize(add_endpoint_stmt_);
    }
    if (add_discovery_stmt_ != NULL)
    {
        sqlite3_finalize(add_discovery_stmt_);
    }
    if (add_capture_stmt_ != NULL)
    {
        sqlite3_finalize(add_capture_stmt_);
    }
}

bool CaptureDB::is_ready() const
{
    return ready_;
}

unsigned int CaptureDB::get_capture_count() const
{
    return capture_count_;
}

bool CaptureDB::execute(
        const char * statement)
{
    const char* const METHOD_NAME = "execute";
    char * error = NULL;

    if (SQLITE_OK != sqlite3_exec(database_, statement, NULL, NULL, &error))
    {
        logError(log_, "Cannot run '%s': %s", statement, error != NULL ? error : "");
        sqlite3_free(error);
        return false;
    }

    return true;
}

bool CaptureDB::create_schema()
{
    for (int i = 0; TABLES_DROP[i] != NULL; ++i)
    {
        if (!execute(TABLES_DROP[i]))
        {
            return false;
        }
    }

    return execute(TABLE_ENDPOINTS_CREATE) &&
           execute(TABLE_DISCOVERYMESSAGES_CREATE) &&
           execute(TABLE_MESSAGESCAPTURE_CREATE) &&
           execute(INDEX_MESSAGESCAPTURE_CREATE);
}

bool CaptureDB::add_discovery(
        unsigned int npacket,
        const struct timeval& wts,
        const string& ip_src,
        const string& ip_dst,
        struct DDS_Time_t& sourceTmp,
        unsigned int destHostId,
        unsigned int destAppId,
        unsigned int destInstanceId,
        unsigned int hostId,
        unsigned int appId,
        unsigned int instanceId,
        unsigned int entityId,
        bool is_writer,
        const string& topicName,
        const string& typeName)
{
    const char* const METHOD_NAME = "add_discovery";

    if (!ready_)
    {
        return false;
    }

    // These have to outlive the sqlite3_step below, since they are bound as SQLITE_STATIC.
    string guid = MonitorDB::format_guid(hostId, appId, instanceId, entityId);
    string logTime = MonitorDB::format_timestamp(wts.tv_sec,
                    (unsigned long long)wts.tv_usec * 1000ULL);
    string publishTime = MonitorDB::format_timestamp(sourceTmp.seconds,
                    MonitorDB::fraction_to_nanosec(sourceTmp.nanoseconds));
    string destination = MonitorDB::format_guid_prefix(destHostId, destAppId, destInstanceId);
    const char * kind = is_writer ? WRITER_KIND : READER_KIND;

    if (SQLITE_OK != sqlite3_reset(add_endpoint_stmt_))
    {
        logError(log_, "Cannot reset the add endpoint statement");
        return false;
    }

    sqlite3_bind_text(add_endpoint_stmt_, 1, guid.c_str(), (int)guid.length(), SQLITE_STATIC);
    sqlite3_bind_text(add_endpoint_stmt_, 2, kind, (int)strlen(kind), SQLITE_STATIC);
    sqlite3_bind_text(add_endpoint_stmt_, 3, topicName.c_str(), (int)topicName.length(),
            SQLITE_STATIC);
    sqlite3_bind_text(add_endpoint_stmt_, 4, typeName.c_str(), (int)typeName.length(),
            SQLITE_STATIC);

    if (SQLITE_DONE != sqlite3_step(add_endpoint_stmt_))
    {
        logError(log_, "Cannot store the endpoint %s: %s", guid.c_str(),
                sqlite3_errmsg(database_));
        return false;
    }

    if (SQLITE_OK != sqlite3_reset(add_discovery_stmt_))
    {
        logError(log_, "Cannot reset the add discovery statement");
        return false;
    }

    sqlite3_bind_int64(add_discovery_stmt_, 1, (sqlite3_int64)npacket);
    sqlite3_bind_text(add_discovery_stmt_, 2, logTime.c_str(), (int)logTime.length(),
            SQLITE_STATIC);
    sqlite3_bind_text(add_discovery_stmt_, 3, publishTime.c_str(), (int)publishTime.length(),
            SQLITE_STATIC);
    sqlite3_bind_text(add_discovery_stmt_, 4, ip_src.c_str(), (int)ip_src.length(),
            SQLITE_STATIC);
    sqlite3_bind_text(add_discovery_stmt_, 5, ip_dst.c_str(), (int)ip_dst.length(),
            SQLITE_STATIC);

    /* A packet with no INFO_DST was addressed to every participant, which is a NULL here. */
    if (destination.empty())
    {
        sqlite3_bind_null(add_discovery_stmt_, 6);
    }
    else
    {
        sqlite3_bind_text(add_discovery_stmt_, 6, destination.c_str(),
                (int)destination.length(), SQLITE_STATIC);
    }

    sqlite3_bind_text(add_discovery_stmt_, 7, guid.c_str(), (int)guid.length(), SQLITE_STATIC);
    sqlite3_bind_text(add_discovery_stmt_, 8, kind, (int)strlen(kind), SQLITE_STATIC);

    if (SQLITE_DONE != sqlite3_step(add_discovery_stmt_))
    {
        logError(log_, "Cannot store the discovery message of packet %u: %s", npacket,
                sqlite3_errmsg(database_));
        return false;
    }

    return true;
}

bool CaptureDB::add_message_capture(
        unsigned int npacket,
        const struct timeval& wts,
        const string& ip_src,
        const string& ip_dst,
        unsigned int destHostId,
        unsigned int destAppId,
        unsigned int destInstanceId,
        const string& writer_guid,
        unsigned long long sequence_number)
{
    const char* const METHOD_NAME = "add_message_capture";

    if (!ready_)
    {
        return false;
    }

    // These have to outlive the sqlite3_step below, since they are bound as SQLITE_STATIC.
    string logTime = MonitorDB::format_timestamp(wts.tv_sec,
                    (unsigned long long)wts.tv_usec * 1000ULL);
    string destination = MonitorDB::format_guid_prefix(destHostId, destAppId, destInstanceId);

    if (SQLITE_OK != sqlite3_reset(add_capture_stmt_))
    {
        logError(log_, "Cannot reset the add capture statement");
        return false;
    }

    sqlite3_bind_int64(add_capture_stmt_, 1, (sqlite3_int64)npacket);
    sqlite3_bind_text(add_capture_stmt_, 2, writer_guid.c_str(), (int)writer_guid.length(),
            SQLITE_STATIC);
    sqlite3_bind_int64(add_capture_stmt_, 3, (sqlite3_int64)sequence_number);
    sqlite3_bind_text(add_capture_stmt_, 4, logTime.c_str(), (int)logTime.length(),
            SQLITE_STATIC);
    sqlite3_bind_text(add_capture_stmt_, 5, ip_src.c_str(), (int)ip_src.length(), SQLITE_STATIC);
    sqlite3_bind_text(add_capture_stmt_, 6, ip_dst.c_str(), (int)ip_dst.length(), SQLITE_STATIC);

    if (destination.empty())
    {
        sqlite3_bind_null(add_capture_stmt_, 7);
    }
    else
    {
        sqlite3_bind_text(add_capture_stmt_, 7, destination.c_str(), (int)destination.length(),
                SQLITE_STATIC);
    }

    if (SQLITE_DONE != sqlite3_step(add_capture_stmt_))
    {
        logError(log_, "Cannot store the capture of packet %u: %s", npacket,
                sqlite3_errmsg(database_));
        return false;
    }

    ++capture_count_;

    return true;
}
