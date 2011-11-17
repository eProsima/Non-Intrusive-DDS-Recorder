#ifndef _DEFRAGMENTER_H_
#define _DEFRAGMENTER_H_

#ifdef __cplusplus

#include <list>

namespace eProsima
{
    class eProsimaLog;

    class ipHold
    {
        public:
            ipHold(unsigned int offset, unsigned int length, bool filled, bool last);

            static bool compare(const ipHold *hold1, const ipHold *hold2);

            unsigned int getOffset();
            unsigned int getLength();
			bool getIsFilled();
			void setIsFilled(bool filled);
			bool getIsLast();
            void setIsLast(bool last);

        private:
            unsigned int m_offset;
            unsigned int m_length;
			bool m_filled;
			bool m_last;
    };

    class ipFragment
    {
        public:
            ipFragment(unsigned short id, unsigned int offset,
                    const char *buffer, unsigned short bufferLength, bool last);

            ~ipFragment();

            unsigned short getId();

            void addFragment(unsigned int offset, const char *buffer,
                    unsigned short bufferLength, bool last);

            char* returnBuffer();

        private:

            unsigned short m_id;
            char *m_buffer;
            std::list<ipHold*> m_holds;
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
