#include "cdr/EnumTypeCode.h"
#include "util/IDLPrinter.h"
#include "fastcdr/Cdr.h"

#include "cdr/TypeCodeCopy.h"
using namespace eprosima;
#include <iostream>
using namespace eprosima::fastcdr;


EnumMember::EnumMember(std::string &name, uint32_t ordinal) : Member(name),
		m_ordinal(ordinal)
{
}

EnumMember::EnumMember(const EnumMember& copy)
{
	std::string name = copy.getName();
	this->setName(name);
	m_ordinal = copy.m_ordinal;
}

bool EnumMember::deserialize(Cdr &cdr)
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

EnumTypeCode::EnumTypeCode(const EnumTypeCode& copy): MemberedTypeCode(TypeCode::KIND_ENUM)
{
	std::cout << "Enum TYpe Code copy"<<std::endl;
	for(std::vector<Member*>::const_iterator it = copy.m_members.begin();it!= copy.m_members.end();++it)
	{
		EnumMember* sM = (EnumMember*)(*it);
		sM = new EnumMember(*sM);
		m_members.push_back(sM);
	}
	m_name = copy.m_name;
	m_memberCount = copy.m_memberCount;

}

bool EnumTypeCode::deserialize(Cdr &cdr)
{
	bool returnedValue = true;
	uint16_t size = 0;

	// Deserialize size.
	try
	{
		cdr >> size;
		returnedValue &= deserializeName(cdr);
		returnedValue &= deserializeMembers(cdr);
	}
	catch(exception::Exception &ex)
	{
		returnedValue = false;
	}

	return returnedValue;
}

Member* EnumTypeCode::deserializeMemberInfo(std::string name, Cdr &cdr)
{
	Member *returnedValue = NULL;
	uint32_t ordinal;

	try
	{
		cdr >> ordinal;
		returnedValue = new EnumMember(name, ordinal);
	}
	catch(exception::Exception &ex)
	{
	}

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
		printer.getOut() << getName();

	if(!printer.isTypePrinterAndUp("enum " + getName()))
	{
		IDLPrinter *tPrinter = new IDLPrinter(printer);
		tPrinter->getOut() << "enum " << getName() << " {" << std::endl;

		for(uint32_t count = 0; count < getMemberCount(); ++count)
		{
			const EnumMember *member = dynamic_cast<const EnumMember*>(getMember(count));
			tPrinter->getOut() << "   " << member->getName() << " = " << member->getOrdinal();

			if(count != (getMemberCount() - 1))
				tPrinter->getOut() << "," << std::endl;
		}

		tPrinter->getOut() << std::endl << "};" << std::endl << std::endl;
		printer.addPrinter("enum " + getName(), tPrinter);
	}

	return returnedValue;
}

bool EnumTypeCode::addMember(EnumMember* mem)
{
	if(isMemberWithName(mem->getName()))
		return false;
	this->addMemberPtr((Member*)mem);
	return true;
}

bool eprosima::operator<<(IDLPrinter &printer, const EnumTypeCode *typeCode)
{
	bool returnedValue = false;

	if(typeCode != NULL)
		returnedValue = printer << *typeCode;

	return returnedValue;
}
