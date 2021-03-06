// -*- C++ -*-
//
// $Id$

// ****  Code generated by the The ACE ORB (TAO) IDL Compiler v1.6a_p13 ****
// TAO and the TAO IDL Compiler have been developed by:
//       Center for Distributed Object Computing
//       Washington University
//       St. Louis, MO
//       USA
//       http://www.cs.wustl.edu/~schmidt/doc-center.html
// and
//       Distributed Object Computing Laboratory
//       University of California at Irvine
//       Irvine, CA
//       USA
//       http://doc.ece.uci.edu/
// and
//       Institute for Software Integrated Systems
//       Vanderbilt University
//       Nashville, TN
//       USA
//       http://www.isis.vanderbilt.edu/
//
// Information about TAO is available at:
//     http://www.cs.wustl.edu/~schmidt/TAO.html

// TAO_IDL - Generated from
// be\be_codegen.cpp:381


#include "HelloWorldC.h"
#include "tao/AnyTypeCode/Null_RefCount_Policy.h"
#include "tao/AnyTypeCode/TypeCode_Constants.h"
#include "tao/AnyTypeCode/Alias_TypeCode_Static.h"
#include "tao/AnyTypeCode/String_TypeCode_Static.h"
#include "tao/AnyTypeCode/Struct_TypeCode_Static.h"
#include "tao/AnyTypeCode/TypeCode_Struct_Field.h"
#include "tao/CDR.h"
#include "tao/CDR.h"
#include "tao/AnyTypeCode/Any_Dual_Impl_T.h"

#if !defined (__ACE_INLINE__)
#include "HelloWorldC.inl"
#endif /* !defined INLINE */

// TAO_IDL - Generated from
// be\be_visitor_arg_traits.cpp:73

TAO_BEGIN_VERSIONED_NAMESPACE_DECL


// Arg traits specializations.
namespace TAO
{
}

TAO_END_VERSIONED_NAMESPACE_DECL



// TAO_IDL - Generated from
// d:\richi\workspace\desarrollo\dds\opendds\instalaciones\opendds3.3\ace_wrappers_x64\tao\tao_idl\be\be_visitor_typecode/struct_typecode.cpp:84

static TAO::TypeCode::Struct_Field<
  char const *,
  ::CORBA::TypeCode_ptr const *> const 
    _tao_fields_HelloWorld[] =
      {
        { "counter", &CORBA::_tc_long },
        { "message", &CORBA::_tc_string }
      };
  
static TAO::TypeCode::Struct<
  char const *,
  ::CORBA::TypeCode_ptr const *,
  TAO::TypeCode::Struct_Field<
    char const *,
    ::CORBA::TypeCode_ptr const *> const *,
  TAO::Null_RefCount_Policy>
_tao_tc_HelloWorld (
  ::CORBA::tk_struct,
  "IDL:HelloWorld:1.0",
  "HelloWorld",
  _tao_fields_HelloWorld,
  2);

::CORBA::TypeCode_ptr const _tc_HelloWorld =
  &_tao_tc_HelloWorld;

// TAO_IDL - Generated from 
// d:\richi\workspace\desarrollo\dds\opendds\instalaciones\opendds3.3\ace_wrappers_x64\tao\tao_idl\be\be_visitor_structure/structure_cs.cpp:65

void 
HelloWorld::_tao_any_destructor (
    void *_tao_void_pointer
  )
{
  HelloWorld *_tao_tmp_pointer =
    static_cast<HelloWorld *> (_tao_void_pointer);
  delete _tao_tmp_pointer;
}

// TAO_IDL - Generated from 
// d:\richi\workspace\desarrollo\dds\opendds\instalaciones\opendds3.3\ace_wrappers_x64\tao\tao_idl\be\be_visitor_structure/any_op_cs.cpp:54


TAO_BEGIN_VERSIONED_NAMESPACE_DECL

// Copying insertion.
void operator<<= (
    ::CORBA::Any &_tao_any,
    const HelloWorld &_tao_elem
  )
{
  if (0 == &_tao_elem) // Trying to de-reference NULL object
    _tao_any <<= static_cast<HelloWorld *>( 0 ); // Use non-copying insertion of a NULL
  else
    TAO::Any_Dual_Impl_T<HelloWorld>::insert_copy (
        _tao_any,
        HelloWorld::_tao_any_destructor,
        _tc_HelloWorld,
        _tao_elem
      );
}

// Non-copying insertion.
void operator<<= (
    ::CORBA::Any &_tao_any,
    HelloWorld *_tao_elem
  )
{
  TAO::Any_Dual_Impl_T<HelloWorld>::insert (
      _tao_any,
      HelloWorld::_tao_any_destructor,
      _tc_HelloWorld,
      _tao_elem
    );
}

// Extraction to non-const pointer (deprecated).
::CORBA::Boolean operator>>= (
    const ::CORBA::Any &_tao_any,
    HelloWorld *&_tao_elem
  )
{
  return _tao_any >>= const_cast<
      const HelloWorld *&> (
      _tao_elem
    );
}

// Extraction to const pointer.
::CORBA::Boolean operator>>= (
    const ::CORBA::Any &_tao_any,
    const HelloWorld *&_tao_elem
  )
{
  return
    TAO::Any_Dual_Impl_T<HelloWorld>::extract (
        _tao_any,
        HelloWorld::_tao_any_destructor,
        _tc_HelloWorld,
        _tao_elem
      );
}
TAO_END_VERSIONED_NAMESPACE_DECL



// TAO_IDL - Generated from
// d:\richi\workspace\desarrollo\dds\opendds\instalaciones\opendds3.3\ace_wrappers_x64\tao\tao_idl\be\be_visitor_structure/cdr_op_cs.cpp:61


TAO_BEGIN_VERSIONED_NAMESPACE_DECL

::CORBA::Boolean operator<< (
    TAO_OutputCDR &strm,
    const HelloWorld &_tao_aggregate
  )
{
  return
    (strm << _tao_aggregate.counter) &&
    (strm << _tao_aggregate.message.in ());
}

::CORBA::Boolean operator>> (
    TAO_InputCDR &strm,
    HelloWorld &_tao_aggregate
  )
{
  return
    (strm >> _tao_aggregate.counter) &&
    (strm >> _tao_aggregate.message.out ());
}

TAO_END_VERSIONED_NAMESPACE_DECL



