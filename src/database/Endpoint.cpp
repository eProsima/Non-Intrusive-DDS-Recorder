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
        unsigned int hostId,
        unsigned int appId,
        unsigned int instanceId,
        unsigned int entityId,
        const string& topicName,
        const string& typeName)
    : m_hostId(hostId)
    , m_appId(appId)
    , m_instanceId(instanceId)
    , m_entityId(entityId)
    , m_topicName(topicName)
    , m_typeName(typeName)
{
}

bool Endpoint::equal(
        unsigned int hostId,
        unsigned int appId,
        unsigned int instanceId,
        unsigned int entityId) const
{
    return hostId == m_hostId &&
           appId == m_appId &&
           instanceId == m_instanceId &&
           entityId == m_entityId;
}

const string& Endpoint::getTopicName() const
{
    return m_topicName;
}

const string& Endpoint::getTypeName() const
{
    return m_typeName;
}
