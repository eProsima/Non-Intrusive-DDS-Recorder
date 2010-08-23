
/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from Sequences.idl using "rtiddsgen".
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



#ifndef Sequences_h
#include "Sequences.h"
#endif

/* ========================================================================= */
const char *InsideTYPENAME = "Inside";

DDS_TypeCode* Inside_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode Inside_g_tc_sesh_sequence = DDS_INITIALIZE_SEQUENCE_TYPECODE(100,NULL);

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
            (char *)"sesh",/* Member name */
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

    Inside_g_tc_sesh_sequence._data._typeCode = (RTICdrTypeCode *)&DDS_g_tc_short;

    Inside_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_short;
    Inside_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)&Inside_g_tc_sesh_sequence;

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

    void* buffer;                
    buffer = NULL;        

    if (!RTICdrType_initShort(&sample->count)) {
        return RTI_FALSE;
    }                
            
    DDS_ShortSeq_initialize(&sample->sesh);
                
    if (!DDS_ShortSeq_set_maximum(&sample->sesh,
            (100))) {
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

    DDS_ShortSeq_finalize(&sample->sesh);
            
}

RTIBool Inside_copy(
    Inside* dst,
    const Inside* src)
{        

    if (!RTICdrType_copyShort(
        &dst->count, &src->count)) {
        return RTI_FALSE;
    }
            
    if (!DDS_ShortSeq_copy_no_alloc(&dst->sesh,
                                          &src->sesh)) {
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
const char *SequencesTYPENAME = "Sequences";

DDS_TypeCode* Sequences_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode Sequences_g_tc_message_string = DDS_INITIALIZE_STRING_TYPECODE(255);
    static DDS_TypeCode Sequences_g_tc_selo_sequence = DDS_INITIALIZE_SEQUENCE_TYPECODE(100,NULL);

    static DDS_TypeCode_Member Sequences_g_tc_members[3]=
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
            (char *)"selo",/* Member name */
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

    static DDS_TypeCode Sequences_g_tc =
    {{
        DDS_TK_STRUCT,/* Kind */
        DDS_BOOLEAN_FALSE, /* Ignored */
        -1,/* Ignored */
        (char *)"Sequences", /* Name */
        NULL, /* Ignored */
        0, /* Ignored */
        0, /* Ignored */
        NULL, /* Ignored */
        3, /* Number of members */
        Sequences_g_tc_members, /* Members */
        DDS_VM_NONE /* Ignored */
    }}; /* Type code for Sequences*/

    if (is_initialized) {
        return &Sequences_g_tc;
    }

    Sequences_g_tc_selo_sequence._data._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;

    Sequences_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)&Sequences_g_tc_message_string;
    Sequences_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)&Sequences_g_tc_selo_sequence;
    Sequences_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)Inside_get_typecode();

    is_initialized = RTI_TRUE;

    return &Sequences_g_tc;
}


RTIBool Sequences_initialize(
    Sequences* sample) {
    return Sequences_initialize_ex(sample,RTI_TRUE);
}
        
RTIBool Sequences_initialize_ex(
    Sequences* sample,RTIBool allocatePointers)
{

    void* buffer;                
    buffer = NULL;        

    sample->message = DDS_String_alloc((255));
    if (sample->message == NULL) {
        return RTI_FALSE;
    }
            
    DDS_LongSeq_initialize(&sample->selo);
                
    if (!DDS_LongSeq_set_maximum(&sample->selo,
            (100))) {
        return RTI_FALSE;
    }
            
    if (!Inside_initialize_ex(&sample->ins,allocatePointers)) {
        return RTI_FALSE;
    }
            

    return RTI_TRUE;
}

void Sequences_finalize(
    Sequences* sample)
{
    Sequences_finalize_ex(sample,RTI_TRUE);
}
        
void Sequences_finalize_ex(
    Sequences* sample,RTIBool deletePointers)
{        

    DDS_String_free(sample->message);                
            
    DDS_LongSeq_finalize(&sample->selo);
            
    Inside_finalize_ex(&sample->ins,deletePointers);
            
}

RTIBool Sequences_copy(
    Sequences* dst,
    const Sequences* src)
{        

    if (!RTICdrType_copyString(
        dst->message, src->message, (255) + 1)) {
        return RTI_FALSE;
    }
            
    if (!DDS_LongSeq_copy_no_alloc(&dst->selo,
                                          &src->selo)) {
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
 * Configure and implement 'Sequences' sequence class.
 */
#define T Sequences
#define TSeq SequencesSeq
#define T_initialize_ex Sequences_initialize_ex
#define T_finalize_ex   Sequences_finalize_ex
#define T_copy       Sequences_copy

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

