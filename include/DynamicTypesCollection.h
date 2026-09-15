/******************************************************************************************
 * Copyright (c) 2015 eProsima. All rights reserved.
 *
 * This copy of eProsima Non-Intrusive DDS Recorder is licensed to you
 * under the terms described in the DDSRECORDER_LICENSE file included in this distribution.
 *
 *****************************************************************************************/
#ifndef _DYNAMICTYPESCOLLECTION_H_
#define _DYNAMICTYPESCOLLECTION_H_

#ifdef __cplusplus

#include <string>
#include <vector>

#include "database/TypeDescription.h"

namespace eprosima {

/// Name of the MCAP attachment the data types of a recording are stored in.
static const char* const DYNAMIC_TYPES_ATTACHMENT_NAME = "dynamic_types";

/**
 * \brief Serializes the data types of a recording as the 'dynamic_types' MCAP attachment holds
 * them.
 *
 * An MCAP file has no table of data types: *DDS Record & Replay* keeps them in a single
 * attachment, the CDR of a \c DynamicTypesCollection, which is a sequence of (type name,
 * TypeIdentifier, TypeObject) triples with the two latter base64 encoded, exactly as the Types
 * table of the SQL schema stores them.
 *
 * Its replayer reads that attachment back with the type support fastddsgen generated for that
 * structure, so the bytes have to be the ones that support writes: XCDRv1, which is what
 * \c DEFAULT_DATA_REPRESENTATION selects, the endianness of this machine, and the encapsulation
 * header included.
 *
 * \param types The types to store, each with the name of its row. Dependencies included: a type
 * cannot be rebuilt without the types it is built from.
 * \param serialized Out parameter holding the bytes of the attachment.
 * \return True value is returned when the collection was serialized.
 */
bool serialize_dynamic_types_collection(
        const std::vector<TypeRepresentation>& types,
        std::string& serialized);

} // namespace eprosima

#endif // ifdef __cplusplus

#endif // _DYNAMICTYPESCOLLECTION_H_
