	/* @(#)idl.y 0.1 92/07/04 Copyright (C) 1992 MITRE */
	/******** DEFINITIONS SECTION *******/


%{

#include <vector>
#include <string>
#include <utility>
#include <iostream>

#include "cdr/TypeCode.h"
namespace yy{
typedef std::pair<std::string,std::vector<int32_t>> Declarator;
typedef std::vector<Declarator*> DeclaratorVec;
typedef std::vector<Member*> MemberVec;
typedef std::vector<std::string> StringVec;
typedef std::vector<TypeCode*> TypeCodeVec;
enum LiteralType{ BOOL_TYPE, NUMBER_TYPE,STRING_TYPE,SCOPED_TYPE};
struct TypeLiteral{
	LiteralType type;
	std::string str;
	float num;
	bool boolean;
};
}
%}

/* Just to see how, explicitly show the default type, namely Integer */
%union {TypeCodeVec;
		Declarator; DeclaratorVec;
		MemberVec; Member;
		StringVec; TypeLiteral;
		;default TypeCode}

%token <Integer> INTEGER_LITERAL LONG_LITERAL
%token <Integer> FLOAT_LITERAL DOUBLE_LITERAL
%token <Integer> BOOLEAN_LITERAL
%token <Integer> STRING_LITERAL CHARACTER_LITERAL
%token <Integer> IDENTIFIER
%token <Integer> ANY_TOKEN ATTRIBUTE_TOKEN BOOLEAN_TOKEN CASE_TOKEN
%token <Integer> CHAR_TOKEN CONST_TOKEN CONTEXT_TOKEN DEFAULT_TOKEN
%token <Integer> DOUBLE_TOKEN ENUM_TOKEN EXCEPTION_TOKEN FLOAT_TOKEN
%token <Integer> IN_TOKEN INOUT_TOKEN INTERFACE_TOKEN LONG_TOKEN
%token <Integer> MODULE_TOKEN OCTET_TOKEN ONEWAY_TOKEN OUT_TOKEN
%token <Integer> RAISES_TOKEN READONLY_TOKEN SEQUENCE_TOKEN SHORT_TOKEN
%token <Integer> STRING_TOKEN STRUCT_TOKEN SWITCH_TOKEN TYPEDEF_TOKEN
%token <Integer> UNSIGNED_TOKEN UNION_TOKEN VOID_TOKEN OBJECT_TOKEN
%token <Integer> RESOLVE_TOKEN SHIFTLEFT_TOKEN SHIFTRIGHT_TOKEN
%token <Integer> ';' '{' '}' ':' ',' '=' '+' '-' '(' ')' '<' '>' '[' ']' '|'
%token <Integer> '^' '&' '*' '/' '%' '~'
%token <Integer> '\'' '"' '\\' /* apparently not used */
%token <YYtoken> PRAGMA_INFO IDENT_INFO LINE_AND_FILE_INFO

%left '|'
%left '^'
%left '&'
%left SHIFTLEFT_TOKEN SHIFTRIGHT_TOKEN
%left '-' '+'
%left '*' '/' '%'
%left NEG POS NOT    /* unary minus,plus,not */

/*

REMOVED SECTION 4
*/
%type <TypeCodeVec> type_dcl const_dcl except_dcl interface module sharp_declaratives export
%type <TypeCode> base_type_spec simple_type_spec type_spec
%type <TypeCode> floating_pt_type integer_type signed_int signed_long_int
%type <TypeCode> signed_short_int unsigned_int unsigned_long_int unsigned_short_int
%type <TypeCode> char_type boolean_type octet_type object_type any_type
%type <TypeCode> template_type_spec 
%type <TypeCodeVec> struct_type union_type enum_type constr_type_spec
%type <TypeCode> sequence_type string_type
%type <TypeCodeVec> specification definition_list definition
%type <TypeCodeVec> forward_dcl interface_dcl interface_body op_dcl

%type <MemberVec> struct_member_list struct_member switch_body
%type <DeclaratorVec> declarators
%type <Declarator> declarator simple_declarator complex_declarator fixed_array_size_list
%type <Declarator> array_declarator
%type <uint32_t> fixed_array_size positive_int_const
%type <StringVec> enumerator_list
%type <std::string> enumerator interface_header inheritance_spec scoped_name_list
%type <std::string> res_scoped_name scoped_name_str
%type <TypeCode> scoped_name

%type <TypeCode> switch_type_spec
%type <Member> element_spec
%type <Declarator> case_label_list case_label case

%type <TypeCode> simple_declarators attr_dcl

%type <TypeLiteral> literal expr

%type <uint32_t> op_dcl_cont op_attribute op_type_spec parameter_dcls param_dcl_list 
%type <uint32_t> param_dcl param_attribute	raises_expr context_expr string_literal_list param_type_spec




%start specification

%skeleton "lalr1.cc"
%define "parser_class_name" "eprosimaidlparser"
%defines
%%



	/******* RULES SECTION *******/

specification : definition_list
    {$$ = $1; }
    ;
definition_list : 
    definition
	{
	$$ = $1;
	}
    | definition definition_list
	{
	for(TypeCodeVec::iterator it = $2->begin();it!=$2->end();++it)
	{
	$1.push_back(*it);
	}
	delete($2);
	$$ = $1;
	}
    ;
definition : 
    type_dcl ';' {$$ = $1;}
    | const_dcl ';' {$$ = $1;}
    | except_dcl ';' {$$ = $1;}
    | interface ';' {$$ = $1;}
    | module ';' {$$ = $1;}
    | sharp_declaratives {$$ = $1;}
    
sharp_declaratives:
      PRAGMA_INFO
	{$$ = new TypeCodeVec();}
    | IDENT_INFO
	{$$ = new TypeCodeVec();}
    | LINE_AND_FILE_INFO
	{$$ = new TypeCodeVec();}
    ;    

module : MODULE_TOKEN IDENTIFIER '{' definition_list '}'
	{
	for(TypeCodeVec::iterator it = $4->begin();it!=$4->end();++it)
	{
	if((*it)->getKind() == TypeCode::KIND_STRUCT || 
		(*it)->getKind() == TypeCode::KIND_UNION) ||
		(*it)->getKind() == TypeCode::KIND_ENUM)
	{
		MemberedTypeCode* membered = (MemberedTypeCode*)(*it);
		membered->setName(std::string($2).append("::").append(membered->getName()));
	}
	}
	$$ = $4;
	}
    ;

type_dcl : 
    TYPEDEF_TOKEN ';'
	{std::cout << "Warning: \"typedef\" token not allowed" << std::endl;}
    | struct_type
    | union_type
    | enum_type
    ;
   
struct_type : STRUCT_TOKEN  IDENTIFIER '{'  struct_member_list  '}'
	{TypeCode* sTC = (TypeCode*) new StructTypeCode($2);
	for(MemberVec::iterator it= $4->begin();it!=$4->end();++it)
	{
		sTC.addMember(std::dynamic_cast<StructMember*>(*it));
	}
	$$ = new TypeCodeVec();
	$$->push_back(sTC);
	}
    ;
struct_member_list : 
    struct_member
	{$$ = $1;}
    | struct_member struct_member_list
	{
	if($1 ==NULL)
		$$ = $2;
	else
	{
	for(std::vector<Member*>::iterator it = $1->begin();it!=$1->end();++it)
	{
		$2->push_back(*it);
	}
	delete($1);
	$$ = $2;
	}
	}
    ;
struct_member : type_spec declarators ';'
	{
	if($1->getKind() == TypeCode::KIND_NULL)
	{
		delete($1);
		delete($2);
		$$ = NULL;
	}
	else
	{
	MemberVec MV = new MemberVec();
	bool first = true;
	for(DeclaratorVec::iterator it=$2.begin();it!=$2.end();++it)
	{
		TypeCode* pTC = $1;
		if(!first)
		{
			switch(pTC->getKind())
			{
			case TypeCode::KIND_SHORT:
			{
				pTC = new PrimitiveTypeCode(TypeCode::KIND_SHORT);
				break;
			}
			// TO FINISH THIS FOR ALL TYPES
			}
		}
		first = false;
		StructMember* sm = new StructMember(it.first,0,0);
		if(it.second.size()==0)
		{
			sm->m_typeCode = pTC;
		}
		else
		{
			ArrayTypeCode* ar = new ArrayTypeCode(it.second);
			ar.setContentTypeCode(pTC);
			sm->m_typeCode = ar;
		}
		MV->push_back(MV);
	}
	delete($2);
	$$ = MV;
	}
	}
    ;   
 /*
 
 REMOVED SECTION 5
 */  

type_spec : 
    simple_type_spec
    | constr_type_spec
    {
    $$ = *$1.begin();
    delete($1);
    }
    ;
simple_type_spec : 
    base_type_spec
    | template_type_spec
    | scoped_name
    ;
    
scoped_name : scoped_name_str
    {
    TypeCode* pTC = findTypeCodebyName($1);
    $$ = pTC;
    }
    ;

    
    
base_type_spec	: 
    floating_pt_type
    | integer_type
    | char_type
    | boolean_type
    | octet_type
    | any_type
    | object_type
    ;
object_type : OBJECT_TOKEN
	{
	std::cout << "Warning: \"Object\" token not allowed" << std::endl;
	$$ = new PrimitiveTypeCode(TypeCode::KIND_NULL);
	}
    ;
any_type : ANY_TOKEN
	{std::cout << "Warning: \"any\" token not allowed" << std::endl;
	$$ = new PrimitiveTypeCode(TypeCode::KIND_NULL);}
    ;
template_type_spec : 
    sequence_type
    | string_type
    ;
constr_type_spec : 
    struct_type
    | union_type
    | enum_type
    ;
declarators : 
    declarator
	{
	$$ = new DeclaratorVec();
	$$->push_back($1);
	}
    | declarator  ','  declarators
	{
	$3->push_back($1); 
	$$ = $3;
	}
    ;
declarator : 
    simple_declarator
    | complex_declarator
    ;
simple_declarator : IDENTIFIER
	{
	$$ = new Declarator();
	$$->first = $1;
	}
    ;
complex_declarator : array_declarator
    ;
    
array_declarator : IDENTIFIER  fixed_array_size_list
	{
	$2->first = $1;
	$$ = $2;
	}	
    ;
fixed_array_size_list : 
    fixed_array_size
	{
	$$ = new Declarator();
	$$->second.push_back($1);
	}	
    | fixed_array_size fixed_array_size_list
	{
	$2->push_back($1); 
	$$ = $2;}
    ;
fixed_array_size : '['  positive_int_const  ']'
	{$$ = $2;}
    ;    
    
    
floating_pt_type : 
    FLOAT_TOKEN
	{$$ = new PrimitiveTypeCode(TypeCode::KIND_FLOAT);}
    |  DOUBLE_TOKEN
	{$$ = new PrimitiveTypeCode(TypeCode::KIND_DOUBLE);}
	|  LONG_TOKEN DOUBLE_TOKEN
	{$$ = new PrimitiveTypeCode(TypeCode::KIND_LONGDOUBLE);}	
    ;
integer_type : 
    signed_int
    | unsigned_int
    ;
signed_int : 
    signed_long_int
    | signed_short_int
    ;
signed_long_int	: LONG_TOKEN
	{$$ = new PrimitiveTypeCode(TypeCode::KIND_LONG);}
	| LONG_TOKEN LONG_TOKEN
	{$$ = new PrimitiveTypeCode(TypeCode::KIND_LONGLONG);}
    ;
signed_short_int : SHORT_TOKEN
	{$$ = new PrimitiveTypeCode(TypeCode::KIND_SHORT);}
    ;
unsigned_int : 
    unsigned_long_int
    | unsigned_short_int
    ;
unsigned_long_int : UNSIGNED_TOKEN LONG_TOKEN
	{$$ = new PrimitiveTypeCode(TypeCode::KIND_ULONG);}
	| UNSIGNED_TOKEN LONG_TOKEN LONG_TOKEN
	{$$ = new PrimitiveTypeCode(TypeCode::KIND_ULONGLONG);}
    ;
unsigned_short_int : UNSIGNED_TOKEN SHORT_TOKEN
	{$$ = new PrimitiveTypeCode(TypeCode::KIND_USHORT);}
    ;
char_type : CHAR_TOKEN
	{$$ = new PrimitiveTypeCode(TypeCode::KIND_CHAR);}
    ;
boolean_type : BOOLEAN_TOKEN
	{$$ = new PrimitiveTypeCode(TypeCode::KIND_BOOLEAN);}
    ;
octet_type : OCTET_TOKEN
	{$$ = new PrimitiveTypeCode(TypeCode::KIND_OCTET);}
    ;


enum_type : ENUM_TOKEN IDENTIFIER '{' enumerator_list  '}'
	{
	EnumTypeCode* enTC= new EnumTypeCode();
	enTC->setName($2);
	uint32_t ord = 0;
	for(StringVec::iterator it=$4.begin();it!=$4.end();++it)
	{
		EnumMember* eMember = new EnumMember(*it,ord);
		enTC->addMember(eMember);
		++ord;
	}
	delete($4);
	$$ = (TypeCode*) enTC;
	}
    ;
enumerator_list	: enumerator
	{
	$$ = new StringVec();
	$$->push_back($1);
	}
    | enumerator ',' enumerator_list
	{$3->push_back($1); $$ = $3;}
    ; 
enumerator : IDENTIFIER
	{$$ = $1;}
    ;

string_type : 
    STRING_TOKEN  '<'  positive_int_const  '>'
	{$$ = (TypeCode*)new StringTypeCode($3);}	
    | STRING_TOKEN		/* NULL=UNBOUNDED */
	{$$ = TypeCode*) new StringTypeCode(255);}	
    ;  

sequence_type : 
    SEQUENCE_TOKEN '<' simple_type_spec ',' positive_int_const '>'
	{
	SequenceTypeCode* sTC = new SequenceTypeCode($5);
	sTC->setContentTypeCode($3);
	$$ = (TypeCode*) sTC;
	}	
    | SEQUENCE_TOKEN  '<'  simple_type_spec  '>'
	{
	SequenceTypeCode* sTC = new SequenceTypeCode(255);
	sTC->setContentTypeCode($3);
	$$ = (TypeCode*) sTC;
	}
    ;

interface:
      interface_dcl
    | forward_dcl 
    ;

interface_dcl : interface_header '{' interface_body '}'
	{
	std::vector<int> index_to_remove;
	for(TypeCodeVec::iterator it = $3->begin();it!=$3->end();++it)
	{
	if((*it)->getKind() == TypeCode::KIND_STRUCT || 
		(*it)->getKind() == TypeCode::KIND_UNION) ||
		(*it)->getKind() == TypeCode::KIND_ENUM)
	{
		MemberedTypeCode* membered = (MemberedTypeCode*)(*it);
		membered->setName(std::string($1).append("::").append(membered->getName()));
	}
	else
	{
		delete(*it);
		index_to_remove.push_back(std::distance($4->begin());
	}
	for(std::vector<int>::reverse_iterator it = index_to_remove.rbegin();it!=index_to_remove.rend();++it)
	{
		$4->erase($4->begin()+(*it));
	}
	}
	$$ = $4;
	}
    ;
forward_dcl : INTERFACE_TOKEN IDENTIFIER
	{$$ = new TypeCodeVec();}
    ;
interface_header : 
    INTERFACE_TOKEN IDENTIFIER
	{$$ = std::string($2);}
    | INTERFACE_TOKEN IDENTIFIER inheritance_spec
	{$$ = std::string($2);}
    ;
interface_body  :  /*NULL*/
	{$$ = new TypeCodeVec();}
    | export interface_body
	{
	for(TypeCodeVec::iterator it = $2->begin();it!=$2->end();++it)
		$1->push_back(*it);
	$$ = $1;
	delete($2);
	}
    ;
export : 
    type_dcl ';'
    | const_dcl ';'
    | except_dcl ';'
    | attr_dcl ';'
    {
    delete($1);
    $$ = new TypeCodeVec();
    }
    | op_dcl ';'
    ;
inheritance_spec : ':' scoped_name_list
	{$$ = std::string("");}
	;

scoped_name_list : 
    scoped_name_str
	{$$ = std::string("");
	delete($1);}
    | scoped_name_str ',' scoped_name_list
	{$$ = std::string("");
	delete($1);}
    ;
scoped_name_str : 
    IDENTIFIER
	{
	$$ = std::string($1);
	}
    | IDENTIFIER RESOLVE_TOKEN scoped_name_str
	{
	$$ = std::string($1).append("::").append($3);
	}
    | res_scoped_name
    ;
res_scoped_name : 
    RESOLVE_TOKEN IDENTIFIER
	{$$ = std::string("::").append($2);}
    | RESOLVE_TOKEN IDENTIFIER res_scoped_name
	{$$ = std::string("::").append($2).append($3);}
    ;


union_type : UNION_TOKEN IDENTIFIER SWITCH_TOKEN '(' switch_type_spec  ')' '{' switch_body '}'
	{
	UnionTypeCode* uTC = new UnionTypeCode();
	uTC->setName($2);
	uTC->setDiscriminatorTypeCode($5);
	UnionMember* uM_boolWithDefault = NULL;
	bool isTrue = false;
	for(MemberVec::iterator it = $8->begin();it!=$8->end();++it)
	{
		(UnionMemeber*) uM = (UnionMember*)(*it);
		std::vector<int32_t> labels = uM->getLabels();
		bool change = false;
		bool boolDefaultFound = false;
		for(std::vector<int32_t>::iterator it = labels.begin();it!=labels.end();++it)
		{
			if($5->getKind() == KIND_CHAR $$ (*it) == -1000)
			{
				(*it) = 254;
				change = true;
			}
			if($5->getKind() == KIND_ENUM $$ (*it) == -1000)
			{
				(*it) = 0;
				change = true;
			}
			if($5->getKind() == KIND_BOOL $$ (*it) == -1000)
			{
				uM_boolWithDefault = uM;
				boolDefaultFound = true;
			}
			if($5->getKind() == KIND_BOOL)
			{
				isTrue = (bool)(*it);
			}
		}
		if(change)
			uM->setLabels(labels);
		if(!boolDefaultFound)
			uTC->addMember(uM);
	}
	if(uM_boolWithDefault !=NULL)
	{
	std::vector<int32_t> labels = uM_boolWithDefault->getLabels();
	for(std::vector<int32_t>::iterator it = labels.begin();it!=labels.end();++it)
	{ 
		if(*it == -1000)
			*it = !isTrue;
	}
	uM_boolWithDefault->setLabels(labels);
	uTC->addMember(uM_boolWithDefault);
	}
	delete($8);
	$$ = (TypeCode*) uTC;
	}
    ;
    
switch_type_spec : 
    integer_type
    | char_type
    | boolean_type
    | enum_type
    {
    $$ = * $1->begin();
    }
    | scoped_name
    ;
switch_body : 
    case
	{
	$$ = new MemberVec();
	$$->push_back($1);
	}
    | case switch_body
	{
	$2.push_back($1); 
	$$ = $2;
	delete($1);
	}
    ;
case : case_label_list element_spec  ';'
	{
	((UnionMember*)($2))->setLabels($1.second);
	$$ = $2;
	} /* avoid keyword conflict */
    ;
case_label_list : 
    case_label
	{$$ = $1}
    | case_label case_label_list
	{
	$2.second.push_back(*$1.second.begin());
	$$ = $2;
	delete($1);}
    ;
case_label : 
    CASE_TOKEN  expr  ':'
	{
	Declarator * dCL = new Declarator();
	if($1.type == NUMBER_TYPE)
	{
		dCL->second.push_back($1.num);
	}
	else if($1.type == BOOL_TYPE)
	{
		dCL->second.push_back($1.boolean);	
	}
	else if($1.type == STRING_TYPE)
	{
	int32_t sum = 0;
	for(size_t i = 0;i<$1.str.size();++i)
		sum+=$1.str[i];
	dCL->second.push_back(sum);
	}
	else if($1.type == SCOPED_TYPE)
	{
	dCL->second.push_back(findENUMvalue($1.str));
	}
	} /* semantic */
    | DEFAULT_TOKEN ':'	/* NULL=DEFAULT */
	{
	Declarator * dCL = new Declarator();
	dCL->second.push_back(-1000);
	$$ = dCL;
	}
    ;
element_spec : type_spec  declarator
	{
	UnionMember* uM = new UnionMember();
	uM->setName($2->first);
	uM->setTypeCode($1);
	$$ = (Member*) uM;
	}
    ;

attr_dcl : 
    ATTRIBUTE_TOKEN  param_type_spec  simple_declarators
	{std::cout << "Warning: \"attribute\" token not allowed" << std::endl;
	$$ = new PrimitiveTypeCode(TypeCode::KIND_NULL);}	
    | READONLY_TOKEN ATTRIBUTE_TOKEN  param_type_spec  simple_declarators
	{std::cout << "Warning: \"readonly attribute\" token not allowed" << std::endl;
	$$ = new PrimitiveTypeCode(TypeCode::KIND_NULL);}
    ;
simple_declarators :
    simple_declarator
    {
    $$ = NULL;
    }
    | simple_declarator ',' simple_declarators
	{$$ = NULL;}
    ;

op_dcl : 
    op_type_spec  IDENTIFIER  op_dcl_cont
	{$$ = new TypeCodeVec();}
    | op_attribute  op_type_spec  IDENTIFIER op_dcl_cont
	{$$ = new TypeCodeVec();}
    ;
op_dcl_cont :  parameter_dcls raises_expr context_expr
	{$$ = 0;}
    ;
op_attribute : ONEWAY_TOKEN /* does CORBA2 specify others ? */
	{$$ = 0;}
    ;
op_type_spec : 
    param_type_spec
    | VOID_TOKEN		/* NULL==VOID */
	{$$ = 0;}
    ;
parameter_dcls : 
    '(' param_dcl_list ')'
	{$$ = 0;}
    | '('  ')'	/* NULL==EMPTY */
	{$$ = 0;}
    ;
param_dcl_list : 
    param_dcl
	{$$ = 0;}
    | param_dcl ',' param_dcl_list
	{$$ = 0;}
    ;
param_dcl : param_attribute  param_type_spec  simple_declarator
	{$$ = 0;}
    ;
param_attribute	: 
    IN_TOKEN
	{$$ = 0;}
    | OUT_TOKEN
	{$$ = 0;}
    | INOUT_TOKEN
	{$$ = 0;}
    ;
raises_expr : 
    /* empty */	/* NULL==EMPTY */
	{$$ = 0;} /*semantic*/
    | RAISES_TOKEN  '('  scoped_name_list ')'
	{$$ = 0;}
    ;
context_expr : 
    /* empty */	/* NULL==EMPTY */
	{$$ = 0;} /*semantic*/
    | CONTEXT_TOKEN  '('  string_literal_list  ')'
	{$$ = 0;}
    ;
string_literal_list : 
    STRING_LITERAL
	{$$ = 0;}
    | STRING_LITERAL ',' string_literal_list
	{$$ = 0;}
    ;
param_type_spec :
    base_type_spec
    {
    delete($1);
    $$ = 0;
    }
    | string_type
    {
    delete($1);
    $$ = 0;
    }
    | scoped_name
    {
    delete($1);
    $$ = 0;
    }
    ;    








positive_int_const : expr
	{
	if($1.type == NUMBER_TYPE)
		$$ = (uint32_t)$1.num
	else
		$$ = 0;
	delete($1);
	} /* used for semantic check */
    ;

expr :
    scoped_name_str
	{$$ = new LiteralType();
	$$.type = SCOPED_TYPE;
	$$.str = $1;}
    | literal
	{$$ = $1;}
    | '('  expr  ')'
	{$$ = $2;}
    | expr '|' expr
	{
	if($1.type == $3.type && $1.type == BOOL_TYPE)
		$1.boolean = $1.boolean | $3.boolean;
	else if($1.type == $3.type && $1.type == NUMBER_TYPE)
		$1.boolean = $1.boolean | $3.boolean;
	else
		$1.boolean = false;
	$1.type = BOOL_TYPE;
	delete($3);
	$$ = $1;
	}
    | expr '^' expr
	{if($1.type != NUMBER_TYPE || $3.type != NUMBER_TYPE)
	{
		$1.type = NUMBER_TYPE;
		$1.num = 0;
	}
	else
	{
		$1.num = pow($1.num,$3.num);
	}
	delete($3);
	$$ = $1;
	}
    | expr '&' expr
	{
	if($1.type == $3.type && $1.type == BOOL_TYPE)
		$1.boolean = $1.boolean & $3.boolean;
	else if($1.type == $3.type && $1.type == NUMBER_TYPE)
		$1.boolean = $1.boolean & $3.boolean;
	else
		$1.boolean = false;
	$1.type = BOOL_TYPE;
	delete($3);
	$$ = $1;
	}
    | expr SHIFTLEFT_TOKEN expr
	{if($1.type != NUMBER_TYPE || $3.type != NUMBER_TYPE)
	{
		$1.type = NUMBER_TYPE;
		$1.num = 0;
	}
	else
	{
		$1.num = $1.num << $3.num;
	}
	delete($3);
	$$ = $1;
	}
    | expr SHIFTRIGHT_TOKEN expr
	{if($1.type != NUMBER_TYPE || $3.type != NUMBER_TYPE)
	{
		$1.type = NUMBER_TYPE;
		$1.num = 0;
	}
	else
	{
		$1.num = $1.num >> $3.num;
	}
	delete($3);
	$$ = $1;
	}
    | expr '+' expr
	{
	if($1.type != $3.type || $1.type == BOOL_TYPE)
	{
	delete($3);
	$$ = $1;
	}
	else
	{
	if($1.type == NUMBER_TYPE)
	{
	$1.num = $1.num + $3.num;
	delete($3);
	}
	else
	{
	$1.str.append($3.str);
	delete($3);
	}
	$$ = $1;
	}
	}
    | expr '-' expr
	{
	if($1.type != $3.type || $1.type == BOOL_TYPE || $1.type == STRING_TYPE || $1.type == SCOPED_TYPE)
	{
	delete($3);
	$$ = $1;
	}
	else
	{
	$1.num = $1.num - $3.num;
	delete($3);
	$$ = $1;
	}
	}
    | expr '*' expr
	{
	if($1.type != NUMBER_TYPE || $3.type != NUMBER_TYPE)
	{
		$1.type = NUMBER_TYPE;
		$1.num = 0;
	}
	else
	{
		$1.num = $1.num * $3.num;
	}
	delete($3);
	$$ = $1;
	}
    | expr '/' expr
	{
	if($1.type != NUMBER_TYPE || $3.type != NUMBER_TYPE)
	{
		$1.type = NUMBER_TYPE;
		$1.num = 0;
	}
	else
	{
		$1.num = $1.num / $3.num;
	}
	delete($3);
	$$ = $1;
	}
    | expr '%' expr
	{
	if($1.type != NUMBER_TYPE || $3.type != NUMBER_TYPE)
	{
		$1.type = NUMBER_TYPE;
		$1.num = 0;
	}
	else
	{
		$1.num = $1.num % $3.num;
	}
	delete($3);
	$$ = $1;
	}
    | '-' expr  %prec NEG
	{
	if($2.type != NUMERIC_TYPE)
	{
	$2.type = NUMERIC_TYPE;
	$2.num = 0;
	}
	else
		$2.num--;
	$$ = $2;
	}
    | '+' expr  %prec POS
	{
	if($2.type != NUMERIC_TYPE)
	{
	$2.type = NUMERIC_TYPE;
	$2.num = 0;
	}
	else
		$2.num++;
	$$ = $2;
	}
    | '~' expr  %prec NOT
	{
	if($2.type == STRING_TYPE)
	{
	$2.boolean = false;
	}
	else if ($2.type == BOOL_TYPE)
	{
	$2.boolean = !($2.boolean);
	}
	else
	{
	$2.boolean = !($2.num);
	}
	$2.type = BOOL_TYPE;
	$$ = $2;
	}
    ;
  
    
    
literal	: 
    INTEGER_LITERAL
	{$$ = new TypeLiteral();
	$$.type = NUMBER_TYPE;
	$$.num = $1;}
    | FLOAT_LITERAL
	{$$ = new TypeLiteral();
	$$.type = NUMBER_TYPE;
	$$.num = $1;}
	| STRING_LITERAL
	{$$ = new TypeLiteral();
	$$.type = STRING_TYPE;
	$$.num = $1;}
    | CHARACTER_LITERAL
	{$$ = new TypeLiteral();
	$$.type = STRING_TYPE;
	$$.num = $1;}
	| BOOLEAN_LITERAL
	{$$ = new TypeLiteral();
	$$.type = BOOL_TYPE;
	$$.boolean = $1;}
    ;



    
    
/*
REMOVED SECTION 2

*/


/*
REMOVED SECTION 3

*/


const_dcl : CONST_TOKEN ';'
	{std::cout << "Warning: \"const\" token not allowed" << std::endl;
	$$ = new PrimitiveTypeCode(TypeCode::KIND_NULL);
	}
    ;
    
except_dcl : EXCEPTION_TOKEN ';'
	{std::cout << "Warning: \"exception\" token not allowed" << std::endl;
	$$ = new PrimitiveTypeCode(TypeCode::KIND_NULL);
	}
    ;
    



%%

// directly include the nonterm defs here
@NONTERMTYPES@

/* Override yyerror */
public
void
yyverror(String s) throws ParseException
{
    String msg = yyerror_verbose(s);
    yyerror(msg);
}
