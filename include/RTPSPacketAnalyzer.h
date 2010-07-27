#ifndef _RTPSPACKETANALYZER_H_
#define _RTPSPACKETANALYZER_H_

#ifdef __cplusplus

namespace eProsima
{

    class RTPSPacketAnalyzer
    {
        public:

            /**
             * \brief This function is called each time that a reader finds a RTPS packet.
             *
             * \param user User pointer. In this case is a RTPSPacketAnalyzer object pointer.
             * \param rtpsPayload The RTPS packet. Cannot be NULL.
             */
            static void processRTPSPacketCallback(void *user, const char *rtpsPayload);

        private:

            /**
             * \brief This function process a RTPS packet.
             *
             * \param rtpsPayload The RTPS packet that will be processed. Cannot be NULL.
             */
            void processRTPSPacket(const char *rtpsPayload);
    };
}

#endif // __cplusplus

#endif // _RTPSPACKETANALYZER_H_
