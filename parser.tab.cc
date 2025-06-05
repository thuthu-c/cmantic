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
#line 22 "parser.y"

    #include "custom_lexer.hpp"
    #define yylex lexer.yylex

#line 51 "parser.tab.cc"


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
#line 124 "parser.tab.cc"

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
    switch (yysym.kind ())
    {
      case symbol_kind::S_A_NAME: // A_NAME
#line 57 "parser.y"
                    { delete (yysym.value.sval); }
#line 330 "parser.tab.cc"
        break;

      case symbol_kind::S_A_STRING_LITERAL: // A_STRING_LITERAL
#line 57 "parser.y"
                    { delete (yysym.value.sval); }
#line 336 "parser.tab.cc"
        break;

      default:
        break;
    }
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
  case 4: // $@1: %empty
#line 69 "parser.y"
                       { std::cout << "Parsing program: " << *(yystack_[0].value.sval) << std::endl; delete (yystack_[0].value.sval); }
#line 597 "parser.tab.cc"
    break;


#line 601 "parser.tab.cc"

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









  const signed char parser::yypact_ninf_ = -60;

  const signed char parser::yytable_ninf_ = -101;

  const short
  parser::yypact_[] =
  {
      -7,     7,    17,   -60,   -60,   -60,     9,     8,    19,    21,
      22,    12,     3,   -60,   -60,   -60,   -60,    -5,   -37,    -1,
     -60,     8,    41,     1,   213,    41,   -60,     5,    13,    23,
     -60,   -60,   -60,   -60,   -60,   -60,    15,    -4,   -60,   -60,
      31,   -60,   -60,   -60,   -60,   213,    60,    32,    39,   213,
     247,   -60,   -60,   -60,   -60,   -60,   -60,   -60,    42,    27,
       1,    46,    41,     1,   213,   -60,   213,    11,   -60,   213,
     213,   230,   213,   213,   213,   213,   213,   213,   213,   213,
      85,   213,   213,   213,   213,   213,   -60,    41,   -60,     1,
      82,   -60,    43,   247,   247,    44,    51,   247,    52,    53,
      54,   -60,   281,   281,   281,    11,    11,   -49,   -49,   -49,
     -60,   281,   281,   281,   264,   295,   -60,   -60,     2,   -60,
     -60,   213,   -60,   -60,   -60,    61,   188,   247,   -60,    56,
     213,   213,   213,   213,   213,    95,   -60,    66,    68,    70,
     -60,   -60,   -60,   -60,   -60,   213,    20,   107,   247,   -60,
     124,   212,   -60,   213,   213,   188,    63,   188,   188,   188,
     117,   247,   247,   -60,   108,   119,   116,   119,    71,   -22,
     -60,   -27,   -60,   188,   121,   -60,   122,   137,   188,   117,
     120,   188,   117,   -60,   -60,   -60,   -60,   -60,   -60,   -60,
     -60,   -60
  };

  const signed char
  parser::yydefact_[] =
  {
       3,     0,     0,     2,     4,     1,     0,     6,     0,     0,
       0,     0,     7,     8,    10,    11,    12,     0,     0,     0,
       5,     0,    24,     0,     0,    38,     9,     0,     0,    25,
      26,    21,    17,    18,    19,    20,     0,    15,    69,    68,
      66,    70,    73,    74,    72,     0,     0,     0,     0,     0,
      14,    46,    47,    45,    42,    71,    43,    40,     0,    39,
       0,    29,     0,     0,     0,    13,   102,    49,    44,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    37,     0,    28,     0,
       0,    27,     0,    16,   104,     0,   103,     0,    45,    47,
      45,    48,    52,    54,    56,    58,    59,    60,    61,    62,
      67,    53,    55,    57,    50,    51,    41,    30,    31,    22,
     101,     0,    63,    65,    64,     0,    33,   105,    32,    66,
       0,     0,    98,     0,     0,     0,    34,    47,    45,    35,
      75,    76,    77,    78,    79,   102,     0,     0,    99,    97,
       0,     0,    23,     0,     0,     0,     0,    33,    33,    33,
       0,    81,    80,    36,   101,    85,     0,    85,    92,    94,
      87,     0,    90,    33,     0,    96,     0,     0,    33,     0,
       0,    33,     0,    86,    82,    83,    93,    95,    88,    84,
      89,    91
  };

  const signed char
  parser::yypgoto_[] =
  {
     -60,   -60,   -60,   -60,    25,   -60,   125,   -60,   -60,   -56,
     -60,   -60,   -60,   -23,   -60,   -60,    74,   -10,   -60,   -60,
     -60,   -24,   -60,   -42,   -59,   -60,   -60,   -60,   -60,   -60,
     -20,   -60,   -31,   -60,   -32,   -60,   -60,   -60,   -60,   -60,
     -60,     6,   -60
  };

  const unsigned char
  parser::yydefgoto_[] =
  {
       0,     2,     3,     6,    11,    12,    13,    14,    65,    37,
      15,    28,    29,    30,    90,   126,   135,   136,    16,    58,
      59,    97,    51,    52,    53,    54,    55,   139,   140,   141,
     174,   169,   170,   171,   172,   180,   142,   143,   149,   144,
      56,    95,    96
  };

  const short
  parser::yytable_[] =
  {
      50,     1,    57,   178,    88,    23,    31,    92,    79,    80,
      98,   100,     4,     8,     9,   181,   182,     5,     7,     8,
       9,    67,    20,    24,    17,    71,    18,    19,    99,    32,
      33,    34,    35,   117,   157,    10,    -6,   179,    36,    91,
      93,    10,    94,    22,    21,    25,    27,    60,   102,   103,
     104,   105,   106,   107,   108,   109,    64,   111,   112,   113,
     114,   115,    61,    63,   116,    68,    62,   138,    87,    80,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    66,
      69,    81,    82,    83,   137,    84,    85,    70,    89,    86,
     110,   118,   119,   120,   121,   128,   138,   127,   138,   138,
     138,   122,   123,   124,   145,   152,   146,   147,   148,   150,
     151,   155,   164,   137,   138,   137,   137,   137,  -100,   138,
     168,    94,   138,  -100,  -100,   158,   153,  -100,   154,   161,
     162,   137,  -100,  -100,   173,   175,   137,   184,   177,   137,
     186,   185,   159,   125,   189,   163,    26,   176,   188,  -100,
     191,   156,     0,     0,     0,     0,     0,    72,    73,    74,
      75,    76,    77,    78,    79,    80,     0,  -100,    81,    82,
      83,     0,    84,    85,    72,    73,    74,    75,    76,    77,
      78,    79,    80,     0,     0,    81,    82,    83,     0,    84,
      85,    38,    39,   129,    41,     0,     0,     0,     0,     0,
       0,   130,     0,     0,     0,   131,     0,     0,   132,   133,
     134,     0,     0,     0,    42,    43,    38,    39,    40,    41,
      44,     0,     0,    45,    46,    47,    48,     0,     0,     0,
       0,   165,   166,   167,     0,   160,    49,     0,     0,    42,
      43,     0,     0,     0,     0,    44,     0,   183,    45,    46,
      47,    48,   187,     0,     0,   190,     0,     0,     0,     0,
       0,    49,    72,    73,    74,    75,    76,    77,    78,    79,
      80,     0,     0,    81,    82,    83,     0,    84,    85,   101,
      72,    73,    74,    75,    76,    77,    78,    79,    80,     0,
       0,    81,    82,    83,     0,    84,    85,    72,    73,    74,
      75,    76,    77,    78,    79,    80,     0,     0,    81,    82,
      83,     0,    84,    85,    72,    73,    74,    75,    76,    77,
      78,    79,    80,     0,     0,    81,    82,    83,     0,     0,
      85,  -101,  -101,  -101,    75,    76,    77,    78,    79,    80,
       0,     0,  -101,  -101,  -101,    72,    73,    74,    75,    76,
      77,    78,    79,    80,     0,     0,    81,    82,    83
  };

  const short
  parser::yycheck_[] =
  {
      24,     8,    25,    25,    60,    42,     5,    63,    57,    58,
      69,    70,     5,    11,    12,    42,    43,     0,     9,    11,
      12,    45,    10,    60,     5,    49,     5,     5,    70,    28,
      29,    30,    31,    89,    14,    33,    34,    59,    37,    62,
      64,    33,    66,    48,    41,    46,     5,    42,    72,    73,
      74,    75,    76,    77,    78,    79,    60,    81,    82,    83,
      84,    85,    49,    48,    87,     5,    43,   126,    41,    58,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    48,
      48,    61,    62,    63,   126,    65,    66,    48,    42,    47,
       5,     9,    49,    49,    43,    34,   155,   121,   157,   158,
     159,    49,    49,    49,    48,    10,   130,   131,   132,   133,
     134,    41,    49,   155,   173,   157,   158,   159,    10,   178,
       3,   145,   181,    15,    16,    18,    60,    19,    60,   153,
     154,   173,    24,    25,    15,    19,   178,    16,    67,   181,
       3,    19,    18,   118,    24,   155,    21,   167,   179,    41,
     182,   145,    -1,    -1,    -1,    -1,    -1,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    -1,    59,    61,    62,
      63,    -1,    65,    66,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    -1,    -1,    61,    62,    63,    -1,    65,
      66,     3,     4,     5,     6,    -1,    -1,    -1,    -1,    -1,
      -1,    13,    -1,    -1,    -1,    17,    -1,    -1,    20,    21,
      22,    -1,    -1,    -1,    26,    27,     3,     4,     5,     6,
      32,    -1,    -1,    35,    36,    37,    38,    -1,    -1,    -1,
      -1,   157,   158,   159,    -1,    23,    48,    -1,    -1,    26,
      27,    -1,    -1,    -1,    -1,    32,    -1,   173,    35,    36,
      37,    38,   178,    -1,    -1,   181,    -1,    -1,    -1,    -1,
      -1,    48,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    -1,    -1,    61,    62,    63,    -1,    65,    66,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    -1,
      -1,    61,    62,    63,    -1,    65,    66,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    -1,    -1,    61,    62,
      63,    -1,    65,    66,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    -1,    -1,    61,    62,    63,    -1,    -1,
      66,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      -1,    -1,    61,    62,    63,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    -1,    -1,    61,    62,    63
  };

  const signed char
  parser::yystos_[] =
  {
       0,     8,    69,    70,     5,     0,    71,     9,    11,    12,
      33,    72,    73,    74,    75,    78,    86,     5,     5,     5,
      10,    41,    48,    42,    60,    46,    74,     5,    79,    80,
      81,     5,    28,    29,    30,    31,    37,    77,     3,     4,
       5,     6,    26,    27,    32,    35,    36,    37,    38,    48,
      89,    90,    91,    92,    93,    94,   108,    81,    87,    88,
      42,    49,    43,    48,    60,    76,    48,    89,     5,    48,
      48,    89,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    61,    62,    63,    65,    66,    47,    41,    77,    42,
      82,    81,    77,    89,    89,   109,   110,    89,    92,    91,
      92,    49,    89,    89,    89,    89,    89,    89,    89,    89,
       5,    89,    89,    89,    89,    89,    81,    77,     9,    49,
      49,    43,    49,    49,    49,    72,    83,    89,    34,     5,
      13,    17,    20,    21,    22,    84,    85,    91,    92,    95,
      96,    97,   104,   105,   107,    48,    89,    89,    89,   106,
      89,    89,    10,    60,    60,    41,   109,    14,    18,    18,
      23,    89,    89,    85,    49,    84,    84,    84,     3,    99,
     100,   101,   102,    15,    98,    19,    98,    67,    25,    59,
     103,    42,    43,    84,    16,    19,     3,    84,   100,    24,
      84,   102
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    68,    69,    69,    71,    70,    72,    72,    73,    73,
      74,    74,    74,    75,    75,    76,    76,    77,    77,    77,
      77,    77,    77,    78,    79,    79,    80,    80,    81,    82,
      82,    83,    83,    84,    84,    85,    85,    86,    87,    87,
      88,    88,    89,    89,    89,    89,    89,    89,    89,    89,
      89,    89,    89,    89,    89,    89,    89,    89,    89,    89,
      89,    89,    89,    90,    91,    91,    92,    92,    93,    93,
      93,    93,    93,    94,    94,    95,    95,    95,    95,    95,
      96,    96,    97,    97,    97,    98,    98,    99,    99,   100,
     101,   101,   102,   102,   103,   103,   104,   105,   106,   106,
     107,   108,   109,   109,   110,   110
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     0,     0,     6,     0,     1,     1,     3,
       1,     1,     1,     5,     4,     0,     2,     1,     1,     1,
       1,     1,     4,    10,     0,     1,     1,     3,     3,     0,
       2,     0,     2,     0,     1,     1,     3,     5,     0,     1,
       1,     3,     1,     1,     2,     1,     1,     1,     3,     2,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     4,     4,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     3,     6,     6,     6,     0,     2,     1,     3,     3,
       1,     3,     1,     3,     0,     2,     5,     2,     0,     1,
       4,     4,     0,     1,     1,     3
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "A_INT_LITERAL",
  "A_FLOAT_LITERAL", "A_NAME", "A_STRING_LITERAL", "A_LINE", "A_PROGRAM",
  "A_BEGIN", "A_END", "A_PROCEDURE", "A_VAR", "A_IF", "A_THEN", "A_ELSE",
  "A_FI", "A_WHILE", "A_DO", "A_OD", "A_RETURN", "A_UNLESS", "A_CASE",
  "A_OF", "A_ESAC", "A_OTHERWISE", "A_TRUE", "A_FALSE", "A_FLOAT", "A_INT",
  "A_STRING", "A_BOOL", "A_NULL", "A_STRUCT", "A_IN", "A_NOT", "A_NEW",
  "A_REF", "A_DEREF", "A_U_MINUS", "A_U_PLUS", "';'", "':'", "','", "'['",
  "']'", "'{'", "'}'", "'('", "')'", "'<'", "'>'", "'='", "'+'", "'-'",
  "'*'", "'/'", "'^'", "'.'", "'|'", "A_ASSIGN", "A_LESS_THAN_EQUAL",
  "A_GREATER_THAN_EQUAL", "A_DIFFERENT", "A_EQUAL", "A_OR_LOGIC",
  "A_AND_LOGIC", "A_RANGE", "$accept", "main", "program_prod", "$@1",
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
       0,    64,    64,    65,    69,    69,    73,    75,    79,    80,
      84,    85,    86,    90,    91,    94,    96,   100,   101,   102,
     103,   104,   105,   109,   113,   115,   119,   120,   124,   127,
     129,   132,   134,   137,   139,   143,   144,   148,   151,   153,
     157,   158,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   181,   182,   186,   190,   191,   195,   196,   201,   202,
     203,   204,   205,   209,   210,   214,   215,   216,   217,   218,
     222,   223,   227,   228,   229,   232,   234,   238,   239,   243,
     247,   248,   252,   253,   256,   258,   262,   266,   269,   271,
     275,   279,   283,   285,   289,   290
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
       2,     2,     2,    46,    59,    47,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    60,    61,    62,    63,
      64,    65,    66,    67
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
#line 1134 "parser.tab.cc"

#line 293 "parser.y"
 // Fim das Regras Gramaticais

void yy::parser::error(const std::string &message)
{
    std::cerr << "Error: " << message << std::endl;
}
