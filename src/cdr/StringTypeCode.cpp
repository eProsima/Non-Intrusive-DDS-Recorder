#include "cdr/StringTypeCode.h"
#include "util/IDLPrinter.h"
#include "fastcdr/Cdr.h"
#include "fastcdr/exceptions/Exception.h"

using namespace eProsima;

bool StringTypeCode::deserialize(Cdr &cdr)
{
    try
    {
        cdr >> m_dump;
        cdr >> m_maxLength;
        return true;
    }
    catch(exception::Exception &ex) {}

    return false;
}

bool StringTypeCode::print(IDLPrinter &printer, bool write) const
{
	if(write)
		printer.getOut() << "string ";
	return true;
}

bool eProsima::operator<<(IDLPrinter &printer, const StringTypeCode *typeCode)
{
    bool returnedValue = false;

    if(typeCode != NULL)
        returnedValue = printer << *typeCode;

    return returnedValue;
}
