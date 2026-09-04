/******************************************************************************************
 * Copyright (c) 2015 eProsima. All rights reserved.
 *
 * This copy of eProsima Non-Intrusive DDS Recorder is licensed to you
 * under the terms described in the DDSRECORDER_LICENSE file included in this distribution.
 *
 *****************************************************************************************/
#ifndef _ENDPOINT_H_
#define _ENDPOINT_H_

#ifdef __cplusplus

#include <string>

namespace eprosima {

/**
 * \brief A DataWriter or DataReader seen in the discovery traffic.
 *
 * A user sample carries only the GuidPrefix of its participant and the entity id of its writer,
 * so the topic and the type name it belongs to have to be recovered from the announcement that
 * introduced the endpoint. That is what this remembers.
 */
class Endpoint
{
public:

    Endpoint(
            unsigned int hostId,
            unsigned int appId,
            unsigned int instanceId,
            unsigned int entityId,
            const std::string& topicName,
            const std::string& typeName);

    /**
     * \brief Whether this is the endpoint with the given GUID.
     *
     * \param hostId GuidPrefix of the participant that owns the endpoint.
     * \param appId GuidPrefix of the participant that owns the endpoint.
     * \param instanceId GuidPrefix of the participant that owns the endpoint.
     * \param entityId Entity id of the endpoint inside its participant.
     * \return True if they are equal, false otherwise.
     */
    bool equal(
            unsigned int hostId,
            unsigned int appId,
            unsigned int instanceId,
            unsigned int entityId) const;

    const std::string& getTopicName() const;
    const std::string& getTypeName() const;

private:

    unsigned int m_hostId;
    unsigned int m_appId;
    unsigned int m_instanceId;
    unsigned int m_entityId;
    std::string m_topicName;
    std::string m_typeName;
};
} // namespace eprosima

#endif // ifdef __cplusplus

#endif // _ENDPOINT_H_
