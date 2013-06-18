
/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from HelloWorld.idl using "rtiddsgen".
  The rtiddsgen tool is part of the RTI Connext distribution.
  For more information, type 'rtiddsgen -help' at a command shell
  or consult the RTI Connext manual.
*/

#ifndef HelloWorld_1436885509_h
#define HelloWorld_1436885509_h

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

        
extern const char *HelloWorldTYPENAME;
        

#ifdef __cplusplus
}
#endif


#ifdef __cplusplus
    struct HelloWorldSeq;

#ifndef NDDS_STANDALONE_TYPE
    class HelloWorldTypeSupport;
    class HelloWorldDataWriter;
    class HelloWorldDataReader;
#endif

#endif

            
    
class HelloWorld                                        
{
public:            
#ifdef __cplusplus
    typedef struct HelloWorldSeq Seq;

#ifndef NDDS_STANDALONE_TYPE
    typedef HelloWorldTypeSupport TypeSupport;
    typedef HelloWorldDataWriter DataWriter;
    typedef HelloWorldDataReader DataReader;
#endif

#endif
    
    DDS_Long  counter;

    char*  message; /* maximum length = (255) */

            
};                        
    
                            
#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

    
NDDSUSERDllExport DDS_TypeCode* HelloWorld_get_typecode(void); /* Type code */
    

DDS_SEQUENCE(HelloWorldSeq, HelloWorld);
        
NDDSUSERDllExport
RTIBool HelloWorld_initialize(
        HelloWorld* self);
        
NDDSUSERDllExport
RTIBool HelloWorld_initialize_ex(
        HelloWorld* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
void HelloWorld_finalize(
        HelloWorld* self);
                        
NDDSUSERDllExport
void HelloWorld_finalize_ex(
        HelloWorld* self,RTIBool deletePointers);
        
NDDSUSERDllExport
RTIBool HelloWorld_copy(
        HelloWorld* dst,
        const HelloWorld* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif



#endif /* HelloWorld_1436885509_h */
