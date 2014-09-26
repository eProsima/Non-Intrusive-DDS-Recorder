#include "cdr/PrimitiveTypeCode.h"
#include "util/IDLPrinter.h"
#include "fastcdr/Cdr.h"

using namespace eprosima;

bool PrimitiveTypeCode::deserialize(Cdr &cdr)
{
    try
    {
        cdr >> m_dump;
        return true;
    }
    catch(exception::Exception &ex){}

    return false;
}

bool PrimitiveTypeCode::print(IDLPrinter &printer, bool write) const
{
    bool returnedValue = false;

	if(write)
	{
		switch(getKind())
		{
		case TypeCode::KIND_SHORT:
			 printer.getOut() << "short";
			 returnedValue = true;
			 break;
		case TypeCode::KIND_LONG:
			 printer.getOut() << "long";
			 returnedValue = true;
			 break;
		case TypeCode::KIND_USHORT:
			 printer.getOut() << "unsigned short";
			 returnedValue = true;
			 break;
		case TypeCode::KIND_ULONG:
			 printer.getOut() << "unsigned long";
			 returnedValue = true;
			 break;
		case TypeCode::KIND_FLOAT:
			 printer.getOut() << "float";
			 returnedValue = true;
			 break;
		 case TypeCode::KIND_DOUBLE:
			 printer.getOut() << "double";
			 returnedValue = true;
			 break;
		 case TypeCode::KIND_BOOLEAN:
			 printer.getOut() << "boolean";
			 returnedValue = true;
			 break;
		 case TypeCode::KIND_CHAR:
			 printer.getOut() << "char";
			 returnedValue = true;
			 break;
		 case TypeCode::KIND_OCTET:
			 printer.getOut() << "octet";
			 returnedValue = true;
			 break;
		 case TypeCode::KIND_LONGLONG:
			 printer.getOut() << "long long";
			 returnedValue = true;
			 break;
		 case TypeCode::KIND_ULONGLONG:
			 printer.getOut() << "unsigned long long";
			 returnedValue = true;
			 break;
		 case TypeCode::KIND_LONGDOUBLE:
			 printer.getOut() << "long double";
			 returnedValue = true;
			 break;
		 case TypeCode::KIND_WCHAR:
			 printer.getOut() << "wchar";
			 returnedValue = true;
			 break;
		}
	}
	else
		returnedValue = true;

    return returnedValue;
}

bool eprosima::operator<<(IDLPrinter &printer, const PrimitiveTypeCode *typeCode)
{
    bool returnedValue = false;

    if(typeCode != NULL)
        returnedValue = printer << *typeCode;

    return returnedValue;
}
