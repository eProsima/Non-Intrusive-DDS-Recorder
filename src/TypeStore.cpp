/******************************************************************************************
 * Copyright (c) 2015 eProsima. All rights reserved.
 *
 * This copy of eProsima Non-Intrusive DDS Recorder is licensed to you
 * under the terms described in the DDSRECORDER_LICENSE file included in this distribution.
 *
 *****************************************************************************************/
#include "TypeStore.h"

#include <sstream>
#include <vector>

#include <fastcdr/Cdr.h>
#include <fastcdr/CdrSizeCalculator.hpp>
#include <fastcdr/FastBuffer.h>

#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/xtypes/dynamic_types/DynamicTypeBuilder.hpp>
#include <fastdds/dds/xtypes/dynamic_types/DynamicTypeMember.hpp>
#include <fastdds/dds/xtypes/dynamic_types/MemberDescriptor.hpp>
#include <fastdds/dds/xtypes/dynamic_types/DynamicTypeBuilderFactory.hpp>
#include <fastdds/dds/xtypes/type_representation/ITypeObjectRegistry.hpp>
#include <fastdds/dds/xtypes/type_representation/TypeObject.hpp>
#include <fastdds/dds/xtypes/type_representation/TypeObjectUtils.hpp>
#include <fastdds/dds/xtypes/utils.hpp>
#include <fastdds/rtps/common/SerializedPayload.hpp>

/*
 * After the Fast DDS headers on purpose: fastdds/dds/log/Log.hpp defines a logError of its own,
 * with a different signature, and this header undefines it before defining ours.
 */
#include "log/eProsimaLog.h"

using namespace eprosima;
using namespace eprosima::fastdds::dds;
using namespace std;

static const char* const CLASS_NAME = "TypeStore";

static const char* const BASE64_ALPHABET =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

/*
 * The Types table holds its XTypes columns as base64, so what is written is text whatever the
 * bytes are. This is the encoding cpp_utils::base64_encode uses in *DDS Record & Replay*, and the
 * replayer decodes the columns with its counterpart, so it has to be the standard alphabet and
 * the standard '=' padding.
 */
static string base64_encode(
        const string& in)
{
    string out;
    int val = 0;
    int valb = -6;

    for (unsigned char c : in)
    {
        val = (val << 8) + c;
        valb += 8;

        while (valb >= 0)
        {
            out.push_back(BASE64_ALPHABET[(val >> valb) & 0x3F]);
            valb -= 6;
        }
    }

    if (valb > -6)
    {
        out.push_back(BASE64_ALPHABET[((val << 8) >> (valb + 8)) & 0x3F]);
    }

    while (out.size() % 4)
    {
        out.push_back('=');
    }

    return out;
}

/*
 * Serializes a TypeIdentifier or a TypeObject the way *DDS Record & Replay* does, which is what
 * makes the column readable by its replayer and by the *DDS Monitor*: XCDRv2, the endianness of
 * this machine, no encapsulation header, and zero padding up to a multiple of four bytes.
 *
 * The padding is part of that format, not an accident: Serializer::type_data_to_type_str_ adds it
 * as well. A decoder reads the object and stops, so the trailing bytes are ignored; only the MD5
 * the TypeIdentifier carries is taken over the unpadded length.
 */
template<typename T>
static bool serialize_type_data(
        const T& data,
        string& serialized)
{
    try
    {
        fastcdr::CdrSizeCalculator calculator(fastcdr::CdrVersion::XCDRv2);
        size_t current_alignment = 0;
        size_t capacity = calculator.calculate_serialized_size(data, current_alignment) +
                fastdds::rtps::SerializedPayload_t::representation_header_size;

        // Zero filled, so the padding below needs nothing written into it.
        vector<char> buffer(capacity, 0);
        fastcdr::FastBuffer fastbuffer(buffer.data(), buffer.size());
        fastcdr::Cdr serializer(fastbuffer, fastcdr::Cdr::DEFAULT_ENDIAN, fastcdr::CdrVersion::XCDRv2);

        fastcdr::serialize(serializer, data);

        size_t length = serializer.get_serialized_data_length();
        size_t padded = (length + 3) & ~static_cast<size_t>(3);

        // The header size the capacity was grown by is four bytes, so the padding always fits.
        serialized.assign(buffer.data(), padded);

        return true;
    }
    catch (const std::exception&)
    {
        return false;
    }
}

TypeStore::TypeStore(
        eProsimaLog& log)
    : log_(log)
{
}

bool TypeStore::load(
        const string& idl_file)
{
    const char* const METHOD_NAME = "load";

    types_.clear();
    idl_cache_.clear();

    /*
     * for_each_type_w_uri parses the document once and calls back for every declared type, which
     * is what lets a file describing several types be given as a whole. The alternative,
     * create_type_w_uri, would need the type name up front, and the type names only become known
     * later, from the discovery traffic.
     */
    ReturnCode_t ret = DynamicTypeBuilderFactory::get_instance()->for_each_type_w_uri(
        idl_file,
        IncludePathSeq(),
        [this](DynamicTypeBuilder::_ref_type builder) -> bool
        {
            if (builder)
            {
                DynamicType::_ref_type type = builder->build();

                if (type)
                {
                    types_[type->get_name().to_string()] = type;
                }
            }

            // Keep going even when one type failed to build, so the rest of the file is still read.
            return true;
        });

    if (RETCODE_OK != ret)
    {
        logError(log_, "Cannot parse the IDL file %s", idl_file.c_str());
        types_.clear();
        idl_cache_.clear();
        return false;
    }

    if (types_.empty())
    {
        logError(log_, "The IDL file %s declares no data type", idl_file.c_str());
        return false;
    }

    return true;
}

DynamicType::_ref_type TypeStore::find(
        const string& type_name) const
{
    map<string, DynamicType::_ref_type>::const_iterator it = types_.find(type_name);

    return it != types_.end() ? it->second : DynamicType::_ref_type();
}

string TypeStore::idl_for(
        const string& type_name) const
{
    const char* const METHOD_NAME = "idl_for";
    map<string, string>::const_iterator cached = idl_cache_.find(type_name);

    if (cached != idl_cache_.end())
    {
        return cached->second;
    }

    DynamicType::_ref_type type = find(type_name);
    string rendered;

    if (!type)
    {
        /* Cached as well: an unknown type name would otherwise be looked up again every packet. */
        idl_cache_[type_name] = rendered;
        return rendered;
    }

    ostringstream idl;

    if (RETCODE_OK != idl_serialize(type, idl))
    {
        logError(log_, "Cannot render the data type %s as IDL", type_name.c_str());
    }
    else
    {
        rendered = idl.str();
    }

    idl_cache_[type_name] = rendered;

    return rendered;
}

const TypeDescription& TypeStore::describe(
        const string& type_name) const
{
    map<string, TypeDescription>::const_iterator cached = description_cache_.find(type_name);

    if (cached != description_cache_.end())
    {
        return cached->second;
    }

    TypeDescription description;

    description.idl = idl_for(type_name);

    DynamicType::_ref_type type = find(type_name);

    if (type)
    {
        generate_xtypes(type_name, type, description);
    }

    return description_cache_.insert(make_pair(type_name, description)).first->second;
}

void TypeStore::generate_xtypes(
        const string& type_name,
        const DynamicType::_ref_type& type,
        TypeDescription& description) const
{
    const char* const METHOD_NAME = "generate_xtypes";

    /*
     * The registry is where a TypeIdentifier and a TypeObject can be had from a DynamicType at
     * all, and it is also what resolves the dependencies below. Registering is local: it computes
     * the identifiers and stores them in this process, and reaches no DDS domain.
     */
    xtypes::ITypeObjectRegistry& registry =
            DomainParticipantFactory::get_instance()->type_object_registry();
    xtypes::TypeIdentifierPair type_ids;

    if (RETCODE_OK != registry.register_typeobject_w_dynamic_type(type, type_ids))
    {
        logError(log_, "Cannot generate the XTypes description of the data type %s",
                type_name.c_str());
        return;
    }

    /*
     * Which half of the pair is the complete one depends on how the type got registered, so it is
     * asked for by kind rather than by position. The complete one is the one that is wanted: the
     * minimal TypeObject drops the member names, and a reader of this file wants to see them.
     *
     * The flag means the opposite of what the parameter is called and documented ("Returns if
     * there was an error"): TypeObjectUtils sets it true on entry and clears it only on the
     * inconsistent path, so it reads true when the identifier that comes back is usable.
     */
    bool consistent = false;
    const xtypes::TypeIdentifier& identifier =
            xtypes::TypeObjectUtils::retrieve_complete_type_identifier(type_ids, consistent);

    if (!consistent)
    {
        logError(log_, "The data type %s has no complete TypeIdentifier", type_name.c_str());
        return;
    }

    generate_dependencies(type_name, identifier, description);

    xtypes::TypeObject type_object;

    if (RETCODE_OK != registry.get_type_object(identifier, type_object))
    {
        logError(log_, "Cannot get the TypeObject of the data type %s", type_name.c_str());
        return;
    }

    string serialized_identifier;
    string serialized_object;

    if (!serialize_type_data(identifier, serialized_identifier) ||
            !serialize_type_data(type_object, serialized_object))
    {
        logError(log_, "Cannot serialize the XTypes description of the data type %s",
                type_name.c_str());
        return;
    }

    description.identifier = base64_encode(serialized_identifier);
    description.object = base64_encode(serialized_object);
}

void TypeStore::generate_dependencies(
        const string& type_name,
        const eprosima::fastdds::dds::xtypes::TypeIdentifier& identifier,
        TypeDescription& description) const
{
    const char* const METHOD_NAME = "generate_dependencies";

    xtypes::ITypeObjectRegistry& registry =
            DomainParticipantFactory::get_instance()->type_object_registry();

    /*
     * get_type_information walks the type and returns what it is built from, which is the only
     * way to reach the types a TypeObject names but does not describe. The identifier is passed
     * in the first half of the pair, as BaseHandler::store_dynamic_type_ does.
     */
    xtypes::TypeIdentifierPair complete_ids;
    complete_ids.type_identifier1(identifier);

    xtypes::TypeInformation information;

    if (RETCODE_OK != registry.get_type_information(complete_ids, information, true))
    {
        logError(log_, "Cannot get the TypeInformation of the data type %s", type_name.c_str());
        return;
    }

    const vector<xtypes::TypeIdentfierWithSize>& dependencies =
            information.complete().dependent_typeids();

    for (vector<xtypes::TypeIdentfierWithSize>::const_iterator it = dependencies.begin();
            it != dependencies.end(); ++it)
    {
        const xtypes::TypeIdentifier& dependency = it->type_id();
        xtypes::TypeObject dependency_object;

        if (RETCODE_OK != registry.get_type_object(dependency, dependency_object))
        {
            logError(log_, "Cannot get the TypeObject a dependency of the data type %s names",
                    type_name.c_str());
            continue;
        }

        string serialized_identifier;
        string serialized_object;

        if (!serialize_type_data(dependency, serialized_identifier) ||
                !serialize_type_data(dependency_object, serialized_object))
        {
            logError(log_, "Cannot serialize a dependency of the data type %s", type_name.c_str());
            continue;
        }

        TypeRepresentation representation;

        representation.identifier = base64_encode(serialized_identifier);
        representation.object = base64_encode(serialized_object);
        /*
         * A dependency has no name of its own here, so it is keyed by its own TypeIdentifier, the
         * way *DDS Record & Replay* keys it. Naming it after the type it belongs to would risk
         * shadowing a real DDS type with that very name, and the Types table is keyed by name.
         */
        representation.name = string(TYPE_DEPENDENCY_PREFIX) + representation.identifier;

        description.dependencies.push_back(representation);
    }
}

bool TypeStore::is_keyed(
        const string& type_name) const
{
    DynamicType::_ref_type type = find(type_name);

    if (!type)
    {
        return false;
    }

    uint32_t count = type->get_member_count();

    for (uint32_t i = 0; i < count; ++i)
    {
        DynamicTypeMember::_ref_type member;

        if (RETCODE_OK != type->get_member_by_index(member, i))
        {
            continue;
        }

        MemberDescriptor::_ref_type descriptor = traits<MemberDescriptor>::make_shared();

        if (RETCODE_OK == member->get_descriptor(descriptor) && descriptor->is_key())
        {
            return true;
        }
    }

    return false;
}

size_t TypeStore::size() const
{
    return types_.size();
}
