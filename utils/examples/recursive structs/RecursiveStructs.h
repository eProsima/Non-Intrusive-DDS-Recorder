
/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from RecursiveStructs.idl using "rtiddsgen".
  The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
  For more information, type 'rtiddsgen -help' at a command shell
  or consult the RTI Data Distribution Service manual.
*/

#ifndef RecursiveStructs_h
#define RecursiveStructs_h

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

        
extern const char *LevelTwoTYPENAME;
        

#ifdef __cplusplus
}
#endif

typedef struct LevelTwo
{
    DDS_Long  levelTwoLo;
    char*  levelTwoSt; /* maximum length = (255) */

} LevelTwo;
    
                            
#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

    
NDDSUSERDllExport DDS_TypeCode* LevelTwo_get_typecode(); /* Type code */
    

DDS_SEQUENCE(LevelTwoSeq, LevelTwo);
        
NDDSUSERDllExport
RTIBool LevelTwo_initialize(
        LevelTwo* self);
        
NDDSUSERDllExport
RTIBool LevelTwo_initialize_ex(
        LevelTwo* self,RTIBool allocatePointers);

NDDSUSERDllExport
void LevelTwo_finalize(
        LevelTwo* self);
                        
NDDSUSERDllExport
void LevelTwo_finalize_ex(
        LevelTwo* self,RTIBool deletePointers);
        
NDDSUSERDllExport
RTIBool LevelTwo_copy(
        LevelTwo* dst,
        const LevelTwo* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif


#ifdef __cplusplus
extern "C" {
#endif

        
extern const char *LevelOneTYPENAME;
        

#ifdef __cplusplus
}
#endif

typedef struct LevelOne
{
    LevelTwo  two1;
    LevelTwo  two2;
    DDS_Long  levelOneLo;

} LevelOne;
    
                            
#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

    
NDDSUSERDllExport DDS_TypeCode* LevelOne_get_typecode(); /* Type code */
    

DDS_SEQUENCE(LevelOneSeq, LevelOne);
        
NDDSUSERDllExport
RTIBool LevelOne_initialize(
        LevelOne* self);
        
NDDSUSERDllExport
RTIBool LevelOne_initialize_ex(
        LevelOne* self,RTIBool allocatePointers);

NDDSUSERDllExport
void LevelOne_finalize(
        LevelOne* self);
                        
NDDSUSERDllExport
void LevelOne_finalize_ex(
        LevelOne* self,RTIBool deletePointers);
        
NDDSUSERDllExport
RTIBool LevelOne_copy(
        LevelOne* dst,
        const LevelOne* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif


#ifdef __cplusplus
extern "C" {
#endif

        
extern const char *RecursiveStructsTYPENAME;
        

#ifdef __cplusplus
}
#endif

typedef struct RecursiveStructs
{
    DDS_Long  count;
    char*  message; /* maximum length = (255) */
    LevelOne  one;

} RecursiveStructs;
    
                            
#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

    
NDDSUSERDllExport DDS_TypeCode* RecursiveStructs_get_typecode(); /* Type code */
    

DDS_SEQUENCE(RecursiveStructsSeq, RecursiveStructs);
        
NDDSUSERDllExport
RTIBool RecursiveStructs_initialize(
        RecursiveStructs* self);
        
NDDSUSERDllExport
RTIBool RecursiveStructs_initialize_ex(
        RecursiveStructs* self,RTIBool allocatePointers);

NDDSUSERDllExport
void RecursiveStructs_finalize(
        RecursiveStructs* self);
                        
NDDSUSERDllExport
void RecursiveStructs_finalize_ex(
        RecursiveStructs* self,RTIBool deletePointers);
        
NDDSUSERDllExport
RTIBool RecursiveStructs_copy(
        RecursiveStructs* dst,
        const RecursiveStructs* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif



#endif /* RecursiveStructs_h */
