/*************************************************************************
 * Copyright (c) 2014 eProsima. All rights reserved.
 *
 * This copy of eProsima RTPS is licensed to you under the terms described in the
 * EPROSIMARTPS_LIBRARY_LICENSE file included in this distribution.
 *
 *************************************************************************/

/**
 * @file TypeCodeCopy.h
 *
 */

#ifndef TYPECODECOPY_H_
#define TYPECODECOPY_H_
namespace eProsima{
class TypeCode;
}
using namespace eProsima;

namespace eprosima {



class TypeCodeCopy {
private:
	TypeCodeCopy();
	virtual ~TypeCodeCopy();
public:
	static TypeCode* copy(const TypeCode* copy, bool first = false);
};

} /* namespace eprosima */

#endif /* TYPECODECOPY_H_ */
