/******************************************************************************************
 * Copyright (c) 2015 eProsima. All rights reserved.
 *
 * This copy of eProsima Non-Intrusive DDS Recorder is licensed to you
 * under the terms described in the DDSRECORDER_LICENSE file included in this distribution.
 *
 *****************************************************************************************/
#ifndef _TOPICDATADB_H_
#define _TOPICDATADB_H_

#ifdef __cplusplus

#include <string>
#include <vector>

#include <sqlite3.h>

#include <fastdds/dds/xtypes/dynamic_types/DynamicData.hpp>
#include <fastdds/dds/xtypes/dynamic_types/DynamicPubSubType.hpp>
#include <fastdds/dds/xtypes/dynamic_types/DynamicType.hpp>

namespace eprosima {
class eProsimaLog;

/**
 * \brief Writes the samples of one DDS Topic as rows with one column per data type member.
 *
 * This is what '-queryable' adds on top of the *DDS Record & Replay* schema. The tables it
 * creates hold only the sample: every column the recording shares with the default schema, from
 * the timestamps to the writer, stays in Messages, and each row here points back at it through
 * (writer_guid, sequence_number).
 *
 * The data type is walked twice, once to build the CREATE TABLE and the INSERT and once to bind
 * the values of a sample. Unlike the TypeCode implementation this replaces, the second walk binds
 * by parameter *name* rather than by position, so the two walks disagreeing can no longer shift
 * values silently into the wrong column: a name that does not resolve is an error.
 *
 * A member whose type has no column representation (a map, a bitset, a nested collection) makes
 * the whole topic unrepresentable, and no table is created for it. The samples are still recorded
 * as CDR in Messages, so nothing is lost by that.
 */
class TopicDataDB
{
public:

    /// One table created for this topic: the member it holds, and its SQL name.
    typedef struct TableRef
    {
        /// Path of the collection member, empty for the topic's own table.
        std::string member_path;
        std::string table_name;
    } TableRef;

    /**
     * \brief Constructor. Creates the tables of the topic, dropping them first if present.
     *
     * \param log Log object used to log errors.
     * \param databaseH Handler of an already opened database. Cannot be NULL.
     * \param base_table_name SQL name of the topic's own table. The caller has already made it
     * unique, since two topic names can sanitize to the same identifier.
     * \param type Data type of the topic.
     */
    TopicDataDB(
            eProsimaLog& log,
            sqlite3 * databaseH,
            const std::string& base_table_name,
            const eprosima::fastdds::dds::DynamicType::_ref_type& type);

    ~TopicDataDB();

    /// Whether the tables and statements were created. When false, store() must not be called.
    bool is_ready() const;

    /// The tables created, in creation order, for the caller to record in DataTables.
    const std::vector<TableRef>& tables() const;

    /**
     * \brief Deserializes a sample and writes it as one row, plus one row per collection element.
     *
     * \param writer_guid GUID of the writer, as Messages.writer_guid spells it.
     * \param sequence_number Sequence number of the sample.
     * \param payload The CDR payload, encapsulation header included.
     * \param payload_len Length of the payload.
     * \return True value is returned if the sample was written.
     */
    bool store(
            const std::string& writer_guid,
            unsigned long long sequence_number,
            const char * payload,
            unsigned int payload_len);

private:

    typedef struct Column
    {
        /// Flattened member path. Also the name of the statement's parameter, prefixed with ':'.
        std::string name;
        std::string sql_type;
    } Column;

    typedef struct Table
    {
        std::string member_path;
        std::string name;
        /// Number of index columns: 0 for the topic's own table, one per array dimension.
        uint32_t index_count = 0;
        /// Dimensions of the collection, used to spread a flat element index over the indices.
        std::vector<uint32_t> dimensions;
        std::vector<Column> columns;
        eprosima::fastdds::dds::DynamicType::_ref_type element_type;
        sqlite3_stmt * insert = NULL;
    } Table;

    /// Walks the type and fills tables_. Returns false when a member cannot be represented.
    bool plan(
            const eprosima::fastdds::dds::DynamicType::_ref_type& type,
            const std::string& prefix,
            size_t table_index);

    /// Adds one scalar column to a table. Returns false for a kind with no column representation.
    bool plan_scalar(
            const eprosima::fastdds::dds::DynamicType::_ref_type& type,
            const std::string& name,
            size_t table_index);

    /// Creates a child table for an array or a sequence member.
    bool plan_collection(
            const eprosima::fastdds::dds::DynamicType::_ref_type& type,
            const std::string& prefix,
            size_t table_index);

    /// Creates '<table>_flat', the table joined back to Messages.
    bool create_view(
            const Table& table);

    /// Runs CREATE TABLE and prepares the INSERT for every planned table.
    bool create_tables();

    /// Binds every scalar of `data` into `stmt`, and writes the rows of the child tables below it.
    bool write(
            const eprosima::fastdds::dds::DynamicData::_ref_type& data,
            const eprosima::fastdds::dds::DynamicType::_ref_type& type,
            const std::string& prefix,
            sqlite3_stmt * stmt,
            const std::string& writer_guid,
            unsigned long long sequence_number);

    /// Reads the discriminator of a union as an integer, whichever integral kind it declares.
    bool read_discriminator(
            const eprosima::fastdds::dds::DynamicData::_ref_type& data,
            const eprosima::fastdds::dds::DynamicType::_ref_type& type,
            int64_t& value);

    /// Finds the branch a sample took, by matching the discriminator against the case labels.
    bool union_selected_member(
            const eprosima::fastdds::dds::DynamicData::_ref_type& data,
            const eprosima::fastdds::dds::DynamicType::_ref_type& type,
            const eprosima::fastdds::dds::DynamicType::_ref_type& discriminator_type,
            eprosima::fastdds::dds::MemberId& selected);

    /// Binds one scalar member, read from `data` at `id`, into the parameter called `name`.
    bool write_scalar(
            const eprosima::fastdds::dds::DynamicData::_ref_type& data,
            const eprosima::fastdds::dds::DynamicType::_ref_type& type,
            eprosima::fastdds::dds::MemberId id,
            const std::string& name,
            sqlite3_stmt * stmt);

    /// Writes one row per element of an array or sequence member.
    bool write_collection(
            const eprosima::fastdds::dds::DynamicData::_ref_type& data,
            const eprosima::fastdds::dds::DynamicType::_ref_type& type,
            eprosima::fastdds::dds::MemberId id,
            const std::string& path,
            const std::string& writer_guid,
            unsigned long long sequence_number);

    Table * find_table(
            const std::string& member_path);

    /// Resolves aliases down to the type they name.
    static eprosima::fastdds::dds::DynamicType::_ref_type resolve(
            const eprosima::fastdds::dds::DynamicType::_ref_type& type);

    eProsimaLog& log_;

    sqlite3 * database_{nullptr};

    eprosima::fastdds::dds::DynamicType::_ref_type type_;

    /// Decodes a CDR payload into a DynamicData of type_.
    eprosima::fastdds::dds::DynamicPubSubType pubsub_type_;

    /// The topic's own table first, then one per collection member.
    std::vector<Table> tables_;

    std::vector<TableRef> table_refs_;

    bool ready_{false};
};
} // namespace eprosima

#endif // ifdef __cplusplus

#endif // _TOPICDATADB_H_
