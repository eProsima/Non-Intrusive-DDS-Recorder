#ifndef _CDR_TYPECODE_H_
#define _CDR_TYPECODE_H_

#include <stdint.h>

namespace eProsima
{
    class TypeCode
    {
    public:
        TypeCode(char *cdrTypeCode, uint32_t cdrTypeCodeLength);
    };
};

#endif // _CDR_TYPECODE_H_
