#include "cdr/StructTypeCode.h"
#include "util/IDLPrinter.h"
#include "Cdr.h"

using namespace eProsima;

StructMember::StructMember(std::string &name, uint16_t bits, uint8_t flags) : Member(name),
    m_bits(bits), m_flags(flags)
{
}

StructTypeCode::StructTypeCode() : MemberedTypeCode(TypeCode::KIND_STRUCT)
{
}

bool StructTypeCode::deserialize(CDR &cdr)
{
    bool returnedValue = true;
    uint16_t size = 0;

    // Deserialize size.
    returnedValue &= cdr >> size;
    returnedValue &= deserializeName(cdr);
    returnedValue &= deserializeMembers(cdr);

    return returnedValue;
}

Member* StructTypeCode::deserializeMemberInfo(std::string name, CDR &cdr)
{
    Member *returnedValue = NULL;
    uint8_t mPointer = 0;
    uint16_t bits = 0;
    uint8_t flags = 0;

    if((cdr >> mPointer) &&(cdr >> bits) && cdr >> flags)
        returnedValue = new StructMember(name, bits, flags);

    return returnedValue;
}

bool StructTypeCode::print(IDLPrinter &printer, bool write) const
{
    bool returnedValue = true;

	if(write)
		printer << getName();

    if(!printer.isTypePrinterAndUp("struct " + getName()))
    {
			IDLPrinter tPrinter(printer);
			tPrinter << "struct " << getName() << " {" << std::endl;
        
			for(uint32_t count = 0; count < getMemberCount(); ++count)
			{
				const StructMember *member = dynamic_cast<const StructMember*>(getMember(count));

				if(member != NULL)
				{
					tPrinter << "   ";
					tPrinter << member->getTypeCode();
					tPrinter << " " << member->getName() << ";" << std::endl;
				}
				else
					returnedValue = false;
			}

			tPrinter << "};" << std::endl << std::endl;
			printer.addPrinter("struct " + getName(), std::move(tPrinter));
    }
	else
	{
		for(uint32_t count = 0; count < getMemberCount(); ++count)
		{
			const StructMember *member = dynamic_cast<const StructMember*>(getMember(count));

			if(member != NULL)
			{
				member->getTypeCode()->print(printer, false);
			}
			else
				returnedValue = false;
		}
	}

    return returnedValue;
}

bool eProsima::operator<<(IDLPrinter &printer, const StructTypeCode *typeCode)
{
    bool returnedValue = false;

    if(typeCode != NULL)
        returnedValue = printer << *typeCode;

    return returnedValue;
}