/*************************************************************************
 * Copyright (c) 2014 eProsima. All rights reserved.
 *
 * This copy of eProsima RTPS is licensed to you under the terms described in the
 * EPROSIMARTPS_LIBRARY_LICENSE file included in this distribution.
 *
 *************************************************************************/

/**
 * @file UserTypeCodeProvider.cpp
 *
 */

#include "UserTypeCodeProvider.h"
#include "cdr/TypeCodeCopy.h"

#include "IDLScanner.h"

#include <sstream>
#include <string>
#include <iostream>
#include <fstream>

namespace eprosima {


UserTypeCodeProvider::~UserTypeCodeProvider() {
	// TODO Auto-generated destructor stub
}

UserTypeCodeProvider::UserTypeCodeProvider()
: trace_scanning(false),
  trace_parsing(false),
  lexer(NULL)
{
}

bool UserTypeCodeProvider::parse_stream(std::istream& in, const std::string& sname)
{
	streamname = sname;

	IDLScanner scanner(&in);
	scanner.set_debug(trace_scanning);
	this->lexer = &scanner;

	IDLParser parser(*this);
	parser.set_debug_level((int)trace_parsing);
	return (parser.parse() == 0);
}

bool UserTypeCodeProvider::parse_file(const std::string &filename)
{
	std::ifstream in(filename.c_str());
	if (!in.good()) return false;
	return parse_stream(in, filename);
}

bool UserTypeCodeProvider::parse_string(const std::string &input, const std::string& sname)
{
	std::istringstream iss(input);
	return parse_stream(iss, sname);
}

void UserTypeCodeProvider::error(const class location& l,const std::string& m)
{
	std::cerr << l << ": " << m << std::endl;
}

void UserTypeCodeProvider::error(const std::string& m)
{
	std::cerr << m << std::endl;
}


TypeCode* UserTypeCodeProvider::copyTypeCode(TypeCode* pTC, bool first)
{
	return TypeCodeCopy::copy(pTC,first);
}


TypeCode* UserTypeCodeProvider::findTypeCodebyName(std::string& instr)
{
	TypeCode* pTC = NULL;
	for(std::vector<TypeCode*>::iterator it = m_typeCodes.begin();
			it!=m_typeCodes.end();++it)
	{
		pTC = (*it);
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
		case TypeCode::KIND_STRING:
		case TypeCode::KIND_SEQUENCE:
		{
			std::cout << "Primitive Types don't have names"<<std::endl;
			break;
		}
		case TypeCode::KIND_STRUCT:
		case TypeCode::KIND_UNION:
		case TypeCode::KIND_ENUM:
		{
			if(((MemberedTypeCode*)pTC)->getName() == instr)
				return pTC;
			break;
		}
		case TypeCode::KIND_ALIAS:
		case TypeCode::KIND_WSTRING:
		case TypeCode::KIND_VALUE:
		case TypeCode::KIND_SPARSE:
		{
			std::cout << " Not Defined Yet!"<<std::endl;
			break;
		}
		}
	}
	return new PrimitiveTypeCode(TypeCode::KIND_NULL); //TO FIX LATER
}

int32_t UserTypeCodeProvider::findENUMvalue(std::string& instr)
{
	for(std::vector<TypeCode*>::iterator it = m_typeCodes.begin();
			it!=m_typeCodes.end();++it)
	{
		if((*it)->getKind() == TypeCode::KIND_ENUM)
		{
			EnumTypeCode* eTC = (EnumTypeCode*)(*it);
			for(uint32_t i = 0;i<eTC->getMemberCount();++i)
			{
				EnumMember* eM = (EnumMember*)eTC->getMember(i);
				if(eM->getName() == instr)
					return eM->getOrdinal();
			}
		}
	}
	return 0; //TO FIX LATER
}

bool UserTypeCodeProvider::addTypeCode(TypeCode* TC)
{
	if(TC->getKind()!=TypeCode::KIND_NULL)
	{
		m_typeCodes.push_back(TC);
		return true;
	}
	else
	{
		delete(TC);
	}
	return false;
}









} /* namespace eprosima */
