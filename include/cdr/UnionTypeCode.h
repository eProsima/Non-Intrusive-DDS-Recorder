#ifndef _CDR_UNIONTYPECODE_H_
#define _CDR_UNIONTYPECODE_H_

#include "cdr/MemberedTypeCode.h"
#include <vector>

namespace eProsima
{
    class CDR;
    class IDLPrinter;

    class UnionMember : public Member
    {
    public:
        UnionMember(std::string &name, uint32_t labelCount, std::vector<int32_t> label);

        virtual ~UnionMember(){}

        uint32_t getLabelCount() const;

        int32_t getLabel(uint32_t pos) const;

    private:
        uint32_t m_labelCount;
        std::vector<int32_t> m_labels;
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
        virtual ~UnionTypeCode();

        int32_t getDefaultIndex() const;

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

        int32_t m_defaultIndex;

        TypeCode *m_discriminatorTypeCode;
    };
};

#endif // _CDR_UNIONTYPECODE_H_
