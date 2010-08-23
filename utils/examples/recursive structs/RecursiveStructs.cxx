
/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from RecursiveStructs.idl using "rtiddsgen".
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



#ifndef RecursiveStructs_h
#include "RecursiveStructs.h"
#endif

/* ========================================================================= */
const char *LevelTwoTYPENAME = "LevelTwo";

DDS_TypeCode* LevelTwo_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode LevelTwo_g_tc_levelTwoSt_string = DDS_INITIALIZE_STRING_TYPECODE(255);

    static DDS_TypeCode_Member LevelTwo_g_tc_members[2]=
    {
        {
            (char *)"levelTwoLo",/* Member name */
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
            (char *)"levelTwoSt",/* Member name */
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

    static DDS_TypeCode LevelTwo_g_tc =
    {{
        DDS_TK_STRUCT,/* Kind */
        DDS_BOOLEAN_FALSE, /* Ignored */
        -1,/* Ignored */
        (char *)"LevelTwo", /* Name */
        NULL, /* Ignored */
        0, /* Ignored */
        0, /* Ignored */
        NULL, /* Ignored */
        2, /* Number of members */
        LevelTwo_g_tc_members, /* Members */
        DDS_VM_NONE /* Ignored */
    }}; /* Type code for LevelTwo*/

    if (is_initialized) {
        return &LevelTwo_g_tc;
    }


    LevelTwo_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
    LevelTwo_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)&LevelTwo_g_tc_levelTwoSt_string;

    is_initialized = RTI_TRUE;

    return &LevelTwo_g_tc;
}


RTIBool LevelTwo_initialize(
    LevelTwo* sample) {
    return LevelTwo_initialize_ex(sample,RTI_TRUE);
}
        
RTIBool LevelTwo_initialize_ex(
    LevelTwo* sample,RTIBool allocatePointers)
{

    if (!RTICdrType_initLong(&sample->levelTwoLo)) {
        return RTI_FALSE;
    }                
            
    sample->levelTwoSt = DDS_String_alloc((255));
    if (sample->levelTwoSt == NULL) {
        return RTI_FALSE;
    }
            

    return RTI_TRUE;
}

void LevelTwo_finalize(
    LevelTwo* sample)
{
    LevelTwo_finalize_ex(sample,RTI_TRUE);
}
        
void LevelTwo_finalize_ex(
    LevelTwo* sample,RTIBool deletePointers)
{        

    DDS_String_free(sample->levelTwoSt);                
            
}

RTIBool LevelTwo_copy(
    LevelTwo* dst,
    const LevelTwo* src)
{        

    if (!RTICdrType_copyLong(
        &dst->levelTwoLo, &src->levelTwoLo)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrType_copyString(
        dst->levelTwoSt, src->levelTwoSt, (255) + 1)) {
        return RTI_FALSE;
    }
            

    return RTI_TRUE;
}


/**
 * <<IMPLEMENTATION>>
 *
 * Defines:  TSeq, T
 *
 * Configure and implement 'LevelTwo' sequence class.
 */
#define T LevelTwo
#define TSeq LevelTwoSeq
#define T_initialize_ex LevelTwo_initialize_ex
#define T_finalize_ex   LevelTwo_finalize_ex
#define T_copy       LevelTwo_copy

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
const char *LevelOneTYPENAME = "LevelOne";

DDS_TypeCode* LevelOne_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;


    static DDS_TypeCode_Member LevelOne_g_tc_members[3]=
    {
        {
            (char *)"two1",/* Member name */
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
            (char *)"two2",/* Member name */
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
            (char *)"levelOneLo",/* Member name */
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

    static DDS_TypeCode LevelOne_g_tc =
    {{
        DDS_TK_STRUCT,/* Kind */
        DDS_BOOLEAN_FALSE, /* Ignored */
        -1,/* Ignored */
        (char *)"LevelOne", /* Name */
        NULL, /* Ignored */
        0, /* Ignored */
        0, /* Ignored */
        NULL, /* Ignored */
        3, /* Number of members */
        LevelOne_g_tc_members, /* Members */
        DDS_VM_NONE /* Ignored */
    }}; /* Type code for LevelOne*/

    if (is_initialized) {
        return &LevelOne_g_tc;
    }


    LevelOne_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)LevelTwo_get_typecode();
    LevelOne_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)LevelTwo_get_typecode();
    LevelOne_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;

    is_initialized = RTI_TRUE;

    return &LevelOne_g_tc;
}


RTIBool LevelOne_initialize(
    LevelOne* sample) {
    return LevelOne_initialize_ex(sample,RTI_TRUE);
}
        
RTIBool LevelOne_initialize_ex(
    LevelOne* sample,RTIBool allocatePointers)
{

    if (!LevelTwo_initialize_ex(&sample->two1,allocatePointers)) {
        return RTI_FALSE;
    }
            
    if (!LevelTwo_initialize_ex(&sample->two2,allocatePointers)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrType_initLong(&sample->levelOneLo)) {
        return RTI_FALSE;
    }                
            

    return RTI_TRUE;
}

void LevelOne_finalize(
    LevelOne* sample)
{
    LevelOne_finalize_ex(sample,RTI_TRUE);
}
        
void LevelOne_finalize_ex(
    LevelOne* sample,RTIBool deletePointers)
{        

    LevelTwo_finalize_ex(&sample->two1,deletePointers);
            
    LevelTwo_finalize_ex(&sample->two2,deletePointers);
            
}

RTIBool LevelOne_copy(
    LevelOne* dst,
    const LevelOne* src)
{        

    if (!LevelTwo_copy(
        &dst->two1, &src->two1)) {
        return RTI_FALSE;
    }
            
    if (!LevelTwo_copy(
        &dst->two2, &src->two2)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrType_copyLong(
        &dst->levelOneLo, &src->levelOneLo)) {
        return RTI_FALSE;
    }
            

    return RTI_TRUE;
}


/**
 * <<IMPLEMENTATION>>
 *
 * Defines:  TSeq, T
 *
 * Configure and implement 'LevelOne' sequence class.
 */
#define T LevelOne
#define TSeq LevelOneSeq
#define T_initialize_ex LevelOne_initialize_ex
#define T_finalize_ex   LevelOne_finalize_ex
#define T_copy       LevelOne_copy

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
const char *RecursiveStructsTYPENAME = "RecursiveStructs";

DDS_TypeCode* RecursiveStructs_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode RecursiveStructs_g_tc_message_string = DDS_INITIALIZE_STRING_TYPECODE(255);

    static DDS_TypeCode_Member RecursiveStructs_g_tc_members[3]=
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
            (char *)"one",/* Member name */
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

    static DDS_TypeCode RecursiveStructs_g_tc =
    {{
        DDS_TK_STRUCT,/* Kind */
        DDS_BOOLEAN_FALSE, /* Ignored */
        -1,/* Ignored */
        (char *)"RecursiveStructs", /* Name */
        NULL, /* Ignored */
        0, /* Ignored */
        0, /* Ignored */
        NULL, /* Ignored */
        3, /* Number of members */
        RecursiveStructs_g_tc_members, /* Members */
        DDS_VM_NONE /* Ignored */
    }}; /* Type code for RecursiveStructs*/

    if (is_initialized) {
        return &RecursiveStructs_g_tc;
    }


    RecursiveStructs_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
    RecursiveStructs_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)&RecursiveStructs_g_tc_message_string;
    RecursiveStructs_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)LevelOne_get_typecode();

    is_initialized = RTI_TRUE;

    return &RecursiveStructs_g_tc;
}


RTIBool RecursiveStructs_initialize(
    RecursiveStructs* sample) {
    return RecursiveStructs_initialize_ex(sample,RTI_TRUE);
}
        
RTIBool RecursiveStructs_initialize_ex(
    RecursiveStructs* sample,RTIBool allocatePointers)
{

    if (!RTICdrType_initLong(&sample->count)) {
        return RTI_FALSE;
    }                
            
    sample->message = DDS_String_alloc((255));
    if (sample->message == NULL) {
        return RTI_FALSE;
    }
            
    if (!LevelOne_initialize_ex(&sample->one,allocatePointers)) {
        return RTI_FALSE;
    }
            

    return RTI_TRUE;
}

void RecursiveStructs_finalize(
    RecursiveStructs* sample)
{
    RecursiveStructs_finalize_ex(sample,RTI_TRUE);
}
        
void RecursiveStructs_finalize_ex(
    RecursiveStructs* sample,RTIBool deletePointers)
{        

    DDS_String_free(sample->message);                
            
    LevelOne_finalize_ex(&sample->one,deletePointers);
            
}

RTIBool RecursiveStructs_copy(
    RecursiveStructs* dst,
    const RecursiveStructs* src)
{        

    if (!RTICdrType_copyLong(
        &dst->count, &src->count)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrType_copyString(
        dst->message, src->message, (255) + 1)) {
        return RTI_FALSE;
    }
            
    if (!LevelOne_copy(
        &dst->one, &src->one)) {
        return RTI_FALSE;
    }
            

    return RTI_TRUE;
}


/**
 * <<IMPLEMENTATION>>
 *
 * Defines:  TSeq, T
 *
 * Configure and implement 'RecursiveStructs' sequence class.
 */
#define T RecursiveStructs
#define TSeq RecursiveStructsSeq
#define T_initialize_ex RecursiveStructs_initialize_ex
#define T_finalize_ex   RecursiveStructs_finalize_ex
#define T_copy       RecursiveStructs_copy

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

