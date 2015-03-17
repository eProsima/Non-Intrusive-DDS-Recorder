#ifndef _CDR_ENUMTYPECODE_H_
#define _CDR_ENUMTYPECODE_H_

#include "cdr/MemberedTypeCode.h"

namespace eprosima{ namespace fastcdr{

 class Cdr;
}}
using namespace eprosima::fastcdr;

namespace eprosima
{


    class EnumMember : public Member
    {
    public:
        EnumMember(std::string &name, uint32_t ordinal);

        EnumMember(const EnumMember& copy);

        virtual ~EnumMember(){}

        bool deserialize(Cdr &cdr);

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

        EnumTypeCode(const EnumTypeCode& copy_from_me);

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
        bool deserialize(Cdr &cdr);

        /*!
         * @brief This function returns a pointer to the member with the given ordinal.
         */
        const EnumMember* getMemberWithOrdinal(uint32_t ordinal) const;

		bool print(IDLPrinter &printer, bool write) const;

		friend inline bool operator<<(IDLPrinter &printer, const EnumTypeCode &typeCode) {return typeCode.print(printer, true);}

        friend bool operator<<(IDLPrinter &printer, const EnumTypeCode *typeCode);

        bool addMember(EnumMember* mem);

    private:
        
        Member* deserializeMemberInfo(std::string name, Cdr &cdr);
    };
};

#endif // _CDR_ENUMTYPECODE_H_
