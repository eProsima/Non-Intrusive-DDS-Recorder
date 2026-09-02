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
#include "TypeStore.h"
#include "log/eProsimaLog.h"
#include "writer/McapRecorder.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;
using namespace eprosima;

/*
 * Exit status. Every path used to return -1, success included, which left a script wrapping the
 * recorder with nothing to test: a run that failed to open its capture was indistinguishable
 * from one that recorded it. The convention is the usual one, so the shell's && and || mean what
 * a caller expects.
 *
 * Recording no packets is not a failure. A capture that holds no RTPS traffic is a valid input
 * and produces a valid, empty recording; the packet count on stdout is what tells them apart.
 */
static constexpr int EXIT_OK = EXIT_SUCCESS;    /* the run did what was asked */
static constexpr int EXIT_ERROR = EXIT_FAILURE; /* it could not be carried out */
static constexpr int EXIT_USAGE = 2;            /* the command line was not understood */

void printHelp()
{
    /* 80 colunms: */
    /*      12345678901234567890123456789012345678901234567890123456789012345678901234567890*/
    printf("ni_ddsrecorder usage: ni_ddsrecorder [<pcapFile>]\n");
    printf("                                     [-db <database>]\n");
    printf("                                     [-idl <idlfile>]\n");
    printf("                                     [-queryable]\n");
    if (McapRecorder::is_supported())
    {
        printf("                                     [-mcap <mcapfile>]\n");
    }
    printf("                                     [-help]\n");
    printf("Options:\n");
    printf("    <pcapFile>: The sniffer file to process (PCAP format required)\n");
    printf("    -db <database>: Database file to store the DDS traffic (Default: dump.db)\n");
    printf("    -idl <idlfile>: An IDL file containing the description of the used types.\n");
    printf("              It is the only source of data types, and it is needed only to fill\n");
    printf("              the idl column of the Types table: the samples themselves are\n");
    printf("              recorded as CDR whether the type is known or not.\n");
    printf("    -queryable: Also store each sample in a table of its own DDS Topic, with one\n");
    printf("              column per data type member. Needs -idl to know the data types; the\n");
    printf("              DDS Record & Replay tables are written either way. DataTables says\n");
    printf("              which table holds which topic.\n");
    if (McapRecorder::is_supported())
    {
        printf("    -mcap <mcapfile>: Write an MCAP file instead of a database. Cannot be used\n");
        printf("              together with -db. No IDL file is required.\n");
    }
    printf("    -help: Print help information.\n");
}

int main(
        int argc,
        char * argv[])
{
    /*
     * Failure until a capture has actually been processed, so any path that falls out of the
     * nesting below without recording -- an unopenable file, a failed allocation -- reports it
     * without each one having to remember to say so.
     */
    int returnedValue{EXIT_ERROR};
    string filename;
    string db{"dump.db"};
    string idlfile;
    bool queryable_mode{false};
    string mcap_file;
    bool db_given{false};
    eProsimaLog* log{nullptr};
    pcapReader* reader{nullptr};
    RTPSPacketAnalyzer* analyzer{nullptr};
    DDSRecorder* rtpsdumper{nullptr};
    TypeStore* type_store{nullptr};
    unsigned int numRTPSPackets{0};

    /* Check options */
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-help") == 0)
        {
            printHelp();
            return EXIT_OK;
        }
        else if (strcmp(argv[i], "-db") == 0)
        {
            if (i + 1 < argc)
            {
                db = argv[++i];
                db_given = true;
            }
            else
            {
                printHelp();
                return EXIT_USAGE;
            }
        }
        else if (strcmp(argv[i], "-queryable") == 0)
        {
            queryable_mode = true;
        }
        else if (strcmp(argv[i], "-mcap") == 0)
        {
            if (i + 1 < argc)
            {
                mcap_file = argv[++i];
            }
            else
            {
                printHelp();
                return returnedValue;
            }
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
                return EXIT_USAGE;
            }
        }
        else
        {
            filename = argv[i];
        }
    }

    if (!mcap_file.empty() && !McapRecorder::is_supported())
    {
        printf("Error: -mcap is not available: this build has no MCAP support.\n"
                "       Rebuild with -DMCAP_SUPPORT=ON.\n");
        return EXIT_USAGE;
    }

    /* The MCAP output replaces the database, so asking for both is a contradiction. */
    if (db_given && !mcap_file.empty())
    {
        printf("Error: -db and -mcap cannot be used together. Choose one output.\n");
        return EXIT_USAGE;
    }

    if (!filename.empty())
    {
        printf("Processing file...\n");
        log = new eProsimaLog(NULL);

        if (log != NULL)
        {
            log->setVerbosity(eProsimaLog::EPROSIMA_INFO_VERBOSITY_LEVEL);

            /*
             * The IDL file is parsed once, before any packet is read, because a type may be
             * announced by several endpoints and the file is the only place it can come from.
             * A file that does not parse is fatal: the user asked for the types to be described
             * and silently recording without them would hide the mistake.
             */
            if (!idlfile.empty())
            {
                type_store = new TypeStore(*log);

                if (!type_store->load(idlfile))
                {
                    printf("Error parsing the IDL file %s\n", idlfile.c_str());
                    delete type_store;
                    delete log;
                    return EXIT_ERROR;
                }
            }

            reader = new pcapReader(filename, *log);

            if (reader != NULL)
            {
                if (reader->isOpen())
                {
                    analyzer = new RTPSPacketAnalyzer(*log);

                    if (analyzer != NULL)
                    {
                        rtpsdumper = new DDSRecorder(*log, db, queryable_mode, type_store,
                                        mcap_file);

                        if (rtpsdumper != NULL)
                        {
                            analyzer->setGetDataCallback((void*)rtpsdumper, DDSRecorder::processDataCallback);
                            numRTPSPackets = reader->processRTPSPackets((void*)analyzer,
                                            RTPSPacketAnalyzer::processRTPSPacketCallback);

                            printf("Number of processed RTPS packets: %u\n", numRTPSPackets);
                            returnedValue = EXIT_OK;

                            delete rtpsdumper;
                        }

                        delete analyzer;
                    }
                }

                delete reader;
            }

            if (type_store != nullptr)
            {
                delete type_store;
            }

            delete log;
        }
    }
    else
    {
        /* No capture file named: nothing to do, and the command line is why. */
        printHelp();
        returnedValue = EXIT_USAGE;
    }

    return returnedValue;
}
