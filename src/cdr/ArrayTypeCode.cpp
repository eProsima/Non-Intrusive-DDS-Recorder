#include "cdr/ArrayTypeCode.h"
#include "util/IDLPrinter.h"
#include "Cdr.h"

using namespace eProsima;

ArrayTypeCode::ArrayTypeCode() : ContentTypeCode(TypeCode::KIND_ARRAY)
{
}

uint32_t ArrayTypeCode::getDimensionCount() const
{
    return m_dimensionCount;
}

bool ArrayTypeCode::deserialize(CDR &cdr)
{
    bool returnedValue = true;
    uint32_t dimension = 0;
    uint16_t size = 0;

    // Deserialize size.
    returnedValue &= cdr >> size;
    returnedValue &= cdr >> m_dimensionCount;

    for(uint32_t count = 0; count < m_dimensionCount; ++count)
    {
        returnedValue &= cdr >> dimension;
        m_dimensions.push_back(dimension);
    }

    returnedValue &= deserializeContent(cdr);

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
            printer << "[" << m_dimensions[count] << "]";
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