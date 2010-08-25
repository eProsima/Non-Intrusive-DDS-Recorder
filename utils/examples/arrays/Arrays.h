
/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from Arrays.idl using "rtiddsgen".
  The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
  For more information, type 'rtiddsgen -help' at a command shell
  or consult the RTI Data Distribution Service manual.
*/

#ifndef Arrays_h
#define Arrays_h

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
    DDS_Long  count;
    DDS_Octet  ocarray[10][2];
    DDS_Short  sharray[10][2];
    DDS_UnsignedShort  usharray[10][2];
    DDS_Long  loarray[10][2];
    DDS_UnsignedLong  uloarray[10][2];
    DDS_LongLong  loloarray[10][2];
    DDS_UnsignedLongLong  uloloarray[10][2];
    DDS_Char  charray[10][2];
    DDS_Float  flarray[10][2];
    DDS_Double  dlarray[10][2];

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

        
extern const char *ArraysTYPENAME;
        

#ifdef __cplusplus
}
#endif

typedef struct Arrays
{
    char*  message; /* maximum length = (255) */
    DDS_Octet  ocarray[20];
    DDS_Short  sharray[20];
    DDS_UnsignedShort  usharray[20];
    DDS_Long  loarray[20];
    DDS_UnsignedLong  uloarray[20];
    DDS_LongLong  loloarray[20];
    DDS_UnsignedLongLong  uloloarray[20];
    DDS_Char  charray[20];
    DDS_Float  flarray[20];
    DDS_Double  dlarray[20];
    Inside  ins;

} Arrays;
    
                            
#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

    
NDDSUSERDllExport DDS_TypeCode* Arrays_get_typecode(); /* Type code */
    

DDS_SEQUENCE(ArraysSeq, Arrays);
        
NDDSUSERDllExport
RTIBool Arrays_initialize(
        Arrays* self);
        
NDDSUSERDllExport
RTIBool Arrays_initialize_ex(
        Arrays* self,RTIBool allocatePointers);

NDDSUSERDllExport
void Arrays_finalize(
        Arrays* self);
                        
NDDSUSERDllExport
void Arrays_finalize_ex(
        Arrays* self,RTIBool deletePointers);
        
NDDSUSERDllExport
RTIBool Arrays_copy(
        Arrays* dst,
        const Arrays* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif



#endif /* Arrays_h */
