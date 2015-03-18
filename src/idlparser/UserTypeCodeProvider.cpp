/******************************************************************************************
 * Copyright (c) 2015 eProsima. All rights reserved.
 *
 * This copy of eProsima Non-Intrusive DDS Recorder is licensed to you
 * under the terms described in the DDSRECORDER_LICENSE file included in this distribution.
 *
 *****************************************************************************************/
#include "UserTypeCodeProvider.h"
#include "cdr/TypeCodeCopy.h"

#include "IDLScanner.h"

#include <sstream>
#include <string>
#include <iostream>
#include <fstream>

#include "util/IDLPrinter.h"

namespace eprosima {


UserTypeCodeProvider::~UserTypeCodeProvider() {
	// TODO Auto-generated destructor stub
	this->deleteTypeCodes();
}

UserTypeCodeProvider::UserTypeCodeProvider()
: trace_scanning(false),
  trace_parsing(false),
  lexer(NULL),
  m_errorCode(PROVIDER_OK)
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
	if(parser.parse() != 0)
	{
		m_errorCode = IDLPARSER_ERROR;
	}
	if(m_errorCode != PROVIDER_OK)
		return false;
	return true;
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

bool UserTypeCodeProvider::getStructTypeCode(const std::string& name, TypeCode** ppTC)
{
	TypeCode* pTC = NULL;

	for(std::vector<TypeCode*>::iterator it = m_typeCodes.begin();
			it!=m_typeCodes.end();++it)
	{
		pTC = (*it);
		if(pTC->getKind() == TypeCode::KIND_STRUCT)
		{
			if(((StructTypeCode*)pTC)->getName() == name)
			{
				*ppTC = TypeCodeCopy::copy((TypeCode*)pTC,false);
				return true;
			}
		}
	}
	return false;
}

TypeCode* UserTypeCodeProvider::findTypeCodebyName(std::string& instr)
{
	TypeCode* pTC = findTypeCodeWithExactName(instr);
	if(pTC !=NULL)
		return pTC;

	for(int i = m_namespaces.size();i>0;--i)
	{
		std::string name;
		for(int j = 0;j<i;++j)
		{
			name.append(m_namespaces.at(j));
			name.append("::");
		}
		name.append(instr);
		pTC = findTypeCodeWithExactName(name);
		if(pTC !=NULL)
			return pTC;
	}
	return new PrimitiveTypeCode(TypeCode::KIND_NULL);
}


TypeCode* UserTypeCodeProvider::findTypeCodeWithExactName(std::string& instr)
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
	return NULL; //TO FIX LATER
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
	//printf("Adding TYPECODE\n");
	if(TC->getKind()!=TypeCode::KIND_NULL)
	{
		if(TC->getKind()== TypeCode::KIND_STRUCT || TC->getKind() == TypeCode::KIND_UNION ||
				TC->getKind()==TypeCode::KIND_ENUM)
		{

			MemberedTypeCode* mTC = (MemberedTypeCode*)TC;
			std::string currentname = this->getCurrentNamespace();
			//std::cout <<"Adding TC with name " << mTC->getName() << std::endl;
			currentname.append(mTC->getName());
			mTC->setName(currentname);
			for(std::vector<TypeCode*>::iterator it = m_typeCodes.begin();it!=m_typeCodes.end();++it)
			{
				MemberedTypeCode* mTCin = (MemberedTypeCode*)(*it);
				if(mTCin->getName() == mTC->getName())
				{
					std::cout << "Warning: TypeCode with name: "<< mTC->getName()<< " already defined, ignoring second definition"<<std::endl;
					m_errorCode = REPEATED_TYPECODE_NAME_ERROR;
					return false;
				}
			}
			IDLPrinter txtStream;
			txtStream << TC;
			//std::cout << "*****************Adding TYpeCode "<<m_typeCodes.size() << " ::::::::::::::::::" <<std::endl<<txtStream.str();

			m_typeCodes.push_back(TC);

			//std::cout << "*****************ADDED***************** "<<std::endl;
		}
		return true;
	}
	else
	{
		delete(TC);
	}
	return false;
}


void UserTypeCodeProvider::printTypeCodes()
{
	for(std::vector<TypeCode*>::iterator it = m_typeCodes.begin();it!=m_typeCodes.end();++it)
	{
		IDLPrinter txtStream;
		txtStream << (*it);
		std::cout << "TypeCode: ****  "<< std::distance(m_typeCodes.begin(), it) << " *****************" << std::endl<< std::endl;
		std::cout << txtStream.str();
	}
}

void UserTypeCodeProvider::deleteTypeCodes()
{
	std::cout << "Deleting TypeCodes created when parsing IDL file"<<std::endl;
	for(std::vector<TypeCode*>::iterator it = m_typeCodes.begin();it!=m_typeCodes.end();++it)
	{
		//std::cout << " Deleting typecode " << std::distance(m_typeCodes.begin(), it)<< std::endl;
		delete(*it);
	}
}






} /* namespace eprosima */
