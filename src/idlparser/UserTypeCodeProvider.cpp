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










} /* namespace eprosima */
