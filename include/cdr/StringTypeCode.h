#ifndef _CDR_STRINGTYPECODE_H_
#define _CDR_STRINGTYPECODE_H_

#include "cdr/PrimitiveTypeCode.h"

namespace eProsima
{
    class StringTypeCode : public PrimitiveTypeCode
    {
    public:

        StringTypeCode() : PrimitiveTypeCode(TypeCode::KIND_STRING){}

        StringTypeCode(uint32_t maxL): PrimitiveTypeCode(TypeCode::KIND_STRING),m_maxLength(maxL){};

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
};

#endif // _CDR_STRINGTYPECODE_H_
