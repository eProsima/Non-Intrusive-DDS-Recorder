/******************************************************************************************
 * Copyright (c) 2015 eProsima. All rights reserved.
 *
 * This copy of eProsima Non-Intrusive DDS Recorder is licensed to you
 * under the terms described in the DDSRECORDER_LICENSE file included in this distribution.
 *
 *****************************************************************************************/
#ifndef _CDR_STRINGTYPECODE_H_
#define _CDR_STRINGTYPECODE_H_

#include "cdr/PrimitiveTypeCode.h"

namespace eprosima
{
    class StringTypeCode : public PrimitiveTypeCode
    {
    public:

        StringTypeCode() : PrimitiveTypeCode(TypeCode::KIND_STRING), m_dump(0), m_maxLength(0){}

        StringTypeCode(uint32_t maxL): PrimitiveTypeCode(TypeCode::KIND_STRING),m_dump(0),m_maxLength(maxL){};

        StringTypeCode(const StringTypeCode& copy): PrimitiveTypeCode(TypeCode::KIND_STRING),
        		m_dump(copy.m_dump), m_maxLength(copy.m_maxLength){};

        virtual ~StringTypeCode(){}

        /*!
         * @brief This function deserializes a string that is contained in a CDR stream.
         *
         * @param Reference to the CDR stream.
         * @return if the operation works successfully then a true value is returned. In other case false value is returned.
         */
        bool deserialize(Cdr &cdr);

		bool print(IDLPrinter &printer, bool write) const;

		friend inline bool operator<<(IDLPrinter &printer, const StringTypeCode &typeCode) {return typeCode.print(printer, true);}

        friend bool operator<<(IDLPrinter &printer, const StringTypeCode *typeCode);

    private:

        uint16_t m_dump;
        uint32_t m_maxLength;
    };

    bool operator<<(IDLPrinter &printer, const StringTypeCode *typeCode);
};

#endif // _CDR_STRINGTYPECODE_H_
