#include "cdr/SequenceTypeCode.h"
#include "util/IDLPrinter.h"
#include "fastcdr/Cdr.h"
#include "fastcdr/exceptions/Exception.h"

#include "cdr/TypeCodeCopy.h"
using namespace eprosima;


using namespace eProsima;

SequenceTypeCode::SequenceTypeCode() : ContentTypeCode(TypeCode::KIND_SEQUENCE),m_maxLength(0)
{
}

SequenceTypeCode::SequenceTypeCode(const SequenceTypeCode& copy): ContentTypeCode(TypeCode::KIND_SEQUENCE), m_maxLength(copy.m_maxLength)
{
	this->setContentTypeCode(TypeCodeCopy::copy(copy.getContentTypeCode()));
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
	catch(exception::Exception &ex)
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
