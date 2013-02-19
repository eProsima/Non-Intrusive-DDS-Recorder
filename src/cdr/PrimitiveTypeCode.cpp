#include "cdr/PrimitiveTypeCode.h"
#include "util/IDLPrinter.h"
#include "Cdr.h"

using namespace eProsima;

bool PrimitiveTypeCode::deserialize(CDR &cdr)
{
    return cdr >> m_dump;
}

bool PrimitiveTypeCode::print(IDLPrinter &printer, bool write) const
{
    bool returnedValue = false;

	if(write)
	{
		switch(getKind())
		{
		case TypeCode::KIND_SHORT:
			 printer << "short";
			 returnedValue = true;
			 break;
		case TypeCode::KIND_LONG:
			 printer << "long";
			 returnedValue = true;
			 break;
		case TypeCode::KIND_USHORT:
			 printer << "unsigned short";
			 returnedValue = true;
			 break;
		case TypeCode::KIND_ULONG:
			 printer << "unsigned long";
			 returnedValue = true;
			 break;
		case TypeCode::KIND_FLOAT:
			 printer << "float";
			 returnedValue = true;
			 break;
		 case TypeCode::KIND_DOUBLE:
			 printer << "double";
			 returnedValue = true;
			 break;
		 case TypeCode::KIND_BOOLEAN:
			 printer << "boolean";
			 returnedValue = true;
			 break;
		 case TypeCode::KIND_CHAR:
			 printer << "char";
			 returnedValue = true;
			 break;
		 case TypeCode::KIND_OCTET:
			 printer << "octet";
			 returnedValue = true;
			 break;
		 case TypeCode::KIND_LONGLONG:
			 printer << "long long";
			 returnedValue = true;
			 break;
		 case TypeCode::KIND_ULONGLONG:
			 printer << "unsigned long long";
			 returnedValue = true;
			 break;
		 case TypeCode::KIND_LONGDOUBLE:
			 printer << "long double";
			 returnedValue = true;
			 break;
		 case TypeCode::KIND_WCHAR:
			 printer << "wchar";
			 returnedValue = true;
			 break;
		}
	}
	else
		returnedValue = true;

    return returnedValue;
}

bool eProsima::operator<<(IDLPrinter &printer, const PrimitiveTypeCode *typeCode)
{
    bool returnedValue = false;

    if(typeCode != NULL)
        returnedValue = printer << *typeCode;

    return returnedValue;
}
