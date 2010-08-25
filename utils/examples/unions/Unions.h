
/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from Unions.idl using "rtiddsgen".
  The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
  For more information, type 'rtiddsgen -help' at a command shell
  or consult the RTI Data Distribution Service manual.
*/

#ifndef Unions_h
#define Unions_h

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

        
extern const char *InsideTYPENAME;
        

#ifdef __cplusplus
}
#endif

typedef struct Inside
{
    DDS_UnsignedLong  ulo;
    DDS_Octet  ocar[10];
     DDS_ShortSeq  sesh;

} Inside;
    
                            
#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

    
NDDSUSERDllExport DDS_TypeCode* Inside_get_typecode(); /* Type code */
    

DDS_SEQUENCE(InsideSeq, Inside);
        
NDDSUSERDllExport
RTIBool Inside_initialize(
        Inside* self);
        
NDDSUSERDllExport
RTIBool Inside_initialize_ex(
        Inside* self,RTIBool allocatePointers);

NDDSUSERDllExport
void Inside_finalize(
        Inside* self);
                        
NDDSUSERDllExport
void Inside_finalize_ex(
        Inside* self,RTIBool deletePointers);
        
NDDSUSERDllExport
RTIBool Inside_copy(
        Inside* dst,
        const Inside* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif


#ifdef __cplusplus
extern "C" {
#endif

                
extern const char *UnionTYPENAME;


#ifdef __cplusplus
}
#endif



typedef struct Union {
    DDS_Long _d;
    struct Union_u
    {
    DDS_Float  fls[10];
     DDS_LongSeq  los;
    Inside  ins;
    char*  message; /* maximum length = (255) */

    } _u;
} Union;

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

    
NDDSUSERDllExport DDS_TypeCode* Union_get_typecode(); /* Type code */
    

DDS_SEQUENCE(UnionSeq, Union);

NDDSUSERDllExport
RTIBool Union_initialize(
        Union* self);
        
NDDSUSERDllExport
RTIBool Union_initialize_ex(
        Union* self,RTIBool allocatePointers);

NDDSUSERDllExport
void Union_finalize(
        Union* self);
                        
NDDSUSERDllExport
void Union_finalize_ex(
        Union* self,RTIBool deletePointers);
        
NDDSUSERDllExport
RTIBool Union_copy(
        Union* dst,
        const Union* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif


#ifdef __cplusplus
extern "C" {
#endif

        
extern const char *UnionsTYPENAME;
        

#ifdef __cplusplus
}
#endif

typedef struct Unions
{
    Union  u_n_i_o_n;

} Unions;
    
                            
#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

    
NDDSUSERDllExport DDS_TypeCode* Unions_get_typecode(); /* Type code */
    

DDS_SEQUENCE(UnionsSeq, Unions);
        
NDDSUSERDllExport
RTIBool Unions_initialize(
        Unions* self);
        
NDDSUSERDllExport
RTIBool Unions_initialize_ex(
        Unions* self,RTIBool allocatePointers);

NDDSUSERDllExport
void Unions_finalize(
        Unions* self);
                        
NDDSUSERDllExport
void Unions_finalize_ex(
        Unions* self,RTIBool deletePointers);
        
NDDSUSERDllExport
RTIBool Unions_copy(
        Unions* dst,
        const Unions* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif



#endif /* Unions_h */
