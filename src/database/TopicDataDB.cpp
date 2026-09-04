/******************************************************************************************
 * Copyright (c) 2015 eProsima. All rights reserved.
 *
 * This copy of eProsima Non-Intrusive DDS Recorder is licensed to you
 * under the terms described in the DDSRECORDER_LICENSE file included in this distribution.
 *
 *****************************************************************************************/
#include "database/TopicDataDB.h"
#include "log/eProsimaLog.h"

#include <string.h>

#include <fastdds/dds/xtypes/dynamic_types/DynamicTypeMember.hpp>
#include <fastdds/dds/xtypes/dynamic_types/MemberDescriptor.hpp>
#include <fastdds/dds/xtypes/dynamic_types/TypeDescriptor.hpp>
#include <fastdds/rtps/common/SerializedPayload.hpp>

#ifdef SQLITE_PREPARE_V2
#define SQLITE_PREPARE sqlite3_prepare_v2
#else
#define SQLITE_PREPARE sqlite3_prepare
#endif // ifdef SQLITE_PREPARE_V2

using namespace eprosima;
using namespace eprosima::fastdds::dds;
using namespace std;

static const char* const CLASS_NAME = "TopicDataDB";

/* Every identifier is emitted double quoted, so a member named after an SQL keyword is legal. */
static string quote_identifier(
        const string& identifier)
{
    string out = "\"";

    for (size_t i = 0; i < identifier.length(); ++i)
    {
        if (identifier[i] == '"')
        {
            out += "\"\"";
        }
        else
        {
            out += identifier[i];
        }
    }

    return out + "\"";
}

TopicDataDB::TopicDataDB(
        eProsimaLog& log,
        sqlite3 * databaseH,
        const string& base_table_name,
        const DynamicType::_ref_type& type)
    : log_(log)
    , database_(databaseH)
    , type_(type)
    , pubsub_type_(type)
{
    const char* const METHOD_NAME = "TopicDataDB";
    DynamicType::_ref_type resolved = resolve(type);

    if (database_ == NULL || !resolved)
    {
        logError(log_, "Bad parameters");
        return;
    }

    TypeDescriptor::_ref_type descriptor = traits<TypeDescriptor>::make_shared();

    if (RETCODE_OK != resolved->get_descriptor(descriptor) || TK_STRUCTURE != descriptor->kind())
    {
        logError(log_, "The data type of a topic has to be a structure");
        return;
    }

    Table root;
    root.member_path = "";
    root.name = base_table_name;
    tables_.push_back(root);

    if (!plan(resolved, "", 0))
    {
        /* plan() has already said which member it could not represent. */
        tables_.clear();
        return;
    }

    if (!create_tables())
    {
        tables_.clear();
        return;
    }

    for (size_t i = 0; i < tables_.size(); ++i)
    {
        TableRef ref;
        ref.member_path = tables_[i].member_path;
        ref.table_name = tables_[i].name;
        table_refs_.push_back(ref);
    }

    ready_ = true;
}

TopicDataDB::~TopicDataDB()
{
    for (size_t i = 0; i < tables_.size(); ++i)
    {
        if (tables_[i].insert != NULL)
        {
            sqlite3_finalize(tables_[i].insert);
        }
    }
}

bool TopicDataDB::is_ready() const
{
    return ready_;
}

const vector<TopicDataDB::TableRef>& TopicDataDB::tables() const
{
    return table_refs_;
}

DynamicType::_ref_type TopicDataDB::resolve(
        const DynamicType::_ref_type& type)
{
    DynamicType::_ref_type current = type;

    while (current)
    {
        TypeDescriptor::_ref_type descriptor = traits<TypeDescriptor>::make_shared();

        if (RETCODE_OK != current->get_descriptor(descriptor) || TK_ALIAS != descriptor->kind())
        {
            break;
        }

        current = descriptor->base_type();
    }

    return current;
}

TopicDataDB::Table* TopicDataDB::find_table(
        const string& member_path)
{
    for (size_t i = 0; i < tables_.size(); ++i)
    {
        if (tables_[i].member_path == member_path)
        {
            return &tables_[i];
        }
    }

    return NULL;
}

bool TopicDataDB::plan_scalar(
        const DynamicType::_ref_type& type,
        const string& name,
        size_t table_index)
{
    const char* const METHOD_NAME = "plan_scalar";
    TypeDescriptor::_ref_type descriptor = traits<TypeDescriptor>::make_shared();

    if (RETCODE_OK != type->get_descriptor(descriptor))
    {
        logError(log_, "Cannot read the descriptor of member %s", name.c_str());
        return false;
    }

    Column column;
    column.name = name;

    switch (descriptor->kind())
    {
        case TK_BOOLEAN:
        case TK_BYTE:
        case TK_INT8:
        case TK_UINT8:
        case TK_INT16:
        case TK_UINT16:
        case TK_INT32:
        case TK_UINT32:
        case TK_INT64:
        case TK_UINT64:
        case TK_CHAR8:
        case TK_CHAR16:
        case TK_ENUM:
            column.sql_type = "INTEGER";
            break;
        case TK_FLOAT32:
        case TK_FLOAT64:
            column.sql_type = "REAL";
            break;
        case TK_STRING8:
            column.sql_type = "TEXT";
            break;
        default:
            /*
             * Maps, bitsets, bitmasks, 128 bit floats and wide strings have no column
             * representation here. The topic is left without a table rather than recorded
             * partially; its samples are still in Messages as CDR.
             */
            logInfo(log_, "The member %s has a data type that cannot be stored in a column, "
                    "so the topic gets no table", name.c_str());
            return false;
    }

    tables_[table_index].columns.push_back(column);

    return true;
}

bool TopicDataDB::plan_collection(
        const DynamicType::_ref_type& type,
        const string& prefix,
        size_t table_index)
{
    const char* const METHOD_NAME = "plan_collection";

    if (0 != table_index)
    {
        /* A collection inside a collection element would need a table keyed on both sets of
         * indices. Not represented; the topic gets no table. */
        logInfo(log_, "The member %s is a collection nested in another collection, "
                "so the topic gets no table", prefix.c_str());
        return false;
    }

    TypeDescriptor::_ref_type descriptor = traits<TypeDescriptor>::make_shared();

    if (RETCODE_OK != type->get_descriptor(descriptor))
    {
        logError(log_, "Cannot read the descriptor of member %s", prefix.c_str());
        return false;
    }

    Table child;
    child.member_path = prefix;
    child.name = tables_[0].name + "_" + prefix;
    child.element_type = resolve(descriptor->element_type());

    if (!child.element_type)
    {
        logError(log_, "Cannot read the element type of member %s", prefix.c_str());
        return false;
    }

    const BoundSeq& bounds = descriptor->bound();

    if (TK_ARRAY == descriptor->kind())
    {
        for (size_t i = 0; i < bounds.size(); ++i)
        {
            child.dimensions.push_back(bounds[i]);
        }
    }
    else
    {
        /* A sequence has a single index whatever bound it declares. */
        child.dimensions.push_back(0);
    }

    child.index_count = (uint32_t)child.dimensions.size();

    size_t child_index = tables_.size();
    tables_.push_back(child);

    TypeDescriptor::_ref_type element_descriptor = traits<TypeDescriptor>::make_shared();

    if (RETCODE_OK != tables_[child_index].element_type->get_descriptor(element_descriptor))
    {
        logError(log_, "Cannot read the element descriptor of member %s", prefix.c_str());
        return false;
    }

    if (TK_STRUCTURE == element_descriptor->kind())
    {
        /* One column per member of the element, exactly as the topic's own table is built. */
        return plan(tables_[child_index].element_type, "", child_index);
    }

    return plan_scalar(tables_[child_index].element_type, "value", child_index);
}

bool TopicDataDB::plan(
        const DynamicType::_ref_type& type,
        const string& prefix,
        size_t table_index)
{
    const char* const METHOD_NAME = "plan";
    TypeDescriptor::_ref_type descriptor = traits<TypeDescriptor>::make_shared();

    if (RETCODE_OK != type->get_descriptor(descriptor))
    {
        logError(log_, "Cannot read the descriptor of member %s", prefix.c_str());
        return false;
    }

    bool is_union = (TK_UNION == descriptor->kind());

    if (is_union)
    {
        /* The branch a sample took is only readable from the discriminator, so it gets a column
         * of its own; the columns of the branches not taken are left NULL. */
        DynamicType::_ref_type discriminator = resolve(descriptor->discriminator_type());
        string name = prefix.empty() ? string("discriminator") : prefix + "_discriminator";

        if (!discriminator || !plan_scalar(discriminator, name, table_index))
        {
            return false;
        }
    }

    uint32_t count = type->get_member_count();

    for (uint32_t i = 0; i < count; ++i)
    {
        DynamicTypeMember::_ref_type member;

        if (RETCODE_OK != type->get_member_by_index(member, i))
        {
            logError(log_, "Cannot read the member %u of %s", i, prefix.c_str());
            return false;
        }

        MemberDescriptor::_ref_type member_descriptor = traits<MemberDescriptor>::make_shared();

        if (RETCODE_OK != member->get_descriptor(member_descriptor))
        {
            logError(log_, "Cannot read the descriptor of the member %u of %s", i, prefix.c_str());
            return false;
        }

        /*
         * A union counts its discriminator among its members, and it already got its column
         * above; taking it again here would declare that column twice.
         */
        if (is_union && MemberId(0) == member_descriptor->id())
        {
            continue;
        }

        string name = member_descriptor->name().to_string();
        string path = prefix.empty() ? name : prefix + "_" + name;
        DynamicType::_ref_type member_type = resolve(member_descriptor->type());

        if (!member_type)
        {
            logError(log_, "Cannot read the type of member %s", path.c_str());
            return false;
        }

        TypeDescriptor::_ref_type member_type_descriptor = traits<TypeDescriptor>::make_shared();

        if (RETCODE_OK != member_type->get_descriptor(member_type_descriptor))
        {
            logError(log_, "Cannot read the type descriptor of member %s", path.c_str());
            return false;
        }

        bool ok = false;

        switch (member_type_descriptor->kind())
        {
            case TK_STRUCTURE:
            case TK_UNION:
                /* Flattened into the same table, its members prefixed with the member name. */
                ok = plan(member_type, path, table_index);
                break;
            case TK_ARRAY:
            case TK_SEQUENCE:
                ok = plan_collection(member_type, path, table_index);
                break;
            default:
                ok = plan_scalar(member_type, path, table_index);
                break;
        }

        if (!ok)
        {
            return false;
        }
    }

    return true;
}

bool TopicDataDB::create_tables()
{
    const char* const METHOD_NAME = "create_tables";

    for (size_t t = 0; t < tables_.size(); ++t)
    {
        Table& table = tables_[t];

        string create = "CREATE TABLE " + quote_identifier(table.name) +
                " (writer_guid TEXT NOT NULL, sequence_number INTEGER NOT NULL";
        string insert = "INSERT OR IGNORE INTO " + quote_identifier(table.name) +
                " (writer_guid, sequence_number";
        string values = " VALUES (:writer_guid, :sequence_number";
        string key = "writer_guid, sequence_number";

        for (uint32_t i = 0; i < table.index_count; ++i)
        {
            char index_name[32];
            snprintf(index_name, sizeof(index_name), "index_%u", i);
            create += ", ";
            create += index_name;
            create += " INTEGER NOT NULL";
            insert += ", ";
            insert += index_name;
            values += ", :";
            values += index_name;
            key += ", ";
            key += index_name;
        }

        for (size_t c = 0; c < table.columns.size(); ++c)
        {
            create += ", " + quote_identifier(table.columns[c].name) + " " + table.columns[c].sql_type;
            insert += ", " + quote_identifier(table.columns[c].name);
            values += ", :" + table.columns[c].name;
        }

        create += ", PRIMARY KEY(" + key + ")";
        create += ", FOREIGN KEY(writer_guid, sequence_number) "
                "REFERENCES Messages(writer_guid, sequence_number))";
        insert += ")" + values + ")";

        string drop = "DROP TABLE IF EXISTS " + quote_identifier(table.name);
        char* error = NULL;

        if (SQLITE_OK != sqlite3_exec(database_, drop.c_str(), NULL, NULL, &error))
        {
            logError(log_, "Cannot drop the table %s: %s", table.name.c_str(),
                    error != NULL ? error : "");
            sqlite3_free(error);
            return false;
        }

        if (SQLITE_OK != sqlite3_exec(database_, create.c_str(), NULL, NULL, &error))
        {
            logError(log_, "Cannot create the table %s: %s", table.name.c_str(),
                    error != NULL ? error : "");
            sqlite3_free(error);
            return false;
        }

        if (SQLITE_OK != SQLITE_PREPARE(database_, insert.c_str(), (int)insert.length(),
                &table.insert, NULL))
        {
            logError(log_, "Cannot prepare the insert statement of the table %s: %s",
                    table.name.c_str(), sqlite3_errmsg(database_));
            return false;
        }

        if (!create_view(table))
        {
            return false;
        }
    }

    return true;
}

/*
 * The data tables hold only the sample, so reading one beside its timestamps means joining
 * Messages. That is the price of not repeating those columns in every table, and this view pays
 * it once: '<table>_flat' reads like the single flat table the older schema produced.
 */
bool TopicDataDB::create_view(
        const Table& table)
{
    const char* const METHOD_NAME = "create_view";
    string name = table.name + "_flat";
    string drop = "DROP VIEW IF EXISTS " + quote_identifier(name);
    string create = "CREATE VIEW " + quote_identifier(name) + " AS SELECT "
            "m.log_time, m.publish_time, m.topic, m.type, "
            "d.writer_guid, d.sequence_number";

    for (uint32_t i = 0; i < table.index_count; ++i)
    {
        char index_name[32];
        snprintf(index_name, sizeof(index_name), ", d.index_%u", i);
        create += index_name;
    }

    for (size_t c = 0; c < table.columns.size(); ++c)
    {
        create += ", d." + quote_identifier(table.columns[c].name);
    }

    create += " FROM Messages m JOIN " + quote_identifier(table.name) +
            " d USING (writer_guid, sequence_number)";

    char * error = NULL;

    if (SQLITE_OK != sqlite3_exec(database_, drop.c_str(), NULL, NULL, &error))
    {
        logError(log_, "Cannot drop the view %s: %s", name.c_str(), error != NULL ? error : "");
        sqlite3_free(error);
        return false;
    }

    if (SQLITE_OK != sqlite3_exec(database_, create.c_str(), NULL, NULL, &error))
    {
        logError(log_, "Cannot create the view %s: %s", name.c_str(), error != NULL ? error : "");
        sqlite3_free(error);
        return false;
    }

    return true;
}

/* Binds one value to the parameter called ':name'. A name that does not resolve is an error:
 * that is what keeps the planning walk and this one from drifting apart. */
#define BIND_BY_NAME(stmt, name, bind_call) \
    { \
        string parameter = ":" + (name); \
        int index = sqlite3_bind_parameter_index((stmt), parameter.c_str()); \
        if (0 == index) \
        { \
            logError(log_, "The statement has no parameter %s", parameter.c_str()); \
            return false; \
        } \
        if (SQLITE_OK != (bind_call)) \
        { \
            logError(log_, "Cannot bind the parameter %s", parameter.c_str()); \
            return false; \
        } \
    }

bool TopicDataDB::write_scalar(
        const DynamicData::_ref_type& data,
        const DynamicType::_ref_type& type,
        MemberId id,
        const string& name,
        sqlite3_stmt * stmt)
{
    const char* const METHOD_NAME = "write_scalar";
    TypeDescriptor::_ref_type descriptor = traits<TypeDescriptor>::make_shared();

    if (RETCODE_OK != type->get_descriptor(descriptor))
    {
        logError(log_, "Cannot read the descriptor of member %s", name.c_str());
        return false;
    }

    switch (descriptor->kind())
    {
        case TK_BOOLEAN:
        {
            bool value = false;
            if (RETCODE_OK != data->get_boolean_value(value, id))
            {
                logError(log_, "Cannot read the member %s (id %u)", name.c_str(),
                        (unsigned int)id);
                return false;
            }
            BIND_BY_NAME(stmt, name, sqlite3_bind_int(stmt, index, value ? 1 : 0));
            break;
        }
        case TK_BYTE:
        {
            eprosima::fastdds::rtps::octet value = 0;
            if (RETCODE_OK != data->get_byte_value(value, id))
            {
                logError(log_, "Cannot read the member %s (id %u)", name.c_str(),
                        (unsigned int)id);
                return false;
            }
            BIND_BY_NAME(stmt, name, sqlite3_bind_int(stmt, index, (int)value));
            break;
        }
        case TK_INT8:
        {
            int8_t value = 0;
            if (RETCODE_OK != data->get_int8_value(value, id))
            {
                logError(log_, "Cannot read the member %s (id %u)", name.c_str(),
                        (unsigned int)id);
                return false;
            }
            BIND_BY_NAME(stmt, name, sqlite3_bind_int(stmt, index, (int)value));
            break;
        }
        case TK_UINT8:
        {
            uint8_t value = 0;
            if (RETCODE_OK != data->get_uint8_value(value, id))
            {
                logError(log_, "Cannot read the member %s (id %u)", name.c_str(),
                        (unsigned int)id);
                return false;
            }
            BIND_BY_NAME(stmt, name, sqlite3_bind_int(stmt, index, (int)value));
            break;
        }
        case TK_INT16:
        {
            int16_t value = 0;
            if (RETCODE_OK != data->get_int16_value(value, id))
            {
                logError(log_, "Cannot read the member %s (id %u)", name.c_str(),
                        (unsigned int)id);
                return false;
            }
            BIND_BY_NAME(stmt, name, sqlite3_bind_int(stmt, index, (int)value));
            break;
        }
        case TK_UINT16:
        {
            uint16_t value = 0;
            if (RETCODE_OK != data->get_uint16_value(value, id))
            {
                logError(log_, "Cannot read the member %s (id %u)", name.c_str(),
                        (unsigned int)id);
                return false;
            }
            BIND_BY_NAME(stmt, name, sqlite3_bind_int(stmt, index, (int)value));
            break;
        }
        case TK_INT32:
        {
            int32_t value = 0;
            if (RETCODE_OK != data->get_int32_value(value, id))
            {
                logError(log_, "Cannot read the member %s (id %u)", name.c_str(),
                        (unsigned int)id);
                return false;
            }
            BIND_BY_NAME(stmt, name, sqlite3_bind_int(stmt, index, value));
            break;
        }
        case TK_UINT32:
        {
            uint32_t value = 0;
            if (RETCODE_OK != data->get_uint32_value(value, id))
            {
                logError(log_, "Cannot read the member %s (id %u)", name.c_str(),
                        (unsigned int)id);
                return false;
            }
            BIND_BY_NAME(stmt, name, sqlite3_bind_int64(stmt, index, (sqlite3_int64)value));
            break;
        }
        case TK_INT64:
        {
            int64_t value = 0;
            if (RETCODE_OK != data->get_int64_value(value, id))
            {
                logError(log_, "Cannot read the member %s (id %u)", name.c_str(),
                        (unsigned int)id);
                return false;
            }
            BIND_BY_NAME(stmt, name, sqlite3_bind_int64(stmt, index, (sqlite3_int64)value));
            break;
        }
        case TK_UINT64:
        {
            uint64_t value = 0;
            if (RETCODE_OK != data->get_uint64_value(value, id))
            {
                logError(log_, "Cannot read the member %s (id %u)", name.c_str(),
                        (unsigned int)id);
                return false;
            }
            /* Values above INT64_MAX wrap; SQLite integers are signed and there is no wider one. */
            BIND_BY_NAME(stmt, name, sqlite3_bind_int64(stmt, index, (sqlite3_int64)value));
            break;
        }
        case TK_FLOAT32:
        {
            float value = 0.0f;
            if (RETCODE_OK != data->get_float32_value(value, id))
            {
                logError(log_, "Cannot read the member %s (id %u)", name.c_str(),
                        (unsigned int)id);
                return false;
            }
            BIND_BY_NAME(stmt, name, sqlite3_bind_double(stmt, index, (double)value));
            break;
        }
        case TK_FLOAT64:
        {
            double value = 0.0;
            if (RETCODE_OK != data->get_float64_value(value, id))
            {
                logError(log_, "Cannot read the member %s (id %u)", name.c_str(),
                        (unsigned int)id);
                return false;
            }
            BIND_BY_NAME(stmt, name, sqlite3_bind_double(stmt, index, value));
            break;
        }
        case TK_CHAR8:
        {
            char value = 0;
            if (RETCODE_OK != data->get_char8_value(value, id))
            {
                logError(log_, "Cannot read the member %s (id %u)", name.c_str(),
                        (unsigned int)id);
                return false;
            }
            BIND_BY_NAME(stmt, name, sqlite3_bind_int(stmt, index, (int)value));
            break;
        }
        case TK_CHAR16:
        {
            wchar_t value = 0;
            if (RETCODE_OK != data->get_char16_value(value, id))
            {
                logError(log_, "Cannot read the member %s (id %u)", name.c_str(),
                        (unsigned int)id);
                return false;
            }
            BIND_BY_NAME(stmt, name, sqlite3_bind_int64(stmt, index, (sqlite3_int64)value));
            break;
        }
        case TK_ENUM:
        {
            int32_t value = 0;
            if (RETCODE_OK != data->get_int32_value(value, id))
            {
                logError(log_, "Cannot read the member %s (id %u)", name.c_str(),
                        (unsigned int)id);
                return false;
            }
            BIND_BY_NAME(stmt, name, sqlite3_bind_int(stmt, index, value));
            break;
        }
        case TK_STRING8:
        {
            string value;
            if (RETCODE_OK != data->get_string_value(value, id))
            {
                logError(log_, "Cannot read the member %s (id %u)", name.c_str(),
                        (unsigned int)id);
                return false;
            }
            /* SQLITE_TRANSIENT: the string dies at the end of this scope, before the step. */
            BIND_BY_NAME(stmt, name, sqlite3_bind_text(stmt, index, value.c_str(),
                    (int)value.length(), SQLITE_TRANSIENT));
            break;
        }
        default:
            logError(log_, "The member %s has a data type that cannot be stored", name.c_str());
            return false;
    }

    return true;
}

bool TopicDataDB::write_collection(
        const DynamicData::_ref_type& data,
        const DynamicType::_ref_type& type,
        MemberId id,
        const string& path,
        const string& writer_guid,
        unsigned long long sequence_number)
{
    const char* const METHOD_NAME = "write_collection";
    Table * table = find_table(path);

    if (table == NULL)
    {
        logError(log_, "No table was planned for the collection member %s", path.c_str());
        return false;
    }

    DynamicData::_ref_type collection = data->loan_value(id);

    if (!collection)
    {
        logError(log_, "Cannot read the collection member %s", path.c_str());
        return false;
    }

    bool returnedValue = true;
    uint32_t count = collection->get_item_count();

    TypeDescriptor::_ref_type element_descriptor = traits<TypeDescriptor>::make_shared();
    bool element_is_struct = false;

    if (RETCODE_OK == table->element_type->get_descriptor(element_descriptor))
    {
        element_is_struct = (TK_STRUCTURE == element_descriptor->kind() ||
                TK_UNION == element_descriptor->kind());
    }

    for (uint32_t i = 0; returnedValue && i < count; ++i)
    {
        if (SQLITE_OK != sqlite3_reset(table->insert) ||
                SQLITE_OK != sqlite3_clear_bindings(table->insert))
        {
            logError(log_, "Cannot reset the insert statement of %s", table->name.c_str());
            returnedValue = false;
            break;
        }

        int index = sqlite3_bind_parameter_index(table->insert, ":writer_guid");
        sqlite3_bind_text(table->insert, index, writer_guid.c_str(), (int)writer_guid.length(),
                SQLITE_TRANSIENT);
        index = sqlite3_bind_parameter_index(table->insert, ":sequence_number");
        sqlite3_bind_int64(table->insert, index, (sqlite3_int64)sequence_number);

        /*
         * Fast DDS keeps a multidimensional array flat, so the element index is spread back over
         * the declared dimensions, last dimension varying fastest.
         */
        uint32_t remainder = i;

        for (uint32_t d = table->index_count; d > 0; --d)
        {
            uint32_t dimension = table->dimensions[d - 1];
            uint32_t value = (dimension != 0) ? (remainder % dimension) : remainder;

            if (dimension != 0)
            {
                remainder /= dimension;
            }

            char index_name[32];
            snprintf(index_name, sizeof(index_name), ":index_%u", d - 1);
            int position = sqlite3_bind_parameter_index(table->insert, index_name);

            if (0 == position ||
                    SQLITE_OK != sqlite3_bind_int64(table->insert, position, (sqlite3_int64)value))
            {
                logError(log_, "Cannot bind %s of the table %s", index_name, table->name.c_str());
                returnedValue = false;
                break;
            }
        }

        if (!returnedValue)
        {
            break;
        }

        if (element_is_struct)
        {
            DynamicData::_ref_type element = collection->loan_value(MemberId(i));

            if (element)
            {
                returnedValue = write(element, table->element_type, "", table->insert,
                                writer_guid, sequence_number);
                collection->return_loaned_value(element);
            }
            else
            {
                logError(log_, "Cannot read the element %u of %s", i, path.c_str());
                returnedValue = false;
            }
        }
        else
        {
            returnedValue = write_scalar(collection, table->element_type, MemberId(i), "value",
                            table->insert);
        }

        if (returnedValue && SQLITE_DONE != sqlite3_step(table->insert))
        {
            logError(log_, "Cannot store the element %u of %s: %s", i, path.c_str(),
                    sqlite3_errmsg(database_));
            returnedValue = false;
        }
    }

    data->return_loaned_value(collection);

    return returnedValue;
}


/*
 * Reads the discriminator of a union as an integer. Its declared type is any of the integral
 * kinds, and the case labels it is matched against are int32, so they all widen to int64 here.
 */
bool TopicDataDB::read_discriminator(
        const DynamicData::_ref_type& data,
        const DynamicType::_ref_type& type,
        int64_t& value)
{
    const char* const METHOD_NAME = "read_discriminator";
    TypeDescriptor::_ref_type descriptor = traits<TypeDescriptor>::make_shared();

    if (RETCODE_OK != type->get_descriptor(descriptor))
    {
        logError(log_, "Cannot read the descriptor of a discriminator");
        return false;
    }

    ReturnCode_t ret = RETCODE_BAD_PARAMETER;

    switch (descriptor->kind())
    {
        case TK_BOOLEAN:
        {
            bool raw = false;
            ret = data->get_boolean_value(raw, MemberId(0));
            value = raw ? 1 : 0;
            break;
        }
        case TK_BYTE:
        {
            eprosima::fastdds::rtps::octet raw = 0;
            ret = data->get_byte_value(raw, MemberId(0));
            value = raw;
            break;
        }
        case TK_INT8:
        {
            int8_t raw = 0;
            ret = data->get_int8_value(raw, MemberId(0));
            value = raw;
            break;
        }
        case TK_UINT8:
        {
            uint8_t raw = 0;
            ret = data->get_uint8_value(raw, MemberId(0));
            value = raw;
            break;
        }
        case TK_INT16:
        {
            int16_t raw = 0;
            ret = data->get_int16_value(raw, MemberId(0));
            value = raw;
            break;
        }
        case TK_UINT16:
        {
            uint16_t raw = 0;
            ret = data->get_uint16_value(raw, MemberId(0));
            value = raw;
            break;
        }
        case TK_INT32:
        case TK_ENUM:
        {
            int32_t raw = 0;
            ret = data->get_int32_value(raw, MemberId(0));
            value = raw;
            break;
        }
        case TK_UINT32:
        {
            uint32_t raw = 0;
            ret = data->get_uint32_value(raw, MemberId(0));
            value = raw;
            break;
        }
        case TK_INT64:
        {
            int64_t raw = 0;
            ret = data->get_int64_value(raw, MemberId(0));
            value = raw;
            break;
        }
        case TK_UINT64:
        {
            uint64_t raw = 0;
            ret = data->get_uint64_value(raw, MemberId(0));
            value = (int64_t)raw;
            break;
        }
        case TK_CHAR8:
        {
            char raw = 0;
            ret = data->get_char8_value(raw, MemberId(0));
            value = raw;
            break;
        }
        case TK_CHAR16:
        {
            wchar_t raw = 0;
            ret = data->get_char16_value(raw, MemberId(0));
            value = raw;
            break;
        }
        default:
            logError(log_, "A discriminator cannot have this data type");
            return false;
    }

    return RETCODE_OK == ret;
}

/*
 * Finds the branch a sample took. DynamicData::get_member_id_at_index() enumerates the members as
 * they were declared rather than the one the discriminator selects, so the choice is made here
 * from the case labels, falling back to the branch marked default.
 */
bool TopicDataDB::union_selected_member(
        const DynamicData::_ref_type& data,
        const DynamicType::_ref_type& type,
        const DynamicType::_ref_type& discriminator_type,
        MemberId& selected)
{
    const char* const METHOD_NAME = "union_selected_member";
    int64_t value = 0;

    if (!read_discriminator(data, discriminator_type, value))
    {
        return false;
    }

    MemberId default_member = MEMBER_ID_INVALID;
    selected = MEMBER_ID_INVALID;
    uint32_t count = type->get_member_count();

    for (uint32_t i = 0; i < count; ++i)
    {
        DynamicTypeMember::_ref_type member;

        if (RETCODE_OK != type->get_member_by_index(member, i))
        {
            logError(log_, "Cannot read the branch %u of a union", i);
            return false;
        }

        MemberDescriptor::_ref_type member_descriptor = traits<MemberDescriptor>::make_shared();

        if (RETCODE_OK != member->get_descriptor(member_descriptor))
        {
            logError(log_, "Cannot read the descriptor of the branch %u of a union", i);
            return false;
        }

        if (MemberId(0) == member_descriptor->id())
        {
            continue;
        }

        if (member_descriptor->is_default_label())
        {
            default_member = member_descriptor->id();
        }

        const UnionCaseLabelSeq& labels = member_descriptor->label();

        for (size_t l = 0; l < labels.size(); ++l)
        {
            if ((int64_t)labels[l] == value)
            {
                selected = member_descriptor->id();
                return true;
            }
        }
    }

    /* No label matched, so the default branch is the one, if the union declares one. */
    selected = default_member;

    return true;
}

bool TopicDataDB::write(
        const DynamicData::_ref_type& data,
        const DynamicType::_ref_type& type,
        const string& prefix,
        sqlite3_stmt * stmt,
        const string& writer_guid,
        unsigned long long sequence_number)
{
    const char* const METHOD_NAME = "write";
    TypeDescriptor::_ref_type descriptor = traits<TypeDescriptor>::make_shared();

    if (RETCODE_OK != type->get_descriptor(descriptor))
    {
        logError(log_, "Cannot read the descriptor of %s", prefix.c_str());
        return false;
    }

    MemberId selected = MEMBER_ID_INVALID;
    bool is_union = (TK_UNION == descriptor->kind());

    if (is_union)
    {
        /* Member id 0 is the discriminator; get_item_count() is 2 when a branch is selected. */
        DynamicType::_ref_type discriminator = resolve(descriptor->discriminator_type());
        string name = prefix.empty() ? string("discriminator") : prefix + "_discriminator";

        if (!discriminator || !write_scalar(data, discriminator, MemberId(0), name, stmt))
        {
            logError(log_, "Cannot store the discriminator of %s", prefix.c_str());
            return false;
        }

        if (!union_selected_member(data, type, discriminator, selected))
        {
            logError(log_, "Cannot resolve the selected branch of %s", prefix.c_str());
            return false;
        }
    }

    uint32_t count = type->get_member_count();

    for (uint32_t i = 0; i < count; ++i)
    {
        DynamicTypeMember::_ref_type member;

        if (RETCODE_OK != type->get_member_by_index(member, i))
        {
            logError(log_, "Cannot read the member %u of %s", i, prefix.c_str());
            return false;
        }

        MemberDescriptor::_ref_type member_descriptor = traits<MemberDescriptor>::make_shared();

        if (RETCODE_OK != member->get_descriptor(member_descriptor))
        {
            logError(log_, "Cannot read the descriptor of the member %u of %s", i, prefix.c_str());
            return false;
        }

        MemberId id = member_descriptor->id();

        /* The columns of a branch the sample did not take keep the NULL from clear_bindings. */
        if (is_union && id != selected)
        {
            continue;
        }

        string name = member_descriptor->name().to_string();
        string path = prefix.empty() ? name : prefix + "_" + name;
        DynamicType::_ref_type member_type = resolve(member_descriptor->type());
        TypeDescriptor::_ref_type member_type_descriptor = traits<TypeDescriptor>::make_shared();

        if (!member_type || RETCODE_OK != member_type->get_descriptor(member_type_descriptor))
        {
            logError(log_, "Cannot read the type of member %s", path.c_str());
            return false;
        }

        bool ok = false;

        switch (member_type_descriptor->kind())
        {
            case TK_STRUCTURE:
            case TK_UNION:
            {
                DynamicData::_ref_type nested = data->loan_value(id);

                if (nested)
                {
                    ok = write(nested, member_type, path, stmt, writer_guid, sequence_number);
                    data->return_loaned_value(nested);
                }
                else
                {
                    logError(log_, "Cannot read the member %s", path.c_str());
                }

                break;
            }
            case TK_ARRAY:
            case TK_SEQUENCE:
                ok = write_collection(data, member_type, id, path, writer_guid, sequence_number);
                break;
            default:
                ok = write_scalar(data, member_type, id, path, stmt);
                break;
        }

        if (!ok)
        {
            return false;
        }
    }

    return true;
}

bool TopicDataDB::store(
        const string& writer_guid,
        unsigned long long sequence_number,
        const char * payload,
        unsigned int payload_len)
{
    const char* const METHOD_NAME = "store";

    if (!ready_ || payload == NULL || payload_len == 0)
    {
        logError(log_, "Bad parameters");
        return false;
    }

    /*
     * The payload is borrowed, not copied: data and max_size are cleared before the wrapper goes
     * out of scope so that its destructor does not free a buffer owned by the capture reader.
     */
    eprosima::fastdds::rtps::SerializedPayload_t wrapper;
    wrapper.data = (eprosima::fastdds::rtps::octet*)payload;
    wrapper.length = payload_len;
    wrapper.max_size = payload_len;

    void * sample = pubsub_type_.create_data();

    if (sample == NULL)
    {
        logError(log_, "Cannot create a sample of the data type");
        wrapper.data = NULL;
        wrapper.max_size = 0;
        return false;
    }

    bool returnedValue = pubsub_type_.deserialize(wrapper, sample);

    wrapper.data = NULL;
    wrapper.max_size = 0;

    if (!returnedValue)
    {
        logError(log_, "Cannot deserialize a sample of the topic stored in %s",
                tables_[0].name.c_str());
        pubsub_type_.delete_data(sample);
        return false;
    }

    DynamicData::_ref_type data = *static_cast<DynamicData::_ref_type*>(sample);
    Table& root = tables_[0];

    if (SQLITE_OK != sqlite3_reset(root.insert) ||
            SQLITE_OK != sqlite3_clear_bindings(root.insert))
    {
        logError(log_, "Cannot reset the insert statement of %s", root.name.c_str());
        pubsub_type_.delete_data(sample);
        return false;
    }

    int index = sqlite3_bind_parameter_index(root.insert, ":writer_guid");
    sqlite3_bind_text(root.insert, index, writer_guid.c_str(), (int)writer_guid.length(),
            SQLITE_TRANSIENT);
    index = sqlite3_bind_parameter_index(root.insert, ":sequence_number");
    sqlite3_bind_int64(root.insert, index, (sqlite3_int64)sequence_number);

    returnedValue = write(data, resolve(type_), "", root.insert, writer_guid, sequence_number);

    if (returnedValue && SQLITE_DONE != sqlite3_step(root.insert))
    {
        logError(log_, "Cannot store a sample in %s: %s", root.name.c_str(),
                sqlite3_errmsg(database_));
        returnedValue = false;
    }

    pubsub_type_.delete_data(sample);

    return returnedValue;
}
