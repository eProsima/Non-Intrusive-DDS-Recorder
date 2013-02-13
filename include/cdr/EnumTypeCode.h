#ifndef _CDR_ENUMTYPECODE_H_
#define _CDR_ENUMTYPECODE_H_

#include "cdr/MemberedTypeCode.h"

namespace eProsima
{
    class CDR;

    class EnumMember : public Member
    {
    public:
        EnumMember(std::string &name, uint32_t ordinal);

        virtual ~EnumMember(){}

        bool deserialize(CDR &cdr);

        /*!
         * @brief This function returns the ordinal value of the member.
         */
        uint32_t getOrdinal() const;

    private:
        uint32_t m_ordinal;
    };

    class EnumTypeCode : public MemberedTypeCode
    {
    public:

        /*!
         * @brief Default constructor.
         */
        EnumTypeCode();

        /*!
         * @brief Default destructor.
         */
        virtual ~EnumTypeCode(){}

        /*!
         * @brief This function deserializes a enumeration that is contained in a CDR stream.
         *
         * @param Reference to the CDR stream.
         * @return if the operation works successfully then a true value is returned. In other case false value is returned.
         */
        bool deserialize(CDR &cdr);

        /*!
         * @brief This function returns a pointer to the member with the given ordinal.
         */
        const EnumMember* getMemberWithOrdinal(uint32_t ordinal) const;

        friend bool operator<<(IDLPrinter &printer, const EnumTypeCode &typeCode);

        friend bool operator<<(IDLPrinter &printer, const EnumTypeCode *typeCode);

    private:
        
        Member* deserializeMemberInfo(std::string name, CDR &cdr);
    };
};

#endif // _CDR_ENUMTYPECODE_H_
