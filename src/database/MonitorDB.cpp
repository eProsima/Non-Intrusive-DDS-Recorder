/******************************************************************************************
 * Copyright (c) 2015 eProsima. All rights reserved.
 *
 * This copy of eProsima Non-Intrusive DDS Recorder is licensed to you
 * under the terms described in the DDSRECORDER_LICENSE file included in this distribution.
 *
 *****************************************************************************************/
#include "database/MonitorDB.h"
#include "log/eProsimaLog.h"
#include "log/snprintf.h"

#include <string.h>
#include <time.h>

#ifdef EPROSIMA_LINUX
#include <sys/time.h>
#endif // ifdef EPROSIMA_LINUX

#ifdef SQLITE_PREPARE_V2
#define SQLITE_PREPARE sqlite3_prepare_v2
#else
#define SQLITE_PREPARE sqlite3_prepare
#endif // ifdef SQLITE_PREPARE_V2

/*
 * The DDL of the *DDS Record & Replay* schema, copied from SqlWriter::open_new_file_nts_ in
 * ddsrecorder_participants. The DDS Monitor has no schema-version check, so matching this is the
 * whole compatibility contract, and every table below is reproduced unchanged.
 *
 * Types is the single exception: it gains an 'idl' column, which holds the data type rendered as
 * IDL. That is the only type description the file given with '-idl' can provide, and neither of
 * the columns the original schema has for it fits, since both expect base64 of a TypeIdentifier
 * or a TypeObject. The column is additive, so a reader that selects the original columns by name
 * is unaffected, and it is declared with a default so that a writer that does not know about it
 * can still insert into Types.
 */
static const char* const TABLE_TYPES_CREATE =
        "CREATE TABLE IF NOT EXISTS Types ("
        "name TEXT PRIMARY KEY NOT NULL,"
        "information TEXT NOT NULL,"
        "object TEXT NOT NULL,"
        "is_ros2_type TEXT NOT NULL,"
        "idl TEXT NOT NULL DEFAULT '')";

static const char* const TABLE_TOPICS_CREATE =
        "CREATE TABLE IF NOT EXISTS Topics ("
        "name TEXT NOT NULL,"
        "type TEXT NOT NULL,"
        "qos TEXT NOT NULL,"
        "is_ros2_topic TEXT NOT NULL,"
        "PRIMARY KEY(name, type),"
        "FOREIGN KEY(type) REFERENCES Types(name))";

static const char* const TABLE_MESSAGES_CREATE =
        "CREATE TABLE IF NOT EXISTS Messages ("
        "writer_guid TEXT NOT NULL,"
        "sequence_number INTEGER NOT NULL,"
        "data_json TEXT,"
        "data_cdr BLOB,"
        "data_cdr_size INTEGER,"
        "topic TEXT NOT NULL,"
        "type TEXT NOT NULL,"
        "key TEXT NOT NULL,"
        "log_time DATETIME NOT NULL,"
        "publish_time DATETIME NOT NULL,"
        "PRIMARY KEY(writer_guid, sequence_number),"
        "FOREIGN KEY(topic, type) REFERENCES Topics(name, type))";

static const char* const TABLE_PARTITIONS_CREATE =
        "CREATE TABLE IF NOT EXISTS Partitions ("
        "name TEXT NOT NULL,"
        "PRIMARY KEY(name))";

static const char* const TABLE_TOPICSPARTITIONS_CREATE =
        "CREATE TABLE IF NOT EXISTS TopicsPartitions ("
        "topic TEXT NOT NULL,"
        "type TEXT NOT NULL,"
        "partition TEXT NOT NULL,"
        "PRIMARY KEY(topic, type, partition),"
        "FOREIGN KEY (topic, type) REFERENCES Topics(name, type) ON DELETE CASCADE,"
        "FOREIGN KEY (partition) REFERENCES Partitions(name) ON DELETE CASCADE)";

static const char* const TABLE_MESSAGESPARTITIONS_CREATE =
        "CREATE TABLE IF NOT EXISTS MessagesPartitions ("
        "writer_guid TEXT NOT NULL,"
        "sequence_number INTEGER NOT NULL,"
        "partition TEXT NOT NULL,"
        "PRIMARY KEY (writer_guid, sequence_number, partition),"
        "FOREIGN KEY (writer_guid, sequence_number) "
        "REFERENCES Messages(writer_guid, sequence_number) ON DELETE CASCADE,"
        "FOREIGN KEY (partition) REFERENCES Partitions(name) ON DELETE CASCADE)";

/* Selecting the samples of one topic over a time window is the query this schema is read with. */
static const char* const INDEX_MESSAGES_CREATE =
        "CREATE INDEX IF NOT EXISTS Messages_topic_time ON Messages(topic, type, log_time)";

/* Children first: the schema declares foreign keys even though enforcement is left off. */
static const char* const TABLES_DROP[] =
{
    "DROP INDEX IF EXISTS Messages_topic_time",
    "DROP TABLE IF EXISTS MessagesPartitions",
    "DROP TABLE IF EXISTS TopicsPartitions",
    "DROP TABLE IF EXISTS Messages",
    "DROP TABLE IF EXISTS Topics",
    "DROP TABLE IF EXISTS Types",
    "DROP TABLE IF EXISTS Partitions",
    NULL
};

static const char* const TYPE_ADD =
        "INSERT OR IGNORE INTO Types (name, information, object, is_ros2_type, idl) "
        "VALUES (?, ?, ?, ?, ?)";
static const char* const TYPE_UPDATE =
        "UPDATE Types SET idl = ? WHERE name = ? AND idl = ''";
static const char* const TOPIC_ADD =
        "INSERT OR IGNORE INTO Topics (name, type, qos, is_ros2_topic) VALUES (?, ?, ?, ?)";
static const char* const TOPICPARTITION_ADD =
        "INSERT OR IGNORE INTO TopicsPartitions (topic, type, partition) VALUES (?, ?, ?)";
static const char* const MESSAGE_ADD =
        "INSERT OR IGNORE INTO Messages (writer_guid, sequence_number, data_json, data_cdr, "
        "data_cdr_size, topic, type, key, log_time, publish_time) "
        "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
static const char* const MESSAGEPARTITION_ADD =
        "INSERT OR IGNORE INTO MessagesPartitions (writer_guid, sequence_number, partition) "
        "VALUES (?, ?, ?)";
static const char* const PARTITION_ADD =
        "INSERT OR IGNORE INTO Partitions (name) VALUES ('')";

/*
 * The recorder parses only the topic name, the type name and the GUID out of the discovery
 * messages, so no QoS survives. These are the DDS Record & Replay defaults, in the
 * exact four-key YAML that Serializer::serialize<TopicQoS> emits.
 */
static const char* const DEFAULT_QOS =
        "reliability: true\ndurability: false\nownership: false\nkeyed: false";

/* The single, empty partition every topic and message is associated with. */
static const char* const EMPTY_PARTITION = "";

/* Samples are stored as CDR, never deserialized, so there is no JSON and no key. */
static const char* const EMPTY_JSON = "";
static const char* const EMPTY_KEY = "{}";

static const char* const NOT_ROS2 = "false";

using namespace eprosima;
using namespace std;

static const char* const CLASS_NAME = "MonitorDB";

MonitorDB::MonitorDB(
        eProsimaLog& log,
        sqlite3* databaseH)
    : log_(log)
    , database_(databaseH)
{
    const char* const METHOD_NAME = "MonitorDB";

    if (database_ == NULL)
    {
        logError(log_, "Bad parameters");
        return;
    }

    if (!create_schema())
    {
        return;
    }

    if (!execute(PARTITION_ADD))
    {
        return;
    }

    if (SQLITE_PREPARE(database_, TYPE_ADD, (int)strlen(TYPE_ADD),
            &add_type_stmt_, NULL) != SQLITE_OK ||
            SQLITE_PREPARE(database_, TYPE_UPDATE, (int)strlen(TYPE_UPDATE),
            &updatte_type_stmt_, NULL) != SQLITE_OK ||
            SQLITE_PREPARE(database_, TOPIC_ADD, (int)strlen(TOPIC_ADD),
            &add_topic_stmt_, NULL) != SQLITE_OK ||
            SQLITE_PREPARE(database_, TOPICPARTITION_ADD, (int)strlen(TOPICPARTITION_ADD),
            &add_topic_parttition_stmt_, NULL) != SQLITE_OK ||
            SQLITE_PREPARE(database_, MESSAGE_ADD, (int)strlen(MESSAGE_ADD),
            &add_message_stmt_, NULL) != SQLITE_OK ||
            SQLITE_PREPARE(database_, MESSAGEPARTITION_ADD, (int)strlen(MESSAGEPARTITION_ADD),
            &add_message_partitition_stmt, NULL) != SQLITE_OK)
    {
        logError(log_, "Cannot prepare the statements of the monitor schema: %s",
                sqlite3_errmsg(database_));
        return;
    }

    ready_ = true;
}

MonitorDB::~MonitorDB()
{
    list<Endpoint*>::iterator it;

    if (add_type_stmt_ != NULL)
    {
        sqlite3_finalize(add_type_stmt_);
    }
    if (updatte_type_stmt_ != NULL)
    {
        sqlite3_finalize(updatte_type_stmt_);
    }
    if (add_topic_stmt_ != NULL)
    {
        sqlite3_finalize(add_topic_stmt_);
    }
    if (add_topic_parttition_stmt_ != NULL)
    {
        sqlite3_finalize(add_topic_parttition_stmt_);
    }
    if (add_message_stmt_ != NULL)
    {
        sqlite3_finalize(add_message_stmt_);
    }
    if (add_message_partitition_stmt != NULL)
    {
        sqlite3_finalize(add_message_partitition_stmt);
    }

    for (it = m_endpoints.begin(); it != m_endpoints.end(); it++)
    {
        delete (*it);
    }
}

bool MonitorDB::execute(
        const char* statement)
{
    const char* const METHOD_NAME = "execute";
    sqlite3_stmt* stmt = NULL;
    bool returnedValue = false;

    if (SQLITE_PREPARE(database_, statement, (int)strlen(statement), &stmt, NULL) == SQLITE_OK)
    {
        if (sqlite3_step(stmt) == SQLITE_DONE)
        {
            returnedValue = true;
        }
        else
        {
            logError(log_, "Cannot run \"%s\": %s", statement, sqlite3_errmsg(database_));
        }

        sqlite3_finalize(stmt);
    }
    else
    {
        logError(log_, "Cannot prepare \"%s\": %s", statement, sqlite3_errmsg(database_));
    }

    return returnedValue;
}

bool MonitorDB::create_schema()
{
    static const char* const CREATES[] =
    {
        TABLE_TYPES_CREATE,
        TABLE_TOPICS_CREATE,
        TABLE_MESSAGES_CREATE,
        TABLE_PARTITIONS_CREATE,
        TABLE_TOPICSPARTITIONS_CREATE,
        TABLE_MESSAGESPARTITIONS_CREATE,
        INDEX_MESSAGES_CREATE,
        NULL
    };

    /*
     * Opening a database that already holds a recording replaces it, which is the same
     * behaviour as the default schema.
     */
    for (int count = 0; TABLES_DROP[count] != NULL; ++count)
    {
        if (!execute(TABLES_DROP[count]))
        {
            return false;
        }
    }

    for (int count = 0; CREATES[count] != NULL; ++count)
    {
        if (!execute(CREATES[count]))
        {
            return false;
        }
    }

    return true;
}

std::string MonitorDB::format_guid(
        unsigned int hostId,
        unsigned int appId,
        unsigned int instanceId,
        unsigned int entityId)
{
    const unsigned int words[3] = { hostId, appId, instanceId };
    char buffer[64];
    int offset = 0;
    int shift;

    for (int word = 0; word < 3; ++word)
    {
        for (shift = 24; shift >= 0; shift -= 8)
        {
            offset += SNPRINTF(buffer + offset, sizeof(buffer) - offset, "%02x.",
                            (words[word] >> shift) & 0xFF);
        }
    }

    // Replace the trailing '.' of the prefix with the prefix/entity separator.
    buffer[offset - 1] = '|';

    // The entity id bytes are not zero padded, unlike the ones of the prefix.
    for (shift = 24; shift >= 0; shift -= 8)
    {
        offset += SNPRINTF(buffer + offset, sizeof(buffer) - offset, "%x.",
                        (entityId >> shift) & 0xFF);
    }

    buffer[offset - 1] = '\0';

    return string(buffer);
}

std::string MonitorDB::format_guid_prefix(
        unsigned int hostId,
        unsigned int appId,
        unsigned int instanceId)
{
    const unsigned int words[3] = { hostId, appId, instanceId };
    char buffer[64];
    int offset = 0;

    if (hostId == 0 && appId == 0 && instanceId == 0)
    {
        return std::string();
    }

    for (int word = 0; word < 3; ++word)
    {
        for (int shift = 24; shift >= 0; shift -= 8)
        {
            offset += SNPRINTF(buffer + offset, sizeof(buffer) - offset, "%02x.",
                            (words[word] >> shift) & 0xFF);
        }
    }

    // Drop the trailing '.'; there is no entity id to separate from.
    buffer[offset - 1] = '\0';

    return std::string(buffer);
}

std::string MonitorDB::format_timestamp(
        long long seconds,
        unsigned long long nanos)
{
    char buffer[64];
    time_t moment;
    struct tm* utc = NULL;
    size_t length = 0;

    // Carry any overflow so the fractional part always fits in nine digits.
    seconds += (long long)(nanos / 1000000000ULL);
    nanos %= 1000000000ULL;

    moment = (time_t)seconds;
    utc = gmtime(&moment);

    if (utc == NULL)
    {
        return string("1970-01-01 00:00:00.000000000");
    }

    length = strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", utc);
    SNPRINTF(buffer + length, sizeof(buffer) - length, ".%09u", (unsigned int)nanos);

    return string(buffer);
}

unsigned int MonitorDB::fraction_to_nanosec(
        unsigned int fraction)
{
    return (unsigned int)((((unsigned long long)fraction) * 1000000000ULL) >> 32);
}

Endpoint* MonitorDB::find_endpoint(
        unsigned int hostId,
        unsigned int appId,
        unsigned int instanceId,
        unsigned int entityId)
{
    list<Endpoint*>::iterator it;

    for (it = m_endpoints.begin(); it != m_endpoints.end(); it++)
    {
        if ((*it)->equal(hostId, appId, instanceId, entityId))
        {
            return (*it);
        }
    }

    return NULL;
}

bool MonitorDB::add_topic(
        std::string& topicName,
        std::string& typeName,
        const std::string& idl)
{
    const char* const METHOD_NAME = "addTopic";

    if (!ready_)
    {
        logError(log_, "The monitor schema is not ready");
        return false;
    }

    if (topicName.empty() || typeName.empty())
    {
        logInfo(log_, "Ignoring a discovered topic with no topic name or no type name");
        return false;
    }

    if (sqlite3_reset(add_type_stmt_) != SQLITE_OK)
    {
        logError(log_, "Cannot reset the add type statement");
        return false;
    }

    /*
     * Types.information and Types.object would hold a serialized TypeIdentifier and TypeObject.
     * The recorder reads no XTypes type information off the wire, so both are always left empty:
     * the DDS Monitor drops a Types row whose object does not decode. The type description goes
     * into the 'idl' column instead, rendered from the file given with '-idl'.
     */
    sqlite3_bind_text(add_type_stmt_, 1, typeName.c_str(), (int)typeName.length(), SQLITE_STATIC);
    sqlite3_bind_text(add_type_stmt_, 2, "", 0, SQLITE_STATIC);
    sqlite3_bind_text(add_type_stmt_, 3, "", 0, SQLITE_STATIC);
    sqlite3_bind_text(add_type_stmt_, 4, NOT_ROS2, (int)strlen(NOT_ROS2), SQLITE_STATIC);
    sqlite3_bind_text(add_type_stmt_, 5, idl.c_str(), (int)idl.length(), SQLITE_STATIC);

    if (sqlite3_step(add_type_stmt_) != SQLITE_DONE)
    {
        logError(log_, "Cannot step the add type statement: %s", sqlite3_errmsg(database_));
        return false;
    }

    // Describe a type that a previous announcement registered without any IDL.
    if (!idl.empty())
    {
        if (sqlite3_reset(updatte_type_stmt_) != SQLITE_OK)
        {
            logError(log_, "Cannot reset the update type statement");
            return false;
        }

        sqlite3_bind_text(updatte_type_stmt_, 1, idl.c_str(), (int)idl.length(), SQLITE_STATIC);
        sqlite3_bind_text(updatte_type_stmt_, 2, typeName.c_str(), (int)typeName.length(),
                SQLITE_STATIC);

        if (sqlite3_step(updatte_type_stmt_) != SQLITE_DONE)
        {
            logError(log_, "Cannot step the update type statement: %s",
                    sqlite3_errmsg(database_));
            return false;
        }
    }

    if (sqlite3_reset(add_topic_stmt_) != SQLITE_OK)
    {
        logError(log_, "Cannot reset the add topic statement");
        return false;
    }

    sqlite3_bind_text(add_topic_stmt_, 1, topicName.c_str(), (int)topicName.length(),
            SQLITE_STATIC);
    sqlite3_bind_text(add_topic_stmt_, 2, typeName.c_str(), (int)typeName.length(), SQLITE_STATIC);
    sqlite3_bind_text(add_topic_stmt_, 3, DEFAULT_QOS, (int)strlen(DEFAULT_QOS), SQLITE_STATIC);
    sqlite3_bind_text(add_topic_stmt_, 4, NOT_ROS2, (int)strlen(NOT_ROS2), SQLITE_STATIC);

    if (sqlite3_step(add_topic_stmt_) != SQLITE_DONE)
    {
        logError(log_, "Cannot step the add topic statement: %s", sqlite3_errmsg(database_));
        return false;
    }

    if (sqlite3_reset(add_topic_parttition_stmt_) != SQLITE_OK)
    {
        logError(log_, "Cannot reset the add topic partition statement");
        return false;
    }

    sqlite3_bind_text(add_topic_parttition_stmt_, 1, topicName.c_str(), (int)topicName.length(),
            SQLITE_STATIC);
    sqlite3_bind_text(add_topic_parttition_stmt_, 2, typeName.c_str(), (int)typeName.length(),
            SQLITE_STATIC);
    sqlite3_bind_text(add_topic_parttition_stmt_, 3, EMPTY_PARTITION, 0, SQLITE_STATIC);

    if (sqlite3_step(add_topic_parttition_stmt_) != SQLITE_DONE)
    {
        logError(log_, "Cannot step the add topic partition statement: %s",
                sqlite3_errmsg(database_));
        return false;
    }

    return true;
}

bool MonitorDB::add_endpoint(
        unsigned int hostId,
        unsigned int appId,
        unsigned int instanceId,
        unsigned int entityId,
        std::string& topicName,
        std::string& typeName)
{
    const char* const METHOD_NAME = "addEndpoint";

    if (!ready_)
    {
        logError(log_, "The monitor schema is not ready");
        return false;
    }

    if (find_endpoint(hostId, appId, instanceId, entityId) == NULL)
    {
        m_endpoints.push_back(new Endpoint(hostId, appId, instanceId, entityId,
                topicName, typeName));
    }

    return true;
}

bool MonitorDB::add_message(
        const struct timeval& wts,
        unsigned int hostId,
        unsigned int appId,
        unsigned int instanceId,
        unsigned int readerId,
        unsigned int writerId,
        unsigned long long writerSeqNum,
        struct DDS_Time_t& sourceTmp,
        const char* serializedData,
        unsigned int serializedDataLen,
        StoredMessage* stored)
{
    const char* const METHOD_NAME = "addMessage";
    Endpoint* endpoint = NULL;

    if (stored != NULL)
    {
        stored->stored = false;
    }

    if (!ready_)
    {
        logError(log_, "The monitor schema is not ready");
        return false;
    }

    if (serializedData == NULL || serializedDataLen == 0)
    {
        logError(log_, "Bad parameters");
        return false;
    }

    /*
     * The sample carries the GuidPrefix of its participant plus the entity ids of the writer and
     * of the destination reader. Either of them identifies the topic; the writer is preferred
     * because it is the one the sample is attributed to.
     */
    if ((endpoint = find_endpoint(hostId, appId, instanceId, writerId)) == NULL)
    {
        endpoint = find_endpoint(hostId, appId, instanceId, readerId);
    }

    if (endpoint == NULL)
    {
        if (!unknown_endpoint_warned_)
        {
            logInfo(log_, "Discarding samples whose endpoint was not announced in the "
                    "capture, starting with (%u, %u, %u, %u): their topic is unknown",
                    hostId, appId, instanceId, writerId);
            unknown_endpoint_warned_ = true;
        }

        return false;
    }

    // These have to outlive the sqlite3_step below, since they are bound as SQLITE_STATIC.
    string writerGuid = format_guid(hostId, appId, instanceId, writerId);
    string logTime = format_timestamp(wts.tv_sec, (unsigned long long)wts.tv_usec * 1000ULL);
    string publishTime = format_timestamp(sourceTmp.seconds,
                    fraction_to_nanosec(sourceTmp.nanoseconds));
    const string& topicName = endpoint->getTopicName();
    const string& typeName = endpoint->getTypeName();

    if (stored != NULL)
    {
        stored->resolved = true;
        stored->writer_guid = writerGuid;
        stored->sequence_number = writerSeqNum;
        stored->topic_name = topicName;
        stored->type_name = typeName;
    }

    if (sqlite3_reset(add_message_stmt_) != SQLITE_OK)
    {
        logError(log_, "Cannot reset the add message statement");
        return false;
    }

    sqlite3_bind_text(add_message_stmt_, 1, writerGuid.c_str(), (int)writerGuid.length(),
            SQLITE_STATIC);
    sqlite3_bind_int64(add_message_stmt_, 2, (sqlite3_int64)writerSeqNum);
    sqlite3_bind_text(add_message_stmt_, 3, EMPTY_JSON, 0, SQLITE_STATIC);
    // The payload is stored as it travelled, encapsulation header included.
    sqlite3_bind_blob(add_message_stmt_, 4, serializedData, (int)serializedDataLen,
            SQLITE_STATIC);
    sqlite3_bind_int64(add_message_stmt_, 5, (sqlite3_int64)serializedDataLen);
    sqlite3_bind_text(add_message_stmt_, 6, topicName.c_str(), (int)topicName.length(),
            SQLITE_STATIC);
    sqlite3_bind_text(add_message_stmt_, 7, typeName.c_str(), (int)typeName.length(),
            SQLITE_STATIC);
    sqlite3_bind_text(add_message_stmt_, 8, EMPTY_KEY, (int)strlen(EMPTY_KEY), SQLITE_STATIC);
    sqlite3_bind_text(add_message_stmt_, 9, logTime.c_str(), (int)logTime.length(),
            SQLITE_STATIC);
    sqlite3_bind_text(add_message_stmt_, 10, publishTime.c_str(), (int)publishTime.length(),
            SQLITE_STATIC);

    if (sqlite3_step(add_message_stmt_) != SQLITE_DONE)
    {
        logError(log_, "Cannot step the add message statement: %s",
                sqlite3_errmsg(database_));
        return false;
    }

    /*
     * The same sample is captured more than once when it is seen both as multicast and as
     * unicast, or when the writer repairs it. The primary key of Messages makes those copies
     * collide, so the INSERT OR IGNORE stored nothing and there is nothing else to do.
     */
    if (sqlite3_changes(database_) == 0)
    {
        ++duplicate_count_;
        return true;
    }

    if (sqlite3_reset(add_message_partitition_stmt) != SQLITE_OK)
    {
        logError(log_, "Cannot reset the add message partition statement");
        return false;
    }

    sqlite3_bind_text(add_message_partitition_stmt, 1, writerGuid.c_str(),
            (int)writerGuid.length(), SQLITE_STATIC);
    sqlite3_bind_int64(add_message_partitition_stmt, 2, (sqlite3_int64)writerSeqNum);
    sqlite3_bind_text(add_message_partitition_stmt, 3, EMPTY_PARTITION, 0, SQLITE_STATIC);

    if (sqlite3_step(add_message_partitition_stmt) != SQLITE_DONE)
    {
        logError(log_, "Cannot step the add message partition statement: %s",
                sqlite3_errmsg(database_));
        return false;
    }

    ++message_count;

    if (stored != NULL)
    {
        stored->stored = true;
    }

    return true;
}

unsigned int MonitorDB::getMessageCount()
{
    return message_count;
}

unsigned int MonitorDB::getDuplicateCount()
{
    return duplicate_count_;
}
