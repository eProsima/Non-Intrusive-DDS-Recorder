#include "RTPSPacketAnalyzer.h"
#include "eProsima_cpp/eProsimaLog.h"

#include <stdio.h>

#ifdef RTI_WIN32
#include <winsock.h>
#else
#include <netinet/in.h>
#endif

#define JUMP(buffer, length) buffer = &buffer[length]

#define GET_USHORT_ENDIAN(endian, buffer) \
    endian ? ((unsigned short*)(buffer))[0] : \
ntohs(((unsigned short*)(buffer))[0])
//(((unsigned short)(buffer)[0] << 8) & 0xFF00) + ((unsigned short)(buffer)[1] & 0X00FF);

#define GET_UINT_ENDIAN(endian, buffer) \
    endian ? ((unsigned int*)(buffer))[0] : \
ntohl(((unsigned int*)(buffer))[0])
//(((unsigned int)(buffer)[0] << 24) & 0xFF000000) + (((unsigned int)(buffer)[1] << 16) & 0x00FF0000) + \
//(((unsigned int)(buffer)[2] << 8) & 0x0000FF00) + ((unsigned int)(buffer)[3] & 0x000000FF);

#define GET_ULONGLONG_ENDIAN(endian, buffer) \
    endian ? ((((unsigned long long)(((unsigned int*)(buffer))[0])) << 32) & 0xFFFFFFFF00000000ll) + \
(((unsigned long long)(((unsigned int*)(buffer))[1])) & 0x00000000FFFFFFFFll) : \
((((unsigned long long)ntohl(((unsigned int*)buffer)[0])) << 32) & 0xFFFFFFFF00000000ll) + \
(((unsigned long long)ntohl(((unsigned int*)buffer)[1])) & 0x00000000FFFFFFFFll)

#define GET_ENTITYID(buffer) (((unsigned int)(buffer)[0] << 24) & 0xFF000000) + (((unsigned int)(buffer)[1] << 16) & 0x00FF0000) + \
    (((unsigned int)(buffer)[2] << 8) & 0x0000FF00) + ((unsigned int)(buffer)[3] & 0x000000FF);

#define GET_UINT(buffer) ntohl(((unsigned int*)buffer)[0])

#define RTPS_HEADER_PROTOCOL_SIZE 4
#define RTPS_HEADER_PROTOCOL_VERSION_SIZE 2
#define RTPS_HEADER_VENDORID_SIZE 2
#define RTPS_HEADER_GUIDPREFIX_SIZE 12
#define SUBMESSAGE_HEADER_ID_SIZE 1
#define SUBMESSAGE_HEADER_FLAGS_SIZE 1
#define SUBMESSAGE_HEADER_OCTECTSTONEXTHEADER_SIZE 2
#define SUBMESSAGE_BODY_EXTRAFLAGS_SIZE 2
#define SUBMESSAGE_BODY_OCTETSTOINLINEQOS_SIZE 2
#define SUBMESSAGE_BODY_ENTITIESID_SIZE 8
#define SUBMESSAGE_BODY_SEQUENCENUMBER_SIZE 8
#define SUBMESSAGE_INFOTS_SEC 4
#define SUBMESSAGE_INFOTS_NANOSEC 4

enum RtpsSubmessageId
{
    RTPS_INFOTS_ID = 0x9,
    RTPS_INFODST_ID = 0xe,
    RTPS_DATA_ID = 0x15
};

using namespace eProsima;
using namespace std;

static const char* const CLASS_NAME = "RTPSPacketAnalyzer";

RTPSPacketAnalyzer::RTPSPacketAnalyzer(eProsimaLog &log) : m_log(log), m_getDataUser(NULL),
    m_getDataCallback(NULL)
{
    m_lastSourceTmp.sec = 0;
    m_lastSourceTmp.nanosec = 0;
}

void RTPSPacketAnalyzer::setGetDataCallback(void *user, getDataCallback callback)
{
    m_getDataUser = user;
    m_getDataCallback = callback;
}

void RTPSPacketAnalyzer::processRTPSPacketCallback(void *user, const struct timeval &wts,
        string &ip_src, string &ip_dst, const char *rtpsPayload,
        const unsigned short rtpsPayloadLen)
{
    const char* const METHOD_NAME = "processRTPSPacketCallback";
    RTPSPacketAnalyzer *analyzer = NULL;

    if(user != NULL && rtpsPayload != NULL)
    {
        analyzer = (RTPSPacketAnalyzer*)user;
        analyzer->processRTPSPacket(wts, ip_src, ip_dst, rtpsPayload, rtpsPayloadLen);
    }
    else
    {
        printError("Bad parameters");
    }
}

void RTPSPacketAnalyzer::initialize()
{
    m_protocolVersion[0] = 0;
    m_protocolVersion[1] = 0;
    m_vendorId[0] = 0;
    m_vendorId[1] = 0;
    m_guidPrefix[0] = 0;
    m_guidPrefix[1] = 0;
    m_guidPrefix[2] = 0;
    m_guidDestinationPrefix[0] = 0;
    m_guidDestinationPrefix[1] = 0;
    m_guidDestinationPrefix[2] = 0;
}

void RTPSPacketAnalyzer::processRTPSPacket(const struct timeval &wts, string &ip_src,
        string &ip_dst, const char *rtpsPayload,
        const unsigned short rtpsPayloadLen)
{
    const char* const METHOD_NAME = "processRTPSPacket";
    const char *auxPointer = rtpsPayload;
    unsigned short auxPointerLen = rtpsPayloadLen;
    unsigned short submessageLen = 0;

    if(rtpsPayload != NULL)
    {
        initialize();

        // Jump 'RTPS' bytes.
        JUMP(auxPointer, RTPS_HEADER_PROTOCOL_SIZE);
        auxPointerLen -= RTPS_HEADER_PROTOCOL_SIZE;

        // Save and jump protocol version.
        m_protocolVersion[0] = auxPointer[0];
        m_protocolVersion[1] = auxPointer[1];
        JUMP(auxPointer, RTPS_HEADER_PROTOCOL_VERSION_SIZE);
        auxPointerLen -= RTPS_HEADER_PROTOCOL_VERSION_SIZE;
        
        // Save and jump vendor identifier.
        m_vendorId[0] = auxPointer[0];
        m_vendorId[1] = auxPointer[1];
        JUMP(auxPointer, RTPS_HEADER_VENDORID_SIZE);
        auxPointerLen -= RTPS_HEADER_VENDORID_SIZE;

        // Detect RTPS PING

        if(auxPointerLen >  RTPS_HEADER_GUIDPREFIX_SIZE)
        {
            // Get and jump guid prefix.
            m_guidPrefix[0] = GET_UINT(auxPointer);
            m_guidPrefix[1] = GET_UINT(&((unsigned int*)auxPointer)[1]);
            m_guidPrefix[2] = GET_UINT(&((unsigned int*)auxPointer)[2]);
            JUMP(auxPointer, RTPS_HEADER_GUIDPREFIX_SIZE);
            auxPointerLen -= RTPS_HEADER_GUIDPREFIX_SIZE;

            while(auxPointerLen > 0)
            {
                submessageLen = processRTPSSubmessage(wts, ip_src, ip_dst, auxPointer);
                JUMP(auxPointer, submessageLen);
                auxPointerLen -= submessageLen;
            }
        }

        m_guidDestinationPrefix[0] = 0;
        m_guidDestinationPrefix[1] = 0;
        m_guidDestinationPrefix[2] = 0;
    }
    else
    {
        logError(m_log, "Bad parameter");
    }
}

unsigned short RTPSPacketAnalyzer::processRTPSSubmessage(const struct timeval &wts,
        string ip_src, string ip_dst, const char *submessage)
{
    const char* const METHOD_NAME = "processRTPSSubmessage";
    char submessageId = 0;
    bool endianess = false;
    bool dataInside = false;
    const char *auxPointer = submessage;
    unsigned short submessageSize = 0;

    if(submessage != NULL)
    {
        // Submessage identifier.
        submessageId = auxPointer[0];
        endianess = 0x1 & auxPointer[1];
        dataInside = 0x4 & auxPointer[1];

        // Jump submessage identifier and flags
        JUMP(auxPointer, SUBMESSAGE_HEADER_ID_SIZE + SUBMESSAGE_HEADER_FLAGS_SIZE);

        // Get submessage size and jump size of the submessage.
        submessageSize = GET_USHORT_ENDIAN(endianess, auxPointer);
        JUMP(auxPointer, SUBMESSAGE_HEADER_OCTECTSTONEXTHEADER_SIZE);

        if(submessageId == RTPS_INFOTS_ID)
        {
            processINFOTSSubmessage(auxPointer, endianess);
        }
        else if(submessageId == RTPS_INFODST_ID)
        {
            processINFODSTSubmessage(auxPointer, endianess);
        }
        else if(submessageId == RTPS_DATA_ID && m_getDataCallback != NULL)
        {
            processDATASubmessage(wts, ip_src, ip_dst, auxPointer,
                    submessageSize, endianess, dataInside);
        }

        // Add submessage identifier, flags and submessage size
        submessageSize += SUBMESSAGE_HEADER_ID_SIZE + SUBMESSAGE_HEADER_FLAGS_SIZE +
            SUBMESSAGE_HEADER_OCTECTSTONEXTHEADER_SIZE;
    }
    else
    {
        logError(m_log, "Bad parameter (submessage)");
    }

    return submessageSize;
}

void RTPSPacketAnalyzer::processINFOTSSubmessage(const char *dataSubmessage, bool endianess)
{
    const char* const METHOD_NAME = "processINFOTSSubmessage";
    const char *auxPointer = dataSubmessage;

    if(dataSubmessage != NULL)
    {
        m_lastSourceTmp.sec = GET_UINT_ENDIAN(endianess, auxPointer);
        JUMP(auxPointer, SUBMESSAGE_INFOTS_SEC);
        m_lastSourceTmp.nanosec = GET_UINT_ENDIAN(endianess, auxPointer);
        JUMP(auxPointer, SUBMESSAGE_INFOTS_NANOSEC);
    }
    else
    {
        logError(m_log, "Bad parameters");
    }
}

void RTPSPacketAnalyzer::processINFODSTSubmessage(const char *dataSubmessage, bool endianess)
{
    const char* const METHOD_NAME = "processINFODTSSubmessage";
    const char *auxPointer = dataSubmessage;

    if(dataSubmessage != NULL)
    {
        m_guidDestinationPrefix[0] = GET_UINT(auxPointer);
        m_guidDestinationPrefix[1] = GET_UINT(&((unsigned int*)auxPointer)[1]);
        m_guidDestinationPrefix[2] = GET_UINT(&((unsigned int*)auxPointer)[2]);
        JUMP(auxPointer, RTPS_HEADER_GUIDPREFIX_SIZE);
    }
    else
    {
        logError(m_log, "Bad parameters");
    }
}

void RTPSPacketAnalyzer::processDATASubmessage(const struct timeval &wts,
        string &ip_src, string &ip_dst, const char *dataSubmessage,
        unsigned short dataSubmessageLen, bool endianess, bool dataInside)
{
    const char* const METHOD_NAME = "processDATASubmessage";
    const char *auxPointer = dataSubmessage;
    unsigned short auxPointerLen = dataSubmessageLen;
    unsigned int readerId = 0, writerId = 0;
    unsigned long long sequencenum = 0;
    const char *serializedData = NULL;
    unsigned int serializedDataLen = 0;

    if(dataSubmessage != NULL)
    {
        JUMP(auxPointer, SUBMESSAGE_BODY_EXTRAFLAGS_SIZE + SUBMESSAGE_BODY_OCTETSTOINLINEQOS_SIZE);
        auxPointerLen -= SUBMESSAGE_BODY_EXTRAFLAGS_SIZE + SUBMESSAGE_BODY_OCTETSTOINLINEQOS_SIZE;

        // Get readerId and writerId.
        readerId = GET_ENTITYID(auxPointer);
        writerId = GET_ENTITYID((char*)&((unsigned int*)auxPointer)[1]);
        JUMP(auxPointer, SUBMESSAGE_BODY_ENTITIESID_SIZE);
        auxPointerLen -= SUBMESSAGE_BODY_ENTITIESID_SIZE;

        // Get sequence number.
        sequencenum = GET_ULONGLONG_ENDIAN(endianess, auxPointer);
        JUMP(auxPointer, SUBMESSAGE_BODY_SEQUENCENUMBER_SIZE);
        auxPointerLen -= SUBMESSAGE_BODY_SEQUENCENUMBER_SIZE;
        
        // TODO: Detect inlineQos

        if(dataInside)
        {
            // Get serialized data.
            serializedData = auxPointer;
            serializedDataLen = auxPointerLen;

            if(m_getDataCallback != NULL)
                m_getDataCallback(m_getDataUser, wts, ip_src, ip_dst, m_guidPrefix[0], m_guidPrefix[1],
                        m_guidPrefix[2], readerId, writerId, sequencenum, m_lastSourceTmp, m_guidDestinationPrefix[0],
                        m_guidDestinationPrefix[1], m_guidDestinationPrefix[2], serializedData, serializedDataLen);
        }
    }
    else
    {
        logError(m_log, "Bad parameter (dataSubmessage)");
    }
}
