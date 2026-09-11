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
 *
 * The GUID itself is not held here: MonitorDB keys its endpoints by it, so storing it again would
 * only be a second copy to keep in step.
 */
class Endpoint
{
public:

    Endpoint(
            const std::string& topicName,
            const std::string& typeName);

    const std::string& getTopicName() const;
    const std::string& getTypeName() const;

private:

    std::string m_topicName;
    std::string m_typeName;
};
} // namespace eprosima

#endif // ifdef __cplusplus

#endif // _ENDPOINT_H_
