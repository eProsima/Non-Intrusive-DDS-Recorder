
/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from Sequences.idl using "rtiddsgen".
  The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
  For more information, type 'rtiddsgen -help' at a command shell
  or consult the RTI Data Distribution Service manual.
*/

#ifndef Sequences_h
#define Sequences_h

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
    DDS_Short  count;
     DDS_OctetSeq  seoc;
     DDS_ShortSeq  sesh;
     DDS_UnsignedShortSeq  seush;
     DDS_LongSeq  selo;
     DDS_UnsignedLongSeq  seulo;
     DDS_LongLongSeq  selolo;
     DDS_UnsignedLongLongSeq  seulolo;
     DDS_CharSeq  sech;
     DDS_FloatSeq  sefl;
     DDS_DoubleSeq  sedl;

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

        
extern const char *SequencesTYPENAME;
        

#ifdef __cplusplus
}
#endif

typedef struct Sequences
{
    char*  message; /* maximum length = (255) */
     DDS_OctetSeq  seoc;
     DDS_ShortSeq  sesh;
     DDS_UnsignedShortSeq  seush;
     DDS_LongSeq  selo;
     DDS_UnsignedLongSeq  seulo;
     DDS_LongLongSeq  selolo;
     DDS_UnsignedLongLongSeq  seulolo;
     DDS_CharSeq  sech;
     DDS_FloatSeq  sefl;
     DDS_DoubleSeq  sedl;
    Inside  ins;

} Sequences;
    
                            
#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

    
NDDSUSERDllExport DDS_TypeCode* Sequences_get_typecode(); /* Type code */
    

DDS_SEQUENCE(SequencesSeq, Sequences);
        
NDDSUSERDllExport
RTIBool Sequences_initialize(
        Sequences* self);
        
NDDSUSERDllExport
RTIBool Sequences_initialize_ex(
        Sequences* self,RTIBool allocatePointers);

NDDSUSERDllExport
void Sequences_finalize(
        Sequences* self);
                        
NDDSUSERDllExport
void Sequences_finalize_ex(
        Sequences* self,RTIBool deletePointers);
        
NDDSUSERDllExport
RTIBool Sequences_copy(
        Sequences* dst,
        const Sequences* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif



#endif /* Sequences_h */
