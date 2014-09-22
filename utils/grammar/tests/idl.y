	/* @(#)idl.y 0.1 92/07/04 Copyright (C) 1992 MITRE */
	/******** DEFINITIONS SECTION *******/


%{
#include <vector>
#include <string>
#include <utility>
#include <iostream>
namespace yy{
typedef std::pair<std::string,std::vector<uint32_t>> Declarator;
typedef std::vector<Declarator*> DeclaratorVec;
typedef std::vector<Member*> MemberVec;
typedef std::vector<std::string> StringVec;
}
%}

/* Just to see how, explicitly show the default type, namely Integer */
%union {TypeCodeVec;
		Declarator; DeclaratorVec;
		MemberVec; Member;
		StringVec;
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
%type <TypeCode> definition
%type <TypeCode> type_dcl const_dcl except_dcl interface module sharp_declaratives
%type <TypeCode> base_type_spec simple_type_spec type_spec
%type <TypeCode> floating_pt_type integer_type signed_int signed_long_int
%type <TypeCode> signed_short_int unsigned_int unsigned_long_int unsigned_short_int
%type <TypeCode> char_type boolean_type octet_type object_type any_type
%type <TypeCode> constr_type_spec template_type_spec scoped_name
%type <TypeCode> struct_type union_type enum_type
%type <TypeCode> sequence_type string_type
%type <TypeCodeVec> specification definition_list

%type <MemberVec> struct_member_list struct_member
%type <DeclaratorVec> declarators
%type <Declarator> declarator simple_declarator complex_declarator fixed_array_size_list
%type <Declarator> array_declarator
%type <uint32_t> fixed_array_size positive_int_const
%type <StringVec> enumerator_list
%type <std::string> enumerator




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
	$$ = new TypeCodeVec();
	$$.push_back($1);
	}
    | definition definition_list
	{$2.push_back($1); $$ = $2;}
    ;
definition : 
    type_dcl ';' {$$ = $1;}
    | const_dcl ';' {$$ = $1;}
    | except_dcl ';' {$$ = $1;}
    | interface ';' {$$ = $1;}
    | module ';' {$$ = $1;}
    | sharp_declaratives {$$ = $1;}


type_dcl : 
    TYPEDEF_TOKEN type_declarator
	{std::cout << "Warning: \"typedef\" token not allowed" << std::endl;}
    | struct_type
    | union_type
    | enum_type
    ;
   
struct_type : STRUCT_TOKEN  IDENTIFIER '{'  struct_member_list  '}'
	{$$ = (TypeCode*) new StructTypeCode($2);
	for(MemberVec::iterator it= $4.begin();it!=$4.end();++it)
	{
		$$.addMember(std::dynamic_cast<StructMember*>(*it));
	}
	}
    ;
struct_member_list : 
    struct_member
	{$$ = $1;}
    | struct_member struct_member_list
	{
	for(std::vector<Member*>::iterator it = $1.begin();it!=$2.end();++it)
	{
		$2.push_back(*it);
	}
	$$ = $2;
	}
    ;
struct_member : type_spec declarators ';'
	{
	if($1->getKind() == TypeCode::KIND_NULL)
	{
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
    ;
simple_type_spec : 
    base_type_spec
    | template_type_spec
    | scoped_name
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
	$$.push_back($1);
	}
    | declarator  ','  declarators
	{$3.push_back($1); $$ = $3;}
    ;
declarator : 
    simple_declarator
    | complex_declarator
    ;
simple_declarator : IDENTIFIER
	{
	$$ = new Declarator();
	$$.first = $1;
	}
    ;
complex_declarator : array_declarator
    ;
    
array_declarator : IDENTIFIER  fixed_array_size_list
	{
	$2.first = $1;
	$$ = $2;
	}	
    ;
fixed_array_size_list : 
    fixed_array_size
	{
	$$ = new Declarator();
	$$.second.push_back($1);
	}	
    | fixed_array_size fixed_array_size_list
	{$2.push_back($1); $$ = $2;}
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
	}
    ;
enumerator_list	: enumerator
	{
	$$ = new StringVec();
	$$.push_back($1);
	}
    | enumerator ',' enumerator_list
	{$3.push_back($1); $$ = $3;}
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
	{$$ = new YYnonterminal(nt_sequence_type,$3,$5);}	
    | SEQUENCE_TOKEN  '<'  simple_type_spec  '>'
	{$$ = new YYnonterminal(nt_sequence_type,$3);}	
    ;

/*

REMOVED SECTION 1

*/






    
    
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
