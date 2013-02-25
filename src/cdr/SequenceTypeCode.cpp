#include "cdr/SequenceTypeCode.h"
#include "util/IDLPrinter.h"
#include "Cdr.h"

using namespace eProsima;

SequenceTypeCode::SequenceTypeCode() : ContentTypeCode(TypeCode::KIND_SEQUENCE)
{
}

uint32_t SequenceTypeCode::getMaxLength() const
{
    return m_maxLength;
}

bool SequenceTypeCode::deserialize(CDR &cdr)
{
    bool returnedValue = true;
    uint16_t size = 0;

    // Deserialize size.
    returnedValue &= cdr >> size;
    returnedValue &= cdr >> m_maxLength;

    returnedValue &= deserializeContent(cdr);

    return returnedValue;
}

bool SequenceTypeCode::print(IDLPrinter &printer, bool write) const
{
    bool returnedValue = true;

	if(write)
    {
        printer.getOut() << "sequence<";
		printer << getContentTypeCode();
        printer.getOut() << ", " << m_maxLength << ">";
        
    }
    else
    {
        returnedValue &= getContentTypeCode()->print(printer, false);
    }

    return returnedValue;
}
