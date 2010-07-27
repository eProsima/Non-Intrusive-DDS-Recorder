#include "reader/pcapReader.h"
#include "RTPSPacketAnalyzer.h"
#include "eProsima_cpp/eProsimaLog.h"

#include <stdio.h>
#include <string.h>

using namespace std;
using namespace eProsima;

void printHelp()
{
    printf("RTPSdump usage: RTPSdump.exe [pcap file]\n");
}

int main(int argc, char *argv[])
{
    int returnedValue = -1;
    string filename;
    eProsimaLog *log = NULL;
    pcapReader *reader = NULL;
    RTPSPacketAnalyzer *analyzer = NULL;

    if(argc > 1)
    {
        filename = argv[1];

        log = new eProsimaLog(NULL);

        if(log != NULL)
        {
            reader = new pcapReader(filename, *log);

            if(reader != NULL)
            {
                if(reader->isOpen())
                {
                    analyzer = new RTPSPacketAnalyzer();

                    if(analyzer != NULL)
                    {
                        reader->processRTPSPackets((void*)analyzer, RTPSPacketAnalyzer::processRTPSPacketCallback);

                        delete analyzer;
                    }
                }

                delete reader;
            }
        }
    }
    else
    {
        printHelp();
    }

    return returnedValue;
}
