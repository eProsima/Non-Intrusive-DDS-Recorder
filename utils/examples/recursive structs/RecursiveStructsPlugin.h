
/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from RecursiveStructs.idl using "rtiddsgen".
  The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
  For more information, type 'rtiddsgen -help' at a command shell
  or consult the RTI Data Distribution Service manual.
*/

#ifndef RecursiveStructsPlugin_h
#define RecursiveStructsPlugin_h

#ifndef RecursiveStructs_h
#include "RecursiveStructs.h"
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


#define LevelTwoPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
#define LevelTwoPlugin_return_sample PRESTypePluginDefaultEndpointData_returnSample 
#define LevelTwoPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
#define LevelTwoPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 
 

#define LevelTwoPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
#define LevelTwoPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

/* --------------------------------------------------------------------------------------
    Support functions:
 * -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern LevelTwo*
LevelTwoPluginSupport_create_data_ex(RTIBool allocate_pointers);

NDDSUSERDllExport extern LevelTwo*
LevelTwoPluginSupport_create_data();

NDDSUSERDllExport extern RTIBool 
LevelTwoPluginSupport_copy_data(
    LevelTwo *out,
    const LevelTwo *in);

NDDSUSERDllExport extern void 
LevelTwoPluginSupport_destroy_data_ex(
    LevelTwo *sample,RTIBool deallocate_pointers);

NDDSUSERDllExport extern void 
LevelTwoPluginSupport_destroy_data(
    LevelTwo *sample);

NDDSUSERDllExport extern void 
LevelTwoPluginSupport_print_data(
    const LevelTwo *sample,
    const char *desc,
    unsigned int indent);

 

/* ----------------------------------------------------------------------------
    Callback functions:
 * ---------------------------------------------------------------------------- */

NDDSUSERDllExport extern PRESTypePluginParticipantData 
LevelTwoPlugin_on_participant_attached(
    void *registration_data, 
    const struct PRESTypePluginParticipantInfo *participant_info,
    RTIBool top_level_registration, 
    void *container_plugin_context,
    RTICdrTypeCode *typeCode);

NDDSUSERDllExport extern void 
LevelTwoPlugin_on_participant_detached(
    PRESTypePluginParticipantData participant_data);
    
NDDSUSERDllExport extern PRESTypePluginEndpointData 
LevelTwoPlugin_on_endpoint_attached(
    PRESTypePluginParticipantData participant_data,
    const struct PRESTypePluginEndpointInfo *endpoint_info,
    RTIBool top_level_registration, 
    void *container_plugin_context);

NDDSUSERDllExport extern void 
LevelTwoPlugin_on_endpoint_detached(
    PRESTypePluginEndpointData endpoint_data);

NDDSUSERDllExport extern RTIBool 
LevelTwoPlugin_copy_sample(
    PRESTypePluginEndpointData endpoint_data,
    LevelTwo *out,
    const LevelTwo *in);

/* --------------------------------------------------------------------------------------
    (De)Serialize functions:
 * -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern RTIBool 
LevelTwoPlugin_serialize(
    PRESTypePluginEndpointData endpoint_data,
    const LevelTwo *sample,
    struct RTICdrStream *stream, 
    RTIBool serialize_encapsulation,
    RTIBool serialize_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool 
LevelTwoPlugin_deserialize(
    PRESTypePluginEndpointData endpoint_data,
    LevelTwo *sample, 
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_sample, 
    void *endpoint_plugin_qos);


NDDSUSERDllExport extern RTIBool
LevelTwoPlugin_skip(
    PRESTypePluginEndpointData endpoint_data,
    struct RTICdrStream *stream, 
    RTIBool skip_encapsulation,  
    RTIBool skip_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern unsigned int 
LevelTwoPlugin_get_serialized_sample_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    unsigned int size);

NDDSUSERDllExport extern unsigned int 
LevelTwoPlugin_get_serialized_sample_min_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    unsigned int size);

NDDSUSERDllExport extern unsigned int
LevelTwoPlugin_get_serialized_sample_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    unsigned int size,
    const void * sample);


/* --------------------------------------------------------------------------------------
    Key Management functions:
 * -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern PRESTypePluginKeyKind 
LevelTwoPlugin_get_key_kind();

NDDSUSERDllExport extern unsigned int 
LevelTwoPlugin_get_serialized_key_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    unsigned int current_alignment);

NDDSUSERDllExport extern RTIBool 
LevelTwoPlugin_serialize_key(
    PRESTypePluginEndpointData endpoint_data,
    const LevelTwo *sample,
    struct RTICdrStream *stream,
    RTIBool serialize_encapsulation,
    RTIBool serialize_key,
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool 
LevelTwoPlugin_deserialize_key(
    PRESTypePluginEndpointData endpoint_data,
    LevelTwo * sample,
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_key,
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool
LevelTwoPlugin_serialized_sample_to_key(
    PRESTypePluginEndpointData endpoint_data,
    LevelTwo *sample,
    struct RTICdrStream *stream, 
    RTIBool deserialize_encapsulation,  
    RTIBool deserialize_key, 
    void *endpoint_plugin_qos);

     
/* Plugin Functions */
NDDSUSERDllExport extern struct PRESTypePlugin*
LevelTwoPlugin_new();

NDDSUSERDllExport extern void
LevelTwoPlugin_delete(struct PRESTypePlugin *);
 

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif



#define LevelOnePlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
#define LevelOnePlugin_return_sample PRESTypePluginDefaultEndpointData_returnSample 
#define LevelOnePlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
#define LevelOnePlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 
 

#define LevelOnePlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
#define LevelOnePlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

/* --------------------------------------------------------------------------------------
    Support functions:
 * -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern LevelOne*
LevelOnePluginSupport_create_data_ex(RTIBool allocate_pointers);

NDDSUSERDllExport extern LevelOne*
LevelOnePluginSupport_create_data();

NDDSUSERDllExport extern RTIBool 
LevelOnePluginSupport_copy_data(
    LevelOne *out,
    const LevelOne *in);

NDDSUSERDllExport extern void 
LevelOnePluginSupport_destroy_data_ex(
    LevelOne *sample,RTIBool deallocate_pointers);

NDDSUSERDllExport extern void 
LevelOnePluginSupport_destroy_data(
    LevelOne *sample);

NDDSUSERDllExport extern void 
LevelOnePluginSupport_print_data(
    const LevelOne *sample,
    const char *desc,
    unsigned int indent);

 

/* ----------------------------------------------------------------------------
    Callback functions:
 * ---------------------------------------------------------------------------- */

NDDSUSERDllExport extern PRESTypePluginParticipantData 
LevelOnePlugin_on_participant_attached(
    void *registration_data, 
    const struct PRESTypePluginParticipantInfo *participant_info,
    RTIBool top_level_registration, 
    void *container_plugin_context,
    RTICdrTypeCode *typeCode);

NDDSUSERDllExport extern void 
LevelOnePlugin_on_participant_detached(
    PRESTypePluginParticipantData participant_data);
    
NDDSUSERDllExport extern PRESTypePluginEndpointData 
LevelOnePlugin_on_endpoint_attached(
    PRESTypePluginParticipantData participant_data,
    const struct PRESTypePluginEndpointInfo *endpoint_info,
    RTIBool top_level_registration, 
    void *container_plugin_context);

NDDSUSERDllExport extern void 
LevelOnePlugin_on_endpoint_detached(
    PRESTypePluginEndpointData endpoint_data);

NDDSUSERDllExport extern RTIBool 
LevelOnePlugin_copy_sample(
    PRESTypePluginEndpointData endpoint_data,
    LevelOne *out,
    const LevelOne *in);

/* --------------------------------------------------------------------------------------
    (De)Serialize functions:
 * -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern RTIBool 
LevelOnePlugin_serialize(
    PRESTypePluginEndpointData endpoint_data,
    const LevelOne *sample,
    struct RTICdrStream *stream, 
    RTIBool serialize_encapsulation,
    RTIBool serialize_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool 
LevelOnePlugin_deserialize(
    PRESTypePluginEndpointData endpoint_data,
    LevelOne *sample, 
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_sample, 
    void *endpoint_plugin_qos);


NDDSUSERDllExport extern RTIBool
LevelOnePlugin_skip(
    PRESTypePluginEndpointData endpoint_data,
    struct RTICdrStream *stream, 
    RTIBool skip_encapsulation,  
    RTIBool skip_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern unsigned int 
LevelOnePlugin_get_serialized_sample_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    unsigned int size);

NDDSUSERDllExport extern unsigned int 
LevelOnePlugin_get_serialized_sample_min_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    unsigned int size);

NDDSUSERDllExport extern unsigned int
LevelOnePlugin_get_serialized_sample_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    unsigned int size,
    const void * sample);


/* --------------------------------------------------------------------------------------
    Key Management functions:
 * -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern PRESTypePluginKeyKind 
LevelOnePlugin_get_key_kind();

NDDSUSERDllExport extern unsigned int 
LevelOnePlugin_get_serialized_key_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    unsigned int current_alignment);

NDDSUSERDllExport extern RTIBool 
LevelOnePlugin_serialize_key(
    PRESTypePluginEndpointData endpoint_data,
    const LevelOne *sample,
    struct RTICdrStream *stream,
    RTIBool serialize_encapsulation,
    RTIBool serialize_key,
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool 
LevelOnePlugin_deserialize_key(
    PRESTypePluginEndpointData endpoint_data,
    LevelOne * sample,
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_key,
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool
LevelOnePlugin_serialized_sample_to_key(
    PRESTypePluginEndpointData endpoint_data,
    LevelOne *sample,
    struct RTICdrStream *stream, 
    RTIBool deserialize_encapsulation,  
    RTIBool deserialize_key, 
    void *endpoint_plugin_qos);

     
/* Plugin Functions */
NDDSUSERDllExport extern struct PRESTypePlugin*
LevelOnePlugin_new();

NDDSUSERDllExport extern void
LevelOnePlugin_delete(struct PRESTypePlugin *);
 

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif



#define RecursiveStructsPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
#define RecursiveStructsPlugin_return_sample PRESTypePluginDefaultEndpointData_returnSample 
#define RecursiveStructsPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
#define RecursiveStructsPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 
 

#define RecursiveStructsPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
#define RecursiveStructsPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

/* --------------------------------------------------------------------------------------
    Support functions:
 * -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern RecursiveStructs*
RecursiveStructsPluginSupport_create_data_ex(RTIBool allocate_pointers);

NDDSUSERDllExport extern RecursiveStructs*
RecursiveStructsPluginSupport_create_data();

NDDSUSERDllExport extern RTIBool 
RecursiveStructsPluginSupport_copy_data(
    RecursiveStructs *out,
    const RecursiveStructs *in);

NDDSUSERDllExport extern void 
RecursiveStructsPluginSupport_destroy_data_ex(
    RecursiveStructs *sample,RTIBool deallocate_pointers);

NDDSUSERDllExport extern void 
RecursiveStructsPluginSupport_destroy_data(
    RecursiveStructs *sample);

NDDSUSERDllExport extern void 
RecursiveStructsPluginSupport_print_data(
    const RecursiveStructs *sample,
    const char *desc,
    unsigned int indent);

 

/* ----------------------------------------------------------------------------
    Callback functions:
 * ---------------------------------------------------------------------------- */

NDDSUSERDllExport extern PRESTypePluginParticipantData 
RecursiveStructsPlugin_on_participant_attached(
    void *registration_data, 
    const struct PRESTypePluginParticipantInfo *participant_info,
    RTIBool top_level_registration, 
    void *container_plugin_context,
    RTICdrTypeCode *typeCode);

NDDSUSERDllExport extern void 
RecursiveStructsPlugin_on_participant_detached(
    PRESTypePluginParticipantData participant_data);
    
NDDSUSERDllExport extern PRESTypePluginEndpointData 
RecursiveStructsPlugin_on_endpoint_attached(
    PRESTypePluginParticipantData participant_data,
    const struct PRESTypePluginEndpointInfo *endpoint_info,
    RTIBool top_level_registration, 
    void *container_plugin_context);

NDDSUSERDllExport extern void 
RecursiveStructsPlugin_on_endpoint_detached(
    PRESTypePluginEndpointData endpoint_data);

NDDSUSERDllExport extern RTIBool 
RecursiveStructsPlugin_copy_sample(
    PRESTypePluginEndpointData endpoint_data,
    RecursiveStructs *out,
    const RecursiveStructs *in);

/* --------------------------------------------------------------------------------------
    (De)Serialize functions:
 * -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern RTIBool 
RecursiveStructsPlugin_serialize(
    PRESTypePluginEndpointData endpoint_data,
    const RecursiveStructs *sample,
    struct RTICdrStream *stream, 
    RTIBool serialize_encapsulation,
    RTIBool serialize_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool 
RecursiveStructsPlugin_deserialize(
    PRESTypePluginEndpointData endpoint_data,
    RecursiveStructs *sample, 
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_sample, 
    void *endpoint_plugin_qos);


NDDSUSERDllExport extern RTIBool
RecursiveStructsPlugin_skip(
    PRESTypePluginEndpointData endpoint_data,
    struct RTICdrStream *stream, 
    RTIBool skip_encapsulation,  
    RTIBool skip_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern unsigned int 
RecursiveStructsPlugin_get_serialized_sample_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    unsigned int size);

NDDSUSERDllExport extern unsigned int 
RecursiveStructsPlugin_get_serialized_sample_min_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    unsigned int size);

NDDSUSERDllExport extern unsigned int
RecursiveStructsPlugin_get_serialized_sample_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    unsigned int size,
    const void * sample);


/* --------------------------------------------------------------------------------------
    Key Management functions:
 * -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern PRESTypePluginKeyKind 
RecursiveStructsPlugin_get_key_kind();

NDDSUSERDllExport extern unsigned int 
RecursiveStructsPlugin_get_serialized_key_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    unsigned int current_alignment);

NDDSUSERDllExport extern RTIBool 
RecursiveStructsPlugin_serialize_key(
    PRESTypePluginEndpointData endpoint_data,
    const RecursiveStructs *sample,
    struct RTICdrStream *stream,
    RTIBool serialize_encapsulation,
    RTIBool serialize_key,
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool 
RecursiveStructsPlugin_deserialize_key(
    PRESTypePluginEndpointData endpoint_data,
    RecursiveStructs * sample,
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_key,
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool
RecursiveStructsPlugin_serialized_sample_to_key(
    PRESTypePluginEndpointData endpoint_data,
    RecursiveStructs *sample,
    struct RTICdrStream *stream, 
    RTIBool deserialize_encapsulation,  
    RTIBool deserialize_key, 
    void *endpoint_plugin_qos);

     
/* Plugin Functions */
NDDSUSERDllExport extern struct PRESTypePlugin*
RecursiveStructsPlugin_new();

NDDSUSERDllExport extern void
RecursiveStructsPlugin_delete(struct PRESTypePlugin *);
 

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif


#ifdef __cplusplus
}
#endif
        

#endif /* RecursiveStructsPlugin_h */
