/******************************************************************************************
 * Copyright (c) 2015 eProsima. All rights reserved.
 *
 * This copy of eProsima Non-Intrusive DDS Recorder is licensed to you
 * under the terms described in the DDSRECORDER_LICENSE file included in this distribution.
 *
 *****************************************************************************************/
#ifndef _PCAPREADER_H_
#define _PCAPREADER_H_

#include "pcap.h"

#ifdef __cplusplus

#include <string>

namespace eprosima
{
    class eProsimaLog;
    class ipDefragmenter;

    typedef void (*processRTPSPacketCallback)(void *user, const unsigned int npacket, const struct timeval &wts,
            std::string &ip_src, std::string &ip_dst,
            const char *rtpsPayload, const unsigned short rtpsPayloadLen);

    class pcapReader
    {
        public:

            /**
             * \brief Contructor.
             *
             * This constructor open the pcap file that will be readed.
             *
             * \param filename Name of the pcap file.
             * \param log Log object used to log errors.
             */
            pcapReader(std::string &filename, eProsimaLog &log);

            /**
             * \brief Destructor.
             * This function closes the pcap file.
             */
            ~pcapReader();

            /**
             * \brief This function returns if the pcap file was opened successfully.
             *
             * \return True value is returned if the pcap file was opened successfully.
             * In other case false is returned.
             */
            bool isOpen();

            /**
             * \brief This function processes each RTPS packet in the pcap file.
             *
             * \param user User pointer that will be returned in callback.
             * \param callback For each RTPS packet this callback will be called. Cannot be NULL.
             * \return the number of RTPS packets that was processed.
             */
            unsigned int processRTPSPackets(void *user, processRTPSPacketCallback callback);

        private:

            /**
             * \brief This callback is called by pcap library in each net packet that it processed.
             *
             * \param user User pointer that is returned again by pcap library. In this case
             * it is the pcapReader object pointer.
             * \param hdr Header structure returned by pcap library.
             * \param data The datagram (packet) that will be parsed.
             */
            static void processPacketCallback(u_char *user, const struct pcap_pkthdr *hdr, const u_char *data);

            /**
             * \brief This funcion is called by processPacketCallback static function.
             *
             * For each RTPS packet that is found, this function will call the callback
             * that user set.
             *
             * \param hdr Header structure returned by pcap library.
             * \param data The datagram (packet) that will be parsed.
             */
            void processPacket(const struct pcap_pkthdr *hdr, const u_char *data);

            /// Name of the file that was opened.
            std::string m_filename;

            /// Log object used to log errors.
            eProsimaLog &m_log;

            /// Pointer to the Pcap structure that contains information of capture file.
            pcap_t *m_pcap;

            /// Count the number of RTPS packet that were processed.
            unsigned int m_npackets;
            unsigned int m_nrtpspackets;

            /// Stores the callback that it must be called.
            processRTPSPacketCallback m_callback;
            
            /// Stores the user pointer that it will be returned.
            void *m_user;

            /// Pcap error buffer.
            char m_pcapErrorBuf[PCAP_ERRBUF_SIZE];

            ipDefragmenter  *m_ipDefragmenter;
    };

}

#endif // __cplusplus

#endif // _PCAPREADER_H_
