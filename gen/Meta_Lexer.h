#pragma once

#include<unordered_map>
#include<string>
#include<yuki/Vector.hpp>
#include"cmd.hpp"
#include"gen/Regex_Lexer.h"
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
    size_t INITIAL(I&,typename I::Pos*);
    template<typename I>
    size_t O_NSPACE(I&,typename I::Pos*);
    template<typename I>
    size_t O_LEXER(I&,typename I::Pos*);
    template<typename I>
    size_t O_ICLASS(I&,typename I::Pos*);
    template<typename I>
    size_t O_IHEADER(I&,typename I::Pos*);
    template<typename I>
    size_t O_DPREFIX(I&,typename I::Pos*);
    template<typename I>
    size_t O_FCNSPACE(I&,typename I::Pos*);
    template<typename I>
    size_t O_TTYPE(I&,typename I::Pos*);
    template<typename I>
    size_t O_TPLEXER(I&,typename I::Pos*);
    template<typename I>
    size_t MACRO_DEF_GOBBLE_SPACE(I&,typename I::Pos*);
    template<typename I>
    size_t MACRO_DEF(I&,typename I::Pos*);
    template<typename I>
    size_t CODE0(I&,typename I::Pos*);
    template<typename I>
    size_t CODE1(I&,typename I::Pos*);
    template<typename I>
    size_t C_LIT(I&,typename I::Pos*);
    template<typename I>
    size_t S_LIT(I&,typename I::Pos*);
    template<typename I>
    size_t SEC1(I&,typename I::Pos*);
    template<typename I>
    size_t GOBBLE_NEWLINE_TO_REGEX(I&,typename I::Pos*);
    template<typename I>
    size_t REGEX(I&,typename I::Pos*);
    template<typename I>
    size_t REGEX_CODE(I&,typename I::Pos*);
    template<typename I>
    size_t DISCARD_EVERYTHING_UNTIL_NEWLINE_TO_POST_REGEX(I&,typename I::Pos*);
    template<typename I>
    size_t REGEX_CODE_EOF(I&,typename I::Pos*);
    template<typename I>
    size_t C_LIT_EOF(I&,typename I::Pos*);
    template<typename I>
    size_t S_LIT_EOF(I&,typename I::Pos*);
    template<typename I>
    size_t REGEX_CODE_DEFAULT(I&,typename I::Pos*);
    template<typename I>
    size_t C_LIT_DEFAULT(I&,typename I::Pos*);
    template<typename I>
    size_t S_LIT_DEFAULT(I&,typename I::Pos*);
    template<typename I>
    size_t REGEX_CODE_BEFORE(I&,typename I::Pos*);
    template<typename I>
    size_t C_LIT_BEFORE(I&,typename I::Pos*);
    template<typename I>
    size_t S_LIT_BEFORE(I&,typename I::Pos*);
    template<typename I>
    size_t POST_REGEX(I&,typename I::Pos*);
    template<typename I>
    size_t SEC2(I&,typename I::Pos*);
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

    std::unordered_map<std::string,std::string> macro_table;
    yuki::Vector<std::string_view> macro_stack;

    Regex_Lexer rl{errors_};
    Regex_Parser rp{&rl,errors_};

    std::string str_temp;

    void write_h0() const;
    void write_fsm_code_wrapped();
    void write_lex_and_h1();

    void process_macro(std::string_view current,std::string& to_populate){
        #ifndef YUKI_LEX_MAX_MACRO_EXPANSION
        #define YUKI_LEX_MAX_MACRO_EXPANSION 128
        #endif
        size_t expansion = 0;

        while(1){
            std::string_view::const_iterator b = current.begin();
            const std::string_view::const_iterator e = current.end();
            while(b!=e){
                switch(*b){
                    case '\\':{
                        ++b;
                        if(b!=e){
                            switch(*b){
                                case 'p':
                                case 'u':{
                                    ++b;
                                    if(b!=e)
                                        ++b;
                                    goto next_char;
                                }
                                default: ++b;goto next_char;
                            }
                        }else{
                            fprintf(stderr,"Error: Incomplete escape character at the end!\n");
                            ++errors_;
                            to_populate.append(current.begin(),b).push_back('\\');
                            if(!macro_stack.empty()){
                                current=macro_stack.pop_back_v();
                                goto big_loop_end;
                            }else
                                return;
                        }
                    }
                    case '{':{
                        ++b;
                        if(b!=e){
                            if(isdigit(static_cast<unsigned char>(*b))){
                                ++b;
                                goto next_char;
                            }else{
                                if(expansion<YUKI_LEX_MAX_MACRO_EXPANSION){
                                    const std::string_view::const_iterator macro_b = b;
                                    do{
                                        if(*b=='}'){
                                            try{
                                                const std::string_view::const_iterator b_orig = current.begin();
                                                current = macro_table.at(std::string(macro_b,b));
                                                to_populate.append(b_orig,macro_b-1);
                                                if(b!=e-1)
                                                    macro_stack.emplace_back(b+1,e);
                                                ++expansion;
                                                goto big_loop_end;
                                            }catch(const std::out_of_range&){
                                                fprintf(stderr,"Error: Undefined macro name \"");
                                                for(std::string_view::const_iterator i=macro_b;i!=b;++i)
                                                    fprintf(stderr,"%c",*i);
                                                fprintf(stderr,"\"!\n");
                                                ++errors_;
                                                ++b;
                                                goto next_char;
                                            }
                                        }
                                        else
                                            ++b;
                                    }while(b!=e);
                                    // When `b` hits end with no '}' encountered.
                                    fprintf(stderr,"Error: Incomplete macro name \"");
                                    for(std::string_view::const_iterator i=macro_b;i!=e;++i)
                                        fprintf(stderr,"%c",*i);
                                    fprintf(stderr,"\"!\n");
                                    goto next_stack;
                                }else{
                                    fprintf(stderr,"Error: Macro expansion hits limit %d!\n",YUKI_LEX_MAX_MACRO_EXPANSION);
                                    ++errors_;
                                    ++b;
                                    goto next_char;
                                }
                            } // if(isdigit(static_cast<unsigned char>(*b))) else
                        }else{ // if(b!=e)
                            fprintf(stderr,"Error: Stray { encountered!\n");
                            ++errors_;
                            goto next_stack;
                        }
                    } // case '{'
                    default: ++b; goto next_char;
                } // switch(*b)
                next_char:;
            } // while(b!=e)
            next_stack:
            to_populate.append(current.begin(),b);
            if(!macro_stack.empty())
                current=macro_stack.pop_back_v();
            else
                return;
            big_loop_end:;
        } // while(1)
    } // process_macro
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


