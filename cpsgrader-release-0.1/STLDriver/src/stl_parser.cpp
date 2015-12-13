/* A Bison parser, made by GNU Bison 2.7.12-4996.  */

/* Skeleton implementation for Bison LALR(1) parsers in C++
   
      Copyright (C) 2002-2013 Free Software Foundation, Inc.
   
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
#define yylex   CPSGraderlex

/* First part of user declarations.  */
/* Line 283 of lalr1.cc  */
#line 1 "stl_parser.ypp"

#include "stdafx.h"
#include <iostream>
#include <string>

#include <interval.h>
#include <transducer.h>
#include <signal_expr.h>
#include <robustness.h>
#include <tools.h>

using namespace std;
using namespace CPSGrader;


/* Line 283 of lalr1.cc  */
#line 56 "stl_parser.cpp"


#include "stl_parser.h"

/* User implementation prologue.  */
/* Line 289 of lalr1.cc  */
#line 137 "stl_parser.ypp"


#include "stl_driver.h"
#include "stl_scanner.h"

/* this "connects" the bison parser in the driver to the flex scanner class
 * object. it defines the yylex() function call to pull the next token from the
 * current lexer object of the driver context. */
#undef yylex
#define yylex driver.lexer->lex


/* Line 289 of lalr1.cc  */
#line 77 "stl_parser.cpp"


# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

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

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
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
# define YY_SYMBOL_PRINT(Title, Type, Value, Location) YYUSE(Type)
# define YY_REDUCE_PRINT(Rule)        static_cast<void>(0)
# define YY_STACK_PRINT()             static_cast<void>(0)

#endif /* !YYDEBUG */

#define yyerrok		(yyerrstatus_ = 0)
#define yyclearin	(yychar = yyempty_)

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


namespace CPSGrader {
/* Line 357 of lalr1.cc  */
#line 172 "stl_parser.cpp"

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Parser::yytnamerr_ (const char *yystr)
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
  Parser::Parser (class STLDriver& driver_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      driver (driver_yyarg)
  {
  }

  Parser::~Parser ()
  {
  }

#if YYDEBUG
  /*--------------------------------.
  | Print this symbol on YYOUTPUT.  |
  `--------------------------------*/

  inline void
  Parser::yy_symbol_value_print_ (int yytype,
			   const semantic_type* yyvaluep, const location_type* yylocationp)
  {
    YYUSE (yylocationp);
    YYUSE (yyvaluep);
    std::ostream& yyo = debug_stream ();
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    YYUSE (yytype);
  }


  void
  Parser::yy_symbol_print_ (int yytype,
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
  Parser::yydestruct_ (const char* yymsg,
			   int yytype, semantic_type* yyvaluep, location_type* yylocationp)
  {
    YYUSE (yylocationp);
    YYUSE (yymsg);
    YYUSE (yyvaluep);

    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

    switch (yytype)
    {
      case 31: /* "param_id" */
/* Line 452 of lalr1.cc  */
#line 130 "stl_parser.ypp"
        { delete ((*yyvaluep).stringVal); };
/* Line 452 of lalr1.cc  */
#line 275 "stl_parser.cpp"
        break;
      case 32: /* "phi_id" */
/* Line 452 of lalr1.cc  */
#line 130 "stl_parser.ypp"
        { delete ((*yyvaluep).stringVal); };
/* Line 452 of lalr1.cc  */
#line 282 "stl_parser.cpp"
        break;
      case 33: /* "new_id" */
/* Line 452 of lalr1.cc  */
#line 130 "stl_parser.ypp"
        { delete ((*yyvaluep).stringVal); };
/* Line 452 of lalr1.cc  */
#line 289 "stl_parser.cpp"
        break;
      case 34: /* "signal_id" */
/* Line 452 of lalr1.cc  */
#line 130 "stl_parser.ypp"
        { delete ((*yyvaluep).stringVal); };
/* Line 452 of lalr1.cc  */
#line 296 "stl_parser.cpp"
        break;
      case 35: /* "stl_test_id" */
/* Line 452 of lalr1.cc  */
#line 130 "stl_parser.ypp"
        { delete ((*yyvaluep).stringVal); };
/* Line 452 of lalr1.cc  */
#line 303 "stl_parser.cpp"
        break;
      case 36: /* "string" */
/* Line 452 of lalr1.cc  */
#line 130 "stl_parser.ypp"
        { delete ((*yyvaluep).stringVal); };
/* Line 452 of lalr1.cc  */
#line 310 "stl_parser.cpp"
        break;
      case 43: /* constant_signal */
/* Line 452 of lalr1.cc  */
#line 133 "stl_parser.ypp"
        { delete ((*yyvaluep).transducer_ptr); };
/* Line 452 of lalr1.cc  */
#line 317 "stl_parser.cpp"
        break;
      case 44: /* signal */
/* Line 452 of lalr1.cc  */
#line 132 "stl_parser.ypp"
        { delete ((*yyvaluep).transducer_ptr); };
/* Line 452 of lalr1.cc  */
#line 324 "stl_parser.cpp"
        break;
      case 45: /* signal_atom */
/* Line 452 of lalr1.cc  */
#line 132 "stl_parser.ypp"
        { delete ((*yyvaluep).transducer_ptr); };
/* Line 452 of lalr1.cc  */
#line 331 "stl_parser.cpp"
        break;
      case 46: /* signal_unaryexpr */
/* Line 452 of lalr1.cc  */
#line 133 "stl_parser.ypp"
        { delete ((*yyvaluep).transducer_ptr); };
/* Line 452 of lalr1.cc  */
#line 338 "stl_parser.cpp"
        break;
      case 47: /* signal_multexpr */
/* Line 452 of lalr1.cc  */
#line 133 "stl_parser.ypp"
        { delete ((*yyvaluep).transducer_ptr); };
/* Line 452 of lalr1.cc  */
#line 345 "stl_parser.cpp"
        break;
      case 48: /* signal_addexpr */
/* Line 452 of lalr1.cc  */
#line 133 "stl_parser.ypp"
        { delete ((*yyvaluep).transducer_ptr); };
/* Line 452 of lalr1.cc  */
#line 352 "stl_parser.cpp"
        break;
      case 49: /* signal_expr */
/* Line 452 of lalr1.cc  */
#line 133 "stl_parser.ypp"
        { delete ((*yyvaluep).transducer_ptr); };
/* Line 452 of lalr1.cc  */
#line 359 "stl_parser.cpp"
        break;
      case 50: /* stl_atom */
/* Line 452 of lalr1.cc  */
#line 132 "stl_parser.ypp"
        { delete ((*yyvaluep).transducer_ptr); };
/* Line 452 of lalr1.cc  */
#line 366 "stl_parser.cpp"
        break;
      case 52: /* interval */
/* Line 452 of lalr1.cc  */
#line 131 "stl_parser.ypp"
        { delete ((*yyvaluep).interval_ptr); };
/* Line 452 of lalr1.cc  */
#line 373 "stl_parser.cpp"
        break;
      case 53: /* stl_formula */
/* Line 452 of lalr1.cc  */
#line 132 "stl_parser.ypp"
        { delete ((*yyvaluep).transducer_ptr); };
/* Line 452 of lalr1.cc  */
#line 380 "stl_parser.cpp"
        break;

      default:
        break;
    }
  }

  void
  Parser::yypop_ (unsigned int n)
  {
    yystate_stack_.pop (n);
    yysemantic_stack_.pop (n);
    yylocation_stack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif

  inline bool
  Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Parser::parse ()
  {
    /// Lookahead and lookahead in internal form.
    int yychar = yyempty_;
    int yytoken = 0;

    // State.
    int yyn;
    int yylen = 0;
    int yystate = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// Semantic value of the lookahead.
    static semantic_type yyval_default;
    semantic_type yylval = yyval_default;
    /// Location of the lookahead.
    location_type yylloc;
    /// The locations where the error started and ended.
    location_type yyerror_range[3];

    /// $$.
    semantic_type yyval;
    /// @$.
    location_type yyloc;

    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


/* User initialization code.  */
/* Line 539 of lalr1.cc  */
#line 45 "stl_parser.ypp"
{
    // initialize the initial location object
    yylloc.begin.filename = yylloc.end.filename = &driver.streamname;
}
/* Line 539 of lalr1.cc  */
#line 481 "stl_parser.cpp"

    /* Initialize the stacks.  The initial state will be pushed in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystate_stack_.clear ();
    yysemantic_stack_.clear ();
    yylocation_stack_.clear ();
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
        yychar = yylex (&yylval, &yylloc, driver);
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

    // Compute the default @$.
    {
      slice<location_type, location_stack_type> slice (yylocation_stack_, yylen);
      YYLLOC_DEFAULT (yyloc, slice, yylen);
    }

    // Perform the reduction.
    YY_REDUCE_PRINT (yyn);
    switch (yyn)
      {
          case 2:
/* Line 664 of lalr1.cc  */
#line 153 "stl_parser.ypp"
    {
            (yyval.stringVal) = (yysemantic_stack_[(1) - (1)].stringVal);
        }
    break;

  case 3:
/* Line 664 of lalr1.cc  */
#line 158 "stl_parser.ypp"
    {
           (yyval.stringVal) = (yysemantic_stack_[(1) - (1)].stringVal);
        }
    break;

  case 4:
/* Line 664 of lalr1.cc  */
#line 163 "stl_parser.ypp"
    {
            (yyval.transducer_ptr) = new constant_transducer(*(yysemantic_stack_[(1) - (1)].stringVal));
            delete (yysemantic_stack_[(1) - (1)].stringVal);
        }
    break;

  case 5:
/* Line 664 of lalr1.cc  */
#line 169 "stl_parser.ypp"
    {
           (yyval.transducer_ptr) = new constant_transducer(*(yysemantic_stack_[(1) - (1)].stringVal));
           delete (yysemantic_stack_[(1) - (1)].stringVal);
        }
    break;

  case 6:
/* Line 664 of lalr1.cc  */
#line 175 "stl_parser.ypp"
    {
            (yyval.transducer_ptr) = new signal_transducer(*(yysemantic_stack_[(4) - (1)].stringVal));
            int i = (yyval.transducer_ptr)->signal_map[*(yysemantic_stack_[(4) - (1)].stringVal)];
                 
            if (i==0) {
                cout << "Parsing error: unknown signal " << *(yysemantic_stack_[(4) - (1)].stringVal) << endl;
                delete (yyval.transducer_ptr);
                (yyval.transducer_ptr) = nullptr;
                YYERROR;
            }   
            delete (yysemantic_stack_[(4) - (1)].stringVal);
        }
    break;

  case 7:
/* Line 664 of lalr1.cc  */
#line 190 "stl_parser.ypp"
    {
            (yyval.transducer_ptr) = (yysemantic_stack_[(1) - (1)].transducer_ptr);
        }
    break;

  case 8:
/* Line 664 of lalr1.cc  */
#line 195 "stl_parser.ypp"
    {
            (yyval.transducer_ptr) = (yysemantic_stack_[(1) - (1)].transducer_ptr);
        }
    break;

  case 9:
/* Line 664 of lalr1.cc  */
#line 200 "stl_parser.ypp"
    {
	       (yyval.transducer_ptr) = (yysemantic_stack_[(3) - (2)].transducer_ptr);
	    }
    break;

  case 10:
/* Line 664 of lalr1.cc  */
#line 205 "stl_parser.ypp"
    {
	      (yyval.transducer_ptr) = (yysemantic_stack_[(1) - (1)].transducer_ptr);
	    }
    break;

  case 11:
/* Line 664 of lalr1.cc  */
#line 209 "stl_parser.ypp"
    {
            (yyval.transducer_ptr) = new abs_transducer((yysemantic_stack_[(4) - (3)].transducer_ptr));
        }
    break;

  case 12:
/* Line 664 of lalr1.cc  */
#line 214 "stl_parser.ypp"
    {
	      (yyval.transducer_ptr) = (yysemantic_stack_[(1) - (1)].transducer_ptr);
	    }
    break;

  case 13:
/* Line 664 of lalr1.cc  */
#line 218 "stl_parser.ypp"
    {
	      (yyval.transducer_ptr) = new mult_transducer((yysemantic_stack_[(3) - (1)].transducer_ptr), (yysemantic_stack_[(3) - (3)].transducer_ptr));
          }
    break;

  case 14:
/* Line 664 of lalr1.cc  */
#line 223 "stl_parser.ypp"
    {
	      (yyval.transducer_ptr) = (yysemantic_stack_[(1) - (1)].transducer_ptr);
	    }
    break;

  case 15:
/* Line 664 of lalr1.cc  */
#line 227 "stl_parser.ypp"
    {
	      (yyval.transducer_ptr) = new plus_transducer((yysemantic_stack_[(3) - (1)].transducer_ptr), (yysemantic_stack_[(3) - (3)].transducer_ptr));
        }
    break;

  case 16:
/* Line 664 of lalr1.cc  */
#line 231 "stl_parser.ypp"
    {
	      (yyval.transducer_ptr) = new minus_transducer((yysemantic_stack_[(3) - (1)].transducer_ptr), (yysemantic_stack_[(3) - (3)].transducer_ptr));
        }
    break;

  case 17:
/* Line 664 of lalr1.cc  */
#line 236 "stl_parser.ypp"
    {
            (yyval.transducer_ptr) = (yysemantic_stack_[(1) - (1)].transducer_ptr);
        }
    break;

  case 18:
/* Line 664 of lalr1.cc  */
#line 242 "stl_parser.ypp"
    {
              (yyval.transducer_ptr) = new stl_atom((yysemantic_stack_[(3) - (1)].transducer_ptr), *(yysemantic_stack_[(3) - (2)].stringVal), (yysemantic_stack_[(3) - (3)].transducer_ptr));
          }
    break;

  case 19:
/* Line 664 of lalr1.cc  */
#line 247 "stl_parser.ypp"
    { (yyval.stringVal) = new string("<"); }
    break;

  case 20:
/* Line 664 of lalr1.cc  */
#line 248 "stl_parser.ypp"
    { (yyval.stringVal) = new string(">"); }
    break;

  case 21:
/* Line 664 of lalr1.cc  */
#line 252 "stl_parser.ypp"
    {
             (yyval.interval_ptr) = new interval(*(yysemantic_stack_[(5) - (2)].stringVal), *(yysemantic_stack_[(5) - (4)].stringVal));
             delete (yysemantic_stack_[(5) - (2)].stringVal);
             delete (yysemantic_stack_[(5) - (4)].stringVal);
         }
    break;

  case 22:
/* Line 664 of lalr1.cc  */
#line 259 "stl_parser.ypp"
    {
             (yyval.interval_ptr) = new interval(*(yysemantic_stack_[(4) - (2)].stringVal), *(yysemantic_stack_[(4) - (3)].stringVal)); 
             delete (yysemantic_stack_[(4) - (2)].stringVal);
             delete (yysemantic_stack_[(4) - (3)].stringVal);
         }
    break;

  case 23:
/* Line 664 of lalr1.cc  */
#line 267 "stl_parser.ypp"
    { 
                 (yyval.transducer_ptr) = (yysemantic_stack_[(1) - (1)].transducer_ptr);
             }
    break;

  case 24:
/* Line 664 of lalr1.cc  */
#line 271 "stl_parser.ypp"
    {
                 (yyval.transducer_ptr) = new not_transducer((yysemantic_stack_[(2) - (2)].transducer_ptr));
             }
    break;

  case 25:
/* Line 664 of lalr1.cc  */
#line 275 "stl_parser.ypp"
    {
                 (yyval.transducer_ptr) = new and_transducer((yysemantic_stack_[(3) - (1)].transducer_ptr), (yysemantic_stack_[(3) - (3)].transducer_ptr));
             }
    break;

  case 26:
/* Line 664 of lalr1.cc  */
#line 279 "stl_parser.ypp"
    { 
                 (yyval.transducer_ptr) = new or_transducer((yysemantic_stack_[(3) - (1)].transducer_ptr), (yysemantic_stack_[(3) - (3)].transducer_ptr));
             }
    break;

  case 27:
/* Line 664 of lalr1.cc  */
#line 283 "stl_parser.ypp"
    { 
                 (yyval.transducer_ptr) = new implies_transducer((yysemantic_stack_[(3) - (1)].transducer_ptr), (yysemantic_stack_[(3) - (3)].transducer_ptr));
             }
    break;

  case 28:
/* Line 664 of lalr1.cc  */
#line 287 "stl_parser.ypp"
    { 
                 (yyval.transducer_ptr) = new ev_transducer((yysemantic_stack_[(3) - (2)].interval_ptr), (yysemantic_stack_[(3) - (3)].transducer_ptr));
             }
    break;

  case 29:
/* Line 664 of lalr1.cc  */
#line 291 "stl_parser.ypp"
    { 
                 (yyval.transducer_ptr) = new alw_transducer((yysemantic_stack_[(3) - (2)].interval_ptr), (yysemantic_stack_[(3) - (3)].transducer_ptr));
             }
    break;

  case 30:
/* Line 664 of lalr1.cc  */
#line 295 "stl_parser.ypp"
    {
                 (yyval.transducer_ptr) = new until_transducer((yysemantic_stack_[(4) - (1)].transducer_ptr), (yysemantic_stack_[(4) - (3)].interval_ptr), (yysemantic_stack_[(4) - (4)].transducer_ptr));
             }
    break;

  case 31:
/* Line 664 of lalr1.cc  */
#line 299 "stl_parser.ypp"
    { 
                 (yyval.transducer_ptr) = (yysemantic_stack_[(3) - (2)].transducer_ptr);
             }
    break;

  case 32:
/* Line 664 of lalr1.cc  */
#line 303 "stl_parser.ypp"
    {

                 transducer * ref = driver.formula_map[*(yysemantic_stack_[(1) - (1)].stringVal)];
                 
                 if (ref==nullptr) {
                     cout << "Parsing error: unknown identifier " << *(yysemantic_stack_[(1) - (1)].stringVal) << endl;
                     (yyval.transducer_ptr) = nullptr;
                     YYERROR;
                 }
                 else {            
                     (yyval.transducer_ptr) = ref->clone();
                     delete (yysemantic_stack_[(1) - (1)].stringVal);
                 }
             }
    break;

  case 33:
/* Line 664 of lalr1.cc  */
#line 321 "stl_parser.ypp"
    { 
                driver.formula_map[*(yysemantic_stack_[(3) - (1)].stringVal)] = (yysemantic_stack_[(3) - (3)].transducer_ptr);
                delete (yysemantic_stack_[(3) - (1)].stringVal);
            }
    break;

  case 34:
/* Line 664 of lalr1.cc  */
#line 327 "stl_parser.ypp"
    {
             double x; 
             driver.add_trace_test(*(yysemantic_stack_[(4) - (2)].stringVal), *(yysemantic_stack_[(4) - (4)].stringVal), 0., false); 
             delete (yysemantic_stack_[(4) - (2)].stringVal);
         }
    break;

  case 35:
/* Line 664 of lalr1.cc  */
#line 333 "stl_parser.ypp"
    {
             double x; 
             s_to_d(*(yysemantic_stack_[(8) - (6)].stringVal), x);
             driver.add_trace_test(*(yysemantic_stack_[(8) - (2)].stringVal), *(yysemantic_stack_[(8) - (4)].stringVal), x, (yysemantic_stack_[(8) - (8)].boolVal)); 
             delete (yysemantic_stack_[(8) - (2)].stringVal);
             delete (yysemantic_stack_[(8) - (4)].stringVal);
             delete (yysemantic_stack_[(8) - (6)].stringVal);
         }
    break;

  case 36:
/* Line 664 of lalr1.cc  */
#line 343 "stl_parser.ypp"
    {
           (yyval.boolVal) = true;
       }
    break;

  case 37:
/* Line 664 of lalr1.cc  */
#line 347 "stl_parser.ypp"
    {
           (yyval.boolVal) = false;
       }
    break;

  case 38:
/* Line 664 of lalr1.cc  */
#line 354 "stl_parser.ypp"
    {
                    double val;
                    s_to_d( *(yysemantic_stack_[(3) - (3)].stringVal), val );
                    driver.param_map[*(yysemantic_stack_[(3) - (1)].stringVal)] = val;
                    delete (yysemantic_stack_[(3) - (1)].stringVal);
                    delete (yysemantic_stack_[(3) - (3)].stringVal);
                 }
    break;

  case 39:
/* Line 664 of lalr1.cc  */
#line 362 "stl_parser.ypp"
    {
                    double val;
                    s_to_d( *(yysemantic_stack_[(3) - (3)].stringVal), val );
                    driver.param_map[*(yysemantic_stack_[(3) - (1)].stringVal)] = val;
                    delete (yysemantic_stack_[(3) - (1)].stringVal);
                    delete (yysemantic_stack_[(3) - (3)].stringVal);
                 }
    break;

  case 43:
/* Line 664 of lalr1.cc  */
#line 378 "stl_parser.ypp"
    {
                
                    double val;
                    s_to_d( *(yysemantic_stack_[(3) - (3)].stringVal), val );
                   
                    (yyval.param_map_ptr) = new map<string,double>();
                    (*(yyval.param_map_ptr))[*(yysemantic_stack_[(3) - (1)].stringVal)] = val;
                    delete (yysemantic_stack_[(3) - (1)].stringVal);
                    delete (yysemantic_stack_[(3) - (3)].stringVal);
                 }
    break;

  case 44:
/* Line 664 of lalr1.cc  */
#line 389 "stl_parser.ypp"
    {
                    double val;
                    s_to_d( *(yysemantic_stack_[(3) - (3)].stringVal), val );      
                    (yyval.param_map_ptr) = new map<string,double>();
                    (*(yyval.param_map_ptr))[*(yysemantic_stack_[(3) - (1)].stringVal)] = val;
                    delete (yysemantic_stack_[(3) - (1)].stringVal);
                    delete (yysemantic_stack_[(3) - (3)].stringVal);
                 }
    break;

  case 46:
/* Line 664 of lalr1.cc  */
#line 401 "stl_parser.ypp"
    {
    (yyval.param_map_ptr) = new map<string,double>(*(yysemantic_stack_[(3) - (1)].param_map_ptr));
    auto elem = (yysemantic_stack_[(3) - (3)].param_map_ptr)->begin();
    (*(yyval.param_map_ptr))[elem->first] = elem->second; 
}
    break;

  case 47:
/* Line 664 of lalr1.cc  */
#line 408 "stl_parser.ypp"
    {
                           (yyval.param_map_ptr) = new map<string,double>(); 
                       }
    break;

  case 48:
/* Line 664 of lalr1.cc  */
#line 412 "stl_parser.ypp"
    {
                           (yyval.param_map_ptr) = (yysemantic_stack_[(3) - (2)].param_map_ptr);
                       }
    break;

  case 49:
/* Line 664 of lalr1.cc  */
#line 419 "stl_parser.ypp"
    {
             transducer::signal_map[*(yysemantic_stack_[(1) - (1)].stringVal)] = transducer::signal_map.size()+1;
             delete (yysemantic_stack_[(1) - (1)].stringVal);                    
          }
    break;

  case 50:
/* Line 664 of lalr1.cc  */
#line 424 "stl_parser.ypp"
    {
              delete (yysemantic_stack_[(1) - (1)].stringVal);
          }
    break;

  case 54:
/* Line 664 of lalr1.cc  */
#line 434 "stl_parser.ypp"
    {
            driver.add_stl_test(*(yysemantic_stack_[(11) - (1)].stringVal), *(yysemantic_stack_[(11) - (2)].param_map_ptr), (yysemantic_stack_[(11) - (4)].transducer_ptr), *(yysemantic_stack_[(11) - (6)].stringVal), *(yysemantic_stack_[(11) - (8)].stringVal), (yysemantic_stack_[(11) - (10)].boolVal) );
            delete (yysemantic_stack_[(11) - (1)].stringVal);
            delete (yysemantic_stack_[(11) - (2)].param_map_ptr);
            delete (yysemantic_stack_[(11) - (6)].stringVal);
            delete (yysemantic_stack_[(11) - (8)].stringVal);
        }
    break;

  case 55:
/* Line 664 of lalr1.cc  */
#line 442 "stl_parser.ypp"
    {   
            if ((yysemantic_stack_[(2) - (2)].param_map_ptr)->empty())
                driver.add_stl_test(*(yysemantic_stack_[(2) - (1)].stringVal));
            else {
                driver.add_stl_test(*(yysemantic_stack_[(2) - (1)].stringVal), *(yysemantic_stack_[(2) - (2)].param_map_ptr));
            }
            delete (yysemantic_stack_[(2) - (1)].stringVal);
            delete (yysemantic_stack_[(2) - (2)].param_map_ptr);
        }
    break;


/* Line 664 of lalr1.cc  */
#line 1040 "stl_parser.cpp"
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
    while (1 < yystate_stack_.height ())
      {
        yydestruct_ ("Cleanup: popping",
                     yystos_[yystate_stack_[0]],
                     &yysemantic_stack_[0],
                     &yylocation_stack_[0]);
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
        if (yychar != yyempty_)
          {
            /* Make sure we have latest lookahead translation.  See
               comments at user semantic actions for why this is
               necessary.  */
            yytoken = yytranslate_ (yychar);
            yydestruct_ (YY_NULL, yytoken, &yylval, &yylloc);
          }

        while (1 < yystate_stack_.height ())
          {
            yydestruct_ (YY_NULL,
                         yystos_[yystate_stack_[0]],
                         &yysemantic_stack_[0],
                         &yylocation_stack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (int yystate, int yytoken)
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

    char const* yyformat = YY_NULL;
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
  const signed char Parser::yypact_ninf_ = -84;
  const signed char
  Parser::yypact_[] =
  {
       -16,    -4,    38,   -20,    41,   -84,    28,   -84,   -84,   -84,
       2,    26,    48,   -84,    75,   -84,   -84,   -84,    83,    54,
      25,    12,   -84,   -84,   -84,   -84,    71,    72,    -4,    38,
      67,    25,    25,   101,   101,   100,   -84,   -84,   -84,   103,
     -84,   -84,   -84,   -84,   -84,    74,    27,   -84,    78,   102,
     102,   -84,   -19,   -84,   -84,   -84,   -84,    91,    45,    64,
      10,    47,    25,    25,    35,    93,    19,    19,    19,   -84,
     -84,    35,    25,    25,    25,   101,    30,    73,   -84,   -84,
     -84,    80,   -84,   -84,   -84,   -84,   -11,   -84,   -84,    35,
     105,   109,   -84,   -84,   -84,   -84,     0,     0,     0,    25,
      76,    77,   -84,     1,    25,    99,    47,   113,   112,   -84,
     -84,   -84,    89,    90,   -84,    30,    70,    56,   117,   -84,
     -84,   -84,   -84,    86,   -84,   -84,   -84,   -84,   106,    88,
     108,    56,    87,   -84
  };

  /* YYDEFACT[S] -- default reduction number in state S.  Performed when
     YYTABLE doesn't specify something else to do.  Zero means the
     default is an error.  */
  const unsigned char
  Parser::yydefact_[] =
  {
         0,     0,     0,     0,     0,    59,     0,    61,    62,    60,
       0,     0,     0,    40,    42,    49,    50,    51,    53,     0,
       0,     0,     1,    63,    65,    64,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     4,     5,    32,     0,
       8,     7,    10,    12,    14,    17,     0,    23,    33,    47,
      47,    57,     0,    38,    39,    41,    52,    34,     0,     0,
      24,     0,     0,     0,     0,     0,     0,     0,     0,    19,
      20,     0,     0,     0,     0,     0,     0,     0,    55,    58,
      56,     0,     9,    31,     2,     3,     0,    29,    28,     0,
       0,     0,    15,    16,    13,    18,    25,    26,    27,     0,
       0,     0,    45,     0,     0,     0,     0,     0,     0,    11,
       6,    30,     0,     0,    48,     0,     0,     0,     0,    22,
      43,    44,    46,     0,    36,    37,    35,    21,     0,     0,
       0,     0,     0,    54
  };

  /* YYPGOTO[NTERM-NUM].  */
  const signed char
  Parser::yypgoto_[] =
  {
       -84,   -83,   -84,   -84,    31,   -84,   -84,   -84,   -27,   -84,
     -84,   -29,   -31,   116,   -84,    -3,   104,   -84,   119,    15,
     -84,    81,   107,   -84,   -84,    82,   -84,   123,   -84
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const signed char
  Parser::yydefgoto_[] =
  {
        -1,    86,    40,    41,    42,    43,    44,    45,    46,    47,
      71,    62,    48,     5,     6,   126,    13,    14,     7,   102,
     103,    77,    17,    18,     8,    51,    52,     9,    10
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If YYTABLE_NINF_, syntax error.  */
  const signed char Parser::yytable_ninf_ = -1;
  const unsigned char
  Parser::yytable_[] =
  {
        59,    60,    22,   107,    58,    63,   106,   114,     1,     2,
       3,    73,    74,    19,    49,    75,    50,     4,   115,    84,
      85,    79,    74,   118,    89,    75,     1,    11,     3,    12,
      31,    87,    88,    32,    69,     4,    70,    90,    33,    34,
      89,    96,    97,    98,    95,    49,    99,    50,    35,    36,
      37,    82,    69,    39,    70,    36,    37,    38,    35,    39,
      20,   100,   108,   101,    26,    36,    37,    21,   111,    39,
      83,    15,    16,   116,    72,    73,    74,    84,    85,    75,
      72,    73,    74,   124,   125,    75,    27,   123,    72,    73,
      74,    30,    28,    75,    66,    67,    68,    92,    93,    94,
      29,    53,    54,    57,    61,    64,    65,    76,    81,    91,
     105,   109,   104,   110,   112,   113,   117,   119,    82,   120,
     121,   127,   128,   129,   130,   131,    23,   133,   132,    24,
     122,    78,    55,    25,    80,     0,    56
  };

  /* YYCHECK.  */
  const short int
  Parser::yycheck_[] =
  {
        31,    32,     0,    86,    31,    34,    17,     6,    24,    25,
      26,    11,    12,    33,    33,    15,    35,    33,    17,    30,
      31,    40,    12,   106,     5,    15,    24,    31,    26,    33,
       5,    62,    63,     8,     7,    33,     9,    64,    13,    14,
       5,    72,    73,    74,    71,    33,    75,    35,    23,    30,
      31,     6,     7,    34,     9,    30,    31,    32,    23,    34,
      19,    31,    89,    33,    38,    30,    31,    39,    99,    34,
       6,    33,    34,   104,    10,    11,    12,    30,    31,    15,
      10,    11,    12,    27,    28,    15,    38,    17,    10,    11,
      12,    37,    17,    15,    20,    21,    22,    66,    67,    68,
      17,    30,    30,    36,     3,     5,     3,     5,    17,    16,
      30,     6,    39,     4,    38,    38,    17,     4,     6,    30,
      30,     4,    36,    17,    36,    17,    10,    40,   131,    10,
     115,    50,    28,    10,    52,    -1,    29
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  Parser::yystos_[] =
  {
         0,    24,    25,    26,    33,    54,    55,    59,    65,    68,
      69,    31,    33,    57,    58,    33,    34,    63,    64,    33,
      19,    39,     0,    54,    59,    68,    38,    38,    17,    17,
      37,     5,     8,    13,    14,    23,    30,    31,    32,    34,
      43,    44,    45,    46,    47,    48,    49,    50,    53,    33,
      35,    66,    67,    30,    30,    57,    63,    36,    49,    53,
      53,     3,    52,    52,     5,     3,    20,    21,    22,     7,
       9,    51,    10,    11,    12,    15,     5,    62,    62,    40,
      66,    17,     6,     6,    30,    31,    42,    53,    53,     5,
      49,    16,    45,    45,    45,    49,    53,    53,    53,    52,
      31,    33,    60,    61,    39,    30,    17,    42,    49,     6,
       4,    53,    38,    38,     6,    17,    53,    17,    42,     4,
      30,    30,    60,    17,    27,    28,    56,     4,    36,    17,
      36,    17,    56,    40
  };

#if YYDEBUG
  /* TOKEN_NUMBER_[YYLEX-NUM] -- Internal symbol number corresponding
     to YYLEX-NUM.  */
  const unsigned short int
  Parser::yytoken_number_[] =
  {
         0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,    58,    61,   123,
     125
  };
#endif

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
  const unsigned char
  Parser::yyr1_[] =
  {
         0,    41,    42,    42,    43,    43,    44,    45,    45,    45,
      46,    46,    47,    47,    48,    48,    48,    49,    50,    51,
      51,    52,    52,    53,    53,    53,    53,    53,    53,    53,
      53,    53,    53,    54,    55,    55,    56,    56,    57,    57,
      58,    58,    59,    60,    60,    61,    61,    62,    62,    63,
      63,    64,    64,    65,    66,    66,    67,    67,    68,    69,
      69,    69,    69,    69,    69,    69
  };

  /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
  const unsigned char
  Parser::yyr2_[] =
  {
         0,     2,     1,     1,     1,     1,     4,     1,     1,     3,
       1,     4,     1,     3,     1,     3,     3,     1,     3,     1,
       1,     5,     4,     1,     2,     3,     3,     3,     3,     3,
       4,     3,     1,     3,     4,     8,     1,     1,     3,     3,
       1,     3,     2,     3,     3,     1,     3,     0,     3,     1,
       1,     1,     3,     2,    11,     2,     2,     1,     4,     1,
       1,     1,     1,     2,     2,     2
  };


  /* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
     First, the terminals, then, starting at \a yyntokens_, nonterminals.  */
  const char*
  const Parser::yytname_[] =
  {
    "\"end of file\"", "error", "$undefined", "\"[\"", "\"]\"", "\"(\"",
  "\")\"", "\"<\"", "\"not\"", "\">\"", "\"and\"", "\"or\"", "\"=>\"",
  "\"alw\"", "\"ev\"", "\"until\"", "\"time\"", "\",\"", "\"end of line\"",
  "\":=\"", "\"+\"", "\"-\"", "\"*\"", "\"abs\"", "\"param_decl\"",
  "\"signal_decl\"", "\"test\"", "\"true\"", "\"false\"", "\"double\"",
  "\"constant\"", "\"param_id\"", "\"phi_id\"", "\"new_id\"",
  "\"signal_id\"", "\"stl_test_id\"", "\"string\"", "':'", "'='", "'{'",
  "'}'", "$accept", "constant", "constant_signal", "signal", "signal_atom",
  "signal_unaryexpr", "signal_multexpr", "signal_addexpr", "signal_expr",
  "stl_atom", "op", "interval", "stl_formula", "assignement", "trace_env",
  "boolean", "param_assignement", "param_assignement_list",
  "param_assignements", "local_param_assignement",
  "local_param_assignement_list", "local_param_assignements", "signal_new",
  "signal_new_list", "signal_decl", "stl_test", "stl_tests", "trace_test",
  "start", YY_NULL
  };

#if YYDEBUG
  /* YYRHS -- A `-1'-separated list of the rules' RHS.  */
  const Parser::rhs_number_type
  Parser::yyrhs_[] =
  {
        69,     0,    -1,    30,    -1,    31,    -1,    30,    -1,    31,
      -1,    34,     3,    16,     4,    -1,    44,    -1,    43,    -1,
       5,    49,     6,    -1,    45,    -1,    23,     5,    49,     6,
      -1,    46,    -1,    48,    22,    45,    -1,    47,    -1,    48,
      20,    45,    -1,    48,    21,    45,    -1,    48,    -1,    49,
      51,    49,    -1,     7,    -1,     9,    -1,     3,    42,    17,
      42,     4,    -1,     3,    42,    42,     4,    -1,    50,    -1,
       8,    53,    -1,    53,    10,    53,    -1,    53,    11,    53,
      -1,    53,    12,    53,    -1,    14,    52,    53,    -1,    13,
      52,    53,    -1,    53,    15,    52,    53,    -1,     5,    53,
       6,    -1,    32,    -1,    33,    19,    53,    -1,    26,    33,
      37,    36,    -1,    26,    33,    37,    36,    17,    30,    17,
      56,    -1,    27,    -1,    28,    -1,    31,    38,    30,    -1,
      33,    38,    30,    -1,    57,    -1,    58,    17,    57,    -1,
      24,    58,    -1,    31,    38,    30,    -1,    33,    38,    30,
      -1,    60,    -1,    61,    17,    60,    -1,    -1,     5,    61,
       6,    -1,    33,    -1,    34,    -1,    63,    -1,    64,    17,
      63,    -1,    25,    64,    -1,    33,    62,    39,    53,    17,
      36,    17,    36,    17,    56,    40,    -1,    35,    62,    -1,
      67,    66,    -1,    66,    -1,    55,    39,    67,    40,    -1,
      54,    -1,    68,    -1,    59,    -1,    65,    -1,    69,    54,
      -1,    69,    68,    -1,    69,    59,    -1
  };

  /* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
     YYRHS.  */
  const unsigned char
  Parser::yyprhs_[] =
  {
         0,     0,     3,     5,     7,     9,    11,    16,    18,    20,
      24,    26,    31,    33,    37,    39,    43,    47,    49,    53,
      55,    57,    63,    68,    70,    73,    77,    81,    85,    89,
      93,    98,   102,   104,   108,   113,   122,   124,   126,   130,
     134,   136,   140,   143,   147,   151,   153,   157,   158,   162,
     164,   166,   168,   172,   175,   187,   190,   193,   195,   200,
     202,   204,   206,   208,   211,   214
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned short int
  Parser::yyrline_[] =
  {
         0,   152,   152,   157,   162,   168,   174,   189,   194,   199,
     204,   208,   213,   217,   222,   226,   230,   235,   241,   247,
     248,   251,   258,   266,   270,   274,   278,   282,   286,   290,
     294,   298,   302,   320,   326,   332,   342,   346,   353,   361,
     370,   371,   373,   377,   388,   399,   400,   408,   411,   418,
     423,   428,   429,   431,   433,   441,   452,   453,   455,   457,
     458,   459,   460,   461,   462,   463
  };

  // Print the state stack on the debug stream.
  void
  Parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (state_stack_type::const_iterator i = yystate_stack_.begin ();
	 i != yystate_stack_.end (); ++i)
      *yycdebug_ << ' ' << *i;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  Parser::yy_reduce_print_ (int yyrule)
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
  Parser::token_number_type
  Parser::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
    {
           0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    37,     2,
       2,    38,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    39,     2,    40,     2,     2,     2,     2,
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
      35,    36
    };
    if ((unsigned int) t <= yyuser_token_number_max_)
      return translate_table[t];
    else
      return yyundef_token_;
  }

  const int Parser::yyeof_ = 0;
  const int Parser::yylast_ = 136;
  const int Parser::yynnts_ = 29;
  const int Parser::yyempty_ = -2;
  const int Parser::yyfinal_ = 22;
  const int Parser::yyterror_ = 1;
  const int Parser::yyerrcode_ = 256;
  const int Parser::yyntokens_ = 41;

  const unsigned int Parser::yyuser_token_number_max_ = 291;
  const Parser::token_number_type Parser::yyundef_token_ = 2;


} // CPSGrader
/* Line 1135 of lalr1.cc  */
#line 1672 "stl_parser.cpp"
/* Line 1136 of lalr1.cc  */
#line 464 "stl_parser.ypp"


void CPSGrader::Parser::error(const Parser::location_type& l,
			    const std::string& m)
{
    driver.error(l, m);
}
