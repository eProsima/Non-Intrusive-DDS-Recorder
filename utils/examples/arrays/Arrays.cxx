
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

    static DDS_UnsignedLong Inside_g_tc_ocarray_dimensions[2] = {10,2};
    static DDS_UnsignedLong Inside_g_tc_sharray_dimensions[2] = {10,2};
    static DDS_UnsignedLong Inside_g_tc_usharray_dimensions[2] = {10,2};
    static DDS_UnsignedLong Inside_g_tc_loarray_dimensions[2] = {10,2};
    static DDS_UnsignedLong Inside_g_tc_uloarray_dimensions[2] = {10,2};
    static DDS_UnsignedLong Inside_g_tc_loloarray_dimensions[2] = {10,2};
    static DDS_UnsignedLong Inside_g_tc_uloloarray_dimensions[2] = {10,2};
    static DDS_UnsignedLong Inside_g_tc_charray_dimensions[2] = {10,2};
    static DDS_UnsignedLong Inside_g_tc_flarray_dimensions[2] = {10,2};
    static DDS_UnsignedLong Inside_g_tc_dlarray_dimensions[2] = {10,2};
    static DDS_TypeCode Inside_g_tc_ocarray_array = DDS_INITIALIZE_ARRAY_TYPECODE(2,10,Inside_g_tc_ocarray_dimensions,NULL);
    static DDS_TypeCode Inside_g_tc_sharray_array = DDS_INITIALIZE_ARRAY_TYPECODE(2,10,Inside_g_tc_sharray_dimensions,NULL);
    static DDS_TypeCode Inside_g_tc_usharray_array = DDS_INITIALIZE_ARRAY_TYPECODE(2,10,Inside_g_tc_usharray_dimensions,NULL);
    static DDS_TypeCode Inside_g_tc_loarray_array = DDS_INITIALIZE_ARRAY_TYPECODE(2,10,Inside_g_tc_loarray_dimensions,NULL);
    static DDS_TypeCode Inside_g_tc_uloarray_array = DDS_INITIALIZE_ARRAY_TYPECODE(2,10,Inside_g_tc_uloarray_dimensions,NULL);
    static DDS_TypeCode Inside_g_tc_loloarray_array = DDS_INITIALIZE_ARRAY_TYPECODE(2,10,Inside_g_tc_loloarray_dimensions,NULL);
    static DDS_TypeCode Inside_g_tc_uloloarray_array = DDS_INITIALIZE_ARRAY_TYPECODE(2,10,Inside_g_tc_uloloarray_dimensions,NULL);
    static DDS_TypeCode Inside_g_tc_charray_array = DDS_INITIALIZE_ARRAY_TYPECODE(2,10,Inside_g_tc_charray_dimensions,NULL);
    static DDS_TypeCode Inside_g_tc_flarray_array = DDS_INITIALIZE_ARRAY_TYPECODE(2,10,Inside_g_tc_flarray_dimensions,NULL);
    static DDS_TypeCode Inside_g_tc_dlarray_array = DDS_INITIALIZE_ARRAY_TYPECODE(2,10,Inside_g_tc_dlarray_dimensions,NULL);

    static DDS_TypeCode_Member Inside_g_tc_members[11]=
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
            (char *)"ocarray",/* Member name */
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
        },
        {
            (char *)"usharray",/* Member name */
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
            (char *)"uloarray",/* Member name */
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
            (char *)"loloarray",/* Member name */
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
            (char *)"uloloarray",/* Member name */
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
            (char *)"charray",/* Member name */
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
            (char *)"flarray",/* Member name */
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
            (char *)"dlarray",/* Member name */
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
        11, /* Number of members */
        Inside_g_tc_members, /* Members */
        DDS_VM_NONE /* Ignored */
    }}; /* Type code for Inside*/

    if (is_initialized) {
        return &Inside_g_tc;
    }

    Inside_g_tc_ocarray_array._data._typeCode = (RTICdrTypeCode *)&DDS_g_tc_octet;
    Inside_g_tc_sharray_array._data._typeCode = (RTICdrTypeCode *)&DDS_g_tc_short;
    Inside_g_tc_usharray_array._data._typeCode = (RTICdrTypeCode *)&DDS_g_tc_ushort;
    Inside_g_tc_loarray_array._data._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
    Inside_g_tc_uloarray_array._data._typeCode = (RTICdrTypeCode *)&DDS_g_tc_ulong;
    Inside_g_tc_loloarray_array._data._typeCode = (RTICdrTypeCode *)&DDS_g_tc_longlong;
    Inside_g_tc_uloloarray_array._data._typeCode = (RTICdrTypeCode *)&DDS_g_tc_ulonglong;
    Inside_g_tc_charray_array._data._typeCode = (RTICdrTypeCode *)&DDS_g_tc_char;
    Inside_g_tc_flarray_array._data._typeCode = (RTICdrTypeCode *)&DDS_g_tc_float;
    Inside_g_tc_dlarray_array._data._typeCode = (RTICdrTypeCode *)&DDS_g_tc_double;

    Inside_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
    Inside_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)&Inside_g_tc_ocarray_array;
    Inside_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)&Inside_g_tc_sharray_array;
    Inside_g_tc_members[3]._representation._typeCode = (RTICdrTypeCode *)&Inside_g_tc_usharray_array;
    Inside_g_tc_members[4]._representation._typeCode = (RTICdrTypeCode *)&Inside_g_tc_loarray_array;
    Inside_g_tc_members[5]._representation._typeCode = (RTICdrTypeCode *)&Inside_g_tc_uloarray_array;
    Inside_g_tc_members[6]._representation._typeCode = (RTICdrTypeCode *)&Inside_g_tc_loloarray_array;
    Inside_g_tc_members[7]._representation._typeCode = (RTICdrTypeCode *)&Inside_g_tc_uloloarray_array;
    Inside_g_tc_members[8]._representation._typeCode = (RTICdrTypeCode *)&Inside_g_tc_charray_array;
    Inside_g_tc_members[9]._representation._typeCode = (RTICdrTypeCode *)&Inside_g_tc_flarray_array;
    Inside_g_tc_members[10]._representation._typeCode = (RTICdrTypeCode *)&Inside_g_tc_dlarray_array;

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
        sample->ocarray, (10)*(2), RTI_CDR_OCTET_SIZE)) {
        return RTI_FALSE;
    }
                
    if (!RTICdrType_initArray(
        sample->sharray, (10)*(2), RTI_CDR_SHORT_SIZE)) {
        return RTI_FALSE;
    }
                
    if (!RTICdrType_initArray(
        sample->usharray, (10)*(2), RTI_CDR_UNSIGNED_SHORT_SIZE)) {
        return RTI_FALSE;
    }
                
    if (!RTICdrType_initArray(
        sample->loarray, (10)*(2), RTI_CDR_LONG_SIZE)) {
        return RTI_FALSE;
    }
                
    if (!RTICdrType_initArray(
        sample->uloarray, (10)*(2), RTI_CDR_UNSIGNED_LONG_SIZE)) {
        return RTI_FALSE;
    }
                
    if (!RTICdrType_initArray(
        sample->loloarray, (10)*(2), RTI_CDR_LONG_LONG_SIZE)) {
        return RTI_FALSE;
    }
                
    if (!RTICdrType_initArray(
        sample->uloloarray, (10)*(2), RTI_CDR_UNSIGNED_LONG_LONG_SIZE)) {
        return RTI_FALSE;
    }
                
    if (!RTICdrType_initArray(
        sample->charray, (10)*(2), RTI_CDR_CHAR_SIZE)) {
        return RTI_FALSE;
    }
                
    if (!RTICdrType_initArray(
        sample->flarray, (10)*(2), RTI_CDR_FLOAT_SIZE)) {
        return RTI_FALSE;
    }
                
    if (!RTICdrType_initArray(
        sample->dlarray, (10)*(2), RTI_CDR_DOUBLE_SIZE)) {
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
        dst->ocarray, src->ocarray, (10)*(2), RTI_CDR_OCTET_SIZE)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrType_copyArray(
        dst->sharray, src->sharray, (10)*(2), RTI_CDR_SHORT_SIZE)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrType_copyArray(
        dst->usharray, src->usharray, (10)*(2), RTI_CDR_UNSIGNED_SHORT_SIZE)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrType_copyArray(
        dst->loarray, src->loarray, (10)*(2), RTI_CDR_LONG_SIZE)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrType_copyArray(
        dst->uloarray, src->uloarray, (10)*(2), RTI_CDR_UNSIGNED_LONG_SIZE)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrType_copyArray(
        dst->loloarray, src->loloarray, (10)*(2), RTI_CDR_LONG_LONG_SIZE)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrType_copyArray(
        dst->uloloarray, src->uloloarray, (10)*(2), RTI_CDR_UNSIGNED_LONG_LONG_SIZE)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrType_copyArray(
        dst->charray, src->charray, (10)*(2), RTI_CDR_CHAR_SIZE)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrType_copyArray(
        dst->flarray, src->flarray, (10)*(2), RTI_CDR_FLOAT_SIZE)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrType_copyArray(
        dst->dlarray, src->dlarray, (10)*(2), RTI_CDR_DOUBLE_SIZE)) {
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
    static DDS_TypeCode Arrays_g_tc_ocarray_array = DDS_INITIALIZE_ARRAY_TYPECODE(1,20,NULL,NULL);
    static DDS_TypeCode Arrays_g_tc_sharray_array = DDS_INITIALIZE_ARRAY_TYPECODE(1,20,NULL,NULL);
    static DDS_TypeCode Arrays_g_tc_usharray_array = DDS_INITIALIZE_ARRAY_TYPECODE(1,20,NULL,NULL);
    static DDS_TypeCode Arrays_g_tc_loarray_array = DDS_INITIALIZE_ARRAY_TYPECODE(1,20,NULL,NULL);
    static DDS_TypeCode Arrays_g_tc_uloarray_array = DDS_INITIALIZE_ARRAY_TYPECODE(1,20,NULL,NULL);
    static DDS_TypeCode Arrays_g_tc_loloarray_array = DDS_INITIALIZE_ARRAY_TYPECODE(1,20,NULL,NULL);
    static DDS_TypeCode Arrays_g_tc_uloloarray_array = DDS_INITIALIZE_ARRAY_TYPECODE(1,20,NULL,NULL);
    static DDS_TypeCode Arrays_g_tc_charray_array = DDS_INITIALIZE_ARRAY_TYPECODE(1,20,NULL,NULL);
    static DDS_TypeCode Arrays_g_tc_flarray_array = DDS_INITIALIZE_ARRAY_TYPECODE(1,20,NULL,NULL);
    static DDS_TypeCode Arrays_g_tc_dlarray_array = DDS_INITIALIZE_ARRAY_TYPECODE(1,20,NULL,NULL);

    static DDS_TypeCode_Member Arrays_g_tc_members[12]=
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
            (char *)"ocarray",/* Member name */
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
        },
        {
            (char *)"usharray",/* Member name */
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
            (char *)"uloarray",/* Member name */
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
            (char *)"loloarray",/* Member name */
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
            (char *)"uloloarray",/* Member name */
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
            (char *)"charray",/* Member name */
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
            (char *)"flarray",/* Member name */
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
            (char *)"dlarray",/* Member name */
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
        12, /* Number of members */
        Arrays_g_tc_members, /* Members */
        DDS_VM_NONE /* Ignored */
    }}; /* Type code for Arrays*/

    if (is_initialized) {
        return &Arrays_g_tc;
    }

    Arrays_g_tc_ocarray_array._data._typeCode = (RTICdrTypeCode *)&DDS_g_tc_octet;
    Arrays_g_tc_sharray_array._data._typeCode = (RTICdrTypeCode *)&DDS_g_tc_short;
    Arrays_g_tc_usharray_array._data._typeCode = (RTICdrTypeCode *)&DDS_g_tc_ushort;
    Arrays_g_tc_loarray_array._data._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
    Arrays_g_tc_uloarray_array._data._typeCode = (RTICdrTypeCode *)&DDS_g_tc_ulong;
    Arrays_g_tc_loloarray_array._data._typeCode = (RTICdrTypeCode *)&DDS_g_tc_longlong;
    Arrays_g_tc_uloloarray_array._data._typeCode = (RTICdrTypeCode *)&DDS_g_tc_ulonglong;
    Arrays_g_tc_charray_array._data._typeCode = (RTICdrTypeCode *)&DDS_g_tc_char;
    Arrays_g_tc_flarray_array._data._typeCode = (RTICdrTypeCode *)&DDS_g_tc_float;
    Arrays_g_tc_dlarray_array._data._typeCode = (RTICdrTypeCode *)&DDS_g_tc_double;

    Arrays_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)&Arrays_g_tc_message_string;
    Arrays_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)&Arrays_g_tc_ocarray_array;
    Arrays_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)&Arrays_g_tc_sharray_array;
    Arrays_g_tc_members[3]._representation._typeCode = (RTICdrTypeCode *)&Arrays_g_tc_usharray_array;
    Arrays_g_tc_members[4]._representation._typeCode = (RTICdrTypeCode *)&Arrays_g_tc_loarray_array;
    Arrays_g_tc_members[5]._representation._typeCode = (RTICdrTypeCode *)&Arrays_g_tc_uloarray_array;
    Arrays_g_tc_members[6]._representation._typeCode = (RTICdrTypeCode *)&Arrays_g_tc_loloarray_array;
    Arrays_g_tc_members[7]._representation._typeCode = (RTICdrTypeCode *)&Arrays_g_tc_uloloarray_array;
    Arrays_g_tc_members[8]._representation._typeCode = (RTICdrTypeCode *)&Arrays_g_tc_charray_array;
    Arrays_g_tc_members[9]._representation._typeCode = (RTICdrTypeCode *)&Arrays_g_tc_flarray_array;
    Arrays_g_tc_members[10]._representation._typeCode = (RTICdrTypeCode *)&Arrays_g_tc_dlarray_array;
    Arrays_g_tc_members[11]._representation._typeCode = (RTICdrTypeCode *)Inside_get_typecode();

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
        sample->ocarray, (20), RTI_CDR_OCTET_SIZE)) {
        return RTI_FALSE;
    }
                
    if (!RTICdrType_initArray(
        sample->sharray, (20), RTI_CDR_SHORT_SIZE)) {
        return RTI_FALSE;
    }
                
    if (!RTICdrType_initArray(
        sample->usharray, (20), RTI_CDR_UNSIGNED_SHORT_SIZE)) {
        return RTI_FALSE;
    }
                
    if (!RTICdrType_initArray(
        sample->loarray, (20), RTI_CDR_LONG_SIZE)) {
        return RTI_FALSE;
    }
                
    if (!RTICdrType_initArray(
        sample->uloarray, (20), RTI_CDR_UNSIGNED_LONG_SIZE)) {
        return RTI_FALSE;
    }
                
    if (!RTICdrType_initArray(
        sample->loloarray, (20), RTI_CDR_LONG_LONG_SIZE)) {
        return RTI_FALSE;
    }
                
    if (!RTICdrType_initArray(
        sample->uloloarray, (20), RTI_CDR_UNSIGNED_LONG_LONG_SIZE)) {
        return RTI_FALSE;
    }
                
    if (!RTICdrType_initArray(
        sample->charray, (20), RTI_CDR_CHAR_SIZE)) {
        return RTI_FALSE;
    }
                
    if (!RTICdrType_initArray(
        sample->flarray, (20), RTI_CDR_FLOAT_SIZE)) {
        return RTI_FALSE;
    }
                
    if (!RTICdrType_initArray(
        sample->dlarray, (20), RTI_CDR_DOUBLE_SIZE)) {
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
        dst->ocarray, src->ocarray, (20), RTI_CDR_OCTET_SIZE)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrType_copyArray(
        dst->sharray, src->sharray, (20), RTI_CDR_SHORT_SIZE)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrType_copyArray(
        dst->usharray, src->usharray, (20), RTI_CDR_UNSIGNED_SHORT_SIZE)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrType_copyArray(
        dst->loarray, src->loarray, (20), RTI_CDR_LONG_SIZE)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrType_copyArray(
        dst->uloarray, src->uloarray, (20), RTI_CDR_UNSIGNED_LONG_SIZE)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrType_copyArray(
        dst->loloarray, src->loloarray, (20), RTI_CDR_LONG_LONG_SIZE)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrType_copyArray(
        dst->uloloarray, src->uloloarray, (20), RTI_CDR_UNSIGNED_LONG_LONG_SIZE)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrType_copyArray(
        dst->charray, src->charray, (20), RTI_CDR_CHAR_SIZE)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrType_copyArray(
        dst->flarray, src->flarray, (20), RTI_CDR_FLOAT_SIZE)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrType_copyArray(
        dst->dlarray, src->dlarray, (20), RTI_CDR_DOUBLE_SIZE)) {
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

