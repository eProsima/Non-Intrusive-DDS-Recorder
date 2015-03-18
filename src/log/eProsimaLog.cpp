/******************************************************************************************
 * Copyright (c) 2015 eProsima. All rights reserved.
 *
 * This copy of eProsima Non-Intrusive DDS Recorder is licensed to you
 * under the terms described in the DDSRECORDER_LICENSE file included in this distribution.
 *
 *****************************************************************************************/
#include "log/eProsimaLog.h"
#include "eProsima_c/macros/snprintf.h"

#include <stdarg.h>

static const char* const CLASS_NAME = "eProsimaLog";

static const char* const EPROSIMA_LOG_MESSAGES[] = {"ERROR<%s::%s>: %s\n", "WARNING<%s::%s>: %s\n", "INFO<%s::%s>: %s\n"};

using namespace eprosima;

eProsimaLog::eProsimaLog(const char *filename) : m_logFile(NULL)
{
    const char* const METHOD_NAME = "eProsimaLog";
    
    if(filename != NULL)
        m_logFile = fopen(filename, "a");

    if(m_logFile == NULL)
        m_logFile = stdout;
}

eProsimaLog::~eProsimaLog()
{
    if(m_logFile != NULL && m_logFile != stdout)
        fclose(m_logFile);
}

void eProsimaLog::setVerbosity(EPROSIMA_LOG_VERBOSITY_LEVEL level)
{
    m_verbosity = level;
}

void eprosima::eProsimaLog_print(eProsimaLog::EPROSIMA_LOG_MESSAGE_TYPE messageType, const char *class_text,
        const char *method_text, const char *message)
{
    printf(EPROSIMA_LOG_MESSAGES[messageType], class_text, method_text, message);
}

void eProsimaLog::write(EPROSIMA_LOG_MESSAGE_TYPE messageType, const char *class_text,
        const char *method_text, const char *message, ...)
{
    const char* const METHOD_NAME = "write";
    va_list arg_ptr;

    if((int)messageType < (int)m_verbosity)
    {
        boost::lock_guard<boost::mutex> lock_guard(m_logMutex);
        SNPRINTF(m_logBuffer, LOG_BUFFER_LENGTH, EPROSIMA_LOG_MESSAGES[messageType],
                class_text, method_text, message);
        va_start(arg_ptr, message);
        vfprintf(m_logFile, m_logBuffer, arg_ptr);
        va_end(arg_ptr);

        fflush(m_logFile);
    }
}

