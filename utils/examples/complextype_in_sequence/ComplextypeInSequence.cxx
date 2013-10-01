
/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from ComplextypeInSequence.idl using "rtiddsgen".
  The rtiddsgen tool is part of the RTI Connext distribution.
  For more information, type 'rtiddsgen -help' at a command shell
  or consult the RTI Connext manual.
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



#include "ComplextypeInSequence.h"

/* ========================================================================= */
const char *EstructuraTYPENAME = "Estructura";

DDS_TypeCode* Estructura_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode Estructura_g_tc_msg_string = DDS_INITIALIZE_STRING_TYPECODE(255);

    static DDS_TypeCode_Member Estructura_g_tc_members[2]=
    {
        {
            (char *)"id",/* Member name */
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
            (char *)"msg",/* Member name */
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

    static DDS_TypeCode Estructura_g_tc =
    {{
        DDS_TK_STRUCT,/* Kind */
        DDS_BOOLEAN_FALSE, /* Ignored */
        -1,/* Ignored */
        (char *)"Estructura", /* Name */
        NULL, /* Ignored */
        0, /* Ignored */
        0, /* Ignored */
        NULL, /* Ignored */
        2, /* Number of members */
        Estructura_g_tc_members, /* Members */
        DDS_VM_NONE /* Ignored */
    }}; /* Type code for Estructura*/

    if (is_initialized) {
        return &Estructura_g_tc;
    }


    Estructura_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
    Estructura_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)&Estructura_g_tc_msg_string;

    is_initialized = RTI_TRUE;

    return &Estructura_g_tc;
}


RTIBool Estructura_initialize(
    Estructura* sample) {
  return Estructura_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}
        
RTIBool Estructura_initialize_ex(
    Estructura* sample,RTIBool allocatePointers,RTIBool allocateMemory)
{
        
    
    if (allocatePointers) {} /* To avoid warnings */
    if (allocateMemory) {} /* To avoid warnings */

    if (!RTICdrType_initLong(&sample->id)) {
        return RTI_FALSE;
    }                
            

    if (allocateMemory) {
        sample->msg = DDS_String_alloc((255));
        if (sample->msg == NULL) {
            return RTI_FALSE;
        }
    } else {
        if (sample->msg != NULL) { 
            sample->msg[0] = '\0';
        }
    }
            


    return RTI_TRUE;
}

void Estructura_finalize(
    Estructura* sample)
{
    Estructura_finalize_ex(sample,RTI_TRUE);
}
        
void Estructura_finalize_ex(
    Estructura* sample,RTIBool deletePointers)
{        
    if (sample) { } /* To avoid warnings */
    if (deletePointers) {} /* To avoid warnings */



    DDS_String_free(sample->msg);                
            

}

RTIBool Estructura_copy(
    Estructura* dst,
    const Estructura* src)
{        

    if (!RTICdrType_copyLong(
        &dst->id, &src->id)) {
        return RTI_FALSE;
    }
            

    if (!RTICdrType_copyString(
        dst->msg, src->msg, (255) + 1)) {
        return RTI_FALSE;
    }
            


    return RTI_TRUE;
}


/**
 * <<IMPLEMENTATION>>
 *
 * Defines:  TSeq, T
 *
 * Configure and implement 'Estructura' sequence class.
 */
#define T Estructura
#define TSeq EstructuraSeq
#define T_initialize_ex Estructura_initialize_ex
#define T_finalize_ex   Estructura_finalize_ex
#define T_copy       Estructura_copy

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

DDS_TypeCode* Estructura_seq_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode Estructura_seq_g_tc_sequence = DDS_INITIALIZE_SEQUENCE_TYPECODE(100,NULL);

    static DDS_TypeCode Estructura_seq_g_tc =
    {{
        DDS_TK_ALIAS, /* Kind*/
        DDS_BOOLEAN_FALSE, /* Is a pointer? */
        -1, /* Ignored */
        (char *)"Estructura_seq", /* Name */
        NULL, /* Content type code is assigned later */
        0, /* Ignored */
        0, /* Ignored */
        NULL, /* Ignored */
        0, /* Ignored */
        NULL, /* Ignored */
        DDS_VM_NONE /* Ignored */
    }}; /* Type code for Estructura_seq */

    if (is_initialized) {
        return &Estructura_seq_g_tc;
    }

    Estructura_seq_g_tc_sequence._data._typeCode = (RTICdrTypeCode *)Estructura_get_typecode();
    Estructura_seq_g_tc._data._typeCode = (RTICdrTypeCode *)&Estructura_seq_g_tc_sequence; /* Content type code */

    is_initialized = RTI_TRUE;

    return &Estructura_seq_g_tc;
}


RTIBool Estructura_seq_initialize(
    Estructura_seq* sample)
{
    return Estructura_seq_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool Estructura_seq_initialize_ex(
    Estructura_seq* sample,RTIBool allocatePointers,RTIBool allocateMemory)
{

    void* buffer = NULL;
    if (buffer) {} /* To avoid warnings */


    if (allocatePointers) {} /* To avoid warnings */
    if (allocateMemory) {} /* To avoid warnings */



    if (allocateMemory) {
        EstructuraSeq_initialize(sample);
        EstructuraSeq_set_element_pointers_allocation(sample,allocatePointers);
        if (!EstructuraSeq_set_maximum(sample,
                                           (100))) {
            return RTI_FALSE;
        }
    } else {
        EstructuraSeq_set_length(sample,0);
    }
            


    return RTI_TRUE;
}

void Estructura_seq_finalize(
    Estructura_seq* sample)
{
    Estructura_seq_finalize_ex(sample,RTI_TRUE);
}
            
void Estructura_seq_finalize_ex(
    Estructura_seq* sample,RTIBool deletePointers)
{
    if (sample) {} /* To avoid warnings */
    if (deletePointers) {} /* To avoid warnings */


    EstructuraSeq_finalize(sample);
            

}


RTIBool Estructura_seq_copy(
    Estructura_seq* dst,
    const Estructura_seq* src)
{

    if (!EstructuraSeq_copy_no_alloc(dst,
                                          src)) {
        return RTI_FALSE;
    }
            


    return RTI_TRUE;
}

    
/**
 * <<IMPLEMENTATION>>
 *
 * Defines:  TSeq, T
 *
 * Configure and implement 'Estructura_seq' sequence class.
 */
#define T            Estructura_seq
#define TSeq         Estructura_seqSeq
#define T_initialize_ex Estructura_seq_initialize_ex
#define T_finalize_ex   Estructura_seq_finalize_ex
#define T_copy       Estructura_seq_copy


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
const char *CompletypeInSequenceTYPENAME = "CompletypeInSequence";

DDS_TypeCode* CompletypeInSequence_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;


    static DDS_TypeCode_Member CompletypeInSequence_g_tc_members[1]=
    {
        {
            (char *)"seq",/* Member name */
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

    static DDS_TypeCode CompletypeInSequence_g_tc =
    {{
        DDS_TK_STRUCT,/* Kind */
        DDS_BOOLEAN_FALSE, /* Ignored */
        -1,/* Ignored */
        (char *)"CompletypeInSequence", /* Name */
        NULL, /* Ignored */
        0, /* Ignored */
        0, /* Ignored */
        NULL, /* Ignored */
        1, /* Number of members */
        CompletypeInSequence_g_tc_members, /* Members */
        DDS_VM_NONE /* Ignored */
    }}; /* Type code for CompletypeInSequence*/

    if (is_initialized) {
        return &CompletypeInSequence_g_tc;
    }


    CompletypeInSequence_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)Estructura_seq_get_typecode();

    is_initialized = RTI_TRUE;

    return &CompletypeInSequence_g_tc;
}


RTIBool CompletypeInSequence_initialize(
    CompletypeInSequence* sample) {
  return CompletypeInSequence_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}
        
RTIBool CompletypeInSequence_initialize_ex(
    CompletypeInSequence* sample,RTIBool allocatePointers,RTIBool allocateMemory)
{
        
    
    if (allocatePointers) {} /* To avoid warnings */
    if (allocateMemory) {} /* To avoid warnings */

    if (!Estructura_seq_initialize_ex(&sample->seq,allocatePointers,allocateMemory)) {
        return RTI_FALSE;
    }
            


    return RTI_TRUE;
}

void CompletypeInSequence_finalize(
    CompletypeInSequence* sample)
{
    CompletypeInSequence_finalize_ex(sample,RTI_TRUE);
}
        
void CompletypeInSequence_finalize_ex(
    CompletypeInSequence* sample,RTIBool deletePointers)
{        
    if (sample) { } /* To avoid warnings */
    if (deletePointers) {} /* To avoid warnings */


    Estructura_seq_finalize_ex(&sample->seq,deletePointers);
            

}

RTIBool CompletypeInSequence_copy(
    CompletypeInSequence* dst,
    const CompletypeInSequence* src)
{        

    if (!Estructura_seq_copy(
        &dst->seq, &src->seq)) {
        return RTI_FALSE;
    }
            


    return RTI_TRUE;
}


/**
 * <<IMPLEMENTATION>>
 *
 * Defines:  TSeq, T
 *
 * Configure and implement 'CompletypeInSequence' sequence class.
 */
#define T CompletypeInSequence
#define TSeq CompletypeInSequenceSeq
#define T_initialize_ex CompletypeInSequence_initialize_ex
#define T_finalize_ex   CompletypeInSequence_finalize_ex
#define T_copy       CompletypeInSequence_copy

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

