
/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from Enums.idl using "rtiddsgen".
  The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
  For more information, type 'rtiddsgen -help' at a command shell
  or consult the RTI Data Distribution Service manual.
*/

#ifndef EnumsPlugin_h
#define EnumsPlugin_h

#ifndef Enums_h
#include "Enums.h"
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


/* ------------------------------------------------------------------------
 * (De)Serialization Methods
 * ------------------------------------------------------------------------ */

NDDSUSERDllExport extern RTIBool
EnumeradoPlugin_serialize(
    PRESTypePluginEndpointData endpoint_data,
    const Enumerado *sample, struct RTICdrStream *stream,
    RTIBool serialize_encapsulation,RTIBool serialize_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool
EnumeradoPlugin_deserialize(
    PRESTypePluginEndpointData endpoint_data,
    Enumerado *sample, struct RTICdrStream *stream, 
    RTIBool serialize_encapsulation,RTIBool serialize_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool
EnumeradoPlugin_skip(
    PRESTypePluginEndpointData endpoint_data,
    struct RTICdrStream *stream, 
    RTIBool skip_encapsulation,  
    RTIBool skip_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern unsigned int
EnumeradoPlugin_get_serialized_sample_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    unsigned int current_alignment);

NDDSUSERDllExport extern unsigned int
EnumeradoPlugin_get_serialized_sample_min_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    unsigned int current_alignment);

/* ------------------------------------------------------------------------
    Key Management functions:
 * ------------------------------------------------------------------------ */

NDDSUSERDllExport extern RTIBool 
EnumeradoPlugin_serialize_key(
    PRESTypePluginEndpointData endpoint_data,
    const Enumerado *sample,
    struct RTICdrStream *stream,
    RTIBool serialize_encapsulation,
    RTIBool serialize_key,
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool 
EnumeradoPlugin_deserialize_key(
    PRESTypePluginEndpointData endpoint_data,
    Enumerado *sample,
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_key,
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern unsigned int 
EnumeradoPlugin_get_serialized_key_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    unsigned int current_alignment);

NDDSUSERDllExport extern RTIBool
EnumeradoPlugin_serialized_sample_to_key(
    PRESTypePluginEndpointData endpoint_data,
    Enumerado *sample,
    struct RTICdrStream *stream, 
    RTIBool deserialize_encapsulation,  
    RTIBool deserialize_key, 
    void *endpoint_plugin_qos);

/* ----------------------------------------------------------------------------
    Support functions:
 * ---------------------------------------------------------------------------- */

NDDSUSERDllExport extern void
EnumeradoPluginSupport_print_data(
    const Enumerado *sample, const char *desc, int indent_level);



#define EnumsPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
#define EnumsPlugin_return_sample PRESTypePluginDefaultEndpointData_returnSample 
#define EnumsPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
#define EnumsPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 
 

#define EnumsPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
#define EnumsPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

/* --------------------------------------------------------------------------------------
    Support functions:
 * -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern Enums*
EnumsPluginSupport_create_data_ex(RTIBool allocate_pointers);

NDDSUSERDllExport extern Enums*
EnumsPluginSupport_create_data();

NDDSUSERDllExport extern RTIBool 
EnumsPluginSupport_copy_data(
    Enums *out,
    const Enums *in);

NDDSUSERDllExport extern void 
EnumsPluginSupport_destroy_data_ex(
    Enums *sample,RTIBool deallocate_pointers);

NDDSUSERDllExport extern void 
EnumsPluginSupport_destroy_data(
    Enums *sample);

NDDSUSERDllExport extern void 
EnumsPluginSupport_print_data(
    const Enums *sample,
    const char *desc,
    unsigned int indent);

 

/* ----------------------------------------------------------------------------
    Callback functions:
 * ---------------------------------------------------------------------------- */

NDDSUSERDllExport extern PRESTypePluginParticipantData 
EnumsPlugin_on_participant_attached(
    void *registration_data, 
    const struct PRESTypePluginParticipantInfo *participant_info,
    RTIBool top_level_registration, 
    void *container_plugin_context,
    RTICdrTypeCode *typeCode);

NDDSUSERDllExport extern void 
EnumsPlugin_on_participant_detached(
    PRESTypePluginParticipantData participant_data);
    
NDDSUSERDllExport extern PRESTypePluginEndpointData 
EnumsPlugin_on_endpoint_attached(
    PRESTypePluginParticipantData participant_data,
    const struct PRESTypePluginEndpointInfo *endpoint_info,
    RTIBool top_level_registration, 
    void *container_plugin_context);

NDDSUSERDllExport extern void 
EnumsPlugin_on_endpoint_detached(
    PRESTypePluginEndpointData endpoint_data);

NDDSUSERDllExport extern RTIBool 
EnumsPlugin_copy_sample(
    PRESTypePluginEndpointData endpoint_data,
    Enums *out,
    const Enums *in);

/* --------------------------------------------------------------------------------------
    (De)Serialize functions:
 * -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern RTIBool 
EnumsPlugin_serialize(
    PRESTypePluginEndpointData endpoint_data,
    const Enums *sample,
    struct RTICdrStream *stream, 
    RTIBool serialize_encapsulation,
    RTIBool serialize_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool 
EnumsPlugin_deserialize(
    PRESTypePluginEndpointData endpoint_data,
    Enums *sample, 
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_sample, 
    void *endpoint_plugin_qos);


NDDSUSERDllExport extern RTIBool
EnumsPlugin_skip(
    PRESTypePluginEndpointData endpoint_data,
    struct RTICdrStream *stream, 
    RTIBool skip_encapsulation,  
    RTIBool skip_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern unsigned int 
EnumsPlugin_get_serialized_sample_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    unsigned int size);

NDDSUSERDllExport extern unsigned int 
EnumsPlugin_get_serialized_sample_min_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    unsigned int size);

NDDSUSERDllExport extern unsigned int
EnumsPlugin_get_serialized_sample_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    unsigned int size,
    const void * sample);


/* --------------------------------------------------------------------------------------
    Key Management functions:
 * -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern PRESTypePluginKeyKind 
EnumsPlugin_get_key_kind();

NDDSUSERDllExport extern unsigned int 
EnumsPlugin_get_serialized_key_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    unsigned int current_alignment);

NDDSUSERDllExport extern RTIBool 
EnumsPlugin_serialize_key(
    PRESTypePluginEndpointData endpoint_data,
    const Enums *sample,
    struct RTICdrStream *stream,
    RTIBool serialize_encapsulation,
    RTIBool serialize_key,
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool 
EnumsPlugin_deserialize_key(
    PRESTypePluginEndpointData endpoint_data,
    Enums * sample,
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_key,
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool
EnumsPlugin_serialized_sample_to_key(
    PRESTypePluginEndpointData endpoint_data,
    Enums *sample,
    struct RTICdrStream *stream, 
    RTIBool deserialize_encapsulation,  
    RTIBool deserialize_key, 
    void *endpoint_plugin_qos);

     
/* Plugin Functions */
NDDSUSERDllExport extern struct PRESTypePlugin*
EnumsPlugin_new();

NDDSUSERDllExport extern void
EnumsPlugin_delete(struct PRESTypePlugin *);
 

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif


#ifdef __cplusplus
}
#endif
        

#endif /* EnumsPlugin_h */
