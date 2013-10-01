#ifndef _DDSRECORDER_H_
#define _DDSRECORDER_H_

#include <string>
#include <stdint.h>

#include <sqlite3.h>
#include "RTPSPacketAnalyzer.h"

#ifdef __cplusplus

namespace eProsima
{
    class eProsimaLog;
    class TypeCodeDB;
    class EntitiesDB;

    class DDSRecorder
    {
        public:

            DDSRecorder(eProsimaLog &log, std::string &dabase, int tcMaxSize);

            ~DDSRecorder();

            static void processDataCallback(void *user, const unsigned int npacket, const struct timeval &wts,
                    std::string &ip_src, std::string &ip_dst, unsigned int hostId,
                    unsigned int appId, unsigned int instanceId, unsigned int readerId,
                    unsigned int writerId, unsigned long long writerSequenceNum, 
                    struct DDS_Time_t &sourceTmp, unsigned int destHostId,
                    unsigned int destAppId, unsigned int destInstanceId, bool endianess,
                    const char *serializedData, unsigned int serializedDataLen);

            void processData(const unsigned int npacket, const struct timeval &wts, std::string &ip_src, std::string &ip_dst,
                    unsigned int hostId, unsigned int appId, unsigned int instanceId,
                    unsigned int readerId, unsigned int writerId, unsigned long long writerSeqNum, 
                    struct DDS_Time_t &sourceTmp, unsigned int destHostId,
                    unsigned int destAppId, unsigned int destInstanceId, bool endianess,
                    const char *serializedData, unsigned int serializedDataLen);

        private:

            typedef struct GUID
            {
                public:
                uint32_t hostId;
                uint32_t appId;
                uint32_t instanceId;
                uint32_t objectId;

                GUID() : hostId(0), appId(0),
                    instanceId(0), objectId(0) {}
            } GUID;

            typedef struct PublicationBuiltinTopic
            {
                public:
                
                GUID guid;
                std::string topic_name;
                std::string type_name;
                char *typeCode;
                uint32_t typeCodeLength;
                PublicationBuiltinTopic() : typeCode(NULL), typeCodeLength(0) {}
            } PublicationBuiltinTopic;

            typedef struct SubscriptionBuiltinTopic
            {
                public:
                
                GUID guid;
                std::string topic_name;
                std::string type_name;
                char *typeCode;
                uint32_t typeCodeLength;
                SubscriptionBuiltinTopic() : typeCode(NULL), typeCodeLength(0) {}
            } SubscriptionBuiltinTopic;

            void processDataW(const unsigned int npacket, const struct timeval &wts, std::string &ip_src, std::string &ip_dst,
                    unsigned int hostId, unsigned int appId, unsigned int instanceId,
                    unsigned int readerId, unsigned int writerId, unsigned long long writerSeqNum,
                    struct DDS_Time_t &sourceTmp, unsigned int destHostId,
                    unsigned int destAppId, unsigned int destInstanceId, bool endianess,
                    const char *serializedData, unsigned int serializedDataLen);

            void processDataR(const unsigned int npacket, const struct timeval &wts, std::string &ip_src, std::string &ip_dst,
                    unsigned int hostId, unsigned int appId, unsigned int instanceId,
                    unsigned int readerId, unsigned int writerId, unsigned long long writerSeqNum,
                    struct DDS_Time_t &sourceTmp, unsigned int destHostId,
                    unsigned int destAppId, unsigned int destInstanceId, bool endianess,
                    const char *serializedData, unsigned int serializedDataLen);

            void processDataNormal(const unsigned int npacket, const struct timeval &wts, std::string &ip_src, std::string &ip_dst,
                    unsigned int hostId, unsigned int appId, unsigned int instanceId,
                    unsigned int readerId, unsigned int writerId, unsigned long long writerSeqNum,
                    struct DDS_Time_t &sourceTmp, unsigned int destHostId,
                    unsigned int destAppId, unsigned int destInstanceId, bool endianess,
                    const char *serializedData, unsigned int serializedDataLen);

            bool deserializePublicationBuiltinTopic(bool endianess, char* serializedData, unsigned int serializedDataLength, PublicationBuiltinTopic &pubtopic);

            bool deserializeSubscriptionBuiltinTopic(bool endianess, char* serializedData, unsigned int serializedDataLength, SubscriptionBuiltinTopic &subtopic);

            eProsimaLog &m_log;
            
            /// Handler of the database.
            sqlite3 *m_databaseH;

            TypeCodeDB *m_typecodeDB;

            EntitiesDB *m_entitiesDB;

            int m_tcMaxSize;
    };
}

#endif

#endif // _DDSRECORDER_H_
