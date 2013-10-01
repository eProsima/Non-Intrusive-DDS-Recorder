#include "reader/pcapReader.h"
#include "RTPSPacketAnalyzer.h"
#include "DDSRecorder.h"
#include "eProsima_cpp/eProsimaLog.h"

#include <stdio.h>
#include <string.h>


#define TYPECODE_MAX_SERIALIZED_LENGTH 2048

using namespace std;
using namespace eProsima;

void printHelp()
{
	/* 80 colunms: */
	/*      12345678901234567890123456789012345678901234567890123456789012345678901234567890*/
    printf("DDSRecorder usage: DDSRecorder.exe [<pcapFile>] [-db <database>]\n");
	printf("                                   [-tcMaxSize <size>]\n");
	printf("                                   [-help]\n");
    printf("Options:\n");
    printf("    -db <database>: Database file to store the DDS traffic (Default: dump.db)\n");
    printf("    -tcMaxSize <size>: TypeCode maximum allowed size (Default: 2048)\n");
    printf("    -help: Print help information.\n");
}

int main(int argc, char *argv[])
{
    int returnedValue = -1;
    string filename;
    string db = "dump.db";
    int tcMaxSize = TYPECODE_MAX_SERIALIZED_LENGTH;
    eProsimaLog *log = NULL;
    pcapReader *reader = NULL;
    RTPSPacketAnalyzer *analyzer = NULL;
    DDSRecorder *rtpsdumper = NULL;
    unsigned int numRTPSPackets = 0;

    /* Check options */
    for(int i = 1; i < argc; i++)
    {
        if(strcmp(argv[i], "-help") == 0)
        {
            printHelp();
            return returnedValue;
        }
        else if(strcmp(argv[i], "-db") == 0)
        {
            if(i+1 < argc)
                db = argv[++i];
            else
            {
                printHelp();
                return returnedValue;
            }
        }
        else if(strcmp(argv[i], "-tcMaxSize") == 0)
        {
            if(i+1 < argc)
            {
                if(sscanf(argv[++i], "%d", &tcMaxSize) != 1)
                {
                    printHelp();
                    return returnedValue;
                }
            }
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
            log->setVerbosity(eProsimaLog::EPROSIMA_INFO_VERBOSITY_LEVEL);
            reader = new pcapReader(filename, *log);

            if(reader != NULL)
            {
                if(reader->isOpen())
                {
                    analyzer = new RTPSPacketAnalyzer(*log);

                    if(analyzer != NULL)
                    {
                        rtpsdumper = new DDSRecorder(*log, db, tcMaxSize);

                        if(rtpsdumper != NULL)
                        {
                            analyzer->setGetDataCallback((void*)rtpsdumper, DDSRecorder::processDataCallback);
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
