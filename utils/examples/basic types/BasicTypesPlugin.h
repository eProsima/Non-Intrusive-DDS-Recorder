
/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from BasicTypes.idl using "rtiddsgen".
  The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
  For more information, type 'rtiddsgen -help' at a command shell
  or consult the RTI Data Distribution Service manual.
*/

#ifndef BasicTypesPlugin_h
#define BasicTypesPlugin_h

#ifndef BasicTypes_h
#include "BasicTypes.h"
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


#define BasicTypesPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
#define BasicTypesPlugin_return_sample PRESTypePluginDefaultEndpointData_returnSample 
#define BasicTypesPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
#define BasicTypesPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 
 

#define BasicTypesPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
#define BasicTypesPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

/* --------------------------------------------------------------------------------------
    Support functions:
 * -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern BasicTypes*
BasicTypesPluginSupport_create_data_ex(RTIBool allocate_pointers);

NDDSUSERDllExport extern BasicTypes*
BasicTypesPluginSupport_create_data();

NDDSUSERDllExport extern RTIBool 
BasicTypesPluginSupport_copy_data(
    BasicTypes *out,
    const BasicTypes *in);

NDDSUSERDllExport extern void 
BasicTypesPluginSupport_destroy_data_ex(
    BasicTypes *sample,RTIBool deallocate_pointers);

NDDSUSERDllExport extern void 
BasicTypesPluginSupport_destroy_data(
    BasicTypes *sample);

NDDSUSERDllExport extern void 
BasicTypesPluginSupport_print_data(
    const BasicTypes *sample,
    const char *desc,
    unsigned int indent);

 

/* ----------------------------------------------------------------------------
    Callback functions:
 * ---------------------------------------------------------------------------- */

NDDSUSERDllExport extern PRESTypePluginParticipantData 
BasicTypesPlugin_on_participant_attached(
    void *registration_data, 
    const struct PRESTypePluginParticipantInfo *participant_info,
    RTIBool top_level_registration, 
    void *container_plugin_context,
    RTICdrTypeCode *typeCode);

NDDSUSERDllExport extern void 
BasicTypesPlugin_on_participant_detached(
    PRESTypePluginParticipantData participant_data);
    
NDDSUSERDllExport extern PRESTypePluginEndpointData 
BasicTypesPlugin_on_endpoint_attached(
    PRESTypePluginParticipantData participant_data,
    const struct PRESTypePluginEndpointInfo *endpoint_info,
    RTIBool top_level_registration, 
    void *container_plugin_context);

NDDSUSERDllExport extern void 
BasicTypesPlugin_on_endpoint_detached(
    PRESTypePluginEndpointData endpoint_data);

NDDSUSERDllExport extern RTIBool 
BasicTypesPlugin_copy_sample(
    PRESTypePluginEndpointData endpoint_data,
    BasicTypes *out,
    const BasicTypes *in);

/* --------------------------------------------------------------------------------------
    (De)Serialize functions:
 * -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern RTIBool 
BasicTypesPlugin_serialize(
    PRESTypePluginEndpointData endpoint_data,
    const BasicTypes *sample,
    struct RTICdrStream *stream, 
    RTIBool serialize_encapsulation,
    RTIBool serialize_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool 
BasicTypesPlugin_deserialize(
    PRESTypePluginEndpointData endpoint_data,
    BasicTypes *sample, 
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_sample, 
    void *endpoint_plugin_qos);


NDDSUSERDllExport extern RTIBool
BasicTypesPlugin_skip(
    PRESTypePluginEndpointData endpoint_data,
    struct RTICdrStream *stream, 
    RTIBool skip_encapsulation,  
    RTIBool skip_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern unsigned int 
BasicTypesPlugin_get_serialized_sample_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    unsigned int size);

NDDSUSERDllExport extern unsigned int 
BasicTypesPlugin_get_serialized_sample_min_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    unsigned int size);

NDDSUSERDllExport extern unsigned int
BasicTypesPlugin_get_serialized_sample_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    unsigned int size,
    const void * sample);


/* --------------------------------------------------------------------------------------
    Key Management functions:
 * -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern PRESTypePluginKeyKind 
BasicTypesPlugin_get_key_kind();

NDDSUSERDllExport extern unsigned int 
BasicTypesPlugin_get_serialized_key_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    unsigned int current_alignment);

NDDSUSERDllExport extern RTIBool 
BasicTypesPlugin_serialize_key(
    PRESTypePluginEndpointData endpoint_data,
    const BasicTypes *sample,
    struct RTICdrStream *stream,
    RTIBool serialize_encapsulation,
    RTIBool serialize_key,
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool 
BasicTypesPlugin_deserialize_key(
    PRESTypePluginEndpointData endpoint_data,
    BasicTypes * sample,
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_key,
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool
BasicTypesPlugin_serialized_sample_to_key(
    PRESTypePluginEndpointData endpoint_data,
    BasicTypes *sample,
    struct RTICdrStream *stream, 
    RTIBool deserialize_encapsulation,  
    RTIBool deserialize_key, 
    void *endpoint_plugin_qos);

     
/* Plugin Functions */
NDDSUSERDllExport extern struct PRESTypePlugin*
BasicTypesPlugin_new();

NDDSUSERDllExport extern void
BasicTypesPlugin_delete(struct PRESTypePlugin *);
 

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif


#ifdef __cplusplus
}
#endif
        

#endif /* BasicTypesPlugin_h */
