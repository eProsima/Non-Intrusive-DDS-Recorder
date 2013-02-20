#include "cdr/TypeCode.h"
#include "cdr/StructTypeCode.h"
#include "cdr/ArrayTypeCode.h"
#include "cdr/EnumTypeCode.h"
#include "cdr/StringTypeCode.h"
#include "cdr/PrimitiveTypeCode.h"
#include "Cdr.h"

#include <stdio.h>

using namespace eProsima;

TypeCode::TypeCode(uint32_t kind) : m_kind(kind)
{
}

TypeCode* TypeCode::deserializeTypeCode(char *cdrTypeCode, uint32_t cdrTypeCodeLength)
{
    TypeCode *returnedValue = NULL;

    if(cdrTypeCode != NULL)
    {
        // Create the CDR buffer.
        CDRBuffer cdrBuffer(cdrTypeCode, cdrTypeCodeLength);
        CDR cdr(cdrBuffer, CDR::DDS_CDR);
        uint32_t kind = 0;

        // TODO Check that the DDS middleware is RTI.
        if((cdr >> kind) && (kind & 0x80000000))
        {
            // Remove the extra bit.
            kind &= 0x7FFFFFFF;

            switch(kind)
            {
            case KIND_STRUCT:
                StructTypeCode *structTC = new StructTypeCode();
                if(structTC->deserialize(cdr))
                    returnedValue = static_cast<TypeCode*>(structTC);
                else
                    delete structTC;
                break;
            }
        }
    }
    else
    {
        // TODO Return error.
    }

    return returnedValue;
}

TypeCode* TypeCode::deserializeTypeCode(CDR &cdr)
{
    TypeCode *returnedValue = NULL;
    uint32_t kind = 0;

    // TODO Check that the DDS middleware is RTI.
    if((cdr >> kind) && (kind & 0x80000000))
    {
        // Remove the extra bit.
        kind &= 0x7FFFFFFF;

        if(kind == KIND_STRUCT)
        {
            StructTypeCode *structTC = new StructTypeCode();
            if(structTC->deserialize(cdr))
                returnedValue = static_cast<TypeCode*>(structTC);
            else
                delete structTC;
        }
        if(kind == KIND_ARRAY)
        {
            ArrayTypeCode *arrayTC = new ArrayTypeCode();
            if(arrayTC->deserialize(cdr))
                returnedValue = static_cast<TypeCode*>(arrayTC);
            else
                delete arrayTC;
        }
        else if(kind == KIND_ENUM)
        {
            EnumTypeCode *enumTC = new EnumTypeCode();
            if(enumTC->deserialize(cdr))
                returnedValue = static_cast<TypeCode*>(enumTC);
            else
                delete enumTC;
        }
        else if(kind == KIND_STRING)
        {
            StringTypeCode *stringTC = new StringTypeCode();
            if(stringTC->deserialize(cdr))
                returnedValue = static_cast<TypeCode*>(stringTC);
            else
                delete stringTC;
        }
        else if(kindIsPrimitive(kind))
        {
            PrimitiveTypeCode *primitiveTC = new PrimitiveTypeCode(kind);
            if(primitiveTC->deserialize(cdr))
                returnedValue = static_cast<TypeCode*>(primitiveTC);
            else
                delete primitiveTC;
        }
    }

    return returnedValue;
}

uint32_t TypeCode::getKind() const
{
    return m_kind;
}

bool eProsima::operator<<(IDLPrinter &printer, const TypeCode *typeCode)
{
    bool returnedValue = false;

    if(typeCode != NULL)
        returnedValue = printer << *typeCode;

    return returnedValue;
}