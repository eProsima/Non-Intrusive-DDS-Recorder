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
    {
    delete((yysemantic_stack_[(1) - (1)].mp_TypeCodeVec));
    }
    break;

  case 3:

/* Line 690 of lalr1.cc  */
#line 194 "idl.y"
    {
	(yyval.mp_TypeCodeVec) = (yysemantic_stack_[(1) - (1)].mp_TypeCodeVec);
	}
    break;

  case 4:

/* Line 690 of lalr1.cc  */
#line 198 "idl.y"
    {
	for(TypeCodeVec::iterator it = (yysemantic_stack_[(2) - (2)].mp_TypeCodeVec)->begin();it!=(yysemantic_stack_[(2) - (2)].mp_TypeCodeVec)->end();++it)
	{
	(yysemantic_stack_[(2) - (1)].mp_TypeCodeVec)->push_back(*it);
	}
	delete((yysemantic_stack_[(2) - (2)].mp_TypeCodeVec));
	(yyval.mp_TypeCodeVec) = (yysemantic_stack_[(2) - (1)].mp_TypeCodeVec);
	}
    break;

  case 5:

/* Line 690 of lalr1.cc  */
#line 208 "idl.y"
    {(yyval.mp_TypeCodeVec) = (yysemantic_stack_[(2) - (1)].mp_TypeCodeVec);for(std::vector<TypeCode*>::iterator it = (yysemantic_stack_[(2) - (1)].mp_TypeCodeVec)->begin();it!=(yysemantic_stack_[(2) - (1)].mp_TypeCodeVec)->end();++it)
    {
    	TCprovider.addTypeCode(*it);
    	//printf("Added\n");
    }}
    break;

  case 6:

/* Line 690 of lalr1.cc  */
#line 213 "idl.y"
    {(yyval.mp_TypeCodeVec) = (yysemantic_stack_[(2) - (1)].mp_TypeCodeVec);for(std::vector<TypeCode*>::iterator it = (yysemantic_stack_[(2) - (1)].mp_TypeCodeVec)->begin();it!=(yysemantic_stack_[(2) - (1)].mp_TypeCodeVec)->end();++it)
    {
    	TCprovider.addTypeCode(*it);
    }}
    break;

  case 7:

/* Line 690 of lalr1.cc  */
#line 217 "idl.y"
    {(yyval.mp_TypeCodeVec) = (yysemantic_stack_[(2) - (1)].mp_TypeCodeVec);for(std::vector<TypeCode*>::iterator it = (yysemantic_stack_[(2) - (1)].mp_TypeCodeVec)->begin();it!=(yysemantic_stack_[(2) - (1)].mp_TypeCodeVec)->end();++it)
    {
    	TCprovider.addTypeCode(*it);
    }}
    break;

  case 8:

/* Line 690 of lalr1.cc  */
#line 222 "idl.y"
    {(yyval.mp_TypeCodeVec) = (yysemantic_stack_[(2) - (1)].mp_TypeCodeVec);
    }
    break;

  case 9:

/* Line 690 of lalr1.cc  */
#line 225 "idl.y"
    {
    (yyval.mp_TypeCodeVec) = (yysemantic_stack_[(2) - (1)].mp_TypeCodeVec);
    }
    break;

  case 10:

/* Line 690 of lalr1.cc  */
#line 229 "idl.y"
    {
    (yyval.mp_TypeCodeVec) = (yysemantic_stack_[(1) - (1)].mp_TypeCodeVec);
    for(std::vector<TypeCode*>::iterator it = (yysemantic_stack_[(1) - (1)].mp_TypeCodeVec)->begin();it!=(yysemantic_stack_[(1) - (1)].mp_TypeCodeVec)->end();++it)
    {
    	TCprovider.addTypeCode(*it);
    }}
    break;

  case 11:

/* Line 690 of lalr1.cc  */
#line 238 "idl.y"
    {(yyval.mp_TypeCodeVec) = new TypeCodeVec();}
    break;

  case 12:

/* Line 690 of lalr1.cc  */
#line 240 "idl.y"
    {(yyval.mp_TypeCodeVec) = new TypeCodeVec();}
    break;

  case 13:

/* Line 690 of lalr1.cc  */
#line 242 "idl.y"
    {(yyval.mp_TypeCodeVec) = new TypeCodeVec();}
    break;

  case 14:

/* Line 690 of lalr1.cc  */
#line 245 "idl.y"
    {TCprovider.addNamespace(*(yysemantic_stack_[(2) - (2)].stringVal)); }
    break;

  case 15:

/* Line 690 of lalr1.cc  */
#line 246 "idl.y"
    {
	(yyval.mp_TypeCodeVec) = (yysemantic_stack_[(6) - (5)].mp_TypeCodeVec);
	delete((yysemantic_stack_[(6) - (2)].stringVal));
	TCprovider.removeNamespace();
	}
    break;

  case 16:

/* Line 690 of lalr1.cc  */
#line 254 "idl.y"
    {std::cout << "Warning: \"typedef\" token not allowed" << std::endl;}
    break;

  case 17:

/* Line 690 of lalr1.cc  */
#line 255 "idl.y"
    {
    	(yyval.mp_TypeCodeVec) = (yysemantic_stack_[(3) - (3)].mp_TypeCodeVec);
    }
    break;

  case 21:

/* Line 690 of lalr1.cc  */
#line 264 "idl.y"
    {(yyval.mp_TypeCodeVec) = new TypeCodeVec();
	delete((yysemantic_stack_[(2) - (1)].mp_TypeCode));
	for(DeclaratorVec::iterator it = (yysemantic_stack_[(2) - (2)].mp_DeclaratorVec)->begin();it!=(yysemantic_stack_[(2) - (2)].mp_DeclaratorVec)->end();++it)
		delete(*it);
	delete((yysemantic_stack_[(2) - (2)].mp_DeclaratorVec));
	}
    break;

  case 22:

/* Line 690 of lalr1.cc  */
#line 273 "idl.y"
    {
	if((yysemantic_stack_[(5) - (4)].mp_MemberVec) == NULL)
	{
		(yyval.mp_TypeCodeVec) = new TypeCodeVec();
		(yyval.mp_TypeCodeVec)->push_back(new PrimitiveTypeCode(TypeCode::KIND_NULL));
	}
	else
	{
	StructTypeCode* sTC = new StructTypeCode();
	sTC->setName(*(yysemantic_stack_[(5) - (2)].stringVal));
	delete((yysemantic_stack_[(5) - (2)].stringVal));
	for(MemberVec::iterator it= (yysemantic_stack_[(5) - (4)].mp_MemberVec)->begin();it!=(yysemantic_stack_[(5) - (4)].mp_MemberVec)->end();++it)
	{
		if(!sTC->addMember((StructMember*)(*it)))
		{
			std::cout << "Warning: StructMember with repeated name, second instance not added " << std::endl; //TODO MOfidicar para que devuelva error
			TCprovider.m_errorCode = UserTypeCodeProvider::REPEATED_STRUCT_MEMBER_ERROR;
			delete(*it);
		}
	}
	(yyval.mp_TypeCodeVec) = new TypeCodeVec();
	(yyval.mp_TypeCodeVec)->push_back((TypeCode*)sTC);
	//printf("Structure defined\n");
	}
	}
    break;

  case 23:

/* Line 690 of lalr1.cc  */
#line 301 "idl.y"
    {(yyval.mp_MemberVec) = (yysemantic_stack_[(1) - (1)].mp_MemberVec);}
    break;

  case 24:

/* Line 690 of lalr1.cc  */
#line 303 "idl.y"
    {
	if((yysemantic_stack_[(2) - (1)].mp_MemberVec) ==NULL || (yysemantic_stack_[(2) - (2)].mp_MemberVec) == NULL)
	{
		(yyval.mp_MemberVec) = NULL;
	}
	else
	{
	for(std::vector<Member*>::iterator it = (yysemantic_stack_[(2) - (2)].mp_MemberVec)->begin();it!=(yysemantic_stack_[(2) - (2)].mp_MemberVec)->end();++it)
	{
		(yysemantic_stack_[(2) - (1)].mp_MemberVec)->push_back(*it);
	}
	delete((yysemantic_stack_[(2) - (2)].mp_MemberVec));
	(yyval.mp_MemberVec) = (yysemantic_stack_[(2) - (1)].mp_MemberVec);
	}
	}
    break;

  case 25:

/* Line 690 of lalr1.cc  */
#line 320 "idl.y"
    {
	if((yysemantic_stack_[(3) - (1)].mp_TypeCode)->getKind() == TypeCode::KIND_NULL)
	{
		delete((yysemantic_stack_[(3) - (2)].mp_DeclaratorVec));
		delete((yysemantic_stack_[(3) - (1)].mp_TypeCode));
		(yyval.mp_MemberVec) = NULL;
	}
	else
	{
	MemberVec* MV = new MemberVec();
	bool first = true;
	for(DeclaratorVec::iterator it=(yysemantic_stack_[(3) - (2)].mp_DeclaratorVec)->begin();it!=(yysemantic_stack_[(3) - (2)].mp_DeclaratorVec)->end();++it)
	{
		//std::cout << "Declarator: " << (*it)->first<< std::endl;
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
	for(std::vector<Declarator*>::iterator it = (yysemantic_stack_[(3) - (2)].mp_DeclaratorVec)->begin();it!=(yysemantic_stack_[(3) - (2)].mp_DeclaratorVec)->end();++it)
		delete(*it);
	delete((yysemantic_stack_[(3) - (2)].mp_DeclaratorVec));
	(yyval.mp_MemberVec) = MV;
	}
	}
    break;

  case 27:

/* Line 690 of lalr1.cc  */
#line 365 "idl.y"
    {
    (yyval.mp_TypeCode) = *((yysemantic_stack_[(1) - (1)].mp_TypeCodeVec)->begin());
    delete((yysemantic_stack_[(1) - (1)].mp_TypeCodeVec));
    }
    break;

  case 31:

/* Line 690 of lalr1.cc  */
#line 377 "idl.y"
    {
    TypeCode* pTC = TCprovider.findTypeCodebyName(*(yysemantic_stack_[(1) - (1)].mp_string));
    if(pTC->getKind()==TypeCode::KIND_NULL)
    {
    	std::cout << "Warning, TypeCode with name: " << *(yysemantic_stack_[(1) - (1)].mp_string) << " not found."<< std::endl;
    	TCprovider.m_errorCode = UserTypeCodeProvider::TYPECODE_NOTFOUND;
    }
    delete((yysemantic_stack_[(1) - (1)].mp_string));
    (yyval.mp_TypeCode) = pTC;
    }
    break;

  case 39:

/* Line 690 of lalr1.cc  */
#line 401 "idl.y"
    {
	std::cout << "Warning: \"Object\" token not allowed" << std::endl;
	(yyval.mp_TypeCode) = new PrimitiveTypeCode(TypeCode::KIND_NULL);
	}
    break;

  case 40:

/* Line 690 of lalr1.cc  */
#line 407 "idl.y"
    {std::cout << "Warning: \"any\" token not allowed" << std::endl;
	(yyval.mp_TypeCode) = new PrimitiveTypeCode(TypeCode::KIND_NULL);}
    break;

  case 46:

/* Line 690 of lalr1.cc  */
#line 421 "idl.y"
    {
	(yyval.mp_DeclaratorVec) = new DeclaratorVec();
	(yyval.mp_DeclaratorVec)->push_back((yysemantic_stack_[(1) - (1)].mp_Declarator));
	}
    break;

  case 47:

/* Line 690 of lalr1.cc  */
#line 426 "idl.y"
    {
	(yysemantic_stack_[(3) - (3)].mp_DeclaratorVec)->insert((yysemantic_stack_[(3) - (3)].mp_DeclaratorVec)->begin(),(yysemantic_stack_[(3) - (1)].mp_Declarator)); 
	(yyval.mp_DeclaratorVec) = (yysemantic_stack_[(3) - (3)].mp_DeclaratorVec);
	}
    break;

  case 50:

/* Line 690 of lalr1.cc  */
#line 436 "idl.y"
    {
	(yyval.mp_Declarator) = new Declarator();
	(yyval.mp_Declarator)->first = *(yysemantic_stack_[(1) - (1)].stringVal);
	delete((yysemantic_stack_[(1) - (1)].stringVal));
	}
    break;

  case 52:

/* Line 690 of lalr1.cc  */
#line 446 "idl.y"
    {
	(yysemantic_stack_[(2) - (2)].mp_Declarator)->first = *(yysemantic_stack_[(2) - (1)].stringVal);
	delete((yysemantic_stack_[(2) - (1)].stringVal));
	(yyval.mp_Declarator) = (yysemantic_stack_[(2) - (2)].mp_Declarator);
	}
    break;

  case 53:

/* Line 690 of lalr1.cc  */
#line 454 "idl.y"
    {
	(yyval.mp_Declarator) = new Declarator();
	(yyval.mp_Declarator)->second.push_back((yysemantic_stack_[(1) - (1)].m_uint32_t));
	}
    break;

  case 54:

/* Line 690 of lalr1.cc  */
#line 459 "idl.y"
    {
	(yysemantic_stack_[(2) - (2)].mp_Declarator)->second.push_back((yysemantic_stack_[(2) - (1)].m_uint32_t)); 
	(yyval.mp_Declarator) = (yysemantic_stack_[(2) - (2)].mp_Declarator);}
    break;

  case 55:

/* Line 690 of lalr1.cc  */
#line 464 "idl.y"
    {(yyval.m_uint32_t) = (yysemantic_stack_[(3) - (2)].m_uint32_t);}
    break;

  case 56:

/* Line 690 of lalr1.cc  */
#line 470 "idl.y"
    {(yyval.mp_TypeCode) = new PrimitiveTypeCode(TypeCode::KIND_FLOAT);}
    break;

  case 57:

/* Line 690 of lalr1.cc  */
#line 472 "idl.y"
    {(yyval.mp_TypeCode) = new PrimitiveTypeCode(TypeCode::KIND_DOUBLE);}
    break;

  case 58:

/* Line 690 of lalr1.cc  */
#line 474 "idl.y"
    {(yyval.mp_TypeCode) = new PrimitiveTypeCode(TypeCode::KIND_LONGDOUBLE);}
    break;

  case 63:

/* Line 690 of lalr1.cc  */
#line 485 "idl.y"
    {(yyval.mp_TypeCode) = new PrimitiveTypeCode(TypeCode::KIND_LONG);}
    break;

  case 64:

/* Line 690 of lalr1.cc  */
#line 487 "idl.y"
    {(yyval.mp_TypeCode) = new PrimitiveTypeCode(TypeCode::KIND_LONGLONG);}
    break;

  case 65:

/* Line 690 of lalr1.cc  */
#line 490 "idl.y"
    {(yyval.mp_TypeCode) = new PrimitiveTypeCode(TypeCode::KIND_SHORT);}
    break;

  case 68:

/* Line 690 of lalr1.cc  */
#line 497 "idl.y"
    {(yyval.mp_TypeCode) = new PrimitiveTypeCode(TypeCode::KIND_ULONG);}
    break;

  case 69:

/* Line 690 of lalr1.cc  */
#line 499 "idl.y"
    {(yyval.mp_TypeCode) = new PrimitiveTypeCode(TypeCode::KIND_ULONGLONG);}
    break;

  case 70:

/* Line 690 of lalr1.cc  */
#line 502 "idl.y"
    {(yyval.mp_TypeCode) = new PrimitiveTypeCode(TypeCode::KIND_USHORT);}
    break;

  case 71:

/* Line 690 of lalr1.cc  */
#line 505 "idl.y"
    {(yyval.mp_TypeCode) = new PrimitiveTypeCode(TypeCode::KIND_CHAR);}
    break;

  case 72:

/* Line 690 of lalr1.cc  */
#line 508 "idl.y"
    {(yyval.mp_TypeCode) = new PrimitiveTypeCode(TypeCode::KIND_BOOLEAN);}
    break;

  case 73:

/* Line 690 of lalr1.cc  */
#line 511 "idl.y"
    {(yyval.mp_TypeCode) = new PrimitiveTypeCode(TypeCode::KIND_OCTET);}
    break;

  case 74:

/* Line 690 of lalr1.cc  */
#line 516 "idl.y"
    {
	EnumTypeCode* enTC= new EnumTypeCode();
	enTC->setName(*(yysemantic_stack_[(5) - (2)].stringVal));
	delete((yysemantic_stack_[(5) - (2)].stringVal));
	uint32_t ord = 0;
	for(StringVec::iterator it=(yysemantic_stack_[(5) - (4)].mp_StringVec)->begin();it!=(yysemantic_stack_[(5) - (4)].mp_StringVec)->end();++it)
	{
		EnumMember* eMember = new EnumMember(*it,ord);
		if(!enTC->addMember(eMember))
		{
			std::cout << "Warning: EnumMember with repeated name, second instance not added " << std::endl; //TODO MOfidicar para que devuelva error
			delete(eMember);
		}
		++ord;
	}
	delete((yysemantic_stack_[(5) - (4)].mp_StringVec));
	(yyval.mp_TypeCodeVec) = new TypeCodeVec();
	(yyval.mp_TypeCodeVec)->push_back((TypeCode*) enTC);
	}
    break;

  case 75:

/* Line 690 of lalr1.cc  */
#line 537 "idl.y"
    {
	(yyval.mp_StringVec) = new StringVec();
	(yyval.mp_StringVec)->push_back(*(yysemantic_stack_[(1) - (1)].mp_string));
	delete((yysemantic_stack_[(1) - (1)].mp_string));
	}
    break;

  case 76:

/* Line 690 of lalr1.cc  */
#line 543 "idl.y"
    {(yysemantic_stack_[(3) - (3)].mp_StringVec)->insert((yysemantic_stack_[(3) - (3)].mp_StringVec)->begin(),*(yysemantic_stack_[(3) - (1)].mp_string)); (yyval.mp_StringVec) = (yysemantic_stack_[(3) - (3)].mp_StringVec);delete((yysemantic_stack_[(3) - (1)].mp_string));}
    break;

  case 77:

/* Line 690 of lalr1.cc  */
#line 546 "idl.y"
    {(yyval.mp_string) = new std::string(*(yysemantic_stack_[(1) - (1)].stringVal));
	delete((yysemantic_stack_[(1) - (1)].stringVal));}
    break;

  case 78:

/* Line 690 of lalr1.cc  */
#line 552 "idl.y"
    {
	StringTypeCode* pSTC = new StringTypeCode((yysemantic_stack_[(4) - (3)].m_uint32_t));
	(yyval.mp_TypeCode) = (TypeCode*)pSTC;
	}
    break;

  case 79:

/* Line 690 of lalr1.cc  */
#line 557 "idl.y"
    {StringTypeCode* pSTC = new StringTypeCode(255);
	(yyval.mp_TypeCode) = (TypeCode*)pSTC;}
    break;

  case 80:

/* Line 690 of lalr1.cc  */
#line 563 "idl.y"
    {
	SequenceTypeCode* sTC = new SequenceTypeCode((yysemantic_stack_[(6) - (5)].m_uint32_t));
	sTC->setContentTypeCode((yysemantic_stack_[(6) - (3)].mp_TypeCode));
	(yyval.mp_TypeCode) = (TypeCode*) sTC;
	}
    break;

  case 81:

/* Line 690 of lalr1.cc  */
#line 569 "idl.y"
    {
	SequenceTypeCode* sTC = new SequenceTypeCode(255);
	sTC->setContentTypeCode((yysemantic_stack_[(4) - (3)].mp_TypeCode));
	(yyval.mp_TypeCode) = (TypeCode*) sTC;
	}
    break;

  case 84:

/* Line 690 of lalr1.cc  */
#line 582 "idl.y"
    {
	std::vector<int> index_to_remove;
	for(TypeCodeVec::iterator it = (yysemantic_stack_[(4) - (3)].mp_TypeCodeVec)->begin();it!=(yysemantic_stack_[(4) - (3)].mp_TypeCodeVec)->end();++it)
	{
	if((*it)->getKind() == TypeCode::KIND_STRUCT || 
		(*it)->getKind() == TypeCode::KIND_UNION ||
		(*it)->getKind() == TypeCode::KIND_ENUM)
	{

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
	delete((yysemantic_stack_[(4) - (1)].mp_string));
	TCprovider.removeNamespace();
	}
    break;

  case 85:

/* Line 690 of lalr1.cc  */
#line 608 "idl.y"
    {
	delete((yysemantic_stack_[(2) - (2)].stringVal));
	(yyval.mp_TypeCodeVec) = new TypeCodeVec();
	}
    break;

  case 86:

/* Line 690 of lalr1.cc  */
#line 615 "idl.y"
    {
	TCprovider.addNamespace(*(yysemantic_stack_[(2) - (2)].stringVal));
	(yyval.mp_string) = new std::string(*(yysemantic_stack_[(2) - (2)].stringVal));
	delete((yysemantic_stack_[(2) - (2)].stringVal));
	}
    break;

  case 87:

/* Line 690 of lalr1.cc  */
#line 621 "idl.y"
    {
		TCprovider.addNamespace(*(yysemantic_stack_[(3) - (2)].stringVal));
	(yyval.mp_string) = new std::string(*(yysemantic_stack_[(3) - (2)].stringVal));
	delete((yysemantic_stack_[(3) - (2)].stringVal));
 	}
    break;

  case 88:

/* Line 690 of lalr1.cc  */
#line 628 "idl.y"
    {(yyval.mp_TypeCodeVec) = new TypeCodeVec();}
    break;

  case 89:

/* Line 690 of lalr1.cc  */
#line 630 "idl.y"
    {
	for(TypeCodeVec::iterator it = (yysemantic_stack_[(2) - (2)].mp_TypeCodeVec)->begin();it!=(yysemantic_stack_[(2) - (2)].mp_TypeCodeVec)->end();++it)
		(yysemantic_stack_[(2) - (1)].mp_TypeCodeVec)->push_back(*it);
	(yyval.mp_TypeCodeVec) = (yysemantic_stack_[(2) - (1)].mp_TypeCodeVec);
	delete((yysemantic_stack_[(2) - (2)].mp_TypeCodeVec));
	}
    break;

  case 90:

/* Line 690 of lalr1.cc  */
#line 639 "idl.y"
    {(yyval.mp_TypeCodeVec) = (yysemantic_stack_[(2) - (1)].mp_TypeCodeVec);for(std::vector<TypeCode*>::iterator it = (yysemantic_stack_[(2) - (1)].mp_TypeCodeVec)->begin();it!=(yysemantic_stack_[(2) - (1)].mp_TypeCodeVec)->end();++it)
    {
    	TCprovider.addTypeCode(*it);
    	//printf("Added\n");
    }}
    break;

  case 91:

/* Line 690 of lalr1.cc  */
#line 645 "idl.y"
    {(yyval.mp_TypeCodeVec) = (yysemantic_stack_[(2) - (1)].mp_TypeCodeVec);for(std::vector<TypeCode*>::iterator it = (yysemantic_stack_[(2) - (1)].mp_TypeCodeVec)->begin();it!=(yysemantic_stack_[(2) - (1)].mp_TypeCodeVec)->end();++it)
    {
    	TCprovider.addTypeCode(*it);
    	//printf("Added\n");
    }}
    break;

  case 92:

/* Line 690 of lalr1.cc  */
#line 651 "idl.y"
    {(yyval.mp_TypeCodeVec) = (yysemantic_stack_[(2) - (1)].mp_TypeCodeVec);for(std::vector<TypeCode*>::iterator it = (yysemantic_stack_[(2) - (1)].mp_TypeCodeVec)->begin();it!=(yysemantic_stack_[(2) - (1)].mp_TypeCodeVec)->end();++it)
    {
    	TCprovider.addTypeCode(*it);
    	//printf("Added\n");
    }}
    break;

  case 93:

/* Line 690 of lalr1.cc  */
#line 657 "idl.y"
    {
    delete((yysemantic_stack_[(2) - (1)].mp_TypeCode));
    (yyval.mp_TypeCodeVec) = new TypeCodeVec();
    }
    break;

  case 95:

/* Line 690 of lalr1.cc  */
#line 665 "idl.y"
    {(yyval.mp_string) = new std::string("");
	delete((yysemantic_stack_[(2) - (2)].mp_string));}
    break;

  case 96:

/* Line 690 of lalr1.cc  */
#line 671 "idl.y"
    {
	(yyval.mp_string) = new std::string(*(yysemantic_stack_[(1) - (1)].mp_string));
	delete((yysemantic_stack_[(1) - (1)].mp_string));}
    break;

  case 97:

/* Line 690 of lalr1.cc  */
#line 675 "idl.y"
    {(yyval.mp_string) = (yysemantic_stack_[(3) - (3)].mp_string);
	delete((yysemantic_stack_[(3) - (1)].mp_string));
	}
    break;

  case 98:

/* Line 690 of lalr1.cc  */
#line 681 "idl.y"
    {
	(yyval.mp_string) = new std::string(*(yysemantic_stack_[(1) - (1)].stringVal));
	delete((yysemantic_stack_[(1) - (1)].stringVal));
	}
    break;

  case 99:

/* Line 690 of lalr1.cc  */
#line 686 "idl.y"
    {
	(yysemantic_stack_[(3) - (3)].mp_string)->insert(0,"::");
	(yysemantic_stack_[(3) - (3)].mp_string)->insert(0,*(yysemantic_stack_[(3) - (1)].stringVal));
	delete((yysemantic_stack_[(3) - (1)].stringVal));
	(yyval.mp_string) = (yysemantic_stack_[(3) - (3)].mp_string);
	}
    break;

  case 101:

/* Line 690 of lalr1.cc  */
#line 696 "idl.y"
    {
	std::string* aux_str = new std::string("::");
	aux_str->append(*(yysemantic_stack_[(2) - (2)].stringVal));
	delete((yysemantic_stack_[(2) - (2)].stringVal));
	(yyval.mp_string) = aux_str;
	}
    break;

  case 102:

/* Line 690 of lalr1.cc  */
#line 703 "idl.y"
    {
	(yysemantic_stack_[(3) - (3)].mp_string)->insert(0,*(yysemantic_stack_[(3) - (2)].stringVal));
	(yysemantic_stack_[(3) - (3)].mp_string)->insert(0,"::");
	delete((yysemantic_stack_[(3) - (2)].stringVal));
	(yyval.mp_string) = (yysemantic_stack_[(3) - (3)].mp_string);
	}
    break;

  case 103:

/* Line 690 of lalr1.cc  */
#line 713 "idl.y"
    {
	UnionTypeCode* uTC = new UnionTypeCode();
	uTC->setName(*(yysemantic_stack_[(9) - (2)].stringVal));
	delete((yysemantic_stack_[(9) - (2)].stringVal));
	TypeCode* discTC = TCprovider.copyTypeCode((yysemantic_stack_[(9) - (5)].mp_TypeCode),true);
	uTC->setDiscriminatorTypeCode(discTC);
	UnionMember* uM_boolWithDefault = NULL;
	bool isTrue = false;
	for(MemberVec::iterator it = (yysemantic_stack_[(9) - (8)].mp_MemberVec)->begin();it!=(yysemantic_stack_[(9) - (8)].mp_MemberVec)->end();++it)
	{
		UnionMember* uM = (UnionMember*)(*it);
		std::vector<int32_t> labels = uM->getLabels();
		bool change = false;
		bool boolDefaultFound = false;
		bool defaultIndex = false;
		for(std::vector<int32_t>::iterator it = labels.begin();it!=labels.end();++it)
		{
			if((yysemantic_stack_[(9) - (5)].mp_TypeCode)->getKind() == TypeCode::KIND_CHAR && (*it) == -1000)
			{
				(*it) = 254;
				change = true;
				defaultIndex = true;
			}
			if((yysemantic_stack_[(9) - (5)].mp_TypeCode)->getKind() == TypeCode::KIND_ENUM && (*it) == -1000)
			{
				(*it) = 0;
				change = true;
				defaultIndex = true;
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
	delete((yysemantic_stack_[(9) - (8)].mp_MemberVec));
	(yyval.mp_TypeCodeVec) = new TypeCodeVec();
	(yyval.mp_TypeCodeVec)->push_back((TypeCode*) uTC);
	}
    break;

  case 107:

/* Line 690 of lalr1.cc  */
#line 801 "idl.y"
    {
    (yyval.mp_TypeCode) = *((yysemantic_stack_[(1) - (1)].mp_TypeCodeVec)->begin());
    }
    break;

  case 109:

/* Line 690 of lalr1.cc  */
#line 808 "idl.y"
    {
	(yyval.mp_MemberVec) = new MemberVec();
	(yyval.mp_MemberVec)->push_back((yysemantic_stack_[(1) - (1)].mp_Member));
	}
    break;

  case 110:

/* Line 690 of lalr1.cc  */
#line 813 "idl.y"
    {
	(yysemantic_stack_[(2) - (2)].mp_MemberVec)->insert((yysemantic_stack_[(2) - (2)].mp_MemberVec)->begin(),(yysemantic_stack_[(2) - (1)].mp_Member));
	(yyval.mp_MemberVec) = (yysemantic_stack_[(2) - (2)].mp_MemberVec);
	}
    break;

  case 111:

/* Line 690 of lalr1.cc  */
#line 819 "idl.y"
    {
	((UnionMember*)((yysemantic_stack_[(3) - (2)].mp_Member)))->setLabels((yysemantic_stack_[(3) - (1)].mp_Declarator)->second);
	(yyval.mp_Member) = (yysemantic_stack_[(3) - (2)].mp_Member);
	}
    break;

  case 112:

/* Line 690 of lalr1.cc  */
#line 826 "idl.y"
    {(yyval.mp_Declarator) = (yysemantic_stack_[(1) - (1)].mp_Declarator);}
    break;

  case 113:

/* Line 690 of lalr1.cc  */
#line 828 "idl.y"
    {
	(yysemantic_stack_[(2) - (1)].mp_Declarator)->second.push_back(*((yysemantic_stack_[(2) - (2)].mp_Declarator)->second.begin()));
	(yyval.mp_Declarator) = (yysemantic_stack_[(2) - (1)].mp_Declarator);
	delete((yysemantic_stack_[(2) - (2)].mp_Declarator));}
    break;

  case 114:

/* Line 690 of lalr1.cc  */
#line 835 "idl.y"
    {
	Declarator * dCL = new Declarator();
	if((yysemantic_stack_[(3) - (2)].mp_TypeLiteral)->type == NUMBER_TYPE)
	{
		dCL->second.push_back((yysemantic_stack_[(3) - (2)].mp_TypeLiteral)->num);
	}
	else if((yysemantic_stack_[(3) - (2)].mp_TypeLiteral)->type == BOOL_TYPE)
	{
		if((yysemantic_stack_[(3) - (2)].mp_TypeLiteral)->boolean == true)
			dCL->second.push_back(1);
		else	
			dCL->second.push_back(0);
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
	(yyval.mp_Declarator) = dCL;
	}
    break;

  case 115:

/* Line 690 of lalr1.cc  */
#line 862 "idl.y"
    {
	Declarator * dCL = new Declarator();
	dCL->second.push_back(-1000);
	(yyval.mp_Declarator) = dCL;
	}
    break;

  case 116:

/* Line 690 of lalr1.cc  */
#line 869 "idl.y"
    {
	UnionMember* uM = new UnionMember();
	uM->setName((yysemantic_stack_[(2) - (2)].mp_Declarator)->first);
	delete((yysemantic_stack_[(2) - (2)].mp_Declarator));
	uM->setTypeCode((yysemantic_stack_[(2) - (1)].mp_TypeCode));
	(yyval.mp_Member) = (Member*) uM;
	}
    break;

  case 117:

/* Line 690 of lalr1.cc  */
#line 880 "idl.y"
    {std::cout << "Warning: \"attribute\" token not allowed" << std::endl;
	(yyval.mp_TypeCode) = new PrimitiveTypeCode(TypeCode::KIND_NULL);}
    break;

  case 118:

/* Line 690 of lalr1.cc  */
#line 883 "idl.y"
    {std::cout << "Warning: \"readonly attribute\" token not allowed" << std::endl;
	(yyval.mp_TypeCode) = new PrimitiveTypeCode(TypeCode::KIND_NULL);}
    break;

  case 119:

/* Line 690 of lalr1.cc  */
#line 888 "idl.y"
    {
    (yyval.mp_TypeCode) = NULL;
    }
    break;

  case 120:

/* Line 690 of lalr1.cc  */
#line 892 "idl.y"
    {(yyval.mp_TypeCode) = NULL;}
    break;

  case 121:

/* Line 690 of lalr1.cc  */
#line 897 "idl.y"
    {(yyval.mp_TypeCodeVec) = new TypeCodeVec();
	delete((yysemantic_stack_[(3) - (2)].stringVal));}
    break;

  case 122:

/* Line 690 of lalr1.cc  */
#line 900 "idl.y"
    {(yyval.mp_TypeCodeVec) = new TypeCodeVec();
	delete((yysemantic_stack_[(4) - (3)].stringVal));}
    break;

  case 123:

/* Line 690 of lalr1.cc  */
#line 904 "idl.y"
    {(yyval.m_uint32_t) = 0;}
    break;

  case 124:

/* Line 690 of lalr1.cc  */
#line 907 "idl.y"
    {(yyval.m_uint32_t) = 0;}
    break;

  case 126:

/* Line 690 of lalr1.cc  */
#line 912 "idl.y"
    {(yyval.m_uint32_t) = 0;}
    break;

  case 127:

/* Line 690 of lalr1.cc  */
#line 916 "idl.y"
    {(yyval.m_uint32_t) = 0;}
    break;

  case 128:

/* Line 690 of lalr1.cc  */
#line 918 "idl.y"
    {(yyval.m_uint32_t) = 0;}
    break;

  case 129:

/* Line 690 of lalr1.cc  */
#line 922 "idl.y"
    {(yyval.m_uint32_t) = 0;}
    break;

  case 130:

/* Line 690 of lalr1.cc  */
#line 924 "idl.y"
    {(yyval.m_uint32_t) = 0;}
    break;

  case 131:

/* Line 690 of lalr1.cc  */
#line 927 "idl.y"
    {(yyval.m_uint32_t) = 0;}
    break;

  case 132:

/* Line 690 of lalr1.cc  */
#line 931 "idl.y"
    {(yyval.m_uint32_t) = 0;}
    break;

  case 133:

/* Line 690 of lalr1.cc  */
#line 933 "idl.y"
    {(yyval.m_uint32_t) = 0;}
    break;

  case 134:

/* Line 690 of lalr1.cc  */
#line 935 "idl.y"
    {(yyval.m_uint32_t) = 0;}
    break;

  case 135:

/* Line 690 of lalr1.cc  */
#line 939 "idl.y"
    {(yyval.m_uint32_t) = 0;}
    break;

  case 136:

/* Line 690 of lalr1.cc  */
#line 941 "idl.y"
    {(yyval.m_uint32_t) = 0;}
    break;

  case 137:

/* Line 690 of lalr1.cc  */
#line 945 "idl.y"
    {(yyval.m_uint32_t) = 0;}
    break;

  case 138:

/* Line 690 of lalr1.cc  */
#line 947 "idl.y"
    {(yyval.m_uint32_t) = 0;}
    break;

  case 139:

/* Line 690 of lalr1.cc  */
#line 951 "idl.y"
    {(yyval.m_uint32_t) = 0;
	delete((yysemantic_stack_[(1) - (1)].stringVal));}
    break;

  case 140:

/* Line 690 of lalr1.cc  */
#line 954 "idl.y"
    {(yyval.m_uint32_t) = 0;
	delete((yysemantic_stack_[(3) - (1)].stringVal));}
    break;

  case 141:

/* Line 690 of lalr1.cc  */
#line 959 "idl.y"
    {
    delete((yysemantic_stack_[(1) - (1)].mp_TypeCode));
    (yyval.m_uint32_t) = 0;
    }
    break;

  case 142:

/* Line 690 of lalr1.cc  */
#line 964 "idl.y"
    {
    delete((yysemantic_stack_[(1) - (1)].mp_TypeCode));
    (yyval.m_uint32_t) = 0;
    }
    break;

  case 143:

/* Line 690 of lalr1.cc  */
#line 969 "idl.y"
    {
    delete((yysemantic_stack_[(1) - (1)].mp_TypeCode));
    (yyval.m_uint32_t) = 0;
    }
    break;

  case 144:

/* Line 690 of lalr1.cc  */
#line 983 "idl.y"
    {
	if((yysemantic_stack_[(1) - (1)].mp_TypeLiteral)->type == NUMBER_TYPE)
		(yyval.m_uint32_t) = (uint32_t)(yysemantic_stack_[(1) - (1)].mp_TypeLiteral)->num;
	else
		(yyval.m_uint32_t) = 0;
	delete((yysemantic_stack_[(1) - (1)].mp_TypeLiteral));
	}
    break;

  case 145:

/* Line 690 of lalr1.cc  */
#line 994 "idl.y"
    {(yyval.mp_TypeLiteral) = new TypeLiteral();
	(yyval.mp_TypeLiteral)->type = SCOPED_TYPE;
	(yyval.mp_TypeLiteral)->str = *(yysemantic_stack_[(1) - (1)].mp_string);
	delete((yysemantic_stack_[(1) - (1)].mp_string));
	}
    break;

  case 146:

/* Line 690 of lalr1.cc  */
#line 1000 "idl.y"
    {(yyval.mp_TypeLiteral) = (yysemantic_stack_[(1) - (1)].mp_TypeLiteral);}
    break;

  case 147:

/* Line 690 of lalr1.cc  */
#line 1002 "idl.y"
    {(yyval.mp_TypeLiteral) = (yysemantic_stack_[(3) - (2)].mp_TypeLiteral);}
    break;

  case 148:

/* Line 690 of lalr1.cc  */
#line 1004 "idl.y"
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

  case 149:

/* Line 690 of lalr1.cc  */
#line 1016 "idl.y"
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

  case 150:

/* Line 690 of lalr1.cc  */
#line 1029 "idl.y"
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

  case 151:

/* Line 690 of lalr1.cc  */
#line 1041 "idl.y"
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

  case 152:

/* Line 690 of lalr1.cc  */
#line 1054 "idl.y"
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

  case 153:

/* Line 690 of lalr1.cc  */
#line 1067 "idl.y"
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

  case 154:

/* Line 690 of lalr1.cc  */
#line 1089 "idl.y"
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

  case 155:

/* Line 690 of lalr1.cc  */
#line 1103 "idl.y"
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

  case 156:

/* Line 690 of lalr1.cc  */
#line 1117 "idl.y"
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

  case 157:

/* Line 690 of lalr1.cc  */
#line 1131 "idl.y"
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

  case 158:

/* Line 690 of lalr1.cc  */
#line 1145 "idl.y"
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

  case 159:

/* Line 690 of lalr1.cc  */
#line 1156 "idl.y"
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

  case 160:

/* Line 690 of lalr1.cc  */
#line 1167 "idl.y"
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

  case 161:

/* Line 690 of lalr1.cc  */
#line 1189 "idl.y"
    {(yyval.mp_TypeLiteral) = new TypeLiteral();
	(yyval.mp_TypeLiteral)->type = NUMBER_TYPE;
	(yyval.mp_TypeLiteral)->num = (yysemantic_stack_[(1) - (1)].integerVal);
	}
    break;

  case 162:

/* Line 690 of lalr1.cc  */
#line 1194 "idl.y"
    {(yyval.mp_TypeLiteral) = new TypeLiteral();
	(yyval.mp_TypeLiteral)->type = NUMBER_TYPE;
	(yyval.mp_TypeLiteral)->num = (yysemantic_stack_[(1) - (1)].doubleVal);
	}
    break;

  case 163:

/* Line 690 of lalr1.cc  */
#line 1199 "idl.y"
    {(yyval.mp_TypeLiteral) = new TypeLiteral();
	(yyval.mp_TypeLiteral)->type = STRING_TYPE;
	(yyval.mp_TypeLiteral)->str = *(yysemantic_stack_[(1) - (1)].stringVal);
	delete((yysemantic_stack_[(1) - (1)].stringVal));
	}
    break;

  case 164:

/* Line 690 of lalr1.cc  */
#line 1205 "idl.y"
    {(yyval.mp_TypeLiteral) = new TypeLiteral();
	(yyval.mp_TypeLiteral)->type = STRING_TYPE;
	(yyval.mp_TypeLiteral)->str = *(yysemantic_stack_[(1) - (1)].stringVal);
	delete((yysemantic_stack_[(1) - (1)].stringVal));
	}
    break;

  case 165:

/* Line 690 of lalr1.cc  */
#line 1211 "idl.y"
    {(yyval.mp_TypeLiteral) = new TypeLiteral();
	(yyval.mp_TypeLiteral)->type = BOOL_TYPE;
	(yyval.mp_TypeLiteral)->boolean = (yysemantic_stack_[(1) - (1)].integerVal);
	}
    break;

  case 166:

/* Line 690 of lalr1.cc  */
#line 1234 "idl.y"
    {std::cout << "Warning: \"const\" token not allowed" << std::endl;
	 PrimitiveTypeCode* auxptrTC = new PrimitiveTypeCode(TypeCode::KIND_NULL);
	 (yyval.mp_TypeCodeVec) = new TypeCodeVec();
	 (yyval.mp_TypeCodeVec)->push_back(auxptrTC);
	}
    break;

  case 167:

/* Line 690 of lalr1.cc  */
#line 1242 "idl.y"
    {std::cout << "Warning: \"exception\" token not allowed" << std::endl;
	PrimitiveTypeCode* auxptrTC = new PrimitiveTypeCode(TypeCode::KIND_NULL);
	 (yyval.mp_TypeCodeVec) = new TypeCodeVec();
	 (yyval.mp_TypeCodeVec)->push_back(auxptrTC);
	}
    break;



/* Line 690 of lalr1.cc  */
#line 1960 "IDLParser.cc"
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
  const short int IDLParser::yypact_ninf_ = -162;
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

  /* YYDEFACT[S] -- default reduction number in state S.  Performed when
     YYTABLE doesn't specify something else to do.  Zero means the
     default is an error.  */
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

  /* YYPGOTO[NTERM-NUM].  */
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

  /* YYDEFGOTO[NTERM-NUM].  */
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

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If YYTABLE_NINF_, syntax error.  */
  const signed char IDLParser::yytable_ninf_ = -87;
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

  /* YYCHECK.  */
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

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
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

  /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
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
  "except_dcl", 0
  };
#endif

#if YYDEBUG
  /* YYRHS -- A `-1'-separated list of the rules' RHS.  */
  const IDLParser::rhs_number_type
  IDLParser::yyrhs_[] =
  {
        77,     0,    -1,    78,    -1,    79,    -1,    79,    78,    -1,
      83,    46,    -1,   154,    46,    -1,   155,    46,    -1,   120,
      46,    -1,    81,    46,    -1,    80,    -1,    70,    -1,    71,
      -1,    72,    -1,    -1,    27,    10,    82,    47,    78,    48,
      -1,    -1,    38,    84,    85,    -1,    86,    -1,   130,    -1,
     115,    -1,    89,    97,    -1,    36,    10,    47,    87,    48,
      -1,    88,    -1,    88,    87,    -1,    89,    97,    46,    -1,
      90,    -1,    96,    -1,    92,    -1,    95,    -1,    91,    -1,
     128,    -1,   104,    -1,   105,    -1,   112,    -1,   113,    -1,
     114,    -1,    94,    -1,    93,    -1,    42,    -1,    12,    -1,
     119,    -1,   118,    -1,    86,    -1,   130,    -1,   115,    -1,
      98,    -1,    98,    50,    97,    -1,    99,    -1,   100,    -1,
      10,    -1,   101,    -1,    10,   102,    -1,   103,    -1,   103,
     102,    -1,    58,   151,    59,    -1,    22,    -1,    19,    -1,
      26,    19,    -1,   106,    -1,   109,    -1,   107,    -1,   108,
      -1,    26,    -1,    26,    26,    -1,    34,    -1,   110,    -1,
     111,    -1,    39,    26,    -1,    39,    26,    26,    -1,    39,
      34,    -1,    15,    -1,    11,    -1,    28,    -1,    20,    10,
      47,   116,    48,    -1,   117,    -1,   117,    50,   116,    -1,
      10,    -1,    35,    56,   151,    57,    -1,    35,    -1,    33,
      56,    90,    50,   151,    57,    -1,    33,    56,    90,    57,
      -1,   121,    -1,   122,    -1,   123,    47,   124,    48,    -1,
      25,    10,    -1,    25,    10,    -1,    25,    10,   126,    -1,
      -1,   125,   124,    -1,    83,    46,    -1,   154,    46,    -1,
     155,    46,    -1,   137,    46,    -1,   139,    46,    -1,    49,
     127,    -1,   128,    -1,   128,    50,   127,    -1,    10,    -1,
      10,    43,   128,    -1,   129,    -1,    43,    10,    -1,    43,
      10,   129,    -1,    40,    10,    37,    54,   131,    55,    47,
     132,    48,    -1,   105,    -1,   112,    -1,   113,    -1,   115,
      -1,    91,    -1,   133,    -1,   133,   132,    -1,   134,   136,
      46,    -1,   135,    -1,   135,   134,    -1,    14,   152,    49,
      -1,    18,    49,    -1,    89,    98,    -1,    13,   150,   138,
      -1,    32,    13,   150,   138,    -1,    99,    -1,    99,    50,
     138,    -1,   142,    10,   140,    -1,   141,   142,    10,   140,
      -1,   143,   147,   148,    -1,    29,    -1,   150,    -1,    41,
      -1,    54,   144,    55,    -1,    54,    55,    -1,   145,    -1,
     145,    50,   144,    -1,   146,   150,    99,    -1,    23,    -1,
      30,    -1,    24,    -1,    -1,    31,    54,   127,    55,    -1,
      -1,    17,    54,   149,    55,    -1,     8,    -1,     8,    50,
     149,    -1,    92,    -1,   118,    -1,    91,    -1,   152,    -1,
     128,    -1,   153,    -1,    54,   152,    55,    -1,   152,    60,
     152,    -1,   152,    61,   152,    -1,   152,    62,   152,    -1,
     152,    44,   152,    -1,   152,    45,   152,    -1,   152,    52,
     152,    -1,   152,    53,   152,    -1,   152,    63,   152,    -1,
     152,    64,   152,    -1,   152,    65,   152,    -1,    53,   152,
      -1,    52,   152,    -1,    66,   152,    -1,     3,    -1,     5,
      -1,     8,    -1,     9,    -1,     7,    -1,    16,    46,    -1,
      21,    46,    -1
  };

  /* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
     YYRHS.  */
  const unsigned short int
  IDLParser::yyprhs_[] =
  {
         0,     0,     3,     5,     7,    10,    13,    16,    19,    22,
      25,    27,    29,    31,    33,    34,    41,    42,    46,    48,
      50,    52,    55,    61,    63,    66,    70,    72,    74,    76,
      78,    80,    82,    84,    86,    88,    90,    92,    94,    96,
      98,   100,   102,   104,   106,   108,   110,   112,   116,   118,
     120,   122,   124,   127,   129,   132,   136,   138,   140,   143,
     145,   147,   149,   151,   153,   156,   158,   160,   162,   165,
     169,   172,   174,   176,   178,   184,   186,   190,   192,   197,
     199,   206,   211,   213,   215,   220,   223,   226,   230,   231,
     234,   237,   240,   243,   246,   249,   252,   254,   258,   260,
     264,   266,   269,   273,   283,   285,   287,   289,   291,   293,
     295,   298,   302,   304,   307,   311,   314,   317,   321,   326,
     328,   332,   336,   341,   345,   347,   349,   351,   355,   358,
     360,   364,   368,   370,   372,   374,   375,   380,   381,   386,
     388,   392,   394,   396,   398,   400,   402,   404,   408,   412,
     416,   420,   424,   428,   432,   436,   440,   444,   448,   451,
     454,   457,   459,   461,   463,   465,   467,   470
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned short int
  IDLParser::yyrline_[] =
  {
         0,   187,   187,   193,   197,   208,   213,   217,   221,   224,
     228,   237,   239,   241,   245,   245,   254,   254,   258,   259,
     260,   263,   272,   300,   302,   319,   363,   364,   371,   372,
     373,   376,   392,   393,   394,   395,   396,   397,   398,   400,
     406,   411,   412,   415,   416,   417,   420,   425,   432,   433,
     435,   442,   445,   453,   458,   463,   469,   471,   473,   477,
     478,   481,   482,   484,   486,   489,   493,   494,   496,   498,
     501,   504,   507,   510,   515,   536,   542,   545,   551,   556,
     562,   568,   577,   578,   581,   607,   614,   620,   628,   629,
     638,   644,   650,   656,   661,   664,   670,   674,   680,   685,
     692,   695,   702,   712,   797,   798,   799,   800,   804,   807,
     812,   818,   825,   827,   834,   861,   868,   879,   882,   887,
     891,   896,   899,   903,   906,   910,   911,   915,   917,   921,
     923,   926,   930,   932,   934,   939,   940,   945,   946,   950,
     953,   958,   963,   968,   982,   993,   999,  1001,  1003,  1015,
    1028,  1040,  1053,  1066,  1088,  1102,  1116,  1130,  1144,  1155,
    1166,  1188,  1193,  1198,  1204,  1210,  1233,  1241
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
  const int IDLParser::yylast_ = 404;
  const int IDLParser::yynnts_ = 80;
  const int IDLParser::yyempty_ = -2;
  const int IDLParser::yyfinal_ = 35;
  const int IDLParser::yyterror_ = 1;
  const int IDLParser::yyerrcode_ = 256;
  const int IDLParser::yyntokens_ = 76;

  const unsigned int IDLParser::yyuser_token_number_max_ = 306;
  const IDLParser::token_number_type IDLParser::yyundef_token_ = 2;


} // eprosima

/* Line 1136 of lalr1.cc  */
#line 2761 "IDLParser.cc"


/* Line 1138 of lalr1.cc  */
#line 1252 "idl.y"


// directly include the nonterm defs here
//@NONTERMTYPES@



void eprosima::IDLParser::error(const IDLParser::location_type& l,
                             const std::string& m)
 {
     TCprovider.error(l, m);
 }
