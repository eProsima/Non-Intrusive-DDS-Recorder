
/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from Enums.idl using "rtiddsgen".
  The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
  For more information, type 'rtiddsgen -help' at a command shell
  or consult the RTI Data Distribution Service manual.
*/


#ifndef NDDS_STANDALONE_TYPE
    #ifdef __cplusplus
        #ifndef ndds_cpp_h
            #include "ndds/ndds_cpp.h"
        #endif
        #ifndef dds_c_log_impl_h              
            #include "dds_c/dds_c_log_impl.h"                                
        #endif        
    #else
        #ifndef ndds_c_h
            #include "ndds/ndds_c.h"
        #endif
    #endif
    
    #ifndef cdr_type_h
        #include "cdr/cdr_type.h"
    #endif    

    #ifndef osapi_heap_h
        #include "osapi/osapi_heap.h" 
    #endif
#else
    #include "ndds_standalone_type.h"
#endif



#ifndef Enums_h
#include "Enums.h"
#endif

/* ========================================================================= */
const char *EnumeradoTYPENAME = "Enumerado";

DDS_TypeCode* Enumerado_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member Enumerado_g_tc_members[4] =
    {
        {
            (char *)"VALOR1",/* Member name */
            {
                0,/* Ignored */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /* Ignored */
                NULL /* Ignored */
            },
            VALOR1, /* Enumerator ordinal */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            DDS_BOOLEAN_FALSE, /* Ignored */
            DDS_PRIVATE_MEMBER,/* Ignored */
            0,/* Ignored */
            NULL/* Ignored */
        },
        {
            (char *)"VALOR2",/* Member name */
            {
                0,/* Ignored */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /* Ignored */
                NULL /* Ignored */
            },
            VALOR2, /* Enumerator ordinal */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            DDS_BOOLEAN_FALSE, /* Ignored */
            DDS_PRIVATE_MEMBER,/* Ignored */
            0,/* Ignored */
            NULL/* Ignored */
        },
        {
            (char *)"VALOR3",/* Member name */
            {
                0,/* Ignored */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /* Ignored */
                NULL /* Ignored */
            },
            VALOR3, /* Enumerator ordinal */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            DDS_BOOLEAN_FALSE, /* Ignored */
            DDS_PRIVATE_MEMBER,/* Ignored */
            0,/* Ignored */
            NULL/* Ignored */
        },
        {
            (char *)"VALORZ",/* Member name */
            {
                0,/* Ignored */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /* Ignored */
                NULL /* Ignored */
            },
            VALORZ, /* Enumerator ordinal */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            DDS_BOOLEAN_FALSE, /* Ignored */
            DDS_PRIVATE_MEMBER,/* Ignored */
            0,/* Ignored */
            NULL/* Ignored */
        }
    };

    static DDS_TypeCode Enumerado_g_tc = 
    {{
        DDS_TK_ENUM, /* Kind */
        DDS_BOOLEAN_FALSE, /* Ignored */
        -1, /* Ignored */
        (char *)"Enumerado", /* Name */
        NULL, /* Ignored */
        0, /* Ignored */
        0, /* Ignored */
        NULL, /* Ignored */
        4, /* Number of enumerators */
        Enumerado_g_tc_members, /* Enumerators */
        DDS_VM_NONE /* Ignored */
}    };

    if (is_initialized) {
        return &Enumerado_g_tc;
    }

    is_initialized = RTI_TRUE;
    return &Enumerado_g_tc;
}
 

RTIBool Enumerado_initialize(
    Enumerado* sample)
{
    /* The following method initializes the enum value to zero. However,
     * some enumerations may not have a member with the value zero. In such
     * cases, it may be desirable to modify the generated code to use a valid
     * enumeration member instead.
     */
    return RTICdrType_initEnum((RTICdrEnum*) sample);
}
        
RTIBool Enumerado_initialize_ex(
    Enumerado* sample,RTIBool allocatePointers)
{
    /* The following method initializes the enum value to zero. However,
     * some enumerations may not have a member with the value zero. In such
     * cases, it may be desirable to modify the generated code to use a valid
     * enumeration member instead.
     */
    return RTICdrType_initEnum((RTICdrEnum*) sample);
}

void Enumerado_finalize(
    Enumerado* sample)
{
    /* empty */
}
        
void Enumerado_finalize_ex(
    Enumerado* sample,RTIBool deletePointers)
{
    /* empty */
}

RTIBool Enumerado_copy(
    Enumerado* dst,
    const Enumerado* src)
{
    return RTICdrType_copyEnum((RTICdrEnum *)dst, (RTICdrEnum *)src);
}


/**
 * <<IMPLEMENTATION>>
 *
 * Defines:  TSeq, T
 *
 * Configure and implement 'Enumerado' sequence class.
 */
#define T Enumerado
#define TSeq EnumeradoSeq
#define T_initialize_ex Enumerado_initialize_ex
#define T_finalize_ex   Enumerado_finalize_ex
#define T_copy       Enumerado_copy

#ifndef NDDS_STANDALONE_TYPE
#include "dds_c/generic/dds_c_sequence_TSeq.gen"
#ifdef __cplusplus
#include "dds_cpp/generic/dds_cpp_sequence_TSeq.gen"
#endif
#else
#include "dds_c_sequence_TSeq.gen"
#ifdef __cplusplus
#include "dds_cpp_sequence_TSeq.gen"
#endif
#endif

#undef T_copy
#undef T_finalize_ex
#undef T_initialize_ex
#undef TSeq
#undef T
/* ========================================================================= */
const char *EnumsTYPENAME = "Enums";

DDS_TypeCode* Enums_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode Enums_g_tc_aren_array = DDS_INITIALIZE_ARRAY_TYPECODE(1,10,NULL,NULL);
    static DDS_TypeCode Enums_g_tc_seen_sequence = DDS_INITIALIZE_SEQUENCE_TYPECODE(100,NULL);

    static DDS_TypeCode_Member Enums_g_tc_members[4]=
    {
        {
            (char *)"count",/* Member name */
            {
                0,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            DDS_BOOLEAN_FALSE, /* Is a key? */
            DDS_PRIVATE_MEMBER,/* Ignored */
            0,/* Ignored */
            NULL/* Ignored */
        },
        {
            (char *)"en",/* Member name */
            {
                0,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            DDS_BOOLEAN_FALSE, /* Is a key? */
            DDS_PRIVATE_MEMBER,/* Ignored */
            0,/* Ignored */
            NULL/* Ignored */
        },
        {
            (char *)"aren",/* Member name */
            {
                0,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            DDS_BOOLEAN_FALSE, /* Is a key? */
            DDS_PRIVATE_MEMBER,/* Ignored */
            0,/* Ignored */
            NULL/* Ignored */
        },
        {
            (char *)"seen",/* Member name */
            {
                0,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            DDS_BOOLEAN_FALSE, /* Is a key? */
            DDS_PRIVATE_MEMBER,/* Ignored */
            0,/* Ignored */
            NULL/* Ignored */
        }
    };

    static DDS_TypeCode Enums_g_tc =
    {{
        DDS_TK_STRUCT,/* Kind */
        DDS_BOOLEAN_FALSE, /* Ignored */
        -1,/* Ignored */
        (char *)"Enums", /* Name */
        NULL, /* Ignored */
        0, /* Ignored */
        0, /* Ignored */
        NULL, /* Ignored */
        4, /* Number of members */
        Enums_g_tc_members, /* Members */
        DDS_VM_NONE /* Ignored */
    }}; /* Type code for Enums*/

    if (is_initialized) {
        return &Enums_g_tc;
    }

    Enums_g_tc_aren_array._data._typeCode = (RTICdrTypeCode *)Enumerado_get_typecode();
    Enums_g_tc_seen_sequence._data._typeCode = (RTICdrTypeCode *)Enumerado_get_typecode();

    Enums_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
    Enums_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)Enumerado_get_typecode();
    Enums_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)&Enums_g_tc_aren_array;
    Enums_g_tc_members[3]._representation._typeCode = (RTICdrTypeCode *)&Enums_g_tc_seen_sequence;

    is_initialized = RTI_TRUE;

    return &Enums_g_tc;
}


RTIBool Enums_initialize(
    Enums* sample) {
    return Enums_initialize_ex(sample,RTI_TRUE);
}
        
RTIBool Enums_initialize_ex(
    Enums* sample,RTIBool allocatePointers)
{

    void* buffer;                
    buffer = NULL;        

    if (!RTICdrType_initLong(&sample->count)) {
        return RTI_FALSE;
    }                
            
    if (!Enumerado_initialize_ex(&sample->en,allocatePointers)) {
        return RTI_FALSE;
    }
            
    
    {
        int i = 0;
        Enumerado* elem =
            (Enumerado*) &sample->aren[0];

        for (i = 0; i < (10); ++i, ++elem) {
            if (!Enumerado_initialize_ex(elem,allocatePointers)) {
                return RTI_FALSE;
            }
        }
    }
            
    EnumeradoSeq_initialize(&sample->seen);
    EnumeradoSeq_set_element_pointers_allocation(&sample->seen,allocatePointers);
    if (!EnumeradoSeq_set_maximum(&sample->seen,
                                       (100))) {
        return RTI_FALSE;
    }
            

    return RTI_TRUE;
}

void Enums_finalize(
    Enums* sample)
{
    Enums_finalize_ex(sample,RTI_TRUE);
}
        
void Enums_finalize_ex(
    Enums* sample,RTIBool deletePointers)
{        

    Enumerado_finalize_ex(&sample->en,deletePointers);
            
    
    {
        int i = 0;
        Enumerado* elem =
            (Enumerado*) &sample->aren[0];

        for (i = 0; i < (10); ++i, ++elem) {
            Enumerado_finalize_ex(elem,deletePointers);
        }
    }
            
    EnumeradoSeq_finalize(&sample->seen);
            
}

RTIBool Enums_copy(
    Enums* dst,
    const Enums* src)
{        

    if (!RTICdrType_copyLong(
        &dst->count, &src->count)) {
        return RTI_FALSE;
    }
            
    if (!Enumerado_copy(
        &dst->en, &src->en)) {
        return RTI_FALSE;
    }
            
    
    {
        int i = 0;
        Enumerado* elemOut = (Enumerado*) &dst->aren[0];
        const Enumerado* elemIn = (const Enumerado*) &src->aren[0];

        for (i = 0; i < (10);
             ++i, ++elemOut, ++elemIn) {
            if (!Enumerado_copy(elemOut,(const Enumerado*)elemIn)) {
                return RTI_FALSE;
            }
        }
    }
            
    if (!EnumeradoSeq_copy_no_alloc(&dst->seen,
                                          &src->seen)) {
        return RTI_FALSE;
    }
            

    return RTI_TRUE;
}


/**
 * <<IMPLEMENTATION>>
 *
 * Defines:  TSeq, T
 *
 * Configure and implement 'Enums' sequence class.
 */
#define T Enums
#define TSeq EnumsSeq
#define T_initialize_ex Enums_initialize_ex
#define T_finalize_ex   Enums_finalize_ex
#define T_copy       Enums_copy

#ifndef NDDS_STANDALONE_TYPE
#include "dds_c/generic/dds_c_sequence_TSeq.gen"
#ifdef __cplusplus
#include "dds_cpp/generic/dds_cpp_sequence_TSeq.gen"
#endif
#else
#include "dds_c_sequence_TSeq.gen"
#ifdef __cplusplus
#include "dds_cpp_sequence_TSeq.gen"
#endif
#endif

#undef T_copy
#undef T_finalize_ex
#undef T_initialize_ex
#undef TSeq
#undef T

