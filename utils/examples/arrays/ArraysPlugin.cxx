
/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from Arrays.idl using "rtiddsgen".
  The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
  For more information, type 'rtiddsgen -help' at a command shell
  or consult the RTI Data Distribution Service manual.
*/


#include <string.h>

#ifdef __cplusplus
#ifndef ndds_cpp_h
  #include "ndds/ndds_cpp.h"
#endif
#else
#ifndef ndds_c_h
  #include "ndds/ndds_c.h"
#endif
#endif

#ifndef osapi_type_h
  #include "osapi/osapi_type.h"
#endif
#ifndef osapi_heap_h
  #include "osapi/osapi_heap.h"
#endif

#ifndef osapi_utility_h
  #include "osapi/osapi_utility.h"
#endif

#ifndef cdr_type_h
  #include "cdr/cdr_type.h"
#endif

#ifndef cdr_encapsulation_h
  #include "cdr/cdr_encapsulation.h"
#endif

#ifndef cdr_stream_h
  #include "cdr/cdr_stream.h"
#endif

#ifndef pres_typePlugin_h
  #include "pres/pres_typePlugin.h"
#endif



#ifndef ArraysPlugin_h
#include "ArraysPlugin.h"
#endif


/* --------------------------------------------------------------------------------------
 *  Type Inside
 * -------------------------------------------------------------------------------------- */

/* --------------------------------------------------------------------------------------
    Support functions:
 * -------------------------------------------------------------------------------------- */


Inside *
InsidePluginSupport_create_data_ex(RTIBool allocate_pointers){
    Inside *sample = NULL;

    RTIOsapiHeap_allocateStructure(
        &sample, Inside);

    if(sample != NULL) {
        if (!Inside_initialize_ex(sample,allocate_pointers)) {
            RTIOsapiHeap_freeStructure(&sample);
            return NULL;
        }
    }
    return sample; 
}


Inside *
InsidePluginSupport_create_data()
{
    return InsidePluginSupport_create_data_ex(RTI_TRUE);
}


void 
InsidePluginSupport_destroy_data_ex(
    Inside *sample,RTIBool deallocate_pointers) {

    Inside_finalize_ex(sample,deallocate_pointers);

    RTIOsapiHeap_freeStructure(sample);
}


void 
InsidePluginSupport_destroy_data(
    Inside *sample) {

    InsidePluginSupport_destroy_data_ex(sample,RTI_TRUE);

}


RTIBool 
InsidePluginSupport_copy_data(
    Inside *dst,
    const Inside *src)
{
    return Inside_copy(dst,src);
}


void 
InsidePluginSupport_print_data(
    const Inside *sample,
    const char *desc,
    unsigned int indent_level)
{


    RTICdrType_printIndent(indent_level);

    if (desc != NULL) {
      RTILog_debug("%s:\n", desc);
    } else {
      RTILog_debug("\n");
    }

    if (sample == NULL) {
      RTILog_debug("NULL\n");
      return;
    }


    RTICdrType_printLong(
        &sample->count, "count", indent_level + 1);
            
    RTICdrType_printArray(
        sample->ocarray, (10)*(2), RTI_CDR_OCTET_SIZE,
        (RTICdrTypePrintFunction)RTICdrType_printOctet,
        "ocarray", indent_level + 1);
            
    RTICdrType_printArray(
        sample->sharray, (10)*(2), RTI_CDR_SHORT_SIZE,
        (RTICdrTypePrintFunction)RTICdrType_printShort,
        "sharray", indent_level + 1);
            
    RTICdrType_printArray(
        sample->usharray, (10)*(2), RTI_CDR_UNSIGNED_SHORT_SIZE,
        (RTICdrTypePrintFunction)RTICdrType_printUnsignedShort,
        "usharray", indent_level + 1);
            
    RTICdrType_printArray(
        sample->loarray, (10)*(2), RTI_CDR_LONG_SIZE,
        (RTICdrTypePrintFunction)RTICdrType_printLong,
        "loarray", indent_level + 1);
            
    RTICdrType_printArray(
        sample->uloarray, (10)*(2), RTI_CDR_UNSIGNED_LONG_SIZE,
        (RTICdrTypePrintFunction)RTICdrType_printUnsignedLong,
        "uloarray", indent_level + 1);
            
    RTICdrType_printArray(
        sample->loloarray, (10)*(2), RTI_CDR_LONG_LONG_SIZE,
        (RTICdrTypePrintFunction)RTICdrType_printLongLong,
        "loloarray", indent_level + 1);
            
    RTICdrType_printArray(
        sample->uloloarray, (10)*(2), RTI_CDR_UNSIGNED_LONG_LONG_SIZE,
        (RTICdrTypePrintFunction)RTICdrType_printUnsignedLongLong,
        "uloloarray", indent_level + 1);
            
    RTICdrType_printArray(
        sample->charray, (10)*(2), RTI_CDR_CHAR_SIZE,
        (RTICdrTypePrintFunction)RTICdrType_printChar,
        "charray", indent_level + 1);
            
    RTICdrType_printArray(
        sample->flarray, (10)*(2), RTI_CDR_FLOAT_SIZE,
        (RTICdrTypePrintFunction)RTICdrType_printFloat,
        "flarray", indent_level + 1);
            
    RTICdrType_printArray(
        sample->dlarray, (10)*(2), RTI_CDR_DOUBLE_SIZE,
        (RTICdrTypePrintFunction)RTICdrType_printDouble,
        "dlarray", indent_level + 1);
            

}



/* ----------------------------------------------------------------------------
    Callback functions:
 * ---------------------------------------------------------------------------- */


PRESTypePluginParticipantData 
InsidePlugin_on_participant_attached(
    void *registration_data,
    const struct PRESTypePluginParticipantInfo *participant_info,
    RTIBool top_level_registration,
    void *container_plugin_context,
    RTICdrTypeCode *type_code)
{
    return PRESTypePluginDefaultParticipantData_new(participant_info);
}


void 
InsidePlugin_on_participant_detached(
    PRESTypePluginParticipantData participant_data)
{
  PRESTypePluginDefaultParticipantData_delete(participant_data);
}


PRESTypePluginEndpointData
InsidePlugin_on_endpoint_attached(
    PRESTypePluginParticipantData participant_data,
    const struct PRESTypePluginEndpointInfo *endpoint_info,
    RTIBool top_level_registration, 
    void *containerPluginContext)
{
    PRESTypePluginEndpointData epd = NULL;

    epd = PRESTypePluginDefaultEndpointData_new(
            participant_data,
            endpoint_info,
            (PRESTypePluginDefaultEndpointDataCreateSampleFunction)
            InsidePluginSupport_create_data,
            (PRESTypePluginDefaultEndpointDataDestroySampleFunction)
            InsidePluginSupport_destroy_data,
            NULL, NULL);
    if (epd == NULL) {
        return NULL;
    }
    
    if (endpoint_info->endpointKind == PRES_TYPEPLUGIN_ENDPOINT_WRITER) {
        if (PRESTypePluginDefaultEndpointData_createWriterPool(
                epd,
                endpoint_info,
                InsidePlugin_get_serialized_sample_max_size(epd, RTI_TRUE, 0),
            (PRESTypePluginGetSerializedSampleSizeFunction)
            InsidePlugin_get_serialized_sample_size,
            epd) == RTI_FALSE) {
            PRESTypePluginDefaultEndpointData_delete(epd);
            return NULL;
        }
    }
    return epd;    
}


void 
InsidePlugin_on_endpoint_detached(
    PRESTypePluginEndpointData endpoint_data)
{  
    PRESTypePluginDefaultEndpointData_delete(endpoint_data);
}


RTIBool 
InsidePlugin_copy_sample(
    PRESTypePluginEndpointData endpoint_data,
    Inside *dst,
    const Inside *src)
{
    return InsidePluginSupport_copy_data(dst,src);
}

/* --------------------------------------------------------------------------------------
    (De)Serialize functions:
 * -------------------------------------------------------------------------------------- */


RTIBool 
InsidePlugin_serialize(
    PRESTypePluginEndpointData endpoint_data,
    const Inside *sample, 
    struct RTICdrStream *stream,    
    RTIBool serialize_encapsulation,
    RTIBool serialize_sample, 
    void *endpoint_plugin_qos)
{
    char * position = NULL;


  if(serialize_encapsulation) {
    /* Encapsulate sample */
    if (!RTICdrStream_serializeCdrEncapsulationDefault(stream)) {
        return RTI_FALSE;
    }


    position = RTICdrStream_resetAlignment(stream);

  }

  if(serialize_sample) {

    if (!RTICdrStream_serializeLong(
        stream, &sample->count)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_serializePrimitiveArray(
        stream, (void*)sample->ocarray, (10)*(2), RTI_CDR_OCTET_TYPE)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_serializePrimitiveArray(
        stream, (void*)sample->sharray, (10)*(2), RTI_CDR_SHORT_TYPE)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_serializePrimitiveArray(
        stream, (void*)sample->usharray, (10)*(2), RTI_CDR_UNSIGNED_SHORT_TYPE)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_serializePrimitiveArray(
        stream, (void*)sample->loarray, (10)*(2), RTI_CDR_LONG_TYPE)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_serializePrimitiveArray(
        stream, (void*)sample->uloarray, (10)*(2), RTI_CDR_UNSIGNED_LONG_TYPE)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_serializePrimitiveArray(
        stream, (void*)sample->loloarray, (10)*(2), RTI_CDR_LONG_LONG_TYPE)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_serializePrimitiveArray(
        stream, (void*)sample->uloloarray, (10)*(2), RTI_CDR_UNSIGNED_LONG_LONG_TYPE)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_serializePrimitiveArray(
        stream, (void*)sample->charray, (10)*(2), RTI_CDR_CHAR_TYPE)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_serializePrimitiveArray(
        stream, (void*)sample->flarray, (10)*(2), RTI_CDR_FLOAT_TYPE)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_serializePrimitiveArray(
        stream, (void*)sample->dlarray, (10)*(2), RTI_CDR_DOUBLE_TYPE)) {
        return RTI_FALSE;
    }
            
  }


  if(serialize_encapsulation) {
    RTICdrStream_restoreAlignment(stream,position);
  }


  return RTI_TRUE;
}


RTIBool 
InsidePlugin_deserialize(
    PRESTypePluginEndpointData endpoint_data,
    Inside *sample, 
    struct RTICdrStream *stream,   
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_sample, 
    void *endpoint_plugin_qos)
{
    char * position = NULL;


    if(deserialize_encapsulation) {
        /* Deserialize encapsulation */
        if (!RTICdrStream_deserializeCdrEncapsulationAndSetDefault(stream)) {
            return RTI_FALSE;
        }


        position = RTICdrStream_resetAlignment(stream);

    }
    
    if(deserialize_sample) {

    if (!RTICdrStream_deserializeLong(
        stream, &sample->count)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_deserializePrimitiveArray(
        stream, (void*)sample->ocarray, (10)*(2), RTI_CDR_OCTET_TYPE)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_deserializePrimitiveArray(
        stream, (void*)sample->sharray, (10)*(2), RTI_CDR_SHORT_TYPE)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_deserializePrimitiveArray(
        stream, (void*)sample->usharray, (10)*(2), RTI_CDR_UNSIGNED_SHORT_TYPE)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_deserializePrimitiveArray(
        stream, (void*)sample->loarray, (10)*(2), RTI_CDR_LONG_TYPE)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_deserializePrimitiveArray(
        stream, (void*)sample->uloarray, (10)*(2), RTI_CDR_UNSIGNED_LONG_TYPE)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_deserializePrimitiveArray(
        stream, (void*)sample->loloarray, (10)*(2), RTI_CDR_LONG_LONG_TYPE)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_deserializePrimitiveArray(
        stream, (void*)sample->uloloarray, (10)*(2), RTI_CDR_UNSIGNED_LONG_LONG_TYPE)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_deserializePrimitiveArray(
        stream, (void*)sample->charray, (10)*(2), RTI_CDR_CHAR_TYPE)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_deserializePrimitiveArray(
        stream, (void*)sample->flarray, (10)*(2), RTI_CDR_FLOAT_TYPE)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_deserializePrimitiveArray(
        stream, (void*)sample->dlarray, (10)*(2), RTI_CDR_DOUBLE_TYPE)) {
        return RTI_FALSE;
    }
            
    }


    if(deserialize_encapsulation) {
        RTICdrStream_restoreAlignment(stream,position);
    }


    return RTI_TRUE;
}


RTIBool InsidePlugin_skip(
    PRESTypePluginEndpointData endpoint_data,
    struct RTICdrStream *stream,   
    RTIBool skip_encapsulation,
    RTIBool skip_sample, 
    void *endpoint_plugin_qos)
{
    char * position = NULL;


    if(skip_encapsulation) {
        if (!RTICdrStream_skipEncapsulation(stream)) {
            return RTI_FALSE;
        }


        position = RTICdrStream_resetAlignment(stream);

    }

    if (skip_sample) {

    if (!RTICdrStream_skipLong(stream)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_skipPrimitiveArray(
        stream, (10)*(2), RTI_CDR_OCTET_TYPE)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_skipPrimitiveArray(
        stream, (10)*(2), RTI_CDR_SHORT_TYPE)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_skipPrimitiveArray(
        stream, (10)*(2), RTI_CDR_UNSIGNED_SHORT_TYPE)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_skipPrimitiveArray(
        stream, (10)*(2), RTI_CDR_LONG_TYPE)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_skipPrimitiveArray(
        stream, (10)*(2), RTI_CDR_UNSIGNED_LONG_TYPE)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_skipPrimitiveArray(
        stream, (10)*(2), RTI_CDR_LONG_LONG_TYPE)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_skipPrimitiveArray(
        stream, (10)*(2), RTI_CDR_UNSIGNED_LONG_LONG_TYPE)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_skipPrimitiveArray(
        stream, (10)*(2), RTI_CDR_CHAR_TYPE)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_skipPrimitiveArray(
        stream, (10)*(2), RTI_CDR_FLOAT_TYPE)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_skipPrimitiveArray(
        stream, (10)*(2), RTI_CDR_DOUBLE_TYPE)) {
        return RTI_FALSE;
    }
            
    }


    if(skip_encapsulation) {
        RTICdrStream_restoreAlignment(stream,position);
    }


    return RTI_TRUE;
}


unsigned int 
InsidePlugin_get_serialized_sample_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    unsigned int current_alignment)
{

    unsigned int initial_alignment = current_alignment;

    unsigned int encapsulation_size = current_alignment;


    if (include_encapsulation) {

        RTICdrStream_getEncapsulationSize(encapsulation_size);
        encapsulation_size -= current_alignment;
        current_alignment = 0;
        initial_alignment = 0;

    }


    current_alignment +=  RTICdrType_getLongMaxSizeSerialized(
        current_alignment);
            
    current_alignment +=  RTICdrType_getPrimitiveArrayMaxSizeSerialized(
        current_alignment, (10)*(2), RTI_CDR_OCTET_TYPE);
            
    current_alignment +=  RTICdrType_getPrimitiveArrayMaxSizeSerialized(
        current_alignment, (10)*(2), RTI_CDR_SHORT_TYPE);
            
    current_alignment +=  RTICdrType_getPrimitiveArrayMaxSizeSerialized(
        current_alignment, (10)*(2), RTI_CDR_UNSIGNED_SHORT_TYPE);
            
    current_alignment +=  RTICdrType_getPrimitiveArrayMaxSizeSerialized(
        current_alignment, (10)*(2), RTI_CDR_LONG_TYPE);
            
    current_alignment +=  RTICdrType_getPrimitiveArrayMaxSizeSerialized(
        current_alignment, (10)*(2), RTI_CDR_UNSIGNED_LONG_TYPE);
            
    current_alignment +=  RTICdrType_getPrimitiveArrayMaxSizeSerialized(
        current_alignment, (10)*(2), RTI_CDR_LONG_LONG_TYPE);
            
    current_alignment +=  RTICdrType_getPrimitiveArrayMaxSizeSerialized(
        current_alignment, (10)*(2), RTI_CDR_UNSIGNED_LONG_LONG_TYPE);
            
    current_alignment +=  RTICdrType_getPrimitiveArrayMaxSizeSerialized(
        current_alignment, (10)*(2), RTI_CDR_CHAR_TYPE);
            
    current_alignment +=  RTICdrType_getPrimitiveArrayMaxSizeSerialized(
        current_alignment, (10)*(2), RTI_CDR_FLOAT_TYPE);
            
    current_alignment +=  RTICdrType_getPrimitiveArrayMaxSizeSerialized(
        current_alignment, (10)*(2), RTI_CDR_DOUBLE_TYPE);
            
    if (include_encapsulation) {
        current_alignment += encapsulation_size;
    }

    return current_alignment - initial_alignment;
}


unsigned int 
InsidePlugin_get_serialized_sample_min_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    unsigned int current_alignment)
{

    unsigned int initial_alignment = current_alignment;

    unsigned int encapsulation_size = current_alignment;


    if (include_encapsulation) {

        RTICdrStream_getEncapsulationSize(encapsulation_size);
        encapsulation_size -= current_alignment;
        current_alignment = 0;
        initial_alignment = 0;

    }


    current_alignment +=  RTICdrType_getLongMaxSizeSerialized(
        current_alignment);
            
    current_alignment +=  RTICdrType_getPrimitiveArrayMaxSizeSerialized(
        current_alignment, (10)*(2), RTI_CDR_OCTET_TYPE);
            
    current_alignment +=  RTICdrType_getPrimitiveArrayMaxSizeSerialized(
        current_alignment, (10)*(2), RTI_CDR_SHORT_TYPE);
            
    current_alignment +=  RTICdrType_getPrimitiveArrayMaxSizeSerialized(
        current_alignment, (10)*(2), RTI_CDR_UNSIGNED_SHORT_TYPE);
            
    current_alignment +=  RTICdrType_getPrimitiveArrayMaxSizeSerialized(
        current_alignment, (10)*(2), RTI_CDR_LONG_TYPE);
            
    current_alignment +=  RTICdrType_getPrimitiveArrayMaxSizeSerialized(
        current_alignment, (10)*(2), RTI_CDR_UNSIGNED_LONG_TYPE);
            
    current_alignment +=  RTICdrType_getPrimitiveArrayMaxSizeSerialized(
        current_alignment, (10)*(2), RTI_CDR_LONG_LONG_TYPE);
            
    current_alignment +=  RTICdrType_getPrimitiveArrayMaxSizeSerialized(
        current_alignment, (10)*(2), RTI_CDR_UNSIGNED_LONG_LONG_TYPE);
            
    current_alignment +=  RTICdrType_getPrimitiveArrayMaxSizeSerialized(
        current_alignment, (10)*(2), RTI_CDR_CHAR_TYPE);
            
    current_alignment +=  RTICdrType_getPrimitiveArrayMaxSizeSerialized(
        current_alignment, (10)*(2), RTI_CDR_FLOAT_TYPE);
            
    current_alignment +=  RTICdrType_getPrimitiveArrayMaxSizeSerialized(
        current_alignment, (10)*(2), RTI_CDR_DOUBLE_TYPE);
            
    if (include_encapsulation) {
        current_alignment += encapsulation_size;
    }

    return current_alignment - initial_alignment;
}


/* Returns the size of the sample in its serialized form (in bytes).
 * It can also be an estimation in excess of the real buffer needed 
 * during a call to the serialize() function.
 * The value reported does not have to include the space for the
 * encapsulation flags.
 */
unsigned int
InsidePlugin_get_serialized_sample_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    unsigned int size,
    const void * sample) {
    /* In the default implementation, it consider each sample as big 
     * as the largest sample.
     */
    return InsidePlugin_get_serialized_sample_max_size(
        endpoint_data,
        include_encapsulation,
        size);
}


/* --------------------------------------------------------------------------------------
    Key Management functions:
 * -------------------------------------------------------------------------------------- */


PRESTypePluginKeyKind 
InsidePlugin_get_key_kind()
{

    return PRES_TYPEPLUGIN_NO_KEY;
     
}


RTIBool 
InsidePlugin_serialize_key(
    PRESTypePluginEndpointData endpoint_data,
    const Inside *sample, 
    struct RTICdrStream *stream,    
    RTIBool serialize_encapsulation,
    RTIBool serialize_key,
    void *endpoint_plugin_qos)
{
    char * position = NULL;


    if(serialize_encapsulation) {
        /* Encapsulate sample */
        if (!RTICdrStream_serializeCdrEncapsulationDefault(stream)) {
            return RTI_FALSE;
        }


        position = RTICdrStream_resetAlignment(stream);

    }

    if(serialize_key) {

        if (!InsidePlugin_serialize(
                endpoint_data,
                sample,
                stream,
                RTI_FALSE,RTI_TRUE,
                endpoint_plugin_qos)) {
            return RTI_FALSE;
        }
    
    }


    if(serialize_encapsulation) {
        RTICdrStream_restoreAlignment(stream,position);
    }


    return RTI_TRUE;
}


RTIBool InsidePlugin_deserialize_key(
    PRESTypePluginEndpointData endpoint_data,
    Inside *sample, 
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_key,
    void *endpoint_plugin_qos)
{
    char * position = NULL;


    if(deserialize_encapsulation) {
        /* Deserialize encapsulation */
        if (!RTICdrStream_deserializeCdrEncapsulationAndSetDefault(stream)) {
            return RTI_FALSE;  
        }


        position = RTICdrStream_resetAlignment(stream);

    }

    if (deserialize_key) {

        if (!InsidePlugin_deserialize(
                endpoint_data, sample, stream,
                RTI_FALSE, RTI_TRUE, 
                endpoint_plugin_qos)) {
            return RTI_FALSE;
        }
    
    }


    if(deserialize_encapsulation) {
        RTICdrStream_restoreAlignment(stream,position);
    }


    return RTI_TRUE;
}


unsigned int
InsidePlugin_get_serialized_key_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    unsigned int current_alignment)
{

    unsigned int encapsulation_size = current_alignment;


    unsigned int initial_alignment = current_alignment;

    if (include_encapsulation) {

        RTICdrStream_getEncapsulationSize(encapsulation_size);
        encapsulation_size -= current_alignment;
        current_alignment = 0;
        initial_alignment = 0;

    }
        

    current_alignment += InsidePlugin_get_serialized_sample_max_size(
        endpoint_data,RTI_FALSE,current_alignment);
    
    if (include_encapsulation) {
        current_alignment += encapsulation_size;
    }

    return current_alignment - initial_alignment;
}


RTIBool 
InsidePlugin_serialized_sample_to_key(
    PRESTypePluginEndpointData endpoint_data,
    Inside *sample,
    struct RTICdrStream *stream, 
    RTIBool deserialize_encapsulation,  
    RTIBool deserialize_key, 
    void *endpoint_plugin_qos)
{
    char * position = NULL;


    if(deserialize_encapsulation) {
        if (!RTICdrStream_deserializeCdrEncapsulationAndSetDefault(stream)) {
            return RTI_FALSE;
        }

        position = RTICdrStream_resetAlignment(stream);

    }

    if (deserialize_key) {

        if (!InsidePlugin_deserialize(
            endpoint_data, sample, stream, RTI_FALSE, 
            RTI_TRUE, endpoint_plugin_qos)) {
            return RTI_FALSE;
        }

    }


    if(deserialize_encapsulation) {
        RTICdrStream_restoreAlignment(stream,position);
    }


    return RTI_TRUE;
}


 

/* ------------------------------------------------------------------------
 * Plug-in Installation Methods
 * ------------------------------------------------------------------------ */
 
struct PRESTypePlugin *InsidePlugin_new() 
{ 
    struct PRESTypePlugin *plugin = NULL;
    const struct PRESTypePluginVersion PLUGIN_VERSION = 
        PRES_TYPE_PLUGIN_VERSION_2_0;

    RTIOsapiHeap_allocateStructure(
        &plugin, struct PRESTypePlugin);
    if (plugin == NULL) {
       return NULL;
    }

    plugin->version = PLUGIN_VERSION;

    /* set up parent's function pointers */
    plugin->onParticipantAttached =
        (PRESTypePluginOnParticipantAttachedCallback)
        InsidePlugin_on_participant_attached;
    plugin->onParticipantDetached =
        (PRESTypePluginOnParticipantDetachedCallback)
        InsidePlugin_on_participant_detached;
    plugin->onEndpointAttached =
        (PRESTypePluginOnEndpointAttachedCallback)
        InsidePlugin_on_endpoint_attached;
    plugin->onEndpointDetached =
        (PRESTypePluginOnEndpointDetachedCallback)
        InsidePlugin_on_endpoint_detached;

    plugin->copySampleFnc =
        (PRESTypePluginCopySampleFunction)
        InsidePlugin_copy_sample;
    plugin->createSampleFnc =
        (PRESTypePluginCreateSampleFunction)
        InsidePlugin_create_sample;
    plugin->destroySampleFnc =
        (PRESTypePluginDestroySampleFunction)
        InsidePlugin_destroy_sample;

    plugin->serializeFnc =
        (PRESTypePluginSerializeFunction)
        InsidePlugin_serialize;
    plugin->deserializeFnc =
        (PRESTypePluginDeserializeFunction)
        InsidePlugin_deserialize;
    plugin->getSerializedSampleMaxSizeFnc =
        (PRESTypePluginGetSerializedSampleMaxSizeFunction)
        InsidePlugin_get_serialized_sample_max_size;
    plugin->getSerializedSampleMinSizeFnc =
        (PRESTypePluginGetSerializedSampleMinSizeFunction)
        InsidePlugin_get_serialized_sample_min_size;

    plugin->getSampleFnc =
        (PRESTypePluginGetSampleFunction)
        InsidePlugin_get_sample;
    plugin->returnSampleFnc =
        (PRESTypePluginReturnSampleFunction)
        InsidePlugin_return_sample;

    plugin->getKeyKindFnc =
        (PRESTypePluginGetKeyKindFunction)
        InsidePlugin_get_key_kind;

 
    /* These functions are only used for keyed types. As this is not a keyed
    type they are all set to NULL
    */
    plugin->serializeKeyFnc = NULL;
    plugin->deserializeKeyFnc = NULL;
    plugin->getKeyFnc = NULL;
    plugin->returnKeyFnc = NULL;
    plugin->instanceToKeyFnc = NULL;
    plugin->keyToInstanceFnc = NULL;
    plugin->getSerializedKeyMaxSizeFnc = NULL;
    plugin->instanceToKeyHashFnc = NULL;
    plugin->serializedSampleToKeyHashFnc = NULL;
    plugin->serializedKeyToKeyHashFnc = NULL;
    
    plugin->typeCode =  (struct RTICdrTypeCode *)Inside_get_typecode();
    
    plugin->languageKind = PRES_TYPEPLUGIN_DDS_TYPE; 

    /* Serialized buffer */
    plugin->getBuffer = 
        (PRESTypePluginGetBufferFunction)
        InsidePlugin_get_buffer;
    plugin->returnBuffer = 
        (PRESTypePluginReturnBufferFunction)
        InsidePlugin_return_buffer;
    plugin->getSerializedSampleSizeFnc =
        (PRESTypePluginGetSerializedSampleSizeFunction)
        InsidePlugin_get_serialized_sample_size;

    plugin->endpointTypeName = InsideTYPENAME;

    return plugin;
}

void
InsidePlugin_delete(struct PRESTypePlugin *plugin)
{
    RTIOsapiHeap_freeStructure(plugin);
} 

/* --------------------------------------------------------------------------------------
 *  Type Arrays
 * -------------------------------------------------------------------------------------- */

/* --------------------------------------------------------------------------------------
    Support functions:
 * -------------------------------------------------------------------------------------- */


Arrays *
ArraysPluginSupport_create_data_ex(RTIBool allocate_pointers){
    Arrays *sample = NULL;

    RTIOsapiHeap_allocateStructure(
        &sample, Arrays);

    if(sample != NULL) {
        if (!Arrays_initialize_ex(sample,allocate_pointers)) {
            RTIOsapiHeap_freeStructure(&sample);
            return NULL;
        }
    }
    return sample; 
}


Arrays *
ArraysPluginSupport_create_data()
{
    return ArraysPluginSupport_create_data_ex(RTI_TRUE);
}


void 
ArraysPluginSupport_destroy_data_ex(
    Arrays *sample,RTIBool deallocate_pointers) {

    Arrays_finalize_ex(sample,deallocate_pointers);

    RTIOsapiHeap_freeStructure(sample);
}


void 
ArraysPluginSupport_destroy_data(
    Arrays *sample) {

    ArraysPluginSupport_destroy_data_ex(sample,RTI_TRUE);

}


RTIBool 
ArraysPluginSupport_copy_data(
    Arrays *dst,
    const Arrays *src)
{
    return Arrays_copy(dst,src);
}


void 
ArraysPluginSupport_print_data(
    const Arrays *sample,
    const char *desc,
    unsigned int indent_level)
{


    RTICdrType_printIndent(indent_level);

    if (desc != NULL) {
      RTILog_debug("%s:\n", desc);
    } else {
      RTILog_debug("\n");
    }

    if (sample == NULL) {
      RTILog_debug("NULL\n");
      return;
    }


    if (&sample->message==NULL) {
        RTICdrType_printString(
            NULL, "message", indent_level + 1);                
    } else {
        RTICdrType_printString(
            sample->message, "message", indent_level + 1);                
    }
            
    RTICdrType_printArray(
        sample->ocarray, (20), RTI_CDR_OCTET_SIZE,
        (RTICdrTypePrintFunction)RTICdrType_printOctet,
        "ocarray", indent_level + 1);
            
    RTICdrType_printArray(
        sample->sharray, (20), RTI_CDR_SHORT_SIZE,
        (RTICdrTypePrintFunction)RTICdrType_printShort,
        "sharray", indent_level + 1);
            
    RTICdrType_printArray(
        sample->usharray, (20), RTI_CDR_UNSIGNED_SHORT_SIZE,
        (RTICdrTypePrintFunction)RTICdrType_printUnsignedShort,
        "usharray", indent_level + 1);
            
    RTICdrType_printArray(
        sample->loarray, (20), RTI_CDR_LONG_SIZE,
        (RTICdrTypePrintFunction)RTICdrType_printLong,
        "loarray", indent_level + 1);
            
    RTICdrType_printArray(
        sample->uloarray, (20), RTI_CDR_UNSIGNED_LONG_SIZE,
        (RTICdrTypePrintFunction)RTICdrType_printUnsignedLong,
        "uloarray", indent_level + 1);
            
    RTICdrType_printArray(
        sample->loloarray, (20), RTI_CDR_LONG_LONG_SIZE,
        (RTICdrTypePrintFunction)RTICdrType_printLongLong,
        "loloarray", indent_level + 1);
            
    RTICdrType_printArray(
        sample->uloloarray, (20), RTI_CDR_UNSIGNED_LONG_LONG_SIZE,
        (RTICdrTypePrintFunction)RTICdrType_printUnsignedLongLong,
        "uloloarray", indent_level + 1);
            
    RTICdrType_printArray(
        sample->charray, (20), RTI_CDR_CHAR_SIZE,
        (RTICdrTypePrintFunction)RTICdrType_printChar,
        "charray", indent_level + 1);
            
    RTICdrType_printArray(
        sample->flarray, (20), RTI_CDR_FLOAT_SIZE,
        (RTICdrTypePrintFunction)RTICdrType_printFloat,
        "flarray", indent_level + 1);
            
    RTICdrType_printArray(
        sample->dlarray, (20), RTI_CDR_DOUBLE_SIZE,
        (RTICdrTypePrintFunction)RTICdrType_printDouble,
        "dlarray", indent_level + 1);
            
    InsidePluginSupport_print_data(
        &sample->ins, "ins", indent_level + 1);
            

}



/* ----------------------------------------------------------------------------
    Callback functions:
 * ---------------------------------------------------------------------------- */


PRESTypePluginParticipantData 
ArraysPlugin_on_participant_attached(
    void *registration_data,
    const struct PRESTypePluginParticipantInfo *participant_info,
    RTIBool top_level_registration,
    void *container_plugin_context,
    RTICdrTypeCode *type_code)
{
    return PRESTypePluginDefaultParticipantData_new(participant_info);
}


void 
ArraysPlugin_on_participant_detached(
    PRESTypePluginParticipantData participant_data)
{
  PRESTypePluginDefaultParticipantData_delete(participant_data);
}


PRESTypePluginEndpointData
ArraysPlugin_on_endpoint_attached(
    PRESTypePluginParticipantData participant_data,
    const struct PRESTypePluginEndpointInfo *endpoint_info,
    RTIBool top_level_registration, 
    void *containerPluginContext)
{
    PRESTypePluginEndpointData epd = NULL;

    epd = PRESTypePluginDefaultEndpointData_new(
            participant_data,
            endpoint_info,
            (PRESTypePluginDefaultEndpointDataCreateSampleFunction)
            ArraysPluginSupport_create_data,
            (PRESTypePluginDefaultEndpointDataDestroySampleFunction)
            ArraysPluginSupport_destroy_data,
            NULL, NULL);
    if (epd == NULL) {
        return NULL;
    }
    
    if (endpoint_info->endpointKind == PRES_TYPEPLUGIN_ENDPOINT_WRITER) {
        if (PRESTypePluginDefaultEndpointData_createWriterPool(
                epd,
                endpoint_info,
                ArraysPlugin_get_serialized_sample_max_size(epd, RTI_TRUE, 0),
            (PRESTypePluginGetSerializedSampleSizeFunction)
            ArraysPlugin_get_serialized_sample_size,
            epd) == RTI_FALSE) {
            PRESTypePluginDefaultEndpointData_delete(epd);
            return NULL;
        }
    }
    return epd;    
}


void 
ArraysPlugin_on_endpoint_detached(
    PRESTypePluginEndpointData endpoint_data)
{  
    PRESTypePluginDefaultEndpointData_delete(endpoint_data);
}


RTIBool 
ArraysPlugin_copy_sample(
    PRESTypePluginEndpointData endpoint_data,
    Arrays *dst,
    const Arrays *src)
{
    return ArraysPluginSupport_copy_data(dst,src);
}

/* --------------------------------------------------------------------------------------
    (De)Serialize functions:
 * -------------------------------------------------------------------------------------- */


RTIBool 
ArraysPlugin_serialize(
    PRESTypePluginEndpointData endpoint_data,
    const Arrays *sample, 
    struct RTICdrStream *stream,    
    RTIBool serialize_encapsulation,
    RTIBool serialize_sample, 
    void *endpoint_plugin_qos)
{
    char * position = NULL;


  if(serialize_encapsulation) {
    /* Encapsulate sample */
    if (!RTICdrStream_serializeCdrEncapsulationDefault(stream)) {
        return RTI_FALSE;
    }


    position = RTICdrStream_resetAlignment(stream);

  }

  if(serialize_sample) {

    if (sample->message == NULL) {
        return RTI_FALSE;
    }
    if (!RTICdrStream_serializeString(
        stream, sample->message, (255) + 1)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_serializePrimitiveArray(
        stream, (void*)sample->ocarray, (20), RTI_CDR_OCTET_TYPE)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_serializePrimitiveArray(
        stream, (void*)sample->sharray, (20), RTI_CDR_SHORT_TYPE)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_serializePrimitiveArray(
        stream, (void*)sample->usharray, (20), RTI_CDR_UNSIGNED_SHORT_TYPE)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_serializePrimitiveArray(
        stream, (void*)sample->loarray, (20), RTI_CDR_LONG_TYPE)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_serializePrimitiveArray(
        stream, (void*)sample->uloarray, (20), RTI_CDR_UNSIGNED_LONG_TYPE)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_serializePrimitiveArray(
        stream, (void*)sample->loloarray, (20), RTI_CDR_LONG_LONG_TYPE)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_serializePrimitiveArray(
        stream, (void*)sample->uloloarray, (20), RTI_CDR_UNSIGNED_LONG_LONG_TYPE)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_serializePrimitiveArray(
        stream, (void*)sample->charray, (20), RTI_CDR_CHAR_TYPE)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_serializePrimitiveArray(
        stream, (void*)sample->flarray, (20), RTI_CDR_FLOAT_TYPE)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_serializePrimitiveArray(
        stream, (void*)sample->dlarray, (20), RTI_CDR_DOUBLE_TYPE)) {
        return RTI_FALSE;
    }
            
    if (!InsidePlugin_serialize(
            endpoint_data,
            &sample->ins, 
            stream, 
            RTI_FALSE, RTI_TRUE, 
            endpoint_plugin_qos)) {
        return RTI_FALSE;
    }
            
  }


  if(serialize_encapsulation) {
    RTICdrStream_restoreAlignment(stream,position);
  }


  return RTI_TRUE;
}


RTIBool 
ArraysPlugin_deserialize(
    PRESTypePluginEndpointData endpoint_data,
    Arrays *sample, 
    struct RTICdrStream *stream,   
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_sample, 
    void *endpoint_plugin_qos)
{
    char * position = NULL;


    if(deserialize_encapsulation) {
        /* Deserialize encapsulation */
        if (!RTICdrStream_deserializeCdrEncapsulationAndSetDefault(stream)) {
            return RTI_FALSE;
        }


        position = RTICdrStream_resetAlignment(stream);

    }
    
    if(deserialize_sample) {

    if (!RTICdrStream_deserializeString(
        stream, sample->message, (255) + 1)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_deserializePrimitiveArray(
        stream, (void*)sample->ocarray, (20), RTI_CDR_OCTET_TYPE)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_deserializePrimitiveArray(
        stream, (void*)sample->sharray, (20), RTI_CDR_SHORT_TYPE)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_deserializePrimitiveArray(
        stream, (void*)sample->usharray, (20), RTI_CDR_UNSIGNED_SHORT_TYPE)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_deserializePrimitiveArray(
        stream, (void*)sample->loarray, (20), RTI_CDR_LONG_TYPE)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_deserializePrimitiveArray(
        stream, (void*)sample->uloarray, (20), RTI_CDR_UNSIGNED_LONG_TYPE)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_deserializePrimitiveArray(
        stream, (void*)sample->loloarray, (20), RTI_CDR_LONG_LONG_TYPE)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_deserializePrimitiveArray(
        stream, (void*)sample->uloloarray, (20), RTI_CDR_UNSIGNED_LONG_LONG_TYPE)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_deserializePrimitiveArray(
        stream, (void*)sample->charray, (20), RTI_CDR_CHAR_TYPE)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_deserializePrimitiveArray(
        stream, (void*)sample->flarray, (20), RTI_CDR_FLOAT_TYPE)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_deserializePrimitiveArray(
        stream, (void*)sample->dlarray, (20), RTI_CDR_DOUBLE_TYPE)) {
        return RTI_FALSE;
    }
            
    if (!InsidePlugin_deserialize(
            endpoint_data,
            &sample->ins,
            stream, 
            RTI_FALSE, RTI_TRUE, 
            endpoint_plugin_qos)) {
        return RTI_FALSE;
    }
            
    }


    if(deserialize_encapsulation) {
        RTICdrStream_restoreAlignment(stream,position);
    }


    return RTI_TRUE;
}


RTIBool ArraysPlugin_skip(
    PRESTypePluginEndpointData endpoint_data,
    struct RTICdrStream *stream,   
    RTIBool skip_encapsulation,
    RTIBool skip_sample, 
    void *endpoint_plugin_qos)
{
    char * position = NULL;


    if(skip_encapsulation) {
        if (!RTICdrStream_skipEncapsulation(stream)) {
            return RTI_FALSE;
        }


        position = RTICdrStream_resetAlignment(stream);

    }

    if (skip_sample) {

    if (!RTICdrStream_skipString(stream, (255) + 1)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_skipPrimitiveArray(
        stream, (20), RTI_CDR_OCTET_TYPE)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_skipPrimitiveArray(
        stream, (20), RTI_CDR_SHORT_TYPE)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_skipPrimitiveArray(
        stream, (20), RTI_CDR_UNSIGNED_SHORT_TYPE)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_skipPrimitiveArray(
        stream, (20), RTI_CDR_LONG_TYPE)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_skipPrimitiveArray(
        stream, (20), RTI_CDR_UNSIGNED_LONG_TYPE)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_skipPrimitiveArray(
        stream, (20), RTI_CDR_LONG_LONG_TYPE)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_skipPrimitiveArray(
        stream, (20), RTI_CDR_UNSIGNED_LONG_LONG_TYPE)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_skipPrimitiveArray(
        stream, (20), RTI_CDR_CHAR_TYPE)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_skipPrimitiveArray(
        stream, (20), RTI_CDR_FLOAT_TYPE)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_skipPrimitiveArray(
        stream, (20), RTI_CDR_DOUBLE_TYPE)) {
        return RTI_FALSE;
    }
            
    if (!InsidePlugin_skip(
            endpoint_data,
            stream, 
            RTI_FALSE, RTI_TRUE, 
            endpoint_plugin_qos)) {
        return RTI_FALSE;
    }
            
    }


    if(skip_encapsulation) {
        RTICdrStream_restoreAlignment(stream,position);
    }


    return RTI_TRUE;
}


unsigned int 
ArraysPlugin_get_serialized_sample_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    unsigned int current_alignment)
{

    unsigned int initial_alignment = current_alignment;

    unsigned int encapsulation_size = current_alignment;


    if (include_encapsulation) {

        RTICdrStream_getEncapsulationSize(encapsulation_size);
        encapsulation_size -= current_alignment;
        current_alignment = 0;
        initial_alignment = 0;

    }


    current_alignment +=  RTICdrType_getStringMaxSizeSerialized(
        current_alignment, (255) + 1);
            
    current_alignment +=  RTICdrType_getPrimitiveArrayMaxSizeSerialized(
        current_alignment, (20), RTI_CDR_OCTET_TYPE);
            
    current_alignment +=  RTICdrType_getPrimitiveArrayMaxSizeSerialized(
        current_alignment, (20), RTI_CDR_SHORT_TYPE);
            
    current_alignment +=  RTICdrType_getPrimitiveArrayMaxSizeSerialized(
        current_alignment, (20), RTI_CDR_UNSIGNED_SHORT_TYPE);
            
    current_alignment +=  RTICdrType_getPrimitiveArrayMaxSizeSerialized(
        current_alignment, (20), RTI_CDR_LONG_TYPE);
            
    current_alignment +=  RTICdrType_getPrimitiveArrayMaxSizeSerialized(
        current_alignment, (20), RTI_CDR_UNSIGNED_LONG_TYPE);
            
    current_alignment +=  RTICdrType_getPrimitiveArrayMaxSizeSerialized(
        current_alignment, (20), RTI_CDR_LONG_LONG_TYPE);
            
    current_alignment +=  RTICdrType_getPrimitiveArrayMaxSizeSerialized(
        current_alignment, (20), RTI_CDR_UNSIGNED_LONG_LONG_TYPE);
            
    current_alignment +=  RTICdrType_getPrimitiveArrayMaxSizeSerialized(
        current_alignment, (20), RTI_CDR_CHAR_TYPE);
            
    current_alignment +=  RTICdrType_getPrimitiveArrayMaxSizeSerialized(
        current_alignment, (20), RTI_CDR_FLOAT_TYPE);
            
    current_alignment +=  RTICdrType_getPrimitiveArrayMaxSizeSerialized(
        current_alignment, (20), RTI_CDR_DOUBLE_TYPE);
            
    current_alignment +=  InsidePlugin_get_serialized_sample_max_size(
        endpoint_data,RTI_FALSE,current_alignment);
            
    if (include_encapsulation) {
        current_alignment += encapsulation_size;
    }

    return current_alignment - initial_alignment;
}


unsigned int 
ArraysPlugin_get_serialized_sample_min_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    unsigned int current_alignment)
{

    unsigned int initial_alignment = current_alignment;

    unsigned int encapsulation_size = current_alignment;


    if (include_encapsulation) {

        RTICdrStream_getEncapsulationSize(encapsulation_size);
        encapsulation_size -= current_alignment;
        current_alignment = 0;
        initial_alignment = 0;

    }


    current_alignment +=  RTICdrType_getStringMaxSizeSerialized(
        current_alignment, 1);
            
    current_alignment +=  RTICdrType_getPrimitiveArrayMaxSizeSerialized(
        current_alignment, (20), RTI_CDR_OCTET_TYPE);
            
    current_alignment +=  RTICdrType_getPrimitiveArrayMaxSizeSerialized(
        current_alignment, (20), RTI_CDR_SHORT_TYPE);
            
    current_alignment +=  RTICdrType_getPrimitiveArrayMaxSizeSerialized(
        current_alignment, (20), RTI_CDR_UNSIGNED_SHORT_TYPE);
            
    current_alignment +=  RTICdrType_getPrimitiveArrayMaxSizeSerialized(
        current_alignment, (20), RTI_CDR_LONG_TYPE);
            
    current_alignment +=  RTICdrType_getPrimitiveArrayMaxSizeSerialized(
        current_alignment, (20), RTI_CDR_UNSIGNED_LONG_TYPE);
            
    current_alignment +=  RTICdrType_getPrimitiveArrayMaxSizeSerialized(
        current_alignment, (20), RTI_CDR_LONG_LONG_TYPE);
            
    current_alignment +=  RTICdrType_getPrimitiveArrayMaxSizeSerialized(
        current_alignment, (20), RTI_CDR_UNSIGNED_LONG_LONG_TYPE);
            
    current_alignment +=  RTICdrType_getPrimitiveArrayMaxSizeSerialized(
        current_alignment, (20), RTI_CDR_CHAR_TYPE);
            
    current_alignment +=  RTICdrType_getPrimitiveArrayMaxSizeSerialized(
        current_alignment, (20), RTI_CDR_FLOAT_TYPE);
            
    current_alignment +=  RTICdrType_getPrimitiveArrayMaxSizeSerialized(
        current_alignment, (20), RTI_CDR_DOUBLE_TYPE);
            
    current_alignment +=  InsidePlugin_get_serialized_sample_min_size(
        endpoint_data,RTI_FALSE,current_alignment);
            
    if (include_encapsulation) {
        current_alignment += encapsulation_size;
    }

    return current_alignment - initial_alignment;
}


/* Returns the size of the sample in its serialized form (in bytes).
 * It can also be an estimation in excess of the real buffer needed 
 * during a call to the serialize() function.
 * The value reported does not have to include the space for the
 * encapsulation flags.
 */
unsigned int
ArraysPlugin_get_serialized_sample_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    unsigned int size,
    const void * sample) {
    /* In the default implementation, it consider each sample as big 
     * as the largest sample.
     */
    return ArraysPlugin_get_serialized_sample_max_size(
        endpoint_data,
        include_encapsulation,
        size);
}


/* --------------------------------------------------------------------------------------
    Key Management functions:
 * -------------------------------------------------------------------------------------- */


PRESTypePluginKeyKind 
ArraysPlugin_get_key_kind()
{

    return PRES_TYPEPLUGIN_NO_KEY;
     
}


RTIBool 
ArraysPlugin_serialize_key(
    PRESTypePluginEndpointData endpoint_data,
    const Arrays *sample, 
    struct RTICdrStream *stream,    
    RTIBool serialize_encapsulation,
    RTIBool serialize_key,
    void *endpoint_plugin_qos)
{
    char * position = NULL;


    if(serialize_encapsulation) {
        /* Encapsulate sample */
        if (!RTICdrStream_serializeCdrEncapsulationDefault(stream)) {
            return RTI_FALSE;
        }


        position = RTICdrStream_resetAlignment(stream);

    }

    if(serialize_key) {

        if (!ArraysPlugin_serialize(
                endpoint_data,
                sample,
                stream,
                RTI_FALSE,RTI_TRUE,
                endpoint_plugin_qos)) {
            return RTI_FALSE;
        }
    
    }


    if(serialize_encapsulation) {
        RTICdrStream_restoreAlignment(stream,position);
    }


    return RTI_TRUE;
}


RTIBool ArraysPlugin_deserialize_key(
    PRESTypePluginEndpointData endpoint_data,
    Arrays *sample, 
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_key,
    void *endpoint_plugin_qos)
{
    char * position = NULL;


    if(deserialize_encapsulation) {
        /* Deserialize encapsulation */
        if (!RTICdrStream_deserializeCdrEncapsulationAndSetDefault(stream)) {
            return RTI_FALSE;  
        }


        position = RTICdrStream_resetAlignment(stream);

    }

    if (deserialize_key) {

        if (!ArraysPlugin_deserialize(
                endpoint_data, sample, stream,
                RTI_FALSE, RTI_TRUE, 
                endpoint_plugin_qos)) {
            return RTI_FALSE;
        }
    
    }


    if(deserialize_encapsulation) {
        RTICdrStream_restoreAlignment(stream,position);
    }


    return RTI_TRUE;
}


unsigned int
ArraysPlugin_get_serialized_key_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    unsigned int current_alignment)
{

    unsigned int encapsulation_size = current_alignment;


    unsigned int initial_alignment = current_alignment;

    if (include_encapsulation) {

        RTICdrStream_getEncapsulationSize(encapsulation_size);
        encapsulation_size -= current_alignment;
        current_alignment = 0;
        initial_alignment = 0;

    }
        

    current_alignment += ArraysPlugin_get_serialized_sample_max_size(
        endpoint_data,RTI_FALSE,current_alignment);
    
    if (include_encapsulation) {
        current_alignment += encapsulation_size;
    }

    return current_alignment - initial_alignment;
}


RTIBool 
ArraysPlugin_serialized_sample_to_key(
    PRESTypePluginEndpointData endpoint_data,
    Arrays *sample,
    struct RTICdrStream *stream, 
    RTIBool deserialize_encapsulation,  
    RTIBool deserialize_key, 
    void *endpoint_plugin_qos)
{
    char * position = NULL;


    if(deserialize_encapsulation) {
        if (!RTICdrStream_deserializeCdrEncapsulationAndSetDefault(stream)) {
            return RTI_FALSE;
        }

        position = RTICdrStream_resetAlignment(stream);

    }

    if (deserialize_key) {

        if (!ArraysPlugin_deserialize(
            endpoint_data, sample, stream, RTI_FALSE, 
            RTI_TRUE, endpoint_plugin_qos)) {
            return RTI_FALSE;
        }

    }


    if(deserialize_encapsulation) {
        RTICdrStream_restoreAlignment(stream,position);
    }


    return RTI_TRUE;
}


 

/* ------------------------------------------------------------------------
 * Plug-in Installation Methods
 * ------------------------------------------------------------------------ */
 
struct PRESTypePlugin *ArraysPlugin_new() 
{ 
    struct PRESTypePlugin *plugin = NULL;
    const struct PRESTypePluginVersion PLUGIN_VERSION = 
        PRES_TYPE_PLUGIN_VERSION_2_0;

    RTIOsapiHeap_allocateStructure(
        &plugin, struct PRESTypePlugin);
    if (plugin == NULL) {
       return NULL;
    }

    plugin->version = PLUGIN_VERSION;

    /* set up parent's function pointers */
    plugin->onParticipantAttached =
        (PRESTypePluginOnParticipantAttachedCallback)
        ArraysPlugin_on_participant_attached;
    plugin->onParticipantDetached =
        (PRESTypePluginOnParticipantDetachedCallback)
        ArraysPlugin_on_participant_detached;
    plugin->onEndpointAttached =
        (PRESTypePluginOnEndpointAttachedCallback)
        ArraysPlugin_on_endpoint_attached;
    plugin->onEndpointDetached =
        (PRESTypePluginOnEndpointDetachedCallback)
        ArraysPlugin_on_endpoint_detached;

    plugin->copySampleFnc =
        (PRESTypePluginCopySampleFunction)
        ArraysPlugin_copy_sample;
    plugin->createSampleFnc =
        (PRESTypePluginCreateSampleFunction)
        ArraysPlugin_create_sample;
    plugin->destroySampleFnc =
        (PRESTypePluginDestroySampleFunction)
        ArraysPlugin_destroy_sample;

    plugin->serializeFnc =
        (PRESTypePluginSerializeFunction)
        ArraysPlugin_serialize;
    plugin->deserializeFnc =
        (PRESTypePluginDeserializeFunction)
        ArraysPlugin_deserialize;
    plugin->getSerializedSampleMaxSizeFnc =
        (PRESTypePluginGetSerializedSampleMaxSizeFunction)
        ArraysPlugin_get_serialized_sample_max_size;
    plugin->getSerializedSampleMinSizeFnc =
        (PRESTypePluginGetSerializedSampleMinSizeFunction)
        ArraysPlugin_get_serialized_sample_min_size;

    plugin->getSampleFnc =
        (PRESTypePluginGetSampleFunction)
        ArraysPlugin_get_sample;
    plugin->returnSampleFnc =
        (PRESTypePluginReturnSampleFunction)
        ArraysPlugin_return_sample;

    plugin->getKeyKindFnc =
        (PRESTypePluginGetKeyKindFunction)
        ArraysPlugin_get_key_kind;

 
    /* These functions are only used for keyed types. As this is not a keyed
    type they are all set to NULL
    */
    plugin->serializeKeyFnc = NULL;
    plugin->deserializeKeyFnc = NULL;
    plugin->getKeyFnc = NULL;
    plugin->returnKeyFnc = NULL;
    plugin->instanceToKeyFnc = NULL;
    plugin->keyToInstanceFnc = NULL;
    plugin->getSerializedKeyMaxSizeFnc = NULL;
    plugin->instanceToKeyHashFnc = NULL;
    plugin->serializedSampleToKeyHashFnc = NULL;
    plugin->serializedKeyToKeyHashFnc = NULL;
    
    plugin->typeCode =  (struct RTICdrTypeCode *)Arrays_get_typecode();
    
    plugin->languageKind = PRES_TYPEPLUGIN_DDS_TYPE; 

    /* Serialized buffer */
    plugin->getBuffer = 
        (PRESTypePluginGetBufferFunction)
        ArraysPlugin_get_buffer;
    plugin->returnBuffer = 
        (PRESTypePluginReturnBufferFunction)
        ArraysPlugin_return_buffer;
    plugin->getSerializedSampleSizeFnc =
        (PRESTypePluginGetSerializedSampleSizeFunction)
        ArraysPlugin_get_serialized_sample_size;

    plugin->endpointTypeName = ArraysTYPENAME;

    return plugin;
}

void
ArraysPlugin_delete(struct PRESTypePlugin *plugin)
{
    RTIOsapiHeap_freeStructure(plugin);
} 
