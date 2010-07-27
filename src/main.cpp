#include "reader/pcapReader.h"
#include "eProsima_cpp/eProsimaLog.h"

#include <stdio.h>
#include <string.h>

using namespace std;
using namespace eProsima;

void printHelp()
{
    printf("RTPSdump usage: RTPSdump.exe [pcap file]\n");
}


void prueba(void *user, u_char *rtpsPayload)
{
}

int main(int argc, char *argv[])
{
    int returnedValue = -1;
    string filename;
    eProsimaLog *log = NULL;
    pcapReader *reader = NULL;

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
                    reader->processRTPSPackets(prueba);
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
