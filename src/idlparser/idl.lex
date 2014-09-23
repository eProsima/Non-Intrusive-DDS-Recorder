%{
// import YYtokentypes;
import YYtokentypes;
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

<INITIAL>{

"::"		{ yyreturn(RESOLVE_TOKEN); }
"<<"		{ yyreturn(SHIFTLEFT_TOKEN); }
">>"		{ yyreturn(SHIFTRIGHT_TOKEN); }
";"		{ yyreturn(';');} 
"{" 		{ yyreturn(LBRACE); }
"}" 		{ yyreturn(RBRACE); }
":" 		{ yyreturn(':'); }
"," 		{ yyreturn(','); }
"=" 		{ yyreturn('='); }
"+" 		{ yyreturn('+'); }
"-" 		{ yyreturn('-'); }
"(" 		{ yyreturn('('); }
")" 		{ yyreturn(')'); }
"<" 		{ yyreturn('<'); }
">" 		{ yyreturn('>'); }
"[" 		{ yyreturn('['); }
"]" 		{ yyreturn(']'); }
\" 		{ yyreturn('\"'); }
\\ 		{ yyreturn('\\'); }
"|" 		{ yyreturn('|'); }
"^" 		{ yyreturn('^'); }
"&" 		{ yyreturn('&'); }
"*" 		{ yyreturn('*'); }
"/"	 	{ yyreturn('/'); }
"%" 		{ yyreturn('%'); }
"~" 		{ yyreturn('~'); }

any		{ yyreturn(ANY_TOKEN); }
attribute	{ yyreturn(ATTRIBUTE_TOKEN); }
boolean		{ yyreturn(BOOLEAN_TOKEN); }
case		{ yyreturn(CASE_TOKEN); }
char		{ yyreturn(CHAR_TOKEN); }
const		{ yyreturn(CONST_TOKEN); }
context		{ yyreturn(CONTEXT_TOKEN); }
default		{ yyreturn(DEFAULT_TOKEN); }
double		{ yyreturn(DOUBLE_TOKEN); }
enum		{ yyreturn(ENUM_TOKEN); }
exception	{ yyreturn(EXCEPTION_TOKEN); }
float		{ yyreturn(FLOAT_TOKEN); }
in		{ yyreturn(IN_TOKEN); }
inout		{ yyreturn(INOUT_TOKEN); }
interface	{ yyreturn(INTERFACE_TOKEN); }
long		{ yyreturn(LONG_TOKEN); }
module		{ yyreturn(MODULE_TOKEN); }
octet		{ yyreturn(OCTET_TOKEN); }
oneway		{ yyreturn(ONEWAY_TOKEN); }
out		{ yyreturn(OUT_TOKEN); }
raises		{ yyreturn(RAISES_TOKEN); }
readonly	{ yyreturn(READONLY_TOKEN); }
sequence	{ yyreturn(SEQUENCE_TOKEN); }
short		{ yyreturn(SHORT_TOKEN); }
string		{ yyreturn(STRING_TOKEN); }
struct		{ yyreturn(STRUCT_TOKEN); }
switch		{ yyreturn(SWITCH_TOKEN); }
typedef		{ yyreturn(TYPEDEF_TOKEN); }
unsigned	{ yyreturn(UNSIGNED_TOKEN); }
union		{ yyreturn(UNION_TOKEN); }
void		{ yyreturn(VOID_TOKEN); }
Object		{ yyreturn(OBJECT_TOKEN); }
TRUE		{ yyreturn(BOOLEAN_LITERAL); }
FALSE		{ yyreturn(BOOLEAN_LITERAL); }


{IDCHAR}({IDCHAR}|{DIGIT})* { /* identifier */
		yyreturn(IDENTIFIER);
		}

0[0-7]+		{/* octal */
		yyreturn(INTEGER_LITERAL); 
		}

{DIGIT}+	{ /* decimal */
		yyreturn(INTEGER_LITERAL);
		}

0[xX][0-9a-fA-F]+	{ /* hex */
		yyreturn(INTEGER_LITERAL);
		}

{DIGIT}+\.{DIGIT}*([eE][\+\-]?{DIGIT}+)? { /* float 0.e0 */
		yyreturn(FLOAT_LITERAL);
		}

\.{DIGIT}+([eE][\+\-]?{DIGIT}+)? { /* float .0e0 */
		yyreturn(FLOAT_LITERAL);
		}

{DIGIT}+[eE][\+\-]?{DIGIT}+	{ /* float 0e-0 */
		yyreturn(FLOAT_LITERAL);   
		}

'{SQUOTE_TEXT}'	{ /* quoted char */
		yyreturn(CHARACTER_LITERAL);
		}

\"{STRING_TEXT}\"	{ /* string */
		yyreturn(STRING_LITERAL);
		}
\"{STRING_TEXT} { yylexerror("unclosed string");}

{WHITESPACE}+	{ /*  eliminate white space  */ }

^#pragma.*\n	{ yyreturn(PRAGMA_INFO);}
^#ident.*\n	{ yyreturn(IDENT_INFO);}
^#" "{DIGIT}+" ""\""[^\"]*"\""" "{DIGIT}+\n	{ 
		yyreturn(LINE_AND_FILE_INFO);
		}
#" "{DIGIT}+" ""\""[^\"]*"\""\n	{
		yyreturn(LINE_AND_FILE_INFO);
		}
^#" "{DIGIT}+\n	{
		yyreturn(LINE_AND_FILE_INFO);
		}

"//"[^\n]*	{ /*   uni-line comment */ }
"/*"		{ yybegin(COMMENT); comment_depth++;  }

. { yylexerror("Illegal character: " + ((int)yytext.currentchar()));}

}

<COMMENT>{
"/*"	{ /* begin nested multiline comment */ comment_depth++; }
"*/"	{ /* end multiline comment */
		comment_depth--;
		if (comment_depth == 0) { yybegin(INITIAL); }
		}

[^*/]+ {}
\*[^/] {}
\/[^*] {}
				
. { yylexerror("Illegal character in comment: " + ((int)yytext.currentchar())); }
}

%%

// Include the set of tokentypes to 
// avoid having to say e.g. Tokentypes.INTEGER_LITERAL

// TOKENTYPES

@TOKENTYPES@

protected static final char LBRACE = '{';
protected static final char RBRACE = '}';
protected int comment_depth = 0;
