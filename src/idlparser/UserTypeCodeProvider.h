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
using namespace eProsima;
#include <iostream>

namespace eprosima {



class UserTypeCodeProvider {
public:
	UserTypeCodeProvider();
	virtual ~UserTypeCodeProvider();

	void addTypeCode(TypeCode*);

	TypeCode* findTypeCodebyName(std::string& in)
	{
		return new PrimitiveTypeCode(TypeCode::KIND_NULL); //TO FIX LATER
	}

	int32_t findENUMvalue(std::string& in)
	{
		return 0; //TO FIX LATER
	}



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

	std::vector<TypeCode*> m_typecodes;

	TypeCode* copyTypeCode(TypeCode* tc, bool first);


};

} /* namespace eprosima */

#endif /* USERTYPECODEPROVIDER_H_ */
