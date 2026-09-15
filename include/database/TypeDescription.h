/******************************************************************************************
 * Copyright (c) 2015 eProsima. All rights reserved.
 *
 * This copy of eProsima Non-Intrusive DDS Recorder is licensed to you
 * under the terms described in the DDSRECORDER_LICENSE file included in this distribution.
 *
 *****************************************************************************************/
#ifndef _TYPEDESCRIPTION_H_
#define _TYPEDESCRIPTION_H_

#ifdef __cplusplus

#include <string>
#include <vector>

namespace eprosima {

/**
 * \brief The name a dependency of a data type is stored under in the Types table.
 *
 * A dependency is a fragment of another type, not a DDS Topic data type of its own, so it has no
 * name the discovery traffic ever announces. *DDS Record & Replay* keys it by its own
 * TypeIdentifier instead, behind this prefix, and skips such a row when it looks a topic's data
 * type up. The separator is not a legal IDL identifier character, so the key cannot collide with
 * a genuine type name.
 */
static const char* const TYPE_DEPENDENCY_PREFIX = "__dep__/";

/**
 * \brief One data type, serialized as the XTypes columns of the Types table hold it.
 *
 * Both strings are base64 of the CDR (XCDRv2, no encapsulation header, zero padded to a multiple
 * of four bytes) of the corresponding XTypes object, which is the encoding *DDS Record & Replay*
 * writes and the *DDS Monitor* and the replayer decode.
 */
typedef struct TypeRepresentation
{
    /// Name of the row in the Types table.
    std::string name;

    /// The complete TypeIdentifier, for the 'information' column.
    std::string identifier;

    /// The complete TypeObject, for the 'object' column.
    std::string object;
} TypeRepresentation;

/**
 * \brief Everything the Types table can be told about one DDS Topic data type.
 *
 * All of it comes from the file given with '-idl', the recorder's only source of data types, so
 * every member is empty when the type was not declared there.
 */
typedef struct TypeDescription
{
    /// The data type rendered as IDL, for the 'idl' column. Read by the user, parsed by nobody.
    std::string idl;

    /// The complete TypeIdentifier of the data type, for the 'information' column.
    std::string identifier;

    /// The complete TypeObject of the data type, for the 'object' column.
    std::string object;

    /**
     * The types this one is built from, each needing a Types row of its own.
     *
     * A TypeObject describes its members by TypeIdentifier, so a type with a structure, union,
     * enumeration or alias member cannot be rebuilt from its own row alone: every type it depends
     * on has to be registered first. They are named with \c TYPE_DEPENDENCY_PREFIX.
     */
    std::vector<TypeRepresentation> dependencies;
} TypeDescription;

} // namespace eprosima

#endif // ifdef __cplusplus

#endif // _TYPEDESCRIPTION_H_
