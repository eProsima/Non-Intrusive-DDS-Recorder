#include "cdr/UnionTypeCode.h"
#include "cdr/TypeCodeCopy.h"
#include "util/IDLPrinter.h"
#include "fastcdr/Cdr.h"
#include "fastcdr/exceptions/Exception.h"


using namespace eprosima;

UnionMember::UnionMember(std::string &name, uint32_t labelCount, std::vector<int32_t> labels) : Member(name),
		m_labelCount(labelCount)
{
	std::swap(m_labels, labels);
}

UnionMember::UnionMember():m_labelCount(0)
{

}

UnionMember::UnionMember(const UnionMember& copy)
{
	std::string name = copy.getName();
	this->setName(name);
	TypeCode* TC = TypeCodeCopy::copy(copy.getTypeCode());
	this->setTypeCode(TC);
	m_labelCount = copy.getLabelCount();
	m_labels = copy.getLabels();
}

uint32_t UnionMember::getLabelCount() const
{
	return m_labelCount;
}

int32_t UnionMember::getLabel(uint32_t pos) const
{
	return m_labels[pos];
}

void UnionMember::setLabels(std::vector<int32_t>& labels)
{
	m_labels = labels;
	m_labelCount = m_labels.size();
}

std::vector<int32_t> UnionMember::getLabels() const
{
	return m_labels;
}


UnionTypeCode::UnionTypeCode() : MemberedTypeCode(TypeCode::KIND_UNION), m_defaultIndex(-1),
		m_discriminatorTypeCode(NULL)
{
}

UnionTypeCode::UnionTypeCode(const UnionTypeCode& copy): MemberedTypeCode(TypeCode::KIND_UNION)
{
	for(std::vector<Member*>::const_iterator it = copy.m_members.begin();it!= copy.m_members.end();++it)
	{
		UnionMember* sM = (UnionMember*)(*it);
		sM = new UnionMember(*sM);
		m_members.push_back(sM);
	}
	m_name = copy.m_name;
	m_memberCount = copy.m_memberCount;
	this->m_defaultIndex = copy.m_defaultIndex;
	this->m_discriminatorTypeCode = TypeCodeCopy::copy(copy.m_discriminatorTypeCode);
}

UnionTypeCode::~UnionTypeCode()
{
	if(m_discriminatorTypeCode != NULL)
	{
		delete m_discriminatorTypeCode;
	}
}

int32_t UnionTypeCode::getDefaultIndex() const
{
	return m_defaultIndex;
}

void UnionTypeCode::setDefaultIndex(int32_t def)
{
	m_defaultIndex = def;
}

bool UnionTypeCode::deserialize(Cdr &cdr)
{
	bool returnedValue = true;
	uint16_t size = 0;

	try
	{
		// Deserialize size.
		cdr >> size;

		if((returnedValue &= deserializeName(cdr)))
		{
			cdr >> m_defaultIndex;
			returnedValue &= (m_discriminatorTypeCode = TypeCode::deserializeTypeCode(cdr)) != NULL;
			returnedValue &= deserializeMembers(cdr);
		}
	}
	catch(exception::Exception &ex)
	{
		returnedValue = false;
	}

	return returnedValue;
}

Member* UnionTypeCode::deserializeMemberInfo(std::string name, Cdr &cdr)
{
	Member *returnedValue = NULL;
	uint8_t mPointer = 0;
	uint32_t labelCount = 0;
	std::vector<int32_t> labels;

	try
	{
		cdr >> mPointer;
		cdr >> labelCount;

		int32_t label;

		for(uint32_t count = 0; count < labelCount; ++count)
		{
			cdr >> label;
			labels.push_back(label);
		}

		returnedValue = new UnionMember(name, labelCount, labels);
	}
	catch(exception::Exception &ex)
	{
	}

	return returnedValue;
}

bool UnionTypeCode::print(IDLPrinter &printer, bool write) const
{
	bool returnedValue = true;

	if(write)
		printer.getOut() << getName();

	if(!printer.isTypePrinterAndUp("union " + getName()))
	{
		IDLPrinter *tPrinter = new IDLPrinter(printer);
		tPrinter->getOut() << "union " << getName() << " switch (";
		*tPrinter << this->m_discriminatorTypeCode;
		tPrinter->getOut() << ") {" << std::endl;

		for(uint32_t count = 0; count < getMemberCount(); ++count)
		{
			const UnionMember *member = dynamic_cast<const UnionMember*>(getMember(count));

			if(member != NULL)
			{
				// Print labels.
				for(uint32_t lCount = 0; lCount < member->getLabelCount(); ++lCount)
				{
					if(count == (uint32_t)m_defaultIndex)
						tPrinter->getOut() << "   default:" << std::endl;
					else
						tPrinter->getOut() << "   case " << member->getLabel(lCount) << ":" << std::endl;

				}
				tPrinter->getOut() << "      ";
				returnedValue &= *tPrinter << member->getTypeCode();
				tPrinter->getOut() << " " << member->getName() << ";" << std::endl;
			}
			else
				returnedValue = false;
		}

		tPrinter->getOut() << "};" << std::endl << std::endl;
		printer.addPrinter("union " + getName(), tPrinter);
	}
	else
	{
		for(uint32_t count = 0; count < getMemberCount(); ++count)
		{
			const UnionMember *member = dynamic_cast<const UnionMember*>(getMember(count));

			if(member != NULL)
			{
				returnedValue &= member->getTypeCode()->print(printer, false);
			}
			else
				returnedValue = false;
		}
	}

	return returnedValue;
}

bool UnionTypeCode::addMember(UnionMember* member)
{
	if(isMemberWithName(member->getName()))
		return false;
	this->addMemberPtr((Member*)member);
	return true;
}

void UnionTypeCode::setDiscriminatorTypeCode(TypeCode* TC)
{
	m_discriminatorTypeCode = TC;
}


bool eprosima::operator<<(IDLPrinter &printer, const UnionTypeCode *typeCode)
{
	bool returnedValue = false;

	if(typeCode != NULL)
		returnedValue = printer << *typeCode;

	return returnedValue;
}
