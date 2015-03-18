/******************************************************************************************
 * Copyright (c) 2015 eProsima. All rights reserved.
 *
 * This copy of eProsima Non-Intrusive DDS Recorder is licensed to you
 * under the terms described in the DDSRECORDER_LICENSE file included in this distribution.
 *
 *****************************************************************************************/
#include "cdr/ArrayTypeCode.h"
#include "util/IDLPrinter.h"
#include "fastcdr/Cdr.h"
#include "fastcdr/exceptions/Exception.h"

using namespace eprosima::fastcdr;
using namespace eprosima;

ArrayTypeCode::ArrayTypeCode() : ContentTypeCode(TypeCode::KIND_ARRAY), m_dimensionCount(0)
{
}

ArrayTypeCode::ArrayTypeCode(std::vector<int32_t>& dim) : ContentTypeCode(TypeCode::KIND_ARRAY)
{
	for(std::vector<int32_t>::iterator it = dim.begin();it!=dim.end();++it)
	{
		m_dimensions.push_back((uint32_t)(*it));
		m_dimensionCount++;
	}
}


uint32_t ArrayTypeCode::getDimensionCount() const
{
    return m_dimensionCount;
}

bool ArrayTypeCode::deserialize(Cdr &cdr)
{
    bool returnedValue = true;
    uint32_t dimension = 0;
    uint16_t size = 0;

    try
    {
        // Deserialize size.
        cdr >> size;
        cdr >> m_dimensionCount;

        for(uint32_t count = 0; count < m_dimensionCount; ++count)
        {
            cdr >> dimension;
            m_dimensions.push_back(dimension);
        }

        returnedValue &= deserializeContent(cdr);
    }
    catch(exception::Exception &ex)
    {
        returnedValue = false;
    }

    return returnedValue;
}

bool ArrayTypeCode::print(IDLPrinter &printer, bool write) const
{
    bool returnedValue = true;

	if(write)
    {
		printer << getContentTypeCode();
        
        for(uint32_t count = 0; count < m_dimensionCount; ++count)
        {
            printer.getOut() << "[" << m_dimensions[count] << "]";
        }
    }
    else
    {
        returnedValue &= getContentTypeCode()->print(printer, false);
    }

    return returnedValue;
}

uint32_t ArrayTypeCode::getDimension(uint32_t dim) const
{
    return m_dimensions[dim];
}
