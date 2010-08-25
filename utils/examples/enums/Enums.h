
/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from Enums.idl using "rtiddsgen".
  The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
  For more information, type 'rtiddsgen -help' at a command shell
  or consult the RTI Data Distribution Service manual.
*/

#ifndef Enums_h
#define Enums_h

#ifndef NDDS_STANDALONE_TYPE
    #ifdef __cplusplus
        #ifndef ndds_cpp_h
            #include "ndds/ndds_cpp.h"
        #endif
    #else
        #ifndef ndds_c_h
            #include "ndds/ndds_c.h"
        #endif
    #endif
#else
    #include "ndds_standalone_type.h"
#endif



typedef enum Enumerado
{
    VALOR1,
    VALOR2,
    VALOR3,
    VALORZ
} Enumerado;

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

    
NDDSUSERDllExport DDS_TypeCode* Enumerado_get_typecode(); /* Type code */
    

DDS_SEQUENCE(EnumeradoSeq, Enumerado);
        
NDDSUSERDllExport
RTIBool Enumerado_initialize(
        Enumerado* self);
        
NDDSUSERDllExport
RTIBool Enumerado_initialize_ex(
        Enumerado* self,RTIBool allocatePointers);

NDDSUSERDllExport
void Enumerado_finalize(
        Enumerado* self);
                        
NDDSUSERDllExport
void Enumerado_finalize_ex(
        Enumerado* self,RTIBool deletePointers);
        
NDDSUSERDllExport
RTIBool Enumerado_copy(
        Enumerado* dst,
        const Enumerado* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif


#ifdef __cplusplus
extern "C" {
#endif

        
extern const char *EnumsTYPENAME;
        

#ifdef __cplusplus
}
#endif

typedef struct Enums
{
    DDS_Long  count;
    Enumerado  en;
    Enumerado  aren[10];
     EnumeradoSeq  seen;

} Enums;
    
                            
#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

    
NDDSUSERDllExport DDS_TypeCode* Enums_get_typecode(); /* Type code */
    

DDS_SEQUENCE(EnumsSeq, Enums);
        
NDDSUSERDllExport
RTIBool Enums_initialize(
        Enums* self);
        
NDDSUSERDllExport
RTIBool Enums_initialize_ex(
        Enums* self,RTIBool allocatePointers);

NDDSUSERDllExport
void Enums_finalize(
        Enums* self);
                        
NDDSUSERDllExport
void Enums_finalize_ex(
        Enums* self,RTIBool deletePointers);
        
NDDSUSERDllExport
RTIBool Enums_copy(
        Enums* dst,
        const Enums* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif



#endif /* Enums_h */
