#include "cdr/SequenceTypeCode.h"
#include "util/IDLPrinter.h"
#include "cpp/Cdr.h"
#include "cpp/exceptions/Exception.h"

using namespace eProsima;

SequenceTypeCode::SequenceTypeCode() : ContentTypeCode(TypeCode::KIND_SEQUENCE)
{
}

uint32_t SequenceTypeCode::getMaxLength() const
{
    return m_maxLength;
}

bool SequenceTypeCode::deserialize(Cdr &cdr)
{
    bool returnedValue = true;
    uint16_t size = 0;

    try
    {
        // Deserialize size.
        cdr >> size;
        cdr >> m_maxLength;

        returnedValue &= deserializeContent(cdr);
    }
    catch(eProsima::Exception &ex)
    {
        returnedValue = false;
    }

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
