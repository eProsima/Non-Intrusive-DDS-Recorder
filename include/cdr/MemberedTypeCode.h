#ifndef _CDR_MEMBEREDTYPECODE_H_
#define _CDR_MEMBEREDTYPECODE_H_

#include "cdr/TypeCode.h"
#include "cpp/Cdr.h"
#include "cpp/exceptions/Exception.h"

#include <string>
#include <vector>

namespace eProsima
{
    class Member
    {
        public:

        /*!
         * @brief Default constructor.
         */
        Member(std::string &name);

        //! @brief Default destructor;
        virtual ~Member();

        /*!
         * @brief This function returns the name of the member.
         */
        const std::string& getName() const;

        /*!
         * @brief This function returns the typecode of the member.
         */
        const TypeCode* getTypeCode() const;

        /*!
         * @brief This function deserializes the member's typecode.
         */
        virtual bool deserialize(Cdr &cdr);

        private:

        std::string m_name;

        TypeCode *m_typeCode;
    };

    class MemberedTypeCode : public TypeCode
    {
    public:

        /*!
         * @brief This function returns the name of the membered type.
         */
        std::string getName() const;

        /*!
         * @brief This function returns the member count of the membered type.
         */
        uint32_t getMemberCount() const;

        /*!
         * @brief This function returns the member that is indicated by a indez.
         */
        const Member* getMember(uint32_t index) const;

    protected:

        //! @brief Default constructor.
        MemberedTypeCode(uint32_t kind);

        //! @brief Default destructor.
        virtual ~MemberedTypeCode();

        /*!
         * @brief This function deserializes the name of a membered typecode.
         */
        inline bool deserializeName(Cdr &cdr)
        {
            try
            {
                cdr >> m_name;
                return true;
            }
            catch(eProsima::Exception &ex)
            {
                return false;
            }
        }

        /*!
         * @brief This function deserializes the members of the type.
         */
        bool deserializeMembers(Cdr &cdr);

        /*!
         * @brief This function has to be implemented to deserialize the specific member.
         */
        virtual Member* deserializeMemberInfo(std::string name, Cdr &cdr) = 0;

        std::vector<Member*> m_members;

    private:

        std::string m_name;

        uint32_t m_memberCount;
    };
};

#endif // _CDR_MEMBEREDTYPECODE_H_
