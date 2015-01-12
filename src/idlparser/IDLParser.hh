/* A Bison parser, made by GNU Bison 2.5.  */

/* Skeleton interface for Bison LALR(1) parsers in C++
   
      Copyright (C) 2002-2011 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C++ LALR(1) parser skeleton written by Akim Demaille.  */

#ifndef PARSER_HEADER_H
# define PARSER_HEADER_H

/* "%code requires" blocks.  */

/* Line 35 of lalr1.cc  */
#line 5 "idl.y"


#include <vector>
#include <string>
#include <utility>
#include <iostream>

#include "cdr/all_TypeCodes.h"
using namespace eprosima;

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

extern int yylex ();
extern void yyerror ( char *);

class TypeCodeResults{
public:
	TypeCodeVec* mp_TypeCodeVec;
	Declarator* mp_Declarator;
	DeclaratorVec* mp_DeclaratorVec;
	MemberVec* mp_MemberVec;
	Member* mp_Member;
	StringVec* mp_StringVec;
	TypeLiteral* mp_TypeLiteral;
	uint32_t m_uint32_t;
	std::string m_string;
	TypeCode* mp_TypeCode;
	TypeCodeResults():mp_TypeCode(NULL){};
	~TypeCodeResults(){};
	TypeCodeResults& operator=(const TypeCodeResults& input)
	{
		*this = input;
		return *this;
	}
};






/* Line 35 of lalr1.cc  */
#line 96 "IDLParser.hh"


#include <string>
#include <iostream>
#include "stack.hh"
#include "location.hh"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


namespace eprosima {

/* Line 35 of lalr1.cc  */
#line 126 "IDLParser.hh"

  /// A Bison parser.
  class IDLParser
  {
  public:
    /// Symbol semantic values.
#ifndef YYSTYPE
    union semantic_type
    {

/* Line 35 of lalr1.cc  */
#line 83 "idl.y"
  TypeCodeVec* mp_TypeCodeVec;
	Declarator* mp_Declarator;
	DeclaratorVec* mp_DeclaratorVec;
	MemberVec* mp_MemberVec;
	Member* mp_Member;
	StringVec* mp_StringVec;
	TypeLiteral* mp_TypeLiteral;
	TypeCode* mp_TypeCode;
	std::string* mp_string;
	uint32_t m_uint32_t;
	
 	int integerVal;
 	double doubleVal;
 	int tokenVal;
 	std::string* stringVal;
 


/* Line 35 of lalr1.cc  */
#line 158 "IDLParser.hh"
    };
#else
    typedef YYSTYPE semantic_type;
#endif
    /// Symbol locations.
    typedef location location_type;
    /// Tokens.
    struct token
    {
      /* Tokens.  */
   enum yytokentype {
     END = 0,
     INTEGER_LITERAL = 258,
     LONG_LITERAL = 259,
     FLOAT_LITERAL = 260,
     DOUBLE_LITERAL = 261,
     BOOLEAN_LITERAL = 262,
     STRING_LITERAL = 263,
     CHARACTER_LITERAL = 264,
     IDENTIFIER = 265,
     BOOLEAN_TOKEN = 266,
     ANY_TOKEN = 267,
     ATTRIBUTE_TOKEN = 268,
     CASE_TOKEN = 269,
     CHAR_TOKEN = 270,
     CONST_TOKEN = 271,
     CONTEXT_TOKEN = 272,
     DEFAULT_TOKEN = 273,
     DOUBLE_TOKEN = 274,
     ENUM_TOKEN = 275,
     EXCEPTION_TOKEN = 276,
     FLOAT_TOKEN = 277,
     IN_TOKEN = 278,
     INOUT_TOKEN = 279,
     INTERFACE_TOKEN = 280,
     LONG_TOKEN = 281,
     MODULE_TOKEN = 282,
     OCTET_TOKEN = 283,
     ONEWAY_TOKEN = 284,
     OUT_TOKEN = 285,
     RAISES_TOKEN = 286,
     READONLY_TOKEN = 287,
     SEQUENCE_TOKEN = 288,
     SHORT_TOKEN = 289,
     STRING_TOKEN = 290,
     STRUCT_TOKEN = 291,
     SWITCH_TOKEN = 292,
     TYPEDEF_TOKEN = 293,
     UNSIGNED_TOKEN = 294,
     UNION_TOKEN = 295,
     VOID_TOKEN = 296,
     OBJECT_TOKEN = 297,
     RESOLVE_TOKEN = 298,
     SHIFTLEFT_TOKEN = 299,
     SHIFTRIGHT_TOKEN = 300,
     PRAGMA_INFO = 301,
     IDENT_INFO = 302,
     LINE_AND_FILE_INFO = 303,
     NOT = 304,
     POS = 305,
     NEG = 306
   };

    };
    /// Token type.
    typedef token::yytokentype token_type;

    /// Build a parser object.
    IDLParser (class UserTypeCodeProvider& TCprovider_yyarg);
    virtual ~IDLParser ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if YYDEBUG
    /// The current debugging stream.
    std::ostream& debug_stream () const;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);
#endif

  private:
    /// Report a syntax error.
    /// \param loc    where the syntax error is found.
    /// \param msg    a description of the syntax error.
    virtual void error (const location_type& loc, const std::string& msg);

    /// Generate an error message.
    /// \param state   the state where the error occurred.
    /// \param tok     the lookahead token.
    virtual std::string yysyntax_error_ (int yystate, int tok);

#if YYDEBUG
    /// \brief Report a symbol value on the debug stream.
    /// \param yytype       The token type.
    /// \param yyvaluep     Its semantic value.
    /// \param yylocationp  Its location.
    virtual void yy_symbol_value_print_ (int yytype,
					 const semantic_type* yyvaluep,
					 const location_type* yylocationp);
    /// \brief Report a symbol on the debug stream.
    /// \param yytype       The token type.
    /// \param yyvaluep     Its semantic value.
    /// \param yylocationp  Its location.
    virtual void yy_symbol_print_ (int yytype,
				   const semantic_type* yyvaluep,
				   const location_type* yylocationp);
#endif


    /// State numbers.
    typedef int state_type;
    /// State stack type.
    typedef stack<state_type>    state_stack_type;
    /// Semantic value stack type.
    typedef stack<semantic_type> semantic_stack_type;
    /// location stack type.
    typedef stack<location_type> location_stack_type;

    /// The state stack.
    state_stack_type yystate_stack_;
    /// The semantic value stack.
    semantic_stack_type yysemantic_stack_;
    /// The location stack.
    location_stack_type yylocation_stack_;

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue);

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue);

    /// Internal symbol numbers.
    typedef unsigned char token_number_type;
    /* Tables.  */
    /// For a state, the index in \a yytable_ of its portion.
    static const short int yypact_[];
    static const short int yypact_ninf_;

    /// For a state, default reduction number.
    /// Unless\a  yytable_ specifies something else to do.
    /// Zero means the default is an error.
    static const unsigned char yydefact_[];

    static const short int yypgoto_[];
    static const short int yydefgoto_[];

    /// What to do in a state.
    /// \a yytable_[yypact_[s]]: what to do in state \a s.
    /// - if positive, shift that token.
    /// - if negative, reduce the rule which number is the opposite.
    /// - if zero, do what YYDEFACT says.
    static const short int yytable_[];
    static const signed char yytable_ninf_;

    static const short int yycheck_[];

    /// For a state, its accessing symbol.
    static const unsigned char yystos_[];

    /// For a rule, its LHS.
    static const unsigned char yyr1_[];
    /// For a rule, its RHS length.
    static const unsigned char yyr2_[];

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
    /// For a symbol, its name in clear.
    static const char* const yytname_[];
#endif

    /// Convert the symbol name \a n to a form suitable for a diagnostic.
    static std::string yytnamerr_ (const char *n);

#if YYDEBUG
    /// A type to store symbol numbers and -1.
    typedef short int rhs_number_type;
    /// A `-1'-separated list of the rules' RHS.
    static const rhs_number_type yyrhs_[];
    /// For each rule, the index of the first RHS symbol in \a yyrhs_.
    static const unsigned short int yyprhs_[];
    /// For each rule, its source line number.
    static const unsigned short int yyrline_[];
    /// For each scanner token number, its symbol number.
    static const unsigned short int yytoken_number_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r);
    /// Print the state stack on the debug stream.
    virtual void yystack_print_ ();

    /* Debugging.  */
    int yydebug_;
    std::ostream* yycdebug_;
#endif

    /// Convert a scanner token number \a t to a symbol number.
    token_number_type yytranslate_ (int t);

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg        Why this token is reclaimed.
    /// \param yytype       The symbol type.
    /// \param yyvaluep     Its semantic value.
    /// \param yylocationp  Its location.
    inline void yydestruct_ (const char* yymsg,
			     int yytype,
			     semantic_type* yyvaluep,
			     location_type* yylocationp);

    /// Pop \a n symbols the three stacks.
    inline void yypop_ (unsigned int n = 1);

    /* Constants.  */
    static const int yyeof_;
    /* LAST_ -- Last index in TABLE_.  */
    static const int yylast_;
    static const int yynnts_;
    static const int yyempty_;
    static const int yyfinal_;
    static const int yyterror_;
    static const int yyerrcode_;
    static const int yyntokens_;
    static const unsigned int yyuser_token_number_max_;
    static const token_number_type yyundef_token_;

    /* User arguments.  */
    class UserTypeCodeProvider& TCprovider;
  };

} // eprosima

/* Line 35 of lalr1.cc  */
#line 399 "IDLParser.hh"



#endif /* ! defined PARSER_HEADER_H */