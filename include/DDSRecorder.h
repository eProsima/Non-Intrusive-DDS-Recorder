/******************************************************************************************
 * Copyright (c) 2015 eProsima. All rights reserved.
 *
 * This copy of eProsima Non-Intrusive DDS Recorder is licensed to you
 * under the terms described in the DDSRECORDER_LICENSE file included in this distribution.
 *
 *****************************************************************************************/
#ifndef _DDSRECORDER_H_
#define _DDSRECORDER_H_

#include <string>
#include <stdint.h>

#include <sqlite3.h>
#include "RTPSPacketAnalyzer.h"

#ifdef __cplusplus

namespace eprosima {
class UserTypeCodeProvider;
} // namespace eprosima
using namespace eprosima;
namespace eprosima {
class eProsimaLog;
class TypeCodeDB;
class EntitiesDB;
class MonitorDB;


class DDSRecorder
{
public:

    /**
     * \brief Constructor.
     *
     * \param log Log object used to log errors.
     * \param dabase Name of the database file to write.
     * \param tcMaxSize TypeCode maximum allowed size.
     * \param monitor_mode When true the recording uses the *DDS Record & Replay* schema
     * instead of the default one. See MonitorDB.
     */
    DDSRecorder(
            eProsimaLog& log,
            std::string& dabase,
            int tcMaxSize,
            bool monitor_mode = false);

    ~DDSRecorder();

    static void processDataCallback(
            void * user,
            const unsigned int npacket,
            const struct timeval & wts,
            std::string& ip_src,
            std::string& ip_dst,
            unsigned int hostId,
            unsigned int appId,
            unsigned int instanceId,
            unsigned int readerId,
            unsigned int writerId,
            unsigned long long writerSequenceNum,
            struct DDS_Time_t & sourceTmp,
            unsigned int destHostId,
            unsigned int destAppId,
            unsigned int destInstanceId,
            bool endianess,
            const char * serializedData,
            unsigned int serializedDataLen);

    void processData(
            const unsigned int npacket,
            const struct timeval & wts,
            std::string& ip_src,
            std::string& ip_dst,
            unsigned int hostId,
            unsigned int appId,
            unsigned int instanceId,
            unsigned int readerId,
            unsigned int writerId,
            unsigned long long writerSeqNum,
            struct DDS_Time_t & sourceTmp,
            unsigned int destHostId,
            unsigned int destAppId,
            unsigned int destInstanceId,
            bool endianess,
            const char * serializedData,
            unsigned int serializedDataLen);

    void setUSerTypeCodeProvider(
            UserTypeCodeProvider* utcp)
    {
        UTCprovider = utcp;
    }

private:

    typedef struct GUID
    {
    public:

        uint32_t hostId;
        uint32_t appId;
        uint32_t instanceId;
        uint32_t objectId;

        GUID() : hostId(0), appId(0),
            instanceId(0), objectId(0) {
        }
    } GUID;

    typedef struct PublicationBuiltinTopic
    {
    public:

        GUID guid;
        std::string topic_name;
        std::string type_name;
        char * typeCode;
        uint32_t typeCodeLength;
        PublicationBuiltinTopic() : typeCode(NULL), typeCodeLength(0) {
        }
    } PublicationBuiltinTopic;

    typedef struct SubscriptionBuiltinTopic
    {
    public:

        GUID guid;
        std::string topic_name;
        std::string type_name;
        char * typeCode;
        uint32_t typeCodeLength;
        SubscriptionBuiltinTopic() : typeCode(NULL), typeCodeLength(0) {
        }
    } SubscriptionBuiltinTopic;

    void processDataW(
            const unsigned int npacket,
            const struct timeval & wts,
            std::string& ip_src,
            std::string& ip_dst,
            unsigned int hostId,
            unsigned int appId,
            unsigned int instanceId,
            unsigned int readerId,
            unsigned int writerId,
            unsigned long long writerSeqNum,
            struct DDS_Time_t & sourceTmp,
            unsigned int destHostId,
            unsigned int destAppId,
            unsigned int destInstanceId,
            bool endianess,
            const char * serializedData,
            unsigned int serializedDataLen);

    void processDataR(
            const unsigned int npacket,
            const struct timeval & wts,
            std::string& ip_src,
            std::string& ip_dst,
            unsigned int hostId,
            unsigned int appId,
            unsigned int instanceId,
            unsigned int readerId,
            unsigned int writerId,
            unsigned long long writerSeqNum,
            struct DDS_Time_t & sourceTmp,
            unsigned int destHostId,
            unsigned int destAppId,
            unsigned int destInstanceId,
            bool endianess,
            const char * serializedData,
            unsigned int serializedDataLen);

    void processDataNormal(
            const unsigned int npacket,
            const struct timeval & wts,
            std::string& ip_src,
            std::string& ip_dst,
            unsigned int hostId,
            unsigned int appId,
            unsigned int instanceId,
            unsigned int readerId,
            unsigned int writerId,
            unsigned long long writerSeqNum,
            struct DDS_Time_t & sourceTmp,
            unsigned int destHostId,
            unsigned int destAppId,
            unsigned int destInstanceId,
            bool endianess,
            const char * serializedData,
            unsigned int serializedDataLen);

    bool deserializePublicationBuiltinTopic(
            bool endianess,
            char* serializedData,
            unsigned int serializedDataLength,
            PublicationBuiltinTopic& pubtopic);

    bool deserializeSubscriptionBuiltinTopic(
            bool endianess,
            char* serializedData,
            unsigned int serializedDataLength,
            SubscriptionBuiltinTopic& subtopic);

    eProsimaLog& m_log;

    /// Handler of the database.
    sqlite3 * m_databaseH;

    TypeCodeDB * m_typecodeDB;

    EntitiesDB * m_entitiesDB;

    /// Writer of the *DDS Record & Replay* schema. NULL unless '-monitor' was given.
    MonitorDB * monitor_db_;

    int m_tcMaxSize;

    UserTypeCodeProvider* UTCprovider;
};
} // namespace eprosima

#endif // ifdef __cplusplus

#endif // _DDSRECORDER_H_
