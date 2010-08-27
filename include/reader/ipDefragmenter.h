#ifndef _DEFRAGMENTER_H_
#define _DEFRAGMENTER_H_

#ifdef __cplusplus

#include <list>

namespace eProsima
{
    class eProsimaLog;

    class ipFragment
    {
        public:
            ipFragment(unsigned short id, unsigned int offset,
                    const char *buffer, unsigned short bufferLength);

            ~ipFragment();

            unsigned short getId();

            void addFragment(unsigned int offset, const char *buffer,
                    unsigned short bufferLength);

            char* returnBuffer();

        private:

            unsigned short m_id;
            unsigned int m_lastOffset;
            char *m_buffer;
    };

    class ipDefragmenter
    {
        public:

            ipDefragmenter(eProsimaLog &log);

            ~ipDefragmenter();

            char* addIpPacket(unsigned short id, unsigned int offset,
                    const char *buffer, unsigned short bufferLength, bool last);

        private:

            eProsimaLog &m_log;

            std::list<ipFragment*> m_packets;
    };
}

#endif // __cplusplus
#endif // _DEFRAGMENTER_H_
