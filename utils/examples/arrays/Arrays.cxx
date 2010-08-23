
/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from Arrays.idl using "rtiddsgen".
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



#ifndef Arrays_h
#include "Arrays.h"
#endif

/* ========================================================================= */
const char *InsideTYPENAME = "Inside";

DDS_TypeCode* Inside_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_UnsignedLong Inside_g_tc_sharray_dimensions[2] = {10,2};
    static DDS_TypeCode Inside_g_tc_sharray_array = DDS_INITIALIZE_ARRAY_TYPECODE(2,10,Inside_g_tc_sharray_dimensions,NULL);

    static DDS_TypeCode_Member Inside_g_tc_members[2]=
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
            (char *)"sharray",/* Member name */
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

    static DDS_TypeCode Inside_g_tc =
    {{
        DDS_TK_STRUCT,/* Kind */
        DDS_BOOLEAN_FALSE, /* Ignored */
        -1,/* Ignored */
        (char *)"Inside", /* Name */
        NULL, /* Ignored */
        0, /* Ignored */
        0, /* Ignored */
        NULL, /* Ignored */
        2, /* Number of members */
        Inside_g_tc_members, /* Members */
        DDS_VM_NONE /* Ignored */
    }}; /* Type code for Inside*/

    if (is_initialized) {
        return &Inside_g_tc;
    }

    Inside_g_tc_sharray_array._data._typeCode = (RTICdrTypeCode *)&DDS_g_tc_short;

    Inside_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
    Inside_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)&Inside_g_tc_sharray_array;

    is_initialized = RTI_TRUE;

    return &Inside_g_tc;
}


RTIBool Inside_initialize(
    Inside* sample) {
    return Inside_initialize_ex(sample,RTI_TRUE);
}
        
RTIBool Inside_initialize_ex(
    Inside* sample,RTIBool allocatePointers)
{

    if (!RTICdrType_initLong(&sample->count)) {
        return RTI_FALSE;
    }                
                
    if (!RTICdrType_initArray(
        sample->sharray, (10)*(2), RTI_CDR_SHORT_SIZE)) {
        return RTI_FALSE;
    }
            

    return RTI_TRUE;
}

void Inside_finalize(
    Inside* sample)
{
    Inside_finalize_ex(sample,RTI_TRUE);
}
        
void Inside_finalize_ex(
    Inside* sample,RTIBool deletePointers)
{        

}

RTIBool Inside_copy(
    Inside* dst,
    const Inside* src)
{        

    if (!RTICdrType_copyLong(
        &dst->count, &src->count)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrType_copyArray(
        dst->sharray, src->sharray, (10)*(2), RTI_CDR_SHORT_SIZE)) {
        return RTI_FALSE;
    }
            

    return RTI_TRUE;
}


/**
 * <<IMPLEMENTATION>>
 *
 * Defines:  TSeq, T
 *
 * Configure and implement 'Inside' sequence class.
 */
#define T Inside
#define TSeq InsideSeq
#define T_initialize_ex Inside_initialize_ex
#define T_finalize_ex   Inside_finalize_ex
#define T_copy       Inside_copy

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
const char *ArraysTYPENAME = "Arrays";

DDS_TypeCode* Arrays_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode Arrays_g_tc_message_string = DDS_INITIALIZE_STRING_TYPECODE(255);
    static DDS_TypeCode Arrays_g_tc_loarray_array = DDS_INITIALIZE_ARRAY_TYPECODE(1,20,NULL,NULL);

    static DDS_TypeCode_Member Arrays_g_tc_members[3]=
    {
        {
            (char *)"message",/* Member name */
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
            (char *)"loarray",/* Member name */
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
            (char *)"ins",/* Member name */
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

    static DDS_TypeCode Arrays_g_tc =
    {{
        DDS_TK_STRUCT,/* Kind */
        DDS_BOOLEAN_FALSE, /* Ignored */
        -1,/* Ignored */
        (char *)"Arrays", /* Name */
        NULL, /* Ignored */
        0, /* Ignored */
        0, /* Ignored */
        NULL, /* Ignored */
        3, /* Number of members */
        Arrays_g_tc_members, /* Members */
        DDS_VM_NONE /* Ignored */
    }}; /* Type code for Arrays*/

    if (is_initialized) {
        return &Arrays_g_tc;
    }

    Arrays_g_tc_loarray_array._data._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;

    Arrays_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)&Arrays_g_tc_message_string;
    Arrays_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)&Arrays_g_tc_loarray_array;
    Arrays_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)Inside_get_typecode();

    is_initialized = RTI_TRUE;

    return &Arrays_g_tc;
}


RTIBool Arrays_initialize(
    Arrays* sample) {
    return Arrays_initialize_ex(sample,RTI_TRUE);
}
        
RTIBool Arrays_initialize_ex(
    Arrays* sample,RTIBool allocatePointers)
{

    sample->message = DDS_String_alloc((255));
    if (sample->message == NULL) {
        return RTI_FALSE;
    }
                
    if (!RTICdrType_initArray(
        sample->loarray, (20), RTI_CDR_LONG_SIZE)) {
        return RTI_FALSE;
    }
            
    if (!Inside_initialize_ex(&sample->ins,allocatePointers)) {
        return RTI_FALSE;
    }
            

    return RTI_TRUE;
}

void Arrays_finalize(
    Arrays* sample)
{
    Arrays_finalize_ex(sample,RTI_TRUE);
}
        
void Arrays_finalize_ex(
    Arrays* sample,RTIBool deletePointers)
{        

    DDS_String_free(sample->message);                
            
    Inside_finalize_ex(&sample->ins,deletePointers);
            
}

RTIBool Arrays_copy(
    Arrays* dst,
    const Arrays* src)
{        

    if (!RTICdrType_copyString(
        dst->message, src->message, (255) + 1)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrType_copyArray(
        dst->loarray, src->loarray, (20), RTI_CDR_LONG_SIZE)) {
        return RTI_FALSE;
    }
            
    if (!Inside_copy(
        &dst->ins, &src->ins)) {
        return RTI_FALSE;
    }
            

    return RTI_TRUE;
}


/**
 * <<IMPLEMENTATION>>
 *
 * Defines:  TSeq, T
 *
 * Configure and implement 'Arrays' sequence class.
 */
#define T Arrays
#define TSeq ArraysSeq
#define T_initialize_ex Arrays_initialize_ex
#define T_finalize_ex   Arrays_finalize_ex
#define T_copy       Arrays_copy

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

