/******************************************************************************************
 * Copyright (c) 2015 eProsima. All rights reserved.
 *
 * This copy of eProsima Non-Intrusive DDS Recorder is licensed to you
 * under the terms described in the DDSRECORDER_LICENSE file included in this distribution.
 *
 *****************************************************************************************/
#include "reader/pcapReader.h"
#include "RTPSPacketAnalyzer.h"
#include "DDSRecorder.h"
#include "log/eProsimaLog.h"

#include <stdio.h>
#include <string.h>


#define TYPECODE_MAX_SERIALIZED_LENGTH 2048

using namespace std;
using namespace eprosima;

void printHelp()
{
    /* 80 colunms: */
    /*      12345678901234567890123456789012345678901234567890123456789012345678901234567890*/
    printf("DDSRecorder usage: DDSRecorder [<pcapFile>]\n");
    printf("                               [-db <database>]\n");
    printf("                               [-tcMaxSize <size>]\n");
    printf("                               [-idl <idlfile>]\n");
    printf("                               [-queryable]\n");
    printf("                               [-help]\n");
    printf("Options:\n");
    printf("    <pcapFile>: The sniffer file to process (PCAP format required)\n");
    printf("    -db <database>: Database file to store the DDS traffic (Default: dump.db)\n");
    printf("    -tcMaxSize <size>: TypeCode maximum allowed size (Default: 2048)\n");
    printf("    -idl <idlfile>: An IDL file containing the description of the used types.\n");
    printf("    -queryable: Use the queryable database schema, one table per DDS Topic with\n");
    printf("              one column per data type member, instead of the default DDS Record &\n");
    printf("              Replay schema. Requires the data type of every topic to be known.\n");
    printf("    -help: Print help information.\n");
}

#include "idlparser/UserTypeCodeProvider.h"
using namespace eprosima;

//int main(int argc, char *argv[])
//{
//	if(argc>0)
//	{
//		std::string filename = argv[1];
//		UserTypeCodeProvider prov;
//		if(prov.parse_file(filename))
//		{
//			prov.printTypeCodes();
//		}
//		else
//		{
//			std::cout << "There was an error parsing the file "<<std::endl;
//		}
//
//	}
//	else
//		std::cout << "Enter FileName" << std::endl;
//}


int main(
        int argc,
        char * argv[])
{
    int returnedValue{-1};
    string filename;
    string db{"dump.db"};
    string idlfile;
    int tcMaxSize{TYPECODE_MAX_SERIALIZED_LENGTH};
    bool queryable_mode{false};
    eProsimaLog* log{nullptr};
    pcapReader* reader{nullptr};
    RTPSPacketAnalyzer* analyzer{nullptr};
    DDSRecorder* rtpsdumper{nullptr};
    UserTypeCodeProvider* UTCprovider{nullptr};
    unsigned int numRTPSPackets{0};

    /* Check options */
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-help") == 0)
        {
            printHelp();
            return returnedValue;
        }
        else if (strcmp(argv[i], "-db") == 0)
        {
            if (i + 1 < argc)
            {
                db = argv[++i];
            }
            else
            {
                printHelp();
                return returnedValue;
            }
        }
        else if (strcmp(argv[i], "-queryable") == 0)
        {
            queryable_mode = true;
        }
        /*
         * '-monitor' used to select the DDS Record & Replay schema, which is now the default.
         * Without this branch the option would fall through to the catch-all below and be taken
         * for the capture file name, so a script still passing it would be silently misread.
         */
        else if (strcmp(argv[i], "-monitor") == 0)
        {
            printf("Error: -monitor was removed. The DDS Record & Replay schema is now the\n"
                    "       default, so simply drop the option. Use -queryable to get the\n"
                    "       previous per-topic-table schema instead.\n");
            return returnedValue;
        }
        else if (strcmp(argv[i], "-idl") == 0)
        {
            if (i + 1 < argc)
            {
                idlfile = argv[++i];
            }
            else
            {
                printHelp();
                return returnedValue;
            }
        }
        else if (strcmp(argv[i], "-tcMaxSize") == 0)
        {
            if (i + 1 < argc)
            {
                if (sscanf(argv[++i], "%d", &tcMaxSize) != 1)
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
    if (!idlfile.empty())
    {
        UTCprovider = new UserTypeCodeProvider();
        UTCprovider->parse_file(idlfile);
        if (UTCprovider->m_errorCode != UserTypeCodeProvider::PROVIDER_OK)
        {
            printf("Error parsing the IDL file\n");
            delete(UTCprovider);
            return 0;
        }
    }
    if (!filename.empty())
    {
        printf("Processing file...\n");
        log = new eProsimaLog(NULL);

        if (log != NULL)
        {
            log->setVerbosity(eProsimaLog::EPROSIMA_INFO_VERBOSITY_LEVEL);
            reader = new pcapReader(filename, *log);

            if (reader != NULL)
            {
                if (reader->isOpen())
                {
                    analyzer = new RTPSPacketAnalyzer(*log);

                    if (analyzer != NULL)
                    {
                        rtpsdumper = new DDSRecorder(*log, db, tcMaxSize, queryable_mode);
                        rtpsdumper->setUSerTypeCodeProvider(UTCprovider);

                        if (rtpsdumper != NULL)
                        {
                            analyzer->setGetDataCallback((void*)rtpsdumper, DDSRecorder::processDataCallback);
                            numRTPSPackets = reader->processRTPSPackets((void*)analyzer,
                                            RTPSPacketAnalyzer::processRTPSPacketCallback);

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
    if (UTCprovider != NULL)
    {
        delete UTCprovider;
    }
    return returnedValue;
}
