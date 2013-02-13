#ifndef _CDR_PRIMITIVETYPECODE_H_
#define _CDR_PRIMITIVETYPECODE_H_

#include "cdr/TypeCode.h"

namespace eProsima
{
    class PrimitiveTypeCode : public TypeCode
    {
    public:

        PrimitiveTypeCode(uint32_t kind) : TypeCode(kind){}

        virtual ~PrimitiveTypeCode(){}

        /*!
         * @brief This function deserializes a primitive that is contained in a CDR stream.
         *
         * @param Reference to the CDR stream.
         * @return if the operation works successfully then a true value is returned. In other case false value is returned.
         */
        bool deserialize(CDR &cdr);

        friend bool operator<<(IDLPrinter &printer, const PrimitiveTypeCode &typeCode);

        friend bool operator<<(IDLPrinter &printer, const PrimitiveTypeCode *typeCode);

    private:

        uint16_t m_dump;
    };
};

#endif // _CDR_PRIMITIVETYPECODE_H_
