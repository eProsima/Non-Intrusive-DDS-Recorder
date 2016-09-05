// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// Take the name prefix into account.
#define yylex   eprosimalex

// First part of user declarations.

#line 39 "IDLParser.cc" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "IDLParser.hh"

// User implementation prologue.
#line 169 "idl.y" // lalr1.cc:412

 
 #include "UserTypeCodeProvider.h"
 #include "IDLScanner.h"
  /* this "connects" the bison parser in the UserTypeCodeProvider to the flex scanner class
  * object. it defines the yylex() function call to pull the next token from the
  * current lexer object of the UserTypeCodeProvider context. */
 #undef yylex
 #define yylex TCprovider.lexer->lex
 

#line 64 "IDLParser.cc" // lalr1.cc:412


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (/*CONSTCOND*/ false)
# endif


// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << std::endl;                  \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


namespace eprosima {
#line 150 "IDLParser.cc" // lalr1.cc:479

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  IDLParser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              // Fall through.
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
  IDLParser::IDLParser (class UserTypeCodeProvider& TCprovider_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      TCprovider (TCprovider_yyarg)
  {}

  IDLParser::~IDLParser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/

  inline
  IDLParser::syntax_error::syntax_error (const location_type& l, const std::string& m)
    : std::runtime_error (m)
    , location (l)
  {}

  // basic_symbol.
  template <typename Base>
  inline
  IDLParser::basic_symbol<Base>::basic_symbol ()
    : value ()
  {}

  template <typename Base>
  inline
  IDLParser::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value ()
    , location (other.location)
  {
    value = other.value;
  }


  template <typename Base>
  inline
  IDLParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  inline
  IDLParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  inline
  IDLParser::basic_symbol<Base>::~basic_symbol ()
  {
    clear ();
  }

  template <typename Base>
  inline
  void
  IDLParser::basic_symbol<Base>::clear ()
  {
    Base::clear ();
  }

  template <typename Base>
  inline
  bool
  IDLParser::basic_symbol<Base>::empty () const
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  inline
  void
  IDLParser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move(s);
    value = s.value;
    location = s.location;
  }

  // by_type.
  inline
  IDLParser::by_type::by_type ()
    : type (empty_symbol)
  {}

  inline
  IDLParser::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
  IDLParser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
  IDLParser::by_type::clear ()
  {
    type = empty_symbol;
  }

  inline
  void
  IDLParser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  inline
  int
  IDLParser::by_type::type_get () const
  {
    return type;
  }


  // by_state.
  inline
  IDLParser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  IDLParser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  IDLParser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  IDLParser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  IDLParser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  IDLParser::symbol_number_type
  IDLParser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  IDLParser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  IDLParser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
    value = that.value;
    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  IDLParser::stack_symbol_type&
  IDLParser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
    return *this;
  }


  template <typename Base>
  inline
  void
  IDLParser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    YYUSE (yysym.type_get ());
  }

#if YYDEBUG
  template <typename Base>
  void
  IDLParser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  inline
  void
  IDLParser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  IDLParser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  IDLParser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  IDLParser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  IDLParser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  IDLParser::debug_level_type
  IDLParser::debug_level () const
  {
    return yydebug_;
  }

  void
  IDLParser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline IDLParser::state_type
  IDLParser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  IDLParser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  IDLParser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  IDLParser::parse ()
  {
    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    // User initialization code.
    #line 63 "idl.y" // lalr1.cc:741
{
// initialize the initial location object
     yyla.location.begin.filename = yyla.location.end.filename = &TCprovider.streamname;
}

#line 529 "IDLParser.cc" // lalr1.cc:741

    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            yyla.type = yytranslate_ (yylex (&yyla.value, &yyla.location));
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* If YYLEN is nonzero, implement the default value of the
         action: '$$ = $1'.  Otherwise, use the top of the stack.

         Otherwise, the following line sets YYLHS.VALUE to garbage.
         This behavior is undocumented and Bison users should not rely
         upon it.  */
      if (yylen)
        yylhs.value = yystack_[yylen - 1].value;
      else
        yylhs.value = yystack_[0].value;

      // Compute the default @$.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 2:
#line 189 "idl.y" // lalr1.cc:859
    {
    delete((yystack_[0].value.mp_TypeCodeVec));
    }
#line 641 "IDLParser.cc" // lalr1.cc:859
    break;

  case 3:
#line 195 "idl.y" // lalr1.cc:859
    {
	(yylhs.value.mp_TypeCodeVec) = (yystack_[0].value.mp_TypeCodeVec);
	}
#line 649 "IDLParser.cc" // lalr1.cc:859
    break;

  case 4:
#line 199 "idl.y" // lalr1.cc:859
    {
	for(TypeCodeVec::iterator it = (yystack_[0].value.mp_TypeCodeVec)->begin();it!=(yystack_[0].value.mp_TypeCodeVec)->end();++it)
	{
	(yystack_[1].value.mp_TypeCodeVec)->push_back(*it);
	}
	delete((yystack_[0].value.mp_TypeCodeVec));
	(yylhs.value.mp_TypeCodeVec) = (yystack_[1].value.mp_TypeCodeVec);
	}
#line 662 "IDLParser.cc" // lalr1.cc:859
    break;

  case 5:
#line 209 "idl.y" // lalr1.cc:859
    {(yylhs.value.mp_TypeCodeVec) = (yystack_[1].value.mp_TypeCodeVec);for(std::vector<TypeCode*>::iterator it = (yystack_[1].value.mp_TypeCodeVec)->begin();it!=(yystack_[1].value.mp_TypeCodeVec)->end();++it)
    {
    	TCprovider.addTypeCode(*it);
    	//printf("Added\n");
    }}
#line 672 "IDLParser.cc" // lalr1.cc:859
    break;

  case 6:
#line 214 "idl.y" // lalr1.cc:859
    {(yylhs.value.mp_TypeCodeVec) = (yystack_[1].value.mp_TypeCodeVec);for(std::vector<TypeCode*>::iterator it = (yystack_[1].value.mp_TypeCodeVec)->begin();it!=(yystack_[1].value.mp_TypeCodeVec)->end();++it)
    {
    	TCprovider.addTypeCode(*it);
    }}
#line 681 "IDLParser.cc" // lalr1.cc:859
    break;

  case 7:
#line 218 "idl.y" // lalr1.cc:859
    {(yylhs.value.mp_TypeCodeVec) = (yystack_[1].value.mp_TypeCodeVec);for(std::vector<TypeCode*>::iterator it = (yystack_[1].value.mp_TypeCodeVec)->begin();it!=(yystack_[1].value.mp_TypeCodeVec)->end();++it)
    {
    	TCprovider.addTypeCode(*it);
    }}
#line 690 "IDLParser.cc" // lalr1.cc:859
    break;

  case 8:
#line 223 "idl.y" // lalr1.cc:859
    {(yylhs.value.mp_TypeCodeVec) = (yystack_[1].value.mp_TypeCodeVec);
    }
#line 697 "IDLParser.cc" // lalr1.cc:859
    break;

  case 9:
#line 226 "idl.y" // lalr1.cc:859
    {
    (yylhs.value.mp_TypeCodeVec) = (yystack_[1].value.mp_TypeCodeVec);
    }
#line 705 "IDLParser.cc" // lalr1.cc:859
    break;

  case 10:
#line 230 "idl.y" // lalr1.cc:859
    {
    (yylhs.value.mp_TypeCodeVec) = (yystack_[0].value.mp_TypeCodeVec);
    for(std::vector<TypeCode*>::iterator it = (yystack_[0].value.mp_TypeCodeVec)->begin();it!=(yystack_[0].value.mp_TypeCodeVec)->end();++it)
    {
    	TCprovider.addTypeCode(*it);
    }}
#line 716 "IDLParser.cc" // lalr1.cc:859
    break;

  case 11:
#line 239 "idl.y" // lalr1.cc:859
    {(yylhs.value.mp_TypeCodeVec) = new TypeCodeVec();}
#line 722 "IDLParser.cc" // lalr1.cc:859
    break;

  case 12:
#line 241 "idl.y" // lalr1.cc:859
    {(yylhs.value.mp_TypeCodeVec) = new TypeCodeVec();}
#line 728 "IDLParser.cc" // lalr1.cc:859
    break;

  case 13:
#line 243 "idl.y" // lalr1.cc:859
    {(yylhs.value.mp_TypeCodeVec) = new TypeCodeVec();}
#line 734 "IDLParser.cc" // lalr1.cc:859
    break;

  case 14:
#line 246 "idl.y" // lalr1.cc:859
    {TCprovider.addNamespace(*(yystack_[0].value.stringVal)); }
#line 740 "IDLParser.cc" // lalr1.cc:859
    break;

  case 15:
#line 247 "idl.y" // lalr1.cc:859
    {
	(yylhs.value.mp_TypeCodeVec) = (yystack_[1].value.mp_TypeCodeVec);
	delete((yystack_[4].value.stringVal));
	TCprovider.removeNamespace();
	}
#line 750 "IDLParser.cc" // lalr1.cc:859
    break;

  case 16:
#line 255 "idl.y" // lalr1.cc:859
    {std::cout << "Warning: \"typedef\" token not allowed" << std::endl;}
#line 756 "IDLParser.cc" // lalr1.cc:859
    break;

  case 17:
#line 256 "idl.y" // lalr1.cc:859
    {
    	(yylhs.value.mp_TypeCodeVec) = (yystack_[0].value.mp_TypeCodeVec);
    }
#line 764 "IDLParser.cc" // lalr1.cc:859
    break;

  case 21:
#line 265 "idl.y" // lalr1.cc:859
    {(yylhs.value.mp_TypeCodeVec) = new TypeCodeVec();
	delete((yystack_[1].value.mp_TypeCode));
	for(DeclaratorVec::iterator it = (yystack_[0].value.mp_DeclaratorVec)->begin();it!=(yystack_[0].value.mp_DeclaratorVec)->end();++it)
		delete(*it);
	delete((yystack_[0].value.mp_DeclaratorVec));
	}
#line 775 "IDLParser.cc" // lalr1.cc:859
    break;

  case 22:
#line 274 "idl.y" // lalr1.cc:859
    {
	if((yystack_[1].value.mp_MemberVec) == NULL)
	{
		(yylhs.value.mp_TypeCodeVec) = new TypeCodeVec();
		(yylhs.value.mp_TypeCodeVec)->push_back(new PrimitiveTypeCode(TypeCode::KIND_NULL));
	}
	else
	{
	StructTypeCode* sTC = new StructTypeCode();
	sTC->setName(*(yystack_[3].value.stringVal));
	delete((yystack_[3].value.stringVal));
	for(MemberVec::iterator it= (yystack_[1].value.mp_MemberVec)->begin();it!=(yystack_[1].value.mp_MemberVec)->end();++it)
	{
		if(!sTC->addMember((StructMember*)(*it)))
		{
			std::cout << "Warning: StructMember with repeated name, second instance not added " << std::endl; //TODO MOfidicar para que devuelva error
			TCprovider.m_errorCode = UserTypeCodeProvider::REPEATED_STRUCT_MEMBER_ERROR;
			delete(*it);
		}
	}
	(yylhs.value.mp_TypeCodeVec) = new TypeCodeVec();
	(yylhs.value.mp_TypeCodeVec)->push_back((TypeCode*)sTC);
	//printf("Structure defined\n");
	}
	}
#line 805 "IDLParser.cc" // lalr1.cc:859
    break;

  case 23:
#line 302 "idl.y" // lalr1.cc:859
    {(yylhs.value.mp_MemberVec) = (yystack_[0].value.mp_MemberVec);}
#line 811 "IDLParser.cc" // lalr1.cc:859
    break;

  case 24:
#line 304 "idl.y" // lalr1.cc:859
    {
	if((yystack_[1].value.mp_MemberVec) ==NULL || (yystack_[0].value.mp_MemberVec) == NULL)
	{
		(yylhs.value.mp_MemberVec) = NULL;
	}
	else
	{
	for(std::vector<Member*>::iterator it = (yystack_[0].value.mp_MemberVec)->begin();it!=(yystack_[0].value.mp_MemberVec)->end();++it)
	{
		(yystack_[1].value.mp_MemberVec)->push_back(*it);
	}
	delete((yystack_[0].value.mp_MemberVec));
	(yylhs.value.mp_MemberVec) = (yystack_[1].value.mp_MemberVec);
	}
	}
#line 831 "IDLParser.cc" // lalr1.cc:859
    break;

  case 25:
#line 321 "idl.y" // lalr1.cc:859
    {
	if((yystack_[2].value.mp_TypeCode)->getKind() == TypeCode::KIND_NULL)
	{
		delete((yystack_[1].value.mp_DeclaratorVec));
		delete((yystack_[2].value.mp_TypeCode));
		(yylhs.value.mp_MemberVec) = NULL;
	}
	else
	{
	MemberVec* MV = new MemberVec();
	bool first = true;
	for(DeclaratorVec::iterator it=(yystack_[1].value.mp_DeclaratorVec)->begin();it!=(yystack_[1].value.mp_DeclaratorVec)->end();++it)
	{
		//std::cout << "Declarator: " << (*it)->first<< std::endl;
		TypeCode* pTC = (yystack_[2].value.mp_TypeCode);
		pTC = TCprovider.copyTypeCode(pTC, first);
		first = false;
		StructMember* sm = new StructMember((*it)->first,0,0);
		if((*it)->second.size()==0)
		{
			sm->setTypeCode(pTC);
		}
		else
		{
			ArrayTypeCode* ar = new ArrayTypeCode((*it)->second);
			ar->setContentTypeCode(pTC);
			sm->setTypeCode(ar);
		}
		MV->push_back(sm);
	}
	for(std::vector<Declarator*>::iterator it = (yystack_[1].value.mp_DeclaratorVec)->begin();it!=(yystack_[1].value.mp_DeclaratorVec)->end();++it)
		delete(*it);
	delete((yystack_[1].value.mp_DeclaratorVec));
	(yylhs.value.mp_MemberVec) = MV;
	}
	}
#line 872 "IDLParser.cc" // lalr1.cc:859
    break;

  case 27:
#line 366 "idl.y" // lalr1.cc:859
    {
    (yylhs.value.mp_TypeCode) = *((yystack_[0].value.mp_TypeCodeVec)->begin());
    delete((yystack_[0].value.mp_TypeCodeVec));
    }
#line 881 "IDLParser.cc" // lalr1.cc:859
    break;

  case 31:
#line 378 "idl.y" // lalr1.cc:859
    {
    TypeCode* pTC = TCprovider.findTypeCodebyName(*(yystack_[0].value.mp_string));
    if(pTC->getKind()==TypeCode::KIND_NULL)
    {
    	std::cout << "Warning, TypeCode with name: " << *(yystack_[0].value.mp_string) << " not found."<< std::endl;
    	TCprovider.m_errorCode = UserTypeCodeProvider::TYPECODE_NOTFOUND;
    }
    delete((yystack_[0].value.mp_string));
    (yylhs.value.mp_TypeCode) = pTC;
    }
#line 896 "IDLParser.cc" // lalr1.cc:859
    break;

  case 39:
#line 402 "idl.y" // lalr1.cc:859
    {
	std::cout << "Warning: \"Object\" token not allowed" << std::endl;
	(yylhs.value.mp_TypeCode) = new PrimitiveTypeCode(TypeCode::KIND_NULL);
	}
#line 905 "IDLParser.cc" // lalr1.cc:859
    break;

  case 40:
#line 408 "idl.y" // lalr1.cc:859
    {std::cout << "Warning: \"any\" token not allowed" << std::endl;
	(yylhs.value.mp_TypeCode) = new PrimitiveTypeCode(TypeCode::KIND_NULL);}
#line 912 "IDLParser.cc" // lalr1.cc:859
    break;

  case 46:
#line 422 "idl.y" // lalr1.cc:859
    {
	(yylhs.value.mp_DeclaratorVec) = new DeclaratorVec();
	(yylhs.value.mp_DeclaratorVec)->push_back((yystack_[0].value.mp_Declarator));
	}
#line 921 "IDLParser.cc" // lalr1.cc:859
    break;

  case 47:
#line 427 "idl.y" // lalr1.cc:859
    {
	(yystack_[0].value.mp_DeclaratorVec)->insert((yystack_[0].value.mp_DeclaratorVec)->begin(),(yystack_[2].value.mp_Declarator)); 
	(yylhs.value.mp_DeclaratorVec) = (yystack_[0].value.mp_DeclaratorVec);
	}
#line 930 "IDLParser.cc" // lalr1.cc:859
    break;

  case 50:
#line 437 "idl.y" // lalr1.cc:859
    {
	(yylhs.value.mp_Declarator) = new Declarator();
	(yylhs.value.mp_Declarator)->first = *(yystack_[0].value.stringVal);
	delete((yystack_[0].value.stringVal));
	}
#line 940 "IDLParser.cc" // lalr1.cc:859
    break;

  case 52:
#line 447 "idl.y" // lalr1.cc:859
    {
	(yystack_[0].value.mp_Declarator)->first = *(yystack_[1].value.stringVal);
	delete((yystack_[1].value.stringVal));
	(yylhs.value.mp_Declarator) = (yystack_[0].value.mp_Declarator);
	}
#line 950 "IDLParser.cc" // lalr1.cc:859
    break;

  case 53:
#line 455 "idl.y" // lalr1.cc:859
    {
	(yylhs.value.mp_Declarator) = new Declarator();
	(yylhs.value.mp_Declarator)->second.push_back((yystack_[0].value.m_uint32_t));
	}
#line 959 "IDLParser.cc" // lalr1.cc:859
    break;

  case 54:
#line 460 "idl.y" // lalr1.cc:859
    {
	(yystack_[0].value.mp_Declarator)->second.push_back((yystack_[1].value.m_uint32_t)); 
	(yylhs.value.mp_Declarator) = (yystack_[0].value.mp_Declarator);}
#line 967 "IDLParser.cc" // lalr1.cc:859
    break;

  case 55:
#line 465 "idl.y" // lalr1.cc:859
    {(yylhs.value.m_uint32_t) = (yystack_[1].value.m_uint32_t);}
#line 973 "IDLParser.cc" // lalr1.cc:859
    break;

  case 56:
#line 471 "idl.y" // lalr1.cc:859
    {(yylhs.value.mp_TypeCode) = new PrimitiveTypeCode(TypeCode::KIND_FLOAT);}
#line 979 "IDLParser.cc" // lalr1.cc:859
    break;

  case 57:
#line 473 "idl.y" // lalr1.cc:859
    {(yylhs.value.mp_TypeCode) = new PrimitiveTypeCode(TypeCode::KIND_DOUBLE);}
#line 985 "IDLParser.cc" // lalr1.cc:859
    break;

  case 58:
#line 475 "idl.y" // lalr1.cc:859
    {(yylhs.value.mp_TypeCode) = new PrimitiveTypeCode(TypeCode::KIND_LONGDOUBLE);}
#line 991 "IDLParser.cc" // lalr1.cc:859
    break;

  case 63:
#line 486 "idl.y" // lalr1.cc:859
    {(yylhs.value.mp_TypeCode) = new PrimitiveTypeCode(TypeCode::KIND_LONG);}
#line 997 "IDLParser.cc" // lalr1.cc:859
    break;

  case 64:
#line 488 "idl.y" // lalr1.cc:859
    {(yylhs.value.mp_TypeCode) = new PrimitiveTypeCode(TypeCode::KIND_LONGLONG);}
#line 1003 "IDLParser.cc" // lalr1.cc:859
    break;

  case 65:
#line 491 "idl.y" // lalr1.cc:859
    {(yylhs.value.mp_TypeCode) = new PrimitiveTypeCode(TypeCode::KIND_SHORT);}
#line 1009 "IDLParser.cc" // lalr1.cc:859
    break;

  case 68:
#line 498 "idl.y" // lalr1.cc:859
    {(yylhs.value.mp_TypeCode) = new PrimitiveTypeCode(TypeCode::KIND_ULONG);}
#line 1015 "IDLParser.cc" // lalr1.cc:859
    break;

  case 69:
#line 500 "idl.y" // lalr1.cc:859
    {(yylhs.value.mp_TypeCode) = new PrimitiveTypeCode(TypeCode::KIND_ULONGLONG);}
#line 1021 "IDLParser.cc" // lalr1.cc:859
    break;

  case 70:
#line 503 "idl.y" // lalr1.cc:859
    {(yylhs.value.mp_TypeCode) = new PrimitiveTypeCode(TypeCode::KIND_USHORT);}
#line 1027 "IDLParser.cc" // lalr1.cc:859
    break;

  case 71:
#line 506 "idl.y" // lalr1.cc:859
    {(yylhs.value.mp_TypeCode) = new PrimitiveTypeCode(TypeCode::KIND_CHAR);}
#line 1033 "IDLParser.cc" // lalr1.cc:859
    break;

  case 72:
#line 509 "idl.y" // lalr1.cc:859
    {(yylhs.value.mp_TypeCode) = new PrimitiveTypeCode(TypeCode::KIND_BOOLEAN);}
#line 1039 "IDLParser.cc" // lalr1.cc:859
    break;

  case 73:
#line 512 "idl.y" // lalr1.cc:859
    {(yylhs.value.mp_TypeCode) = new PrimitiveTypeCode(TypeCode::KIND_OCTET);}
#line 1045 "IDLParser.cc" // lalr1.cc:859
    break;

  case 74:
#line 517 "idl.y" // lalr1.cc:859
    {
	EnumTypeCode* enTC= new EnumTypeCode();
	enTC->setName(*(yystack_[3].value.stringVal));
	delete((yystack_[3].value.stringVal));
	uint32_t ord = 0;
	for(StringVec::iterator it=(yystack_[1].value.mp_StringVec)->begin();it!=(yystack_[1].value.mp_StringVec)->end();++it)
	{
		EnumMember* eMember = new EnumMember(*it,ord);
		if(!enTC->addMember(eMember))
		{
			std::cout << "Warning: EnumMember with repeated name, second instance not added " << std::endl; //TODO MOfidicar para que devuelva error
			delete(eMember);
		}
		++ord;
	}
	delete((yystack_[1].value.mp_StringVec));
	(yylhs.value.mp_TypeCodeVec) = new TypeCodeVec();
	(yylhs.value.mp_TypeCodeVec)->push_back((TypeCode*) enTC);
	}
#line 1069 "IDLParser.cc" // lalr1.cc:859
    break;

  case 75:
#line 538 "idl.y" // lalr1.cc:859
    {
	(yylhs.value.mp_StringVec) = new StringVec();
	(yylhs.value.mp_StringVec)->push_back(*(yystack_[0].value.mp_string));
	delete((yystack_[0].value.mp_string));
	}
#line 1079 "IDLParser.cc" // lalr1.cc:859
    break;

  case 76:
#line 544 "idl.y" // lalr1.cc:859
    {(yystack_[0].value.mp_StringVec)->insert((yystack_[0].value.mp_StringVec)->begin(),*(yystack_[2].value.mp_string)); (yylhs.value.mp_StringVec) = (yystack_[0].value.mp_StringVec);delete((yystack_[2].value.mp_string));}
#line 1085 "IDLParser.cc" // lalr1.cc:859
    break;

  case 77:
#line 547 "idl.y" // lalr1.cc:859
    {(yylhs.value.mp_string) = new std::string(*(yystack_[0].value.stringVal));
	delete((yystack_[0].value.stringVal));}
#line 1092 "IDLParser.cc" // lalr1.cc:859
    break;

  case 78:
#line 553 "idl.y" // lalr1.cc:859
    {
	StringTypeCode* pSTC = new StringTypeCode((yystack_[1].value.m_uint32_t));
	(yylhs.value.mp_TypeCode) = (TypeCode*)pSTC;
	}
#line 1101 "IDLParser.cc" // lalr1.cc:859
    break;

  case 79:
#line 558 "idl.y" // lalr1.cc:859
    {StringTypeCode* pSTC = new StringTypeCode(255);
	(yylhs.value.mp_TypeCode) = (TypeCode*)pSTC;}
#line 1108 "IDLParser.cc" // lalr1.cc:859
    break;

  case 80:
#line 564 "idl.y" // lalr1.cc:859
    {
	SequenceTypeCode* sTC = new SequenceTypeCode((yystack_[1].value.m_uint32_t));
	sTC->setContentTypeCode(TCprovider.copyTypeCode((yystack_[3].value.mp_TypeCode),false));
	(yylhs.value.mp_TypeCode) = (TypeCode*) sTC;
	}
#line 1118 "IDLParser.cc" // lalr1.cc:859
    break;

  case 81:
#line 570 "idl.y" // lalr1.cc:859
    {
	SequenceTypeCode* sTC = new SequenceTypeCode(255);
	sTC->setContentTypeCode((yystack_[1].value.mp_TypeCode));
	(yylhs.value.mp_TypeCode) = (TypeCode*) sTC;
	}
#line 1128 "IDLParser.cc" // lalr1.cc:859
    break;

  case 84:
#line 583 "idl.y" // lalr1.cc:859
    {
	std::vector<int> index_to_remove;
	for(TypeCodeVec::iterator it = (yystack_[1].value.mp_TypeCodeVec)->begin();it!=(yystack_[1].value.mp_TypeCodeVec)->end();++it)
	{
	if((*it)->getKind() == TypeCode::KIND_STRUCT || 
		(*it)->getKind() == TypeCode::KIND_UNION ||
		(*it)->getKind() == TypeCode::KIND_ENUM)
	{

	}
	else
	{
		index_to_remove.push_back(std::distance((yystack_[1].value.mp_TypeCodeVec)->begin(),it));
		delete(*it);
	}
	for(std::vector<int>::reverse_iterator it = index_to_remove.rbegin();it!=index_to_remove.rend();++it)
	{
		(yystack_[1].value.mp_TypeCodeVec)->erase((yystack_[1].value.mp_TypeCodeVec)->begin()+(*it));
	}
	}
	(yylhs.value.mp_TypeCodeVec) = (yystack_[1].value.mp_TypeCodeVec);
	delete((yystack_[3].value.mp_string));
	TCprovider.removeNamespace();
	}
#line 1157 "IDLParser.cc" // lalr1.cc:859
    break;

  case 85:
#line 609 "idl.y" // lalr1.cc:859
    {
	delete((yystack_[0].value.stringVal));
	(yylhs.value.mp_TypeCodeVec) = new TypeCodeVec();
	}
#line 1166 "IDLParser.cc" // lalr1.cc:859
    break;

  case 86:
#line 616 "idl.y" // lalr1.cc:859
    {
	TCprovider.addNamespace(*(yystack_[0].value.stringVal));
	(yylhs.value.mp_string) = new std::string(*(yystack_[0].value.stringVal));
	delete((yystack_[0].value.stringVal));
	}
#line 1176 "IDLParser.cc" // lalr1.cc:859
    break;

  case 87:
#line 622 "idl.y" // lalr1.cc:859
    {
		TCprovider.addNamespace(*(yystack_[1].value.stringVal));
	(yylhs.value.mp_string) = new std::string(*(yystack_[1].value.stringVal));
	delete((yystack_[1].value.stringVal));
 	}
#line 1186 "IDLParser.cc" // lalr1.cc:859
    break;

  case 88:
#line 629 "idl.y" // lalr1.cc:859
    {(yylhs.value.mp_TypeCodeVec) = new TypeCodeVec();}
#line 1192 "IDLParser.cc" // lalr1.cc:859
    break;

  case 89:
#line 631 "idl.y" // lalr1.cc:859
    {
	for(TypeCodeVec::iterator it = (yystack_[0].value.mp_TypeCodeVec)->begin();it!=(yystack_[0].value.mp_TypeCodeVec)->end();++it)
		(yystack_[1].value.mp_TypeCodeVec)->push_back(*it);
	(yylhs.value.mp_TypeCodeVec) = (yystack_[1].value.mp_TypeCodeVec);
	delete((yystack_[0].value.mp_TypeCodeVec));
	}
#line 1203 "IDLParser.cc" // lalr1.cc:859
    break;

  case 90:
#line 640 "idl.y" // lalr1.cc:859
    {(yylhs.value.mp_TypeCodeVec) = (yystack_[1].value.mp_TypeCodeVec);for(std::vector<TypeCode*>::iterator it = (yystack_[1].value.mp_TypeCodeVec)->begin();it!=(yystack_[1].value.mp_TypeCodeVec)->end();++it)
    {
    	TCprovider.addTypeCode(*it);
    	//printf("Added\n");
    }}
#line 1213 "IDLParser.cc" // lalr1.cc:859
    break;

  case 91:
#line 646 "idl.y" // lalr1.cc:859
    {(yylhs.value.mp_TypeCodeVec) = (yystack_[1].value.mp_TypeCodeVec);for(std::vector<TypeCode*>::iterator it = (yystack_[1].value.mp_TypeCodeVec)->begin();it!=(yystack_[1].value.mp_TypeCodeVec)->end();++it)
    {
    	TCprovider.addTypeCode(*it);
    	//printf("Added\n");
    }}
#line 1223 "IDLParser.cc" // lalr1.cc:859
    break;

  case 92:
#line 652 "idl.y" // lalr1.cc:859
    {(yylhs.value.mp_TypeCodeVec) = (yystack_[1].value.mp_TypeCodeVec);for(std::vector<TypeCode*>::iterator it = (yystack_[1].value.mp_TypeCodeVec)->begin();it!=(yystack_[1].value.mp_TypeCodeVec)->end();++it)
    {
    	TCprovider.addTypeCode(*it);
    	//printf("Added\n");
    }}
#line 1233 "IDLParser.cc" // lalr1.cc:859
    break;

  case 93:
#line 658 "idl.y" // lalr1.cc:859
    {
    delete((yystack_[1].value.mp_TypeCode));
    (yylhs.value.mp_TypeCodeVec) = new TypeCodeVec();
    }
#line 1242 "IDLParser.cc" // lalr1.cc:859
    break;

  case 95:
#line 666 "idl.y" // lalr1.cc:859
    {(yylhs.value.mp_string) = new std::string("");
	delete((yystack_[0].value.mp_string));}
#line 1249 "IDLParser.cc" // lalr1.cc:859
    break;

  case 96:
#line 672 "idl.y" // lalr1.cc:859
    {
	(yylhs.value.mp_string) = new std::string(*(yystack_[0].value.mp_string));
	delete((yystack_[0].value.mp_string));}
#line 1257 "IDLParser.cc" // lalr1.cc:859
    break;

  case 97:
#line 676 "idl.y" // lalr1.cc:859
    {(yylhs.value.mp_string) = (yystack_[0].value.mp_string);
	delete((yystack_[2].value.mp_string));
	}
#line 1265 "IDLParser.cc" // lalr1.cc:859
    break;

  case 98:
#line 682 "idl.y" // lalr1.cc:859
    {
	(yylhs.value.mp_string) = new std::string(*(yystack_[0].value.stringVal));
	delete((yystack_[0].value.stringVal));
	}
#line 1274 "IDLParser.cc" // lalr1.cc:859
    break;

  case 99:
#line 687 "idl.y" // lalr1.cc:859
    {
	(yystack_[0].value.mp_string)->insert(0,"::");
	(yystack_[0].value.mp_string)->insert(0,*(yystack_[2].value.stringVal));
	delete((yystack_[2].value.stringVal));
	(yylhs.value.mp_string) = (yystack_[0].value.mp_string);
	}
#line 1285 "IDLParser.cc" // lalr1.cc:859
    break;

  case 101:
#line 697 "idl.y" // lalr1.cc:859
    {
	std::string* aux_str = new std::string("::");
	aux_str->append(*(yystack_[0].value.stringVal));
	delete((yystack_[0].value.stringVal));
	(yylhs.value.mp_string) = aux_str;
	}
#line 1296 "IDLParser.cc" // lalr1.cc:859
    break;

  case 102:
#line 704 "idl.y" // lalr1.cc:859
    {
	(yystack_[0].value.mp_string)->insert(0,*(yystack_[1].value.stringVal));
	(yystack_[0].value.mp_string)->insert(0,"::");
	delete((yystack_[1].value.stringVal));
	(yylhs.value.mp_string) = (yystack_[0].value.mp_string);
	}
#line 1307 "IDLParser.cc" // lalr1.cc:859
    break;

  case 103:
#line 714 "idl.y" // lalr1.cc:859
    {
	UnionTypeCode* uTC = new UnionTypeCode();
	uTC->setName(*(yystack_[7].value.stringVal));
	delete((yystack_[7].value.stringVal));
	TypeCode* discTC = TCprovider.copyTypeCode((yystack_[4].value.mp_TypeCode),true);
	uTC->setDiscriminatorTypeCode(discTC);
	UnionMember* uM_boolWithDefault = NULL;
	bool isTrue = false;
	for(MemberVec::iterator it = (yystack_[1].value.mp_MemberVec)->begin();it!=(yystack_[1].value.mp_MemberVec)->end();++it)
	{
		UnionMember* uM = (UnionMember*)(*it);
		std::vector<int32_t> labels = uM->getLabels();
		bool change = false;
		bool boolDefaultFound = false;
		bool defaultIndex = false;
		for(std::vector<int32_t>::iterator it = labels.begin();it!=labels.end();++it)
		{
			if((yystack_[4].value.mp_TypeCode)->getKind() == TypeCode::KIND_CHAR && (*it) == -1000)
			{
				(*it) = 254;
				change = true;
				defaultIndex = true;
			}
			if((yystack_[4].value.mp_TypeCode)->getKind() == TypeCode::KIND_ENUM && (*it) == -1000)
			{
				(*it) = 0;
				change = true;
				defaultIndex = true;
			}
			if((yystack_[4].value.mp_TypeCode)->getKind() == TypeCode::KIND_BOOLEAN && (*it) == -1000)
			{
				uM_boolWithDefault = uM;
				boolDefaultFound = true;
			}
			if((yystack_[4].value.mp_TypeCode)->getKind() == TypeCode::KIND_BOOLEAN)
			{
				isTrue = (bool)(*it);
			}
			if((*it) == -1000) //REST OF THE CASES
			{
				change = true;
				defaultIndex = true;
			}
		}
		if(change)
			uM->setLabels(labels);
		if(!boolDefaultFound)
		{
			if(!uTC->addMember(uM))
			{
			std::cout << "Warning: UnionMember with repeated name, second instance not added " << std::endl; //TODO MOfidicar para que devuelva error
			delete(uM);
			}
			else
			{
				if(defaultIndex)
				{
					uTC->setDefaultIndex(uTC->getMemberCount()-1);
				}
			}
		}
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
	if(!uTC->addMember(uM_boolWithDefault))
			{
			std::cout << "Warning: UnionMember with repeated name, second instance not added " << std::endl; //TODO MOfidicar para que devuelva error
			delete(uM_boolWithDefault);
			}
	}
	delete((yystack_[1].value.mp_MemberVec));
	(yylhs.value.mp_TypeCodeVec) = new TypeCodeVec();
	(yylhs.value.mp_TypeCodeVec)->push_back((TypeCode*) uTC);
	}
#line 1393 "IDLParser.cc" // lalr1.cc:859
    break;

  case 107:
#line 802 "idl.y" // lalr1.cc:859
    {
    (yylhs.value.mp_TypeCode) = *((yystack_[0].value.mp_TypeCodeVec)->begin());
    }
#line 1401 "IDLParser.cc" // lalr1.cc:859
    break;

  case 109:
#line 809 "idl.y" // lalr1.cc:859
    {
	(yylhs.value.mp_MemberVec) = new MemberVec();
	(yylhs.value.mp_MemberVec)->push_back((yystack_[0].value.mp_Member));
	}
#line 1410 "IDLParser.cc" // lalr1.cc:859
    break;

  case 110:
#line 814 "idl.y" // lalr1.cc:859
    {
	(yystack_[0].value.mp_MemberVec)->insert((yystack_[0].value.mp_MemberVec)->begin(),(yystack_[1].value.mp_Member));
	(yylhs.value.mp_MemberVec) = (yystack_[0].value.mp_MemberVec);
	}
#line 1419 "IDLParser.cc" // lalr1.cc:859
    break;

  case 111:
#line 820 "idl.y" // lalr1.cc:859
    {
	((UnionMember*)((yystack_[1].value.mp_Member)))->setLabels((yystack_[2].value.mp_Declarator)->second);
	(yylhs.value.mp_Member) = (yystack_[1].value.mp_Member);
	}
#line 1428 "IDLParser.cc" // lalr1.cc:859
    break;

  case 112:
#line 827 "idl.y" // lalr1.cc:859
    {(yylhs.value.mp_Declarator) = (yystack_[0].value.mp_Declarator);}
#line 1434 "IDLParser.cc" // lalr1.cc:859
    break;

  case 113:
#line 829 "idl.y" // lalr1.cc:859
    {
	(yystack_[1].value.mp_Declarator)->second.push_back(*((yystack_[0].value.mp_Declarator)->second.begin()));
	(yylhs.value.mp_Declarator) = (yystack_[1].value.mp_Declarator);
	delete((yystack_[0].value.mp_Declarator));}
#line 1443 "IDLParser.cc" // lalr1.cc:859
    break;

  case 114:
#line 836 "idl.y" // lalr1.cc:859
    {
	Declarator * dCL = new Declarator();
	if((yystack_[1].value.mp_TypeLiteral)->type == NUMBER_TYPE)
	{
		dCL->second.push_back((yystack_[1].value.mp_TypeLiteral)->num);
	}
	else if((yystack_[1].value.mp_TypeLiteral)->type == BOOL_TYPE)
	{
		if((yystack_[1].value.mp_TypeLiteral)->boolean == true)
			dCL->second.push_back(1);
		else	
			dCL->second.push_back(0);
	}
	else if((yystack_[1].value.mp_TypeLiteral)->type == STRING_TYPE)
	{
	int32_t sum = 0;
	for(size_t i = 0;i<(yystack_[1].value.mp_TypeLiteral)->str.size();++i)
		sum+=(yystack_[1].value.mp_TypeLiteral)->str[i];
	dCL->second.push_back(sum);
	}
	else if((yystack_[1].value.mp_TypeLiteral)->type == SCOPED_TYPE)
	{
	dCL->second.push_back(TCprovider.findENUMvalue((yystack_[1].value.mp_TypeLiteral)->str));
	}
	(yylhs.value.mp_Declarator) = dCL;
	}
#line 1474 "IDLParser.cc" // lalr1.cc:859
    break;

  case 115:
#line 863 "idl.y" // lalr1.cc:859
    {
	Declarator * dCL = new Declarator();
	dCL->second.push_back(-1000);
	(yylhs.value.mp_Declarator) = dCL;
	}
#line 1484 "IDLParser.cc" // lalr1.cc:859
    break;

  case 116:
#line 870 "idl.y" // lalr1.cc:859
    {
	UnionMember* uM = new UnionMember();
	uM->setName((yystack_[0].value.mp_Declarator)->first);
	delete((yystack_[0].value.mp_Declarator));
	uM->setTypeCode((yystack_[1].value.mp_TypeCode));
	(yylhs.value.mp_Member) = (Member*) uM;
	}
#line 1496 "IDLParser.cc" // lalr1.cc:859
    break;

  case 117:
#line 881 "idl.y" // lalr1.cc:859
    {std::cout << "Warning: \"attribute\" token not allowed" << std::endl;
	(yylhs.value.mp_TypeCode) = new PrimitiveTypeCode(TypeCode::KIND_NULL);}
#line 1503 "IDLParser.cc" // lalr1.cc:859
    break;

  case 118:
#line 884 "idl.y" // lalr1.cc:859
    {std::cout << "Warning: \"readonly attribute\" token not allowed" << std::endl;
	(yylhs.value.mp_TypeCode) = new PrimitiveTypeCode(TypeCode::KIND_NULL);}
#line 1510 "IDLParser.cc" // lalr1.cc:859
    break;

  case 119:
#line 889 "idl.y" // lalr1.cc:859
    {
    (yylhs.value.mp_TypeCode) = NULL;
    }
#line 1518 "IDLParser.cc" // lalr1.cc:859
    break;

  case 120:
#line 893 "idl.y" // lalr1.cc:859
    {(yylhs.value.mp_TypeCode) = NULL;}
#line 1524 "IDLParser.cc" // lalr1.cc:859
    break;

  case 121:
#line 898 "idl.y" // lalr1.cc:859
    {(yylhs.value.mp_TypeCodeVec) = new TypeCodeVec();
	delete((yystack_[1].value.stringVal));}
#line 1531 "IDLParser.cc" // lalr1.cc:859
    break;

  case 122:
#line 901 "idl.y" // lalr1.cc:859
    {(yylhs.value.mp_TypeCodeVec) = new TypeCodeVec();
	delete((yystack_[1].value.stringVal));}
#line 1538 "IDLParser.cc" // lalr1.cc:859
    break;

  case 123:
#line 905 "idl.y" // lalr1.cc:859
    {(yylhs.value.m_uint32_t) = 0;}
#line 1544 "IDLParser.cc" // lalr1.cc:859
    break;

  case 124:
#line 908 "idl.y" // lalr1.cc:859
    {(yylhs.value.m_uint32_t) = 0;}
#line 1550 "IDLParser.cc" // lalr1.cc:859
    break;

  case 126:
#line 913 "idl.y" // lalr1.cc:859
    {(yylhs.value.m_uint32_t) = 0;}
#line 1556 "IDLParser.cc" // lalr1.cc:859
    break;

  case 127:
#line 917 "idl.y" // lalr1.cc:859
    {(yylhs.value.m_uint32_t) = 0;}
#line 1562 "IDLParser.cc" // lalr1.cc:859
    break;

  case 128:
#line 919 "idl.y" // lalr1.cc:859
    {(yylhs.value.m_uint32_t) = 0;}
#line 1568 "IDLParser.cc" // lalr1.cc:859
    break;

  case 129:
#line 923 "idl.y" // lalr1.cc:859
    {(yylhs.value.m_uint32_t) = 0;}
#line 1574 "IDLParser.cc" // lalr1.cc:859
    break;

  case 130:
#line 925 "idl.y" // lalr1.cc:859
    {(yylhs.value.m_uint32_t) = 0;}
#line 1580 "IDLParser.cc" // lalr1.cc:859
    break;

  case 131:
#line 928 "idl.y" // lalr1.cc:859
    {(yylhs.value.m_uint32_t) = 0;}
#line 1586 "IDLParser.cc" // lalr1.cc:859
    break;

  case 132:
#line 932 "idl.y" // lalr1.cc:859
    {(yylhs.value.m_uint32_t) = 0;}
#line 1592 "IDLParser.cc" // lalr1.cc:859
    break;

  case 133:
#line 934 "idl.y" // lalr1.cc:859
    {(yylhs.value.m_uint32_t) = 0;}
#line 1598 "IDLParser.cc" // lalr1.cc:859
    break;

  case 134:
#line 936 "idl.y" // lalr1.cc:859
    {(yylhs.value.m_uint32_t) = 0;}
#line 1604 "IDLParser.cc" // lalr1.cc:859
    break;

  case 135:
#line 940 "idl.y" // lalr1.cc:859
    {(yylhs.value.m_uint32_t) = 0;}
#line 1610 "IDLParser.cc" // lalr1.cc:859
    break;

  case 136:
#line 942 "idl.y" // lalr1.cc:859
    {(yylhs.value.m_uint32_t) = 0;}
#line 1616 "IDLParser.cc" // lalr1.cc:859
    break;

  case 137:
#line 946 "idl.y" // lalr1.cc:859
    {(yylhs.value.m_uint32_t) = 0;}
#line 1622 "IDLParser.cc" // lalr1.cc:859
    break;

  case 138:
#line 948 "idl.y" // lalr1.cc:859
    {(yylhs.value.m_uint32_t) = 0;}
#line 1628 "IDLParser.cc" // lalr1.cc:859
    break;

  case 139:
#line 952 "idl.y" // lalr1.cc:859
    {(yylhs.value.m_uint32_t) = 0;
	delete((yystack_[0].value.stringVal));}
#line 1635 "IDLParser.cc" // lalr1.cc:859
    break;

  case 140:
#line 955 "idl.y" // lalr1.cc:859
    {(yylhs.value.m_uint32_t) = 0;
	delete((yystack_[2].value.stringVal));}
#line 1642 "IDLParser.cc" // lalr1.cc:859
    break;

  case 141:
#line 960 "idl.y" // lalr1.cc:859
    {
    delete((yystack_[0].value.mp_TypeCode));
    (yylhs.value.m_uint32_t) = 0;
    }
#line 1651 "IDLParser.cc" // lalr1.cc:859
    break;

  case 142:
#line 965 "idl.y" // lalr1.cc:859
    {
    delete((yystack_[0].value.mp_TypeCode));
    (yylhs.value.m_uint32_t) = 0;
    }
#line 1660 "IDLParser.cc" // lalr1.cc:859
    break;

  case 143:
#line 970 "idl.y" // lalr1.cc:859
    {
    delete((yystack_[0].value.mp_TypeCode));
    (yylhs.value.m_uint32_t) = 0;
    }
#line 1669 "IDLParser.cc" // lalr1.cc:859
    break;

  case 144:
#line 984 "idl.y" // lalr1.cc:859
    {
	if((yystack_[0].value.mp_TypeLiteral)->type == NUMBER_TYPE)
		(yylhs.value.m_uint32_t) = (uint32_t)(yystack_[0].value.mp_TypeLiteral)->num;
	else
		(yylhs.value.m_uint32_t) = 0;
	delete((yystack_[0].value.mp_TypeLiteral));
	}
#line 1681 "IDLParser.cc" // lalr1.cc:859
    break;

  case 145:
#line 995 "idl.y" // lalr1.cc:859
    {(yylhs.value.mp_TypeLiteral) = new TypeLiteral();
	(yylhs.value.mp_TypeLiteral)->type = SCOPED_TYPE;
	(yylhs.value.mp_TypeLiteral)->str = *(yystack_[0].value.mp_string);
	delete((yystack_[0].value.mp_string));
	}
#line 1691 "IDLParser.cc" // lalr1.cc:859
    break;

  case 146:
#line 1001 "idl.y" // lalr1.cc:859
    {(yylhs.value.mp_TypeLiteral) = (yystack_[0].value.mp_TypeLiteral);}
#line 1697 "IDLParser.cc" // lalr1.cc:859
    break;

  case 147:
#line 1003 "idl.y" // lalr1.cc:859
    {(yylhs.value.mp_TypeLiteral) = (yystack_[1].value.mp_TypeLiteral);}
#line 1703 "IDLParser.cc" // lalr1.cc:859
    break;

  case 148:
#line 1005 "idl.y" // lalr1.cc:859
    {
	if((yystack_[2].value.mp_TypeLiteral)->type == (yystack_[0].value.mp_TypeLiteral)->type && (yystack_[2].value.mp_TypeLiteral)->type == BOOL_TYPE)
		(yystack_[2].value.mp_TypeLiteral)->boolean = (yystack_[2].value.mp_TypeLiteral)->boolean | (yystack_[0].value.mp_TypeLiteral)->boolean;
	else if((yystack_[2].value.mp_TypeLiteral)->type == (yystack_[0].value.mp_TypeLiteral)->type && (yystack_[2].value.mp_TypeLiteral)->type == NUMBER_TYPE)
		(yystack_[2].value.mp_TypeLiteral)->boolean = (yystack_[2].value.mp_TypeLiteral)->boolean | (yystack_[0].value.mp_TypeLiteral)->boolean;
	else
		(yystack_[2].value.mp_TypeLiteral)->boolean = false;
	(yystack_[2].value.mp_TypeLiteral)->type = BOOL_TYPE;
	delete((yystack_[0].value.mp_TypeLiteral));
	(yylhs.value.mp_TypeLiteral) = (yystack_[2].value.mp_TypeLiteral);
	}
#line 1719 "IDLParser.cc" // lalr1.cc:859
    break;

  case 149:
#line 1017 "idl.y" // lalr1.cc:859
    {if((yystack_[2].value.mp_TypeLiteral)->type != NUMBER_TYPE || (yystack_[0].value.mp_TypeLiteral)->type != NUMBER_TYPE)
	{
		(yystack_[2].value.mp_TypeLiteral)->type = NUMBER_TYPE;
		(yystack_[2].value.mp_TypeLiteral)->num = 0;
	}
	else
	{
		(yystack_[2].value.mp_TypeLiteral)->num = pow((yystack_[2].value.mp_TypeLiteral)->num,(yystack_[0].value.mp_TypeLiteral)->num);
	}
	delete((yystack_[0].value.mp_TypeLiteral));
	(yylhs.value.mp_TypeLiteral) = (yystack_[2].value.mp_TypeLiteral);
	}
#line 1736 "IDLParser.cc" // lalr1.cc:859
    break;

  case 150:
#line 1030 "idl.y" // lalr1.cc:859
    {
	if((yystack_[2].value.mp_TypeLiteral)->type == (yystack_[0].value.mp_TypeLiteral)->type && (yystack_[2].value.mp_TypeLiteral)->type == BOOL_TYPE)
		(yystack_[2].value.mp_TypeLiteral)->boolean = (yystack_[2].value.mp_TypeLiteral)->boolean & (yystack_[0].value.mp_TypeLiteral)->boolean;
	else if((yystack_[2].value.mp_TypeLiteral)->type == (yystack_[0].value.mp_TypeLiteral)->type && (yystack_[2].value.mp_TypeLiteral)->type == NUMBER_TYPE)
		(yystack_[2].value.mp_TypeLiteral)->boolean = (yystack_[2].value.mp_TypeLiteral)->boolean & (yystack_[0].value.mp_TypeLiteral)->boolean;
	else
		(yystack_[2].value.mp_TypeLiteral)->boolean = false;
	(yystack_[2].value.mp_TypeLiteral)->type = BOOL_TYPE;
	delete((yystack_[0].value.mp_TypeLiteral));
	(yylhs.value.mp_TypeLiteral) = (yystack_[2].value.mp_TypeLiteral);
	}
#line 1752 "IDLParser.cc" // lalr1.cc:859
    break;

  case 151:
#line 1042 "idl.y" // lalr1.cc:859
    {if((yystack_[2].value.mp_TypeLiteral)->type != NUMBER_TYPE || (yystack_[0].value.mp_TypeLiteral)->type != NUMBER_TYPE)
	{
		(yystack_[2].value.mp_TypeLiteral)->type = NUMBER_TYPE;
		(yystack_[2].value.mp_TypeLiteral)->num = 0;
	}
	else
	{
		(yystack_[2].value.mp_TypeLiteral)->num = (int)(yystack_[2].value.mp_TypeLiteral)->num << (int)(yystack_[0].value.mp_TypeLiteral)->num;
	}
	delete((yystack_[0].value.mp_TypeLiteral));
	(yylhs.value.mp_TypeLiteral) = (yystack_[2].value.mp_TypeLiteral);
	}
#line 1769 "IDLParser.cc" // lalr1.cc:859
    break;

  case 152:
#line 1055 "idl.y" // lalr1.cc:859
    {if((yystack_[2].value.mp_TypeLiteral)->type != NUMBER_TYPE || (yystack_[0].value.mp_TypeLiteral)->type != NUMBER_TYPE)
	{
		(yystack_[2].value.mp_TypeLiteral)->type = NUMBER_TYPE;
		(yystack_[2].value.mp_TypeLiteral)->num = 0;
	}
	else
	{
		(yystack_[2].value.mp_TypeLiteral)->num = (int)(yystack_[2].value.mp_TypeLiteral)->num >> (int)(yystack_[0].value.mp_TypeLiteral)->num;
	}
	delete((yystack_[0].value.mp_TypeLiteral));
	(yylhs.value.mp_TypeLiteral) = (yystack_[2].value.mp_TypeLiteral);
	}
#line 1786 "IDLParser.cc" // lalr1.cc:859
    break;

  case 153:
#line 1068 "idl.y" // lalr1.cc:859
    {
	if((yystack_[2].value.mp_TypeLiteral)->type != (yystack_[0].value.mp_TypeLiteral)->type || (yystack_[2].value.mp_TypeLiteral)->type == BOOL_TYPE)
	{
	delete((yystack_[0].value.mp_TypeLiteral));
	(yylhs.value.mp_TypeLiteral) = (yystack_[2].value.mp_TypeLiteral);
	}
	else
	{
	if((yystack_[2].value.mp_TypeLiteral)->type == NUMBER_TYPE)
	{
	(yystack_[2].value.mp_TypeLiteral)->num = (yystack_[2].value.mp_TypeLiteral)->num + (yystack_[0].value.mp_TypeLiteral)->num;
	delete((yystack_[0].value.mp_TypeLiteral));
	}
	else
	{
	(yystack_[2].value.mp_TypeLiteral)->str.append((yystack_[0].value.mp_TypeLiteral)->str);
	delete((yystack_[0].value.mp_TypeLiteral));
	}
	(yylhs.value.mp_TypeLiteral) = (yystack_[2].value.mp_TypeLiteral);
	}
	}
#line 1812 "IDLParser.cc" // lalr1.cc:859
    break;

  case 154:
#line 1090 "idl.y" // lalr1.cc:859
    {
	if((yystack_[2].value.mp_TypeLiteral)->type != (yystack_[0].value.mp_TypeLiteral)->type || (yystack_[2].value.mp_TypeLiteral)->type == BOOL_TYPE || (yystack_[2].value.mp_TypeLiteral)->type == STRING_TYPE || (yystack_[2].value.mp_TypeLiteral)->type == SCOPED_TYPE)
	{
	delete((yystack_[0].value.mp_TypeLiteral));
	(yylhs.value.mp_TypeLiteral) = (yystack_[2].value.mp_TypeLiteral);
	}
	else
	{
	(yystack_[2].value.mp_TypeLiteral)->num = (yystack_[2].value.mp_TypeLiteral)->num - (yystack_[0].value.mp_TypeLiteral)->num;
	delete((yystack_[0].value.mp_TypeLiteral));
	(yylhs.value.mp_TypeLiteral) = (yystack_[2].value.mp_TypeLiteral);
	}
	}
#line 1830 "IDLParser.cc" // lalr1.cc:859
    break;

  case 155:
#line 1104 "idl.y" // lalr1.cc:859
    {
	if((yystack_[2].value.mp_TypeLiteral)->type != NUMBER_TYPE || (yystack_[0].value.mp_TypeLiteral)->type != NUMBER_TYPE)
	{
		(yystack_[2].value.mp_TypeLiteral)->type = NUMBER_TYPE;
		(yystack_[2].value.mp_TypeLiteral)->num = 0;
	}
	else
	{
		(yystack_[2].value.mp_TypeLiteral)->num = (yystack_[2].value.mp_TypeLiteral)->num * (yystack_[0].value.mp_TypeLiteral)->num;
	}
	delete((yystack_[0].value.mp_TypeLiteral));
	(yylhs.value.mp_TypeLiteral) = (yystack_[2].value.mp_TypeLiteral);
	}
#line 1848 "IDLParser.cc" // lalr1.cc:859
    break;

  case 156:
#line 1118 "idl.y" // lalr1.cc:859
    {
	if((yystack_[2].value.mp_TypeLiteral)->type != NUMBER_TYPE || (yystack_[0].value.mp_TypeLiteral)->type != NUMBER_TYPE)
	{
		(yystack_[2].value.mp_TypeLiteral)->type = NUMBER_TYPE;
		(yystack_[2].value.mp_TypeLiteral)->num = 0;
	}
	else
	{
		(yystack_[2].value.mp_TypeLiteral)->num = (yystack_[2].value.mp_TypeLiteral)->num / (yystack_[0].value.mp_TypeLiteral)->num;
	}
	delete((yystack_[0].value.mp_TypeLiteral));
	(yylhs.value.mp_TypeLiteral) = (yystack_[2].value.mp_TypeLiteral);
	}
#line 1866 "IDLParser.cc" // lalr1.cc:859
    break;

  case 157:
#line 1132 "idl.y" // lalr1.cc:859
    {
	if((yystack_[2].value.mp_TypeLiteral)->type != NUMBER_TYPE || (yystack_[0].value.mp_TypeLiteral)->type != NUMBER_TYPE)
	{
		(yystack_[2].value.mp_TypeLiteral)->type = NUMBER_TYPE;
		(yystack_[2].value.mp_TypeLiteral)->num = 0;
	}
	else
	{
		(yystack_[2].value.mp_TypeLiteral)->num = (int)(yystack_[2].value.mp_TypeLiteral)->num % (int)(yystack_[0].value.mp_TypeLiteral)->num;
	}
	delete((yystack_[0].value.mp_TypeLiteral));
	(yylhs.value.mp_TypeLiteral) = (yystack_[2].value.mp_TypeLiteral);
	}
#line 1884 "IDLParser.cc" // lalr1.cc:859
    break;

  case 158:
#line 1146 "idl.y" // lalr1.cc:859
    {
	if((yystack_[0].value.mp_TypeLiteral)->type != NUMBER_TYPE)
	{
	(yystack_[0].value.mp_TypeLiteral)->type = NUMBER_TYPE;
	(yystack_[0].value.mp_TypeLiteral)->num = 0;
	}
	else
		(yystack_[0].value.mp_TypeLiteral)->num--;
	(yylhs.value.mp_TypeLiteral) = (yystack_[0].value.mp_TypeLiteral);
	}
#line 1899 "IDLParser.cc" // lalr1.cc:859
    break;

  case 159:
#line 1157 "idl.y" // lalr1.cc:859
    {
	if((yystack_[0].value.mp_TypeLiteral)->type != NUMBER_TYPE)
	{
	(yystack_[0].value.mp_TypeLiteral)->type = NUMBER_TYPE;
	(yystack_[0].value.mp_TypeLiteral)->num = 0;
	}
	else
		(yystack_[0].value.mp_TypeLiteral)->num++;
	(yylhs.value.mp_TypeLiteral) = (yystack_[0].value.mp_TypeLiteral);
	}
#line 1914 "IDLParser.cc" // lalr1.cc:859
    break;

  case 160:
#line 1168 "idl.y" // lalr1.cc:859
    {
	if((yystack_[0].value.mp_TypeLiteral)->type == STRING_TYPE)
	{
	(yystack_[0].value.mp_TypeLiteral)->boolean = false;
	}
	else if ((yystack_[0].value.mp_TypeLiteral)->type == BOOL_TYPE)
	{
	(yystack_[0].value.mp_TypeLiteral)->boolean = !((yystack_[0].value.mp_TypeLiteral)->boolean);
	}
	else
	{
	(yystack_[0].value.mp_TypeLiteral)->boolean = !((yystack_[0].value.mp_TypeLiteral)->num);
	}
	(yystack_[0].value.mp_TypeLiteral)->type = BOOL_TYPE;
	(yylhs.value.mp_TypeLiteral) = (yystack_[0].value.mp_TypeLiteral);
	}
#line 1935 "IDLParser.cc" // lalr1.cc:859
    break;

  case 161:
#line 1190 "idl.y" // lalr1.cc:859
    {(yylhs.value.mp_TypeLiteral) = new TypeLiteral();
	(yylhs.value.mp_TypeLiteral)->type = NUMBER_TYPE;
	(yylhs.value.mp_TypeLiteral)->num = (yystack_[0].value.integerVal);
	}
#line 1944 "IDLParser.cc" // lalr1.cc:859
    break;

  case 162:
#line 1195 "idl.y" // lalr1.cc:859
    {(yylhs.value.mp_TypeLiteral) = new TypeLiteral();
	(yylhs.value.mp_TypeLiteral)->type = NUMBER_TYPE;
	(yylhs.value.mp_TypeLiteral)->num = (yystack_[0].value.doubleVal);
	}
#line 1953 "IDLParser.cc" // lalr1.cc:859
    break;

  case 163:
#line 1200 "idl.y" // lalr1.cc:859
    {(yylhs.value.mp_TypeLiteral) = new TypeLiteral();
	(yylhs.value.mp_TypeLiteral)->type = STRING_TYPE;
	(yylhs.value.mp_TypeLiteral)->str = *(yystack_[0].value.stringVal);
	delete((yystack_[0].value.stringVal));
	}
#line 1963 "IDLParser.cc" // lalr1.cc:859
    break;

  case 164:
#line 1206 "idl.y" // lalr1.cc:859
    {(yylhs.value.mp_TypeLiteral) = new TypeLiteral();
	(yylhs.value.mp_TypeLiteral)->type = STRING_TYPE;
	(yylhs.value.mp_TypeLiteral)->str = *(yystack_[0].value.stringVal);
	delete((yystack_[0].value.stringVal));
	}
#line 1973 "IDLParser.cc" // lalr1.cc:859
    break;

  case 165:
#line 1212 "idl.y" // lalr1.cc:859
    {(yylhs.value.mp_TypeLiteral) = new TypeLiteral();
	(yylhs.value.mp_TypeLiteral)->type = BOOL_TYPE;
	(yylhs.value.mp_TypeLiteral)->boolean = (yystack_[0].value.integerVal);
	}
#line 1982 "IDLParser.cc" // lalr1.cc:859
    break;

  case 166:
#line 1235 "idl.y" // lalr1.cc:859
    {std::cout << "Warning: \"const\" token not allowed" << std::endl;
	 PrimitiveTypeCode* auxptrTC = new PrimitiveTypeCode(TypeCode::KIND_NULL);
	 (yylhs.value.mp_TypeCodeVec) = new TypeCodeVec();
	 (yylhs.value.mp_TypeCodeVec)->push_back(auxptrTC);
	}
#line 1992 "IDLParser.cc" // lalr1.cc:859
    break;

  case 167:
#line 1243 "idl.y" // lalr1.cc:859
    {std::cout << "Warning: \"exception\" token not allowed" << std::endl;
	PrimitiveTypeCode* auxptrTC = new PrimitiveTypeCode(TypeCode::KIND_NULL);
	 (yylhs.value.mp_TypeCodeVec) = new TypeCodeVec();
	 (yylhs.value.mp_TypeCodeVec)->push_back(auxptrTC);
	}
#line 2002 "IDLParser.cc" // lalr1.cc:859
    break;


#line 2006 "IDLParser.cc" // lalr1.cc:859
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
    }
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    yyerror_range[1].location = yystack_[yylen - 1].location;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  IDLParser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  IDLParser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
    */
    if (!yyla.empty ())
      {
        int yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const short int IDLParser::yypact_ninf_ = -162;

  const signed char IDLParser::yytable_ninf_ = -87;

  const short int
  IDLParser::yypact_[] =
  {
      99,     2,    15,    54,    40,    46,    58,  -162,    92,  -162,
    -162,  -162,   106,  -162,    99,  -162,    67,    68,  -162,  -162,
      70,  -162,  -162,   -25,  -162,    71,    79,  -162,    84,  -162,
     -10,  -162,    86,   211,   105,  -162,  -162,  -162,  -162,  -162,
     162,  -162,  -162,   126,    -2,  -162,    97,   211,   104,  -162,
    -162,  -162,  -162,  -162,    32,  -162,    94,  -162,   107,    12,
    -162,   152,  -162,  -162,   154,  -162,  -162,  -162,  -162,  -162,
    -162,  -162,  -162,  -162,  -162,  -162,  -162,  -162,  -162,  -162,
    -162,  -162,  -162,  -162,  -162,  -162,  -162,  -162,  -162,   111,
     305,  -162,   155,  -162,   121,  -162,  -162,  -162,   128,   162,
     133,   134,   245,   175,  -162,   141,   143,  -162,   144,   145,
    -162,   149,    99,   158,   211,   154,    -2,  -162,  -162,   279,
     100,   167,  -162,   165,   151,  -162,   160,  -162,  -162,  -162,
     112,   201,   305,  -162,  -162,  -162,  -162,  -162,   202,   159,
    -162,  -162,  -162,   126,    -2,   166,  -162,  -162,   174,  -162,
      10,  -162,  -162,  -162,  -162,  -162,   100,   100,   100,   100,
    -162,   171,   312,  -162,  -162,  -162,   100,  -162,   151,   154,
     203,  -162,  -162,  -162,  -162,  -162,   177,  -162,   184,  -162,
     201,   159,     4,  -162,   204,  -162,  -162,  -162,  -162,   100,
    -162,  -162,  -162,   290,  -162,  -162,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   179,  -162,  -162,   189,
     201,  -162,  -162,  -162,  -162,  -162,  -162,   185,   191,   305,
     188,   226,   192,  -162,   213,   213,    65,    65,   317,   339,
       0,  -162,  -162,  -162,  -162,    22,  -162,  -162,    31,   201,
      -2,   194,  -162,  -162,   100,   209,   214,    22,   211,    22,
    -162,  -162,   197,   251,    96,  -162,  -162,  -162,   154,   215,
    -162,  -162,   218,   208,  -162,  -162,  -162,   251,  -162,  -162
  };

  const unsigned char
  IDLParser::yydefact_[] =
  {
       0,     0,     0,     0,     0,     0,     0,    16,     0,    11,
      12,    13,     0,     2,     3,    10,     0,     0,    18,    20,
       0,    82,    83,     0,    19,     0,     0,   166,     0,   167,
      85,    14,     0,     0,     0,     1,     4,     9,     5,     8,
      88,     6,     7,     0,     0,    87,     0,     0,    98,    72,
      40,    71,    57,    56,    63,    73,     0,    65,    79,     0,
      39,     0,    17,    43,     0,    26,    30,    28,    38,    37,
      29,    27,    32,    33,    59,    61,    62,    60,    66,    67,
      34,    35,    36,    45,    42,    41,    31,   100,    44,     0,
       0,   124,     0,   126,     0,   143,   141,   142,     0,    88,
       0,     0,     0,     0,   125,     0,     0,    77,     0,    75,
      95,    96,     0,     0,    23,     0,     0,    58,    64,     0,
       0,    68,    70,   101,    50,    21,    46,    48,    49,    51,
       0,     0,     0,    90,    84,    89,    93,    94,     0,     0,
      91,    92,    74,     0,     0,     0,    22,    24,     0,    99,
       0,   161,   162,   165,   163,   164,     0,     0,     0,     0,
     145,     0,   144,   146,    69,   102,     0,    52,    53,     0,
      63,   108,   104,   105,   106,   107,     0,    50,   119,   117,
       0,     0,     0,   121,   135,    76,    97,    15,    25,     0,
      81,   159,   158,     0,   160,    78,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    54,    47,     0,
       0,   118,   122,   132,   134,   133,   128,     0,   129,     0,
       0,   137,     0,   147,   151,   152,   153,   154,   148,   149,
     150,   155,   156,   157,    55,     0,   120,   127,     0,     0,
       0,     0,   123,    80,     0,     0,     0,   109,     0,   112,
     130,   131,     0,     0,     0,   115,   103,   110,     0,     0,
     113,   136,   139,     0,   114,   116,   111,     0,   138,   140
  };

  const short int
  IDLParser::yypgoto_[] =
  {
    -162,  -162,    -8,  -162,  -162,  -162,  -162,   -19,  -162,  -162,
     -23,   156,  -162,   -31,   150,   -32,   -30,  -162,  -162,  -162,
    -162,   -73,    14,  -118,  -162,  -162,   113,  -162,  -162,   153,
    -162,  -162,  -162,  -162,  -162,  -162,   163,   169,  -162,   -29,
     131,  -162,   -24,  -162,  -162,  -162,  -162,  -162,   176,  -162,
    -162,  -128,   -33,   172,   -21,  -162,    35,  -162,    36,  -162,
    -162,  -162,  -161,  -162,   115,  -162,   190,  -162,    59,  -162,
    -162,  -162,  -162,    33,   -85,  -146,  -126,  -162,   -11,    -5
  };

  const short int
  IDLParser::yydefgoto_[] =
  {
      -1,    12,    13,    14,    15,    16,    46,    17,    33,    62,
      18,   113,   114,   115,    65,    95,    96,    68,    69,    70,
      71,   125,   126,   127,   128,   129,   167,   168,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    19,
     108,   109,    97,    85,    20,    21,    22,    23,    98,    99,
      45,   110,   160,    87,    24,   176,   246,   247,   248,   249,
     259,   100,   179,   101,   183,   102,   103,   184,   217,   218,
     219,   221,   242,   263,   104,   161,   162,   163,    25,    26
  };

  const short int
  IDLParser::yytable_[] =
  {
      86,    66,    64,    67,    83,   131,    36,    86,    48,    84,
      63,   111,    88,   178,    86,    66,   186,    67,    83,   211,
     206,    94,    40,    84,    63,    28,    88,   213,   214,   105,
     191,   192,   193,   194,   215,   106,   244,   -86,   121,    44,
     245,    61,   148,   222,   196,   197,   122,   180,    27,   236,
      30,   117,   198,   199,   213,   214,    31,    86,   118,   216,
     189,   215,   178,   203,   204,   205,    86,   190,    32,    86,
     224,   225,   226,   227,   228,   229,   230,   231,   232,   233,
      94,    86,    66,   149,    67,    83,    86,    66,   105,    67,
      84,    63,   178,    88,   106,    84,   208,    86,   171,    86,
      29,   175,    34,   151,   145,   152,    35,   153,   154,   155,
      48,   111,   252,    37,    38,     1,    39,    41,   254,     2,
       3,   251,    48,    49,     4,    42,     5,    51,   203,   204,
     205,    43,     2,    47,   239,     6,   107,     7,   170,     8,
     196,   197,    89,    61,   112,   264,    57,   116,   198,   199,
     119,    59,   156,   157,   158,    61,   200,   201,   202,   203,
     204,   205,   123,   120,   124,   130,   159,   133,   132,     9,
      10,    11,    48,    49,    50,    90,   134,    51,     1,   136,
     137,    52,     2,     3,    53,   139,    86,   140,    54,   141,
      55,    91,   142,   164,    92,   143,    57,    58,     6,   144,
       7,    59,     8,    93,    60,    61,   146,   111,    61,   166,
     169,   177,   181,   182,   187,    86,    66,   258,    67,    83,
     188,    48,    49,    50,    84,    63,    51,    88,   195,   118,
      52,     2,   209,    53,   210,   220,   235,    54,   234,    55,
     237,   238,   240,   241,    56,    57,    58,     6,   253,   243,
      59,     8,   261,    60,    61,    48,    49,    50,   255,   262,
      51,   266,   256,   268,    52,   198,   199,    53,   267,   150,
     147,    54,   265,    55,   185,   135,   203,   204,   205,    57,
      58,   207,   257,   172,    59,   260,    93,    60,    61,    48,
      49,    50,   138,   173,    51,   165,   212,   250,    52,   174,
     269,    53,     0,     0,     0,    54,     0,    55,     0,     0,
       0,     0,    56,    57,    58,    48,    49,    50,    59,     0,
      51,    60,    61,     0,    52,     0,     0,    53,     0,     0,
       0,    54,     0,    55,   196,   197,     0,     0,     0,    57,
      58,     0,   198,   199,    59,   223,     0,    60,    61,     0,
     200,   201,   202,   203,   204,   205,   196,   197,     0,     0,
       0,   196,   197,     0,   198,   199,     0,     0,     0,   198,
     199,     0,   200,   201,   202,   203,   204,   205,   201,   202,
     203,   204,   205,   196,   197,     0,     0,     0,     0,     0,
       0,   198,   199,     0,     0,     0,     0,     0,     0,     0,
       0,   202,   203,   204,   205
  };

  const short int
  IDLParser::yycheck_[] =
  {
      33,    33,    33,    33,    33,    90,    14,    40,    10,    33,
      33,    44,    33,   131,    47,    47,   144,    47,    47,   180,
     166,    40,    47,    47,    47,    10,    47,    23,    24,    40,
     156,   157,   158,   159,    30,    40,    14,    47,    26,    49,
      18,    43,   115,   189,    44,    45,    34,   132,    46,   210,
      10,    19,    52,    53,    23,    24,    10,    90,    26,    55,
      50,    30,   180,    63,    64,    65,    99,    57,    10,   102,
     196,   197,   198,   199,   200,   201,   202,   203,   204,   205,
      99,   114,   114,   116,   114,   114,   119,   119,    99,   119,
     114,   114,   210,   114,    99,   119,   169,   130,   130,   132,
      46,   130,    10,     3,   112,     5,     0,     7,     8,     9,
      10,   144,   240,    46,    46,    16,    46,    46,   244,    20,
      21,   239,    10,    11,    25,    46,    27,    15,    63,    64,
      65,    47,    20,    47,   219,    36,    10,    38,    26,    40,
      44,    45,    37,    43,    47,    49,    34,    43,    52,    53,
      56,    39,    52,    53,    54,    43,    60,    61,    62,    63,
      64,    65,    10,    56,    10,    54,    66,    46,    13,    70,
      71,    72,    10,    11,    12,    13,    48,    15,    16,    46,
      46,    19,    20,    21,    22,    10,   219,    46,    26,    46,
      28,    29,    48,    26,    32,    50,    34,    35,    36,    50,
      38,    39,    40,    41,    42,    43,    48,   240,    43,    58,
      50,    10,    10,    54,    48,   248,   248,   248,   248,   248,
      46,    10,    11,    12,   248,   248,    15,   248,    57,    26,
      19,    20,    55,    22,    50,    31,    47,    26,    59,    28,
      55,    50,    54,    17,    33,    34,    35,    36,    54,    57,
      39,    40,    55,    42,    43,    10,    11,    12,    49,     8,
      15,    46,    48,    55,    19,    52,    53,    22,    50,   119,
     114,    26,   258,    28,   143,    99,    63,    64,    65,    34,
      35,   168,   247,   130,    39,   249,    41,    42,    43,    10,
      11,    12,   102,   130,    15,   123,   181,   238,    19,   130,
     267,    22,    -1,    -1,    -1,    26,    -1,    28,    -1,    -1,
      -1,    -1,    33,    34,    35,    10,    11,    12,    39,    -1,
      15,    42,    43,    -1,    19,    -1,    -1,    22,    -1,    -1,
      -1,    26,    -1,    28,    44,    45,    -1,    -1,    -1,    34,
      35,    -1,    52,    53,    39,    55,    -1,    42,    43,    -1,
      60,    61,    62,    63,    64,    65,    44,    45,    -1,    -1,
      -1,    44,    45,    -1,    52,    53,    -1,    -1,    -1,    52,
      53,    -1,    60,    61,    62,    63,    64,    65,    61,    62,
      63,    64,    65,    44,    45,    -1,    -1,    -1,    -1,    -1,
      -1,    52,    53,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    62,    63,    64,    65
  };

  const unsigned char
  IDLParser::yystos_[] =
  {
       0,    16,    20,    21,    25,    27,    36,    38,    40,    70,
      71,    72,    77,    78,    79,    80,    81,    83,    86,   115,
     120,   121,   122,   123,   130,   154,   155,    46,    10,    46,
      10,    10,    10,    84,    10,     0,    78,    46,    46,    46,
      47,    46,    46,    47,    49,   126,    82,    47,    10,    11,
      12,    15,    19,    22,    26,    28,    33,    34,    35,    39,
      42,    43,    85,    86,    89,    90,    91,    92,    93,    94,
      95,    96,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   118,   119,   128,   129,   130,    37,
      13,    29,    32,    41,    83,    91,    92,   118,   124,   125,
     137,   139,   141,   142,   150,   154,   155,    10,   116,   117,
     127,   128,    47,    87,    88,    89,    43,    19,    26,    56,
      56,    26,    34,    10,    10,    97,    98,    99,   100,   101,
      54,   150,    13,    46,    48,   124,    46,    46,   142,    10,
      46,    46,    48,    50,    50,    78,    48,    87,    97,   128,
      90,     3,     5,     7,     8,     9,    52,    53,    54,    66,
     128,   151,   152,   153,    26,   129,    58,   102,   103,    50,
      26,    91,   105,   112,   113,   115,   131,    10,    99,   138,
     150,    10,    54,   140,   143,   116,   127,    48,    46,    50,
      57,   152,   152,   152,   152,    57,    44,    45,    52,    53,
      60,    61,    62,    63,    64,    65,   151,   102,    97,    55,
      50,   138,   140,    23,    24,    30,    55,   144,   145,   146,
      31,   147,   151,    55,   152,   152,   152,   152,   152,   152,
     152,   152,   152,   152,    59,    47,   138,    55,    50,   150,
      54,    17,   148,    57,    14,    18,   132,   133,   134,   135,
     144,    99,   127,    54,   152,    49,    48,   132,    89,   136,
     134,    55,     8,   149,    49,    98,    46,    50,    55,   149
  };

  const unsigned char
  IDLParser::yyr1_[] =
  {
       0,    76,    77,    78,    78,    79,    79,    79,    79,    79,
      79,    80,    80,    80,    82,    81,    84,    83,    83,    83,
      83,    85,    86,    87,    87,    88,    89,    89,    90,    90,
      90,    91,    92,    92,    92,    92,    92,    92,    92,    93,
      94,    95,    95,    96,    96,    96,    97,    97,    98,    98,
      99,   100,   101,   102,   102,   103,   104,   104,   104,   105,
     105,   106,   106,   107,   107,   108,   109,   109,   110,   110,
     111,   112,   113,   114,   115,   116,   116,   117,   118,   118,
     119,   119,   120,   120,   121,   122,   123,   123,   124,   124,
     125,   125,   125,   125,   125,   126,   127,   127,   128,   128,
     128,   129,   129,   130,   131,   131,   131,   131,   131,   132,
     132,   133,   134,   134,   135,   135,   136,   137,   137,   138,
     138,   139,   139,   140,   141,   142,   142,   143,   143,   144,
     144,   145,   146,   146,   146,   147,   147,   148,   148,   149,
     149,   150,   150,   150,   151,   152,   152,   152,   152,   152,
     152,   152,   152,   152,   152,   152,   152,   152,   152,   152,
     152,   153,   153,   153,   153,   153,   154,   155
  };

  const unsigned char
  IDLParser::yyr2_[] =
  {
       0,     2,     1,     1,     2,     2,     2,     2,     2,     2,
       1,     1,     1,     1,     0,     6,     0,     3,     1,     1,
       1,     2,     5,     1,     2,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     1,     1,
       1,     1,     2,     1,     2,     3,     1,     1,     2,     1,
       1,     1,     1,     1,     2,     1,     1,     1,     2,     3,
       2,     1,     1,     1,     5,     1,     3,     1,     4,     1,
       6,     4,     1,     1,     4,     2,     2,     3,     0,     2,
       2,     2,     2,     2,     2,     2,     1,     3,     1,     3,
       1,     2,     3,     9,     1,     1,     1,     1,     1,     1,
       2,     3,     1,     2,     3,     2,     2,     3,     4,     1,
       3,     3,     4,     3,     1,     1,     1,     3,     2,     1,
       3,     3,     1,     1,     1,     0,     4,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     2,
       2,     1,     1,     1,     1,     1,     2,     2
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const IDLParser::yytname_[] =
  {
  "END", "error", "$undefined", "INTEGER_LITERAL", "LONG_LITERAL",
  "FLOAT_LITERAL", "DOUBLE_LITERAL", "BOOLEAN_LITERAL", "STRING_LITERAL",
  "CHARACTER_LITERAL", "IDENTIFIER", "BOOLEAN_TOKEN", "ANY_TOKEN",
  "ATTRIBUTE_TOKEN", "CASE_TOKEN", "CHAR_TOKEN", "CONST_TOKEN",
  "CONTEXT_TOKEN", "DEFAULT_TOKEN", "DOUBLE_TOKEN", "ENUM_TOKEN",
  "EXCEPTION_TOKEN", "FLOAT_TOKEN", "IN_TOKEN", "INOUT_TOKEN",
  "INTERFACE_TOKEN", "LONG_TOKEN", "MODULE_TOKEN", "OCTET_TOKEN",
  "ONEWAY_TOKEN", "OUT_TOKEN", "RAISES_TOKEN", "READONLY_TOKEN",
  "SEQUENCE_TOKEN", "SHORT_TOKEN", "STRING_TOKEN", "STRUCT_TOKEN",
  "SWITCH_TOKEN", "TYPEDEF_TOKEN", "UNSIGNED_TOKEN", "UNION_TOKEN",
  "VOID_TOKEN", "OBJECT_TOKEN", "RESOLVE_TOKEN", "SHIFTLEFT_TOKEN",
  "SHIFTRIGHT_TOKEN", "';'", "'{'", "'}'", "':'", "','", "'='", "'+'",
  "'-'", "'('", "')'", "'<'", "'>'", "'['", "']'", "'|'", "'^'", "'&'",
  "'*'", "'/'", "'%'", "'~'", "'\\''", "'\"'", "'\\\\'", "PRAGMA_INFO",
  "IDENT_INFO", "LINE_AND_FILE_INFO", "NEG", "POS", "NOT", "$accept",
  "specification", "definition_list", "definition", "sharp_declaratives",
  "module", "$@1", "type_dcl", "$@2", "type_declarator", "struct_type",
  "struct_member_list", "struct_member", "type_spec", "simple_type_spec",
  "scoped_name", "base_type_spec", "object_type", "any_type",
  "template_type_spec", "constr_type_spec", "declarators", "declarator",
  "simple_declarator", "complex_declarator", "array_declarator",
  "fixed_array_size_list", "fixed_array_size", "floating_pt_type",
  "integer_type", "signed_int", "signed_long_int", "signed_short_int",
  "unsigned_int", "unsigned_long_int", "unsigned_short_int", "char_type",
  "boolean_type", "octet_type", "enum_type", "enumerator_list",
  "enumerator", "string_type", "sequence_type", "interface",
  "interface_dcl", "forward_dcl", "interface_header", "interface_body",
  "export", "inheritance_spec", "scoped_name_list", "scoped_name_str",
  "res_scoped_name", "union_type", "switch_type_spec", "switch_body",
  "case", "case_label_list", "case_label", "element_spec", "attr_dcl",
  "simple_declarators", "op_dcl", "op_dcl_cont", "op_attribute",
  "op_type_spec", "parameter_dcls", "param_dcl_list", "param_dcl",
  "param_attribute", "raises_expr", "context_expr", "string_literal_list",
  "param_type_spec", "positive_int_const", "expr", "literal", "const_dcl",
  "except_dcl", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  IDLParser::yyrline_[] =
  {
       0,   188,   188,   194,   198,   209,   214,   218,   222,   225,
     229,   238,   240,   242,   246,   246,   255,   255,   259,   260,
     261,   264,   273,   301,   303,   320,   364,   365,   372,   373,
     374,   377,   393,   394,   395,   396,   397,   398,   399,   401,
     407,   412,   413,   416,   417,   418,   421,   426,   433,   434,
     436,   443,   446,   454,   459,   464,   470,   472,   474,   478,
     479,   482,   483,   485,   487,   490,   494,   495,   497,   499,
     502,   505,   508,   511,   516,   537,   543,   546,   552,   557,
     563,   569,   578,   579,   582,   608,   615,   621,   629,   630,
     639,   645,   651,   657,   662,   665,   671,   675,   681,   686,
     693,   696,   703,   713,   798,   799,   800,   801,   805,   808,
     813,   819,   826,   828,   835,   862,   869,   880,   883,   888,
     892,   897,   900,   904,   907,   911,   912,   916,   918,   922,
     924,   927,   931,   933,   935,   940,   941,   946,   947,   951,
     954,   959,   964,   969,   983,   994,  1000,  1002,  1004,  1016,
    1029,  1041,  1054,  1067,  1089,  1103,  1117,  1131,  1145,  1156,
    1167,  1189,  1194,  1199,  1205,  1211,  1234,  1242
  };

  // Print the state stack on the debug stream.
  void
  IDLParser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  IDLParser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  // Symbol number corresponding to token number t.
  inline
  IDLParser::token_number_type
  IDLParser::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
    {
     0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    68,     2,     2,    65,    62,    67,
      54,    55,    63,    52,    50,    53,     2,    64,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    49,    46,
      56,    51,    57,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    58,    69,    59,    61,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    47,    60,    48,    66,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    70,    71,    72,    73,    74,    75
    };
    const unsigned int user_token_number_max_ = 306;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }


} // eprosima
#line 2673 "IDLParser.cc" // lalr1.cc:1167
#line 1253 "idl.y" // lalr1.cc:1168


// directly include the nonterm defs here
//@NONTERMTYPES@



void eprosima::IDLParser::error(const IDLParser::location_type& l,
                             const std::string& m)
 {
     TCprovider.error(l, m);
 }
