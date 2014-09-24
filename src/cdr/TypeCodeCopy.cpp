/*************************************************************************
 * Copyright (c) 2014 eProsima. All rights reserved.
 *
 * This copy of eProsima RTPS is licensed to you under the terms described in the
 * EPROSIMARTPS_LIBRARY_LICENSE file included in this distribution.
 *
 *************************************************************************/

/**
 * @file TypeCodeCopy.cpp
 *
 */

#include "cdr/TypeCodeCopy.h"
#include "cdr/all_TypeCodes.h"
using namespace eProsima;

#include <iostream>

namespace eprosima {

TypeCodeCopy::TypeCodeCopy() {
	// TODO Auto-generated constructor stub

}

TypeCodeCopy::~TypeCodeCopy() {
	// TODO Auto-generated destructor stub
}

TypeCode* TypeCodeCopy::copy(const TypeCode* pTC, bool first)
{
	TypeCode* outpTC = (TypeCode*)pTC;
	switch(pTC->getKind())
		{
		case TypeCode::KIND_SHORT:
		case TypeCode::KIND_LONG:
		case TypeCode::KIND_USHORT:
		case TypeCode::KIND_ULONG:
		case TypeCode::KIND_FLOAT:
		case TypeCode::KIND_DOUBLE:
		case TypeCode::KIND_BOOLEAN:
		case TypeCode::KIND_CHAR:
		case TypeCode::KIND_OCTET:
		case TypeCode::KIND_LONGLONG:
		case TypeCode::KIND_ULONGLONG:
		case TypeCode::KIND_LONGDOUBLE:
		case TypeCode::KIND_WCHAR:
		case TypeCode::KIND_NULL:
		{
			if(!first)
				outpTC = (TypeCode*)new PrimitiveTypeCode(pTC->getKind());
			break;
		}
		case TypeCode::KIND_STRUCT:
		{
			outpTC = (TypeCode*) new StructTypeCode(*(StructTypeCode*)pTC);
			break;
		}
		case TypeCode::KIND_UNION:
		{
			outpTC = (TypeCode*) new UnionTypeCode(*(UnionTypeCode*)pTC);
			break;
		}
		case TypeCode::KIND_ENUM:
		{
			outpTC = (TypeCode*) new EnumTypeCode(*(EnumTypeCode*)pTC);
			break;
		}
		case TypeCode::KIND_STRING:
		{
			if(!first)
				outpTC = (TypeCode*) new StringTypeCode(*(StringTypeCode*)pTC);
			break;
		}
		case TypeCode::KIND_SEQUENCE:
		{
			if(!first)
				outpTC = (TypeCode*) new SequenceTypeCode(*(SequenceTypeCode*)pTC);
			break;
		}
		case TypeCode::KIND_ALIAS:
		{
			std::cout << "Copy Not Defined Yet!"<<std::endl;
			break;
		}
		case TypeCode::KIND_WSTRING:
		{
			std::cout << "Copy Not Defined Yet!"<<std::endl;
			break;
		}
		case TypeCode::KIND_VALUE:
		{
			std::cout << "Copy Not Defined Yet!"<<std::endl;
			break;
		}
		case TypeCode::KIND_SPARSE:
		{
			std::cout << "Copy Not Defined Yet!"<<std::endl;
			break;
		}
		}
		// TO FINISH THIS FOR ALL TYPES

		return outpTC;
}

} /* namespace eprosima */
