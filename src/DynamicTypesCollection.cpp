/******************************************************************************************
 * Copyright (c) 2015 eProsima. All rights reserved.
 *
 * This copy of eProsima Non-Intrusive DDS Recorder is licensed to you
 * under the terms described in the DDSRECORDER_LICENSE file included in this distribution.
 *
 *****************************************************************************************/
#include "DynamicTypesCollection.h"

#include <array>
#include <exception>

#include <fastcdr/Cdr.h>
#include <fastcdr/FastBuffer.h>

using namespace eprosima;
using namespace std;

/*
 * The element of the collection, written exactly as fastddsgen generates it for the structure
 * *DDS Record & Replay* declares:
 *
 *     struct DynamicType { string type_name; string type_identifier; string type_object; };
 *
 * Member names never reach the wire, so TypeRepresentation stands in for that structure; what has
 * to match is the order of the three strings and the encoding. The encoding follows the CDR
 * version the way the generated code does, so that a caller serializing as XCDRv2 would get the
 * DHEADER that version calls for, although the attachment is written as XCDRv1.
 *
 * Specializing eprosima::fastcdr::serialize is how a type tells Fast CDR how to encode itself:
 * the library declares the template and leaves it to the type to define it, which is what lets
 * the sequence below serialize its elements.
 */
namespace eprosima {
namespace fastcdr {

template<>
void serialize(
        Cdr& scdr,
        const eprosima::TypeRepresentation& data)
{
    Cdr::state current_state(scdr);

    scdr.begin_serialize_type(current_state,
            CdrVersion::XCDRv2 == scdr.get_cdr_version()
            ? EncodingAlgorithmFlag::DELIMIT_CDR2 : EncodingAlgorithmFlag::PLAIN_CDR);

    scdr << MemberId(0) << data.name
        << MemberId(1) << data.identifier
        << MemberId(2) << data.object;

    scdr.end_serialize_type(current_state);
}

} // namespace fastcdr
} // namespace eprosima

bool eprosima::serialize_dynamic_types_collection(
        const vector<TypeRepresentation>& types,
        string& serialized)
{
    try
    {
        // Default constructed, so it owns its memory and grows as the collection is written into
        // it. The generated type support sizes the buffer up front instead, which needs a size
        // calculation for every structure involved; the bytes that come out are the same.
        fastcdr::FastBuffer buffer;
        fastcdr::Cdr serializer(buffer, fastcdr::Cdr::DEFAULT_ENDIAN, fastcdr::CdrVersion::XCDRv1);

        serializer.set_encoding_flag(fastcdr::EncodingAlgorithmFlag::PLAIN_CDR);
        serializer.serialize_encapsulation();

        // The collection is a structure with the sequence of types as its only member.
        fastcdr::Cdr::state current_state(serializer);
        serializer.begin_serialize_type(current_state, fastcdr::EncodingAlgorithmFlag::PLAIN_CDR);
        serializer << fastcdr::MemberId(0) << types;
        serializer.end_serialize_type(current_state);

        // Writes the two option bytes of the encapsulation header, which the generated type
        // support leaves at zero.
        serializer.set_dds_cdr_options({0, 0});

        serialized.assign(buffer.getBuffer(), serializer.get_serialized_data_length());

        return true;
    }
    catch (const std::exception&)
    {
        return false;
    }
}
