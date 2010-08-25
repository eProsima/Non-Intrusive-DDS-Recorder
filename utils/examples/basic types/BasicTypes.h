
/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from BasicTypes.idl using "rtiddsgen".
  The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
  For more information, type 'rtiddsgen -help' at a command shell
  or consult the RTI Data Distribution Service manual.
*/

#ifndef BasicTypes_h
#define BasicTypes_h

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


#ifdef __cplusplus
extern "C" {
#endif

        
extern const char *BasicTypesTYPENAME;
        

#ifdef __cplusplus
}
#endif

typedef struct BasicTypes
{
    DDS_Octet  oc;
    DDS_Char  ch;
    DDS_Short  sh;
    DDS_UnsignedShort  ush;
    DDS_Long  lo;
    DDS_UnsignedLong  ulo;
    DDS_LongLong  lolo;
    DDS_UnsignedLongLong  ulolo;
    char*  st; /* maximum length = (255) */
    DDS_Float  fl;
    DDS_Double  dl;

} BasicTypes;
    
                            
#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

    
NDDSUSERDllExport DDS_TypeCode* BasicTypes_get_typecode(); /* Type code */
    

DDS_SEQUENCE(BasicTypesSeq, BasicTypes);
        
NDDSUSERDllExport
RTIBool BasicTypes_initialize(
        BasicTypes* self);
        
NDDSUSERDllExport
RTIBool BasicTypes_initialize_ex(
        BasicTypes* self,RTIBool allocatePointers);

NDDSUSERDllExport
void BasicTypes_finalize(
        BasicTypes* self);
                        
NDDSUSERDllExport
void BasicTypes_finalize_ex(
        BasicTypes* self,RTIBool deletePointers);
        
NDDSUSERDllExport
RTIBool BasicTypes_copy(
        BasicTypes* dst,
        const BasicTypes* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif



#endif /* BasicTypes_h */
