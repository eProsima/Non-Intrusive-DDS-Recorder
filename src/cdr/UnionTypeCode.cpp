#include "cdr/UnionTypeCode.h"
#include "util/IDLPrinter.h"
#include "fastcdr/Cdr.h"
#include "fastcdr/exceptions/Exception.h"

using namespace eProsima;

UnionMember::UnionMember(std::string &name, uint32_t labelCount, std::vector<int32_t> labels) : Member(name),
    m_labelCount(labelCount)
{
    std::swap(m_labels, labels);
}

uint32_t UnionMember::getLabelCount() const
{
    return m_labelCount;
}

int32_t UnionMember::getLabel(uint32_t pos) const
{
    return m_labels[pos];
}

UnionTypeCode::UnionTypeCode() : MemberedTypeCode(TypeCode::KIND_UNION), m_defaultIndex(0),
    m_discriminatorTypeCode(NULL)
{
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
			tPrinter->getOut() << "union " << getName() << " {" << std::endl;
        
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

bool eProsima::operator<<(IDLPrinter &printer, const UnionTypeCode *typeCode)
{
    bool returnedValue = false;

    if(typeCode != NULL)
        returnedValue = printer << *typeCode;

    return returnedValue;
}
