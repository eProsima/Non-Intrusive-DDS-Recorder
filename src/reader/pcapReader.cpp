/******************************************************************************************
 * Copyright (c) 2015 eProsima. All rights reserved.
 *
 * This copy of eProsima Non-Intrusive DDS Recorder is licensed to you
 * under the terms described in the DDSRECORDER_LICENSE file included in this distribution.
 *
 *****************************************************************************************/
#include "reader/pcapReader.h"
#include "reader/ipDefragmenter.h"
#include "log/eProsimaLog.h"

#include <string.h>
#include <malloc.h>

#ifdef _WIN32
#include <winsock.h>

/* Ethernet header */
struct ether_header
{
    u_int8_t ether_dhost[6];
    u_int8_t ether_shost[6];
    u_int16_t ether_type;
};

/* IPv4 header */
struct ip
{
	u_char	ver_ihl;		// Version (4 bits) + Internet header length (4 bits)
	u_char	tos;			// Type of service 
	u_short ip_len;			// Total length 
	u_short ip_id; // Identification
	u_short ip_off;		// Flags (3 bits) + Fragment offset (13 bits)
#define	IP_RF 0x8000			/* reserved fragment flag */
#define	IP_DF 0x4000			/* dont fragment flag */
#define	IP_MF 0x2000			/* more fragments flag */
#define	IP_OFFMASK 0x1fff		/* mask for fragmenting bits */
	u_char	ttl;			// Time to live
	u_char	ip_p;			// Protocol
	u_short crc;			// Header checksum
	in_addr	ip_src;		// Source address
	in_addr	ip_dst;		// Destination address
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
#include <arpa/inet.h>

#define IP_HEADER_LEN(ip) ip->ip_hl * 4

#endif

using namespace std;
using namespace eprosima;

static const char* const CLASS_NAME = "pcapReader";

pcapReader::pcapReader(string &filename, eProsimaLog &log) : m_filename(filename), m_log(log), m_pcap(NULL),
    m_npackets(0), m_nrtpspackets(0), m_callback(NULL), m_ipDefragmenter(NULL)
{
    const char* const METHOD_NAME = "pcapReader";

    m_pcap = pcap_open_offline(m_filename.c_str(), m_pcapErrorBuf);

    if(m_pcap != NULL)
    {
        m_ipDefragmenter = new ipDefragmenter(log);
    }
    else
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

    if(m_ipDefragmenter != NULL)
        delete m_ipDefragmenter;
}

bool pcapReader::isOpen()
{
    return (m_pcap != NULL);
}

unsigned int pcapReader::processRTPSPackets(void *user, processRTPSPacketCallback callback)
{
    const char* const METHOD_NAME = "processRTPSPackets";
    unsigned int returnedValue = 0;

    if(callback != NULL)
    {
        if(m_pcap != NULL)
        {
            m_callback = callback;
            m_user = user;

            if(pcap_dispatch(m_pcap, 0, pcapReader::processPacketCallback, (u_char*)this) >= 0)
            {
                returnedValue = m_nrtpspackets;
                m_nrtpspackets = 0;
                m_callback = NULL;
                m_user = NULL;
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
    string ip_src, ip_dst;
    bool fragmented = false;

    if(hdr != NULL && data != NULL)
    {
        ++m_npackets;

        if(hdr->caplen == hdr->len)
        {
            eptr = (struct ether_header*)data;

            if(ntohs(eptr->ether_type) == ETHERTYPE_IP) // IP type.
            {
                ipc = (struct ip*)(data + sizeof(struct ether_header));
 
                if(ipc->ip_p == 17) // UDP type.
                {
                    if((ntohs(ipc->ip_off) & IP_MF) ||
                            ((ntohs(ipc->ip_off) & IP_OFFMASK) > 0))
                    {
                        fragmented = true;
                        udpc = (struct udphdr*)m_ipDefragmenter->addIpPacket(ntohs(ipc->ip_id), (unsigned int)(ntohs(ipc->ip_off) & IP_OFFMASK) * 8,
                                ((char*)ipc) + IP_HEADER_LEN(ipc), ntohs(ipc->ip_len) - IP_HEADER_LEN(ipc),
                                (ntohs(ipc->ip_off) & IP_MF) ? false : true);
                    }
                    else
                    {
                        udpc = (struct udphdr*)(((u_char*)ipc) + IP_HEADER_LEN(ipc));
                    }

                    if(udpc != NULL) 
                    {
                        rtpsPayload = (u_char*)((u_char*)udpc) + sizeof(struct udphdr);

                        if(rtpsPayload[0] == 'R' &&
                                rtpsPayload[1] == 'T' &&
                                rtpsPayload[2] == 'P' &&
                                rtpsPayload[3] == 'S')
                        {
                            // Get IPs in strings.
                            ip_src = inet_ntoa(ipc->ip_src);
                            ip_dst = inet_ntoa(ipc->ip_dst);

                            ++m_nrtpspackets;

                            if(m_callback != NULL)
                                m_callback(m_user, m_npackets, hdr->ts, ip_src, ip_dst,
                                        (char*)rtpsPayload, ntohs(udpc->len) - sizeof(struct udphdr));
                        }

                        if(fragmented)
                            free(udpc);
                    }
                }
            }
        }
        else
        {
            logError(m_log, "Packet with different capture length than off wire length\n");
        }
    }
    else
    {
        logError(m_log, "Bad parameters.");
    }
}

