/******************************************************************************************
 * Copyright (c) 2015 eProsima. All rights reserved.
 *
 * This copy of eProsima Non-Intrusive DDS Recorder is licensed to you
 * under the terms described in the DDSRECORDER_LICENSE file included in this distribution.
 *
 *****************************************************************************************/
#include "cdr/StringTypeCode.h"
#include "util/IDLPrinter.h"
#include "fastcdr/Cdr.h"
#include "fastcdr/exceptions/Exception.h"

using namespace eprosima;

bool StringTypeCode::deserialize(Cdr &cdr)
{
    try
    {
        cdr >> m_dump;
        cdr >> m_maxLength;
        return true;
    }
    catch(exception::Exception &ex) {}

    return false;
}

bool StringTypeCode::print(IDLPrinter &printer, bool write) const
{
	if(write)
		printer.getOut() << "string<"<< m_maxLength << ">";
	return true;
}

bool eprosima::operator<<(IDLPrinter &printer, const StringTypeCode *typeCode)
{
    bool returnedValue = false;

    if(typeCode != NULL)
        returnedValue = printer << *typeCode;

    return returnedValue;
}
