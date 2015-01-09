#ifndef _CDR_MEMBEREDTYPECODE_H_
#define _CDR_MEMBEREDTYPECODE_H_

#include "cdr/TypeCode.h"
#include "fastcdr/Cdr.h"
#include "fastcdr/exceptions/Exception.h"

#include <string>
#include <vector>

using namespace eprosima::fastcdr;


namespace eprosima
{
    class Member
    {
        public:

        /*!
         * @brief Default constructor.
         */
        Member(std::string &name);

        Member();

        //! @brief Default destructor;
        virtual ~Member();

        /*!
         * @brief This function returns the name of the member.
         */
        const std::string& getName() const;
        /**
         * Set the name of the MemberedTypeCode.
         * @param name String to set.
         */
        void setName(std::string& name);

        /*!
         * @brief This function returns the typecode of the member.
         */
        const TypeCode* getTypeCode() const;
        /**
         * Set the TypeCode of the member.
         * @param Pointer to the typecode.
         */
        void setTypeCode(TypeCode*);

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
        /**
         * This functions sets the name of the MemberedTypeCode
         * @param name
         */
        void setName(std::string& name);

        /*!
         * @brief This function returns the member count of the membered type.
         */
        uint32_t getMemberCount() const;

        /*!
         * @brief This function returns the member that is indicated by a indez.
         */
        const Member* getMember(uint32_t index) const;


       bool isMemberWithName(const std::string& name);


    protected:

        void addMemberPtr(Member* m);

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
            catch(exception::Exception &ex)
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



        std::string m_name;

        uint32_t m_memberCount;
    };
};

#endif // _CDR_MEMBEREDTYPECODE_H_
