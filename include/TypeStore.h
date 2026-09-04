/******************************************************************************************
 * Copyright (c) 2015 eProsima. All rights reserved.
 *
 * This copy of eProsima Non-Intrusive DDS Recorder is licensed to you
 * under the terms described in the DDSRECORDER_LICENSE file included in this distribution.
 *
 *****************************************************************************************/
#ifndef _TYPESTORE_H_
#define _TYPESTORE_H_

#ifdef __cplusplus

#include <map>
#include <string>

#include <fastdds/dds/xtypes/dynamic_types/DynamicType.hpp>

namespace eprosima {
class eProsimaLog;

/**
 * \brief The data types the recorder knows, indexed by type name.
 *
 * The RTPS traffic carries no type description the recorder can use, so the only source is the
 * IDL file given with '-idl'. The whole file is parsed once at start up and every type declared
 * in it is kept here; a topic whose type name is not among them is recorded without a data type.
 *
 * The types are Fast DDS \c DynamicType instances. Fast DDS is used purely as a local type model
 * and CDR decoder: the recorder never joins a DDS domain, never reads a TypeObject off the wire,
 * and leaves the Types.information and Types.object columns of the schema empty.
 */
class TypeStore
{
public:

    /**
     * \brief Constructor. Creates an empty store.
     *
     * \param log Log object used to log errors.
     */
    TypeStore(
            eProsimaLog& log);

    /**
     * \brief Parses an IDL file and keeps every type declared in it.
     *
     * Structures, unions, enumerations and aliases are all taken, so a type that is only reachable
     * through an alias resolves like any other. Parsing is all or nothing: when the file does not
     * parse the store is left empty.
     *
     * \param idl_file Path to the IDL file.
     * \return True value is returned when the file parsed and declared at least one type.
     */
    bool load(
            const std::string& idl_file);

    /**
     * \brief Looks a data type up by its name.
     *
     * \param type_name Name of the DDS Topic data type, as announced in the discovery traffic.
     * \return The data type, or a nil reference when the IDL file did not declare it.
     */
    eprosima::fastdds::dds::DynamicType::_ref_type find(
            const std::string& type_name) const;

    /**
     * \brief Renders a data type as IDL, for the 'idl' column of the Types table.
     *
     * \param type_name Name of the DDS Topic data type.
     * \return The type rendered as IDL, or an empty string when it is not known.
     */
    std::string idl_for(
            const std::string& type_name) const;

    /// Number of types the IDL file declared.
    size_t size() const;

private:

    eProsimaLog& log_;

    std::map<std::string, eprosima::fastdds::dds::DynamicType::_ref_type> types_;
};
} // namespace eprosima

#endif // ifdef __cplusplus

#endif // _TYPESTORE_H_
