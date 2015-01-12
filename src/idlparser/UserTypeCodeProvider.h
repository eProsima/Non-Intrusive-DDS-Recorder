/*************************************************************************
 * Copyright (c) 2014 eProsima. All rights reserved.
 *
 * This copy of eProsima RTPS is licensed to you under the terms described in the
 * EPROSIMARTPS_LIBRARY_LICENSE file included in this distribution.
 *
 *************************************************************************/

/**
 * @file UserTypeCodeProvider.h
 *
 */

#ifndef USERTYPECODEPROVIDER_H_
#define USERTYPECODEPROVIDER_H_

#include <string>
#include <vector>
#include "cdr/all_TypeCodes.h"

#include <iostream>

namespace eprosima {




class UserTypeCodeProvider {
public:
	UserTypeCodeProvider();
	virtual ~UserTypeCodeProvider();

	TypeCode* findTypeCodebyName(std::string& in);

	TypeCode* findTypeCodeWithExactName(std::string& in);

	int32_t findENUMvalue(std::string& in);

	bool addTypeCode(TypeCode* TC);

	bool getStructTypeCode(const std::string& name, TypeCode** ppTC);


	bool trace_scanning;

	bool trace_parsing;

	std::string streamname;

	bool parse_stream(std::istream& in,
			const std::string& sname = "stream input");

	bool parse_string(const std::string& input,
			const std::string& sname = "string stream");

	bool parse_file(const std::string& filename);

	// To demonstrate pure handling of parse errors, instead of
	// simply dumping them on the standard error output, we will pass
	// them to the driver using the following two member functions.

	void error(const class location& l, const std::string& m);

	void error(const std::string& m);

	class IDLScanner* lexer;

	void printTypeCodes();
private:
	void deleteTypeCodes();
public:


	TypeCode* copyTypeCode(TypeCode* tc, bool first);
	enum ProviderError
	{
        PROVIDER_OK,
		TYPECODE_NOTFOUND,
		IDLPARSER_ERROR,
		REPEATED_STRUCT_MEMBER_ERROR,
		REPEATED_TYPECODE_NAME_ERROR
	};
	ProviderError m_errorCode;

	std::vector<std::string> m_namespaces;

	void addNamespace(std::string & name)
	{
		//printf("ADDING NAMESPACE\n");
		m_namespaces.push_back(name);
	}

	void removeNamespace()
	{
		//printf("REMOVING NAMESPACE\n");
		m_namespaces.pop_back();
	}

	std::string getCurrentNamespace()
	{
		std::string current;
		for(std::vector<std::string>::iterator it = m_namespaces.begin();
				it!=m_namespaces.end();++it)
		{
			current.append(*it);
			current.append("::");
		}
		//std::cout << "Current: "<< current << std::endl;
		return current;
	}

private:
	std::vector<TypeCode*> m_typeCodes;


};

} /* namespace eprosima */

#endif /* USERTYPECODEPROVIDER_H_ */
