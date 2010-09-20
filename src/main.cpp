#include "reader/pcapReader.h"
#include "RTPSPacketAnalyzer.h"
#include "RTPSdump.h"
#include "eProsima_cpp/eProsimaLog.h"

#include "ndds/ndds_config_c.h"

#include <stdio.h>
#include <string.h>

using namespace std;
using namespace eProsima;

void printHelp()
{
    printf("RTPSdump usage: RTPSdump.exe [--db database] [pcap file]\n");
    printf("Options:\n");
    printf("    --db file: Database file where information will be dumped (Default: dump.db).\n");
    printf("    --help: Print help information.\n");
}

int main(int argc, char *argv[])
{
    int returnedValue = -1;
    string filename;
    string db = "dump.db";
    eProsimaLog *log = NULL;
    pcapReader *reader = NULL;
    RTPSPacketAnalyzer *analyzer = NULL;
    RTPSdump *rtpsdumper = NULL;
    unsigned int numRTPSPackets = 0;

    /* Check options */
    for(int i = 1; i < argc; i++)
    {
        if(strcmp(argv[i], "--help") == 0)
        {
            printHelp();
            return returnedValue;
        }
        else if(strcmp(argv[i], "--db") == 0)
        {
            if(i+1 < argc)
                db = argv[++i];
            else
            {
                printHelp();
                return returnedValue;
            }
        }
        else
        {
            filename = argv[i];
        }
    }

    /*NDDS_Config_Logger_set_verbosity(NDDS_Config_Logger_get_instance(),
            NDDS_CONFIG_LOG_VERBOSITY_STATUS_ALL);*/

    if(!filename.empty())
    {
        log = new eProsimaLog(NULL);

        if(log != NULL)
        {
            log->setVerbosity(EPROSIMA_INFO_VERBOSITY_LEVEL);
            reader = new pcapReader(filename, *log);

            if(reader != NULL)
            {
                if(reader->isOpen())
                {
                    analyzer = new RTPSPacketAnalyzer(*log);

                    if(analyzer != NULL)
                    {
                        rtpsdumper = new RTPSdump(*log, db);

                        if(rtpsdumper != NULL)
                        {
                            analyzer->setGetDataCallback((void*)rtpsdumper, RTPSdump::processDataCallback);
                            numRTPSPackets = reader->processRTPSPackets((void*)analyzer, RTPSPacketAnalyzer::processRTPSPacketCallback);

                            printf("Number of processed RTPS packets: %u\n", numRTPSPackets);

                            delete rtpsdumper;
                        }

                        delete analyzer;
                    }
                }

                delete reader;
            }

            delete log;
        }
    }
    else
    {
        printHelp();
    }

    return returnedValue;
}
