#include "reader/ipDefragmenter.h"
#include "eProsima_cpp/eProsimaLog.h"

#include <malloc.h>
#include <string.h>

static const char* const CLASS_NAME = "ipDefragmenter";

using namespace eProsima;
using namespace std;

ipHold::ipHold(unsigned int offset, unsigned int length) : m_offset(offset), m_length(length)
{
}

unsigned int ipHold::getOffset()
{
    return m_offset;
}

unsigned int ipHold::getLength()
{
    return m_length;
}

ipFragment::ipFragment(unsigned short id, unsigned int offset,
        const char *buffer, unsigned short bufferLength) : m_id(id),
    m_nextOffset(0), m_buffer(NULL)
{
    const char* const METHOD_NAME = "ipFragment";
    m_buffer = (char*)calloc(offset + bufferLength, sizeof(char));

    if(m_buffer != NULL)
    {
        if(buffer != NULL)
        {
            memcpy(&m_buffer[offset], buffer, bufferLength);

            if(offset > m_nextOffset)
            {
                ipHold *hold = new ipHold(m_nextOffset, offset - m_nextOffset);
                m_holds.push_back(hold);
            }

            m_nextOffset = offset += bufferLength;
        }
    }
    else
    {
        printError("Cannot allocate buffer");
    }
}

ipFragment::~ipFragment()
{
    ipHold *hold = NULL;
    list<ipHold*>::iterator it = m_holds.begin();

    while(it != m_holds.end())
    {
        hold = (*it);
        it = m_holds.erase(it);
        free(hold);
    }
    if(m_buffer != NULL)
        free(m_buffer);
}

unsigned short ipFragment::getId()
{
    return m_id;
}

void ipFragment::addFragment(unsigned int offset, const char *buffer,
        unsigned short bufferLength)
{
    const char* const METHOD_NAME = "addFragment";

    if(offset >= m_nextOffset)
    {
        if(offset != m_nextOffset)
        {
            ipHold *hold = new ipHold(m_nextOffset, offset - m_nextOffset);
            m_holds.push_back(hold);
        }

        m_buffer = (char*)realloc(m_buffer, (offset + bufferLength)*sizeof(char));
        m_nextOffset = offset + bufferLength;
    }
    else
    {
        list<ipHold*>::iterator it = m_holds.begin();

        for(; it != m_holds.end(); it++)
        {
            if(((*it)->getOffset() <= offset) &&
                    (offset < (*it)->getOffset() + (*it)->getLength()))
                break;
        }

        if(it != m_holds.end())
        {
            ipHold *hold = (*it);
            m_holds.erase(it);

            if(hold->getOffset() == offset)
            {
                if(hold->getLength() != bufferLength)
                {
                    ipHold *newhold = new ipHold(offset + bufferLength, hold->getLength() - bufferLength);
                    m_holds.push_back(newhold);
                }
            }
            else
            {
                ipHold *newhold = new ipHold(hold->getOffset(), offset - hold->getOffset());
                m_holds.push_back(newhold);

                if(offset + bufferLength != hold->getOffset() + hold->getLength())
                {
                    newhold = new ipHold(offset + bufferLength, (hold->getOffset() + hold->getLength()) - (offset + bufferLength));
                    m_holds.push_back(newhold);
                }
            }

            free(hold);
        }
    }

    if(m_buffer != NULL)
    {
        memcpy(&m_buffer[offset], buffer, bufferLength);
    }
    else
    {
        printError("m_buffer is NULL");
    }
}

char* ipFragment::returnBuffer()
{
    char *returnedValue = NULL;

    if(m_holds.empty())
    {
        returnedValue = m_buffer;
        m_buffer = NULL;
    }
    else
    {
        printf("INFO<ipFragment::returnBuffer>: Descartado paquete IP 0x%hX porque tiene huecos\n", m_id);
    }

    return returnedValue;
}

ipDefragmenter::ipDefragmenter(eProsimaLog &log) : m_log(log)
{
}

ipDefragmenter::~ipDefragmenter()
{
    list<ipFragment*>::iterator it;

    for(it = m_packets.begin(); it != m_packets.end(); it++)
        delete (*it);
}

char* ipDefragmenter::addIpPacket(unsigned short id, unsigned int offset,
        const char *buffer, unsigned short bufferLength, bool last)
{
    char *returnedValue = NULL;
    list<ipFragment*>::iterator it;
    ipFragment *packet = NULL;

    // Search in list if the packet exists.
    for(it = m_packets.begin(); it != m_packets.end(); it++)
    {
        if((*it)->getId() == id)
            break;
    }

    if(it == m_packets.end())
    {
        packet = new ipFragment(id, offset, buffer, bufferLength);

        if(packet != NULL)
            m_packets.push_back(packet);
    }
    else
    {
        packet = (*it);
        packet->addFragment(offset, buffer, bufferLength);

        // TODO Se pueden perder datos si llega uno más tarde que el último fragmento.
        if(last)
        {
            m_packets.erase(it);
            returnedValue = packet->returnBuffer();
            delete packet;
        }
    }

    return returnedValue;
}
