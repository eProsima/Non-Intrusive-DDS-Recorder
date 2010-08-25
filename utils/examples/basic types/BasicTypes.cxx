
/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from BasicTypes.idl using "rtiddsgen".
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



#ifndef BasicTypes_h
#include "BasicTypes.h"
#endif

/* ========================================================================= */
const char *BasicTypesTYPENAME = "BasicTypes";

DDS_TypeCode* BasicTypes_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode BasicTypes_g_tc_st_string = DDS_INITIALIZE_STRING_TYPECODE(255);

    static DDS_TypeCode_Member BasicTypes_g_tc_members[11]=
    {
        {
            (char *)"oc",/* Member name */
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
            (char *)"ch",/* Member name */
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
            (char *)"sh",/* Member name */
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
            (char *)"ush",/* Member name */
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
            (char *)"lo",/* Member name */
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
            (char *)"ulo",/* Member name */
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
            (char *)"lolo",/* Member name */
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
            (char *)"ulolo",/* Member name */
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
            (char *)"st",/* Member name */
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
            (char *)"fl",/* Member name */
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
            (char *)"dl",/* Member name */
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

    static DDS_TypeCode BasicTypes_g_tc =
    {{
        DDS_TK_STRUCT,/* Kind */
        DDS_BOOLEAN_FALSE, /* Ignored */
        -1,/* Ignored */
        (char *)"BasicTypes", /* Name */
        NULL, /* Ignored */
        0, /* Ignored */
        0, /* Ignored */
        NULL, /* Ignored */
        11, /* Number of members */
        BasicTypes_g_tc_members, /* Members */
        DDS_VM_NONE /* Ignored */
    }}; /* Type code for BasicTypes*/

    if (is_initialized) {
        return &BasicTypes_g_tc;
    }


    BasicTypes_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_octet;
    BasicTypes_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_char;
    BasicTypes_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_short;
    BasicTypes_g_tc_members[3]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_ushort;
    BasicTypes_g_tc_members[4]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
    BasicTypes_g_tc_members[5]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_ulong;
    BasicTypes_g_tc_members[6]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_longlong;
    BasicTypes_g_tc_members[7]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_ulonglong;
    BasicTypes_g_tc_members[8]._representation._typeCode = (RTICdrTypeCode *)&BasicTypes_g_tc_st_string;
    BasicTypes_g_tc_members[9]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_float;
    BasicTypes_g_tc_members[10]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_double;

    is_initialized = RTI_TRUE;

    return &BasicTypes_g_tc;
}


RTIBool BasicTypes_initialize(
    BasicTypes* sample) {
    return BasicTypes_initialize_ex(sample,RTI_TRUE);
}
        
RTIBool BasicTypes_initialize_ex(
    BasicTypes* sample,RTIBool allocatePointers)
{

    if (!RTICdrType_initOctet(&sample->oc)) {
        return RTI_FALSE;
    }                
            
    if (!RTICdrType_initChar(&sample->ch)) {
        return RTI_FALSE;
    }                
            
    if (!RTICdrType_initShort(&sample->sh)) {
        return RTI_FALSE;
    }                
            
    if (!RTICdrType_initUnsignedShort(&sample->ush)) {
        return RTI_FALSE;
    }                
            
    if (!RTICdrType_initLong(&sample->lo)) {
        return RTI_FALSE;
    }                
            
    if (!RTICdrType_initUnsignedLong(&sample->ulo)) {
        return RTI_FALSE;
    }                
            
    if (!RTICdrType_initLongLong(&sample->lolo)) {
        return RTI_FALSE;
    }                
            
    if (!RTICdrType_initUnsignedLongLong(&sample->ulolo)) {
        return RTI_FALSE;
    }                
            
    sample->st = DDS_String_alloc((255));
    if (sample->st == NULL) {
        return RTI_FALSE;
    }
            
    if (!RTICdrType_initFloat(&sample->fl)) {
        return RTI_FALSE;
    }                
            
    if (!RTICdrType_initDouble(&sample->dl)) {
        return RTI_FALSE;
    }                
            

    return RTI_TRUE;
}

void BasicTypes_finalize(
    BasicTypes* sample)
{
    BasicTypes_finalize_ex(sample,RTI_TRUE);
}
        
void BasicTypes_finalize_ex(
    BasicTypes* sample,RTIBool deletePointers)
{        

    DDS_String_free(sample->st);                
            
}

RTIBool BasicTypes_copy(
    BasicTypes* dst,
    const BasicTypes* src)
{        

    if (!RTICdrType_copyOctet(
        &dst->oc, &src->oc)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrType_copyChar(
        &dst->ch, &src->ch)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrType_copyShort(
        &dst->sh, &src->sh)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrType_copyUnsignedShort(
        &dst->ush, &src->ush)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrType_copyLong(
        &dst->lo, &src->lo)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrType_copyUnsignedLong(
        &dst->ulo, &src->ulo)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrType_copyLongLong(
        &dst->lolo, &src->lolo)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrType_copyUnsignedLongLong(
        &dst->ulolo, &src->ulolo)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrType_copyString(
        dst->st, src->st, (255) + 1)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrType_copyFloat(
        &dst->fl, &src->fl)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrType_copyDouble(
        &dst->dl, &src->dl)) {
        return RTI_FALSE;
    }
            

    return RTI_TRUE;
}


/**
 * <<IMPLEMENTATION>>
 *
 * Defines:  TSeq, T
 *
 * Configure and implement 'BasicTypes' sequence class.
 */
#define T BasicTypes
#define TSeq BasicTypesSeq
#define T_initialize_ex BasicTypes_initialize_ex
#define T_finalize_ex   BasicTypes_finalize_ex
#define T_copy       BasicTypes_copy

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

