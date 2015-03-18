/******************************************************************************************
 * Copyright (c) 2015 eProsima. All rights reserved.
 *
 * This copy of eProsima Non-Intrusive DDS Recorder is licensed to you
 * under the terms described in the DDSRECORDER_LICENSE file included in this distribution.
 *
 *****************************************************************************************/
#ifndef _CDR_PRIMITIVETYPECODE_H_
#define _CDR_PRIMITIVETYPECODE_H_

#include "cdr/TypeCode.h"

namespace eprosima
{
    class PrimitiveTypeCode : public TypeCode
    {
    public:

        PrimitiveTypeCode(uint32_t kind) : TypeCode(kind),m_dump(0){}

        virtual ~PrimitiveTypeCode(){}

        /*!
         * @brief This function deserializes a primitive that is contained in a CDR stream.
         *
         * @param Reference to the CDR stream.
         * @return if the operation works successfully then a true value is returned. In other case false value is returned.
         */
        bool deserialize(Cdr &cdr);

		bool print(IDLPrinter &printer, bool write) const;

		friend inline bool operator<<(IDLPrinter &printer, const PrimitiveTypeCode &typeCode) {return typeCode.print(printer, true);}

        friend bool operator<<(IDLPrinter &printer, const PrimitiveTypeCode *typeCode);

    private:

        uint16_t m_dump;
    };
};

#endif // _CDR_PRIMITIVETYPECODE_H_
