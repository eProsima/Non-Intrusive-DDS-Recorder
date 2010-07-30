#ifndef _RTPSDUMP_H_
#define _RTPSDUMP_H_

#include "database/TypeCodeDB.h"
#include <string>

#include <sqlite3.h>

#ifdef __cplusplus

namespace eProsima
{
    class eProsimaLog;

    class RTPSdump
    {
        public:

            RTPSdump(eProsimaLog &log, std::string &dabase);

            ~RTPSdump();

            static void processDataCallback(void *user, unsigned int readerId,
                    unsigned int writerId, const char *serializedData,
                    unsigned int serializedDataLen);

            void processData(unsigned int readerId,
                    unsigned int writerId, const char *serializedData,
                    unsigned int serializedDataLen);

        private:

            void processDataW(const char *serializedData,
                    unsigned int serializedDataLen);

            void processDataR(const char *serializedData,
                    unsigned int serializedDataLen);

            eProsimaLog &m_log;
            
            /// Handler of the database.
            sqlite3 *m_databaseH;

            TypeCodeDB *m_typecodeDB;
    };
}

#endif

#endif // _RTPSDUMP_H_
