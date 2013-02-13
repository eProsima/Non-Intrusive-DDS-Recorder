#ifndef _CDR_STRINGTYPECODE_H_
#define _CDR_STRINGTYPECODE_H_

#include "cdr/TypeCode.h"

namespace eProsima
{
    class StringTypeCode : public TypeCode
    {
    public:

        StringTypeCode() : TypeCode(TypeCode::KIND_STRING){}

        virtual ~StringTypeCode(){}

        /*!
         * @brief This function deserializes a string that is contained in a CDR stream.
         *
         * @param Reference to the CDR stream.
         * @return if the operation works successfully then a true value is returned. In other case false value is returned.
         */
        bool deserialize(CDR &cdr);

        friend bool operator<<(IDLPrinter &printer, const StringTypeCode &typeCode);

        friend bool operator<<(IDLPrinter &printer, const StringTypeCode *typeCode);

    private:

        uint16_t m_dump;
        uint32_t m_maxLength;
    };
};

#endif // _CDR_STRINGTYPECODE_H_
