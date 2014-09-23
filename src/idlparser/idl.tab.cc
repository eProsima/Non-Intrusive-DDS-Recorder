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
#line 41 "idl.tab.cc"


#include "idl.tab.hh"

/* User implementation prologue.  */


/* Line 299 of lalr1.cc  */
#line 50 "idl.tab.cc"

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
#line 136 "idl.tab.cc"

  /// Build a parser object.
  IDLParser::IDLParser ()
#if YYDEBUG
     :yydebug_ (false),
      yycdebug_ (&std::cerr)
#endif
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
	yychar = yylex (&yylval);
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
#line 164 "idl.y"
    {(yyval.mp_TypeCodeVec) = (yysemantic_stack_[(1) - (1)].mp_TypeCodeVec); }
    break;

  case 3:

/* Line 690 of lalr1.cc  */
#line 168 "idl.y"
    {
	(yyval.mp_TypeCodeVec) = (yysemantic_stack_[(1) - (1)].mp_TypeCodeVec);
	}
    break;

  case 4:

/* Line 690 of lalr1.cc  */
#line 172 "idl.y"
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
#line 182 "idl.y"
    {(yyval.mp_TypeCodeVec) = (yysemantic_stack_[(2) - (1)].mp_TypeCodeVec);}
    break;

  case 6:

/* Line 690 of lalr1.cc  */
#line 183 "idl.y"
    {(yyval.mp_TypeCodeVec) = (yysemantic_stack_[(2) - (1)].mp_TypeCodeVec);}
    break;

  case 7:

/* Line 690 of lalr1.cc  */
#line 184 "idl.y"
    {(yyval.mp_TypeCodeVec) = (yysemantic_stack_[(2) - (1)].mp_TypeCodeVec);}
    break;

  case 8:

/* Line 690 of lalr1.cc  */
#line 185 "idl.y"
    {(yyval.mp_TypeCodeVec) = (yysemantic_stack_[(2) - (1)].mp_TypeCodeVec);}
    break;

  case 9:

/* Line 690 of lalr1.cc  */
#line 186 "idl.y"
    {(yyval.mp_TypeCodeVec) = (yysemantic_stack_[(2) - (1)].mp_TypeCodeVec);}
    break;

  case 10:

/* Line 690 of lalr1.cc  */
#line 187 "idl.y"
    {(yyval.mp_TypeCodeVec) = (yysemantic_stack_[(1) - (1)].mp_TypeCodeVec);}
    break;

  case 11:

/* Line 690 of lalr1.cc  */
#line 191 "idl.y"
    {(yyval.mp_TypeCodeVec) = new TypeCodeVec();}
    break;

  case 12:

/* Line 690 of lalr1.cc  */
#line 193 "idl.y"
    {(yyval.mp_TypeCodeVec) = new TypeCodeVec();}
    break;

  case 13:

/* Line 690 of lalr1.cc  */
#line 195 "idl.y"
    {(yyval.mp_TypeCodeVec) = new TypeCodeVec();}
    break;

  case 14:

/* Line 690 of lalr1.cc  */
#line 199 "idl.y"
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
#line 219 "idl.y"
    {std::cout << "Warning: \"typedef\" token not allowed" << std::endl;}
    break;

  case 19:

/* Line 690 of lalr1.cc  */
#line 226 "idl.y"
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
#line 239 "idl.y"
    {(yyval.mp_MemberVec) = (yysemantic_stack_[(1) - (1)].mp_MemberVec);}
    break;

  case 21:

/* Line 690 of lalr1.cc  */
#line 241 "idl.y"
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
#line 256 "idl.y"
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
#line 309 "idl.y"
    {
    (yyval.mp_TypeCode) = *((yysemantic_stack_[(1) - (1)].mp_TypeCodeVec)->begin());
    delete((yysemantic_stack_[(1) - (1)].mp_TypeCodeVec));
    }
    break;

  case 28:

/* Line 690 of lalr1.cc  */
#line 321 "idl.y"
    {
    TypeCode* pTC = findTypeCodebyName(*(yysemantic_stack_[(1) - (1)].mp_string));
    delete((yysemantic_stack_[(1) - (1)].mp_string));
    (yyval.mp_TypeCode) = pTC;
    }
    break;

  case 36:

/* Line 690 of lalr1.cc  */
#line 340 "idl.y"
    {
	std::cout << "Warning: \"Object\" token not allowed" << std::endl;
	(yyval.mp_TypeCode) = new PrimitiveTypeCode(TypeCode::KIND_NULL);
	}
    break;

  case 37:

/* Line 690 of lalr1.cc  */
#line 346 "idl.y"
    {std::cout << "Warning: \"any\" token not allowed" << std::endl;
	(yyval.mp_TypeCode) = new PrimitiveTypeCode(TypeCode::KIND_NULL);}
    break;

  case 43:

/* Line 690 of lalr1.cc  */
#line 360 "idl.y"
    {
	(yyval.mp_DeclaratorVec) = new DeclaratorVec();
	(yyval.mp_DeclaratorVec)->push_back((yysemantic_stack_[(1) - (1)].mp_Declarator));
	}
    break;

  case 44:

/* Line 690 of lalr1.cc  */
#line 365 "idl.y"
    {
	(yysemantic_stack_[(3) - (3)].mp_DeclaratorVec)->push_back((yysemantic_stack_[(3) - (1)].mp_Declarator)); 
	(yyval.mp_DeclaratorVec) = (yysemantic_stack_[(3) - (3)].mp_DeclaratorVec);
	}
    break;

  case 47:

/* Line 690 of lalr1.cc  */
#line 375 "idl.y"
    {
	(yyval.mp_Declarator) = new Declarator();
	(yyval.mp_Declarator)->first = *(yysemantic_stack_[(1) - (1)].stringVal);
	delete((yysemantic_stack_[(1) - (1)].stringVal));
	}
    break;

  case 49:

/* Line 690 of lalr1.cc  */
#line 385 "idl.y"
    {
	(yysemantic_stack_[(2) - (2)].mp_Declarator)->first = *(yysemantic_stack_[(2) - (1)].stringVal);
	delete((yysemantic_stack_[(2) - (1)].stringVal));
	(yyval.mp_Declarator) = (yysemantic_stack_[(2) - (2)].mp_Declarator);
	}
    break;

  case 50:

/* Line 690 of lalr1.cc  */
#line 393 "idl.y"
    {
	(yyval.mp_Declarator) = new Declarator();
	(yyval.mp_Declarator)->second.push_back((yysemantic_stack_[(1) - (1)].m_uint32_t));
	}
    break;

  case 51:

/* Line 690 of lalr1.cc  */
#line 398 "idl.y"
    {
	(yysemantic_stack_[(2) - (2)].mp_Declarator)->second.push_back((yysemantic_stack_[(2) - (1)].m_uint32_t)); 
	(yyval.mp_Declarator) = (yysemantic_stack_[(2) - (2)].mp_Declarator);}
    break;

  case 52:

/* Line 690 of lalr1.cc  */
#line 403 "idl.y"
    {(yyval.m_uint32_t) = (yysemantic_stack_[(3) - (2)].m_uint32_t);}
    break;

  case 53:

/* Line 690 of lalr1.cc  */
#line 409 "idl.y"
    {(yyval.mp_TypeCode) = new PrimitiveTypeCode(TypeCode::KIND_FLOAT);}
    break;

  case 54:

/* Line 690 of lalr1.cc  */
#line 411 "idl.y"
    {(yyval.mp_TypeCode) = new PrimitiveTypeCode(TypeCode::KIND_DOUBLE);}
    break;

  case 55:

/* Line 690 of lalr1.cc  */
#line 413 "idl.y"
    {(yyval.mp_TypeCode) = new PrimitiveTypeCode(TypeCode::KIND_LONGDOUBLE);}
    break;

  case 60:

/* Line 690 of lalr1.cc  */
#line 424 "idl.y"
    {(yyval.mp_TypeCode) = new PrimitiveTypeCode(TypeCode::KIND_LONG);}
    break;

  case 61:

/* Line 690 of lalr1.cc  */
#line 426 "idl.y"
    {(yyval.mp_TypeCode) = new PrimitiveTypeCode(TypeCode::KIND_LONGLONG);}
    break;

  case 62:

/* Line 690 of lalr1.cc  */
#line 429 "idl.y"
    {(yyval.mp_TypeCode) = new PrimitiveTypeCode(TypeCode::KIND_SHORT);}
    break;

  case 65:

/* Line 690 of lalr1.cc  */
#line 436 "idl.y"
    {(yyval.mp_TypeCode) = new PrimitiveTypeCode(TypeCode::KIND_ULONG);}
    break;

  case 66:

/* Line 690 of lalr1.cc  */
#line 438 "idl.y"
    {(yyval.mp_TypeCode) = new PrimitiveTypeCode(TypeCode::KIND_ULONGLONG);}
    break;

  case 67:

/* Line 690 of lalr1.cc  */
#line 441 "idl.y"
    {(yyval.mp_TypeCode) = new PrimitiveTypeCode(TypeCode::KIND_USHORT);}
    break;

  case 68:

/* Line 690 of lalr1.cc  */
#line 444 "idl.y"
    {(yyval.mp_TypeCode) = new PrimitiveTypeCode(TypeCode::KIND_CHAR);}
    break;

  case 69:

/* Line 690 of lalr1.cc  */
#line 447 "idl.y"
    {(yyval.mp_TypeCode) = new PrimitiveTypeCode(TypeCode::KIND_BOOLEAN);}
    break;

  case 70:

/* Line 690 of lalr1.cc  */
#line 450 "idl.y"
    {(yyval.mp_TypeCode) = new PrimitiveTypeCode(TypeCode::KIND_OCTET);}
    break;

  case 71:

/* Line 690 of lalr1.cc  */
#line 455 "idl.y"
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
#line 472 "idl.y"
    {
	(yyval.mp_StringVec) = new StringVec();
	(yyval.mp_StringVec)->push_back(*(yysemantic_stack_[(1) - (1)].mp_string));
	delete((yysemantic_stack_[(1) - (1)].mp_string));
	}
    break;

  case 73:

/* Line 690 of lalr1.cc  */
#line 478 "idl.y"
    {(yysemantic_stack_[(3) - (3)].mp_StringVec)->push_back(*(yysemantic_stack_[(3) - (1)].mp_string)); (yyval.mp_StringVec) = (yysemantic_stack_[(3) - (3)].mp_StringVec);delete((yysemantic_stack_[(3) - (1)].mp_string));}
    break;

  case 74:

/* Line 690 of lalr1.cc  */
#line 481 "idl.y"
    {(yyval.mp_string) = new std::string(*(yysemantic_stack_[(1) - (1)].stringVal));
	delete((yysemantic_stack_[(1) - (1)].stringVal));}
    break;

  case 75:

/* Line 690 of lalr1.cc  */
#line 487 "idl.y"
    {
	StringTypeCode* pSTC = new StringTypeCode((yysemantic_stack_[(4) - (3)].m_uint32_t));
	(yyval.mp_TypeCode) = (TypeCode*)pSTC;
	}
    break;

  case 76:

/* Line 690 of lalr1.cc  */
#line 492 "idl.y"
    {StringTypeCode* pSTC = new StringTypeCode(255);
	(yyval.mp_TypeCode) = (TypeCode*)pSTC;}
    break;

  case 77:

/* Line 690 of lalr1.cc  */
#line 498 "idl.y"
    {
	SequenceTypeCode* sTC = new SequenceTypeCode((yysemantic_stack_[(6) - (5)].m_uint32_t));
	sTC->setContentTypeCode((yysemantic_stack_[(6) - (3)].mp_TypeCode));
	(yyval.mp_TypeCode) = (TypeCode*) sTC;
	}
    break;

  case 78:

/* Line 690 of lalr1.cc  */
#line 504 "idl.y"
    {
	SequenceTypeCode* sTC = new SequenceTypeCode(255);
	sTC->setContentTypeCode((yysemantic_stack_[(4) - (3)].mp_TypeCode));
	(yyval.mp_TypeCode) = (TypeCode*) sTC;
	}
    break;

  case 81:

/* Line 690 of lalr1.cc  */
#line 517 "idl.y"
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
#line 545 "idl.y"
    {
	delete((yysemantic_stack_[(2) - (2)].stringVal));
	(yyval.mp_TypeCodeVec) = new TypeCodeVec();
	}
    break;

  case 83:

/* Line 690 of lalr1.cc  */
#line 552 "idl.y"
    {(yyval.mp_string) = new std::string(*(yysemantic_stack_[(2) - (2)].stringVal));
	delete((yysemantic_stack_[(2) - (2)].stringVal));}
    break;

  case 84:

/* Line 690 of lalr1.cc  */
#line 555 "idl.y"
    {(yyval.mp_string) = new std::string(*(yysemantic_stack_[(3) - (2)].stringVal));
	delete((yysemantic_stack_[(3) - (2)].stringVal));}
    break;

  case 85:

/* Line 690 of lalr1.cc  */
#line 559 "idl.y"
    {(yyval.mp_TypeCodeVec) = new TypeCodeVec();}
    break;

  case 86:

/* Line 690 of lalr1.cc  */
#line 561 "idl.y"
    {
	for(TypeCodeVec::iterator it = (yysemantic_stack_[(2) - (2)].mp_TypeCodeVec)->begin();it!=(yysemantic_stack_[(2) - (2)].mp_TypeCodeVec)->end();++it)
		(yysemantic_stack_[(2) - (1)].mp_TypeCodeVec)->push_back(*it);
	(yyval.mp_TypeCodeVec) = (yysemantic_stack_[(2) - (1)].mp_TypeCodeVec);
	delete((yysemantic_stack_[(2) - (2)].mp_TypeCodeVec));
	}
    break;

  case 90:

/* Line 690 of lalr1.cc  */
#line 573 "idl.y"
    {
    delete((yysemantic_stack_[(2) - (1)].mp_TypeCode));
    (yyval.mp_TypeCodeVec) = new TypeCodeVec();
    }
    break;

  case 92:

/* Line 690 of lalr1.cc  */
#line 581 "idl.y"
    {(yyval.mp_string) = new std::string("");
	delete((yysemantic_stack_[(2) - (2)].mp_string));}
    break;

  case 93:

/* Line 690 of lalr1.cc  */
#line 587 "idl.y"
    {
	(yyval.mp_string) = new std::string(*(yysemantic_stack_[(1) - (1)].mp_string));
	delete((yysemantic_stack_[(1) - (1)].mp_string));}
    break;

  case 94:

/* Line 690 of lalr1.cc  */
#line 591 "idl.y"
    {(yyval.mp_string) = (yysemantic_stack_[(3) - (3)].mp_string);
	delete((yysemantic_stack_[(3) - (1)].mp_string));
	}
    break;

  case 95:

/* Line 690 of lalr1.cc  */
#line 597 "idl.y"
    {
	(yyval.mp_string) = new std::string(*(yysemantic_stack_[(1) - (1)].stringVal));
	delete((yysemantic_stack_[(1) - (1)].stringVal));
	}
    break;

  case 96:

/* Line 690 of lalr1.cc  */
#line 602 "idl.y"
    {
	(yysemantic_stack_[(3) - (3)].mp_string)->insert(0,"::");
	(yysemantic_stack_[(3) - (3)].mp_string)->insert(0,*(yysemantic_stack_[(3) - (1)].stringVal));
	delete((yysemantic_stack_[(3) - (1)].stringVal));
	(yyval.mp_string) = (yysemantic_stack_[(3) - (3)].mp_string);
	}
    break;

  case 98:

/* Line 690 of lalr1.cc  */
#line 612 "idl.y"
    {
	std::string* aux_str = new std::string("::");
	aux_str->append(*(yysemantic_stack_[(2) - (2)].stringVal));
	delete((yysemantic_stack_[(2) - (2)].stringVal));
	(yyval.mp_string) = aux_str;
	}
    break;

  case 99:

/* Line 690 of lalr1.cc  */
#line 619 "idl.y"
    {
	(yysemantic_stack_[(3) - (3)].mp_string)->insert(0,*(yysemantic_stack_[(3) - (2)].stringVal));
	(yysemantic_stack_[(3) - (3)].mp_string)->insert(0,"::");
	delete((yysemantic_stack_[(3) - (2)].stringVal));
	(yyval.mp_string) = (yysemantic_stack_[(3) - (3)].mp_string);
	}
    break;

  case 100:

/* Line 690 of lalr1.cc  */
#line 629 "idl.y"
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
#line 691 "idl.y"
    {
    (yyval.mp_TypeCode) = * (yysemantic_stack_[(1) - (1)].mp_TypeCodeVec)->begin();
    }
    break;

  case 106:

/* Line 690 of lalr1.cc  */
#line 698 "idl.y"
    {
	(yyval.mp_MemberVec) = new MemberVec();
	(yyval.mp_MemberVec)->push_back((yysemantic_stack_[(1) - (1)].mp_Member));
	}
    break;

  case 107:

/* Line 690 of lalr1.cc  */
#line 703 "idl.y"
    {
	(yysemantic_stack_[(2) - (2)].mp_MemberVec)->push_back((yysemantic_stack_[(2) - (1)].mp_Member)); 
	(yyval.mp_MemberVec) = (yysemantic_stack_[(2) - (2)].mp_MemberVec);
	}
    break;

  case 108:

/* Line 690 of lalr1.cc  */
#line 709 "idl.y"
    {
	((UnionMember*)((yysemantic_stack_[(3) - (2)].mp_Member)))->setLabels((yysemantic_stack_[(3) - (1)].mp_Declarator)->second);
	(yyval.mp_Member) = (yysemantic_stack_[(3) - (2)].mp_Member);
	}
    break;

  case 109:

/* Line 690 of lalr1.cc  */
#line 716 "idl.y"
    {(yyval.mp_Declarator) = (yysemantic_stack_[(1) - (1)].mp_Declarator);}
    break;

  case 110:

/* Line 690 of lalr1.cc  */
#line 718 "idl.y"
    {
	(yysemantic_stack_[(2) - (2)].mp_Declarator)->second.push_back(*((yysemantic_stack_[(2) - (1)].mp_Declarator)->second.begin()));
	(yyval.mp_Declarator) = (yysemantic_stack_[(2) - (2)].mp_Declarator);
	delete((yysemantic_stack_[(2) - (1)].mp_Declarator));}
    break;

  case 111:

/* Line 690 of lalr1.cc  */
#line 725 "idl.y"
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
	dCL->second.push_back(findENUMvalue((yysemantic_stack_[(3) - (2)].mp_TypeLiteral)->str));
	}
	}
    break;

  case 112:

/* Line 690 of lalr1.cc  */
#line 748 "idl.y"
    {
	Declarator * dCL = new Declarator();
	dCL->second.push_back(-1000);
	(yyval.mp_Declarator) = dCL;
	}
    break;

  case 113:

/* Line 690 of lalr1.cc  */
#line 755 "idl.y"
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
#line 766 "idl.y"
    {std::cout << "Warning: \"attribute\" token not allowed" << std::endl;
	(yyval.mp_TypeCode) = new PrimitiveTypeCode(TypeCode::KIND_NULL);}
    break;

  case 115:

/* Line 690 of lalr1.cc  */
#line 769 "idl.y"
    {std::cout << "Warning: \"readonly attribute\" token not allowed" << std::endl;
	(yyval.mp_TypeCode) = new PrimitiveTypeCode(TypeCode::KIND_NULL);}
    break;

  case 116:

/* Line 690 of lalr1.cc  */
#line 774 "idl.y"
    {
    (yyval.mp_TypeCode) = NULL;
    }
    break;

  case 117:

/* Line 690 of lalr1.cc  */
#line 778 "idl.y"
    {(yyval.mp_TypeCode) = NULL;}
    break;

  case 118:

/* Line 690 of lalr1.cc  */
#line 783 "idl.y"
    {(yyval.mp_TypeCodeVec) = new TypeCodeVec();
	delete((yysemantic_stack_[(3) - (2)].stringVal));}
    break;

  case 119:

/* Line 690 of lalr1.cc  */
#line 786 "idl.y"
    {(yyval.mp_TypeCodeVec) = new TypeCodeVec();
	delete((yysemantic_stack_[(4) - (3)].stringVal));}
    break;

  case 120:

/* Line 690 of lalr1.cc  */
#line 790 "idl.y"
    {(yyval.m_uint32_t) = 0;}
    break;

  case 121:

/* Line 690 of lalr1.cc  */
#line 793 "idl.y"
    {(yyval.m_uint32_t) = 0;}
    break;

  case 123:

/* Line 690 of lalr1.cc  */
#line 798 "idl.y"
    {(yyval.m_uint32_t) = 0;}
    break;

  case 124:

/* Line 690 of lalr1.cc  */
#line 802 "idl.y"
    {(yyval.m_uint32_t) = 0;}
    break;

  case 125:

/* Line 690 of lalr1.cc  */
#line 804 "idl.y"
    {(yyval.m_uint32_t) = 0;}
    break;

  case 126:

/* Line 690 of lalr1.cc  */
#line 808 "idl.y"
    {(yyval.m_uint32_t) = 0;}
    break;

  case 127:

/* Line 690 of lalr1.cc  */
#line 810 "idl.y"
    {(yyval.m_uint32_t) = 0;}
    break;

  case 128:

/* Line 690 of lalr1.cc  */
#line 813 "idl.y"
    {(yyval.m_uint32_t) = 0;}
    break;

  case 129:

/* Line 690 of lalr1.cc  */
#line 817 "idl.y"
    {(yyval.m_uint32_t) = 0;}
    break;

  case 130:

/* Line 690 of lalr1.cc  */
#line 819 "idl.y"
    {(yyval.m_uint32_t) = 0;}
    break;

  case 131:

/* Line 690 of lalr1.cc  */
#line 821 "idl.y"
    {(yyval.m_uint32_t) = 0;}
    break;

  case 132:

/* Line 690 of lalr1.cc  */
#line 825 "idl.y"
    {(yyval.m_uint32_t) = 0;}
    break;

  case 133:

/* Line 690 of lalr1.cc  */
#line 827 "idl.y"
    {(yyval.m_uint32_t) = 0;}
    break;

  case 134:

/* Line 690 of lalr1.cc  */
#line 831 "idl.y"
    {(yyval.m_uint32_t) = 0;}
    break;

  case 135:

/* Line 690 of lalr1.cc  */
#line 833 "idl.y"
    {(yyval.m_uint32_t) = 0;}
    break;

  case 136:

/* Line 690 of lalr1.cc  */
#line 837 "idl.y"
    {(yyval.m_uint32_t) = 0;
	delete((yysemantic_stack_[(1) - (1)].stringVal));}
    break;

  case 137:

/* Line 690 of lalr1.cc  */
#line 840 "idl.y"
    {(yyval.m_uint32_t) = 0;
	delete((yysemantic_stack_[(3) - (1)].stringVal));}
    break;

  case 138:

/* Line 690 of lalr1.cc  */
#line 845 "idl.y"
    {
    delete((yysemantic_stack_[(1) - (1)].mp_TypeCode));
    (yyval.m_uint32_t) = 0;
    }
    break;

  case 139:

/* Line 690 of lalr1.cc  */
#line 850 "idl.y"
    {
    delete((yysemantic_stack_[(1) - (1)].mp_TypeCode));
    (yyval.m_uint32_t) = 0;
    }
    break;

  case 140:

/* Line 690 of lalr1.cc  */
#line 855 "idl.y"
    {
    delete((yysemantic_stack_[(1) - (1)].mp_TypeCode));
    (yyval.m_uint32_t) = 0;
    }
    break;

  case 141:

/* Line 690 of lalr1.cc  */
#line 869 "idl.y"
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
#line 880 "idl.y"
    {(yyval.mp_TypeLiteral) = new TypeLiteral();
	(yyval.mp_TypeLiteral)->type = SCOPED_TYPE;
	(yyval.mp_TypeLiteral)->str = *(yysemantic_stack_[(1) - (1)].mp_string);
	delete((yysemantic_stack_[(1) - (1)].mp_string));
	}
    break;

  case 143:

/* Line 690 of lalr1.cc  */
#line 886 "idl.y"
    {(yyval.mp_TypeLiteral) = (yysemantic_stack_[(1) - (1)].mp_TypeLiteral);}
    break;

  case 144:

/* Line 690 of lalr1.cc  */
#line 888 "idl.y"
    {(yyval.mp_TypeLiteral) = (yysemantic_stack_[(3) - (2)].mp_TypeLiteral);}
    break;

  case 145:

/* Line 690 of lalr1.cc  */
#line 890 "idl.y"
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
#line 902 "idl.y"
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
#line 915 "idl.y"
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
#line 927 "idl.y"
    {if((yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->type != NUMBER_TYPE || (yysemantic_stack_[(3) - (3)].mp_TypeLiteral)->type != NUMBER_TYPE)
	{
		(yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->type = NUMBER_TYPE;
		(yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->num = 0;
	}
	else
	{
		(yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->num = (yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->num << (yysemantic_stack_[(3) - (3)].mp_TypeLiteral)->num;
	}
	delete((yysemantic_stack_[(3) - (3)].mp_TypeLiteral));
	(yyval.mp_TypeLiteral) = (yysemantic_stack_[(3) - (1)].mp_TypeLiteral);
	}
    break;

  case 149:

/* Line 690 of lalr1.cc  */
#line 940 "idl.y"
    {if((yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->type != NUMBER_TYPE || (yysemantic_stack_[(3) - (3)].mp_TypeLiteral)->type != NUMBER_TYPE)
	{
		(yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->type = NUMBER_TYPE;
		(yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->num = 0;
	}
	else
	{
		(yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->num = (yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->num >> (yysemantic_stack_[(3) - (3)].mp_TypeLiteral)->num;
	}
	delete((yysemantic_stack_[(3) - (3)].mp_TypeLiteral));
	(yyval.mp_TypeLiteral) = (yysemantic_stack_[(3) - (1)].mp_TypeLiteral);
	}
    break;

  case 150:

/* Line 690 of lalr1.cc  */
#line 953 "idl.y"
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
#line 975 "idl.y"
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
#line 989 "idl.y"
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
#line 1003 "idl.y"
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
#line 1017 "idl.y"
    {
	if((yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->type != NUMBER_TYPE || (yysemantic_stack_[(3) - (3)].mp_TypeLiteral)->type != NUMBER_TYPE)
	{
		(yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->type = NUMBER_TYPE;
		(yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->num = 0;
	}
	else
	{
		(yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->num = (yysemantic_stack_[(3) - (1)].mp_TypeLiteral)->num % (yysemantic_stack_[(3) - (3)].mp_TypeLiteral)->num;
	}
	delete((yysemantic_stack_[(3) - (3)].mp_TypeLiteral));
	(yyval.mp_TypeLiteral) = (yysemantic_stack_[(3) - (1)].mp_TypeLiteral);
	}
    break;

  case 155:

/* Line 690 of lalr1.cc  */
#line 1031 "idl.y"
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
#line 1042 "idl.y"
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
#line 1053 "idl.y"
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
#line 1075 "idl.y"
    {(yyval.mp_TypeLiteral) = new TypeLiteral();
	(yyval.mp_TypeLiteral)->type = NUMBER_TYPE;
	(yyval.mp_TypeLiteral)->num = (yysemantic_stack_[(1) - (1)].integerVal);
	}
    break;

  case 159:

/* Line 690 of lalr1.cc  */
#line 1080 "idl.y"
    {(yyval.mp_TypeLiteral) = new TypeLiteral();
	(yyval.mp_TypeLiteral)->type = NUMBER_TYPE;
	(yyval.mp_TypeLiteral)->num = (yysemantic_stack_[(1) - (1)].doubleVal);
	}
    break;

  case 160:

/* Line 690 of lalr1.cc  */
#line 1085 "idl.y"
    {(yyval.mp_TypeLiteral) = new TypeLiteral();
	(yyval.mp_TypeLiteral)->type = STRING_TYPE;
	(yyval.mp_TypeLiteral)->str = *(yysemantic_stack_[(1) - (1)].stringVal);
	delete((yysemantic_stack_[(1) - (1)].stringVal));
	}
    break;

  case 161:

/* Line 690 of lalr1.cc  */
#line 1091 "idl.y"
    {(yyval.mp_TypeLiteral) = new TypeLiteral();
	(yyval.mp_TypeLiteral)->type = STRING_TYPE;
	(yyval.mp_TypeLiteral)->str = *(yysemantic_stack_[(1) - (1)].stringVal);
	delete((yysemantic_stack_[(1) - (1)].stringVal));
	}
    break;

  case 162:

/* Line 690 of lalr1.cc  */
#line 1097 "idl.y"
    {(yyval.mp_TypeLiteral) = new TypeLiteral();
	(yyval.mp_TypeLiteral)->type = BOOL_TYPE;
	(yyval.mp_TypeLiteral)->boolean = (yysemantic_stack_[(1) - (1)].integerVal);
	}
    break;

  case 163:

/* Line 690 of lalr1.cc  */
#line 1120 "idl.y"
    {std::cout << "Warning: \"const\" token not allowed" << std::endl;
	 PrimitiveTypeCode* auxptrTC = new PrimitiveTypeCode(TypeCode::KIND_NULL);
	 (yyval.mp_TypeCodeVec) = new TypeCodeVec();
	 (yyval.mp_TypeCodeVec)->push_back(auxptrTC);
	}
    break;

  case 164:

/* Line 690 of lalr1.cc  */
#line 1128 "idl.y"
    {std::cout << "Warning: \"exception\" token not allowed" << std::endl;
	PrimitiveTypeCode* auxptrTC = new PrimitiveTypeCode(TypeCode::KIND_NULL);
	 (yyval.mp_TypeCodeVec) = new TypeCodeVec();
	 (yyval.mp_TypeCodeVec)->push_back(auxptrTC);
	}
    break;



/* Line 690 of lalr1.cc  */
#line 1773 "idl.tab.cc"
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
  IDLParser::yysyntax_error_ (int, int)
  {
    return YY_("syntax error");
  }


  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
  const short int IDLParser::yypact_ninf_ = -166;
  const short int
  IDLParser::yypact_[] =
  {
         1,   -27,     8,    20,    76,    83,    84,    43,    91,  -166,
    -166,  -166,   107,  -166,     1,  -166,    64,    65,  -166,  -166,
      85,  -166,  -166,    75,  -166,    90,    92,  -166,    93,  -166,
      -7,    96,    97,  -166,   100,  -166,  -166,  -166,  -166,  -166,
     113,  -166,  -166,   120,     4,  -166,     1,   149,   103,   118,
    -166,   239,  -166,  -166,  -166,  -166,    19,  -166,  -166,   134,
    -166,    94,     9,  -166,  -166,   153,   119,  -166,  -166,  -166,
    -166,  -166,  -166,  -166,  -166,  -166,  -166,  -166,  -166,  -166,
    -166,  -166,  -166,   125,   113,  -166,  -166,   121,   128,   195,
     156,  -166,   130,   132,  -166,   131,   136,  -166,   137,   133,
     124,  -166,   142,   149,   183,  -166,  -166,  -166,  -166,  -166,
    -166,  -166,  -166,  -166,   270,     4,   185,  -166,  -166,   239,
      24,   170,  -166,   157,  -166,  -166,  -166,  -166,  -166,   197,
     155,  -166,  -166,  -166,   120,     4,  -166,   229,  -166,  -166,
     154,   165,   163,  -166,  -166,  -166,   189,  -166,  -166,  -166,
    -166,  -166,   161,  -166,  -166,   168,  -166,   185,  -166,  -166,
    -166,  -166,  -166,    24,    24,    24,    24,  -166,   162,   283,
    -166,  -166,  -166,   155,     0,  -166,   191,  -166,  -166,    -4,
      24,  -166,   154,  -166,   183,   173,   185,  -166,  -166,  -166,
     255,  -166,  -166,    24,    24,    24,    24,    24,    24,    24,
      24,    24,    24,  -166,  -166,  -166,  -166,  -166,   169,   175,
     239,   172,   210,    24,  -166,   174,  -166,  -166,    36,  -166,
    -166,    35,    35,    41,    41,   305,   309,   331,  -166,  -166,
    -166,  -166,    79,   185,     4,   177,  -166,   171,  -166,    24,
     186,   184,    36,   149,    36,  -166,  -166,   188,   233,  -166,
     277,  -166,  -166,  -166,   183,   199,  -166,  -166,   196,   192,
    -166,  -166,  -166,   233,  -166,  -166
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
      37,     0,    69,    68,    54,    53,    60,    70,   121,     0,
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
      -166,  -166,     6,  -166,  -166,  -166,   -28,   -42,   150,  -166,
      13,   122,   -46,   -45,  -166,  -166,  -166,  -166,    82,    15,
    -106,  -166,  -166,    78,  -166,  -166,   178,  -166,  -166,  -166,
    -166,  -166,  -166,   179,   180,  -166,   -44,   141,  -166,   -41,
    -166,  -166,  -166,  -166,  -166,   193,  -166,  -166,  -126,   -40,
     147,   -39,  -166,    34,  -166,    40,  -166,  -166,  -166,  -121,
    -166,   106,  -166,   198,  -166,    54,  -166,  -166,  -166,  -166,
      25,   -38,  -165,   -81,  -166,   -24,   -15
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
        85,   106,   107,   110,    98,   101,   111,    85,   113,   178,
     155,    85,    66,   116,    49,   215,    92,     1,    28,    27,
      36,     2,     3,   204,   205,    93,     4,   158,     5,   159,
     206,   160,   161,   162,    49,   121,   187,     6,   117,     7,
     -83,     8,    44,   122,    85,   118,   213,    65,   237,    85,
     239,   155,    99,   214,   240,   207,    66,   106,   107,   110,
      92,   101,   111,    85,   113,   219,    29,    65,   147,    93,
     151,     9,    10,    11,    85,   153,   163,   164,   165,    85,
     155,   157,   188,   189,   190,   191,    30,   195,   196,    33,
     166,   106,   107,    31,    32,    98,   111,    85,   200,   201,
     202,    34,   204,   205,   200,   201,   202,    35,   247,   206,
      37,    38,   221,   222,   223,   224,   225,   226,   227,   228,
     229,   230,    40,    49,    50,    51,    52,   246,    53,     1,
      94,    39,    54,     2,     3,    55,    41,    48,    42,    56,
      43,    57,    58,    46,    47,    59,   119,    60,    61,     6,
     120,     7,    62,     8,    63,    64,    65,   114,   250,    49,
      50,   115,    52,   123,    53,   124,   130,   127,    54,     2,
      85,    55,   233,   125,   128,    56,   131,    57,   132,   133,
     137,   136,   100,    60,    61,     6,   134,   135,    62,     8,
     138,    64,    65,   140,    98,   154,   171,   106,   107,   110,
      65,   101,   111,    85,   113,    49,    50,   173,    52,   174,
      53,   183,   180,   184,    54,   118,   185,    55,   186,   192,
     218,    56,   211,    57,   231,   232,   234,   235,   249,    60,
      61,   248,   252,   238,    62,   251,    63,    64,    65,    49,
      50,   258,    52,   257,    53,   262,   263,   264,    54,    49,
      50,    55,    52,   139,    53,    56,   254,    57,    54,   179,
     216,    55,   100,    60,    61,    56,   217,    57,    62,   261,
     172,    64,    65,    60,    61,   177,   253,   126,    62,   203,
      49,    64,    65,    52,   256,    53,   245,   129,   265,     0,
       2,     0,   148,   149,   150,     0,   146,     0,     0,   193,
     194,     0,     0,     0,    60,     0,     0,   195,   196,    62,
     220,     0,     0,    65,     0,   197,   198,   199,   200,   201,
     202,   193,   194,     0,     0,     0,   260,   193,   194,   195,
     196,     0,     0,     0,     0,   195,   196,   197,   198,   199,
     200,   201,   202,   197,   198,   199,   200,   201,   202,   193,
     194,     0,     0,   193,   194,     0,     0,   195,   196,     0,
       0,   195,   196,     0,     0,     0,   198,   199,   200,   201,
     202,   199,   200,   201,   202,   193,   194,     0,     0,     0,
       0,     0,     0,   195,   196,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   200,   201,   202
  };

  /* YYCHECK.  */
  const short int
  IDLParser::yycheck_[] =
  {
        40,    47,    47,    47,    44,    47,    47,    47,    47,   135,
     116,    51,    40,    51,    10,   180,    40,    16,    10,    46,
      14,    20,    21,    23,    24,    40,    25,     3,    27,     5,
      30,     7,     8,     9,    10,    26,   157,    36,    19,    38,
      47,    40,    49,    34,    84,    26,    50,    43,   213,    89,
      14,   157,    46,    57,    18,    55,    84,   103,   103,   103,
      84,   103,   103,   103,   103,   186,    46,    43,   114,    84,
     114,    70,    71,    72,   114,   115,    52,    53,    54,   119,
     186,   119,   163,   164,   165,   166,    10,    52,    53,    46,
      66,   137,   137,    10,    10,   135,   137,   137,    63,    64,
      65,    10,    23,    24,    63,    64,    65,     0,   234,    30,
      46,    46,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,    47,    10,    11,    12,    13,   233,    15,    16,
      10,    46,    19,    20,    21,    22,    46,    37,    46,    26,
      47,    28,    29,    47,    47,    32,    12,    34,    35,    36,
      56,    38,    39,    40,    41,    42,    43,    54,   239,    10,
      11,    43,    13,    10,    15,    46,    10,    46,    19,    20,
     210,    22,   210,    48,    46,    26,    46,    28,    46,    48,
      56,    48,    33,    34,    35,    36,    50,    50,    39,    40,
      48,    42,    43,    10,   234,    10,    26,   243,   243,   243,
      43,   243,   243,   243,   243,    10,    11,    10,    13,    54,
      15,    46,    58,    50,    19,    26,    55,    22,    50,    57,
      47,    26,    31,    28,    55,    50,    54,    17,    57,    34,
      35,    54,    48,    59,    39,    49,    41,    42,    43,    10,
      11,     8,    13,    55,    15,    46,    50,    55,    19,    10,
      11,    22,    13,   103,    15,    26,   243,    28,    19,   137,
     182,    22,    33,    34,    35,    26,   184,    28,    39,   254,
     123,    42,    43,    34,    35,   134,   242,    84,    39,   173,
      10,    42,    43,    13,   244,    15,   232,    89,   263,    -1,
      20,    -1,   114,   114,   114,    -1,    26,    -1,    -1,    44,
      45,    -1,    -1,    -1,    34,    -1,    -1,    52,    53,    39,
      55,    -1,    -1,    43,    -1,    60,    61,    62,    63,    64,
      65,    44,    45,    -1,    -1,    -1,    49,    44,    45,    52,
      53,    -1,    -1,    -1,    -1,    52,    53,    60,    61,    62,
      63,    64,    65,    60,    61,    62,    63,    64,    65,    44,
      45,    -1,    -1,    44,    45,    -1,    -1,    52,    53,    -1,
      -1,    52,    53,    -1,    -1,    -1,    61,    62,    63,    64,
      65,    62,    63,    64,    65,    44,    45,    -1,    -1,    -1,
      -1,    -1,    -1,    52,    53,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    63,    64,    65
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
     112,   115,   116,   127,    54,    43,   147,    19,    26,    12,
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
    "$end", "error", "$undefined", "INTEGER_LITERAL", "LONG_LITERAL",
  "FLOAT_LITERAL", "DOUBLE_LITERAL", "BOOLEAN_LITERAL", "STRING_LITERAL",
  "CHARACTER_LITERAL", "IDENTIFIER", "ANY_TOKEN", "ATTRIBUTE_TOKEN",
  "BOOLEAN_TOKEN", "CASE_TOKEN", "CHAR_TOKEN", "CONST_TOKEN",
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
      -1,    11,    -1,   116,    -1,   115,    -1,    83,    -1,   127,
      -1,   112,    -1,    95,    -1,    95,    50,    94,    -1,    96,
      -1,    97,    -1,    10,    -1,    98,    -1,    10,    99,    -1,
     100,    -1,   100,    99,    -1,    58,   148,    59,    -1,    22,
      -1,    19,    -1,    26,    19,    -1,   103,    -1,   106,    -1,
     104,    -1,   105,    -1,    26,    -1,    26,    26,    -1,    34,
      -1,   107,    -1,   108,    -1,    39,    26,    -1,    39,    26,
      26,    -1,    39,    34,    -1,    15,    -1,    13,    -1,    28,
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
      12,   147,   135,    -1,    32,    12,   147,   135,    -1,    96,
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
         0,   163,   163,   167,   171,   182,   183,   184,   185,   186,
     187,   190,   192,   194,   198,   218,   220,   221,   222,   225,
     238,   240,   255,   307,   308,   315,   316,   317,   320,   331,
     332,   333,   334,   335,   336,   337,   339,   345,   350,   351,
     354,   355,   356,   359,   364,   371,   372,   374,   381,   384,
     392,   397,   402,   408,   410,   412,   416,   417,   420,   421,
     423,   425,   428,   432,   433,   435,   437,   440,   443,   446,
     449,   454,   471,   477,   480,   486,   491,   497,   503,   512,
     513,   516,   544,   551,   554,   559,   560,   569,   570,   571,
     572,   577,   580,   586,   590,   596,   601,   608,   611,   618,
     628,   687,   688,   689,   690,   694,   697,   702,   708,   715,
     717,   724,   747,   754,   765,   768,   773,   777,   782,   785,
     789,   792,   796,   797,   801,   803,   807,   809,   812,   816,
     818,   820,   825,   826,   831,   832,   836,   839,   844,   849,
     854,   868,   879,   885,   887,   889,   901,   914,   926,   939,
     952,   974,   988,  1002,  1016,  1030,  1041,  1052,  1074,  1079,
    1084,  1090,  1096,  1119,  1127
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
  const int IDLParser::yylast_ = 396;
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
#line 2483 "idl.tab.cc"


/* Line 1138 of lalr1.cc  */
#line 1138 "idl.y"


// directly include the nonterm defs here
//@NONTERMTYPES@

/* Override yyerror */
public
void
yyverror(String s) throws ParseException
{
    String msg = yyerror_verbose(s);
    yyerror(msg);
}

