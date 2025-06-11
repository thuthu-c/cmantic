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
#line 23 "parser.y"

    #include "custom_lexer.hpp"
    #define yylex lexer.yylex

    SymbolTable symbol_table;

#line 53 "parser.tab.cc"


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
#line 126 "parser.tab.cc"

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
#line 68 "parser.y"
                    { delete (yysym.value.sval); }
#line 332 "parser.tab.cc"
        break;

      case symbol_kind::S_A_STRING_LITERAL: // A_STRING_LITERAL
#line 68 "parser.y"
                    { delete (yysym.value.sval); }
#line 338 "parser.tab.cc"
        break;

      case symbol_kind::S_optional_assign_exp: // optional_assign_exp
#line 68 "parser.y"
                    { delete (yysym.value.type_val); }
#line 344 "parser.tab.cc"
        break;

      case symbol_kind::S_type_spec: // type_spec
#line 68 "parser.y"
                    { delete (yysym.value.type_val); }
#line 350 "parser.tab.cc"
        break;

      case symbol_kind::S_optional_param_list: // optional_param_list
#line 68 "parser.y"
                    { delete (yysym.value.param_vec); }
#line 356 "parser.tab.cc"
        break;

      case symbol_kind::S_param_list: // param_list
#line 68 "parser.y"
                    { delete (yysym.value.param_vec); }
#line 362 "parser.tab.cc"
        break;

      case symbol_kind::S_paramfield_decl: // paramfield_decl
#line 68 "parser.y"
                    { delete (yysym.value.param_vec); }
#line 368 "parser.tab.cc"
        break;

      case symbol_kind::S_optional_return_type: // optional_return_type
#line 68 "parser.y"
                    { delete (yysym.value.type_val); }
#line 374 "parser.tab.cc"
        break;

      case symbol_kind::S_optional_rec_field_list: // optional_rec_field_list
#line 68 "parser.y"
                    { delete (yysym.value.param_vec); }
#line 380 "parser.tab.cc"
        break;

      case symbol_kind::S_rec_field_list: // rec_field_list
#line 68 "parser.y"
                    { delete (yysym.value.param_vec); }
#line 386 "parser.tab.cc"
        break;

      case symbol_kind::S_exp: // exp
#line 68 "parser.y"
                    { delete (yysym.value.type_val); }
#line 392 "parser.tab.cc"
        break;

      case symbol_kind::S_ref_var: // ref_var
#line 68 "parser.y"
                    { delete (yysym.value.type_val); }
#line 398 "parser.tab.cc"
        break;

      case symbol_kind::S_deref_var: // deref_var
#line 68 "parser.y"
                    { delete (yysym.value.type_val); }
#line 404 "parser.tab.cc"
        break;

      case symbol_kind::S_var_access: // var_access
#line 68 "parser.y"
                    { delete (yysym.value.type_val); }
#line 410 "parser.tab.cc"
        break;

      case symbol_kind::S_literal: // literal
#line 68 "parser.y"
                    { delete (yysym.value.type_val); }
#line 416 "parser.tab.cc"
        break;

      case symbol_kind::S_bool_literal: // bool_literal
#line 68 "parser.y"
                    { delete (yysym.value.type_val); }
#line 422 "parser.tab.cc"
        break;

      case symbol_kind::S_optional_exp_val: // optional_exp_val
#line 68 "parser.y"
                    { delete (yysym.value.type_val); }
#line 428 "parser.tab.cc"
        break;

      case symbol_kind::S_call_stmt_as_exp: // call_stmt_as_exp
#line 68 "parser.y"
                    { delete (yysym.value.type_val); }
#line 434 "parser.tab.cc"
        break;

      case symbol_kind::S_optional_arg_list: // optional_arg_list
#line 69 "parser.y"
                    { if ((yysym.value.type_vec)) { for(auto p : *(yysym.value.type_vec)) delete p; delete (yysym.value.type_vec); } }
#line 440 "parser.tab.cc"
        break;

      case symbol_kind::S_arg_list: // arg_list
#line 69 "parser.y"
                    { if ((yysym.value.type_vec)) { for(auto p : *(yysym.value.type_vec)) delete p; delete (yysym.value.type_vec); } }
#line 446 "parser.tab.cc"
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
#line 81 "parser.y"
                     { std::cout << "Parsing program: " << *(yystack_[0].value.sval) << std::endl; delete (yystack_[0].value.sval); }
#line 707 "parser.tab.cc"
    break;

  case 5: // program_prod: A_PROGRAM A_NAME $@1 A_BEGIN optional_declaration_list A_END
#line 82 "parser.y"
                                            { symbol_table.print(); }
#line 713 "parser.tab.cc"
    break;

  case 13: // var_declaration: A_VAR A_NAME ':' type_spec optional_assign_exp
#line 103 "parser.y"
    {
      if (symbol_table.lookup_current_scope_only(*(yystack_[3].value.sval))) {
        error("Variavel '" + *(yystack_[3].value.sval) + "' ja declarada neste escopo.");
      } else {
        bool types_are_ok = true;
        if ((yystack_[0].value.type_val)) {
          if (!are_types_compatible(*(yystack_[1].value.type_val), *(yystack_[0].value.type_val))) {
              std::string declared_type = type_to_string(*(yystack_[1].value.type_val));
              std::string assigned_type = type_to_string(*(yystack_[0].value.type_val));
              error("Incompatibilidade de tipos para a variável '" + *(yystack_[3].value.sval) +
                    "'. Tipo declarado: " + declared_type +
                    ", mas o tipo da expressão atribuída é:: " + assigned_type + ".");
              types_are_ok = false;
          }
        }

        if (types_are_ok) {
          Variable var_content{*(yystack_[1].value.type_val)};
          Symbol new_symbol{*(yystack_[3].value.sval), SymbolCategory::VARIABLE, var_content};
          symbol_table.insert_symbol(*(yystack_[3].value.sval), new_symbol);
        }
      }
      delete (yystack_[3].value.sval);
      delete (yystack_[1].value.type_val);
      if ((yystack_[0].value.type_val)) delete (yystack_[0].value.type_val);
    }
#line 744 "parser.tab.cc"
    break;

  case 14: // var_declaration: A_VAR A_NAME A_ASSIGN exp
#line 130 "parser.y"
      {
        if (symbol_table.lookup_current_scope_only(*(yystack_[2].value.sval))) {
          error("Variavel '" + *(yystack_[2].value.sval) + "' ja declarada neste escopo.");
          delete (yystack_[0].value.type_val);
        } else {
          Variable var_content{*(yystack_[0].value.type_val)};
          Symbol new_symbol{*(yystack_[2].value.sval), SymbolCategory::VARIABLE, var_content};
          symbol_table.insert_symbol(*(yystack_[2].value.sval), new_symbol);
        }
        delete (yystack_[2].value.sval);
        delete (yystack_[0].value.type_val);
      }
#line 761 "parser.tab.cc"
    break;

  case 15: // optional_assign_exp: %empty
#line 145 "parser.y"
                { (yylhs.value.type_val) = nullptr; }
#line 767 "parser.tab.cc"
    break;

  case 16: // optional_assign_exp: A_ASSIGN exp
#line 146 "parser.y"
                   { (yylhs.value.type_val) = (yystack_[0].value.type_val); }
#line 773 "parser.tab.cc"
    break;

  case 17: // type_spec: A_FLOAT
#line 150 "parser.y"
            { (yylhs.value.type_val) = new VarType{PrimitiveType::FLOAT}; }
#line 779 "parser.tab.cc"
    break;

  case 18: // type_spec: A_INT
#line 151 "parser.y"
            { (yylhs.value.type_val) = new VarType{PrimitiveType::INT}; }
#line 785 "parser.tab.cc"
    break;

  case 19: // type_spec: A_STRING
#line 152 "parser.y"
               { (yylhs.value.type_val) = new VarType{PrimitiveType::STRING}; }
#line 791 "parser.tab.cc"
    break;

  case 20: // type_spec: A_BOOL
#line 153 "parser.y"
             { (yylhs.value.type_val) = new VarType{PrimitiveType::BOOL}; }
#line 797 "parser.tab.cc"
    break;

  case 21: // type_spec: A_NAME
#line 155 "parser.y"
    {
      Symbol* s = symbol_table.lookup(*(yystack_[0].value.sval));
      if (!s || s->category != SymbolCategory::RECORD) {
        error("Tipo '" + *(yystack_[0].value.sval) + "' nao eh um tipo de struct valido.");
        (yylhs.value.type_val) = new VarType{PrimitiveType::UNDEFINED};
      } else {
        (yylhs.value.type_val) = new VarType{PrimitiveType::NOT_PRIMITIVE, *(yystack_[0].value.sval)};
      }
      delete (yystack_[0].value.sval);
    }
#line 812 "parser.tab.cc"
    break;

  case 22: // type_spec: A_REF '(' type_spec ')'
#line 166 "parser.y"
      {
        auto referenced_type = std::make_unique<VarType>(*(yystack_[1].value.type_val));
        (yylhs.value.type_val) = new VarType(PrimitiveType::REF, std::move(referenced_type));
        delete (yystack_[1].value.type_val);
      }
#line 822 "parser.tab.cc"
    break;

  case 23: // proc_declaration: A_PROCEDURE A_NAME '(' optional_param_list ')' optional_return_type A_BEGIN optional_proc_decls_in_block stmt_list A_END
#line 176 "parser.y"
      {
        std::vector<ParamField>* params = *(yystack_[6].value.param_vec);

        if (symbol_table.lookup_current_scope_only(*(yystack_[8].value.sval))) {
            error("Procedimento '" + *(yystack_[8].value.sval) + "' já declarado neste escopo.");
        } else {
            Procedure proc_content;
            proc_content.params = *params;
            proc_content.return_type = (yystack_[4].value.type_val) ? *(yystack_[4].value.type_val) : VarType{PrimitiveType::VOID};
            Symbol proc_symbol{*(yystack_[8].value.sval), SymbolCategory::PROCEDURE, proc_content};
            symbol_table.insert_symbol(*(yystack_[8].value.sval), proc_symbol);
        }

        delete (yystack_[8].value.sval);
        delete params;
        if ((yystack_[4].value.type_val)) delete (yystack_[4].value.type_val);
      }
#line 844 "parser.tab.cc"
    break;

  case 24: // optional_param_list: %empty
#line 196 "parser.y"
                 { (yylhs.value.param_vec) = new std::vector<ParamField>(); }
#line 850 "parser.tab.cc"
    break;

  case 25: // optional_param_list: param_list
#line 197 "parser.y"
                 { (yylhs.value.param_vec) = (yystack_[0].value.param_vec); }
#line 856 "parser.tab.cc"
    break;

  case 26: // param_list: paramfield_decl
#line 201 "parser.y"
                    { (yylhs.value.param_vec) = (yystack_[0].value.param_vec); }
#line 862 "parser.tab.cc"
    break;

  case 27: // param_list: param_list ',' paramfield_decl
#line 202 "parser.y"
                                     { (yystack_[2].value.param_vec)->insert((yystack_[2].value.param_vec)->end(), (yystack_[0].value.param_vec)->begin(), (yystack_[0].value.param_vec)->end()); delete (yystack_[0].value.param_vec); (yylhs.value.param_vec) = (yystack_[2].value.param_vec); }
#line 868 "parser.tab.cc"
    break;

  case 28: // paramfield_decl: A_NAME ':' type_spec
#line 206 "parser.y"
                         { (yylhs.value.param_vec) = new std::vector<ParamField>{{*(yystack_[2].value.sval), *(yystack_[0].value.type_val)}}; delete (yystack_[2].value.sval); delete (yystack_[0].value.type_val); }
#line 874 "parser.tab.cc"
    break;

  case 29: // optional_return_type: %empty
#line 210 "parser.y"
                { (yylhs.value.type_val) = nullptr; }
#line 880 "parser.tab.cc"
    break;

  case 30: // optional_return_type: ':' type_spec
#line 211 "parser.y"
                    { (yylhs.value.type_val) = (yystack_[0].value.type_val); }
#line 886 "parser.tab.cc"
    break;

  case 37: // rec_declaration: A_STRUCT A_NAME '{' optional_rec_field_list '}'
#line 231 "parser.y"
    {
      if (symbol_table.lookup_current_scope_only(*(yystack_[3].value.sval))) {
          error("Tipo de struct '" + *(yystack_[3].value.sval) + "' já definido neste escopo.");
      } else {
          Record rec_content{*(yystack_[1].value.param_vec)};
          Symbol new_symbol{*(yystack_[3].value.sval), SymbolCategory::RECORD, rec_content};
          symbol_table.insert_symbol(*(yystack_[3].value.sval), new_symbol);
      }
      delete (yystack_[3].value.sval);
      delete (yystack_[1].value.param_vec);
    }
#line 902 "parser.tab.cc"
    break;

  case 38: // optional_rec_field_list: %empty
#line 245 "parser.y"
                { (yylhs.value.param_vec) = new std::vector<ParamField>(); }
#line 908 "parser.tab.cc"
    break;

  case 39: // optional_rec_field_list: rec_field_list
#line 246 "parser.y"
                     { (yylhs.value.param_vec) = (yystack_[0].value.param_vec); }
#line 914 "parser.tab.cc"
    break;

  case 40: // rec_field_list: paramfield_decl
#line 250 "parser.y"
    { (yylhs.value.param_vec) = (yystack_[0].value.param_vec); }
#line 920 "parser.tab.cc"
    break;

  case 41: // rec_field_list: rec_field_list ';' paramfield_decl
#line 251 "parser.y"
                                         { (yystack_[2].value.param_vec)->insert((yystack_[2].value.param_vec)->end(), (yystack_[0].value.param_vec)->begin(), (yystack_[0].value.param_vec)->end()); delete (yystack_[0].value.param_vec); (yylhs.value.param_vec) = (yystack_[2].value.param_vec); }
#line 926 "parser.tab.cc"
    break;

  case 42: // exp: literal
#line 255 "parser.y"
             { (yylhs.value.type_val) = (yystack_[0].value.type_val); }
#line 932 "parser.tab.cc"
    break;

  case 43: // exp: call_stmt_as_exp
#line 256 "parser.y"
                       { (yylhs.value.type_val) = (yystack_[0].value.type_val); }
#line 938 "parser.tab.cc"
    break;

  case 44: // exp: A_NEW A_NAME
#line 258 "parser.y"
    {
      Symbol* s = symbol_table.lookup(*(yystack_[0].value.sval));
      if (!s || s->category != SymbolCategory::RECORD) {
          error("Tipo '" + *(yystack_[0].value.sval) + "' não é um tipo de registro válido para 'new'.");
          (yylhs.value.type_val) = new VarType{PrimitiveType::UNDEFINED};
      } else {
          (yylhs.value.type_val) = new VarType{PrimitiveType::NOT_PRIMITIVE, *(yystack_[0].value.sval)};
      }
      delete (yystack_[0].value.sval);
    }
#line 953 "parser.tab.cc"
    break;

  case 45: // exp: var_access
#line 268 "parser.y"
                 { (yylhs.value.type_val) = (yystack_[0].value.type_val); }
#line 959 "parser.tab.cc"
    break;

  case 46: // exp: ref_var
#line 269 "parser.y"
              { (yylhs.value.type_val) = (yystack_[0].value.type_val); }
#line 965 "parser.tab.cc"
    break;

  case 47: // exp: deref_var
#line 270 "parser.y"
                { (yylhs.value.type_val) = (yystack_[0].value.type_val); }
#line 971 "parser.tab.cc"
    break;

  case 48: // exp: '(' exp ')'
#line 271 "parser.y"
                  { (yylhs.value.type_val) = (yystack_[1].value.type_val); }
#line 977 "parser.tab.cc"
    break;

  case 49: // exp: A_NOT exp
#line 273 "parser.y"
    {
        if ((yystack_[0].value.type_val)->p_type != PrimitiveType::BOOL) {
            error("Operador 'not' requer um operando booleano, mas obteve " + type_to_string(*(yystack_[0].value.type_val)) + ".");
        }
        delete (yystack_[0].value.type_val);
        (yylhs.value.type_val) = new VarType{PrimitiveType::BOOL};
    }
#line 989 "parser.tab.cc"
    break;

  case 50: // exp: '-' exp
#line 281 "parser.y"
    {
      if (!(yystack_[0].value.type_val) || ((yystack_[0].value.type_val)->p_type != PrimitiveType::INT && (yystack_[0].value.type_val)->p_type != PrimitiveType::FLOAT)) {
          error("Operador unário '-' requer operando numérico. Foi: " + type_to_string(*(yystack_[0].value.type_val)) + ".");
          (yylhs.value.type_val) = new VarType{PrimitiveType::UNDEFINED};
          delete (yystack_[0].value.type_val);
      } else {
          (yylhs.value.type_val) = (yystack_[0].value.type_val);
      }
    }
#line 1003 "parser.tab.cc"
    break;

  case 51: // exp: '+' exp
#line 291 "parser.y"
    {
      if (!(yystack_[0].value.type_val) || ((yystack_[0].value.type_val)->p_type != PrimitiveType::INT && (yystack_[0].value.type_val)->p_type != PrimitiveType::FLOAT)) {
          error("Operador unário '+' requer operando numérico. Foi: " + type_to_string(*(yystack_[0].value.type_val)) + ".");
          (yylhs.value.type_val) = new VarType{PrimitiveType::UNDEFINED};
          delete (yystack_[0].value.type_val);
      } else {
          (yylhs.value.type_val) = (yystack_[0].value.type_val);
      }
    }
#line 1017 "parser.tab.cc"
    break;

  case 52: // exp: exp A_OR_LOGIC exp
#line 300 "parser.y"
                         { (yylhs.value.type_val) = check_logical_op((yystack_[2].value.type_val), (yystack_[0].value.type_val), "||"); }
#line 1023 "parser.tab.cc"
    break;

  case 53: // exp: exp A_AND_LOGIC exp
#line 301 "parser.y"
                          { (yylhs.value.type_val) = check_logical_op((yystack_[2].value.type_val), (yystack_[0].value.type_val), "&&"); }
#line 1029 "parser.tab.cc"
    break;

  case 54: // exp: exp '<' exp
#line 302 "parser.y"
                  { (yylhs.value.type_val) = check_relational_op((yystack_[2].value.type_val), (yystack_[0].value.type_val), "<"); }
#line 1035 "parser.tab.cc"
    break;

  case 55: // exp: exp A_LESS_THAN_EQUAL exp
#line 303 "parser.y"
                                { (yylhs.value.type_val) = check_relational_op((yystack_[2].value.type_val), (yystack_[0].value.type_val), "<="); }
#line 1041 "parser.tab.cc"
    break;

  case 56: // exp: exp '>' exp
#line 304 "parser.y"
                  { (yylhs.value.type_val) = check_relational_op((yystack_[2].value.type_val), (yystack_[0].value.type_val), ">"); }
#line 1047 "parser.tab.cc"
    break;

  case 57: // exp: exp A_GREATER_THAN_EQUAL exp
#line 305 "parser.y"
                                   { (yylhs.value.type_val) = check_relational_op((yystack_[2].value.type_val), (yystack_[0].value.type_val), ">="); }
#line 1053 "parser.tab.cc"
    break;

  case 58: // exp: exp '=' exp
#line 306 "parser.y"
                  { (yylhs.value.type_val) = check_relational_op((yystack_[2].value.type_val), (yystack_[0].value.type_val), "="); }
#line 1059 "parser.tab.cc"
    break;

  case 59: // exp: exp A_DIFFERENT exp
#line 307 "parser.y"
                          { (yylhs.value.type_val) = check_relational_op((yystack_[2].value.type_val), (yystack_[0].value.type_val), "<>"); }
#line 1065 "parser.tab.cc"
    break;

  case 60: // exp: exp '+' exp
#line 308 "parser.y"
                  { (yylhs.value.type_val) = check_arithmetic_op((yystack_[2].value.type_val), (yystack_[0].value.type_val), "+"); }
#line 1071 "parser.tab.cc"
    break;

  case 61: // exp: exp '-' exp
#line 309 "parser.y"
                  { (yylhs.value.type_val) = check_arithmetic_op((yystack_[2].value.type_val), (yystack_[0].value.type_val), "-"); }
#line 1077 "parser.tab.cc"
    break;

  case 62: // exp: exp '*' exp
#line 310 "parser.y"
                  { (yylhs.value.type_val) = check_arithmetic_op((yystack_[2].value.type_val), (yystack_[0].value.type_val), "*"); }
#line 1083 "parser.tab.cc"
    break;

  case 63: // exp: exp '/' exp
#line 311 "parser.y"
                  { (yylhs.value.type_val) = check_arithmetic_op((yystack_[2].value.type_val), (yystack_[0].value.type_val), "/"); }
#line 1089 "parser.tab.cc"
    break;

  case 64: // exp: exp '^' exp
#line 312 "parser.y"
                  { (yylhs.value.type_val) = check_arithmetic_op((yystack_[2].value.type_val), (yystack_[0].value.type_val), "^"); }
#line 1095 "parser.tab.cc"
    break;

  case 65: // ref_var: A_REF '(' var_access ')'
#line 317 "parser.y"
    {
      auto referenced_type = std::make_unique<VarType>(*(yystack_[1].value.type_val));
      (yylhs.value.type_val) = new VarType(PrimitiveType::REF, std::move(referenced_type));
      delete (yystack_[1].value.type_val);
    }
#line 1105 "parser.tab.cc"
    break;

  case 66: // deref_var: A_DEREF '(' var_access ')'
#line 326 "parser.y"
    {
      if ((yystack_[1].value.type_val)->p_type != PrimitiveType::REF || !(yystack_[1].value.type_val)->referenced_type) {
          error("Não é possível desreferenciar um tipo não-referência: " + type_to_string(*(yystack_[1].value.type_val)) + ".");
          (yylhs.value.type_val) = new VarType{PrimitiveType::UNDEFINED};
      } else {
          (yylhs.value.type_val) = new VarType{*(yystack_[1].value.type_val)->referenced_type};
      }
      delete (yystack_[1].value.type_val);
    }
#line 1119 "parser.tab.cc"
    break;

  case 67: // deref_var: A_DEREF '(' deref_var ')'
#line 336 "parser.y"
    {
      if ((yystack_[1].value.type_val)->p_type != PrimitiveType::REF || !(yystack_[1].value.type_val)->referenced_type) {
          error("Não é possível desreferenciar um tipo não-referência aninhado: " + type_to_string(*(yystack_[1].value.type_val)) + ".");
          (yylhs.value.type_val) = new VarType{PrimitiveType::UNDEFINED};
      } else {
          (yylhs.value.type_val) = new VarType{*(yystack_[1].value.type_val)->referenced_type};
      }
      delete (yystack_[1].value.type_val);
    }
#line 1133 "parser.tab.cc"
    break;

  case 68: // var_access: A_NAME
#line 349 "parser.y"
    {
      Symbol* s = symbol_table.lookup(*(yystack_[0].value.sval));
      if (!s) {
          error("Variável '" + *(yystack_[0].value.sval) + "' não declarada.");
          (yylhs.value.type_val) = new VarType{PrimitiveType::UNDEFINED};
      } else if (s->category != SymbolCategory::VARIABLE) {
          error("Símbolo '" + *(yystack_[0].value.sval) + "' não é uma variável.");
          (yylhs.value.type_val) = new VarType{PrimitiveType::UNDEFINED};
      } else {
          (yylhs.value.type_val) = new VarType{std::get<Variable>(s->content).type};
      }
      delete (yystack_[0].value.sval);
    }
#line 1151 "parser.tab.cc"
    break;

  case 69: // var_access: exp '.' A_NAME
#line 363 "parser.y"
    {
      (yylhs.value.type_val) = new VarType{PrimitiveType::UNDEFINED};
      if ((yystack_[2].value.type_val)->p_type == PrimitiveType::NOT_PRIMITIVE && (yystack_[2].value.type_val)->record_name.has_value()) {
          Symbol* rec_symbol = symbol_table.lookup((yystack_[2].value.type_val)->record_name.value());
          if (rec_symbol && rec_symbol->category == SymbolCategory::RECORD) {
              const Record& rec = std::get<Record>(rec_symbol->content);
              bool found_field = false;
              for (const auto& field : rec.fields) {
                  if (field.name == *(yystack_[0].value.sval)) {
                      delete (yylhs.value.type_val); // Descarta o UNDEFINED
                      (yylhs.value.type_val) = new VarType{field.type};
                      found_field = true;
                      break;
                  }
              }
              if (!found_field) {
                  error("Registro '" + (yystack_[2].value.type_val)->record_name.value() + "' não possui o campo '" + *(yystack_[0].value.sval) + "'.");
              }
          } else {
              error("Tipo de registro '" + (yystack_[2].value.type_val)->record_name.value() + "' não encontrado.");
          }
      } else {
          error("Acesso de membro '.' requer um tipo de registro à esquerda, mas obteve " + type_to_string(*(yystack_[2].value.type_val)) + ".");
      }
      delete (yystack_[2].value.type_val);
      delete (yystack_[0].value.sval);
    }
#line 1183 "parser.tab.cc"
    break;

  case 70: // literal: A_FLOAT_LITERAL
#line 394 "parser.y"
                     { (yylhs.value.type_val) = new VarType{PrimitiveType::FLOAT}; }
#line 1189 "parser.tab.cc"
    break;

  case 71: // literal: A_INT_LITERAL
#line 395 "parser.y"
                       { (yylhs.value.type_val) = new VarType{PrimitiveType::INT}; }
#line 1195 "parser.tab.cc"
    break;

  case 72: // literal: A_STRING_LITERAL
#line 396 "parser.y"
                       { (yylhs.value.type_val) = new VarType{PrimitiveType::STRING}; }
#line 1201 "parser.tab.cc"
    break;

  case 73: // literal: bool_literal
#line 397 "parser.y"
                     { (yylhs.value.type_val) = (yystack_[0].value.type_val); }
#line 1207 "parser.tab.cc"
    break;

  case 74: // literal: A_NULL
#line 398 "parser.y"
                     { (yylhs.value.type_val) = new VarType{PrimitiveType::VOID}; }
#line 1213 "parser.tab.cc"
    break;

  case 75: // bool_literal: A_TRUE
#line 402 "parser.y"
            { (yylhs.value.type_val) = new VarType{PrimitiveType::BOOL}; }
#line 1219 "parser.tab.cc"
    break;

  case 76: // bool_literal: A_FALSE
#line 403 "parser.y"
              { (yylhs.value.type_val) = new VarType{PrimitiveType::BOOL}; }
#line 1225 "parser.tab.cc"
    break;

  case 82: // assign_stmt: var_access A_ASSIGN exp
#line 416 "parser.y"
    {
      if (!are_types_compatible(*(yystack_[2].value.type_val), *(yystack_[0].value.type_val))) {
          error("Incompatibilidade de tipos na atribuição. Esperado " + type_to_string(*(yystack_[2].value.type_val)) + " mas obteve " + type_to_string(*(yystack_[0].value.type_val)) + ".");
      }
      delete (yystack_[2].value.type_val);
      delete (yystack_[0].value.type_val);
    }
#line 1237 "parser.tab.cc"
    break;

  case 83: // assign_stmt: deref_var A_ASSIGN exp
#line 424 "parser.y"
    {
      if (!are_types_compatible(*(yystack_[2].value.type_val), *(yystack_[0].value.type_val))) {
          error("Incompatibilidade de tipos na atribuição por desreferência. Esperado " + type_to_string(*(yystack_[2].value.type_val)) + " mas obteve " + type_to_string(*(yystack_[0].value.type_val)) + ".");
      }
      delete (yystack_[2].value.type_val);
      delete (yystack_[0].value.type_val);
    }
#line 1249 "parser.tab.cc"
    break;

  case 84: // if_stmt: A_IF exp A_THEN stmt_list optional_else_clause A_FI
#line 435 "parser.y"
    {
      if ((yystack_[4].value.type_val)->p_type != PrimitiveType::BOOL) {
          error("Condição do 'if' deve ser booleana, mas foi " + type_to_string(*(yystack_[4].value.type_val)) + ".");
      }
      delete (yystack_[4].value.type_val);
    }
#line 1260 "parser.tab.cc"
    break;

  case 85: // if_stmt: A_UNLESS exp A_DO stmt_list optional_else_clause A_OD
#line 442 "parser.y"
    {
      if ((yystack_[4].value.type_val)->p_type != PrimitiveType::BOOL) {
          error("Condição do 'unless' deve ser booleana, mas foi " + type_to_string(*(yystack_[4].value.type_val)) + ".");
      }
      delete (yystack_[4].value.type_val);
    }
#line 1271 "parser.tab.cc"
    break;

  case 86: // if_stmt: A_CASE exp A_OF case_list optional_otherwise_clause A_ESAC
#line 449 "parser.y"
    {
      if ((yystack_[4].value.type_val)->p_type != PrimitiveType::INT) {
            error("Expressão do 'case' deve ser do tipo inteiro, mas foi " + type_to_string(*(yystack_[4].value.type_val)) + ".");
      }
      delete (yystack_[4].value.type_val);
    }
#line 1282 "parser.tab.cc"
    break;

  case 98: // while_stmt: A_WHILE exp A_DO stmt_list A_OD
#line 488 "parser.y"
    {
      if ((yystack_[3].value.type_val)->p_type != PrimitiveType::BOOL) {
          error("Condição do 'while' deve ser booleana, mas foi " + type_to_string(*(yystack_[3].value.type_val)) + ".");
      }
      delete (yystack_[3].value.type_val);
    }
#line 1293 "parser.tab.cc"
    break;

  case 99: // return_stmt: A_RETURN optional_exp_val
#line 498 "parser.y"
    {
        VarType expected_return_type;
        if (func_return_type_stack.empty()) {
            error("'return' utilizado fora de um procedimento/função.");
            expected_return_type = VarType{PrimitiveType::UNDEFINED};
        } else {
            expected_return_type = func_return_type_stack.back();
        }

        VarType actual_return_type = (yystack_[0].value.type_val) ? *(yystack_[0].value.type_val) : VarType{PrimitiveType::VOID};

        if (!are_types_compatible(expected_return_type, actual_return_type)) {
            error("Tipo de retorno incompatível. Procedimento espera " + type_to_string(expected_return_type) + ", mas 'return' provê " + type_to_string(actual_return_type) + ".");
        }
        if ((yystack_[0].value.type_val)) delete (yystack_[0].value.type_val);
    }
#line 1314 "parser.tab.cc"
    break;

  case 100: // optional_exp_val: %empty
#line 517 "parser.y"
                { (yylhs.value.type_val) = nullptr; }
#line 1320 "parser.tab.cc"
    break;

  case 101: // optional_exp_val: exp
#line 518 "parser.y"
          { (yylhs.value.type_val) = (yystack_[0].value.type_val); }
#line 1326 "parser.tab.cc"
    break;

  case 102: // call_stmt: A_NAME '(' optional_arg_list ')'
#line 523 "parser.y"
    {
      Symbol* s = symbol_table.lookup(*(yystack_[3].value.sval));
      if (!s) {
          error("Procedimento ou função '" + *(yystack_[3].value.sval) + "' não foi declarado(a).");
      } else if (s->category != SymbolCategory::PROCEDURE) {
          error("Símbolo '" + *(yystack_[3].value.sval) + "' não é um procedimento/função, não pode ser chamado.");
      } else {
          const Procedure& proc = std::get<Procedure>(s->content);
          const auto& params = proc.params;
          const auto& args = *(yystack_[1].value.type_vec); // std::vector<VarType*>

          if (params.size() != args.size()) {
              error("Número incorreto de argumentos para '" + *(yystack_[3].value.sval) + "'. Esperado: " + std::to_string(params.size()) + ", Fornecido: " + std::to_string(args.size()) + ".");
          } else {
              for (size_t i = 0; i < params.size(); ++i) {
                  if (!are_types_compatible(params[i].type, *args[i])) {
                      error("Incompatibilidade de tipo para o argumento " + std::to_string(i+1) + " na chamada de '" + *(yystack_[3].value.sval) + "'. Esperado: " + type_to_string(params[i].type) + ", Fornecido: " + type_to_string(*args[i]) + ".");
                  }
              }
          }
      }
      delete (yystack_[3].value.sval);
    }
#line 1354 "parser.tab.cc"
    break;

  case 103: // call_stmt_as_exp: A_NAME '(' optional_arg_list ')'
#line 550 "parser.y"
    {
      (yylhs.value.type_val) = new VarType{PrimitiveType::UNDEFINED};
      Symbol* s = symbol_table.lookup(*(yystack_[3].value.sval));
      if (!s) {
          error("Função '" + *(yystack_[3].value.sval) + "' não foi declarada.");
      } else if (s->category != SymbolCategory::PROCEDURE) {
          error("Símbolo '" + *(yystack_[3].value.sval) + "' não é uma função.");
      } else {
          const Procedure& proc = std::get<Procedure>(s->content);
          if (proc.return_type.p_type == PrimitiveType::VOID) {
              error("Procedimento '" + *(yystack_[3].value.sval) + "' não retorna um valor e não pode ser usado em uma expressão.");
          } else {
                delete (yylhs.value.type_val);
                (yylhs.value.type_val) = new VarType{proc.return_type};
          }

          const auto& params = proc.params;
          const auto& args = *(yystack_[1].value.type_vec);
          if (params.size() != args.size()) {
              error("Número incorreto de argumentos para '" + *(yystack_[3].value.sval) + "'. Esperado: " + std::to_string(params.size()) + ", Fornecido: " + std::to_string(args.size()) + ".");
          } else {
                for (size_t i = 0; i < params.size(); ++i) {
                  if (!are_types_compatible(params[i].type, *args[i])) {
                    error("Incompatibilidade de tipo para o argumento " + std::to_string(i+1) + " na chamada de '" + *(yystack_[3].value.sval) + "'. Esperado: " + type_to_string(params[i].type) + ", Fornecido: " + type_to_string(*args[i]) + ".");
                  }
              }
          }
      }
      delete (yystack_[3].value.sval);
    }
#line 1389 "parser.tab.cc"
    break;

  case 104: // optional_arg_list: %empty
#line 584 "parser.y"
                { (yylhs.value.type_vec) = new std::vector<VarType*>(); }
#line 1395 "parser.tab.cc"
    break;

  case 105: // optional_arg_list: arg_list
#line 585 "parser.y"
               { (yylhs.value.type_vec) = (yystack_[0].value.type_vec); }
#line 1401 "parser.tab.cc"
    break;

  case 106: // arg_list: exp
#line 589 "parser.y"
        { (yylhs.value.type_vec) = new std::vector<VarType*>{(yystack_[0].value.type_val)}; }
#line 1407 "parser.tab.cc"
    break;

  case 107: // arg_list: arg_list ',' exp
#line 590 "parser.y"
                       { (yystack_[2].value.type_vec)->push_back((yystack_[0].value.type_val)); (yylhs.value.type_vec) = (yystack_[2].value.type_vec); }
#line 1413 "parser.tab.cc"
    break;


#line 1417 "parser.tab.cc"

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

  const signed char parser::yytable_ninf_ = -103;

  const short
  parser::yypact_[] =
  {
       1,     9,    11,   -60,   -60,   -60,    10,    12,    15,    26,
      28,    33,     5,   -60,   -60,   -60,   -60,    -1,   -38,     2,
     -60,    12,    44,    68,   149,    44,   -60,    18,    17,     8,
     -60,   -60,   -60,   -60,   -60,   -60,    19,    23,   -60,   -60,
      21,   -60,   -60,   -60,   -60,   149,    65,    47,    58,   149,
     149,   149,   226,   -60,   -60,   -60,   -60,   -60,   -60,   -60,
      25,    43,    68,    66,    44,    68,   149,   -60,   149,    49,
     -60,   149,   149,   209,    49,    49,   149,   149,   149,   149,
     149,   149,   149,   149,   104,   149,   149,   149,   149,   149,
     -60,    44,   -60,    68,   106,   -60,    67,   226,   226,    73,
      81,   226,    82,    83,    87,   -60,   260,   260,   260,    36,
      36,   -29,   -29,   -29,   -60,   260,   260,   260,   243,   274,
     -60,   -60,     6,   -60,   -60,   149,   -60,   -60,   -60,   105,
     124,   226,   -60,    90,   149,   149,   149,   149,   149,   132,
     -60,    97,    98,   123,   -60,   -60,   -60,   -60,   -60,   149,
      24,   155,   226,   -60,   172,   191,   -60,   149,   149,   124,
     116,   124,   124,   124,   163,   226,   226,   -60,    -9,   152,
     150,   152,   103,   -22,   -60,    -8,   -60,   124,   158,   -60,
     160,   177,   124,   163,   159,   124,   163,   -60,   -60,   -60,
     -60,   -60,   -60,   -60,   -60,   -60
  };

  const signed char
  parser::yydefact_[] =
  {
       3,     0,     0,     2,     4,     1,     0,     6,     0,     0,
       0,     0,     7,     8,    10,    11,    12,     0,     0,     0,
       5,     0,    24,     0,     0,    38,     9,     0,     0,    25,
      26,    21,    17,    18,    19,    20,     0,    15,    71,    70,
      68,    72,    75,    76,    74,     0,     0,     0,     0,     0,
       0,     0,    14,    46,    47,    45,    42,    73,    43,    40,
       0,    39,     0,    29,     0,     0,     0,    13,   104,    49,
      44,     0,     0,     0,    51,    50,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      37,     0,    28,     0,     0,    27,     0,    16,   106,     0,
     105,     0,    45,    47,    45,    48,    54,    56,    58,    60,
      61,    62,    63,    64,    69,    55,    57,    59,    52,    53,
      41,    30,    31,    22,   103,     0,    65,    67,    66,     0,
      33,   107,    32,    68,     0,     0,   100,     0,     0,     0,
      34,    47,    45,    35,    77,    78,    79,    80,    81,   104,
       0,     0,   101,    99,     0,     0,    23,     0,     0,     0,
       0,    33,    33,    33,     0,    83,    82,    36,   103,    87,
       0,    87,    94,    96,    89,     0,    92,    33,     0,    98,
       0,     0,    33,     0,     0,    33,     0,    88,    84,    85,
      95,    97,    90,    86,    91,    93
  };

  const short
  parser::yypgoto_[] =
  {
     -60,   -60,   -60,   -60,    60,   -60,   167,   -60,   -60,   -57,
     -60,   -60,   -60,   -23,   -60,   -60,   -14,    30,   -60,   -60,
     -60,   -24,   -60,   -42,   -59,   -60,   -60,   -60,   -60,   -60,
      20,   -60,    13,   -60,     7,   -60,   -60,   -60,   -60,   -60,
     -60,    45,   -60
  };

  const unsigned char
  parser::yydefgoto_[] =
  {
       0,     2,     3,     6,    11,    12,    13,    14,    67,    37,
      15,    28,    29,    30,    94,   130,   139,   140,    16,    60,
      61,   101,    53,    54,    55,    56,    57,   143,   144,   145,
     178,   173,   174,   175,   176,   184,   146,   147,   153,   148,
      58,    99,   100
  };

  const short
  parser::yytable_[] =
  {
      52,  -102,    59,   182,    23,    92,  -102,  -102,    96,     1,
    -102,     5,   102,   104,     4,  -102,  -102,     8,     9,     7,
      17,    69,    24,     8,     9,    73,    74,    75,    83,    84,
     103,    18,  -102,    19,   185,   186,   121,   183,   161,    10,
      -6,    95,    97,    20,    98,    10,    21,    22,    25,    27,
    -102,    64,   106,   107,   108,   109,   110,   111,   112,   113,
      62,   115,   116,   117,   118,   119,    63,    65,   120,    68,
      70,   142,    90,    31,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    66,    91,    85,    86,    87,   141,    88,
      89,    81,    82,    83,    84,    71,    32,    33,    34,    35,
     142,   131,   142,   142,   142,    36,    72,    84,    93,   114,
     150,   151,   152,   154,   155,   122,   123,   141,   142,   141,
     141,   141,   124,   142,   125,    98,   142,    38,    39,   133,
      41,   126,   127,   165,   166,   141,   128,   134,   149,   132,
     141,   135,   156,   141,   136,   137,   138,   169,   170,   171,
      42,    43,    38,    39,    40,    41,    44,   157,   158,    45,
      46,    47,    48,   187,   159,   168,   172,   177,   191,   179,
     181,   194,    49,   162,   188,    42,    43,    50,    51,   189,
     190,    44,   129,   193,    45,    46,    47,    48,    26,   167,
     163,   180,     0,   195,   160,     0,   192,    49,     0,     0,
       0,     0,    50,    51,     0,    76,    77,    78,    79,    80,
      81,    82,    83,    84,   164,     0,    85,    86,    87,     0,
      88,    89,    76,    77,    78,    79,    80,    81,    82,    83,
      84,     0,     0,    85,    86,    87,     0,    88,    89,     0,
       0,    76,    77,    78,    79,    80,    81,    82,    83,    84,
       0,     0,    85,    86,    87,     0,    88,    89,   105,    76,
      77,    78,    79,    80,    81,    82,    83,    84,     0,     0,
      85,    86,    87,     0,    88,    89,    76,    77,    78,    79,
      80,    81,    82,    83,    84,     0,     0,    85,    86,    87,
       0,    88,    89,    76,    77,    78,    79,    80,    81,    82,
      83,    84,     0,     0,    85,    86,    87,     0,     0,    89,
    -103,  -103,  -103,    79,    80,    81,    82,    83,    84,     0,
       0,  -103,  -103,  -103,    76,    77,    78,    79,    80,    81,
      82,    83,    84,     0,     0,    85,    86,    87
  };

  const short
  parser::yycheck_[] =
  {
      24,    10,    25,    25,    42,    62,    15,    16,    65,     8,
      19,     0,    71,    72,     5,    24,    25,    11,    12,     9,
       5,    45,    60,    11,    12,    49,    50,    51,    57,    58,
      72,     5,    41,     5,    42,    43,    93,    59,    14,    33,
      34,    64,    66,    10,    68,    33,    41,    48,    46,     5,
      59,    43,    76,    77,    78,    79,    80,    81,    82,    83,
      42,    85,    86,    87,    88,    89,    49,    48,    91,    48,
       5,   130,    47,     5,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    60,    41,    61,    62,    63,   130,    65,
      66,    55,    56,    57,    58,    48,    28,    29,    30,    31,
     159,   125,   161,   162,   163,    37,    48,    58,    42,     5,
     134,   135,   136,   137,   138,     9,    49,   159,   177,   161,
     162,   163,    49,   182,    43,   149,   185,     3,     4,     5,
       6,    49,    49,   157,   158,   177,    49,    13,    48,    34,
     182,    17,    10,   185,    20,    21,    22,   161,   162,   163,
      26,    27,     3,     4,     5,     6,    32,    60,    60,    35,
      36,    37,    38,   177,    41,    49,     3,    15,   182,    19,
      67,   185,    48,    18,    16,    26,    27,    53,    54,    19,
       3,    32,   122,    24,    35,    36,    37,    38,    21,   159,
      18,   171,    -1,   186,   149,    -1,   183,    48,    -1,    -1,
      -1,    -1,    53,    54,    -1,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    23,    -1,    61,    62,    63,    -1,
      65,    66,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    -1,    -1,    61,    62,    63,    -1,    65,    66,    -1,
      -1,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      -1,    -1,    61,    62,    63,    -1,    65,    66,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    -1,    -1,
      61,    62,    63,    -1,    65,    66,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    -1,    -1,    61,    62,    63,
      -1,    65,    66,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    -1,    -1,    61,    62,    63,    -1,    -1,    66,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    -1,
      -1,    61,    62,    63,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    -1,    -1,    61,    62,    63
  };

  const signed char
  parser::yystos_[] =
  {
       0,     8,    69,    70,     5,     0,    71,     9,    11,    12,
      33,    72,    73,    74,    75,    78,    86,     5,     5,     5,
      10,    41,    48,    42,    60,    46,    74,     5,    79,    80,
      81,     5,    28,    29,    30,    31,    37,    77,     3,     4,
       5,     6,    26,    27,    32,    35,    36,    37,    38,    48,
      53,    54,    89,    90,    91,    92,    93,    94,   108,    81,
      87,    88,    42,    49,    43,    48,    60,    76,    48,    89,
       5,    48,    48,    89,    89,    89,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    61,    62,    63,    65,    66,
      47,    41,    77,    42,    82,    81,    77,    89,    89,   109,
     110,    89,    92,    91,    92,    49,    89,    89,    89,    89,
      89,    89,    89,    89,     5,    89,    89,    89,    89,    89,
      81,    77,     9,    49,    49,    43,    49,    49,    49,    72,
      83,    89,    34,     5,    13,    17,    20,    21,    22,    84,
      85,    91,    92,    95,    96,    97,   104,   105,   107,    48,
      89,    89,    89,   106,    89,    89,    10,    60,    60,    41,
     109,    14,    18,    18,    23,    89,    89,    85,    49,    84,
      84,    84,     3,    99,   100,   101,   102,    15,    98,    19,
      98,    67,    25,    59,   103,    42,    43,    84,    16,    19,
       3,    84,   100,    24,    84,   102
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
      89,    89,    89,    89,    89,    90,    91,    91,    92,    92,
      93,    93,    93,    93,    93,    94,    94,    95,    95,    95,
      95,    95,    96,    96,    97,    97,    97,    98,    98,    99,
      99,   100,   101,   101,   102,   102,   103,   103,   104,   105,
     106,   106,   107,   108,   109,   109,   110,   110
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     0,     0,     6,     0,     1,     1,     3,
       1,     1,     1,     5,     4,     0,     2,     1,     1,     1,
       1,     1,     4,    10,     0,     1,     1,     3,     3,     0,
       2,     0,     2,     0,     1,     1,     3,     5,     0,     1,
       1,     3,     1,     1,     2,     1,     1,     1,     3,     2,
       2,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     4,     4,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     3,     6,     6,     6,     0,     2,     1,
       3,     3,     1,     3,     1,     3,     0,     2,     5,     2,
       0,     1,     4,     4,     0,     1,     1,     3
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
       0,    76,    76,    77,    81,    81,    85,    87,    91,    92,
      96,    97,    98,   102,   129,   145,   146,   150,   151,   152,
     153,   154,   165,   174,   196,   197,   201,   202,   206,   210,
     211,   214,   216,   219,   221,   225,   226,   230,   245,   246,
     250,   251,   255,   256,   257,   268,   269,   270,   271,   272,
     280,   290,   300,   301,   302,   303,   304,   305,   306,   307,
     308,   309,   310,   311,   312,   316,   325,   335,   348,   362,
     394,   395,   396,   397,   398,   402,   403,   407,   408,   409,
     410,   411,   415,   423,   434,   441,   448,   457,   459,   463,
     464,   468,   472,   473,   477,   478,   481,   483,   487,   497,
     517,   518,   522,   549,   584,   585,   589,   590
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
#line 1946 "parser.tab.cc"

#line 593 "parser.y"
 // Fim das Regras Gramaticais

void yy::parser::error(const std::string &message)
{
    std::cerr << "Error: " << message << std::endl;
}
