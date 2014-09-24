

 #ifndef IDL_SCANNER_H
 #define IDL_SCANNER_H

 // Flex expects the signature of yylex to be defined in the macro YY_DECL, and
 // the C++ parser expects it to be declared. We can factor both as follows.

 #ifndef YY_DECL

 #define YY_DECL                                         \
     eprosima::IDLParser::token_type                         \
     eprosima::IDLScanner::lex(                              \
         eprosima::IDLParser::semantic_type* yyval,         \
         eprosima::IDLParser::location_type* yylloc          \
     )
 #endif
#ifndef __FLEX_LEXER_H
// #define yyFlexLexer yyFlexLexer
 #include "FlexLexer.h"
//#undef yyFlexLexer
#endif

#include "IDLParser.hh"

namespace eprosima {

class IDLScanner : public yyFlexLexer
{
public:
	IDLScanner(std::istream* arg_yyin = 0,
			std::ostream* arg_yyout = 0);

virtual ~IDLScanner();

virtual IDLParser::token_type lex(
 IDLParser::semantic_type* yylval,
         IDLParser::location_type* yylloc
         );

     void set_debug(bool b);
 };

 } // namespace eprosima

 #endif // IDL_SCANNER_H
