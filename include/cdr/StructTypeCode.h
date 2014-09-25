#ifndef _CDR_STRUCTTYPECODE_H_
#define _CDR_STRUCTTYPECODE_H_

#include "cdr/MemberedTypeCode.h"

namespace eprosima{ namespace fastcdr{

 class Cdr;
}}
using namespace eprosima::fastcdr;

namespace eProsima
{

    class IDLPrinter;

    class StructMember : public Member
    {
    public:
        StructMember(std::string &name, uint16_t bits, uint8_t flags);
        StructMember(const StructMember& copy);

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

        StructTypeCode(const StructTypeCode& copy_from_me);

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
        bool deserialize(Cdr &cdr);

		bool print(IDLPrinter &printer, bool write) const;

		friend inline bool operator<<(IDLPrinter &printer, const StructTypeCode &structTypeCode) {return structTypeCode.print(printer, true);}

        friend bool operator<<(IDLPrinter &printer, const StructTypeCode *structTypeCode);

        bool addMember(StructMember* sm);

    private:
        
        Member* deserializeMemberInfo(std::string name, Cdr &cdr);
    };
};

#endif // _CDR_STRUCTTYPECODE_H_
