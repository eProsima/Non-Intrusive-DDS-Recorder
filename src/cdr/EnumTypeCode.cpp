#include "cdr/EnumTypeCode.h"
#include "util/IDLPrinter.h"
#include "Cdr.h"

using namespace eProsima;

EnumMember::EnumMember(std::string &name, uint32_t ordinal) : Member(name),
    m_ordinal(ordinal)
{
}

bool EnumMember::deserialize(CDR &cdr)
{
    return true;
}

uint32_t EnumMember::getOrdinal() const
{
    return m_ordinal;
}

EnumTypeCode::EnumTypeCode() : MemberedTypeCode(TypeCode::KIND_ENUM)
{
}

bool EnumTypeCode::deserialize(CDR &cdr)
{
    bool returnedValue = true;
    uint16_t size = 0;

    // Deserialize size.
    returnedValue &= cdr >> size;
    returnedValue &= deserializeName(cdr);
    returnedValue &= deserializeMembers(cdr);

    return returnedValue;
}

Member* EnumTypeCode::deserializeMemberInfo(std::string name, CDR &cdr)
{
    Member *returnedValue = NULL;
    uint32_t ordinal;

    if(cdr >> ordinal)
        returnedValue = new EnumMember(name, ordinal);

    return returnedValue;
}

const EnumMember* EnumTypeCode::getMemberWithOrdinal(uint32_t ordinal) const
{
    const EnumMember *returnedValue = NULL, *member = NULL;
    std::vector<Member*>::const_iterator it = m_members.begin();

    while(it != m_members.end())
    {
        member = dynamic_cast<EnumMember*>(*it);

        if(member != NULL)
        {
            if(member->getOrdinal() == ordinal)
            {
                returnedValue = member;
                break;
            }
        }

        ++it;
    }

    return returnedValue;
}

bool EnumTypeCode::print(IDLPrinter &printer, bool write) const
{
    bool returnedValue = true;

	if(write)
		printer << getName();

    if(!printer.isTypePrinterAndUp("enum " + getName()))
    {
		IDLPrinter tPrinter(printer);
        tPrinter << "enum " << getName() << " {" << std::endl;

        for(uint32_t count = 0; count < getMemberCount(); ++count)
        {
            const EnumMember *member = dynamic_cast<const EnumMember*>(getMember(count));
            tPrinter << "   " << member->getName() << " = " << member->getOrdinal();

            if(count != (getMemberCount() - 1))
                tPrinter << "," << std::endl;
        }

        tPrinter << std::endl << "};" << std::endl << std::endl;
		printer.addPrinter("enum " + getName(), std::move(tPrinter));
    }

    return returnedValue;
}

bool eProsima::operator<<(IDLPrinter &printer, const EnumTypeCode *typeCode)
{
    bool returnedValue = false;

    if(typeCode != NULL)
        returnedValue = printer << *typeCode;

    return returnedValue;
}