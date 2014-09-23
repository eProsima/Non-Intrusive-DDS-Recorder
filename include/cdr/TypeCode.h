#ifndef _CDR_TYPECODE_H_
#define _CDR_TYPECODE_H_

#include <stdint.h>

namespace eProsima
{

    class Cdr;
    class IDLPrinter;

    class TypeCode
    {
    public:

        static const uint32_t KIND_NULL = 0x00000000;
        static const uint32_t KIND_SHORT = 0x00000001;
        static const uint32_t KIND_LONG = 0x00000002;
        static const uint32_t KIND_USHORT = 0x00000003;
        static const uint32_t KIND_ULONG = 0x00000004;
        static const uint32_t KIND_FLOAT = 0x00000005;
        static const uint32_t KIND_DOUBLE = 0x00000006;
        static const uint32_t KIND_BOOLEAN = 0x00000007;
        static const uint32_t KIND_CHAR = 0x00000008;
        static const uint32_t KIND_OCTET = 0x00000009;
        static const uint32_t KIND_STRUCT = 0x0000000a;
        static const uint32_t KIND_UNION = 0x0000000b;
        static const uint32_t KIND_ENUM = 0x0000000c;
        static const uint32_t KIND_STRING = 0x0000000d;
        static const uint32_t KIND_SEQUENCE = 0x0000000e;
        static const uint32_t KIND_ARRAY = 0x0000000f;
        static const uint32_t KIND_ALIAS = 0x00000010;
        static const uint32_t KIND_LONGLONG = 0x00000011;
        static const uint32_t KIND_ULONGLONG = 0x00000012;
        static const uint32_t KIND_LONGDOUBLE = 0x00000013;
        static const uint32_t KIND_WCHAR = 0x00000014;
        static const uint32_t KIND_WSTRING = 0x00000015;
        static const uint32_t KIND_VALUE = 0x00000016;
        static const uint32_t KIND_SPARSE = 0x00000017;
    
        /*!
         * @brief Default destructor.
         */
        virtual ~TypeCode(){}

        /*!
         * @brief This function deserialize a TypeCode using a buffer that contains the serialized typecode.
         *      This function is used to deserialize the main typecode.
         *
         * @param cdrTypeCode Pointer to the buffer that contains the serialized typecode. Cannot be NULL.
         * @param cdrTypeCodeLength Length of the CDR stream.
         * @return Pointer to the new TypeCode object. If there was an error, then a NULL pointer is returned.
         */
        static TypeCode*  deserializeTypeCode(char *cdrTypeCode, uint32_t cdrTypeCodeLength);

        /*!
         * @brief This function deserialize a TypeCode using a CDR stream that contains the serialized typecode.
         *      This function is used to deserialize a member's typecode.
         *
         * @param cdr CDR stream that contains the serialized typecode.
         * @return Pointer to the new TypeCode object. If there was an error, then a NULL pointer is returned.
         */
        static TypeCode*  deserializeTypeCode(Cdr &cdr);

        /*!
         * @brief This function returns the kind of the type.
         */
        uint32_t getKind() const;

        /*!
         * @brief This function check if the kind of a type is primitive.
         */
        inline static bool kindIsPrimitive(uint32_t kind)
        {
            return !((kind == KIND_STRUCT) ||
            (kind == KIND_ARRAY) ||
            (kind == KIND_SEQUENCE) ||
            (kind == KIND_UNION) ||
            (kind == KIND_ALIAS) ||
            (kind == KIND_VALUE) ||
            (kind == KIND_SPARSE) ||
            (kind == KIND_ENUM));

        }

		virtual bool print(IDLPrinter &printer, bool write) const = 0;

		friend inline bool operator<<(IDLPrinter &printer, const TypeCode &typeCode) {return typeCode.print(printer, true);}

        friend bool operator<<(IDLPrinter &printer, const TypeCode *typeCode);

    protected:
        /*!
         * @brief Default constructor.
         *
         * @param kind The kind of the type.
         */
        TypeCode(uint32_t kind);

    private:

        //! @brief Kind of the type.
        uint32_t m_kind;
    };
};

#endif // _CDR_TYPECODE_H_
