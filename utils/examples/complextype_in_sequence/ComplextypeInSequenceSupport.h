
/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from ComplextypeInSequence.idl using "rtiddsgen".
  The rtiddsgen tool is part of the RTI Connext distribution.
  For more information, type 'rtiddsgen -help' at a command shell
  or consult the RTI Connext manual.
*/

#ifndef ComplextypeInSequenceSupport_564124009_h
#define ComplextypeInSequenceSupport_564124009_h

/* Uses */
#include "ComplextypeInSequence.h"



#ifdef __cplusplus
#ifndef ndds_cpp_h
  #include "ndds/ndds_cpp.h"
#endif
#else
#ifndef ndds_c_h
  #include "ndds/ndds_c.h"
#endif
#endif

        

/* ========================================================================= */
/**
   Uses:     T

   Defines:  TTypeSupport, TDataWriter, TDataReader

   Organized using the well-documented "Generics Pattern" for
   implementing generics in C and C++.
*/

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)

#ifdef __cplusplus
  /* If we're building on Windows, explicitly import the superclasses of
   * the types declared below.
   */        
  class __declspec(dllimport) DDSTypeSupport;
  class __declspec(dllimport) DDSDataWriter;
  class __declspec(dllimport) DDSDataReader;
#endif

#endif

#ifdef __cplusplus

DDS_TYPESUPPORT_CPP(EstructuraTypeSupport, Estructura);

DDS_DATAWRITER_CPP(EstructuraDataWriter, Estructura);
DDS_DATAREADER_CPP(EstructuraDataReader, EstructuraSeq, Estructura);


#else

DDS_TYPESUPPORT_C(EstructuraTypeSupport, Estructura);
DDS_DATAWRITER_C(EstructuraDataWriter, Estructura);
DDS_DATAREADER_C(EstructuraDataReader, EstructuraSeq, Estructura);

#endif

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif

        

/* ========================================================================= */
/**
   Uses:     T

   Defines:  TTypeSupport, TDataWriter, TDataReader

   Organized using the well-documented "Generics Pattern" for
   implementing generics in C and C++.
*/

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)

#ifdef __cplusplus
  /* If we're building on Windows, explicitly import the superclasses of
   * the types declared below.
   */        
  class __declspec(dllimport) DDSTypeSupport;
  class __declspec(dllimport) DDSDataWriter;
  class __declspec(dllimport) DDSDataReader;
#endif

#endif

#ifdef __cplusplus

DDS_TYPESUPPORT_CPP(CompletypeInSequenceTypeSupport, CompletypeInSequence);

DDS_DATAWRITER_CPP(CompletypeInSequenceDataWriter, CompletypeInSequence);
DDS_DATAREADER_CPP(CompletypeInSequenceDataReader, CompletypeInSequenceSeq, CompletypeInSequence);


#else

DDS_TYPESUPPORT_C(CompletypeInSequenceTypeSupport, CompletypeInSequence);
DDS_DATAWRITER_C(CompletypeInSequenceDataWriter, CompletypeInSequence);
DDS_DATAREADER_C(CompletypeInSequenceDataReader, CompletypeInSequenceSeq, CompletypeInSequence);

#endif

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif



#endif  /* ComplextypeInSequenceSupport_564124009_h */
