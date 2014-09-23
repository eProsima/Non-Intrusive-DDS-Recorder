#include "cdr/MemberedTypeCode.h"

using namespace eProsima;

Member::Member(std::string &name) : m_name(name), m_typeCode(NULL)
{
}

Member::~Member()
{
    if(m_typeCode != NULL)
        delete m_typeCode;
}

const std::string& Member::getName() const
{
    return m_name;
}

const TypeCode* Member::getTypeCode() const
{
    return m_typeCode;
}

bool Member::deserialize(Cdr &cdr)
{
    return (m_typeCode = TypeCode::deserializeTypeCode(cdr)) != NULL;
}

MemberedTypeCode::MemberedTypeCode(uint32_t kind) : TypeCode(kind)
{
}

MemberedTypeCode::~MemberedTypeCode()
{
    std::vector<Member*>::iterator it = m_members.begin();
    Member *member = NULL;

    while(it != m_members.end())
    {
        member = *it;

        if(member != NULL)
            delete member;

        it = m_members.erase(it);
    }
}

std::string MemberedTypeCode::getName() const
{
    return m_name;
}

uint32_t MemberedTypeCode::getMemberCount() const
{
    return m_memberCount;
}

const Member* MemberedTypeCode::getMember(uint32_t index) const
{
    return m_members[index];
}

bool MemberedTypeCode::deserializeMembers(Cdr &cdr)
{
    bool returnedValue = true;
    uint16_t msize = 0;
    std::string mname;
    Member *member = NULL;

    try
    {
        cdr >> m_memberCount;

        for(uint32_t i = 0; i < m_memberCount; ++i)
        {
            cdr >> msize;
            cdr >> mname;
            member = deserializeMemberInfo(mname, cdr);

            if(member != NULL)
            {
                if(member->deserialize(cdr))
                {
                    m_members.push_back(member);
                }
                else
                {
                    delete member;
                    returnedValue = false;
                    break;
                }
            }
        }
    }
    catch(exception::Exception &ex)
    {
        returnedValue = false;
    }

    return returnedValue;
}
