#include "reader/pcapReader.h"
#include "eProsima_cpp/eProsimaLog.h"

#ifdef RTI_WIN32
#include <winsock.h>

/* Ethernet header */
struct ether_header
{
    u_int8_t ether_dhost[6];
    u_int8_t ether_shost[6];
    u_int16_t ether_type;
};

typedef struct ip_address
{
	u_char byte1;
	u_char byte2;
	u_char byte3;
	u_char byte4;
} ip_address;

/* IPv4 header */
struct ip
{
	u_char	ver_ihl;		// Version (4 bits) + Internet header length (4 bits)
	u_char	tos;			// Type of service 
	u_short tlen;			// Total length 
	u_short identification; // Identification
	u_short flags_fo;		// Flags (3 bits) + Fragment offset (13 bits)
	u_char	ttl;			// Time to live
	u_char	ip_p;			// Protocol
	u_short crc;			// Header checksum
	ip_address	saddr;		// Source address
	ip_address	daddr;		// Destination address
	u_int	op_pad;			// Option + Padding
};

/* UDP header*/
struct udphdr
{
	u_short sport;			// Source port
	u_short dport;			// Destination port
	u_short len;			// Datagram length
	u_short crc;			// Checksum
};

#define ETHERTYPE_IP 0x0800
#define IP_HEADER_LEN(ip) ((ip->ver_ihl & 0xf) * 4)

#else
#include <netinet/in.h>
#include <netinet/if_ether.h>
#include <netinet/ip.h>
#include <netinet/udp.h>

#define IP_HEADER_LEN(ip) ip->ip_hl * 4

#endif //RTI_WIN32

using namespace std;
using namespace eProsima;

static const char* const CLASS_NAME = "pcapReader";

pcapReader::pcapReader(string &filename, eProsimaLog &log) : m_filename(filename), m_log(log), m_pcap(NULL),
    m_npackets(0), m_callback(NULL)
{
    const char* const METHOD_NAME = "pcapReader";

    m_pcap = pcap_open_offline(m_filename.c_str(), m_pcapErrorBuf);

    if(m_pcap == NULL)
    {
        logError(m_log, "Cannot open file %s in read mode: %s", m_filename.c_str(), m_pcapErrorBuf);
    }
}

pcapReader::~pcapReader()
{
    if(m_pcap != NULL)
    {
        pcap_close(m_pcap);
    }
}

bool pcapReader::isOpen()
{
    return (m_pcap != NULL);
}

unsigned int pcapReader::processRTPSPackets(processRTPSPacketCallback callback)
{
    const char* const METHOD_NAME = "processRTPSPackets";
    unsigned int returnedValue = 0;

    if(callback != NULL)
    {
        if(m_pcap != NULL)
        {
            m_callback = callback;

            if(pcap_dispatch(m_pcap, 0, pcapReader::processPacketCallback, (u_char*)this) >= 0)
            {
                returnedValue = m_npackets;
                m_npackets = 0;
                m_callback = NULL;
            }
            else
            {
                logError(m_log, "Pcap library error processing packets in file.");
            }
        }
        else
        {
            logError(m_log, "The file wasn't opened");
        }
    }
    else
    {
        logError(m_log, "Bad parameters (callback).");
    }

    return returnedValue;
}

void pcapReader::processPacketCallback(u_char *user, const struct pcap_pkthdr *hdr, const u_char *data)
{
    const char* const METHOD_NAME = "processPacketCallback";
    pcapReader *reader = NULL;

    if(user != NULL && hdr != NULL && data != NULL)
    {
        reader = (pcapReader*)user;
        reader->processPacket(hdr, data);
    }
    else
    {
        printError("Bad parameters.");
    }
}

void pcapReader::processPacket(const struct pcap_pkthdr *hdr, const u_char *data)
{
    const char* const METHOD_NAME = "processPacket";
    struct ether_header *eptr = NULL;
    struct ip *ipc = NULL;
    struct udphdr *udpc = NULL;
    u_char *rtpsPayload = NULL;

    if(hdr != NULL && data != NULL)
    {
        eptr = (struct ether_header*)data;

        if(ntohs(eptr->ether_type) == ETHERTYPE_IP) // IP type.
        {
            ipc = (struct ip*)(data + sizeof(struct ether_header));

            if(ipc->ip_p == 17) // UDP type.
            {
                udpc = (struct udphdr*)(((u_char*)ipc) + IP_HEADER_LEN(ipc));
                rtpsPayload = (u_char*)((u_char*)udpc) + sizeof(struct udphdr);

                if(rtpsPayload[0] == 'R' &&
                        rtpsPayload[1] == 'T' &&
                        rtpsPayload[2] == 'P' &&
                        rtpsPayload[3] == 'S')
                {
                    m_npackets++;

                    if(m_callback != NULL)
                        m_callback(NULL, rtpsPayload);
                }
            }
        }
    }
    else
    {
        printError("Bad parameters.");
    }
}

