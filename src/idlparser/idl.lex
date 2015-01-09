%{
// import YYtokentypes;
//import YYtokentypes;

#include "IDLScanner.h"

 typedef eprosima::IDLParser::token token;
typedef eprosima::IDLParser::token_type token_type;

#define yyterminate() return token::END

/* This disables inclusion of unistd.h, which is not available under Visual C++
 * on Win32. The C++ scanner uses STL streams instead. */
#define YY_NO_UNISTD_H


//const static char LBRACE = '{';
//const static char RBRACE = '}';
 int comment_depth = 0;

%}

 /* enable c++ scanner class generation */
%option c++

/* change the name of the scanner class. results in "ExampleFlexLexer" */
/*%option prefix="Example"  */


/* the manual says "somewhat more optimized" */
%option batch
 
 /* enable scanner to generate debug output. disable this for release
  * versions. */
%option debug
 
 /* no support for include files is planned */
%option yywrap nounput 
 
 /* enables the use of start condition stacks */
%option stack
 
/* The following paragraph suffices to track locations accurately. Each time
 * yylex is invoked, the begin position is moved onto the end position. */
%{
#define YY_USER_ACTION  yylloc->columns(yyleng);
%}



%x COMMENT

IDCHAR [A-Za-z_$]
DIGIT [0-9]
HEXDIGIT [0-9a-fA-F]
OCTDIGIT [0-7]
NONL_WHITESPACE [\ \t\b\f\r]
WHITESPACE [\n\ \t\b\r\f]
UNICODE (\\u{HEXDIGIT}|\\u{HEXDIGIT}{HEXDIGIT}|\\u{HEXDIGIT}{HEXDIGIT}{HEXDIGIT}|\\u{HEXDIGIT}{HEXDIGIT}{HEXDIGIT}{HEXDIGIT})
OCTCODE (\\{OCTDIGIT}|\\{OCTDIGIT}{OCTDIGIT}|\\{OCTDIGIT}{OCTDIGIT}{OCTDIGIT})
STRING_TEXT ({UNICODE}|{OCTCODE}|\\\"|[^\n\"]|\\{WHITESPACE}+\\)*
SQUOTE_TEXT ({UNICODE}|{OCTCODE}|[^']|\\.)

%%
%{
// reset location
 yylloc->step();
%}

<INITIAL>{

"::"		{ return(token::RESOLVE_TOKEN); }
"<<"		{ return(token::SHIFTLEFT_TOKEN); }
">>"		{ return(token::SHIFTRIGHT_TOKEN); }
";"			{ return static_cast<token_type>(*yytext);} 
"{" 		{ return static_cast<token_type>(*yytext);/*return(LBRACE);*/ }
"}" 		{ return static_cast<token_type>(*yytext);/*return(RBRACE);*/ }
":" 		{ return static_cast<token_type>(*yytext);/*return(':');*/ }
"," 		{ return static_cast<token_type>(*yytext);/*return(',');*/ }
"=" 		{ return static_cast<token_type>(*yytext);/*return('='); */}
"+" 		{ return static_cast<token_type>(*yytext);/*return('+');*/ }
"-" 		{ return static_cast<token_type>(*yytext);/*return('-');*/ }
"(" 		{ return static_cast<token_type>(*yytext);/*return('(');*/ }
")" 		{ return static_cast<token_type>(*yytext);/*return(')');*/ }
"<" 		{ return static_cast<token_type>(*yytext);/*return('<');*/ }
">" 		{ return static_cast<token_type>(*yytext);/*return('>'); */}
"[" 		{ return static_cast<token_type>(*yytext);/*return('['); */}
"]" 		{ return static_cast<token_type>(*yytext);/*return(']'); */}
\" 			{ return static_cast<token_type>(*yytext);/*return('\"'); */}
\\ 			{ return static_cast<token_type>(*yytext);/*return('\\'); */}
"|" 		{ return static_cast<token_type>(*yytext);/*return('|'); */}
"^" 		{ return static_cast<token_type>(*yytext);/*return('^'); */}
"&" 		{ return static_cast<token_type>(*yytext);/*return('&');*/ }
"*" 		{ return static_cast<token_type>(*yytext);/*return('*'); */}
"/"	 		{ return static_cast<token_type>(*yytext);/*return('/'); */}
"%" 		{ return static_cast<token_type>(*yytext);/*return('%'); */}

any			{ return(token::ANY_TOKEN); }
attribute	{ return(token::ATTRIBUTE_TOKEN); }
boolean		{ return(token::BOOLEAN_TOKEN); }
case		{ return(token::CASE_TOKEN); }
char		{ return(token::CHAR_TOKEN); }
const		{ return(token::CONST_TOKEN); }
context		{ return(token::CONTEXT_TOKEN); }
default		{ return(token::DEFAULT_TOKEN); }
double		{ return(token::DOUBLE_TOKEN); }
enum		{ return(token::ENUM_TOKEN); }
exception	{ return(token::EXCEPTION_TOKEN); }
float		{ return(token::FLOAT_TOKEN); }
in			{ return(token::IN_TOKEN); }
inout		{ return(token::INOUT_TOKEN); }
interface	{ return(token::INTERFACE_TOKEN); }
long		{ return(token::LONG_TOKEN); }
module		{ return(token::MODULE_TOKEN); }
octet		{ return(token::OCTET_TOKEN); }
oneway		{ return(token::ONEWAY_TOKEN); }
out			{ return(token::OUT_TOKEN); }
raises		{ return(token::RAISES_TOKEN); }
readonly	{ return(token::READONLY_TOKEN); }
sequence	{ return(token::SEQUENCE_TOKEN); }
short		{ return(token::SHORT_TOKEN); }
string		{ return(token::STRING_TOKEN); }
struct		{ return(token::STRUCT_TOKEN); }
switch		{ return(token::SWITCH_TOKEN); }
typedef		{ return(token::TYPEDEF_TOKEN); }
unsigned	{ return(token::UNSIGNED_TOKEN); }
union		{ return(token::UNION_TOKEN); }
void		{ return(token::VOID_TOKEN); }
Object		{ return(token::OBJECT_TOKEN); }


TRUE		{yyval->integerVal = 1;
			 return(token::BOOLEAN_LITERAL); }
FALSE		{ yyval->integerVal = 0;
			return(token::BOOLEAN_LITERAL); }


{IDCHAR}({IDCHAR}|{DIGIT})* { /* identifier */
		yyval->stringVal = new std::string(yytext,yyleng);
		return(token::IDENTIFIER);
		}

0[0-7]+		{/* octal */
		yyval->integerVal = atoi(yytext);
		return(token::INTEGER_LITERAL); 
		}

{DIGIT}+	{ /* decimal */
		yyval->integerVal = atoi(yytext);
		return(token::INTEGER_LITERAL);
		}

0[xX][0-9a-fA-F]+	{ /* hex */
		yyval->integerVal = strtol (yytext,NULL,0);
		return(token::INTEGER_LITERAL);
		}

{DIGIT}+\.{DIGIT}*([eE][\+\-]?{DIGIT}+)? { /* float 0.e0 */
	yyval->doubleVal = atof(yytext);
		return(token::FLOAT_LITERAL);
		}

\.{DIGIT}+([eE][\+\-]?{DIGIT}+)? { /* float .0e0 */
yyval->doubleVal = atof(yytext);
		return(token::FLOAT_LITERAL);
		}

{DIGIT}+[eE][\+\-]?{DIGIT}+	{ /* float 0e-0 */
yyval->doubleVal = atof(yytext);
		return(token::FLOAT_LITERAL);   
		}

'{SQUOTE_TEXT}'	{ /* quoted char */
		yyval->stringVal = new std::string(yytext,yyleng);
		return(token::CHARACTER_LITERAL);
		}

\"{STRING_TEXT}\"	{ /* string */
		yyval->stringVal = new std::string(yytext,yyleng);
		return(token::STRING_LITERAL);
		}
\"{STRING_TEXT} { std::cerr << "Error" << std::endl;/*yyerror("unclosed string");*/}

{WHITESPACE}+	{ yylloc->step();/*  eliminate white space  */ }

^#pragma.*\n	{ return(token::PRAGMA_INFO);}
^#ident.*\n		{ return(token::IDENT_INFO);}
^#" "{DIGIT}+" ""\""[^\"]*"\""" "{DIGIT}+\n	{ 
		return(token::LINE_AND_FILE_INFO);
		}
#" "{DIGIT}+" ""\""[^\"]*"\""\n	{
		return(token::LINE_AND_FILE_INFO);
		}
^#" "{DIGIT}+\n	{
		return(token::LINE_AND_FILE_INFO);
		}

"//"[^\n]*	{ /*   uni-line comment */ }
"/*"		{ BEGIN(COMMENT); comment_depth++;  }

. { std::cerr << "Error" << std::endl;/* yyerror("Illegal character: ");*/}

}

<COMMENT>{
"/*"	{ /* begin nested multiline comment */ comment_depth++; }
"*/"	{ /* end multiline comment */
		comment_depth--;
		if (comment_depth == 0) { BEGIN(INITIAL); }
		}

[^*/]+ {}
\*[^/] {}
\/[^*] {}
				
. { std::cerr << "Error" << std::endl;/*yyerror("Illegal character in comment ");*/ }
}

%%  /*** Additional Code ***/

 
 namespace eprosima {
 
 IDLScanner::IDLScanner(std::istream* in, std::ostream* out): yyFlexLexer(in, out)
 {
 }
 
 IDLScanner::~IDLScanner()
 {
 }
 
 void IDLScanner::set_debug(bool b)
 {
     yy_flex_debug = b;
 }
 
 }
 
 /* This implementation of ExampleFlexLexer::yylex() is required to fill the
  * vtable of the class ExampleFlexLexer. We define the scanner's main yylex
  * function via YY_DECL to reside in the Scanner class instead. */
 
 #ifdef yylex
 #undef yylex
 #endif
 
int yyFlexLexer::yylex()
{
     std::cerr << "in IDLFlexLexer::yylex() !" << std::endl;
     return 0;
}
 
 /* When the scanner receives an end-of-file indication from YY_INPUT, it then
  * checks the yywrap() function. If yywrap() returns false (zero), then it is
  * assumed that the function has gone ahead and set up `yyin' to point to
  * another input file, and scanning continues. If it returns true (non-zero),
  * then the scanner terminates, returning 0 to its caller. */
 
int yyFlexLexer::yywrap()
{
     return 1;
}
 
 
