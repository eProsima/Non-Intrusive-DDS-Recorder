
/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from Enums.idl using "rtiddsgen".
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



#ifndef EnumsPlugin_h
#include "EnumsPlugin.h"
#endif



/* ------------------------------------------------------------------------
   Enum Type: Enumerado
 * ------------------------------------------------------------------------- */
 
/* ------------------------------------------------------------------------
 * (De)Serialization Methods
 * ------------------------------------------------------------------------ */


RTIBool EnumeradoPlugin_serialize(
    PRESTypePluginEndpointData endpoint_data,
    const Enumerado *sample,
    struct RTICdrStream *stream, 
    RTIBool serialize_encapsulation,
    RTIBool serialize_sample,
    void *endpoint_plugin_qos)
{
    char * position = NULL;


    if(serialize_encapsulation) {
        if (!RTICdrStream_serializeCdrEncapsulationDefault(stream)) {
            return RTI_FALSE;
        }


        position = RTICdrStream_resetAlignment(stream);

    }

    if(serialize_sample) {

        if (!RTICdrStream_serializeEnum(stream, sample))
        {
            return RTI_FALSE;
        }

    }


    if(serialize_encapsulation) {
        RTICdrStream_restoreAlignment(stream,position);
    }


    return RTI_TRUE;
}


RTIBool 
EnumeradoPlugin_deserialize(
    PRESTypePluginEndpointData endpoint_data,
    Enumerado *sample,
    struct RTICdrStream *stream, 
    RTIBool deserialize_encapsulation,  
    RTIBool deserialize_sample, 
    void *endpoint_plugin_qos)
{
    char * position = NULL;

    if(deserialize_encapsulation) {
        if (!RTICdrStream_deserializeCdrEncapsulationAndSetDefault(stream)) {
            return RTI_FALSE;
        }


        position = RTICdrStream_resetAlignment(stream);

    }

    if(deserialize_sample) {

        if (!RTICdrStream_deserializeEnum(stream, sample))
        {
            return RTI_FALSE;
        } 

    }


    if(deserialize_encapsulation) {
        RTICdrStream_restoreAlignment(stream,position);
    }


    return RTI_TRUE;
}


RTIBool EnumeradoPlugin_skip(
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

    if(skip_sample) {

        if (!RTICdrStream_skipEnum(stream)) {
            return RTI_FALSE;
        }


    }


    if(skip_encapsulation) {
        RTICdrStream_restoreAlignment(stream,position);
    }


    return RTI_TRUE;
}


unsigned int EnumeradoPlugin_get_serialized_sample_max_size(
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

    current_alignment += RTICdrType_getEnumMaxSizeSerialized(current_alignment);


    if (include_encapsulation) {
        current_alignment += encapsulation_size;
    }


    return current_alignment - initial_alignment;
}


unsigned int EnumeradoPlugin_get_serialized_sample_min_size(
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

    current_alignment += RTICdrType_getEnumMaxSizeSerialized(current_alignment);


    if (include_encapsulation) {
        current_alignment += encapsulation_size;
    }


    return current_alignment - initial_alignment;
}


/* ------------------------------------------------------------------------
    Key Management functions:
 * ------------------------------------------------------------------------ */


RTIBool EnumeradoPlugin_serialize_key(
    PRESTypePluginEndpointData endpoint_data,
    const Enumerado *sample, 
    struct RTICdrStream *stream, 
    RTIBool serialize_encapsulation,
    RTIBool serialize_key,
    void *endpoint_plugin_qos)
{   
    return EnumeradoPlugin_serialize(
            endpoint_data, sample, stream, serialize_encapsulation, 
            serialize_key, endpoint_plugin_qos);
}


RTIBool EnumeradoPlugin_deserialize_key(
    PRESTypePluginEndpointData endpoint_data,
    Enumerado *sample,
    struct RTICdrStream *stream, 
    RTIBool deserialize_encapsulation,  
    RTIBool deserialize_key, 
    void *endpoint_plugin_qos)
{   
    return EnumeradoPlugin_deserialize(
            endpoint_data, sample, stream, deserialize_encapsulation, 
            deserialize_key, endpoint_plugin_qos);
}


unsigned int EnumeradoPlugin_get_serialized_key_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    unsigned int current_alignment)
{
    unsigned int initial_alignment = current_alignment;

    current_alignment += EnumeradoPlugin_get_serialized_sample_max_size(
        endpoint_data,include_encapsulation,current_alignment);

    return current_alignment - initial_alignment;
}


RTIBool 
EnumeradoPlugin_serialized_sample_to_key(
    PRESTypePluginEndpointData endpoint_data,
    Enumerado *sample,
    struct RTICdrStream *stream, 
    RTIBool deserialize_encapsulation,  
    RTIBool deserialize_key, 
    void *endpoint_plugin_qos)
{    
    return EnumeradoPlugin_deserialize(
            endpoint_data, sample, stream, deserialize_encapsulation, 
            deserialize_key, endpoint_plugin_qos);
}

/* ----------------------------------------------------------------------------
    Support functions:
 * ---------------------------------------------------------------------------- */


void EnumeradoPluginSupport_print_data(
    const Enumerado *sample,
    const char *description, int indent_level)
{
    if (description != NULL) {
        RTICdrType_printIndent(indent_level);
        RTILog_debug("%s:\n", description);
    }

    if (sample == NULL) {
        RTICdrType_printIndent(indent_level+1);
        RTILog_debug("NULL\n");
        return;
    }

    RTICdrType_printEnum((RTICdrEnum *)sample, "Enumerado", indent_level + 1);
}



/* --------------------------------------------------------------------------------------
 *  Type Enums
 * -------------------------------------------------------------------------------------- */

/* --------------------------------------------------------------------------------------
    Support functions:
 * -------------------------------------------------------------------------------------- */


Enums *
EnumsPluginSupport_create_data_ex(RTIBool allocate_pointers){
    Enums *sample = NULL;

    RTIOsapiHeap_allocateStructure(
        &sample, Enums);

    if(sample != NULL) {
        if (!Enums_initialize_ex(sample,allocate_pointers)) {
            RTIOsapiHeap_freeStructure(&sample);
            return NULL;
        }
    }
    return sample; 
}


Enums *
EnumsPluginSupport_create_data()
{
    return EnumsPluginSupport_create_data_ex(RTI_TRUE);
}


void 
EnumsPluginSupport_destroy_data_ex(
    Enums *sample,RTIBool deallocate_pointers) {

    Enums_finalize_ex(sample,deallocate_pointers);

    RTIOsapiHeap_freeStructure(sample);
}


void 
EnumsPluginSupport_destroy_data(
    Enums *sample) {

    EnumsPluginSupport_destroy_data_ex(sample,RTI_TRUE);

}


RTIBool 
EnumsPluginSupport_copy_data(
    Enums *dst,
    const Enums *src)
{
    return Enums_copy(dst,src);
}


void 
EnumsPluginSupport_print_data(
    const Enums *sample,
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
            
    EnumeradoPluginSupport_print_data(
        &sample->en, "en", indent_level + 1);
            
    RTICdrType_printArray(
        sample->aren, (10), sizeof(Enumerado),
        (RTICdrTypePrintFunction)EnumeradoPluginSupport_print_data,
        "aren", indent_level + 1);
            
    if (&sample->seen == NULL) {
        RTICdrType_printIndent(indent_level+1);
        RTILog_debug("seen: NULL\n");    
    } else {
                
        if (EnumeradoSeq_get_contiguous_bufferI(&sample->seen) != NULL) {
            RTICdrType_printArray(
                EnumeradoSeq_get_contiguous_bufferI(&sample->seen), 
                EnumeradoSeq_get_length(&sample->seen),
                sizeof(Enumerado),
                (RTICdrTypePrintFunction)EnumeradoPluginSupport_print_data,
                "seen", indent_level + 1);
        } else {
            RTICdrType_printPointerArray(
                EnumeradoSeq_get_discontiguous_bufferI(&sample->seen), 
                EnumeradoSeq_get_length(&sample->seen),
                (RTICdrTypePrintFunction)EnumeradoPluginSupport_print_data,
                "seen", indent_level + 1);
        }
    
    }
            

}



/* ----------------------------------------------------------------------------
    Callback functions:
 * ---------------------------------------------------------------------------- */


PRESTypePluginParticipantData 
EnumsPlugin_on_participant_attached(
    void *registration_data,
    const struct PRESTypePluginParticipantInfo *participant_info,
    RTIBool top_level_registration,
    void *container_plugin_context,
    RTICdrTypeCode *type_code)
{
    return PRESTypePluginDefaultParticipantData_new(participant_info);
}


void 
EnumsPlugin_on_participant_detached(
    PRESTypePluginParticipantData participant_data)
{
  PRESTypePluginDefaultParticipantData_delete(participant_data);
}


PRESTypePluginEndpointData
EnumsPlugin_on_endpoint_attached(
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
            EnumsPluginSupport_create_data,
            (PRESTypePluginDefaultEndpointDataDestroySampleFunction)
            EnumsPluginSupport_destroy_data,
            NULL, NULL);
    if (epd == NULL) {
        return NULL;
    }
    
    if (endpoint_info->endpointKind == PRES_TYPEPLUGIN_ENDPOINT_WRITER) {
        if (PRESTypePluginDefaultEndpointData_createWriterPool(
                epd,
                endpoint_info,
                EnumsPlugin_get_serialized_sample_max_size(epd, RTI_TRUE, 0),
            (PRESTypePluginGetSerializedSampleSizeFunction)
            EnumsPlugin_get_serialized_sample_size,
            epd) == RTI_FALSE) {
            PRESTypePluginDefaultEndpointData_delete(epd);
            return NULL;
        }
    }
    return epd;    
}


void 
EnumsPlugin_on_endpoint_detached(
    PRESTypePluginEndpointData endpoint_data)
{  
    PRESTypePluginDefaultEndpointData_delete(endpoint_data);
}


RTIBool 
EnumsPlugin_copy_sample(
    PRESTypePluginEndpointData endpoint_data,
    Enums *dst,
    const Enums *src)
{
    return EnumsPluginSupport_copy_data(dst,src);
}

/* --------------------------------------------------------------------------------------
    (De)Serialize functions:
 * -------------------------------------------------------------------------------------- */


RTIBool 
EnumsPlugin_serialize(
    PRESTypePluginEndpointData endpoint_data,
    const Enums *sample, 
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
            
    if (!EnumeradoPlugin_serialize(
            endpoint_data,
            &sample->en, 
            stream, 
            RTI_FALSE, RTI_TRUE, 
            endpoint_plugin_qos)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_serializeNonPrimitiveArray(
        stream, (void*)sample->aren,
        (10), sizeof(Enumerado),
        (RTICdrStreamSerializeFunction)EnumeradoPlugin_serialize,
        RTI_FALSE,RTI_TRUE,
        endpoint_data,endpoint_plugin_qos)) {
        return RTI_FALSE;
    }
            
    if (EnumeradoSeq_get_contiguous_bufferI(&sample->seen) != NULL) {
        if (!RTICdrStream_serializeNonPrimitiveSequence(
            stream,
            EnumeradoSeq_get_contiguous_bufferI(&sample->seen),
            EnumeradoSeq_get_length(&sample->seen),
            (100),
            sizeof(Enumerado),
            (RTICdrStreamSerializeFunction)EnumeradoPlugin_serialize,
            RTI_FALSE,RTI_TRUE,
            endpoint_data,endpoint_plugin_qos)) {
            return RTI_FALSE;
        }
    } else {
        if (!RTICdrStream_serializeNonPrimitivePointerSequence(
            stream,
            (const void **)EnumeradoSeq_get_discontiguous_bufferI(&sample->seen),
            EnumeradoSeq_get_length(&sample->seen),
            (100),
            (RTICdrStreamSerializeFunction)EnumeradoPlugin_serialize,
            RTI_FALSE,RTI_TRUE,
            endpoint_data,endpoint_plugin_qos)) {
            return RTI_FALSE;
        }
    }
            
  }


  if(serialize_encapsulation) {
    RTICdrStream_restoreAlignment(stream,position);
  }


  return RTI_TRUE;
}


RTIBool 
EnumsPlugin_deserialize(
    PRESTypePluginEndpointData endpoint_data,
    Enums *sample, 
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
            
    if (!EnumeradoPlugin_deserialize(
            endpoint_data,
            &sample->en,
            stream, 
            RTI_FALSE, RTI_TRUE, 
            endpoint_plugin_qos)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_deserializeNonPrimitiveArray(
        stream, (void*)sample->aren,
        (10), sizeof(Enumerado),
        (RTICdrStreamDeserializeFunction)EnumeradoPlugin_deserialize,
        RTI_FALSE,RTI_TRUE,
        endpoint_data,endpoint_plugin_qos)) {
        return RTI_FALSE;
    }
            
    {
        RTICdrUnsignedLong sequence_length;

        if (EnumeradoSeq_get_contiguous_bufferI(&sample->seen) != NULL) {
            if (!RTICdrStream_deserializeNonPrimitiveSequence(
                stream,
                EnumeradoSeq_get_contiguous_bufferI(&sample->seen),
                &sequence_length,
                EnumeradoSeq_get_maximum(&sample->seen),
                sizeof(Enumerado),
                (RTICdrStreamDeserializeFunction)EnumeradoPlugin_deserialize,
                RTI_FALSE,RTI_TRUE,
                endpoint_data,endpoint_plugin_qos)) {
                return RTI_FALSE;
            }
        } else {
            if (!RTICdrStream_deserializeNonPrimitivePointerSequence(
                stream,
                (void **)EnumeradoSeq_get_discontiguous_bufferI(&sample->seen),
                &sequence_length,
                EnumeradoSeq_get_maximum(&sample->seen),
                (RTICdrStreamDeserializeFunction)EnumeradoPlugin_deserialize,
                RTI_FALSE,RTI_TRUE,
                endpoint_data,endpoint_plugin_qos)) {
                return RTI_FALSE;
            }
        }
        if (!EnumeradoSeq_set_length(
            &sample->seen, sequence_length)) {
            return RTI_FALSE;
        }
    }
            
    }


    if(deserialize_encapsulation) {
        RTICdrStream_restoreAlignment(stream,position);
    }


    return RTI_TRUE;
}


RTIBool EnumsPlugin_skip(
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
            
    if (!EnumeradoPlugin_skip(
            endpoint_data,
            stream, 
            RTI_FALSE, RTI_TRUE, 
            endpoint_plugin_qos)) {
        return RTI_FALSE;
    }
            
    if (!RTICdrStream_skipNonPrimitiveArray(
        stream, (10), sizeof(Enumerado),
        (RTICdrStreamSkipFunction)EnumeradoPlugin_skip, 
        RTI_FALSE,RTI_TRUE,
        endpoint_data,endpoint_plugin_qos)) {
        return RTI_FALSE;
    }
            
    {
        RTICdrUnsignedLong sequence_length;

        if (!RTICdrStream_skipNonPrimitiveSequence(
            stream,
            &sequence_length,
            sizeof(Enumerado),
            (RTICdrStreamSkipFunction)EnumeradoPlugin_skip,
            RTI_FALSE,RTI_TRUE,
            endpoint_data,endpoint_plugin_qos)) {
            return RTI_FALSE;
        }
    }
            
    }


    if(skip_encapsulation) {
        RTICdrStream_restoreAlignment(stream,position);
    }


    return RTI_TRUE;
}


unsigned int 
EnumsPlugin_get_serialized_sample_max_size(
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
            
    current_alignment +=  EnumeradoPlugin_get_serialized_sample_max_size(
        endpoint_data,RTI_FALSE,current_alignment);
            
    current_alignment +=  RTICdrType_getNonPrimitiveArrayMaxSizeSerialized(
        current_alignment, (10),
        EnumeradoPlugin_get_serialized_sample_max_size,RTI_FALSE,endpoint_data);
            
    current_alignment +=  RTICdrType_getNonPrimitiveSequenceMaxSizeSerialized(
        current_alignment, (100),
        EnumeradoPlugin_get_serialized_sample_max_size,RTI_FALSE,endpoint_data);
            
    if (include_encapsulation) {
        current_alignment += encapsulation_size;
    }

    return current_alignment - initial_alignment;
}


unsigned int 
EnumsPlugin_get_serialized_sample_min_size(
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
            
    current_alignment +=  EnumeradoPlugin_get_serialized_sample_min_size(
        endpoint_data,RTI_FALSE,current_alignment);
            
    current_alignment +=  RTICdrType_getNonPrimitiveArrayMaxSizeSerialized(
        current_alignment, (10),
        EnumeradoPlugin_get_serialized_sample_min_size,RTI_FALSE,endpoint_data);
            
    current_alignment +=  RTICdrType_getNonPrimitiveSequenceMaxSizeSerialized(
        current_alignment, 0,
        EnumeradoPlugin_get_serialized_sample_min_size,RTI_FALSE,endpoint_data);
            
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
EnumsPlugin_get_serialized_sample_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    unsigned int size,
    const void * sample) {
    /* In the default implementation, it consider each sample as big 
     * as the largest sample.
     */
    return EnumsPlugin_get_serialized_sample_max_size(
        endpoint_data,
        include_encapsulation,
        size);
}


/* --------------------------------------------------------------------------------------
    Key Management functions:
 * -------------------------------------------------------------------------------------- */


PRESTypePluginKeyKind 
EnumsPlugin_get_key_kind()
{

    return PRES_TYPEPLUGIN_NO_KEY;
     
}


RTIBool 
EnumsPlugin_serialize_key(
    PRESTypePluginEndpointData endpoint_data,
    const Enums *sample, 
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

        if (!EnumsPlugin_serialize(
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


RTIBool EnumsPlugin_deserialize_key(
    PRESTypePluginEndpointData endpoint_data,
    Enums *sample, 
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

        if (!EnumsPlugin_deserialize(
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
EnumsPlugin_get_serialized_key_max_size(
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
        

    current_alignment += EnumsPlugin_get_serialized_sample_max_size(
        endpoint_data,RTI_FALSE,current_alignment);
    
    if (include_encapsulation) {
        current_alignment += encapsulation_size;
    }

    return current_alignment - initial_alignment;
}


RTIBool 
EnumsPlugin_serialized_sample_to_key(
    PRESTypePluginEndpointData endpoint_data,
    Enums *sample,
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

        if (!EnumsPlugin_deserialize(
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
 
struct PRESTypePlugin *EnumsPlugin_new() 
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
        EnumsPlugin_on_participant_attached;
    plugin->onParticipantDetached =
        (PRESTypePluginOnParticipantDetachedCallback)
        EnumsPlugin_on_participant_detached;
    plugin->onEndpointAttached =
        (PRESTypePluginOnEndpointAttachedCallback)
        EnumsPlugin_on_endpoint_attached;
    plugin->onEndpointDetached =
        (PRESTypePluginOnEndpointDetachedCallback)
        EnumsPlugin_on_endpoint_detached;

    plugin->copySampleFnc =
        (PRESTypePluginCopySampleFunction)
        EnumsPlugin_copy_sample;
    plugin->createSampleFnc =
        (PRESTypePluginCreateSampleFunction)
        EnumsPlugin_create_sample;
    plugin->destroySampleFnc =
        (PRESTypePluginDestroySampleFunction)
        EnumsPlugin_destroy_sample;

    plugin->serializeFnc =
        (PRESTypePluginSerializeFunction)
        EnumsPlugin_serialize;
    plugin->deserializeFnc =
        (PRESTypePluginDeserializeFunction)
        EnumsPlugin_deserialize;
    plugin->getSerializedSampleMaxSizeFnc =
        (PRESTypePluginGetSerializedSampleMaxSizeFunction)
        EnumsPlugin_get_serialized_sample_max_size;
    plugin->getSerializedSampleMinSizeFnc =
        (PRESTypePluginGetSerializedSampleMinSizeFunction)
        EnumsPlugin_get_serialized_sample_min_size;

    plugin->getSampleFnc =
        (PRESTypePluginGetSampleFunction)
        EnumsPlugin_get_sample;
    plugin->returnSampleFnc =
        (PRESTypePluginReturnSampleFunction)
        EnumsPlugin_return_sample;

    plugin->getKeyKindFnc =
        (PRESTypePluginGetKeyKindFunction)
        EnumsPlugin_get_key_kind;

 
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
    
    plugin->typeCode =  (struct RTICdrTypeCode *)Enums_get_typecode();
    
    plugin->languageKind = PRES_TYPEPLUGIN_DDS_TYPE; 

    /* Serialized buffer */
    plugin->getBuffer = 
        (PRESTypePluginGetBufferFunction)
        EnumsPlugin_get_buffer;
    plugin->returnBuffer = 
        (PRESTypePluginReturnBufferFunction)
        EnumsPlugin_return_buffer;
    plugin->getSerializedSampleSizeFnc =
        (PRESTypePluginGetSerializedSampleSizeFunction)
        EnumsPlugin_get_serialized_sample_size;

    plugin->endpointTypeName = EnumsTYPENAME;

    return plugin;
}

void
EnumsPlugin_delete(struct PRESTypePlugin *plugin)
{
    RTIOsapiHeap_freeStructure(plugin);
} 
