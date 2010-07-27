#ifndef _PCAPREADER_H_
#define _PCAPREADER_H_

#include "pcap.h"

#ifdef __cplusplus

#include <string>

namespace eProsima
{
    class eProsimaLog;

    typedef void (*processRTPSPacketCallback)(void *user, u_char *rtpsPayload);

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
             * \return the number of RTPS packets that was processed.
             */
            unsigned int processRTPSPackets(processRTPSPacketCallback callback);

        private:

            /**
             * \brief This callback is called by pcap library in each net packet that it processed.
             */
            static void processPacketCallback(u_char *user, const struct pcap_pkthdr *hdr, const u_char *data);

            void processPacket(const struct pcap_pkthdr *hdr, const u_char *data);

            /// Name of the file that was opened.
            std::string m_filename;

            /// Log object used to log errors.
            eProsimaLog &m_log;

            /// Pointer to the Pcap structure that contains information of capture file.
            pcap_t *m_pcap;

            /// Count the number of RTPS packet that were processed.
            unsigned int m_npackets;

            /// Stores the callback that it must be called.
            processRTPSPacketCallback m_callback;

            /// Pcap error buffer.
            char m_pcapErrorBuf[PCAP_ERRBUF_SIZE];
    };

}

#endif // __cplusplus

#endif // _PCAPREADER_H_
