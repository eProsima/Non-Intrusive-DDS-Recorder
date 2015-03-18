/******************************************************************************************
 * Copyright (c) 2015 eProsima. All rights reserved.
 *
 * This copy of eProsima Non-Intrusive DDS Recorder is licensed to you
 * under the terms described in the DDSRECORDER_LICENSE file included in this distribution.
 *
 *****************************************************************************************/
#ifndef TYPECODECOPY_H_
#define TYPECODECOPY_H_
namespace eprosima{
class TypeCode;
}


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
