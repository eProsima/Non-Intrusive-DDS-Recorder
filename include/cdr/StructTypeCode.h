#ifndef _CDR_STRUCTTYPECODE_H_
#define _CDR_STRUCTTYPECODE_H_

#include "cdr/MemberedTypeCode.h"

namespace eProsima
{
    class CDR;
    class IDLPrinter;

    class StructMember : public Member
    {
    public:
        StructMember(std::string &name, uint16_t bits, uint8_t flags);

        virtual ~StructMember(){}

    private:
        uint16_t m_bits;
        uint8_t m_flags;
    };

    class StructTypeCode : public MemberedTypeCode
    {
    public:

        /*!
         * @brief Default constructor.
         */
        StructTypeCode();

        /*!
         * @brief Default destructor.
         */
        virtual ~StructTypeCode(){}

        /*!
         * @brief This function deserializes a structure that is contained in a CDR stream.
         *
         * @param Reference to the CDR stream.
         * @return if the operation works successfully then a true value is returned. In other case false value is returned.
         */
        bool deserialize(CDR &cdr);

		bool print(IDLPrinter &printer, bool write) const;

		friend inline bool operator<<(IDLPrinter &printer, const StructTypeCode &structTypeCode) {return structTypeCode.print(printer, true);}

        friend bool operator<<(IDLPrinter &printer, const StructTypeCode *structTypeCode);

    private:
        
        Member* deserializeMemberInfo(std::string name, CDR &cdr);
    };
};

#endif // _CDR_STRUCTTYPECODE_H_
