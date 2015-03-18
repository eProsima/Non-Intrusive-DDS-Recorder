/******************************************************************************************
 * Copyright (c) 2015 eProsima. All rights reserved.
 *
 * This copy of eProsima Non-Intrusive DDS Recorder is licensed to you
 * under the terms described in the DDSRECORDER_LICENSE file included in this distribution.
 *
 *****************************************************************************************/
#ifndef _EPROSIMA_CPP_EPROSIMALOG_H_
#define _EPROSIMA_CPP_EPROSIMALOG_H_

#include <stdio.h>
#include <boost/thread.hpp>

#undef printError
#undef printWarning
#undef printInfo
#undef logError
#undef logWarning
#undef logInfo

#define LOG_BUFFER_LENGTH 300

#define printError(message) eProsimaLog_print(eProsimaLog::EPROSIMA_LOG_ERROR, CLASS_NAME, METHOD_NAME, message);

#define printWarning(message) eProsimaLog_print(eProsimaLog::EPROSIMA_LOG_WARNING, CLASS_NAME, METHOD_NAME, message);

#define printInfo(message) eProsimaLog_print(eProsimaLog::EPROSIMA_LOG_INFO, CLASS_NAME, METHOD_NAME, message);

#define logError(logObject, message, ...) logObject.write(eProsimaLog::EPROSIMA_LOG_ERROR, CLASS_NAME, METHOD_NAME, message, ##__VA_ARGS__);

#define logWarning(logObject, message, ...) logObject.writeeProsimaLog::EPROSIMA_LOG_WARNING, CLASS_NAME, METHOD_NAME, message, ##__VA_ARGS__);

#define logInfo(logObject, message, ...) logObject.write(eProsimaLog::EPROSIMA_LOG_INFO, CLASS_NAME, METHOD_NAME, message, ##__VA_ARGS__);

#ifdef __cplusplus
namespace eprosima
{
    class eProsimaLog
    {
        public:

            typedef enum EPROSIMA_LOG_VERBOSITY_LEVEL
            {
                EPROSIMA_QUIET_VERBOSITY_LEVEL = 0,
                EPROSIMA_ERROR_VERBOSITY_LEVEL,
                EPROSIMA_WARNING_VERBOSITY_LEVEL,
                EPROSIMA_INFO_VERBOSITY_LEVEL
            } EPROSIMA_LOG_VERBOSITY_LEVEL;

            typedef enum EPROSIMA_LOG_MESSAGE_TYPE
            {
                EPROSIMA_LOG_ERROR = 0,
                EPROSIMA_LOG_WARNING,
                EPROSIMA_LOG_INFO
            } EPROSIMA_LOG_MESSAGE_TYPE;

            eProsimaLog(const char *filename);

            ~eProsimaLog();

            void setVerbosity(EPROSIMA_LOG_VERBOSITY_LEVEL level);

            void write(EPROSIMA_LOG_MESSAGE_TYPE messageType, const char *class_text,
                    const char *method_text, const char *message, ...);

        private:

            EPROSIMA_LOG_VERBOSITY_LEVEL m_verbosity;

            boost::mutex m_logMutex;

            FILE *m_logFile;

            char m_logBuffer[LOG_BUFFER_LENGTH];
    };

    void eProsimaLog_print(eProsimaLog::EPROSIMA_LOG_MESSAGE_TYPE messageType,const char *class_text,
            const char *method_text, const char *message);

} // eprosima
#endif // __cplusplus

#endif // _EPROSIMA_CPP_EPROSIMALOG_H_
