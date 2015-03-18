/******************************************************************************************
 * Copyright (c) 2015 eProsima. All rights reserved.
 *
 * This copy of eProsima Non-Intrusive DDS Recorder is licensed to you
 * under the terms described in the DDSRECORDER_LICENSE file included in this distribution.
 *
 *****************************************************************************************/
#include "cdr/ContentTypeCode.h"

#include <stdio.h>

using namespace eprosima;

ContentTypeCode::ContentTypeCode(uint32_t kind) : TypeCode(kind),
    m_contentTypeCode(NULL)
{
}

ContentTypeCode::~ContentTypeCode()
{
	//printf("Deleting contentTypeCode\n");
    if(m_contentTypeCode != NULL)
        delete m_contentTypeCode;
}

const TypeCode* ContentTypeCode::getContentTypeCode() const
{
    return m_contentTypeCode;
}

bool ContentTypeCode::deserializeContent(Cdr &cdr)
{
    return (m_contentTypeCode = TypeCode::deserializeTypeCode(cdr)) != NULL;
}

void ContentTypeCode::setContentTypeCode(TypeCode* TC)
{
	m_contentTypeCode = TC;
}
