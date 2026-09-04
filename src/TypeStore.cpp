/******************************************************************************************
 * Copyright (c) 2015 eProsima. All rights reserved.
 *
 * This copy of eProsima Non-Intrusive DDS Recorder is licensed to you
 * under the terms described in the DDSRECORDER_LICENSE file included in this distribution.
 *
 *****************************************************************************************/
#include "TypeStore.h"
#include "log/eProsimaLog.h"

#include <sstream>

#include <fastdds/dds/xtypes/dynamic_types/DynamicTypeBuilder.hpp>
#include <fastdds/dds/xtypes/dynamic_types/DynamicTypeBuilderFactory.hpp>
#include <fastdds/dds/xtypes/utils.hpp>

using namespace eprosima;
using namespace eprosima::fastdds::dds;
using namespace std;

static const char* const CLASS_NAME = "TypeStore";

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
    DynamicType::_ref_type type = find(type_name);

    if (!type)
    {
        return string();
    }

    ostringstream idl;

    if (RETCODE_OK != idl_serialize(type, idl))
    {
        logError(log_, "Cannot render the data type %s as IDL", type_name.c_str());
        return string();
    }

    return idl.str();
}

size_t TypeStore::size() const
{
    return types_.size();
}
