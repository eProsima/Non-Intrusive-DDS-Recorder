
/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from Unions.idl using "rtiddsgen".
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



#ifndef Unions_h
#include "Unions.h"
#endif

/* ========================================================================= */
const char *InsideTYPENAME = "Inside";

DDS_TypeCode* Inside_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode Inside_g_tc_ocar_array = DDS_INITIALIZE_ARRAY_TYPECODE(1,10,NULL,NULL);
    static DDS_TypeCode Inside_g_tc_sesh_sequence = DDS_INITIALIZE_SEQUENCE_TYPECODE(10,NULL);

    static DDS_TypeCode_Member Inside_g_tc_members[3]=
    {
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
            (char *)"ocar",/* Member name */
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
        3, /* Number of members */
        Inside_g_tc_members, /* Members */
        DDS_VM_NONE /* Ignored */
    }}; /* Type code for Inside*/

    if (is_initialized) {
        return &Inside_g_tc;
    }

    Inside_g_tc_ocar_array._data._typeCode = (RTICdrTypeCode *)&DDS_g_tc_octet;
    Inside_g_tc_sesh_sequence._data._typeCode = (RTICdrTypeCode *)&DDS_g_tc_short;

    Inside_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_ulong;
    Inside_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)&Inside_g_tc_ocar_array;
    Inside_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)&Inside_g_tc_sesh_sequence;

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

    if (!RTICdrType_initUnsignedLong(&sample->ulo)) {
        return RTI_FALSE;
    }                
                
    if (!RTICdrType_initArray(
        sample->ocar, (10), RTI_CDR_OCTET_SIZE)) {
        return RTI_FALSE;
    }
            
    DDS_ShortSeq_initialize(&sample->sesh);
                
    if (!DDS_ShortSeq_set_maximum(&sample->sesh,
            (10))) {
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

    if (!RTICdrType_copyUnsignedLong(
        &dst->ulo, &src->ulo)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrType_copyArray(
        dst->ocar, src->ocar, (10), RTI_CDR_OCTET_SIZE)) {
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
const char *UnionTYPENAME = "Union";

DDS_TypeCode* Union_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode Union_g_tc_fls_array = DDS_INITIALIZE_ARRAY_TYPECODE(1,10,NULL,NULL);
    static DDS_TypeCode Union_g_tc_los_sequence = DDS_INITIALIZE_SEQUENCE_TYPECODE(10,NULL);
    static DDS_TypeCode Union_g_tc_message_string = DDS_INITIALIZE_STRING_TYPECODE(255);

    static DDS_TypeCode_Member Union_g_tc_members[4]=
    {
        {
            (char *)"fls",/* Member name */
            {
                0,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            1, /* Number of labels */
            1, /* First label */
            NULL, /* Labels (it is NULL when there is only one label)*/
            DDS_BOOLEAN_FALSE, /* Is a key? */
            DDS_PRIVATE_MEMBER,/* Ignored */
            0,/* Ignored */
            NULL/* Ignored */
        },
        {
            (char *)"los",/* Member name */
            {
                0,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            1, /* Number of labels */
            2, /* First label */
            NULL, /* Labels (it is NULL when there is only one label)*/
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
            1, /* Number of labels */
            5, /* First label */
            NULL, /* Labels (it is NULL when there is only one label)*/
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
            1, /* Number of labels */
            RTI_CDR_TYPE_CODE_UNION_DEFAULT_LABEL, /* First label */
            NULL, /* Labels (it is NULL when there is only one label)*/
            DDS_BOOLEAN_FALSE, /* Is a key? */
            DDS_PRIVATE_MEMBER,/* Ignored */
            0,/* Ignored */
            NULL/* Ignored */
        }
    };

    static DDS_TypeCode Union_g_tc =
    {{
        DDS_TK_UNION,/* Kind */
        DDS_BOOLEAN_FALSE, /* Ignored */
        3,/* Default index */
        (char *)"Union", /* Name */
        NULL, /* Discriminator type code is assigned later */
        0, /* Ignored */
        0, /* Ignored */
        NULL, /* Ignored */
        4, /* Number of members */
        Union_g_tc_members, /* Members */
        DDS_VM_NONE /* Ignored */
    }}; /* Type code for Union*/

    if (is_initialized) {
        return &Union_g_tc;
    }

    Union_g_tc_fls_array._data._typeCode = (RTICdrTypeCode *)&DDS_g_tc_float;
    Union_g_tc_los_sequence._data._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;

    Union_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)&Union_g_tc_fls_array;
    Union_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)&Union_g_tc_los_sequence;
    Union_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)Inside_get_typecode();
    Union_g_tc_members[3]._representation._typeCode = (RTICdrTypeCode *)&Union_g_tc_message_string;

    Union_g_tc._data._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long; /* Discriminator type code */

    is_initialized = RTI_TRUE;

    return &Union_g_tc;
}


RTIBool Union_initialize(
    Union* sample) {
    return Union_initialize_ex(sample,RTI_TRUE);
}
        
RTIBool Union_initialize_ex(
    Union* sample,RTIBool allocatePointers)
{

    void* buffer;                
    buffer = NULL;        
    
    if (!RTICdrType_initArray(
        sample->_u.fls, (10), RTI_CDR_FLOAT_SIZE)) {
        return RTI_FALSE;
    }
            
    DDS_LongSeq_initialize(&sample->_u.los);
                
    if (!DDS_LongSeq_set_maximum(&sample->_u.los,
            (10))) {
        return RTI_FALSE;
    }
            
    if (!Inside_initialize_ex(&sample->_u.ins,allocatePointers)) {
        return RTI_FALSE;
    }
            
    sample->_u.message = DDS_String_alloc((255));
    if (sample->_u.message == NULL) {
        return RTI_FALSE;
    }
            

    return RTI_TRUE;
}

void Union_finalize(
    Union* sample)
{
    Union_finalize_ex(sample,RTI_TRUE);
}
        
void Union_finalize_ex(
    Union* sample,RTIBool deletePointers)
{        

    DDS_LongSeq_finalize(&sample->_u.los);
            
    Inside_finalize_ex(&sample->_u.ins,deletePointers);
            
    DDS_String_free(sample->_u.message);                
            
}

RTIBool Union_copy(
    Union* dst,
    const Union* src)
{        

    if (!RTICdrType_copyLong(
        &dst->_d, &src->_d)) {
        return RTI_FALSE;
    }
            
    switch(src->_d) {
          case 1:
        {                                    
        
    if (!RTICdrType_copyArray(
        dst->_u.fls, src->_u.fls, (10), RTI_CDR_FLOAT_SIZE)) {
        return RTI_FALSE;
    }
            
        } break;
      case 2:
        {                                    
        
    if (!DDS_LongSeq_copy_no_alloc(&dst->_u.los,
                                          &src->_u.los)) {
        return RTI_FALSE;
    }
            
        } break;
      case 5:
        {                                    
        
    if (!Inside_copy(
        &dst->_u.ins, &src->_u.ins)) {
        return RTI_FALSE;
    }
            
        } break;
      default:
        {                                    
        
    if (!RTICdrType_copyString(
        dst->_u.message, src->_u.message, (255) + 1)) {
        return RTI_FALSE;
    }
            
        };
              
    }
      

    return RTI_TRUE;
}


/**
 * <<IMPLEMENTATION>>
 *
 * Defines:  TSeq, T
 *
 * Configure and implement 'Union' sequence class.
 */
#define T Union
#define TSeq UnionSeq
#define T_initialize_ex Union_initialize_ex
#define T_finalize_ex   Union_finalize_ex
#define T_copy       Union_copy

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
const char *UnionsTYPENAME = "Unions";

DDS_TypeCode* Unions_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;


    static DDS_TypeCode_Member Unions_g_tc_members[1]=
    {
        {
            (char *)"u_n_i_o_n",/* Member name */
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

    static DDS_TypeCode Unions_g_tc =
    {{
        DDS_TK_STRUCT,/* Kind */
        DDS_BOOLEAN_FALSE, /* Ignored */
        -1,/* Ignored */
        (char *)"Unions", /* Name */
        NULL, /* Ignored */
        0, /* Ignored */
        0, /* Ignored */
        NULL, /* Ignored */
        1, /* Number of members */
        Unions_g_tc_members, /* Members */
        DDS_VM_NONE /* Ignored */
    }}; /* Type code for Unions*/

    if (is_initialized) {
        return &Unions_g_tc;
    }


    Unions_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)Union_get_typecode();

    is_initialized = RTI_TRUE;

    return &Unions_g_tc;
}


RTIBool Unions_initialize(
    Unions* sample) {
    return Unions_initialize_ex(sample,RTI_TRUE);
}
        
RTIBool Unions_initialize_ex(
    Unions* sample,RTIBool allocatePointers)
{

    if (!Union_initialize_ex(&sample->u_n_i_o_n,allocatePointers)) {
        return RTI_FALSE;
    }
            

    return RTI_TRUE;
}

void Unions_finalize(
    Unions* sample)
{
    Unions_finalize_ex(sample,RTI_TRUE);
}
        
void Unions_finalize_ex(
    Unions* sample,RTIBool deletePointers)
{        

    Union_finalize_ex(&sample->u_n_i_o_n,deletePointers);
            
}

RTIBool Unions_copy(
    Unions* dst,
    const Unions* src)
{        

    if (!Union_copy(
        &dst->u_n_i_o_n, &src->u_n_i_o_n)) {
        return RTI_FALSE;
    }
            

    return RTI_TRUE;
}


/**
 * <<IMPLEMENTATION>>
 *
 * Defines:  TSeq, T
 *
 * Configure and implement 'Unions' sequence class.
 */
#define T Unions
#define TSeq UnionsSeq
#define T_initialize_ex Unions_initialize_ex
#define T_finalize_ex   Unions_finalize_ex
#define T_copy       Unions_copy

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

