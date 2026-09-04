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
class eProsimaLog;
class CaptureDB;
class MonitorDB;
class TopicsDB;
class TypeStore;


class DDSRecorder
{
public:

    /**
     * \brief Constructor.
     *
     * \param log Log object used to log errors.
     * \param dabase Name of the database file to write.
     * \param queryable_mode When true, each sample is additionally deserialized into a table of
     * its own topic, with one column per data type member. The *DDS Record & Replay* tables are
     * written either way, so this only ever adds to the recording.
     * \param type_store The data types read from the file given with '-idl'. Not owned, and has
     * to outlive the recorder. May be NULL.
     */
    DDSRecorder(
            eProsimaLog& log,
            std::string& dabase,
            bool queryable_mode,
            const TypeStore * type_store);

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
    } PublicationBuiltinTopic;

    typedef struct SubscriptionBuiltinTopic
    {
    public:

        GUID guid;
        std::string topic_name;
        std::string type_name;
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

    /// Writer of the *DDS Record & Replay* schema.
    MonitorDB * monitor_db_{nullptr};

    /// Writer of the per topic data tables. NULL unless '-queryable' was given.
    TopicsDB * topics_db_{nullptr};

    /// Writer of the packet level tables. NULL unless '-queryable' was given.
    CaptureDB * capture_db_{nullptr};

    /// Data types read from the file given with '-idl'. Not owned, and may be NULL.
    const TypeStore * type_store_{nullptr};
};
} // namespace eprosima

#endif // ifdef __cplusplus

#endif // _DDSRECORDER_H_
