/******************************************************************************************
 * Copyright (c) 2015 eProsima. All rights reserved.
 *
 * This copy of eProsima Non-Intrusive DDS Recorder is licensed to you
 * under the terms described in the DDSRECORDER_LICENSE file included in this distribution.
 *
 *****************************************************************************************/
#include "database/Endpoint.h"

using namespace eprosima;
using namespace std;

Endpoint::Endpoint(
        const string& topicName,
        const string& typeName)
    : m_topicName(topicName)
    , m_typeName(typeName)
{
}

const string& Endpoint::getTopicName() const
{
    return m_topicName;
}

const string& Endpoint::getTypeName() const
{
    return m_typeName;
}
