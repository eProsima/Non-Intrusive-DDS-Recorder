/******************************************************************************************
 * Copyright (c) 2015 eProsima. All rights reserved.
 *
 * This copy of eProsima Non-Intrusive DDS Recorder is licensed to you
 * under the terms described in the DDSRECORDER_LICENSE file included in this distribution.
 *
 *****************************************************************************************/
#ifndef _CDR_UNIONTYPECODE_H_
#define _CDR_UNIONTYPECODE_H_

#include "cdr/MemberedTypeCode.h"
#include <vector>

namespace eprosima{ namespace fastcdr{

 class Cdr;
}}
using namespace eprosima::fastcdr;

namespace eprosima
{

    class IDLPrinter;

    class UnionMember : public Member
    {
    public:
        UnionMember(std::string &name, uint32_t labelCount, std::vector<int32_t> label);

        UnionMember();

        UnionMember(const UnionMember& copy);

        virtual ~UnionMember(){}

        uint32_t getLabelCount() const;

        int32_t getLabel(uint32_t pos) const;

        void setLabels(std::vector<int32_t>& labels);

        std::vector<int32_t> getLabels() const;

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

        UnionTypeCode(const UnionTypeCode& copy_from_me);

        /*!
         * @brief Default destructor.
         */
        virtual ~UnionTypeCode();



        int32_t getDefaultIndex() const;

        void setDefaultIndex(int32_t def);

        /*!
         * @brief This function deserializes a union that is contained in a CDR stream.
         *
         * @param Reference to the CDR stream.
         * @return if the operation works successfully then a true value is returned. In other case false value is returned.
         */
        bool deserialize(Cdr &cdr);

		bool print(IDLPrinter &printer, bool write) const;

		friend inline bool operator<<(IDLPrinter &printer, const UnionTypeCode &unionTypeCode) {return unionTypeCode.print(printer, true);}

        friend bool operator<<(IDLPrinter &printer, const UnionTypeCode *unionTypeCode);

        bool addMember(UnionMember* member);

        void setDiscriminatorTypeCode(TypeCode*);



    private:

        Member* deserializeMemberInfo(std::string name, Cdr &cdr);

        int32_t m_defaultIndex;

        TypeCode *m_discriminatorTypeCode;
    };

    bool operator<<(IDLPrinter &printer, const UnionTypeCode *unionTypeCode);
};

#endif // _CDR_UNIONTYPECODE_H_
