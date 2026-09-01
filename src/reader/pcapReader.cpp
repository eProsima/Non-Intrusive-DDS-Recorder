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
#include <stdint.h>

#ifdef _WIN32
#include <winsock.h>

/* Ethernet header */
struct ether_header
{
    uint8_t ether_dhost[6];
    uint8_t ether_shost[6];
    uint16_t ether_type;
};

/* IPv4 header */
struct ip
{
    u_char ver_ihl;         // Version (4 bits) + Internet header length (4 bits)
    u_char tos;             // Type of service
    u_short ip_len;         // Total length
    u_short ip_id; // Identification
    u_short ip_off;     // Flags (3 bits) + Fragment offset (13 bits)
#define IP_RF 0x8000            /* reserved fragment flag */
#define IP_DF 0x4000            /* dont fragment flag */
#define IP_MF 0x2000            /* more fragments flag */
#define IP_OFFMASK 0x1fff       /* mask for fragmenting bits */
    u_char ttl;             // Time to live
    u_char ip_p;            // Protocol
    u_short crc;            // Header checksum
    in_addr ip_src;     // Source address
    in_addr ip_dst;     // Destination address
    u_int op_pad;           // Option + Padding
};

/* UDP header*/
struct udphdr
{
    u_short sport;          // Source port
    u_short dport;          // Destination port
    u_short len;            // Datagram length
    u_short crc;            // Checksum
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

#endif // ifdef _WIN32

/*
 * Link layer identifiers that may be missing in older pcap headers.
 * Their numeric values are fixed by the pcap file format.
 */
#ifndef DLT_LINUX_SLL
#define DLT_LINUX_SLL 113
#endif
#ifndef DLT_LINUX_SLL2
#define DLT_LINUX_SLL2 276
#endif

/* Length of the link layer headers that precede the IPv4 datagram. */
#define NULL_HEADER_LEN 4
#define SLL_HEADER_LEN 16
#define SLL2_HEADER_LEN 20

/* Offset of the field holding the encapsulated protocol, an EtherType value. */
#define SLL_PROTOCOL_OFFSET 14
#define SLL2_PROTOCOL_OFFSET 0

/*
 * Address family of IPv4 as stored in a DLT_NULL or DLT_LOOP header. This is the
 * AF_INET value of the host that took the capture, which is 2 on every platform
 * that writes these link layers, and not necessarily the AF_INET of this host.
 */
#define LINK_AF_INET 2

/* Minimum length of an IPv4 header, without options. */
#define IP_MIN_HEADER_LEN 20

using namespace std;
using namespace eprosima;

static const char* const CLASS_NAME = "pcapReader";

pcapReader::pcapReader(
        string& filename,
        eProsimaLog& log)
    : m_filename(filename)
    , m_log(log)
    , m_pcap(NULL)
    , m_linkType(-1)
    , m_npackets(0)
    , m_nrtpspackets(0)
    , m_callback(NULL)
    , m_ipDefragmenter(NULL)
{
    const char* const METHOD_NAME = "pcapReader";

    m_pcap = pcap_open_offline(m_filename.c_str(), m_pcapErrorBuf);

    if (m_pcap != NULL)
    {
        m_linkType = pcap_datalink(m_pcap);
        checkLinkType();
        m_ipDefragmenter = new ipDefragmenter(log);
    }
    else
    {
        logError(m_log, "Cannot open file %s in read mode: %s", m_filename.c_str(), m_pcapErrorBuf);
    }
}

bool pcapReader::checkLinkType()
{
    const char* const METHOD_NAME = "checkLinkType";
    bool returnedValue = false;

    switch (m_linkType)
    {
        case DLT_EN10MB:
        case DLT_NULL:
        case DLT_LOOP:
        case DLT_LINUX_SLL:
        case DLT_LINUX_SLL2:
        case DLT_RAW:
            returnedValue = true;
            break;

        default:
        {
            const char* name = pcap_datalink_val_to_name(m_linkType);
            logError(m_log,
                    "Unsupported link layer %s (%d) in file %s. Supported link layers are "
                    "EN10MB (Ethernet), NULL and LOOP (loopback), LINUX_SLL and LINUX_SLL2 "
                    "(Linux cooked capture, used by the 'any' interface) and RAW (raw IP)",
                    (name != NULL) ? name : "UNKNOWN", m_linkType, m_filename.c_str());
            break;
        }
    }

    return returnedValue;
}

const u_char* pcapReader::getIpHeader(
        const u_char* data,
        unsigned int caplen)
{
    unsigned int headerLen = 0;

    switch (m_linkType)
    {
        case DLT_EN10MB:
        {
            if (caplen < sizeof(struct ether_header))
            {
                return NULL;
            }

            if (ntohs(((const struct ether_header*)data)->ether_type) != ETHERTYPE_IP)
            {
                return NULL;
            }

            headerLen = sizeof(struct ether_header);
            break;
        }

        case DLT_NULL:
        case DLT_LOOP:
        {
            uint32_t family = 0;

            if (caplen < NULL_HEADER_LEN)
            {
                return NULL;
            }

            memcpy(&family, data, sizeof(family));

            /*
             * DLT_LOOP always stores the address family in network byte order, while
             * DLT_NULL stores it in the byte order of the capturing host. In the latter
             * case a value that does not fit in a single byte was written by a host of
             * the opposite byte order, so it has to be swapped.
             */
            if (m_linkType == DLT_LOOP || family > 0xFF)
            {
                family = ntohl(family);
            }

            if (family != LINK_AF_INET)
            {
                return NULL;
            }

            headerLen = NULL_HEADER_LEN;
            break;
        }

        case DLT_LINUX_SLL:
        case DLT_LINUX_SLL2:
        {
            uint16_t protocol = 0;
            unsigned int protocolOffset = SLL_PROTOCOL_OFFSET;

            headerLen = SLL_HEADER_LEN;

            if (m_linkType == DLT_LINUX_SLL2)
            {
                headerLen = SLL2_HEADER_LEN;
                protocolOffset = SLL2_PROTOCOL_OFFSET;
            }

            if (caplen < headerLen)
            {
                return NULL;
            }

            memcpy(&protocol, data + protocolOffset, sizeof(protocol));

            if (ntohs(protocol) != ETHERTYPE_IP)
            {
                return NULL;
            }

            break;
        }

        case DLT_RAW:
        {
            /* The packet is the IPv4 datagram itself, there is no link layer header. */
            headerLen = 0;
            break;
        }

        default:
            /* The link layer was already reported when the file was opened. */
            return NULL;
    }

    if (caplen < headerLen + IP_MIN_HEADER_LEN)
    {
        return NULL;
    }

    /*
     * DLT_RAW carries no protocol field, and the address family of a loopback header
     * may not match the datagram, so the IP version is checked in every case.
     */
    if ((data[headerLen] >> 4) != 4)
    {
        return NULL;
    }

    return data + headerLen;
}

pcapReader::~pcapReader()
{
    if (m_pcap != NULL)
    {
        pcap_close(m_pcap);
    }

    if (m_ipDefragmenter != NULL)
    {
        delete m_ipDefragmenter;
    }
}

bool pcapReader::isOpen()
{
    return (m_pcap != NULL);
}

unsigned int pcapReader::processRTPSPackets(
        void* user,
        processRTPSPacketCallback callback)
{
    const char* const METHOD_NAME = "processRTPSPackets";
    unsigned int returnedValue = 0;

    if (callback != NULL)
    {
        if (m_pcap != NULL)
        {
            m_callback = callback;
            m_user = user;

            if (pcap_dispatch(m_pcap, 0, pcapReader::processPacketCallback, (u_char*)this) >= 0)
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

void pcapReader::processPacketCallback(
        u_char* user,
        const struct pcap_pkthdr* hdr,
        const u_char* data)
{
    const char* const METHOD_NAME = "processPacketCallback";
    pcapReader* reader = NULL;

    if (user != NULL && hdr != NULL && data != NULL)
    {
        reader = (pcapReader*)user;
        reader->processPacket(hdr, data);
    }
    else
    {
        printError("Bad parameters.");
    }
}

void pcapReader::processPacket(
        const struct pcap_pkthdr* hdr,
        const u_char* data)
{
    const char* const METHOD_NAME = "processPacket";
    struct ip* ipc = NULL;
    struct udphdr* udpc = NULL;
    u_char* rtpsPayload = NULL;
    string ip_src, ip_dst;
    bool fragmented = false;

    if (hdr != NULL && data != NULL)
    {
        ++m_npackets;

        if (hdr->caplen == hdr->len)
        {
            /*
             * Locate the IPv4 header according to the link layer of the capture file.
             * Packets that do not carry IPv4 are silently skipped.
             */
            ipc = (struct ip*)getIpHeader(data, hdr->caplen);

            if (ipc == NULL)
            {
                return;
            }

            if (ipc->ip_p == 17)     // UDP type.
            {
                if ((ntohs(ipc->ip_off) & IP_MF) ||
                        ((ntohs(ipc->ip_off) & IP_OFFMASK) > 0))
                {
                    fragmented = true;
                    udpc =
                            (struct udphdr*)m_ipDefragmenter->addIpPacket(ntohs(ipc->ip_id),
                                    (unsigned int)(ntohs(ipc->ip_off) & IP_OFFMASK) * 8,
                                    ((char*)ipc) + IP_HEADER_LEN(ipc), ntohs(ipc->ip_len) - IP_HEADER_LEN(ipc),
                                    (ntohs(ipc->ip_off) & IP_MF) ? false : true);
                }
                else
                {
                    udpc = (struct udphdr*)(((u_char*)ipc) + IP_HEADER_LEN(ipc));
                }

                if (udpc != NULL)
                {
                    rtpsPayload = (u_char*)((u_char*)udpc) + sizeof(struct udphdr);

                    if (rtpsPayload[0] == 'R' &&
                            rtpsPayload[1] == 'T' &&
                            rtpsPayload[2] == 'P' &&
                            rtpsPayload[3] == 'S')
                    {
                        // Get IPs in strings.
                        ip_src = inet_ntoa(ipc->ip_src);
                        ip_dst = inet_ntoa(ipc->ip_dst);

                        ++m_nrtpspackets;

                        if (m_callback != NULL)
                        {
                            m_callback(m_user, m_npackets, hdr->ts, ip_src, ip_dst,
                                    (char*)rtpsPayload, ntohs(udpc->len) - sizeof(struct udphdr));
                        }
                    }

                    if (fragmented)
                    {
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
