// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

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

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.





#include "parser.tab.hh"


// Unqualified %code blocks.
#line 13 "parser.y"

    #define yylex lexer.yylex

#line 50 "parser.tab.cc"


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


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif



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
      *yycdebug_ << '\n';                       \
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
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

namespace yy {
#line 123 "parser.tab.cc"

  /// Build a parser object.
  parser::parser (CustomLexer &lexer_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      lexer (lexer_yyarg)
  {}

  parser::~parser ()
  {}

  parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/

  // basic_symbol.
  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value (that.value)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t)
    : Base (t)
    , value ()
  {}

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (value_type) v)
    : Base (t)
    , value (YY_MOVE (v))
  {}


  template <typename Base>
  parser::symbol_kind_type
  parser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


  template <typename Base>
  bool
  parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    value = YY_MOVE (s.value);
  }

  // by_kind.
  parser::by_kind::by_kind () YY_NOEXCEPT
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  parser::by_kind::by_kind (by_kind&& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  parser::by_kind::by_kind (const by_kind& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {}

  parser::by_kind::by_kind (token_kind_type t) YY_NOEXCEPT
    : kind_ (yytranslate_ (t))
  {}



  void
  parser::by_kind::clear () YY_NOEXCEPT
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  void
  parser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  parser::symbol_kind_type
  parser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }


  parser::symbol_kind_type
  parser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }



  // by_state.
  parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  parser::symbol_kind_type
  parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  parser::stack_symbol_type::stack_symbol_type ()
  {}

  parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.value))
  {
#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.value))
  {
    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    return *this;
  }

  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    YY_USE (yysym.kind ());
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " (";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  parser::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  parser::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  parser::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::operator() ()
  {
    return parse ();
  }

  int
  parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            yyla.kind_ = yytranslate_ (yylex (&yyla.value));
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

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
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* If YYLEN is nonzero, implement the default value of the
         action: '$$ = $1'.  Otherwise, use the top of the stack.

         Otherwise, the following line sets YYLHS.VALUE to garbage.
         This behavior is undocumented and Bison users should not rely
         upon it.  */
      if (yylen)
        yylhs.value = yystack_[yylen - 1].value;
      else
        yylhs.value = yystack_[0].value;


      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {

#line 578 "parser.tab.cc"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
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
        std::string msg = YY_("syntax error");
        error (YY_MOVE (msg));
      }


    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
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
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;


      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.what ());
  }

#if YYDEBUG || 0
  const char *
  parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytname_[yysymbol];
  }
#endif // #if YYDEBUG || 0









  const signed char parser::yypact_ninf_ = -59;

  const signed char parser::yytable_ninf_ = -100;

  const short
  parser::yypact_[] =
  {
      -5,    14,    20,   -59,    13,   -59,    -3,    19,    21,    29,
      31,   -18,   -59,   -59,   -59,   -59,    -2,   -41,    -1,   -59,
      -3,    38,     7,   179,    38,   -59,     5,    16,    23,   -59,
     -59,   -59,   -59,   -59,   -59,     8,     3,   -59,   -59,    15,
     -59,   -59,   -59,   -59,   179,    72,    33,    36,   179,   244,
     -59,   -59,   -59,   -59,   -59,   -59,   -59,    39,    46,     7,
      47,    38,     7,   179,   -59,   179,    30,   -59,   179,   179,
     228,   179,   179,   179,   179,   179,   179,   179,   179,    85,
     179,   179,   179,   179,   179,   -59,    38,   -59,     7,    82,
     -59,    43,   244,   244,    44,    52,   244,    53,    54,    55,
     -59,   260,   260,   260,    30,    30,   -44,   -44,   -44,   -59,
     260,   260,   260,   209,   273,   -59,   -59,    -6,   -59,   -59,
     179,   -59,   -59,   -59,    62,   172,   244,   -59,    57,   179,
     179,   179,   179,   179,    91,    74,    61,    64,   -59,   -59,
     -59,   -59,   -59,   -59,   179,    18,    93,   244,   -59,   109,
     178,   -59,   172,   179,   179,    75,   172,   172,   172,   110,
     -59,   244,   244,   231,   111,   106,   111,    63,   -10,   -59,
     -26,   -59,   172,   112,   -59,   114,   131,   172,   110,   115,
     172,   110,   -59,   -59,   -59,   -59,   -59,   -59,   -59,   -59,
     -59
  };

  const signed char
  parser::yydefact_[] =
  {
       3,     0,     0,     2,     0,     1,     5,     0,     0,     0,
       0,     6,     7,     9,    10,    11,     0,     0,     0,     4,
       0,    23,     0,     0,    37,     8,     0,     0,    24,    25,
      20,    16,    17,    18,    19,     0,    14,    68,    67,    65,
      69,    72,    73,    71,     0,     0,     0,     0,     0,    13,
      45,    46,    44,    41,    70,    42,    39,     0,    38,     0,
      28,     0,     0,     0,    12,   101,    48,    43,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    36,     0,    27,     0,     0,
      26,     0,    15,   103,     0,   102,     0,    44,    46,    44,
      47,    51,    53,    55,    57,    58,    59,    60,    61,    66,
      52,    54,    56,    49,    50,    40,    29,    30,    21,   100,
       0,    62,    64,    63,     0,    32,   104,    31,    65,     0,
       0,    97,     0,     0,     0,    33,    46,    44,    34,    74,
      75,    76,    77,    78,   101,     0,     0,    98,    96,     0,
       0,    22,     0,     0,     0,     0,    32,    32,    32,     0,
      35,    80,    79,   100,    84,     0,    84,    91,    93,    86,
       0,    89,    32,     0,    95,     0,     0,    32,     0,     0,
      32,     0,    85,    81,    82,    92,    94,    87,    83,    88,
      90
  };

  const signed char
  parser::yypgoto_[] =
  {
     -59,   -59,   -59,    24,   -59,   116,   -59,   -59,   -55,   -59,
     -59,   -59,   -22,   -59,   -59,    96,   -59,   -59,   -59,   -59,
     -23,   -59,   -40,   -58,   -59,   -59,   -17,   -59,   -59,   -28,
     -59,   -36,   -59,   -29,   -59,   -59,   -59,   -59,   -59,   -59,
      12,   -59
  };

  const unsigned char
  parser::yydefgoto_[] =
  {
       0,     2,     3,    10,    11,    12,    13,    64,    36,    14,
      27,    28,    29,    89,   125,   134,   135,    15,    57,    58,
      96,    50,    51,    52,    53,    54,   138,   139,   140,   173,
     168,   169,   170,   171,   179,   141,   142,   148,   143,    55,
      94,    95
  };

  const short
  parser::yytable_[] =
  {
      49,    22,    56,     1,    87,     7,     8,    91,     7,     8,
      97,    99,    30,    78,    79,   177,   180,   181,    23,     4,
       5,    66,     6,    20,    16,    70,    17,     9,    -5,    98,
       9,   178,   156,   116,    18,    31,    32,    33,    34,    90,
      92,    19,    93,    26,    35,    24,    21,    59,   101,   102,
     103,   104,   105,   106,   107,   108,    62,   110,   111,   112,
     113,   114,    63,    65,   115,    60,    61,   137,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    67,    80,    81,
      82,    68,    83,    84,    69,   136,    85,    86,    79,    88,
     109,   117,   118,   119,   137,   120,   127,   126,   137,   137,
     137,   151,   121,   122,   123,   144,   145,   146,   147,   149,
     150,   157,   136,   167,   137,   152,   136,   136,   136,   137,
     153,    93,   137,   154,   163,   174,   172,   158,   183,   176,
     161,   162,   136,   184,   185,   160,    25,   136,   175,   188,
     136,   124,   187,    71,    72,    73,    74,    75,    76,    77,
      78,    79,   190,    80,    81,    82,   155,    83,    84,    71,
      72,    73,    74,    75,    76,    77,    78,    79,     0,    80,
      81,    82,     0,    83,    84,    37,    38,   128,     0,    40,
       0,     0,    37,    38,    39,   129,    40,     0,     0,   130,
       0,     0,   131,   132,   133,     0,     0,     0,    41,    42,
       0,   159,     0,     0,    43,    41,    42,    44,    45,    46,
      47,    43,     0,     0,    44,    45,    46,    47,     0,     0,
      48,     0,     0,     0,     0,     0,     0,    48,    71,    72,
      73,    74,    75,    76,    77,    78,    79,     0,    80,    81,
      82,   -99,    83,    84,     0,     0,   -99,   -99,     0,     0,
     -99,     0,   164,   165,   166,   -99,   -99,     0,     0,    71,
      72,    73,    74,    75,    76,    77,    78,    79,   182,    80,
      81,    82,   -99,   186,    84,     0,   189,   100,    71,    72,
      73,    74,    75,    76,    77,    78,    79,     0,    80,    81,
      82,     0,    83,    84,    71,    72,    73,    74,    75,    76,
      77,    78,    79,     0,    80,    81,    82,     0,    83,    84,
    -100,  -100,  -100,    74,    75,    76,    77,    78,    79,     0,
    -100,  -100,  -100,    71,    72,    73,    74,    75,    76,    77,
      78,    79,     0,    80,    81,    82
  };

  const short
  parser::yycheck_[] =
  {
      23,    42,    24,     8,    59,    11,    12,    62,    11,    12,
      68,    69,     5,    57,    58,    25,    42,    43,    59,     5,
       0,    44,     9,    41,     5,    48,     5,    33,    34,    69,
      33,    41,    14,    88,     5,    28,    29,    30,    31,    61,
      63,    10,    65,     5,    37,    46,    48,    42,    71,    72,
      73,    74,    75,    76,    77,    78,    48,    80,    81,    82,
      83,    84,    59,    48,    86,    49,    43,   125,    50,    51,
      52,    53,    54,    55,    56,    57,    58,     5,    60,    61,
      62,    48,    64,    65,    48,   125,    47,    41,    58,    42,
       5,     9,    49,    49,   152,    43,    34,   120,   156,   157,
     158,    10,    49,    49,    49,    48,   129,   130,   131,   132,
     133,    18,   152,     3,   172,    41,   156,   157,   158,   177,
      59,   144,   180,    59,    49,    19,    15,    18,    16,    66,
     153,   154,   172,    19,     3,   152,    20,   177,   166,    24,
     180,   117,   178,    50,    51,    52,    53,    54,    55,    56,
      57,    58,   181,    60,    61,    62,   144,    64,    65,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    -1,    60,
      61,    62,    -1,    64,    65,     3,     4,     5,    -1,     7,
      -1,    -1,     3,     4,     5,    13,     7,    -1,    -1,    17,
      -1,    -1,    20,    21,    22,    -1,    -1,    -1,    26,    27,
      -1,    23,    -1,    -1,    32,    26,    27,    35,    36,    37,
      38,    32,    -1,    -1,    35,    36,    37,    38,    -1,    -1,
      48,    -1,    -1,    -1,    -1,    -1,    -1,    48,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    -1,    60,    61,
      62,    10,    64,    65,    -1,    -1,    15,    16,    -1,    -1,
      19,    -1,   156,   157,   158,    24,    25,    -1,    -1,    50,
      51,    52,    53,    54,    55,    56,    57,    58,   172,    60,
      61,    62,    41,   177,    65,    -1,   180,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    -1,    60,    61,
      62,    -1,    64,    65,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    -1,    60,    61,    62,    -1,    64,    65,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    -1,
      60,    61,    62,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    -1,    60,    61,    62
  };

  const signed char
  parser::yystos_[] =
  {
       0,     8,    68,    69,     5,     0,     9,    11,    12,    33,
      70,    71,    72,    73,    76,    84,     5,     5,     5,    10,
      41,    48,    42,    59,    46,    72,     5,    77,    78,    79,
       5,    28,    29,    30,    31,    37,    75,     3,     4,     5,
       7,    26,    27,    32,    35,    36,    37,    38,    48,    87,
      88,    89,    90,    91,    92,   106,    79,    85,    86,    42,
      49,    43,    48,    59,    74,    48,    87,     5,    48,    48,
      87,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      60,    61,    62,    64,    65,    47,    41,    75,    42,    80,
      79,    75,    87,    87,   107,   108,    87,    90,    89,    90,
      49,    87,    87,    87,    87,    87,    87,    87,    87,     5,
      87,    87,    87,    87,    87,    79,    75,     9,    49,    49,
      43,    49,    49,    49,    70,    81,    87,    34,     5,    13,
      17,    20,    21,    22,    82,    83,    89,    90,    93,    94,
      95,   102,   103,   105,    48,    87,    87,    87,   104,    87,
      87,    10,    41,    59,    59,   107,    14,    18,    18,    23,
      93,    87,    87,    49,    82,    82,    82,     3,    97,    98,
      99,   100,    15,    96,    19,    96,    66,    25,    41,   101,
      42,    43,    82,    16,    19,     3,    82,    98,    24,    82,
     100
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    67,    68,    68,    69,    70,    70,    71,    71,    72,
      72,    72,    73,    73,    74,    74,    75,    75,    75,    75,
      75,    75,    76,    77,    77,    78,    78,    79,    80,    80,
      81,    81,    82,    82,    83,    83,    84,    85,    85,    86,
      86,    87,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    88,    89,    89,    90,    90,    91,    91,    91,
      91,    91,    92,    92,    93,    93,    93,    93,    93,    94,
      94,    95,    95,    95,    96,    96,    97,    97,    98,    99,
      99,   100,   100,   101,   101,   102,   103,   104,   104,   105,
     106,   107,   107,   108,   108
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     0,     5,     0,     1,     1,     3,     1,
       1,     1,     5,     4,     0,     2,     1,     1,     1,     1,
       1,     4,    10,     0,     1,     1,     3,     3,     0,     2,
       0,     2,     0,     1,     1,     3,     5,     0,     1,     1,
       3,     1,     1,     2,     1,     1,     1,     3,     2,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     4,     4,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       3,     6,     6,     6,     0,     2,     1,     3,     3,     1,
       3,     1,     3,     0,     2,     5,     2,     0,     1,     4,
       4,     0,     1,     1,     3
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "INT_LITERAL",
  "FLOAT_LITERAL", "A_NAME", "A_LINE", "STRING_LITERAL", "A_PROGRAM",
  "A_BEGIN", "A_END", "A_PROCEDURE", "A_VAR", "A_IF", "A_THEN", "A_ELSE",
  "A_FI", "A_WHILE", "A_DO", "A_OD", "A_RETURN", "A_UNLESS", "A_CASE",
  "A_OF", "A_ESAC", "A_OTHERWISE", "A_TRUE", "A_FALSE", "A_FLOAT", "A_INT",
  "A_STRING", "A_BOOL", "A_NULL", "A_STRUCT", "A_IN", "A_NOT", "A_NEW",
  "A_REF", "A_DEREF", "A_U_MINUS", "A_U_PLUS", "';'", "':'", "','", "'['",
  "']'", "'{'", "'}'", "'('", "')'", "'<'", "'>'", "'='", "'+'", "'-'",
  "'*'", "'/'", "'^'", "'.'", "A_ASSIGN", "A_LESS_THAN_EQUAL",
  "A_GREATER_THAN_EQUAL", "A_DIFFERENT", "A_EQUAL", "A_OR_LOGIC",
  "A_AND_LOGIC", "A_RANGE", "$accept", "main", "program_prod",
  "optional_declaration_list", "declaration_list", "declaration",
  "var_declaration", "optional_assign_exp", "type_spec",
  "proc_declaration", "optional_param_list", "param_list",
  "paramfield_decl", "optional_return_type",
  "optional_proc_decls_in_block", "stmt_list", "stmt_sequence",
  "rec_declaration", "optional_rec_field_list", "rec_field_list", "exp",
  "ref_var", "deref_var", "var_access", "literal", "bool_literal", "stmt",
  "assign_stmt", "if_stmt", "optional_else_clause", "case_list",
  "case_clause", "case_label_list", "case_label_element",
  "optional_otherwise_clause", "while_stmt", "return_stmt",
  "optional_exp_val", "call_stmt", "call_stmt_as_exp", "optional_arg_list",
  "arg_list", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,    51,    51,    52,    56,    59,    61,    65,    66,    70,
      71,    72,    76,    77,    80,    82,    86,    87,    88,    89,
      90,    91,    95,    99,   101,   105,   106,   110,   113,   115,
     118,   120,   123,   125,   129,   130,   134,   137,   139,   143,
     144,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   161,   162,   163,   164,   165,   166,
     167,   168,   172,   176,   177,   181,   182,   187,   188,   189,
     190,   191,   195,   196,   200,   201,   202,   203,   204,   208,
     209,   213,   214,   215,   218,   220,   224,   225,   229,   233,
     234,   238,   239,   242,   244,   248,   252,   255,   257,   261,
     265,   269,   271,   275,   276
  };

  void
  parser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  parser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  parser::symbol_kind_type
  parser::yytranslate_ (int t) YY_NOEXCEPT
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const signed char
    translate_table[] =
    {
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      48,    49,    55,    53,    43,    54,    58,    56,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    42,    41,
      50,    52,    51,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    44,     2,    45,    57,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    46,     2,    47,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    59,    60,    61,    62,
      63,    64,    65,    66
    };
    // Last valid token kind.
    const int code_max = 303;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return static_cast <symbol_kind_type> (translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

} // yy
#line 1107 "parser.tab.cc"

#line 279 "parser.y"
 // Fim das Regras Gramaticais

int main() {
	yyin = stdin;
	do {
		yyparse();
	} while(!feof(yyin));

	return 0;
}

void yy::parser::error(const std::string &message)
{
    std::cerr << "Error: " << message << std::endl;
}
