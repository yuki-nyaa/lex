#pragma once

#include<unordered_map>
#include<string>
#include<yuki/Vector.hpp>
#include"cmd.hpp"
#include"Regex_Lexer.hpp"
#include"gen/Regex_Parser.h"

namespace yuki::lex{
void write_fsm_code(
    FILE* const out,
    const FSM* const fsms,
    const size_t fsms_size,
    const size_t max_branch_size,
    const size_t max_branch_number,
    unsigned& errors,
    const char* const fsm_name
    #ifdef YUKI_LEX_META_DBG
    ,Cmd_Data::Debug_Options debug_options = {}
    #endif
);
}
#include<yuki/lex/U8Input.hpp>

#ifdef YUKI_LEX_Meta_Lexer_DBG
#include<yuki/print.hpp>
#ifndef YUKI_LEX_Meta_Lexer_DBG_LOG
#define YUKI_LEX_Meta_Lexer_DBG_LOG "YUKI_LEX_Meta_Lexer_DBG.log"
#endif
namespace yuki::lex{
#ifndef YUKI_LEX_Meta_Lexer_DBG_FP
inline FILE* const YUKI_LEX_Meta_Lexer_DBG_fp_=fopen(YUKI_LEX_Meta_Lexer_DBG_LOG,"w");
#define YUKI_LEX_Meta_Lexer_DBG_FP yuki::lex::YUKI_LEX_Meta_Lexer_DBG_fp_
#endif
} // namespace yuki::lex
#define YUKI_LEX_Meta_Lexer_DBGO(...) yuki::dbgout_base(fp_dbg_,"YUKI_LEX_Meta_Lexer_DBG",__VA_ARGS__)
#define CONSTEXPR_YUKI_LEX_Meta_Lexer_DBG // Debug output would render constexpr-functions non-constexpr.
#ifndef YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT
#define YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT 128
#endif
#else
#define YUKI_LEX_Meta_Lexer_DBGO(...)
#define CONSTEXPR_YUKI_LEX_Meta_Lexer_DBG constexpr
#endif

namespace yuki::lex{
namespace Meta_Lexer_fsm_codes{
    template<typename I>
    size_t INITIAL(I&,typename I::Pos*) noexcept;
    template<typename I>
    size_t O_NSPACE(I&,typename I::Pos*) noexcept;
    template<typename I>
    size_t O_LEXER(I&,typename I::Pos*) noexcept;
    template<typename I>
    size_t O_ICLASS(I&,typename I::Pos*) noexcept;
    template<typename I>
    size_t O_IHEADER(I&,typename I::Pos*) noexcept;
    template<typename I>
    size_t O_DPREFIX(I&,typename I::Pos*) noexcept;
    template<typename I>
    size_t O_FCNSPACE(I&,typename I::Pos*) noexcept;
    template<typename I>
    size_t O_TTYPE(I&,typename I::Pos*) noexcept;
    template<typename I>
    size_t O_TPLEXER(I&,typename I::Pos*) noexcept;
    template<typename I>
    size_t MACRO_DEF_GOBBLE_SPACE(I&,typename I::Pos*) noexcept;
    template<typename I>
    size_t MACRO_DEF(I&,typename I::Pos*) noexcept;
    template<typename I>
    size_t CODE0(I&,typename I::Pos*) noexcept;
    template<typename I>
    size_t CODE1(I&,typename I::Pos*) noexcept;
    template<typename I>
    size_t C_LIT(I&,typename I::Pos*) noexcept;
    template<typename I>
    size_t S_LIT(I&,typename I::Pos*) noexcept;
    template<typename I>
    size_t SEC1(I&,typename I::Pos*) noexcept;
    template<typename I>
    size_t GOBBLE_NEWLINE_TO_REGEX(I&,typename I::Pos*) noexcept;
    template<typename I>
    size_t REGEX(I&,typename I::Pos*) noexcept;
    template<typename I>
    size_t REGEX_CODE(I&,typename I::Pos*) noexcept;
    template<typename I>
    size_t DISCARD_EVERYTHING_UNTIL_NEWLINE_TO_POST_REGEX(I&,typename I::Pos*) noexcept;
    template<typename I>
    size_t REGEX_CODE_EOF(I&,typename I::Pos*) noexcept;
    template<typename I>
    size_t C_LIT_EOF(I&,typename I::Pos*) noexcept;
    template<typename I>
    size_t S_LIT_EOF(I&,typename I::Pos*) noexcept;
    template<typename I>
    size_t REGEX_CODE_DEFAULT(I&,typename I::Pos*) noexcept;
    template<typename I>
    size_t C_LIT_DEFAULT(I&,typename I::Pos*) noexcept;
    template<typename I>
    size_t S_LIT_DEFAULT(I&,typename I::Pos*) noexcept;
    template<typename I>
    size_t REGEX_CODE_BEFORE(I&,typename I::Pos*) noexcept;
    template<typename I>
    size_t C_LIT_BEFORE(I&,typename I::Pos*) noexcept;
    template<typename I>
    size_t S_LIT_BEFORE(I&,typename I::Pos*) noexcept;
    template<typename I>
    size_t POST_REGEX(I&,typename I::Pos*) noexcept;
    template<typename I>
    size_t SEC2(I&,typename I::Pos*) noexcept;
} // namespace Meta_Lexer_fsm_codes


struct Meta_Lexer{
    enum struct State {INITIAL,O_NSPACE,O_LEXER,O_ICLASS,O_IHEADER,O_DPREFIX,O_FCNSPACE,O_TTYPE,O_TPLEXER,MACRO_DEF_GOBBLE_SPACE,MACRO_DEF,CODE0,CODE1,C_LIT,S_LIT,SEC1,GOBBLE_NEWLINE_TO_REGEX,REGEX,REGEX_CODE,DISCARD_EVERYTHING_UNTIL_NEWLINE_TO_POST_REGEX,REGEX_CODE_EOF,C_LIT_EOF,S_LIT_EOF,REGEX_CODE_DEFAULT,C_LIT_DEFAULT,S_LIT_DEFAULT,REGEX_CODE_BEFORE,C_LIT_BEFORE,S_LIT_BEFORE,POST_REGEX,SEC2,} state=State::INITIAL;
    std::string_view matched;
    yuki::lex::U8Input in;
    #ifdef YUKI_LEX_Meta_Lexer_DBG
    FILE* fp_dbg_=YUKI_LEX_Meta_Lexer_DBG_FP;
    #endif

    Meta_Lexer() noexcept=default;

    template<typename... Args>
    explicit Meta_Lexer(Args&&... args) noexcept : in(std::forward<Args>(args)...) {}
  protected:
    yuki::lex::U8Input::Pos heads[1];
    void clear_heads(){
        static_assert(std::is_trivially_copyable_v<yuki::lex::U8Input::Pos>);
        memset(heads,0,sizeof(heads));
    }
  public:

  private:
    Cmd_Data cmd_data;
    std::string nspace;
    std::string lexer = "Lexer";
    std::string debug_prefix;
    std::string fsm_codes_nspace;
    std::string input_class = "yuki::lex::U8Input";
    std::string input_header = "<yuki/lex/U8Input.hpp>";
    std::string token_type = "int";
    std::string lex_params;
    std::string template_decl;
    std::string templated_lexer;

    std::string nspace_head;
    std::string nspace_tail;

    std::unordered_map<std::string,std::string> code_htable;

    size_t max_heads=0;

    std::string current_fsm_name;
    std::string current_regex;
    struct Regex_Code{
        std::string regex;
        std::string code;
    };
    yuki::Vector<Regex_Code> current_regex_codes;
    std::string current_eof;
    std::string current_default;
    std::string current_before;
    struct Named_Regex_Codes{
        std::string name;
        yuki::Vector<Regex_Code> regex_codes;
        std::string eof_code;
        std::string default_code;
        std::string before_code;
    };
    yuki::Vector<Named_Regex_Codes> named_regex_codes;

    unsigned errors_=0;
    unsigned brace_level;
    bool initial_encountered = false;
    bool no_default_ctor = false;
    decltype(State::INITIAL) state_prev;

    Regex_Lexer rl{errors_};
    Regex_Parser rp{&rl,errors_};

    std::string str_temp;

    void write_h0() const;
    void write_fsm_code_wrapped();
    void write_lex_and_h1();
  public:
    auto errors() const {return errors_;}

    template<typename... Args>
    Meta_Lexer(yuki::lex::Cmd_Data&& cmd_data_p,Args&&... args) noexcept :
        in(cmd_data_p.fp_in),
        cmd_data(std::move(cmd_data_p)),
        code_htable(16)
    {}
  public:
    int lex();
}; // struct Meta_Lexer
} // namespace yuki::lex


