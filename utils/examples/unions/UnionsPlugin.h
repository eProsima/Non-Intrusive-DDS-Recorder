
/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from Unions.idl using "rtiddsgen".
  The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
  For more information, type 'rtiddsgen -help' at a command shell
  or consult the RTI Data Distribution Service manual.
*/

#ifndef UnionsPlugin_h
#define UnionsPlugin_h

#ifndef Unions_h
#include "Unions.h"
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


#define UnionPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
#define UnionPlugin_return_sample PRESTypePluginDefaultEndpointData_returnSample 
#define UnionPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
#define UnionPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 
 

#define UnionPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
#define UnionPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

/* --------------------------------------------------------------------------------------
    Support functions:
 * -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern Union*
UnionPluginSupport_create_data_ex(RTIBool allocate_pointers);

NDDSUSERDllExport extern Union*
UnionPluginSupport_create_data();

NDDSUSERDllExport extern RTIBool 
UnionPluginSupport_copy_data(
    Union *out,
    const Union *in);

NDDSUSERDllExport extern void 
UnionPluginSupport_destroy_data_ex(
    Union *sample,RTIBool deallocate_pointers);

NDDSUSERDllExport extern void 
UnionPluginSupport_destroy_data(
    Union *sample);

NDDSUSERDllExport extern void 
UnionPluginSupport_print_data(
    const Union *sample,
    const char *desc,
    unsigned int indent);

 

/* ----------------------------------------------------------------------------
    Callback functions:
 * ---------------------------------------------------------------------------- */

NDDSUSERDllExport extern PRESTypePluginParticipantData 
UnionPlugin_on_participant_attached(
    void *registration_data, 
    const struct PRESTypePluginParticipantInfo *participant_info,
    RTIBool top_level_registration, 
    void *container_plugin_context,
    RTICdrTypeCode *typeCode);

NDDSUSERDllExport extern void 
UnionPlugin_on_participant_detached(
    PRESTypePluginParticipantData participant_data);
    
NDDSUSERDllExport extern PRESTypePluginEndpointData 
UnionPlugin_on_endpoint_attached(
    PRESTypePluginParticipantData participant_data,
    const struct PRESTypePluginEndpointInfo *endpoint_info,
    RTIBool top_level_registration, 
    void *container_plugin_context);

NDDSUSERDllExport extern void 
UnionPlugin_on_endpoint_detached(
    PRESTypePluginEndpointData endpoint_data);

NDDSUSERDllExport extern RTIBool 
UnionPlugin_copy_sample(
    PRESTypePluginEndpointData endpoint_data,
    Union *out,
    const Union *in);

/* --------------------------------------------------------------------------------------
    (De)Serialize functions:
 * -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern RTIBool 
UnionPlugin_serialize(
    PRESTypePluginEndpointData endpoint_data,
    const Union *sample,
    struct RTICdrStream *stream, 
    RTIBool serialize_encapsulation,
    RTIBool serialize_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool 
UnionPlugin_deserialize(
    PRESTypePluginEndpointData endpoint_data,
    Union *sample, 
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_sample, 
    void *endpoint_plugin_qos);


NDDSUSERDllExport extern RTIBool
UnionPlugin_skip(
    PRESTypePluginEndpointData endpoint_data,
    struct RTICdrStream *stream, 
    RTIBool skip_encapsulation,  
    RTIBool skip_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern unsigned int 
UnionPlugin_get_serialized_sample_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    unsigned int size);

NDDSUSERDllExport extern unsigned int 
UnionPlugin_get_serialized_sample_min_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    unsigned int size);

NDDSUSERDllExport extern unsigned int
UnionPlugin_get_serialized_sample_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    unsigned int size,
    const void * sample);


/* --------------------------------------------------------------------------------------
    Key Management functions:
 * -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern PRESTypePluginKeyKind 
UnionPlugin_get_key_kind();

NDDSUSERDllExport extern unsigned int 
UnionPlugin_get_serialized_key_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    unsigned int current_alignment);

NDDSUSERDllExport extern RTIBool 
UnionPlugin_serialize_key(
    PRESTypePluginEndpointData endpoint_data,
    const Union *sample,
    struct RTICdrStream *stream,
    RTIBool serialize_encapsulation,
    RTIBool serialize_key,
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool 
UnionPlugin_deserialize_key(
    PRESTypePluginEndpointData endpoint_data,
    Union * sample,
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_key,
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool
UnionPlugin_serialized_sample_to_key(
    PRESTypePluginEndpointData endpoint_data,
    Union *sample,
    struct RTICdrStream *stream, 
    RTIBool deserialize_encapsulation,  
    RTIBool deserialize_key, 
    void *endpoint_plugin_qos);

     
/* Plugin Functions */
NDDSUSERDllExport extern struct PRESTypePlugin*
UnionPlugin_new();

NDDSUSERDllExport extern void
UnionPlugin_delete(struct PRESTypePlugin *);
 

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif



#define UnionsPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
#define UnionsPlugin_return_sample PRESTypePluginDefaultEndpointData_returnSample 
#define UnionsPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
#define UnionsPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 
 

#define UnionsPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
#define UnionsPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

/* --------------------------------------------------------------------------------------
    Support functions:
 * -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern Unions*
UnionsPluginSupport_create_data_ex(RTIBool allocate_pointers);

NDDSUSERDllExport extern Unions*
UnionsPluginSupport_create_data();

NDDSUSERDllExport extern RTIBool 
UnionsPluginSupport_copy_data(
    Unions *out,
    const Unions *in);

NDDSUSERDllExport extern void 
UnionsPluginSupport_destroy_data_ex(
    Unions *sample,RTIBool deallocate_pointers);

NDDSUSERDllExport extern void 
UnionsPluginSupport_destroy_data(
    Unions *sample);

NDDSUSERDllExport extern void 
UnionsPluginSupport_print_data(
    const Unions *sample,
    const char *desc,
    unsigned int indent);

 

/* ----------------------------------------------------------------------------
    Callback functions:
 * ---------------------------------------------------------------------------- */

NDDSUSERDllExport extern PRESTypePluginParticipantData 
UnionsPlugin_on_participant_attached(
    void *registration_data, 
    const struct PRESTypePluginParticipantInfo *participant_info,
    RTIBool top_level_registration, 
    void *container_plugin_context,
    RTICdrTypeCode *typeCode);

NDDSUSERDllExport extern void 
UnionsPlugin_on_participant_detached(
    PRESTypePluginParticipantData participant_data);
    
NDDSUSERDllExport extern PRESTypePluginEndpointData 
UnionsPlugin_on_endpoint_attached(
    PRESTypePluginParticipantData participant_data,
    const struct PRESTypePluginEndpointInfo *endpoint_info,
    RTIBool top_level_registration, 
    void *container_plugin_context);

NDDSUSERDllExport extern void 
UnionsPlugin_on_endpoint_detached(
    PRESTypePluginEndpointData endpoint_data);

NDDSUSERDllExport extern RTIBool 
UnionsPlugin_copy_sample(
    PRESTypePluginEndpointData endpoint_data,
    Unions *out,
    const Unions *in);

/* --------------------------------------------------------------------------------------
    (De)Serialize functions:
 * -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern RTIBool 
UnionsPlugin_serialize(
    PRESTypePluginEndpointData endpoint_data,
    const Unions *sample,
    struct RTICdrStream *stream, 
    RTIBool serialize_encapsulation,
    RTIBool serialize_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool 
UnionsPlugin_deserialize(
    PRESTypePluginEndpointData endpoint_data,
    Unions *sample, 
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_sample, 
    void *endpoint_plugin_qos);


NDDSUSERDllExport extern RTIBool
UnionsPlugin_skip(
    PRESTypePluginEndpointData endpoint_data,
    struct RTICdrStream *stream, 
    RTIBool skip_encapsulation,  
    RTIBool skip_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern unsigned int 
UnionsPlugin_get_serialized_sample_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    unsigned int size);

NDDSUSERDllExport extern unsigned int 
UnionsPlugin_get_serialized_sample_min_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    unsigned int size);

NDDSUSERDllExport extern unsigned int
UnionsPlugin_get_serialized_sample_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    unsigned int size,
    const void * sample);


/* --------------------------------------------------------------------------------------
    Key Management functions:
 * -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern PRESTypePluginKeyKind 
UnionsPlugin_get_key_kind();

NDDSUSERDllExport extern unsigned int 
UnionsPlugin_get_serialized_key_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    unsigned int current_alignment);

NDDSUSERDllExport extern RTIBool 
UnionsPlugin_serialize_key(
    PRESTypePluginEndpointData endpoint_data,
    const Unions *sample,
    struct RTICdrStream *stream,
    RTIBool serialize_encapsulation,
    RTIBool serialize_key,
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool 
UnionsPlugin_deserialize_key(
    PRESTypePluginEndpointData endpoint_data,
    Unions * sample,
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_key,
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool
UnionsPlugin_serialized_sample_to_key(
    PRESTypePluginEndpointData endpoint_data,
    Unions *sample,
    struct RTICdrStream *stream, 
    RTIBool deserialize_encapsulation,  
    RTIBool deserialize_key, 
    void *endpoint_plugin_qos);

     
/* Plugin Functions */
NDDSUSERDllExport extern struct PRESTypePlugin*
UnionsPlugin_new();

NDDSUSERDllExport extern void
UnionsPlugin_delete(struct PRESTypePlugin *);
 

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif


#ifdef __cplusplus
}
#endif
        

#endif /* UnionsPlugin_h */
