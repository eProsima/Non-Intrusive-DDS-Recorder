
/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from ComplextypeInSequence.idl using "rtiddsgen".
  The rtiddsgen tool is part of the RTI Connext distribution.
  For more information, type 'rtiddsgen -help' at a command shell
  or consult the RTI Connext manual.
*/

#ifndef ComplextypeInSequence_564124009_h
#define ComplextypeInSequence_564124009_h

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

        
extern const char *EstructuraTYPENAME;
        

#ifdef __cplusplus
}
#endif


#ifdef __cplusplus
    struct EstructuraSeq;

#ifndef NDDS_STANDALONE_TYPE
    class EstructuraTypeSupport;
    class EstructuraDataWriter;
    class EstructuraDataReader;
#endif

#endif

            
    
class Estructura                                        
{
public:            
#ifdef __cplusplus
    typedef struct EstructuraSeq Seq;

#ifndef NDDS_STANDALONE_TYPE
    typedef EstructuraTypeSupport TypeSupport;
    typedef EstructuraDataWriter DataWriter;
    typedef EstructuraDataReader DataReader;
#endif

#endif
    
    DDS_Long  id;

    char*  msg; /* maximum length = (255) */

            
};                        
    
                            
#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

    
NDDSUSERDllExport DDS_TypeCode* Estructura_get_typecode(void); /* Type code */
    

DDS_SEQUENCE(EstructuraSeq, Estructura);
        
NDDSUSERDllExport
RTIBool Estructura_initialize(
        Estructura* self);
        
NDDSUSERDllExport
RTIBool Estructura_initialize_ex(
        Estructura* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
void Estructura_finalize(
        Estructura* self);
                        
NDDSUSERDllExport
void Estructura_finalize_ex(
        Estructura* self,RTIBool deletePointers);
        
NDDSUSERDllExport
RTIBool Estructura_copy(
        Estructura* dst,
        const Estructura* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif


typedef  EstructuraSeq  Estructura_seq;
        
        
#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols. */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

    
NDDSUSERDllExport DDS_TypeCode* Estructura_seq_get_typecode(void); /* Type code */
    
DDS_SEQUENCE(Estructura_seqSeq, Estructura_seq);                                        
            
NDDSUSERDllExport
RTIBool Estructura_seq_initialize(
        Estructura_seq* self);
            
NDDSUSERDllExport
RTIBool Estructura_seq_initialize_ex(
        Estructura_seq* self,RTIBool allocatePointers,RTIBool allocateMemory);
                    
NDDSUSERDllExport
void Estructura_seq_finalize(
        Estructura_seq* self);
            
NDDSUSERDllExport
void Estructura_seq_finalize_ex(
        Estructura_seq* self,RTIBool deletePointers);
                    
NDDSUSERDllExport
RTIBool Estructura_seq_copy(
        Estructura_seq* dst,
        const Estructura_seq* src);

    

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols. */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif


#ifdef __cplusplus
extern "C" {
#endif

        
extern const char *CompletypeInSequenceTYPENAME;
        

#ifdef __cplusplus
}
#endif


#ifdef __cplusplus
    struct CompletypeInSequenceSeq;

#ifndef NDDS_STANDALONE_TYPE
    class CompletypeInSequenceTypeSupport;
    class CompletypeInSequenceDataWriter;
    class CompletypeInSequenceDataReader;
#endif

#endif

            
    
class CompletypeInSequence                                        
{
public:            
#ifdef __cplusplus
    typedef struct CompletypeInSequenceSeq Seq;

#ifndef NDDS_STANDALONE_TYPE
    typedef CompletypeInSequenceTypeSupport TypeSupport;
    typedef CompletypeInSequenceDataWriter DataWriter;
    typedef CompletypeInSequenceDataReader DataReader;
#endif

#endif
    
    Estructura_seq  seq;

            
};                        
    
                            
#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

    
NDDSUSERDllExport DDS_TypeCode* CompletypeInSequence_get_typecode(void); /* Type code */
    

DDS_SEQUENCE(CompletypeInSequenceSeq, CompletypeInSequence);
        
NDDSUSERDllExport
RTIBool CompletypeInSequence_initialize(
        CompletypeInSequence* self);
        
NDDSUSERDllExport
RTIBool CompletypeInSequence_initialize_ex(
        CompletypeInSequence* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
void CompletypeInSequence_finalize(
        CompletypeInSequence* self);
                        
NDDSUSERDllExport
void CompletypeInSequence_finalize_ex(
        CompletypeInSequence* self,RTIBool deletePointers);
        
NDDSUSERDllExport
RTIBool CompletypeInSequence_copy(
        CompletypeInSequence* dst,
        const CompletypeInSequence* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif



#endif /* ComplextypeInSequence_564124009_h */
