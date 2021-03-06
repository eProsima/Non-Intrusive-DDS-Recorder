/******************************************************************************************
 * Copyright (c) 2015 eProsima. All rights reserved.
 *
 * This copy of eProsima Non-Intrusive DDS Recorder is licensed to you
 * under the terms described in the DDSRECORDER_LICENSE file included in this distribution.
 *
 *****************************************************************************************/
#ifndef _RTPSPACKETANALYZER_H_
#define _RTPSPACKETANALYZER_H_

#ifdef __cplusplus

#include <string>
#include <stdint.h>

#ifdef _WIN32
#include <winsock.h>
#else
#include <netinet/in.h>
#include <sys/time.h>
#endif

namespace eprosima
{
    class eProsimaLog;

    typedef void (*getDataCallback)(void *user, const unsigned int npacket, const struct timeval &wts,
            std::string &ip_src, std::string &ip_dst, unsigned int hostId,
            unsigned int appId, unsigned int instanceId, unsigned int readerId, unsigned int writerId,
            unsigned long long writerSequenceNum, struct DDS_Time_t &sourceTmp,
            unsigned int destHostId, unsigned int destAppId, unsigned int destInstanceId, bool endianess,
            const char *serializedData, unsigned int serializedDataLen);

    typedef struct DDS_Time_t
    {
        int32_t seconds;
        uint32_t nanoseconds;
    } DDS_Time_t;

    class RTPSPacketAnalyzer
    {
        public:

            RTPSPacketAnalyzer(eProsimaLog &log);

            /**
             * \brief This function is called each time that a reader finds a RTPS packet.
             *
             * \param user User pointer. In this case is a RTPSPacketAnalyzer object pointer.
             * \param rtpsPayload The RTPS packet. Cannot be NULL.
             * \param rtpsPayloadLen The length of the RTPS packet.
             */
            static void processRTPSPacketCallback(void *user, const unsigned int npacket, const struct timeval &wts,
                    std::string &ip_src, std::string &ip_dst, 
                    const char *rtpsPayload, const unsigned short rtpsPayloadLen);

            /**
             * \brief This function process a RTPS packet.
             *
             * \param rtpsPayload The RTPS packet that will be processed. Cannot be NULL.
             * \param rtpsPayloadLen The length of th RTPS packet.
             */
            void processRTPSPacket(const unsigned int npacket, const struct timeval &wts, std::string &ip_src,
                    std::string &ip_dst, const char *rtpsPayload, const unsigned short rtpsPayloadLen);

            /**
             * \brief This function sets the getData callback.
             */
            void setGetDataCallback(void *user, getDataCallback callback);

        private:

            /**
             * \brief This function is called when a new RTPS packet will be processed.
             *
             * This function initialized the variables that store information about the processed RTPS packet.
             */
            void initialize();

            /**
             * \brief This function processes a submessange that is inside of a RTPS package.
             *
             * \param submessage The pointer to the submessage inside RTPS packet payload. Cannot be NULL.
             * \return The length of the submessage that was processed.
             */
            unsigned short processRTPSSubmessage(const unsigned int npacket, const struct timeval &wts,
                    std::string ip_src, std::string ip_dst, const char *submessage);

            /**
             * \brief This function processes a DATA submessage.
             *
             * \param dataSubmessage The pointer to the DATA submessage. Cannot be NULL.
             * \param dataSubmessageLen Length of the DATA submessage.
             * \param endianess False value indicates that DATA submessage uses big-endian.
             * True value indicates that DATA submessage uses little-endian.
             * \param dataInside Indicates if the DATA submessage contains serialized data.
			 * \param inlineQos Indicates if the DATA submessage contains inlineQos.
             */
            void processDATASubmessage(const unsigned int npacket, const struct timeval &wts, std::string &ip_src,
                    std::string &ip_dst, const char *dataSubmessage, unsigned short dataSubmessageLen,
                    bool endianess, bool dataInside, bool inlineQos);

            void processINFOTSSubmessage(const char *dataSubmessage, bool endianess);

            void processINFODSTSubmessage(const char *dataSubmessage, bool endianess);

            eProsimaLog &m_log;

            /// Stores the RTPS protocol version
            unsigned char m_protocolVersion[2];

            /// Stores the vendor identifier.
            unsigned char m_vendorId[2];

            unsigned int m_guidPrefix[3];

            unsigned int m_guidDestinationPrefix[3];

            /// Stores callback that is called when DATA submessage was found.
            void *m_getDataUser;
            getDataCallback m_getDataCallback;

            DDS_Time_t m_lastSourceTmp;
    };
}

#endif // __cplusplus

#endif // _RTPSPACKETANALYZER_H_
