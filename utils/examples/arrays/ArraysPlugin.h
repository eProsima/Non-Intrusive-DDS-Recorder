
/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from Arrays.idl using "rtiddsgen".
  The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
  For more information, type 'rtiddsgen -help' at a command shell
  or consult the RTI Data Distribution Service manual.
*/

#ifndef ArraysPlugin_h
#define ArraysPlugin_h

#ifndef Arrays_h
#include "Arrays.h"
#endif




struct RTICdrStream;

#ifndef pres_typePlugin_h
#include "pres/pres_typePlugin.h"
#endif


#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif


#ifdef __cplusplus
extern "C" {
#endif


#define InsidePlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
#define InsidePlugin_return_sample PRESTypePluginDefaultEndpointData_returnSample 
#define InsidePlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
#define InsidePlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 
 

#define InsidePlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
#define InsidePlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

/* --------------------------------------------------------------------------------------
    Support functions:
 * -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern Inside*
InsidePluginSupport_create_data_ex(RTIBool allocate_pointers);

NDDSUSERDllExport extern Inside*
InsidePluginSupport_create_data();

NDDSUSERDllExport extern RTIBool 
InsidePluginSupport_copy_data(
    Inside *out,
    const Inside *in);

NDDSUSERDllExport extern void 
InsidePluginSupport_destroy_data_ex(
    Inside *sample,RTIBool deallocate_pointers);

NDDSUSERDllExport extern void 
InsidePluginSupport_destroy_data(
    Inside *sample);

NDDSUSERDllExport extern void 
InsidePluginSupport_print_data(
    const Inside *sample,
    const char *desc,
    unsigned int indent);

 

/* ----------------------------------------------------------------------------
    Callback functions:
 * ---------------------------------------------------------------------------- */

NDDSUSERDllExport extern PRESTypePluginParticipantData 
InsidePlugin_on_participant_attached(
    void *registration_data, 
    const struct PRESTypePluginParticipantInfo *participant_info,
    RTIBool top_level_registration, 
    void *container_plugin_context,
    RTICdrTypeCode *typeCode);

NDDSUSERDllExport extern void 
InsidePlugin_on_participant_detached(
    PRESTypePluginParticipantData participant_data);
    
NDDSUSERDllExport extern PRESTypePluginEndpointData 
InsidePlugin_on_endpoint_attached(
    PRESTypePluginParticipantData participant_data,
    const struct PRESTypePluginEndpointInfo *endpoint_info,
    RTIBool top_level_registration, 
    void *container_plugin_context);

NDDSUSERDllExport extern void 
InsidePlugin_on_endpoint_detached(
    PRESTypePluginEndpointData endpoint_data);

NDDSUSERDllExport extern RTIBool 
InsidePlugin_copy_sample(
    PRESTypePluginEndpointData endpoint_data,
    Inside *out,
    const Inside *in);

/* --------------------------------------------------------------------------------------
    (De)Serialize functions:
 * -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern RTIBool 
InsidePlugin_serialize(
    PRESTypePluginEndpointData endpoint_data,
    const Inside *sample,
    struct RTICdrStream *stream, 
    RTIBool serialize_encapsulation,
    RTIBool serialize_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool 
InsidePlugin_deserialize(
    PRESTypePluginEndpointData endpoint_data,
    Inside *sample, 
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_sample, 
    void *endpoint_plugin_qos);


NDDSUSERDllExport extern RTIBool
InsidePlugin_skip(
    PRESTypePluginEndpointData endpoint_data,
    struct RTICdrStream *stream, 
    RTIBool skip_encapsulation,  
    RTIBool skip_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern unsigned int 
InsidePlugin_get_serialized_sample_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    unsigned int size);

NDDSUSERDllExport extern unsigned int 
InsidePlugin_get_serialized_sample_min_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    unsigned int size);

NDDSUSERDllExport extern unsigned int
InsidePlugin_get_serialized_sample_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    unsigned int size,
    const void * sample);


/* --------------------------------------------------------------------------------------
    Key Management functions:
 * -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern PRESTypePluginKeyKind 
InsidePlugin_get_key_kind();

NDDSUSERDllExport extern unsigned int 
InsidePlugin_get_serialized_key_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    unsigned int current_alignment);

NDDSUSERDllExport extern RTIBool 
InsidePlugin_serialize_key(
    PRESTypePluginEndpointData endpoint_data,
    const Inside *sample,
    struct RTICdrStream *stream,
    RTIBool serialize_encapsulation,
    RTIBool serialize_key,
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool 
InsidePlugin_deserialize_key(
    PRESTypePluginEndpointData endpoint_data,
    Inside * sample,
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_key,
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool
InsidePlugin_serialized_sample_to_key(
    PRESTypePluginEndpointData endpoint_data,
    Inside *sample,
    struct RTICdrStream *stream, 
    RTIBool deserialize_encapsulation,  
    RTIBool deserialize_key, 
    void *endpoint_plugin_qos);

     
/* Plugin Functions */
NDDSUSERDllExport extern struct PRESTypePlugin*
InsidePlugin_new();

NDDSUSERDllExport extern void
InsidePlugin_delete(struct PRESTypePlugin *);
 

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif



#define ArraysPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
#define ArraysPlugin_return_sample PRESTypePluginDefaultEndpointData_returnSample 
#define ArraysPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
#define ArraysPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 
 

#define ArraysPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
#define ArraysPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

/* --------------------------------------------------------------------------------------
    Support functions:
 * -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern Arrays*
ArraysPluginSupport_create_data_ex(RTIBool allocate_pointers);

NDDSUSERDllExport extern Arrays*
ArraysPluginSupport_create_data();

NDDSUSERDllExport extern RTIBool 
ArraysPluginSupport_copy_data(
    Arrays *out,
    const Arrays *in);

NDDSUSERDllExport extern void 
ArraysPluginSupport_destroy_data_ex(
    Arrays *sample,RTIBool deallocate_pointers);

NDDSUSERDllExport extern void 
ArraysPluginSupport_destroy_data(
    Arrays *sample);

NDDSUSERDllExport extern void 
ArraysPluginSupport_print_data(
    const Arrays *sample,
    const char *desc,
    unsigned int indent);

 

/* ----------------------------------------------------------------------------
    Callback functions:
 * ---------------------------------------------------------------------------- */

NDDSUSERDllExport extern PRESTypePluginParticipantData 
ArraysPlugin_on_participant_attached(
    void *registration_data, 
    const struct PRESTypePluginParticipantInfo *participant_info,
    RTIBool top_level_registration, 
    void *container_plugin_context,
    RTICdrTypeCode *typeCode);

NDDSUSERDllExport extern void 
ArraysPlugin_on_participant_detached(
    PRESTypePluginParticipantData participant_data);
    
NDDSUSERDllExport extern PRESTypePluginEndpointData 
ArraysPlugin_on_endpoint_attached(
    PRESTypePluginParticipantData participant_data,
    const struct PRESTypePluginEndpointInfo *endpoint_info,
    RTIBool top_level_registration, 
    void *container_plugin_context);

NDDSUSERDllExport extern void 
ArraysPlugin_on_endpoint_detached(
    PRESTypePluginEndpointData endpoint_data);

NDDSUSERDllExport extern RTIBool 
ArraysPlugin_copy_sample(
    PRESTypePluginEndpointData endpoint_data,
    Arrays *out,
    const Arrays *in);

/* --------------------------------------------------------------------------------------
    (De)Serialize functions:
 * -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern RTIBool 
ArraysPlugin_serialize(
    PRESTypePluginEndpointData endpoint_data,
    const Arrays *sample,
    struct RTICdrStream *stream, 
    RTIBool serialize_encapsulation,
    RTIBool serialize_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool 
ArraysPlugin_deserialize(
    PRESTypePluginEndpointData endpoint_data,
    Arrays *sample, 
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_sample, 
    void *endpoint_plugin_qos);


NDDSUSERDllExport extern RTIBool
ArraysPlugin_skip(
    PRESTypePluginEndpointData endpoint_data,
    struct RTICdrStream *stream, 
    RTIBool skip_encapsulation,  
    RTIBool skip_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern unsigned int 
ArraysPlugin_get_serialized_sample_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    unsigned int size);

NDDSUSERDllExport extern unsigned int 
ArraysPlugin_get_serialized_sample_min_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    unsigned int size);

NDDSUSERDllExport extern unsigned int
ArraysPlugin_get_serialized_sample_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    unsigned int size,
    const void * sample);


/* --------------------------------------------------------------------------------------
    Key Management functions:
 * -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern PRESTypePluginKeyKind 
ArraysPlugin_get_key_kind();

NDDSUSERDllExport extern unsigned int 
ArraysPlugin_get_serialized_key_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    unsigned int current_alignment);

NDDSUSERDllExport extern RTIBool 
ArraysPlugin_serialize_key(
    PRESTypePluginEndpointData endpoint_data,
    const Arrays *sample,
    struct RTICdrStream *stream,
    RTIBool serialize_encapsulation,
    RTIBool serialize_key,
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool 
ArraysPlugin_deserialize_key(
    PRESTypePluginEndpointData endpoint_data,
    Arrays * sample,
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_key,
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool
ArraysPlugin_serialized_sample_to_key(
    PRESTypePluginEndpointData endpoint_data,
    Arrays *sample,
    struct RTICdrStream *stream, 
    RTIBool deserialize_encapsulation,  
    RTIBool deserialize_key, 
    void *endpoint_plugin_qos);

     
/* Plugin Functions */
NDDSUSERDllExport extern struct PRESTypePlugin*
ArraysPlugin_new();

NDDSUSERDllExport extern void
ArraysPlugin_delete(struct PRESTypePlugin *);
 

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif


#ifdef __cplusplus
}
#endif
        

#endif /* ArraysPlugin_h */
