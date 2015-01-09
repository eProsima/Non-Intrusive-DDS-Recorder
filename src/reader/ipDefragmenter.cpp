#include "reader/ipDefragmenter.h"
#include "log/eProsimaLog.h"

#include <malloc.h>
#include <string.h>

static const char* const CLASS_NAME = "ipDefragmenter";

using namespace eprosima;
using namespace std;

ipHold::ipHold(unsigned int offset, unsigned int length, bool filled, bool last) : m_offset(offset), m_length(length),
    m_filled(filled), m_last(last)
{
}

bool ipHold::compare(const ipHold *hold1, const ipHold *hold2)
{
    if(hold1->m_offset < hold2->m_offset)
        return true;

    return false;
}

unsigned int ipHold::getOffset()
{
    return m_offset;
}

unsigned int ipHold::getLength()
{
    return m_length;
}

bool ipHold::getIsFilled()
{
	return m_filled;
}

void ipHold::setIsFilled(bool filled)
{
	m_filled = filled;
}

bool ipHold::getIsLast()
{
	return m_last;
}

void ipHold::setIsLast(bool last)
{
    m_last = last;
}

ipFragment::ipFragment(unsigned short id, unsigned int offset,
        const char *buffer, unsigned short bufferLength, bool last) : m_id(id),
    m_buffer(NULL)
{
    const char* const METHOD_NAME = "ipFragment";
    m_buffer = (char*)calloc(offset + bufferLength, sizeof(char));

    if(m_buffer != NULL)
    {
        if(buffer != NULL)
        {
            // If not first fragment, create empty hold.
            if(offset > 0)
            {
                ipHold *prev_hold = new ipHold(0, offset, false, false);
                m_holds.push_back(prev_hold);
            }

            memcpy(&m_buffer[offset], buffer, bufferLength);
            ipHold *hold = new ipHold(offset, bufferLength, true, last);
            m_holds.push_back(hold);
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
        unsigned short bufferLength, bool last)
{
    const char* const METHOD_NAME = "addFragment";
    list<ipHold*>::iterator it;

    // Sort holds list.
    m_holds.sort(ipHold::compare);

    // Find place from new fragment in holds list.
    it = m_holds.begin();

    for(; it != m_holds.end(); ++it)
    {
        if(((*it)->getOffset() <= offset) &&
                (offset < (*it)->getOffset() + (*it)->getLength()))
            break;
    }

    if(it != m_holds.end())
    {
            ipHold *hold = (*it);

            if(hold->getOffset() == offset)
            {
                if(hold->getLength() != bufferLength)
                {
                    m_holds.erase(it);

                    ipHold *new_hold = new ipHold(offset, bufferLength, true, last);
                    m_holds.push_back(new_hold);
                    ipHold *post_hold = new ipHold(offset + bufferLength, hold->getLength() - bufferLength, false, false);
                    m_holds.push_back(post_hold);
                   
                    free(hold);
                }
                else
                {
                    hold->setIsFilled(true);
                    hold->setIsLast(last);
                }
            }
            else
            {
                m_holds.erase(it);

                ipHold *prev_hold = new ipHold(hold->getOffset(), offset - hold->getOffset(), false, false);
                m_holds.push_back(prev_hold);
                ipHold *new_hold = new ipHold(offset, bufferLength, true, last);
                m_holds.push_back(new_hold);

                if(offset + bufferLength != hold->getOffset() + hold->getLength())
                {
                    ipHold *post_hold = new ipHold(offset + bufferLength, (hold->getOffset() + hold->getLength()) - (offset + bufferLength), false, false);
                    m_holds.push_back(post_hold);
                }

                free(hold);
            }
    }
    else
    {
        
        // Check if between last fragment and new there is a empty hold.
        // In true case, then create empty hold in holds list.
        --it;
        if(offset > (*it)->getOffset() + (*it)->getLength())
        {
            ipHold *prev_hold = new ipHold((*it)->getOffset() + (*it)->getLength(), offset - ((*it)->getOffset() + (*it)->getLength()), false, false);
            m_holds.push_back(prev_hold);
        }
        
        // Reallocate buffer for future copy of new fragment.
        m_buffer = (char*)realloc(m_buffer, (offset + bufferLength)*sizeof(char));

        // Create new filled hold to new fragment
        ipHold *hold = new ipHold(offset, bufferLength, true, last);
        m_holds.push_back(hold);
    }

    // Copy new fragment.
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
    list<ipHold*>::iterator it = m_holds.begin();
    bool allFilled = true, last = false;

    for(; it != m_holds.end(); ++it)
    {
        allFilled &= (*it)->getIsFilled();
        if((*it)->getIsLast())
            last = true;
    }

    if(allFilled && last)
    {
        returnedValue = m_buffer;
        m_buffer = NULL;
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
        packet = new ipFragment(id, offset, buffer, bufferLength, last);

        if(packet != NULL)
            m_packets.push_back(packet);
    }
    else
    {
        packet = (*it);
        packet->addFragment(offset, buffer, bufferLength, last);

         // Check if the IP packet is complete;
        returnedValue = packet->returnBuffer();

        if(returnedValue != NULL)
        {
            m_packets.erase(it);           
            delete packet;
        }
    }




    return returnedValue;
}
