/******************************************************************************************
 * Copyright (c) 2015 eProsima. All rights reserved.
 *
 * This copy of eProsima Non-Intrusive DDS Recorder is licensed to you
 * under the terms described in the DDSRECORDER_LICENSE file included in this distribution.
 *
 *****************************************************************************************/
#include "database/TopicsDB.h"
#include "database/TopicDataDB.h"
#include "TypeStore.h"
#include "log/eProsimaLog.h"

#include <string.h>

#ifdef SQLITE_PREPARE_V2
#define SQLITE_PREPARE sqlite3_prepare_v2
#else
#define SQLITE_PREPARE sqlite3_prepare
#endif // ifdef SQLITE_PREPARE_V2

using namespace eprosima;
using namespace eprosima::fastdds::dds;
using namespace std;

static const char* const CLASS_NAME = "TopicsDB";

static const char* const TABLE_DATATABLES_CREATE =
        "CREATE TABLE IF NOT EXISTS DataTables ("
        "topic TEXT NOT NULL,"
        "type TEXT NOT NULL,"
        "member_path TEXT NOT NULL DEFAULT '',"
        "table_name TEXT NOT NULL,"
        "PRIMARY KEY(topic, type, member_path),"
        "FOREIGN KEY(topic, type) REFERENCES Topics(name, type))";

static const char* const TABLE_DATATABLES_DROP = "DROP TABLE IF EXISTS DataTables";

static const char* const DATATABLE_ADD =
        "INSERT OR IGNORE INTO DataTables (topic, type, member_path, table_name) "
        "VALUES (?, ?, ?, ?)";

TopicsDB::TopicsDB(
        eProsimaLog& log,
        sqlite3 * databaseH,
        const TypeStore * type_store)
    : log_(log)
    , database_(databaseH)
    , type_store_(type_store)
{
    const char* const METHOD_NAME = "TopicsDB";
    char* error = NULL;

    if (database_ == NULL)
    {
        logError(log_, "Bad parameters");
        return;
    }

    /*
     * The data tables themselves are dropped by TopicDataDB as each topic is discovered, since
     * only then is their name known. The registry has to go first so that a table left behind by
     * a previous run, for a topic this capture does not contain, is not still listed.
     */
    if (SQLITE_OK != sqlite3_exec(database_, TABLE_DATATABLES_DROP, NULL, NULL, &error))
    {
        logError(log_, "Cannot drop the DataTables table: %s", error != NULL ? error : "");
        sqlite3_free(error);
        return;
    }

    if (SQLITE_OK != sqlite3_exec(database_, TABLE_DATATABLES_CREATE, NULL, NULL, &error))
    {
        logError(log_, "Cannot create the DataTables table: %s", error != NULL ? error : "");
        sqlite3_free(error);
        return;
    }

    if (SQLITE_OK != SQLITE_PREPARE(database_, DATATABLE_ADD, (int)strlen(DATATABLE_ADD),
            &add_data_table_stmt_, NULL))
    {
        logError(log_, "Cannot prepare the add data table statement: %s",
                sqlite3_errmsg(database_));
        return;
    }

    ready_ = true;
}

TopicsDB::~TopicsDB()
{
    for (list<Entry*>::iterator it = topics_.begin(); it != topics_.end(); ++it)
    {
        if ((*it)->data != NULL)
        {
            delete (*it)->data;
        }

        delete *it;
    }

    if (add_data_table_stmt_ != NULL)
    {
        sqlite3_finalize(add_data_table_stmt_);
    }
}

bool TopicsDB::is_ready() const
{
    return ready_;
}

unsigned int TopicsDB::get_row_count() const
{
    return row_count_;
}

TopicsDB::Entry* TopicsDB::find(
        const string& topicName,
        const string& typeName)
{
    for (list<Entry*>::iterator it = topics_.begin(); it != topics_.end(); ++it)
    {
        if ((*it)->topic == topicName && (*it)->type == typeName)
        {
            return *it;
        }
    }

    return NULL;
}

string TopicsDB::unique_table_name(
        const string& topicName)
{
    string base = "Data_";

    for (size_t i = 0; i < topicName.length(); ++i)
    {
        char c = topicName[i];

        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_')
        {
            base += c;
        }
        else
        {
            base += '_';
        }
    }

    string candidate = base;
    unsigned int suffix = 1;

    /* Two topic names can sanitize to the same identifier; DataTables says which is which. */
    while (table_names_.find(candidate) != table_names_.end())
    {
        char tail[16];
        snprintf(tail, sizeof(tail), "_%u", ++suffix);
        candidate = base + tail;
    }

    table_names_.insert(candidate);

    return candidate;
}

bool TopicsDB::register_table(
        const string& topicName,
        const string& typeName,
        const string& member_path,
        const string& table_name)
{
    const char* const METHOD_NAME = "register_table";

    if (SQLITE_OK != sqlite3_reset(add_data_table_stmt_))
    {
        logError(log_, "Cannot reset the add data table statement");
        return false;
    }

    sqlite3_bind_text(add_data_table_stmt_, 1, topicName.c_str(), (int)topicName.length(),
            SQLITE_STATIC);
    sqlite3_bind_text(add_data_table_stmt_, 2, typeName.c_str(), (int)typeName.length(),
            SQLITE_STATIC);
    sqlite3_bind_text(add_data_table_stmt_, 3, member_path.c_str(), (int)member_path.length(),
            SQLITE_STATIC);
    sqlite3_bind_text(add_data_table_stmt_, 4, table_name.c_str(), (int)table_name.length(),
            SQLITE_STATIC);

    if (SQLITE_DONE != sqlite3_step(add_data_table_stmt_))
    {
        logError(log_, "Cannot register the table %s: %s", table_name.c_str(),
                sqlite3_errmsg(database_));
        return false;
    }

    return true;
}

bool TopicsDB::add_topic(
        const string& topicName,
        const string& typeName)
{
    const char* const METHOD_NAME = "add_topic";

    if (!ready_)
    {
        return false;
    }

    if (find(topicName, typeName) != NULL)
    {
        return true;
    }

    Entry * entry = new Entry();
    entry->topic = topicName;
    entry->type = typeName;
    topics_.push_back(entry);

    if (type_store_ == NULL)
    {
        logInfo(log_, "The topic %s gets no table: no IDL file was given with '-idl'",
                topicName.c_str());
        return true;
    }

    DynamicType::_ref_type type = type_store_->find(typeName);

    if (!type)
    {
        logInfo(log_, "The topic %s gets no table: the IDL file does not declare its data "
                "type %s", topicName.c_str(), typeName.c_str());
        return true;
    }

    TopicDataDB * data = new TopicDataDB(log_, database_, unique_table_name(topicName), type);

    if (!data->is_ready())
    {
        /* TopicDataDB has already said why. The topic stays recorded, only without a table. */
        delete data;
        return true;
    }

    entry->data = data;

    const vector<TopicDataDB::TableRef>& tables = data->tables();

    for (size_t i = 0; i < tables.size(); ++i)
    {
        if (!register_table(topicName, typeName, tables[i].member_path, tables[i].table_name))
        {
            return false;
        }
    }

    return true;
}

bool TopicsDB::store(
        const string& topicName,
        const string& typeName,
        const string& writer_guid,
        unsigned long long sequence_number,
        const char * payload,
        unsigned int payload_len)
{
    if (!ready_)
    {
        return false;
    }

    Entry * entry = find(topicName, typeName);

    if (entry == NULL || entry->data == NULL)
    {
        /* A topic without a table is not an error: its samples live in Messages as CDR. */
        return true;
    }

    if (!entry->data->store(writer_guid, sequence_number, payload, payload_len))
    {
        return false;
    }

    ++row_count_;

    return true;
}
