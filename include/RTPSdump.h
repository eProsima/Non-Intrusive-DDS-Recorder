#ifndef _RTPSDUMP_H_
#define _RTPSDUMP_H_

#include <string>

#include <sqlite3.h>

struct DDS_Time_t;
struct timeval;

#ifdef __cplusplus

namespace eProsima
{
    class eProsimaLog;
    class TypeCodeDB;
    class EntitiesDB;

    class RTPSdump
    {
        public:

            RTPSdump(eProsimaLog &log, std::string &dabase);

            ~RTPSdump();

            static void processDataCallback(void *user, const struct timeval &wts,
                    std::string &ip_src, std::string &ip_dst, unsigned int hostId,
                    unsigned int appId, unsigned int instanceId, unsigned int readerId,
                    unsigned int writerId, unsigned long long writerSequenceNum, 
                    struct DDS_Time_t &sourceTmp, const char *serializedData,
                    unsigned int serializedDataLen);

            void processData(const struct timeval &wts, std::string &ip_src, std::string &ip_dst,
                    unsigned int hostId, unsigned int appId, unsigned int instanceId,
                    unsigned int readerId, unsigned int writerId, unsigned long long writerSeqNum, 
                    struct DDS_Time_t &sourceTmp, const char *serializedData,
                    unsigned int serializedDataLen);

        private:

            void processDataW(const char *serializedData,
                    unsigned int serializedDataLen);

            void processDataR(const char *serializedData,
                    unsigned int serializedDataLen);

            void processDataNormal(const struct timeval &wts, std::string &ip_src, std::string &ip_dst,
                    unsigned int hostId, unsigned int appId, unsigned int instanceId,
                    unsigned int readerId, unsigned int writerId, unsigned long long writerSeqNum,
                    struct DDS_Time_t &sourceTmp, const char *serializedData,
                    unsigned int serializedDataLen);

            eProsimaLog &m_log;
            
            /// Handler of the database.
            sqlite3 *m_databaseH;

            TypeCodeDB *m_typecodeDB;

            EntitiesDB *m_entitiesDB;
    };
}

#endif

#endif // _RTPSDUMP_H_
