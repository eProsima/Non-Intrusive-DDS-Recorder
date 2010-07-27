#include "RTPSPacketAnalyzer.h"
#include "eProsima_cpp/eProsimaLog.h"

#include <stdio.h>

using namespace eProsima;

static const char* const CLASS_NAME = "RTPSPacketAnalyzer";

void RTPSPacketAnalyzer::processRTPSPacketCallback(void *user, const char *rtpsPayload)
{
    const char* const METHOD_NAME = "processRTPSPacketCallback";
    RTPSPacketAnalyzer *analyzer = NULL;

    if(user != NULL && rtpsPayload != NULL)
    {
        analyzer = (RTPSPacketAnalyzer*)user;
        analyzer->processRTPSPacket(rtpsPayload);
    }
    else
    {
        printError("Bad parameters");
    }
}

void RTPSPacketAnalyzer::processRTPSPacket(const char *rtpsPayload)
{
}
