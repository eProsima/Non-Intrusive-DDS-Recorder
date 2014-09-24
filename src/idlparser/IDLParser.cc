/* A Bison parser, made by GNU Bison 2.5.  */

/* Skeleton implementation for Bison LALR(1) parsers in C++
   
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

// Take the name prefix into account.
#define yylex   eprosimalex

/* First part of user declarations.  */


/* Line 293 of lalr1.cc  */
#line 41 "IDLParser.cc"


#include "IDLParser.hh"

/* User implementation prologue.  */

/* Line 299 of lalr1.cc  */
#line 168 "idl.y"

 
 #include "UserTypeCodeProvider.h"
 #include "IDLScanner.h"
  /* this "connects" the bison parser in the UserTypeCodeProvider to the flex scanner class
  * object. it defines the yylex() function call to pull the next token from the
  * current lexer object of the UserTypeCodeProvider context. */
 #undef yylex
 #define yylex TCprovider.lexer->lex
 


/* Line 299 of lalr1.cc  */
#line 63 "IDLParser.cc"

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* FIXME: INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                               \
 do                                                                    \
   if (N)                                                              \
     {                                                                 \
       (Current).begin = YYRHSLOC (Rhs, 1).begin;                      \
       (Current).end   = YYRHSLOC (Rhs, N).end;                        \
     }                                                                 \
   else                                                                \
     {                                                                 \
       (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;        \
     }                                                                 \
 while (false)
#endif

/* Suppress unused-variable warnings by "using" E.  */
#define YYUSE(e) ((void) (e))

/* Enable debugging if requested.  */
#if YYDEBUG

/* A pseudo ostream that takes yydebug_ into account.  */
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)	\
do {							\
  if (yydebug_)						\
    {							\
      *yycdebug_ << Title << ' ';			\
      yy_symbol_print_ ((Type), (Value), (Location));	\
      *yycdebug_ << std::endl;				\
    }							\
} while (false)

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug_)				\
    yy_reduce_print_ (Rule);		\
} while (false)

# define YY_STACK_PRINT()		\
do {					\
  if (yydebug_)				\
    yystack_print_ ();			\
} while (false)

#else /* !YYDEBUG */

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_REDUCE_PRINT(Rule)
# define YY_STACK_PRINT()

#endif /* !YYDEBUG */

#define yyerrok		(yyerrstatus_ = 0)
#define yyclearin	(yychar = yyempty_)

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


namespace eprosima {

/* Line 382 of lalr1.cc  */
#line 149 "IDLParser.cc"

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
              /* Fall through.  */
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
  {
  }

  IDLParser::~IDLParser ()
  {
  }

#if YYDEBUG
  /*--------------------------------.
  | Print this symbol on YYOUTPUT.  |
  `--------------------------------*/

  inline void
  IDLParser::yy_symbol_value_print_ (int yytype,
			   const semantic_type* yyvaluep, const location_type* yylocationp)
  {
    YYUSE (yylocationp);
    YYUSE (yyvaluep);
    switch (yytype)
      {
         default:
	  break;
      }
  }


  void
  IDLParser::yy_symbol_print_ (int yytype,
			   const semantic_type* yyvaluep, const location_type* yylocationp)
  {
    *yycdebug_ << (yytype < yyntokens_ ? "token" : "nterm")
	       << ' ' << yytname_[yytype] << " ("
	       << *yylocationp << ": ";
    yy_symbol_value_print_ (yytype, yyvaluep, yylocationp);
    *yycdebug_ << ')';
  }
#endif

  void
  IDLParser::yydestruct_ (const char* yymsg,
			   int yytype, semantic_type* yyvaluep, location_type* yylocationp)
  {
    YYUSE (yylocationp);
    YYUSE (yymsg);
    YYUSE (yyvaluep);

    YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

    switch (yytype)
      {
  
	default:
	  break;
      }
  }

  void
  IDLParser::yypop_ (unsigned int n)
  {
    yystate_stack_.pop (n);
    yysemantic_stack_.pop (n);
    yylocation_stack_.pop (n);
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
#endif

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
    /// Lookahead and lookahead in internal form.
    int yychar = yyempty_;
    int yytoken = 0;

    /* State.  */
    int yyn;
    int yylen = 0;
    int yystate = 0;

    /* Error handling.  */
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// Semantic value of the lookahead.
    semantic_type yylval;
    /// Location of the lookahead.
    location_type yylloc;
    /// The locations where the error started and ended.
    location_type yyerror_range[3];

    /// $$.
    semantic_type yyval;
    /// @$.
    location_type yyloc;

    int yyresult;

    YYCDEBUG << "Starting parse" << std::endl;


    /* User initialization code.  */
    
/* Line 565 of lalr1.cc  */
#line 62 "idl.y"
{
// initialize the initial location object
     yylloc.begin.filename = yylloc.end.filename = &TCprovider.streamname;
}

/* Line 565 of lalr1.cc  */
#line 343 "IDLParser.cc"

    /* Initialize the stacks.  The initial state will be pushed in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystate_stack_ = state_stack_type (0);
    yysemantic_stack_ = semantic_stack_type (0);
    yylocation_stack_ = location_stack_type (0);
    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yylloc);

    /* New state.  */
  yynewstate:
    yystate_stack_.push (yystate);
    YYCDEBUG << "Entering state " << yystate << std::endl;

    /* Accept?  */
    if (yystate == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    /* Backup.  */
  yybackup:

    /* Try to take a decision without lookahead.  */
    yyn = yypact_[yystate];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    /* Read a lookahead token.  */
    if (yychar == yyempty_)
      {
	YYCDEBUG << "Reading a token: ";
	yychar = yylex (&yylval, &yylloc);
      }


    /* Convert token to internal form.  */
    if (yychar <= yyeof_)
      {
	yychar = yytoken = yyeof_;
	YYCDEBUG << "Now at end of input." << std::endl;
      }
    else
      {
	yytoken = yytranslate_ (yychar);
	YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
      }

    /* If the proper action on seeing token YYTOKEN is to reduce or to
       detect an error, take that action.  */
    yyn += yytoken;
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yytoken)
      goto yydefault;

    /* Reduce or error.  */
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
	if (yy_table_value_is_error_ (yyn))
	  goto yyerrlab;
	yyn = -yyn;
	goto yyreduce;
      }

    /* Shift the lookahead token.  */
    YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

    /* Discard the token being shifted.  */
    yychar = yyempty_;

    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yylloc);

    /* Count tokens shifted since error; after three, turn off error
       status.  */
    if (yyerrstatus_)
      --yyerrstatus_;

    yystate = yyn;
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystate];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    /* If YYLEN is nonzero, implement the default value of the action:
       `$$ = $1'.  Otherwise, use the top of the stack.

       Otherwise, the following line sets YYVAL to garbage.
       This behavior is undocumented and Bison
       users should not rely upon it.  */
    if (yylen)
      yyval = yysemantic_stack_[yylen - 1];
    else
      yyval = yysemantic_stack_[0];

    {
      slice<location_type, location_stack_type> slice (yylocation_stack_, yylen);
      YYLLOC_DEFAULT (yyloc, slice, yylen);
    }
    YY_REDUCE_PRINT (yyn);
    switch (yyn)
      {
	  case 2:

/* Line 690 of lalr1.cc  */
#line 188 "idl.y"
    {for(std::vector<TypeCode*>::iterator it = (yysemantic_stack_[(1) - (1)].mp_TypeCodeVec)->begin();it!=(yysemantic_stack_[(1) - (1)].mp_TypeCodeVec)->end();++it)
    {
    	TCprovider.addTypeCode(*it);
    }
    delete((yysemantic_stack_[(1) - (1)].mp_TypeCodeVec));
    }
    break;

  case 3:

/* Line 690 of lalr1.cc  */
#line 197 "idl.y"
    {
	(yyval.mp_TypeCodeVec) = (yysemantic_stack_[(1) - (1)].mp_TypeCodeVec);
	}
    break;

  case 4:

/* Line 690 of lalr1.cc  */
#line 201 "idl.y"
    {
	for(TypeCodeVec::iterator it = (yysemantic_stack_[(2) - (1)].mp_TypeCodeVec)->begin();it!=(yysemantic_stack_[(2) - (1)].mp_TypeCodeVec)->end();++it)
	{
	(yysemantic_stack_[(2) - (2)].mp_TypeCodeVec)->push_back(*it);
	}
	delete((yysemantic_stack_[(2) - (1)].mp_TypeCodeVec));
	(yyval.mp_TypeCodeVec) = (yysemantic_stack_[(2) - (2)].mp_TypeCodeVec);
	}
    break;

  case 5:

/* Line 690 of lalr1.cc  */
#line 211 "idl.y"
    {(yyval.mp_TypeCodeVec) = (yysemantic_stack_[(2) - (1)].mp_TypeCodeVec);}
    break;

  case 6:

/* Line 690 of lalr1.cc  */
#line 212 "idl.y"
    {(yyval.mp_TypeCodeVec) = (yysemantic_stack_[(2) - (1)].mp_TypeCodeVec);}
    break;

  case 7:

/* Line 690 of lalr1.cc  */
#line 213 "idl.y"
    {(yyval.mp_TypeCodeVec) = (yysemantic_stack_[(2) - (1)].mp_TypeCodeVec);}
    break;

  case 8:

/* Line 690 of lalr1.cc  */
#line 214 "idl.y"
    {(yyval.mp_TypeCodeVec) = (yysemantic_stack_[(2) - (1)].mp_TypeCodeVec);}
    break;

  case 9:

/* Line 690 of lalr1.cc  */
#line 215 "idl.y"
    {(yyval.mp_TypeCodeVec) = (yysemantic_stack_[(2) - (1)].mp_TypeCodeVec);}
    break;

  case 10:

/* Line 690 of lalr1.cc  */
#line 216 "idl.y"
    {(yyval.mp_TypeCodeVec) = (yysemantic_stack_[(1) - (1)].mp_TypeCodeVec);}
    break;

  case 11:

/* Line 690 of lalr1.cc  */
#line 220 "idl.y"
    {(yyval.mp_TypeCodeVec) = new TypeCodeVec();}
    break;

  case 12:

/* Line 690 of lalr1.cc  */
#line 222 "idl.y"
    {(yyval.mp_TypeCodeVec) = new TypeCodeVec();}
    break;

  case 13:

/* Line 690 of lalr1.cc  */
#line 224 "idl.y"
    {(yyval.mp_TypeCodeVec) = new TypeCodeVec();}
    break;

  case 14:

/* Line 690 of lalr1.cc  */
#line 228 "idl.y"
    {
	for(TypeCodeVec::iterator it = (yysemantic_stack_[(5) - (4)].mp_TypeCodeVec)->begin();it!=(yysemantic_stack_[(5) - (4)].mp_TypeCodeVec)->end();++it)
	{
	if((*it)->getKind() == TypeCode::KIND_STRUCT || 
		(*it)->getKind() == TypeCode::KIND_UNION ||
		(*it)->getKind() == TypeCode::KIND_ENUM)
	{
		MemberedTypeCode* membered = (MemberedTypeCode*)(*it);
		(yysemantic_stack_[(5) - (2)].stringVal)->append("::");
		(yysemantic_stack_[(5) - (2)].stringVal)->append(membered->getName());
		membered->setName(*(yysemantic_stack_[(5) - (2)].stringVal));
		delete((yysemantic_stack_[(5) - (2)].stringVal));
	}
	}
	(yyval.mp_TypeCodeVec) = (yysemantic_stack_[(5) - (4)].mp_TypeCodeVec);
	}
    break;

  case 15:

/* Line 690 of lalr1.cc  */
#line 248 "idl.y"
    {std::cout << "Warning: \"typedef\" token not allowed" << std::endl;}
    break;

  case 19:

/* Line 690 of lalr1.cc  */
#line 255 "idl.y"
    {StructTypeCode* sTC = new StructTypeCode();
	sTC->setName(*(yysemantic_stack_[(5) - (2)].stringVal));
	delete((yysemantic_stack_[(5) - (2)].stringVal));
	for(MemberVec::iterator it= (yysemantic_stack_[(5) - (4)].mp_MemberVec)->begin();it!=(yysemantic_stack_[(5) - (4)].mp_MemberVec)->end();++it)
	{
		sTC->addMember((StructMember*)(*it));
	}
	(yyval.mp_TypeCodeVec) = new TypeCodeVec();
	(yyval.mp_TypeCodeVec)->push_back((TypeCode*)sTC);
	}
    break;

  case 20:

/* Line 690 of lalr1.cc  */
#line 268 "idl.y"
    {(yyval.mp_MemberVec) = (yysemantic_stack_[(1) - (1)].mp_MemberVec);}
    break;

  case 21:

/* Line 690 of lalr1.cc  */
#line 270 "idl.y"
    {
	if((yysemantic_stack_[(2) - (1)].mp_MemberVec) ==NULL)
		(yyval.mp_MemberVec) = (yysemantic_stack_[(2) - (2)].mp_MemberVec);
	else
	{
	for(std::vector<Member*>::iterator it = (yysemantic_stack_[(2) - (1)].mp_MemberVec)->begin();it!=(yysemantic_stack_[(2) - (1)].mp_MemberVec)->end();++it)
	{
		(yysemantic_stack_[(2) - (2)].mp_MemberVec)->push_back(*it);
	}
	delete((yysemantic_stack_[(2) - (1)].mp_MemberVec));
	(yyval.mp_MemberVec) = (yysemantic_stack_[(2) - (2)].mp_MemberVec);
	}
	}
    break;

  case 22:

/* Line 690 of lalr1.cc  */
#line 285 "idl.y"
    {
	if((yysemantic_stack_[(3) - (1)].mp_TypeCode)->getKind() == TypeCode::KIND_NULL)
	{
		delete((yysemantic_stack_[(3) - (1)].mp_TypeCode));
		delete((yysemantic_stack_[(3) - (2)].mp_DeclaratorVec));
		(yyval.mp_MemberVec) = NULL;
	}
	else
	{
	MemberVec* MV = new MemberVec();
	bool first = true;
	for(DeclaratorVec::iterator it=(yysemantic_stack_[(3) - (2)].mp_DeclaratorVec)->begin();it!=(yysemantic_stack_[(3) - (2)].mp_DeclaratorVec)->end();++it)
	{
		TypeCode* pTC = (yysemantic_stack_[(3) - (1)].mp_TypeCode);
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
	delete((yysemantic_stack_[(3) - (2)].mp_DeclaratorVec));
	(yyval.mp_MemberVec) = MV;
	}
	}
    break;

  case 24:

/* Line 690 of lalr1.cc  */
#line 327 "idl.y"
    {
    (yyval.mp_TypeCode) = *((yysemantic_stack_[(1) - (1)].mp_TypeCodeVec)->begin());
    delete((yysemantic_stack_[(1) - (1)].mp_TypeCodeVec));
    }
    break;

  case 28:

/* Line 690 of lalr1.cc  */
#line 339 "idl.y"
    {
    TypeCode* pTC = TCprovider.findTypeCodebyName(*(yysemantic_stack_[(1) - (1)].mp_string));
    delete((yysemantic_stack_[(1) - (1)].mp_string));
    (yyval.mp_TypeCode) = pTC;
    }
    break;

  case 36:

/* Line 690 of lalr1.cc  */
#line 358 "idl.y"
    {
	std::cout << "Warning: \"Object\" token not allowed" << std::endl;
	(yyval.mp_TypeCode) = new PrimitiveTypeCode(TypeCode::KIND_NULL);
	}
    break;

  case 37:

/* Line 690 of lalr1.cc  */
#line 364 "idl.y"
    {std::cout << "Warning: \"any\" token not allowed" << std::endl;
	(yyval.mp_TypeCode) = new PrimitiveTypeCode(TypeCode::KIND_NULL);}
    break;

  case 43:

/* Line 690 of lalr1.cc  */
#line 378 "idl.y"
    {
	(yyval.mp_DeclaratorVec) = new DeclaratorVec();
	(yyval.mp_DeclaratorVec)->push_back((yysemantic_stack_[(1) - (1)].mp_Declarator));
	}
    break;

  case 44:

/* Line 690 of lalr1.cc  */
#line 383 "idl.y"
    {
	(yysemantic_stack_[(3) - (3)].mp_DeclaratorVec)->push_back((yysemantic_stack_[(3) - (1)].mp_Declarator)); 
	(yyval.mp_DeclaratorVec) = (yysemantic_stack_[(3) - (3)].mp_DeclaratorVec);
	}
    break;

  case 47:

/* Line 690 of lalr1.cc  */
#line 393 "idl.y"
    {
	(yyval.mp_Declarator) = new Declarator();
	(yyval.mp_Declarator)->first = *(yysemantic_stack_[(1) - (1)].stringVal);
	delete((yysemantic_stack_[(1) - (1)].stringVal));
	}
    break;

  case 49:

/* Line 690 of lalr1.cc  */
#line 403 "idl.y"
    {
	(yysemantic_stack_[(2) - (2)].mp_Declarator)->first = *(yysemantic_stack_[(2) - (1)].stringVal);
	delete((yysemantic_stack_[(2) - (1)].stringVal));
	(yyval.mp_Declarator) = (yysemantic_stack_[(2) - (2)].mp_Declarator);
	}
    break;

  case 50:

/* Line 690 of lalr1.cc  */
#line 411 "idl.y"
    {
	(yyval.mp_Declarator) = new Declarator();
	(yyval.mp_Declarator)->second.push_back((yysemantic_stack_[(1) - (1)].m_uint32_t));
	}
    break;

  case 51:

/* Line 690 of lalr1.cc  */
#line 416 "idl.y"
    {
	(yysemantic_stack_[(2) - (2)].mp_Declarator)->second.push_back((yysemantic_stack_[(2) - (1)].m_uint32_t)); 
	(yyval.mp_Declarator) = (yysemantic_stack_[(2) - (2)].mp_Declarator);}
    break;

  case 52:

/* Line 690 of lalr1.cc  */
#line 421 "idl.y"
    {(yyval.m_uint32_t) = (yysemantic_stack_[(3) - (2)].m_uint32_t);}
    break;

  case 53:

/* Line 690 of lalr1.cc  */
#line 427 "idl.y"
    {(yyval.mp_TypeCode) = new PrimitiveTypeCode(TypeCode::KIND_FLOAT);}
    break;

  case 54:

/* Line 690 of lalr1.cc  */
#line 429 "idl.y"
    {(yyval.mp_TypeCode) = new PrimitiveTypeCode(TypeCode::KIND_DOUBLE);}
    break;

  case 55:

/* Line 690 of lalr1.cc  */
#line 431 "idl.y"
    {(yyval.mp_TypeCode) = new PrimitiveTypeCode(TypeCode::KIND_LONGDOUBLE);}
    break;

  case 60:

/* Line 690 of lalr1.cc  */
#line 442 "idl.y"
    {(yyval.mp_TypeCode) = new PrimitiveTypeCode(TypeCode::KIND_LONG);}
    break;

  case 61:

/* Line 690 of lalr1.cc  */
#line 444 "idl.y"
    {(yyval.mp_TypeCode) = new PrimitiveTypeCode(TypeCode::KIND_LONGLONG);}
    break;

  case 62:

/* Line 690 of lalr1.cc  */
#line 447 "idl.y"
    {(yyval.mp_TypeCode) = new PrimitiveTypeCode(TypeCode::KIND_SHORT);}
    break;

  case 65:

/* Line 690 of lalr1.cc  */
#line 454 "idl.y"
    {(yyval.mp_TypeCode) = new PrimitiveTypeCode(TypeCode::KIND_ULONG);}
    break;

  case 66:

/* Line 690 of lalr1.cc  */
#line 456 "idl.y"
    {(yyval.mp_TypeCode) = new PrimitiveTypeCode(TypeCode::KIND_ULONGLONG);}
    break;

  case 67:

/* Line 690 of lalr1.cc  */
#line 459 "idl.y"
    {(yyval.mp_TypeCode) = new PrimitiveTypeCode(TypeCode::KIND_USHORT);}
    break;

  case 68:

/* Line 690 of lalr1.cc  */
#line 462 "idl.y"
    {(yyval.mp_TypeCode) = new PrimitiveTypeCode(TypeCode::KIND_CHAR);}
    break;

  case 69:

/* Line 690 of lalr1.cc  */
#line 465 "idl.y"
    {(yyval.mp_TypeCode) = new PrimitiveTypeCode(TypeCode::KIND_BOOLEAN);}
    break;

  case 70:

/* Line 690 of lalr1.cc  */
#line 468 "idl.y"
    {(yyval.mp_TypeCode) = new PrimitiveTypeCode(TypeCode::KIND_OCTET);}
    break;

  case 71:

/* Line 690 of lalr1.cc  */
#line 473 "idl.y"
    {
	EnumTypeCode* enTC= new EnumTypeCode();
	enTC->setName(*(yysemantic_stack_[(5) - (2)].stringVal));
	delete((yysemantic_stack_[(5) - (2)].stringVal));
	uint32_t ord = 0;
	for(StringVec::iterator it=(yysemantic_stack_[(5) - (4)].mp_StringVec)->begin();it!=(yysemantic_stack_[(5) - (4)].mp_StringVec)->end();++it)
	{
		EnumMember* eMember = new EnumMember(*it,ord);
		enTC->addMember(eMember);
		++ord;
	}
	delete((yysemantic_stack_[(5) - (4)].mp_StringVec));
	(yyval.mp_TypeCodeVec) = new TypeCodeVec();
	(yyval.mp_TypeCodeVec)->push_back((TypeCode*) enTC);
	}
    break;

  case 72:

/* Line 690 of lalr1.cc  */
#line 490 "idl.y"
    {
	(yyval.mp_StringVec) = new StringVec();
	(yyval.mp_StringVec)->push_back(*(yysemantic_stack_[(1) - (1)].mp_string));
	delete((yysemantic_stack_[(1) - (1)].mp_string));
	}
    break;

  case 73:

/* Line 690 of lalr1.cc  */
#line 496 "idl.y"
    {(yysemantic_stack_[(3) - (3)].mp_StringVec)->push_back(*(yysemantic_stack_[(3) - (1)].mp_string)); (yyval.mp_StringVec) = (yysemantic_stack_[(3) - (3)].mp_StringVec);delete((yysemantic_stack_[(3) - (1)].mp_string));}
    break;

  case 74:

/* Line 690 of lalr1.cc  */
#line 499 "idl.y"
    {(yyval.mp_string) = new std::string(*(yysemantic_stack_[(1) - (1)].stringVal));
	delete((yysemantic_stack_[(1) - (1)].stringVal));}
    break;

  case 75:

/* Line 690 of lalr1.cc  */
#line 505 "idl.y"
    {
	StringTypeCode* pSTC = new StringTypeCode((yysemantic_stack_[(4) - (3)].m_uint32_t));
	(yyval.mp_TypeCode) = (TypeCode*)pSTC;
	}
    break;

  case 76:

/* Line 690 of lalr1.cc  */
#line 510 "idl.y"
    {StringTypeCode* pSTC = new StringTypeCode(255);
	(yyval.mp_TypeCode) = (TypeCode*)pSTC;}
    break;

  case 77:

/* Line 690 of lalr1.cc  */
#line 516 "idl.y"
    {
	SequenceTypeCode* sTC = new SequenceTypeCode((yysemantic_stack_[(6) - (5)].m_uint32_t));
	sTC->setContentTypeCode((yysemantic_stack_[(6) - (3)].mp_TypeCode));
	(yyval.mp_TypeCode) = (TypeCode*) sTC;
	}
    break;

  case 78:

/* Line 690 of lalr1.cc  */
#line 522 "idl.y"
    {
	SequenceTypeCode* sTC = new SequenceTypeCode(255);
	sTC->setContentTypeCode((yysemantic_stack_[(4) - (3)].mp_TypeCode));
	(yyval.mp_TypeCode) = (TypeCode*) sTC;
	}
    break;

  case 81:

/* Line 690 of lalr1.cc  */
#line 535 "idl.y"
    {
	std::vector<int> index_to_remove;
	for(TypeCodeVec::iterator it = (yysemantic_stack_[(4) - (3)].mp_TypeCodeVec)->begin();it!=(yysemantic_stack_[(4) - (3)].mp_TypeCodeVec)->end();++it)
	{
	if((*it)->getKind() == TypeCode::KIND_STRUCT || 
		(*it)->getKind() == TypeCode::KIND_UNION ||
		(*it)->getKind() == TypeCode::KIND_ENUM)
	{
		MemberedTypeCode* membered = (MemberedTypeCode*)(*it);
		(yysemantic_stack_[(4) - (1)].mp_string)->append("::");
		(yysemantic_stack_[(4) - (1)].mp_string)->append(membered->getName());
		membered->setName(*(yysemantic_stack_[(4) - (1)].mp_string));
		delete((yysemantic_stack_[(4) - (1)].mp_string));
	}
	else
	{
		index_to_remove.push_back(std::distance((yysemantic_stack_[(4) - (3)].mp_TypeCodeVec)->begin(),it));
		delete(*it);
	}
	for(std::vector<int>::reverse_iterator it = index_to_remove.rbegin();it!=index_to_remove.rend();++it)
	{
		(yysemantic_stack_[(4) - (3)].mp_TypeCodeVec)->erase((yysemantic_stack_[(4) - (3)].mp_TypeCodeVec)->begin()+(*it));
	}
	}
	(yyval.mp_TypeCodeVec) = (yysemantic_stack_[(4) - (3)].mp_TypeCodeVec);
	}
    break;

  case 82:

/* Line 690 of lalr1.cc  */
#line 563 "idl.y"
    {
	delete((yysemantic_stack_[(2) - (2)].stringVal));
	(yyval.mp_TypeCodeVec) = new TypeCodeVec();
	}
    break;

  case 83:

/* Line 690 of lalr1.cc  */
#line 570 "idl.y"
    {(yyval.mp_string) = new std::string(*(yysemantic_stack_[(2) - (2)].stringVal));
	delete((yysemantic_stack_[(2) - (2)].stringVal));}
    break;

  case 84:

/* Line 690 of lalr1.cc  */
#line 573 "idl.y"
    {(yyval.mp_string) = new std::string(*(yysemantic_stack_[(3) - (2)].stringVal));
	delete((yysemantic_stack_[(3) - (2)].stringVal));}
    break;

  case 85:

/* Line 690 of lalr1.cc  */
#line 577 "idl.y"
    {(yyval.mp_TypeCodeVec) = new TypeCodeVec();}
    break;

  case 86:

/* Line 690 of lalr1.cc  */
#line 579 "idl.y"
    {
	for(TypeCodeVec::iterator it = (yysemantic_stack_[(2) - (2)].mp_TypeCodeVec)->begin();it!=(yysemantic_stack_[(2) - (2)].mp_TypeCodeVec)->end();++it)
		(yysemantic_stack_[(2) - (1)].mp_TypeCodeVec)->push_back(*it);
	(yyval.mp_TypeCodeVec) = (yysemantic_stack_[(2) - (1)].mp_TypeCodeVec);
	delete((yysemantic_stack_[(2) - (2)].mp_TypeCodeVec));
	}
    break;

  case 90:

/* Line 690 of lalr1.cc  */
#line 591 "idl.y"
    {
    delete((yysemantic_stack_[(2) - (1)].mp_TypeCode));
    (yyval.mp_TypeCodeVec) = new TypeCodeVec();
    }
    break;

  case 92:

/* Line 690 of lalr1.cc  */
#line 599 "idl.y"
    {(yyval.mp_string) = new std::string("");
	delete((yysemantic_stack_[(2) - (2)].mp_string));}
    break;

  case 93:

/* Line 690 of lalr1.cc  */
#line 605 "idl.y"
    {
	(yyval.mp_string) = new std::string(*(yysemantic_stack_[(1) - (1)].mp_string));
	delete((yysemantic_stack_[(1) - (1)].mp_string));}
    break;

  case 94:

/* Line 690 of lalr1.cc  */
#line 609 "idl.y"
    {(yyval.mp_string) = (yysemantic_stack_[(3) - (3)].mp_string);
	delete((yysemantic_stack_[(3) - (1)].mp_string));
	}
    break;

  case 95:

/* Line 690 of lalr1.cc  */
#line 615 "idl.y"
    {
	(yyval.mp_string) = new std::string(*(yysemantic_stack_[(1) - (1)].stringVal));
	delete((yysemantic_stack_[(1) - (1)].stringVal));
	}
    break;

  case 96:

/* Line 690 of lalr1.cc  */
#line 620 "idl.y"
    {
	(yysemantic_stack_[(3) - (3)].mp_string)->insert(0,"::");
	(yysemantic_stack_[(3) - (3)].mp_string)->insert(0,*(yysemantic_stack_[(3) - (1)].stringVal));
	delete((yysemantic_stack_[(3) - (1)].stringVal));
	(yyval.mp_string) = (yysemantic_stack_[(3) - (3)].mp_string);
	}
    break;

  case 98:

/* Line 690 of lalr1.cc  */
#line 630 "idl.y"
    {
	std::string* aux_str = new std::string("::");
	aux_str->append(*(yysemantic_stack_[(2) - (2)].stringVal));
	delete((yysemantic_stack_[(2) - (2)].stringVal));
	(yyval.mp_string) = aux_str;
	}
    break;

  case 99:

/* Line 690 of lalr1.cc  */
#line 637 "idl.y"
    {
	(yysemantic_stack_[(3) - (3)].mp_string)->insert(0,*(yysemantic_stack_[(3) - (2)].stringVal));
	(yysemantic_stack_[(3) - (3)].mp_string)->insert(0,"::");
	delete((yysemantic_stack_[(3) - (2)].stringVal));
	(yyval.mp_string) = (yysemantic_stack_[(3) - (3)].mp_string);
	}
    break;

  case 100:

/* Line 690 of lalr1.cc  */
#line 647 "idl.y"
    {
	UnionTypeCode* uTC = new UnionTypeCode();
	uTC->setName(*(yysemantic_stack_[(9) - (2)].stringVal));
	delete((yysemantic_stack_[(9) - (2)].stringVal));
	uTC->setDiscriminatorTypeCode((yysemantic_stack_[(9) - (5)].mp_TypeCode));
	UnionMember* uM_boolWithDefault = NULL;
	bool isTrue = false;
	for(MemberVec::iterator it = (yysemantic_stack_[(9) - (8)].mp_MemberVec)->begin();it!=(yysemantic_stack_[(9) - (8)].mp_MemberVec)->end();++it)
	{
		UnionMember* uM = (UnionMember*)(*it);
		std::vector<int32_t> labels = uM->getLabels();
		bool change = false;
		bool boolDefaultFound = false;
		for(std::vector<int32_t>::iterator it = labels.begin();it!=labels.end();++it)
		{
			if((yysemantic_stack_[(9) - (5)].mp_TypeCode)->getKind() == TypeCode::KIND_CHAR && (*it) == -1000)
			{
				(*it) = 254;
				change = true;
			}
			if((yysemantic_stack_[(9) - (5)].mp_TypeCode)->getKind() == TypeCode::KIND_ENUM && (*it) == -1000)
			{
				(*it) = 0;
				change = true;
			}
			if((yysemantic_stack_[(9) - (5)].mp_TypeCode)->getKind() == TypeCode::KIND_BOOLEAN && (*it) == -1000)
			{
				uM_boolWithDefault = uM;
				boolDefaultFound = true;
			}
			if((yysemantic_stack_[(9) - (5)].mp_TypeCode)->getKind() == TypeCode::KIND_BOOLEAN)
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
	delete((yysemantic_stack_[(9) - (8)].mp_MemberVec));
	(yyval.mp_TypeCodeVec) = new TypeCodeVec();
	(yyval.mp_TypeCodeVec)->push_back((TypeCode*) uTC);
	}
    break;

  case 104:

/* Line 690 of lalr1.cc  */
#line 709 "idl.y"
    {
    (yyval.mp_TypeCode) = * (yysemantic_stack_[(1) - (1)].mp_TypeCodeVec)->begin();
    }
    break;

  case 106:

/* Line 690 of lalr1.cc  */
#line 716 "idl.y"
    {
	(yyval.mp_MemberVec) = new MemberVec();
	(yyval.mp_MemberVec)->push_back((yysemantic_stack_[(1) - (1)].mp_Member));
	}
    break;

  case 107:

/* Line 690 of lalr1.cc  */
#line 721 "idl.y"
    {
	(yysemantic_stack_[(2) - (2)].mp_MemberVec)->push_back((yysemantic_stack_[(2) - (1)].mp_Member)); 
	(yyval.mp_MemberVec) = (yysemantic_stack_[(2) - (2)].mp_MemberVec);
	}
    break;

  case 108:

/* Line 690 of lalr1.cc  */
#line 727 "idl.y"
    {
	((UnionMember*)((yysemantic_stack_[(3) - (2)].mp_Member)))->setLabels((yysemantic_stack_[(3) - (1)].mp_Declarator)->second);
	(yyval.mp_Member) = (yysemantic_stack_[(3) - (2)].mp_Member);
	}
    break;

  case 109:

/* Line 690 of lalr1.cc  */
#line 734 "idl.y"
    {(yyval.mp_Declarator) = (yysemantic_stack_[(1) - (1)].mp_Declarator);}
    break;

  case 110:

/* Line 690 of lalr1.cc  */
#line 736 "idl.y"
    {
	(yysemantic_stack_[(2) - (2)].mp_Declarator)->second.push_back(*((yysemantic_stack_[(2) - (1)].mp_Declarator)->second.begin()));
	(yyval.mp_Declarator) = (yysemantic_stack_[(2) - (2)].mp_Declarator);
	delete((yysemantic_stack_[(2) - (1)].mp_Declarator));}
    break;

  case 111:

/* Line 690 of lalr1.cc  */
#line 743 "idl.y"
    {
	Declarator * dCL = new Declarator();
	if((yysemantic_stack_[(3) - (2)].mp_TypeLiteral)->type == NUMBER_TYPE)
	{
		dCL->second.push_back((yysemantic_stack_[(3) - (2)].mp_TypeLiteral)->num);
	}
	else if((yysemantic_stack_[(3) - (2)].mp_TypeLiteral)->type == BOOL_TYPE)
	{
		dCL->second.push_back((yysemantic_stack_[(3) - (2)].mp_TypeLiteral)->boolean);	
	}
	else if((yysemantic_stack_[(3) - (2)].mp_TypeLiteral)->type == STRING_TYPE)
	{
	int32_t sum = 0;
	for(size_t i = 0;i<(yysemantic_stack_[(3) - (2)].mp_TypeLiteral)->str.size();++i)
		sum+=(yysemantic_stack_[(3) - (2)].mp_TypeLiteral)->str[i];
	dCL->second.push_back(sum);
	}
	else if((yysemantic_stack_[(3) - (2)].mp_TypeLiteral)->type == SCOPED_TYPE)
	{
	dCL->second.push_back(TCprovider.findENUMvalue((yysemantic_stack_[(3) - (2)].mp_TypeLiteral)->str));
	}
	}
    break;

  case 112:

/* Line 690 of lalr1.cc  */
#line 766 "idl.y"
    {
	Declarator * dCL = new Declarator();
	dCL->second.push_back(-1000);
	(yyval.mp_Declarator) = dCL;
	}
    break;

  case 113:

/* Line 690 of lalr1.cc  */
#line 773 "idl.y"
    {
	UnionMember* uM = new UnionMember();
	uM->setName((yysemantic_stack_[(2) - (2)].mp_Declarator)->first);
	delete((yysemantic_stack_[(2) - (2)].mp_Declarator));
	uM->setTypeCode((yysemantic_stack_[(2) - (1)].mp_TypeCode));
	(yyval.mp_Member) = (Member*) uM;
	}
    break;

  case 114:

/* Line 690 of lalr1.cc  */
#line 784 "idl.y"
    {std::cout << "Warning: \"attribute\" token not allowed" << std::endl;
	(yyval.mp_TypeCode) = new PrimitiveTypeCode(TypeCode::KIND_NULL);}
    break;

  case 115:

/* Line 690 of lalr1.cc  */
#line 787 "idl.y"
    {std::cout << "Warning: \"readonly attribute\" token not allowed" << std::endl;
	(yyval.mp_TypeCode) = new PrimitiveTypeCode(TypeCode::KIND_NULL);}
    break;

  case 116:

/* Line 690 of lalr1.cc  */
#line 792 "idl.y"
    {
    (yyval.mp_TypeCode) = NULL;
    }
    break;

  case 117:

/* Line 690 of lalr1.cc  */
#line 796 "idl.y"
    {(yyval.mp_TypeCode) = NULL;}
    break;

  case 118:

/* Line 690 of lalr1.cc  */
#line 801 "idl.y"
    {(yyval.mp_TypeCodeVec) = new TypeCodeVec();
	delete((yysemantic_stack_[(3) - (2)].stringVal));}
    break;

  case 119:

/* Line 690 of lalr1.cc  */
#line 804 "idl.y"
    {(yyval.mp_TypeCodeVec) = new TypeCodeVec();
	delete((yysemantic_stack_[(4) - (3)].stringVal));}
    break;

  case 120:

/* Line 690 of lalr1.cc  */
#line 808 "idl.y"
    {(yyval.m_uint32_t) = 0;}
    break;

  case 121:

/* Line 690 of lalr1.cc  */
#line 811 "idl.y"
    {(yyval.m_uint32_t) = 0;}
    break;

  case 123:

/* Line 690 of lalr1.cc  */
#line 816 "idl.y"
    {(yyval.m_uint32_t) = 0;}
    break;

  case 124:

/* Line 690 of lalr1.cc  */
#line 820 "idl.y"
    {(yyval.m_uint32_t) = 0;}
    break;

  case 125:

/* Line 690 of lalr1.cc  */
#line 822 "idl.y"
    {(yyval.m_uint32_t) = 0;}
    break;

  case 126:

/* Line 690 of lalr1.cc  */
#line 826 "idl.y"
    {(yyval.m_uint32_t) = 0;}
    break;

  case 127:

/* Line 690 of lalr1.cc  */
#line 828 "idl.y"
    {(yyval.m_uint32_t) = 0;}
    break;

  case 128:

/* Line 690 of lalr1.cc  */
#line 831 "idl.y"
    {(yyval.m_uint32_t) = 0;}
    break;

  case 129:

/* Line 690 of lalr1.cc  */
#line 835 "idl.y"
    {(yyval.m_uint32_t) = 0;}
    break;

  case 130:

/* Line 690 of lalr1.cc  */
#line 837 "idl.y"
    {(yyval.m_uint32_t) = 0;}
    break;

  case 131:

/* Line 690 of lalr1.cc  */
#line 839 "idl.y"
    {(yyval.m_uint32_t) = 0;}
    break;

  case 132:

/* Line 690 of lalr1.cc  */
#line 843 "idl.y"
    {(yyval.m_uint32_t) = 0;}
    break;

  case 133:

/* Line 690 of lalr1.cc  */
#line 845 "idl.y"
    {(yyval.m_uint32_t) = 0;}
    break;

  case 134:

/* Line 690 of lalr1.cc  */
#line 849 "idl.y"
    {(yyval.m_uint32_t) = 0;}
    break;

  case 135:

/* Line 690 of lalr1.cc  */
#line 851 "idl.y"
    {(yyval.m_uint32_t) = 0;}
    break;

  case 136:

/* Line 690 of lalr1.cc  */
#line 855 "idl.y"
    {(yyval.m_uint32_t) = 0;
	delete((yysemantic_stack_[(1) - (1)].stringVal));}
    break;

  case 137:

/* Line 690 of lalr1.cc  */
#line 858 "idl.y"
    {(yyval.m_uint32_t) = 0;
	delete((yysemantic_stack_[(3) - (1)].stringVal));}
    break;

  case 138:

/* Line 690 of lalr1.cc  */
#line 863 "idl.y"
    {
    delete((yysemantic_stack_[(1) - (1)].mp_TypeCode));
    (yyval.m_uint32_t) = 0;
    }
    break;

  case 139:

/* Line 690 of lalr1.cc  */
#line 868 "idl.y"
    {
    delete((yysemantic_stack_[(1) - (1)].mp_TypeCode));
    (yyval.m_uint32_t) = 0;
    }
    break;

  case 140:

/* Line 690 of lalr1.cc  */
#line 873 "idl.y"
    {
    delete((yysemantic_stack_[(1) - (1)].mp_TypeCode));
    (yyval.m_uint32_t) = 0;
    }
    break;

  case 141:

/* Line 690 of lalr1.cc  */
#line 887 "idl.y"
    {
	if((yysemantic_stack_[(1) - (1)].mp_TypeLiteral)->type == NUMBER_TYPE)
		(yyval.m_uint32_t) = (uint32_t)(yysemantic_stack_[(1) - (1)].mp_TypeLiteral)->num;
	else
		(yyval.m_uint32_t) = 0;
	delete((yysemantic_stack_[(1) - (1)].mp_TypeLiteral));
	}
    break;

  case 142:

/* Line 690 of lalr1.cc  */
#line 898 "idl.y"
    {(yyval.mp_TypeLiteral) = new TypeLiteral();
	(yyval.mp_TypeLiteral)->type = SCOPED_TYPE;
	(yyval.mp_TypeLiteral)->str = *(yysemantic_stack_[(1) - (1)].mp_string);
	delete((yysemantic_stack_[(1) - (1)].mp_string));
	}
    break;

  case 143:

/* Line 690 of lalr1.cc  */
#line 904 "idl.y"
    {(yyval.mp_TypeLiteral) = (yysemantic_stack_[(1) - (1)].mp_TypeLiteral);}
    break;

  case 144:

/* Line 690 of lalr1.cc  */
#line 906 "idl.y"
    {(yyval.mp_TypeLiteral) = (yysemantic_stack_[(3) - (2)].mp_TypeLiteral);}
    break;

  case 145:

/* Line 690 of lalr1.cc  */
#line 908 "idl.y"
    {
	if((yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->type == (yysemantic_stack_[(3) - (3)].mp_TypeLiteral)->type && (yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->type == BOOL_TYPE)
		(yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->boolean = (yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->boolean | (yysemantic_stack_[(3) - (3)].mp_TypeLiteral)->boolean;
	else if((yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->type == (yysemantic_stack_[(3) - (3)].mp_TypeLiteral)->type && (yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->type == NUMBER_TYPE)
		(yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->boolean = (yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->boolean | (yysemantic_stack_[(3) - (3)].mp_TypeLiteral)->boolean;
	else
		(yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->boolean = false;
	(yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->type = BOOL_TYPE;
	delete((yysemantic_stack_[(3) - (3)].mp_TypeLiteral));
	(yyval.mp_TypeLiteral) = (yysemantic_stack_[(3) - (1)].mp_TypeLiteral);
	}
    break;

  case 146:

/* Line 690 of lalr1.cc  */
#line 920 "idl.y"
    {if((yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->type != NUMBER_TYPE || (yysemantic_stack_[(3) - (3)].mp_TypeLiteral)->type != NUMBER_TYPE)
	{
		(yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->type = NUMBER_TYPE;
		(yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->num = 0;
	}
	else
	{
		(yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->num = pow((yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->num,(yysemantic_stack_[(3) - (3)].mp_TypeLiteral)->num);
	}
	delete((yysemantic_stack_[(3) - (3)].mp_TypeLiteral));
	(yyval.mp_TypeLiteral) = (yysemantic_stack_[(3) - (1)].mp_TypeLiteral);
	}
    break;

  case 147:

/* Line 690 of lalr1.cc  */
#line 933 "idl.y"
    {
	if((yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->type == (yysemantic_stack_[(3) - (3)].mp_TypeLiteral)->type && (yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->type == BOOL_TYPE)
		(yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->boolean = (yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->boolean & (yysemantic_stack_[(3) - (3)].mp_TypeLiteral)->boolean;
	else if((yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->type == (yysemantic_stack_[(3) - (3)].mp_TypeLiteral)->type && (yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->type == NUMBER_TYPE)
		(yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->boolean = (yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->boolean & (yysemantic_stack_[(3) - (3)].mp_TypeLiteral)->boolean;
	else
		(yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->boolean = false;
	(yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->type = BOOL_TYPE;
	delete((yysemantic_stack_[(3) - (3)].mp_TypeLiteral));
	(yyval.mp_TypeLiteral) = (yysemantic_stack_[(3) - (1)].mp_TypeLiteral);
	}
    break;

  case 148:

/* Line 690 of lalr1.cc  */
#line 945 "idl.y"
    {if((yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->type != NUMBER_TYPE || (yysemantic_stack_[(3) - (3)].mp_TypeLiteral)->type != NUMBER_TYPE)
	{
		(yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->type = NUMBER_TYPE;
		(yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->num = 0;
	}
	else
	{
		(yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->num = (int)(yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->num << (int)(yysemantic_stack_[(3) - (3)].mp_TypeLiteral)->num;
	}
	delete((yysemantic_stack_[(3) - (3)].mp_TypeLiteral));
	(yyval.mp_TypeLiteral) = (yysemantic_stack_[(3) - (1)].mp_TypeLiteral);
	}
    break;

  case 149:

/* Line 690 of lalr1.cc  */
#line 958 "idl.y"
    {if((yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->type != NUMBER_TYPE || (yysemantic_stack_[(3) - (3)].mp_TypeLiteral)->type != NUMBER_TYPE)
	{
		(yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->type = NUMBER_TYPE;
		(yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->num = 0;
	}
	else
	{
		(yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->num = (int)(yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->num >> (int)(yysemantic_stack_[(3) - (3)].mp_TypeLiteral)->num;
	}
	delete((yysemantic_stack_[(3) - (3)].mp_TypeLiteral));
	(yyval.mp_TypeLiteral) = (yysemantic_stack_[(3) - (1)].mp_TypeLiteral);
	}
    break;

  case 150:

/* Line 690 of lalr1.cc  */
#line 971 "idl.y"
    {
	if((yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->type != (yysemantic_stack_[(3) - (3)].mp_TypeLiteral)->type || (yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->type == BOOL_TYPE)
	{
	delete((yysemantic_stack_[(3) - (3)].mp_TypeLiteral));
	(yyval.mp_TypeLiteral) = (yysemantic_stack_[(3) - (1)].mp_TypeLiteral);
	}
	else
	{
	if((yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->type == NUMBER_TYPE)
	{
	(yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->num = (yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->num + (yysemantic_stack_[(3) - (3)].mp_TypeLiteral)->num;
	delete((yysemantic_stack_[(3) - (3)].mp_TypeLiteral));
	}
	else
	{
	(yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->str.append((yysemantic_stack_[(3) - (3)].mp_TypeLiteral)->str);
	delete((yysemantic_stack_[(3) - (3)].mp_TypeLiteral));
	}
	(yyval.mp_TypeLiteral) = (yysemantic_stack_[(3) - (1)].mp_TypeLiteral);
	}
	}
    break;

  case 151:

/* Line 690 of lalr1.cc  */
#line 993 "idl.y"
    {
	if((yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->type != (yysemantic_stack_[(3) - (3)].mp_TypeLiteral)->type || (yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->type == BOOL_TYPE || (yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->type == STRING_TYPE || (yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->type == SCOPED_TYPE)
	{
	delete((yysemantic_stack_[(3) - (3)].mp_TypeLiteral));
	(yyval.mp_TypeLiteral) = (yysemantic_stack_[(3) - (1)].mp_TypeLiteral);
	}
	else
	{
	(yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->num = (yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->num - (yysemantic_stack_[(3) - (3)].mp_TypeLiteral)->num;
	delete((yysemantic_stack_[(3) - (3)].mp_TypeLiteral));
	(yyval.mp_TypeLiteral) = (yysemantic_stack_[(3) - (1)].mp_TypeLiteral);
	}
	}
    break;

  case 152:

/* Line 690 of lalr1.cc  */
#line 1007 "idl.y"
    {
	if((yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->type != NUMBER_TYPE || (yysemantic_stack_[(3) - (3)].mp_TypeLiteral)->type != NUMBER_TYPE)
	{
		(yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->type = NUMBER_TYPE;
		(yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->num = 0;
	}
	else
	{
		(yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->num = (yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->num * (yysemantic_stack_[(3) - (3)].mp_TypeLiteral)->num;
	}
	delete((yysemantic_stack_[(3) - (3)].mp_TypeLiteral));
	(yyval.mp_TypeLiteral) = (yysemantic_stack_[(3) - (1)].mp_TypeLiteral);
	}
    break;

  case 153:

/* Line 690 of lalr1.cc  */
#line 1021 "idl.y"
    {
	if((yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->type != NUMBER_TYPE || (yysemantic_stack_[(3) - (3)].mp_TypeLiteral)->type != NUMBER_TYPE)
	{
		(yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->type = NUMBER_TYPE;
		(yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->num = 0;
	}
	else
	{
		(yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->num = (yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->num / (yysemantic_stack_[(3) - (3)].mp_TypeLiteral)->num;
	}
	delete((yysemantic_stack_[(3) - (3)].mp_TypeLiteral));
	(yyval.mp_TypeLiteral) = (yysemantic_stack_[(3) - (1)].mp_TypeLiteral);
	}
    break;

  case 154:

/* Line 690 of lalr1.cc  */
#line 1035 "idl.y"
    {
	if((yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->type != NUMBER_TYPE || (yysemantic_stack_[(3) - (3)].mp_TypeLiteral)->type != NUMBER_TYPE)
	{
		(yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->type = NUMBER_TYPE;
		(yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->num = 0;
	}
	else
	{
		(yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->num = (int)(yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->num % (int)(yysemantic_stack_[(3) - (3)].mp_TypeLiteral)->num;
	}
	delete((yysemantic_stack_[(3) - (3)].mp_TypeLiteral));
	(yyval.mp_TypeLiteral) = (yysemantic_stack_[(3) - (1)].mp_TypeLiteral);
	}
    break;

  case 155:

/* Line 690 of lalr1.cc  */
#line 1049 "idl.y"
    {
	if((yysemantic_stack_[(2) - (2)].mp_TypeLiteral)->type != NUMBER_TYPE)
	{
	(yysemantic_stack_[(2) - (2)].mp_TypeLiteral)->type = NUMBER_TYPE;
	(yysemantic_stack_[(2) - (2)].mp_TypeLiteral)->num = 0;
	}
	else
		(yysemantic_stack_[(2) - (2)].mp_TypeLiteral)->num--;
	(yyval.mp_TypeLiteral) = (yysemantic_stack_[(2) - (2)].mp_TypeLiteral);
	}
    break;

  case 156:

/* Line 690 of lalr1.cc  */
#line 1060 "idl.y"
    {
	if((yysemantic_stack_[(2) - (2)].mp_TypeLiteral)->type != NUMBER_TYPE)
	{
	(yysemantic_stack_[(2) - (2)].mp_TypeLiteral)->type = NUMBER_TYPE;
	(yysemantic_stack_[(2) - (2)].mp_TypeLiteral)->num = 0;
	}
	else
		(yysemantic_stack_[(2) - (2)].mp_TypeLiteral)->num++;
	(yyval.mp_TypeLiteral) = (yysemantic_stack_[(2) - (2)].mp_TypeLiteral);
	}
    break;

  case 157:

/* Line 690 of lalr1.cc  */
#line 1071 "idl.y"
    {
	if((yysemantic_stack_[(2) - (2)].mp_TypeLiteral)->type == STRING_TYPE)
	{
	(yysemantic_stack_[(2) - (2)].mp_TypeLiteral)->boolean = false;
	}
	else if ((yysemantic_stack_[(2) - (2)].mp_TypeLiteral)->type == BOOL_TYPE)
	{
	(yysemantic_stack_[(2) - (2)].mp_TypeLiteral)->boolean = !((yysemantic_stack_[(2) - (2)].mp_TypeLiteral)->boolean);
	}
	else
	{
	(yysemantic_stack_[(2) - (2)].mp_TypeLiteral)->boolean = !((yysemantic_stack_[(2) - (2)].mp_TypeLiteral)->num);
	}
	(yysemantic_stack_[(2) - (2)].mp_TypeLiteral)->type = BOOL_TYPE;
	(yyval.mp_TypeLiteral) = (yysemantic_stack_[(2) - (2)].mp_TypeLiteral);
	}
    break;

  case 158:

/* Line 690 of lalr1.cc  */
#line 1093 "idl.y"
    {(yyval.mp_TypeLiteral) = new TypeLiteral();
	(yyval.mp_TypeLiteral)->type = NUMBER_TYPE;
	(yyval.mp_TypeLiteral)->num = (yysemantic_stack_[(1) - (1)].integerVal);
	}
    break;

  case 159:

/* Line 690 of lalr1.cc  */
#line 1098 "idl.y"
    {(yyval.mp_TypeLiteral) = new TypeLiteral();
	(yyval.mp_TypeLiteral)->type = NUMBER_TYPE;
	(yyval.mp_TypeLiteral)->num = (yysemantic_stack_[(1) - (1)].doubleVal);
	}
    break;

  case 160:

/* Line 690 of lalr1.cc  */
#line 1103 "idl.y"
    {(yyval.mp_TypeLiteral) = new TypeLiteral();
	(yyval.mp_TypeLiteral)->type = STRING_TYPE;
	(yyval.mp_TypeLiteral)->str = *(yysemantic_stack_[(1) - (1)].stringVal);
	delete((yysemantic_stack_[(1) - (1)].stringVal));
	}
    break;

  case 161:

/* Line 690 of lalr1.cc  */
#line 1109 "idl.y"
    {(yyval.mp_TypeLiteral) = new TypeLiteral();
	(yyval.mp_TypeLiteral)->type = STRING_TYPE;
	(yyval.mp_TypeLiteral)->str = *(yysemantic_stack_[(1) - (1)].stringVal);
	delete((yysemantic_stack_[(1) - (1)].stringVal));
	}
    break;

  case 162:

/* Line 690 of lalr1.cc  */
#line 1115 "idl.y"
    {(yyval.mp_TypeLiteral) = new TypeLiteral();
	(yyval.mp_TypeLiteral)->type = BOOL_TYPE;
	(yyval.mp_TypeLiteral)->boolean = (yysemantic_stack_[(1) - (1)].integerVal);
	}
    break;

  case 163:

/* Line 690 of lalr1.cc  */
#line 1138 "idl.y"
    {std::cout << "Warning: \"const\" token not allowed" << std::endl;
	 PrimitiveTypeCode* auxptrTC = new PrimitiveTypeCode(TypeCode::KIND_NULL);
	 (yyval.mp_TypeCodeVec) = new TypeCodeVec();
	 (yyval.mp_TypeCodeVec)->push_back(auxptrTC);
	}
    break;

  case 164:

/* Line 690 of lalr1.cc  */
#line 1146 "idl.y"
    {std::cout << "Warning: \"exception\" token not allowed" << std::endl;
	PrimitiveTypeCode* auxptrTC = new PrimitiveTypeCode(TypeCode::KIND_NULL);
	 (yyval.mp_TypeCodeVec) = new TypeCodeVec();
	 (yyval.mp_TypeCodeVec)->push_back(auxptrTC);
	}
    break;



/* Line 690 of lalr1.cc  */
#line 1832 "IDLParser.cc"
	default:
          break;
      }
    /* User semantic actions sometimes alter yychar, and that requires
       that yytoken be updated with the new translation.  We take the
       approach of translating immediately before every use of yytoken.
       One alternative is translating here after every semantic action,
       but that translation would be missed if the semantic action
       invokes YYABORT, YYACCEPT, or YYERROR immediately after altering
       yychar.  In the case of YYABORT or YYACCEPT, an incorrect
       destructor might then be invoked immediately.  In the case of
       YYERROR, subsequent parser actions might lead to an incorrect
       destructor call or verbose syntax error message before the
       lookahead is translated.  */
    YY_SYMBOL_PRINT ("-> $$ =", yyr1_[yyn], &yyval, &yyloc);

    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();

    yysemantic_stack_.push (yyval);
    yylocation_stack_.push (yyloc);

    /* Shift the result of the reduction.  */
    yyn = yyr1_[yyn];
    yystate = yypgoto_[yyn - yyntokens_] + yystate_stack_[0];
    if (0 <= yystate && yystate <= yylast_
	&& yycheck_[yystate] == yystate_stack_[0])
      yystate = yytable_[yystate];
    else
      yystate = yydefgoto_[yyn - yyntokens_];
    goto yynewstate;

  /*------------------------------------.
  | yyerrlab -- here on detecting error |
  `------------------------------------*/
  yyerrlab:
    /* Make sure we have latest lookahead translation.  See comments at
       user semantic actions for why this is necessary.  */
    yytoken = yytranslate_ (yychar);

    /* If not already recovering from an error, report this error.  */
    if (!yyerrstatus_)
      {
	++yynerrs_;
	if (yychar == yyempty_)
	  yytoken = yyempty_;
	error (yylloc, yysyntax_error_ (yystate, yytoken));
      }

    yyerror_range[1] = yylloc;
    if (yyerrstatus_ == 3)
      {
	/* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

	if (yychar <= yyeof_)
	  {
	  /* Return failure if at end of input.  */
	  if (yychar == yyeof_)
	    YYABORT;
	  }
	else
	  {
	    yydestruct_ ("Error: discarding", yytoken, &yylval, &yylloc);
	    yychar = yyempty_;
	  }
      }

    /* Else will try to reuse lookahead token after shifting the error
       token.  */
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

    yyerror_range[1] = yylocation_stack_[yylen - 1];
    /* Do not reclaim the symbols of the rule which action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    yystate = yystate_stack_[0];
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;	/* Each real token shifted decrements this.  */

    for (;;)
      {
	yyn = yypact_[yystate];
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

	/* Pop the current state because it cannot handle the error token.  */
	if (yystate_stack_.height () == 1)
	YYABORT;

	yyerror_range[1] = yylocation_stack_[0];
	yydestruct_ ("Error: popping",
		     yystos_[yystate],
		     &yysemantic_stack_[0], &yylocation_stack_[0]);
	yypop_ ();
	yystate = yystate_stack_[0];
	YY_STACK_PRINT ();
      }

    yyerror_range[2] = yylloc;
    // Using YYLLOC is tempting, but would change the location of
    // the lookahead.  YYLOC is available though.
    YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yyloc);

    /* Shift the error token.  */
    YY_SYMBOL_PRINT ("Shifting", yystos_[yyn],
		     &yysemantic_stack_[0], &yylocation_stack_[0]);

    yystate = yyn;
    goto yynewstate;

    /* Accept.  */
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    /* Abort.  */
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (yychar != yyempty_)
      {
        /* Make sure we have latest lookahead translation.  See comments
           at user semantic actions for why this is necessary.  */
        yytoken = yytranslate_ (yychar);
        yydestruct_ ("Cleanup: discarding lookahead", yytoken, &yylval,
                     &yylloc);
      }

    /* Do not reclaim the symbols of the rule which action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (yystate_stack_.height () != 1)
      {
	yydestruct_ ("Cleanup: popping",
		   yystos_[yystate_stack_[0]],
		   &yysemantic_stack_[0],
		   &yylocation_stack_[0]);
	yypop_ ();
      }

    return yyresult;
  }

  // Generate an error message.
  std::string
  IDLParser::yysyntax_error_ (int yystate, int yytoken)
  {
    std::string yyres;
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
       - The only way there can be no lookahead present (in yytoken) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yychar.
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
    if (yytoken != yyempty_)
      {
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            /* Stay within bounds of both yycheck and yytname.  */
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

    char const* yyformat = 0;
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


  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
  const short int IDLParser::yypact_ninf_ = -161;
  const short int
  IDLParser::yypact_[] =
  {
         1,   -28,    22,    20,    68,    75,    84,    53,    91,  -161,
    -161,  -161,   106,  -161,     1,  -161,    61,    62,  -161,  -161,
      76,  -161,  -161,    74,  -161,    80,    82,  -161,    78,  -161,
       5,    83,    86,  -161,    72,  -161,  -161,  -161,  -161,  -161,
     143,  -161,  -161,   119,     3,  -161,     1,   195,    81,    93,
    -161,  -161,   289,  -161,  -161,  -161,    29,  -161,  -161,   124,
    -161,    89,    16,  -161,  -161,   136,   104,  -161,  -161,  -161,
    -161,  -161,  -161,  -161,  -161,  -161,  -161,  -161,  -161,  -161,
    -161,  -161,  -161,   103,   143,  -161,  -161,   114,   120,   229,
     142,  -161,   122,   127,  -161,   126,   130,  -161,   137,   128,
     132,  -161,   141,   195,   180,  -161,  -161,  -161,  -161,  -161,
    -161,  -161,  -161,  -161,     4,     3,   181,  -161,  -161,   289,
      95,   166,  -161,   150,  -161,  -161,  -161,  -161,  -161,   185,
     146,  -161,  -161,  -161,   119,     3,  -161,   263,  -161,  -161,
     138,   162,   159,  -161,  -161,  -161,   186,  -161,  -161,  -161,
    -161,  -161,   156,  -161,  -161,   163,  -161,   181,  -161,  -161,
    -161,  -161,  -161,    95,    95,    95,    95,  -161,   161,   291,
    -161,  -161,  -161,   146,    10,  -161,   188,  -161,  -161,   -21,
      95,  -161,   138,  -161,   180,   169,   181,  -161,  -161,  -161,
      79,  -161,  -161,    95,    95,    95,    95,    95,    95,    95,
      95,    95,    95,  -161,  -161,  -161,  -161,  -161,   165,   172,
     289,   170,   208,    95,  -161,   167,  -161,  -161,    17,  -161,
    -161,   197,   197,    25,    25,   305,   319,   333,  -161,  -161,
    -161,  -161,    63,   181,     3,   173,  -161,   175,  -161,    95,
     184,   194,    17,   195,    17,  -161,  -161,   190,   228,  -161,
     277,  -161,  -161,  -161,   180,   200,  -161,  -161,   193,   192,
    -161,  -161,  -161,   228,  -161,  -161
  };

  /* YYDEFACT[S] -- default reduction number in state S.  Performed when
     YYTABLE doesn't specify something else to do.  Zero means the
     default is an error.  */
  const unsigned char
  IDLParser::yydefact_[] =
  {
         0,     0,     0,     0,     0,     0,     0,     0,     0,    11,
      12,    13,     0,     2,     3,    10,     0,     0,    16,    18,
       0,    79,    80,     0,    17,     0,     0,   163,     0,   164,
      82,     0,     0,    15,     0,     1,     4,     9,     5,     8,
      85,     6,     7,     0,     0,    84,     0,     0,     0,    95,
      69,    37,     0,    68,    54,    53,    60,    70,   121,     0,
      62,    76,     0,   123,    36,     0,     0,   140,   138,    35,
      34,    29,    30,    56,    58,    59,    57,    63,    64,    31,
      32,    33,   139,     0,    85,    28,    97,     0,     0,     0,
       0,   122,     0,     0,    74,     0,    72,    92,    93,     0,
       0,    40,     0,    20,     0,    23,    27,    25,    26,    24,
      42,    39,    38,    41,     0,     0,     0,    55,    61,     0,
       0,    65,    67,    98,    87,    81,    86,    90,    91,     0,
       0,    88,    89,    71,     0,     0,    14,     0,    19,    21,
      47,     0,    43,    45,    46,    48,    60,   105,   101,   102,
     103,   104,     0,    96,    47,   116,   114,     0,   158,   159,
     162,   160,   161,     0,     0,     0,     0,   142,     0,   141,
     143,    66,    99,     0,     0,   118,   132,    73,    94,     0,
       0,    49,    50,    22,     0,     0,     0,   115,   156,   155,
       0,   157,    75,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   119,   129,   131,   130,   125,     0,   126,
       0,     0,   134,     0,    78,     0,    51,    44,     0,   117,
     144,   148,   149,   150,   151,   145,   146,   147,   152,   153,
     154,   124,     0,     0,     0,     0,   120,     0,    52,     0,
       0,     0,   106,     0,   109,   127,   128,     0,     0,    77,
       0,   112,   100,   107,     0,     0,   110,   133,   136,     0,
     111,   113,   108,     0,   135,   137
  };

  /* YYPGOTO[NTERM-NUM].  */
  const short int
  IDLParser::yypgoto_[] =
  {
      -161,  -161,    31,  -161,  -161,  -161,   -24,   -42,   149,  -161,
      11,   116,   -46,   -45,  -161,  -161,  -161,  -161,    85,     2,
    -106,  -161,  -161,    77,  -161,  -161,   144,  -161,  -161,  -161,
    -161,  -161,  -161,   151,   152,  -161,   -44,   133,  -161,   -41,
    -161,  -161,  -161,  -161,  -161,   196,  -161,  -161,  -124,   -40,
     153,   -39,  -161,    35,  -161,    37,  -161,  -161,  -161,  -130,
    -161,   110,  -161,   198,  -161,    47,  -161,  -161,  -161,  -161,
      21,   -43,  -160,   -82,  -161,   -17,   -15
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const short int
  IDLParser::yydefgoto_[] =
  {
        -1,    12,    13,    14,    15,    16,    17,    18,   102,   103,
     104,   105,    67,    68,    69,    70,   108,   109,   141,   142,
     143,   144,   145,   181,   182,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    19,    95,    96,    82,
     112,    20,    21,    22,    23,    83,    84,    45,    97,   167,
      86,    24,   152,   241,   242,   243,   244,   255,    87,   156,
      88,   175,    89,    90,   176,   208,   209,   210,   212,   236,
     259,    91,   168,   169,   170,    25,    26
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If YYTABLE_NINF_, syntax error.  */
  const signed char IDLParser::yytable_ninf_ = -84;
  const short int
  IDLParser::yytable_[] =
  {
        85,   106,   107,   110,    98,   101,   111,    85,   113,   116,
     155,   178,    85,    49,    49,    50,    66,     1,    27,    53,
     215,     2,     3,    92,     2,    93,     4,   187,     5,   213,
     146,   239,    28,   204,   205,   240,   214,     6,    60,     7,
     206,     8,   121,    62,    85,    36,    65,    65,   117,    85,
     122,   155,   -83,   237,    44,   118,   219,   106,   107,   110,
      66,   101,   111,    85,   113,   207,    29,    92,   147,    93,
     151,     9,    10,    11,    85,   153,   157,    99,    30,    85,
     155,   188,   189,   190,   191,    31,   204,   205,   200,   201,
     202,   106,   107,   206,    32,    98,   111,    85,   158,    33,
     159,    34,   160,   161,   162,    49,    35,    37,    38,    48,
     247,   221,   222,   223,   224,   225,   226,   227,   228,   229,
     230,    40,    39,   193,   194,    43,    41,   246,    42,    94,
      46,   195,   196,    47,   220,   114,   115,   119,    65,   197,
     198,   199,   200,   201,   202,   120,   123,   163,   164,   165,
     124,   125,   130,    49,    50,    51,    52,   250,    53,     1,
     127,   166,    54,     2,     3,    55,   128,   233,   131,    56,
      85,    57,    58,   132,   133,    59,   136,    60,    61,     6,
     134,     7,    62,     8,    63,    64,    65,   135,   137,   138,
     140,   154,   171,    65,    98,   173,   180,   106,   107,   110,
     174,   101,   111,    85,   113,    49,    50,    51,   183,   184,
      53,   185,   118,   186,    54,     2,   218,    55,   192,   211,
     231,    56,   232,    57,   234,   235,   238,   248,   100,    60,
      61,     6,   249,   251,    62,     8,   258,    64,    65,    49,
      50,    51,   252,   263,    53,   257,   262,   264,    54,   195,
     196,    55,   139,   179,   254,    56,   261,    57,   148,   216,
     200,   201,   202,    60,    61,   149,   150,   177,    62,   217,
      63,    64,    65,    49,    50,    51,   172,   253,    53,   245,
     126,   256,    54,   203,   265,    55,     0,   129,     0,    56,
       0,    57,     0,     0,     0,     0,   100,    60,    61,    49,
      50,    51,    62,     0,    53,    64,    65,     0,    54,     0,
       0,    55,     0,     0,     0,    56,     0,    57,     0,     0,
       0,   193,   194,    60,    61,     0,   260,     0,    62,   195,
     196,    64,    65,     0,     0,   193,   194,   197,   198,   199,
     200,   201,   202,   195,   196,     0,     0,     0,     0,   193,
     194,   197,   198,   199,   200,   201,   202,   195,   196,     0,
       0,     0,     0,   193,   194,     0,   198,   199,   200,   201,
     202,   195,   196,     0,     0,     0,     0,   193,   194,     0,
       0,   199,   200,   201,   202,   195,   196,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   200,   201,   202
  };

  /* YYCHECK.  */
  const short int
  IDLParser::yycheck_[] =
  {
        40,    47,    47,    47,    44,    47,    47,    47,    47,    52,
     116,   135,    52,    10,    10,    11,    40,    16,    46,    15,
     180,    20,    21,    40,    20,    40,    25,   157,    27,    50,
      26,    14,    10,    23,    24,    18,    57,    36,    34,    38,
      30,    40,    26,    39,    84,    14,    43,    43,    19,    89,
      34,   157,    47,   213,    49,    26,   186,   103,   103,   103,
      84,   103,   103,   103,   103,    55,    46,    84,   114,    84,
     114,    70,    71,    72,   114,   115,   119,    46,    10,   119,
     186,   163,   164,   165,   166,    10,    23,    24,    63,    64,
      65,   137,   137,    30,    10,   135,   137,   137,     3,    46,
       5,    10,     7,     8,     9,    10,     0,    46,    46,    37,
     234,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,    47,    46,    44,    45,    47,    46,   233,    46,    10,
      47,    52,    53,    47,    55,    54,    43,    13,    43,    60,
      61,    62,    63,    64,    65,    56,    10,    52,    53,    54,
      46,    48,    10,    10,    11,    12,    13,   239,    15,    16,
      46,    66,    19,    20,    21,    22,    46,   210,    46,    26,
     210,    28,    29,    46,    48,    32,    48,    34,    35,    36,
      50,    38,    39,    40,    41,    42,    43,    50,    56,    48,
      10,    10,    26,    43,   234,    10,    58,   243,   243,   243,
      54,   243,   243,   243,   243,    10,    11,    12,    46,    50,
      15,    55,    26,    50,    19,    20,    47,    22,    57,    31,
      55,    26,    50,    28,    54,    17,    59,    54,    33,    34,
      35,    36,    57,    49,    39,    40,     8,    42,    43,    10,
      11,    12,    48,    50,    15,    55,    46,    55,    19,    52,
      53,    22,   103,   137,   243,    26,   254,    28,   114,   182,
      63,    64,    65,    34,    35,   114,   114,   134,    39,   184,
      41,    42,    43,    10,    11,    12,   123,   242,    15,   232,
      84,   244,    19,   173,   263,    22,    -1,    89,    -1,    26,
      -1,    28,    -1,    -1,    -1,    -1,    33,    34,    35,    10,
      11,    12,    39,    -1,    15,    42,    43,    -1,    19,    -1,
      -1,    22,    -1,    -1,    -1,    26,    -1,    28,    -1,    -1,
      -1,    44,    45,    34,    35,    -1,    49,    -1,    39,    52,
      53,    42,    43,    -1,    -1,    44,    45,    60,    61,    62,
      63,    64,    65,    52,    53,    -1,    -1,    -1,    -1,    44,
      45,    60,    61,    62,    63,    64,    65,    52,    53,    -1,
      -1,    -1,    -1,    44,    45,    -1,    61,    62,    63,    64,
      65,    52,    53,    -1,    -1,    -1,    -1,    44,    45,    -1,
      -1,    62,    63,    64,    65,    52,    53,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    63,    64,    65
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  IDLParser::yystos_[] =
  {
         0,    16,    20,    21,    25,    27,    36,    38,    40,    70,
      71,    72,    77,    78,    79,    80,    81,    82,    83,   112,
     117,   118,   119,   120,   127,   151,   152,    46,    10,    46,
      10,    10,    10,    46,    10,     0,    78,    46,    46,    46,
      47,    46,    46,    47,    49,   123,    47,    47,    37,    10,
      11,    12,    13,    15,    19,    22,    26,    28,    29,    32,
      34,    35,    39,    41,    42,    43,    82,    88,    89,    90,
      91,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   115,   121,   122,   125,   126,   134,   136,   138,
     139,   147,   151,   152,    10,   113,   114,   124,   125,    78,
      33,    83,    84,    85,    86,    87,    88,    89,    92,    93,
     112,   115,   116,   127,    54,    43,   147,    19,    26,    13,
      56,    26,    34,    10,    46,    48,   121,    46,    46,   139,
      10,    46,    46,    48,    50,    50,    48,    56,    48,    84,
      10,    94,    95,    96,    97,    98,    26,    88,   102,   109,
     110,   112,   128,   125,    10,    96,   135,   147,     3,     5,
       7,     8,     9,    52,    53,    54,    66,   125,   148,   149,
     150,    26,   126,    10,    54,   137,   140,   113,   124,    87,
      58,    99,   100,    46,    50,    55,    50,   135,   149,   149,
     149,   149,    57,    44,    45,    52,    53,    60,    61,    62,
      63,    64,    65,   137,    23,    24,    30,    55,   141,   142,
     143,    31,   144,    50,    57,   148,    99,    94,    47,   135,
      55,   149,   149,   149,   149,   149,   149,   149,   149,   149,
     149,    55,    50,   147,    54,    17,   145,   148,    59,    14,
      18,   129,   130,   131,   132,   141,    96,   124,    54,    57,
     149,    49,    48,   129,    86,   133,   131,    55,     8,   146,
      49,    95,    46,    50,    55,   146
  };

#if YYDEBUG
  /* TOKEN_NUMBER_[YYLEX-NUM] -- Internal symbol number corresponding
     to YYLEX-NUM.  */
  const unsigned short int
  IDLParser::yytoken_number_[] =
  {
         0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,    59,   123,   125,    58,
      44,    61,    43,    45,    40,    41,    60,    62,    91,    93,
     124,    94,    38,    42,    47,    37,   126,    39,    34,    92,
     301,   302,   303,   304,   305,   306
  };
#endif

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
  const unsigned char
  IDLParser::yyr1_[] =
  {
         0,    76,    77,    78,    78,    79,    79,    79,    79,    79,
      79,    80,    80,    80,    81,    82,    82,    82,    82,    83,
      84,    84,    85,    86,    86,    87,    87,    87,    88,    89,
      89,    89,    89,    89,    89,    89,    90,    91,    92,    92,
      93,    93,    93,    94,    94,    95,    95,    96,    97,    98,
      99,    99,   100,   101,   101,   101,   102,   102,   103,   103,
     104,   104,   105,   106,   106,   107,   107,   108,   109,   110,
     111,   112,   113,   113,   114,   115,   115,   116,   116,   117,
     117,   118,   119,   120,   120,   121,   121,   122,   122,   122,
     122,   122,   123,   124,   124,   125,   125,   125,   126,   126,
     127,   128,   128,   128,   128,   128,   129,   129,   130,   131,
     131,   132,   132,   133,   134,   134,   135,   135,   136,   136,
     137,   138,   139,   139,   140,   140,   141,   141,   142,   143,
     143,   143,   144,   144,   145,   145,   146,   146,   147,   147,
     147,   148,   149,   149,   149,   149,   149,   149,   149,   149,
     149,   149,   149,   149,   149,   149,   149,   149,   150,   150,
     150,   150,   150,   151,   152
  };

  /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
  const unsigned char
  IDLParser::yyr2_[] =
  {
         0,     2,     1,     1,     2,     2,     2,     2,     2,     2,
       1,     1,     1,     1,     5,     2,     1,     1,     1,     5,
       1,     2,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     1,     1,     1,     1,     2,
       1,     2,     3,     1,     1,     2,     1,     1,     1,     1,
       1,     2,     1,     1,     1,     2,     3,     2,     1,     1,
       1,     5,     1,     3,     1,     4,     1,     6,     4,     1,
       1,     4,     2,     2,     3,     0,     2,     2,     2,     2,
       2,     2,     2,     1,     3,     1,     3,     1,     2,     3,
       9,     1,     1,     1,     1,     1,     1,     2,     3,     1,
       2,     3,     2,     2,     3,     4,     1,     3,     3,     4,
       3,     1,     1,     1,     3,     2,     1,     3,     3,     1,
       1,     1,     0,     4,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     2,     2,     1,     1,
       1,     1,     1,     2,     2
  };

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
  /* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
     First, the terminals, then, starting at \a yyntokens_, nonterminals.  */
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
  "IDENT_INFO", "LINE_AND_FILE_INFO", "NOT", "POS", "NEG", "$accept",
  "specification", "definition_list", "definition", "sharp_declaratives",
  "module", "type_dcl", "struct_type", "struct_member_list",
  "struct_member", "type_spec", "simple_type_spec", "scoped_name",
  "base_type_spec", "object_type", "any_type", "template_type_spec",
  "constr_type_spec", "declarators", "declarator", "simple_declarator",
  "complex_declarator", "array_declarator", "fixed_array_size_list",
  "fixed_array_size", "floating_pt_type", "integer_type", "signed_int",
  "signed_long_int", "signed_short_int", "unsigned_int",
  "unsigned_long_int", "unsigned_short_int", "char_type", "boolean_type",
  "octet_type", "enum_type", "enumerator_list", "enumerator",
  "string_type", "sequence_type", "interface", "interface_dcl",
  "forward_dcl", "interface_header", "interface_body", "export",
  "inheritance_spec", "scoped_name_list", "scoped_name_str",
  "res_scoped_name", "union_type", "switch_type_spec", "switch_body",
  "case", "case_label_list", "case_label", "element_spec", "attr_dcl",
  "simple_declarators", "op_dcl", "op_dcl_cont", "op_attribute",
  "op_type_spec", "parameter_dcls", "param_dcl_list", "param_dcl",
  "param_attribute", "raises_expr", "context_expr", "string_literal_list",
  "param_type_spec", "positive_int_const", "expr", "literal", "const_dcl",
  "except_dcl", 0
  };
#endif

#if YYDEBUG
  /* YYRHS -- A `-1'-separated list of the rules' RHS.  */
  const IDLParser::rhs_number_type
  IDLParser::yyrhs_[] =
  {
        77,     0,    -1,    78,    -1,    79,    -1,    79,    78,    -1,
      82,    46,    -1,   151,    46,    -1,   152,    46,    -1,   117,
      46,    -1,    81,    46,    -1,    80,    -1,    70,    -1,    71,
      -1,    72,    -1,    27,    10,    47,    78,    48,    -1,    38,
      46,    -1,    83,    -1,   127,    -1,   112,    -1,    36,    10,
      47,    84,    48,    -1,    85,    -1,    85,    84,    -1,    86,
      94,    46,    -1,    87,    -1,    93,    -1,    89,    -1,    92,
      -1,    88,    -1,   125,    -1,   101,    -1,   102,    -1,   109,
      -1,   110,    -1,   111,    -1,    91,    -1,    90,    -1,    42,
      -1,    12,    -1,   116,    -1,   115,    -1,    83,    -1,   127,
      -1,   112,    -1,    95,    -1,    95,    50,    94,    -1,    96,
      -1,    97,    -1,    10,    -1,    98,    -1,    10,    99,    -1,
     100,    -1,   100,    99,    -1,    58,   148,    59,    -1,    22,
      -1,    19,    -1,    26,    19,    -1,   103,    -1,   106,    -1,
     104,    -1,   105,    -1,    26,    -1,    26,    26,    -1,    34,
      -1,   107,    -1,   108,    -1,    39,    26,    -1,    39,    26,
      26,    -1,    39,    34,    -1,    15,    -1,    11,    -1,    28,
      -1,    20,    10,    47,   113,    48,    -1,   114,    -1,   114,
      50,   113,    -1,    10,    -1,    35,    56,   148,    57,    -1,
      35,    -1,    33,    56,    87,    50,   148,    57,    -1,    33,
      56,    87,    57,    -1,   118,    -1,   119,    -1,   120,    47,
     121,    48,    -1,    25,    10,    -1,    25,    10,    -1,    25,
      10,   123,    -1,    -1,   122,   121,    -1,    82,    46,    -1,
     151,    46,    -1,   152,    46,    -1,   134,    46,    -1,   136,
      46,    -1,    49,   124,    -1,   125,    -1,   125,    50,   124,
      -1,    10,    -1,    10,    43,   125,    -1,   126,    -1,    43,
      10,    -1,    43,    10,   126,    -1,    40,    10,    37,    54,
     128,    55,    47,   129,    48,    -1,   102,    -1,   109,    -1,
     110,    -1,   112,    -1,    88,    -1,   130,    -1,   130,   129,
      -1,   131,   133,    46,    -1,   132,    -1,   132,   131,    -1,
      14,   149,    49,    -1,    18,    49,    -1,    86,    95,    -1,
      13,   147,   135,    -1,    32,    13,   147,   135,    -1,    96,
      -1,    96,    50,   135,    -1,   139,    10,   137,    -1,   138,
     139,    10,   137,    -1,   140,   144,   145,    -1,    29,    -1,
     147,    -1,    41,    -1,    54,   141,    55,    -1,    54,    55,
      -1,   142,    -1,   142,    50,   141,    -1,   143,   147,    96,
      -1,    23,    -1,    30,    -1,    24,    -1,    -1,    31,    54,
     124,    55,    -1,    -1,    17,    54,   146,    55,    -1,     8,
      -1,     8,    50,   146,    -1,    89,    -1,   115,    -1,    88,
      -1,   149,    -1,   125,    -1,   150,    -1,    54,   149,    55,
      -1,   149,    60,   149,    -1,   149,    61,   149,    -1,   149,
      62,   149,    -1,   149,    44,   149,    -1,   149,    45,   149,
      -1,   149,    52,   149,    -1,   149,    53,   149,    -1,   149,
      63,   149,    -1,   149,    64,   149,    -1,   149,    65,   149,
      -1,    53,   149,    -1,    52,   149,    -1,    66,   149,    -1,
       3,    -1,     5,    -1,     8,    -1,     9,    -1,     7,    -1,
      16,    46,    -1,    21,    46,    -1
  };

  /* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
     YYRHS.  */
  const unsigned short int
  IDLParser::yyprhs_[] =
  {
         0,     0,     3,     5,     7,    10,    13,    16,    19,    22,
      25,    27,    29,    31,    33,    39,    42,    44,    46,    48,
      54,    56,    59,    63,    65,    67,    69,    71,    73,    75,
      77,    79,    81,    83,    85,    87,    89,    91,    93,    95,
      97,    99,   101,   103,   105,   109,   111,   113,   115,   117,
     120,   122,   125,   129,   131,   133,   136,   138,   140,   142,
     144,   146,   149,   151,   153,   155,   158,   162,   165,   167,
     169,   171,   177,   179,   183,   185,   190,   192,   199,   204,
     206,   208,   213,   216,   219,   223,   224,   227,   230,   233,
     236,   239,   242,   245,   247,   251,   253,   257,   259,   262,
     266,   276,   278,   280,   282,   284,   286,   288,   291,   295,
     297,   300,   304,   307,   310,   314,   319,   321,   325,   329,
     334,   338,   340,   342,   344,   348,   351,   353,   357,   361,
     363,   365,   367,   368,   373,   374,   379,   381,   385,   387,
     389,   391,   393,   395,   397,   401,   405,   409,   413,   417,
     421,   425,   429,   433,   437,   441,   444,   447,   450,   452,
     454,   456,   458,   460,   463
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned short int
  IDLParser::yyrline_[] =
  {
         0,   187,   187,   196,   200,   211,   212,   213,   214,   215,
     216,   219,   221,   223,   227,   247,   249,   250,   251,   254,
     267,   269,   284,   325,   326,   333,   334,   335,   338,   349,
     350,   351,   352,   353,   354,   355,   357,   363,   368,   369,
     372,   373,   374,   377,   382,   389,   390,   392,   399,   402,
     410,   415,   420,   426,   428,   430,   434,   435,   438,   439,
     441,   443,   446,   450,   451,   453,   455,   458,   461,   464,
     467,   472,   489,   495,   498,   504,   509,   515,   521,   530,
     531,   534,   562,   569,   572,   577,   578,   587,   588,   589,
     590,   595,   598,   604,   608,   614,   619,   626,   629,   636,
     646,   705,   706,   707,   708,   712,   715,   720,   726,   733,
     735,   742,   765,   772,   783,   786,   791,   795,   800,   803,
     807,   810,   814,   815,   819,   821,   825,   827,   830,   834,
     836,   838,   843,   844,   849,   850,   854,   857,   862,   867,
     872,   886,   897,   903,   905,   907,   919,   932,   944,   957,
     970,   992,  1006,  1020,  1034,  1048,  1059,  1070,  1092,  1097,
    1102,  1108,  1114,  1137,  1145
  };

  // Print the state stack on the debug stream.
  void
  IDLParser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (state_stack_type::const_iterator i = yystate_stack_.begin ();
	 i != yystate_stack_.end (); ++i)
      *yycdebug_ << ' ' << *i;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  IDLParser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    /* Print the symbols being reduced, and their result.  */
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
	       << " (line " << yylno << "):" << std::endl;
    /* The symbols being reduced.  */
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
		       yyrhs_[yyprhs_[yyrule] + yyi],
		       &(yysemantic_stack_[(yynrhs) - (yyi + 1)]),
		       &(yylocation_stack_[(yynrhs) - (yyi + 1)]));
  }
#endif // YYDEBUG

  /* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
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
    if ((unsigned int) t <= yyuser_token_number_max_)
      return translate_table[t];
    else
      return yyundef_token_;
  }

  const int IDLParser::yyeof_ = 0;
  const int IDLParser::yylast_ = 398;
  const int IDLParser::yynnts_ = 77;
  const int IDLParser::yyempty_ = -2;
  const int IDLParser::yyfinal_ = 35;
  const int IDLParser::yyterror_ = 1;
  const int IDLParser::yyerrcode_ = 256;
  const int IDLParser::yyntokens_ = 76;

  const unsigned int IDLParser::yyuser_token_number_max_ = 306;
  const IDLParser::token_number_type IDLParser::yyundef_token_ = 2;


} // eprosima

/* Line 1136 of lalr1.cc  */
#line 2630 "IDLParser.cc"


/* Line 1138 of lalr1.cc  */
#line 1156 "idl.y"


// directly include the nonterm defs here
//@NONTERMTYPES@



void eprosima::IDLParser::error(const IDLParser::location_type& l,
                             const std::string& m)
 {
     TCprovider.error(l, m);
 }
