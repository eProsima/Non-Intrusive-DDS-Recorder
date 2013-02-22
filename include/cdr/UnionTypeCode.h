#ifndef _CDR_UNIONTYPECODE_H_
#define _CDR_UNIONTYPECODE_H_

#include "cdr/MemberedTypeCode.h"

namespace eProsima
{
    class CDR;
    class IDLPrinter;

    class UnionMember : public Member
    {
    public:
        UnionMember(std::string &name, uint16_t bits, uint8_t flags);

        virtual ~UnionMember(){}

    private:
        uint16_t m_bits;
        uint8_t m_flags;
    };

    class UnionTypeCode : public MemberedTypeCode
    {
    public:

        /*!
         * @brief Default constructor.
         */
        UnionTypeCode();

        /*!
         * @brief Default destructor.
         */
        virtual ~UnionTypeCode(){}

        /*!
         * @brief This function deserializes a union that is contained in a CDR stream.
         *
         * @param Reference to the CDR stream.
         * @return if the operation works successfully then a true value is returned. In other case false value is returned.
         */
        bool deserialize(CDR &cdr);

		bool print(IDLPrinter &printer, bool write) const;

		friend inline bool operator<<(IDLPrinter &printer, const UnionTypeCode &unionTypeCode) {return unionTypeCode.print(printer, true);}

        friend bool operator<<(IDLPrinter &printer, const UnionTypeCode *unionTypeCode);

    private:
        
        Member* deserializeMemberInfo(std::string name, CDR &cdr);
    };
};

#endif // _CDR_UNIONTYPECODE_H_
