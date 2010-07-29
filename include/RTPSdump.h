#ifndef _RTPSDUMP_H_
#define _RTPSDUMP_H_

#ifdef __cplusplus

namespace eProsima
{
    class eProsimaLog;

    class RTPSdump
    {
        public:

            RTPSdump(eProsimaLog &log);

            static void processDataCallback(void *user, unsigned int readerId,
                    unsigned int writerId, const char *serializedData,
                    unsigned int serializedDataLen);

            void processData(unsigned int readerId,
                    unsigned int writerId, const char *serializedData,
                    unsigned int serializedDataLen);

        private:

            void processDataW(const char *serializedData,
                    unsigned int serializedDataLen);

            eProsimaLog &m_log;
    };
}

#endif

#endif // _RTPSDUMP_H_
