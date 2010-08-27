#include "reader/ipDefragmenter.h"
#include "eProsima_cpp/eProsimaLog.h"

#include <malloc.h>
#include <string.h>

static const char* const CLASS_NAME = "ipDefragmenter";

using namespace eProsima;
using namespace std;

ipFragment::ipFragment(unsigned short id, unsigned int offset,
        const char *buffer, unsigned short bufferLength) : m_id(id),
    m_lastOffset(offset), m_buffer(NULL)
{
    const char* const METHOD_NAME = "ipFragment";
    m_buffer = (char*)calloc(offset + bufferLength, sizeof(char));

    if(m_buffer != NULL)
    {
        if(buffer != NULL)
            memcpy(&m_buffer[offset], buffer, bufferLength);
    }
    else
    {
        printError("Cannot allocate buffer");
    }
}

ipFragment::~ipFragment()
{
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

    if(offset > m_lastOffset)
    {
        m_buffer = (char*)realloc(m_buffer, (offset + bufferLength)*sizeof(char));
        m_lastOffset = offset;
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
    char *returnedValue = m_buffer;
    m_buffer = NULL;
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

        if(last)
        {
            m_packets.erase(it);
            returnedValue = packet->returnBuffer();
            delete packet;
        }
    }

    return returnedValue;
}
