#pragma once

#include"gen/Regex_Parser.token.hpp"
#include<yuki/lex/U8Input.hpp>

#ifdef YUKI_LEX_Regex_Lexer_DBG
#include<yuki/print.hpp>
#ifndef YUKI_LEX_Regex_Lexer_DBG_LOG
#define YUKI_LEX_Regex_Lexer_DBG_LOG "YUKI_LEX_Regex_Lexer_DBG.log"
#endif
namespace yuki::lex{
#ifndef YUKI_LEX_Regex_Lexer_DBG_FP
inline FILE* const YUKI_LEX_Regex_Lexer_DBG_fp_=fopen(YUKI_LEX_Regex_Lexer_DBG_LOG,"w");
#define YUKI_LEX_Regex_Lexer_DBG_FP yuki::lex::YUKI_LEX_Regex_Lexer_DBG_fp_
#endif
} // namespace yuki::lex
#define YUKI_LEX_Regex_Lexer_DBGO(...) yuki::dbgout_base(fp_dbg_,"YUKI_LEX_Regex_Lexer_DBG",__VA_ARGS__)
#define CONSTEXPR_YUKI_LEX_Regex_Lexer_DBG // Debug output would render constexpr-functions non-constexpr.
#ifndef YUKI_LEX_Regex_Lexer_DBG_REGEX_MAX_PRINT
#define YUKI_LEX_Regex_Lexer_DBG_REGEX_MAX_PRINT 128
#endif
#else
#define YUKI_LEX_Regex_Lexer_DBGO(...)
#define CONSTEXPR_YUKI_LEX_Regex_Lexer_DBG constexpr
#endif

namespace yuki::lex{
namespace Regex_Lexer_fsm_codes{
    template<typename I>
    size_t INITIAL(I&,typename I::Pos*);
} // namespace Regex_Lexer_fsm_codes


struct Regex_Lexer{
    enum struct State {INITIAL,} state=State::INITIAL;
    std::string_view matched;
    yuki::lex::U8Input in;
    #ifdef YUKI_LEX_Regex_Lexer_DBG
    FILE* fp_dbg_=YUKI_LEX_Regex_Lexer_DBG_FP;
    #endif

  public:

  private:
    typedef Regex_Parser_TS::Token_Kind Token_Kind;
    typedef Regex_Parser_TS::Token_t Token_t;

    unsigned& errors;
  public:
    Regex_Lexer(unsigned& e) noexcept :
        errors(e)
    {}
  public:
    yuki::lex::Regex_Parser_TS::Token_t lex();
}; // struct Regex_Lexer
} // namespace yuki::lex


