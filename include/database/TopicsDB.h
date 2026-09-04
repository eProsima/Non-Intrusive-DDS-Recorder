/******************************************************************************************
 * Copyright (c) 2015 eProsima. All rights reserved.
 *
 * This copy of eProsima Non-Intrusive DDS Recorder is licensed to you
 * under the terms described in the DDSRECORDER_LICENSE file included in this distribution.
 *
 *****************************************************************************************/
#ifndef _TOPICSDB_H_
#define _TOPICSDB_H_

#ifdef __cplusplus

#include <list>
#include <set>
#include <string>

#include <sqlite3.h>

namespace eprosima {
class eProsimaLog;
class TopicDataDB;
class TypeStore;

/**
 * \brief Owns the per topic data tables that '-queryable' adds, and the registry naming them.
 *
 * The tables of a topic are named after it, and a topic name is not a legal SQL identifier: it
 * may hold ':', '.', '-' or a space, and two different topics can sanitize to the same
 * identifier. Rather than let the second silently replace the first, as the schema this replaces
 * did, every table is recorded in DataTables so a reader can look up which table holds which
 * topic instead of reproducing the mangling.
 *
 * A topic whose type is not in the file given with '-idl', or whose type has no column
 * representation, simply gets no table. Its samples are still recorded as CDR in Messages.
 */
class TopicsDB
{
public:

    /**
     * \brief Constructor. Creates the DataTables registry, dropping it first if present.
     *
     * \param log Log object used to log errors.
     * \param databaseH Handler of an already opened database. Cannot be NULL.
     * \param type_store The data types read from the file given with '-idl'. Not owned, and has
     * to outlive this object. May be NULL, in which case no topic gets a table.
     */
    TopicsDB(
            eProsimaLog& log,
            sqlite3 * databaseH,
            const TypeStore * type_store);

    ~TopicsDB();

    /// Whether the registry was created. When false, the other methods do nothing.
    bool is_ready() const;

    /**
     * \brief Registers a DDS Topic and creates its data tables when the type is known.
     *
     * Repeated announcements of the same topic are ignored, so this can be called for every
     * discovery message.
     *
     * \param topicName Name of the DDS Topic.
     * \param typeName Name of the DDS Topic data type.
     * \return True value is returned when the topic was registered, whether or not it got a
     * table. False is returned only on a database error.
     */
    bool add_topic(
            const std::string& topicName,
            const std::string& typeName);

    /**
     * \brief Writes a sample into the data table of its topic.
     *
     * \return True value is returned when the sample was written, and when the topic has no
     * table, which is not an error.
     */
    bool store(
            const std::string& topicName,
            const std::string& typeName,
            const std::string& writer_guid,
            unsigned long long sequence_number,
            const char * payload,
            unsigned int payload_len);

    /// Number of rows written into the data tables.
    unsigned int get_row_count() const;

private:

    typedef struct Entry
    {
        std::string topic;
        std::string type;
        /// NULL when the type was unknown or could not be represented as columns.
        TopicDataDB * data = NULL;
    } Entry;

    Entry * find(
            const std::string& topicName,
            const std::string& typeName);

    /// Turns a topic name into an SQL identifier no other topic is already using.
    std::string unique_table_name(
            const std::string& topicName);

    /// Adds one row to DataTables.
    bool register_table(
            const std::string& topicName,
            const std::string& typeName,
            const std::string& member_path,
            const std::string& table_name);

    eProsimaLog& log_;

    sqlite3 * database_{nullptr};

    const TypeStore * type_store_{nullptr};

    sqlite3_stmt * add_data_table_stmt_{nullptr};

    std::list<Entry*> topics_;

    std::set<std::string> table_names_;

    unsigned int row_count_{0};

    bool ready_{false};
} ;
} // namespace eprosima

#endif // ifdef __cplusplus

#endif // _TOPICSDB_H_
