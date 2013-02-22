#include "cdr/UnionTypeCode.h"
#include "util/IDLPrinter.h"
#include "Cdr.h"

using namespace eProsima;

UnionMember::UnionMember(std::string &name, uint16_t bits, uint8_t flags) : Member(name),
    m_bits(bits), m_flags(flags)
{
}

UnionTypeCode::UnionTypeCode() : MemberedTypeCode(TypeCode::KIND_UNION)
{
}

bool UnionTypeCode::deserialize(CDR &cdr)
{
    bool returnedValue = true;
    uint16_t size = 0;

    // Deserialize size.
    returnedValue &= cdr >> size;
    returnedValue &= deserializeName(cdr);
    returnedValue &= deserializeMembers(cdr);

    return returnedValue;
}