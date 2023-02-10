%namespace yuki::lex
%lexer Meta_Lexer

%code cpp_top{
#include"cconfig"
}

%code h_top{
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
}

%code class{
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
}

%%
<INITIAL>{
\%namespace\u{Space}*    {state=State::O_NSPACE;}
\%lexer\u{Space}*    {state=State::O_LEXER;}
\%input[_\-]class\u{Space}*    {state=State::O_ICLASS;}
\%input[_\-]header\u{Space}*    {state=State::O_IHEADER;}
\%debug[_\-]prefix\u{Space}*    {state=State::O_DPREFIX;}
\%fsm[_\-]codes[_\-]namespace\u{Space}*    {state=State::O_FCNSPACE;}
\%token[_\-]type\u{Space}*    {state=State::O_TTYPE;}
\%no[_\-]default[_\-]ctor\u{Space}*    {no_default_ctor=true;}
\%template\u{Space}*<.*    {matched.remove_prefix(1); template_decl=matched;}
\%templated[_\-]lexer\u{Space}*    {state=State::O_TPLEXER;}

\%code\u{Space}*    {current_regex.clear(); state=State::CODE0;}

[a-zA-Z_][0-9a-zA-Z_]*    {current_regex=matched; state=State::MACRO_DEF_GOBBLE_SPACE;}

\%\%\u{Space}*    {
    if(debug_prefix.empty())
        debug_prefix.append("YUKI_LEX_").append(lexer).append("_DBG");
    if(fsm_codes_nspace.empty())
        fsm_codes_nspace.append(lexer).append("_fsm_codes");
    if(!nspace.empty()){
        nspace_head.append("namespace ").append(nspace).push_back('{');
        nspace_tail.append("} // namespace ").append(nspace);
    }
    if(!template_decl.empty() && templated_lexer.empty()){
        fprintf(stderr,"Error: The lexer is templated but no templated name is given! (Note: Specify it by %%templated_lexer)\n");
        ++errors_;
        templated_lexer = lexer;
    }
    write_h0();
    state=State::SEC1;
}

\u{Space}+    {}

\/\/.*\R    {} // Comments.
}


<O_NSPACE>{
.*   {nspace=matched;state=State::INITIAL;}
}

<O_LEXER>{
.*    {lexer=matched;state=State::INITIAL;}
}

<O_ICLASS>{
.*   {input_class=matched;state=State::INITIAL;}
}

<O_IHEADER>{
.*   {input_header=matched;state=State::INITIAL;}
}

<O_DPREFIX>{
.*    {debug_prefix=matched;state=State::INITIAL;}
}

<O_FCNSPACE>{
.*    {fsm_codes_nspace=matched;state=State::INITIAL;}
}

<O_TTYPE>{
.*    {token_type=matched;state=State::INITIAL;}
}

<O_TPLEXER>{
.*    {templated_lexer=matched;state=State::INITIAL;}
}


<MACRO_DEF_GOBBLE_SPACE>{
\u{Space}+    {}
<<DEFAULT>>    {state=State::MACRO_DEF;}
}


<MACRO_DEF>{
.*(?=\R)    {
    str_temp.assign("(");
    str_temp.append(matched).push_back(')');
    const std::pair<std::unordered_map<std::string,std::string>::iterator,bool> emplace_ret = macro_table.try_emplace(std::move(current_regex),std::move(str_temp));
    if(!emplace_ret.second){
        fprintf(stderr,"Error: Multiple definition of macro \"%s\"!\n",emplace_ret.first->first.c_str());
        ++errors_;
    }
    state=State::INITIAL;
}
}


<CODE0>{
\u{Space}+    {}
\/\/.*\R    {} // Comments.
\{    {
    brace_level=0;
    str_temp.clear();
    state=State::CODE1;
}
.    {current_regex.append(matched);}
}


<CODE1>{
\{    {++brace_level;str_temp.push_back('{');}
\}    {
    if(brace_level!=0){
        --brace_level;
        str_temp.push_back('}');
    }else{
        yuki::trim_trailing_spaces(str_temp);
        const std::pair<std::unordered_map<std::string,std::string>::iterator,bool> emplace_ret = code_htable.try_emplace(std::move(current_regex),std::move(str_temp));
        if(!emplace_ret.second){
            fprintf(stderr,"Error: Multiple definition of code section \"%s\"!\n",emplace_ret.first->first.c_str());
            ++errors_;
        }
        state=State::INITIAL;
    }
}
'    {str_temp.push_back('\''); state_prev=State::CODE1; state=State::C_LIT;}
"    {str_temp.push_back('\"'); state_prev=State::CODE1; state=State::S_LIT;}
\u{All}   {str_temp.append(matched);}
}


<C_LIT>{
\\.    {str_temp.append(matched);}
'    {str_temp.push_back('\''); state=state_prev;}
\u{All}    {str_temp.append(matched);}
}


<S_LIT>{
\\.    {str_temp.append(matched);}
"    {str_temp.push_back('\"'); state=state_prev;}
\u{All}    {str_temp.append(matched);}
}


<SEC1>{
<[^>]*>\{    {
    current_fsm_name=matched.substr(1,matched.size()-3);
    if(current_fsm_name.compare("INITIAL")==0)
        initial_encountered=true;
    rp.recycle();
    state=State::GOBBLE_NEWLINE_TO_REGEX;
}

\%\%\u{Space}*    {
    if(!initial_encountered){
        fprintf(stderr,"Error: No \"INITIAL\" state found!\n");
        ++errors_;
    }
    write_lex_and_h1();
    state=State::SEC2;
}

\u{Space}+    {}

\/\/.*\R    {} // Comments.
}


<GOBBLE_NEWLINE_TO_REGEX>{
\R+    {}
<<DEFAULT>>    {state=State::REGEX;}
}


<REGEX>{
\u{Space}+\{\u{Space}*    {
    process_macro(str_temp,current_regex);
    rl.in.set_source(current_regex.data(),current_regex.size());
    rp.parse();
    #ifndef YUKI_LEX_MAX_REGEX_PRINTABLE
    #define YUKI_LEX_MAX_REGEX_PRINTABLE 256
    #endif
    if(str_temp.size()>YUKI_LEX_MAX_REGEX_PRINTABLE)
        str_temp.resize(YUKI_LEX_MAX_REGEX_PRINTABLE);
    current_regex=std::move(str_temp);
    brace_level=0;
    state=State::REGEX_CODE;
}
<<EOF>>\u{Space}+\{\u{Space}*    {
    brace_level=0;
    current_eof.clear();
    state=State::REGEX_CODE_EOF;
}
<<DEFAULT>>\u{Space}+\{\u{Space}*    {
    brace_level=0;
    current_default.clear();
    state=State::REGEX_CODE_DEFAULT;
}
<<BEFORE>>\u{Space}+\{\u{Space}*    {
    brace_level=0;
    current_before.clear();
    state=State::REGEX_CODE_BEFORE;
}
.    {str_temp.append(matched);}
}


<REGEX_CODE>{
\{    {++brace_level;str_temp.push_back('{');}
\}    {
    if(brace_level!=0){
        --brace_level;
        str_temp.push_back('}');
    }else{
        yuki::trim_trailing_spaces(str_temp);
        yuki::trim_trailing_spaces(current_regex);
        current_regex_codes.emplace_back(std::move(current_regex),std::move(str_temp));
        state=State::DISCARD_EVERYTHING_UNTIL_NEWLINE_TO_POST_REGEX;
    }
}
'    {str_temp.push_back('\''); state_prev=State::REGEX_CODE; state=State::C_LIT;}
"    {str_temp.push_back('\"'); state_prev=State::REGEX_CODE; state=State::S_LIT;}
\u{All}    {str_temp.append(matched);}
}


<DISCARD_EVERYTHING_UNTIL_NEWLINE_TO_POST_REGEX>{
.*\R+    {state=State::POST_REGEX;}
}


<REGEX_CODE_EOF>{
\{    {++brace_level;current_eof.push_back('{');}
\}    {
    if(brace_level!=0){
        --brace_level;
        current_eof.push_back('}');
    }else{
        yuki::trim_trailing_spaces(current_eof);
        state=State::DISCARD_EVERYTHING_UNTIL_NEWLINE_TO_POST_REGEX;
    }
}
'    {current_eof.push_back('\''); state=State::C_LIT_EOF;}
"    {current_eof.push_back('\"'); state=State::S_LIT_EOF;}
\u{All}    {current_eof.append(matched);}
}


<C_LIT_EOF>{
\\.    {current_eof.append(matched);}
'    {current_eof.push_back('\''); state=State::REGEX_CODE_EOF;}
\u{All}    {current_eof.append(matched);}
}


<S_LIT_EOF>{
\\.    {current_eof.append(matched);}
"    {current_eof.push_back('\"'); state=State::REGEX_CODE_EOF;}
\u{All}    {current_eof.append(matched);}
}


<REGEX_CODE_DEFAULT>{
\{    {++brace_level;current_default.push_back('{');}
\}   {
    if(brace_level!=0){
        --brace_level;
        current_default.push_back('}');
    }else{
        yuki::trim_trailing_spaces(current_default);
        state=State::DISCARD_EVERYTHING_UNTIL_NEWLINE_TO_POST_REGEX;
    }
}
'    {current_default.push_back('\''); state=State::C_LIT_DEFAULT;}
"    {current_default.push_back('\"'); state=State::S_LIT_DEFAULT;}
\u{All}    {current_default.append(matched);}
}


<C_LIT_DEFAULT>{
\\.    {current_default.append(matched);}
'    {current_default.push_back('\''); state=State::REGEX_CODE_DEFAULT;}
\u{All}    {current_default.append(matched);}
}


<S_LIT_DEFAULT>{
\\.    {current_default.append(matched);}
"    {current_default.push_back('\"'); state=State::REGEX_CODE_DEFAULT;}
\u{All}    {current_default.append(matched);}
}


<REGEX_CODE_BEFORE>{
\{    {++brace_level;current_before.push_back('{');}
\}    {
    if(brace_level!=0){
        --brace_level;
        current_before.push_back('}');
    }else{
        yuki::trim_trailing_spaces(current_before);
        state=State::DISCARD_EVERYTHING_UNTIL_NEWLINE_TO_POST_REGEX;
    }
}
'    {current_before.push_back('\''); state=State::C_LIT_BEFORE;}
"    {current_before.push_back('\"'); state=State::S_LIT_BEFORE;}
\u{All}    {current_before.append(matched);}
}


<C_LIT_BEFORE>{
\\.    {current_before.append(matched);}
'    {current_before.push_back('\''); state=State::REGEX_CODE_BEFORE;}
\u{All}    {current_before.append(matched);}
}


<S_LIT_BEFORE>{
\\.    {current_before.append(matched);}
"    {current_before.push_back('\"'); state=State::REGEX_CODE_BEFORE;}
\u{All}    {current_before.append(matched);}
}


<POST_REGEX>{
\u{Space}*\}    {
    if(rp.heads().size()>max_heads)
        max_heads = rp.heads().size();
    write_fsm_code_wrapped();
    named_regex_codes.emplace_back(std::move(current_fsm_name),std::move(current_regex_codes),std::move(current_eof),std::move(current_default),std::move(current_before));
    state=State::SEC1;
}

\%\%\u{Space}*    {
    fprintf(stderr,"Error: Missing closing brace for fsm \"%s\"!\n",current_fsm_name.c_str());
    ++errors_;
    if(rp.heads().size()>max_heads)
        max_heads = rp.heads().size();
    write_fsm_code_wrapped();
    named_regex_codes.emplace_back(std::move(current_fsm_name),std::move(current_regex_codes),std::move(current_eof),std::move(current_default),std::move(current_before));
    if(!initial_encountered){
        fprintf(stderr,"Error: No \"INITIAL\" state found!\n");
        ++errors_;
    }
    write_lex_and_h1();
    state=State::SEC2;
}

<<DEFAULT>>    {state=State::REGEX;}
}


<SEC2>{
\u{All}+    {
    for(const char c: matched)
        fprintf(cmd_data.fp_out_cpp,"%c",c);
    return 0;
}
}

%%
void yuki::lex::Meta_Lexer::write_h0() const {
    #define HIND YUKI_LEX_HIND
    #define IND YUKI_LEX_IND

    FILE* const out_h = cmd_data.fp_out_h;

    fprintf(out_h,"#pragma once\n");
    try{
        fprintf(out_h,"%s\n",code_htable.at("h_top").c_str());
    }catch(const std::out_of_range&){}
    fprintf(out_h,"#include%s\n\n",input_header.c_str());

    #ifndef YUKI_LEX_TARGET_DBG_REGEX_MAX_PRINT
    #define YUKI_LEX_TARGET_DBG_REGEX_MAX_PRINT 128
    #endif
    fprintf(out_h,
        "#ifdef %s\n"
        "#include<yuki/print.hpp>\n"
        "#ifndef %s_LOG\n"
        "#define %s_LOG \"%s.log\"\n"
        "#endif\n"
        "%s\n"
        "#ifndef %s_FP\n"
        "inline FILE* const %s_fp_=fopen(%s_LOG,\"w\");\n"
        "#define %s_FP %s::%s_fp_\n"
        "#endif\n"
        "%s\n"
        "#define %sO(...) yuki::dbgout_base(fp_dbg_,\"%s\",__VA_ARGS__)\n"
        "#define CONSTEXPR_%s // Debug output would render constexpr-functions non-constexpr.\n"
        "#ifndef %s_REGEX_MAX_PRINT\n"
        "#define %s_REGEX_MAX_PRINT %d\n"
        "#endif\n"
        "#else\n"
        "#define %sO(...)\n"
        "#define CONSTEXPR_%s constexpr\n"
        "#endif\n\n",
        debug_prefix.c_str(),
        debug_prefix.c_str(),
        debug_prefix.c_str(),debug_prefix.c_str(),
        nspace_head.c_str(),
        debug_prefix.c_str(),
        debug_prefix.c_str(),debug_prefix.c_str(),
        debug_prefix.c_str(),nspace.c_str(),debug_prefix.c_str(),
        nspace_tail.c_str(),
        debug_prefix.c_str(),debug_prefix.c_str(),
        debug_prefix.c_str(),
        debug_prefix.c_str(),
        debug_prefix.c_str(), YUKI_LEX_TARGET_DBG_REGEX_MAX_PRINT,
        debug_prefix.c_str(),
        debug_prefix.c_str()
    );

    try{
        fprintf(cmd_data.fp_out_cpp,"%s\n",code_htable.at("cpp_top").c_str());
    }catch(const std::out_of_range&){}
    fprintf(cmd_data.fp_out_cpp,
        "#include<cstdlib>\n"
        "#include<yuki/lex/common.hpp>\n"
        "#include<yuki/unicode.hpp>\n"
        "#include\"%s\"\n"
        "\n"
        "%s\n",
        cmd_data.out_h.c_str(),
        nspace_head.c_str()
    );
} // write_h0


void yuki::lex::Meta_Lexer::write_fsm_code_wrapped(){
    FILE* const out_cpp = cmd_data.fp_out_cpp;

    fprintf(out_cpp,
        "template<typename I>\n"
        "size_t %s::%s(I& in,typename I::Pos* const heads){\n"
        IND "using namespace yuki::literals;\n"
        IND "decltype(in.get()) c;\n"
        IND "size_t cap=0;\n"
        IND "const typename I::Pos pos_begin=in.get_pos();\n"
        IND "typename I::Pos pos_take=in.get_pos();\n",
        fsm_codes_nspace.c_str(), current_fsm_name.c_str()
    );
    const auto& heads = rp.heads();
    if(!heads.empty()){
        fprintf(out_cpp,
            IND "typename I::Pos pos_head=in.get_pos();\n"
            IND "static constexpr size_t HEAD_MAP[%zu]={",
            rp.total_branches()
        );
        size_t i=0;
        size_t head_counter=0;
        for(const size_t next_head : heads){
            for(;i<next_head;++i)
                fprintf(out_cpp,"0,");
            assert(i==next_head);
            fprintf(out_cpp,"%zu",head_counter++);
        }
        fprintf(out_cpp,"};\n");
    }else
        fprintf(out_cpp,IND "(void)heads;\n");
    #ifdef YUKI_LEX_META_DBG
    if(!cmd_data.debug_options.no_normal)
        yuki::lex::write_fsm_code(out_cpp,rp.fsms(),rp.fsms_size(),rp.max_branch_size(),rp.max_branch_number(),errors_,current_fsm_name.c_str());
    if(cmd_data.debug_options.policy_char){
        fprintf(cmd_data.debug_options.policy_char,"%s\n",current_fsm_name.c_str());
        yuki::lex::write_fsm_code(cmd_data.debug_options.policy_char,rp.fsms(),rp.fsms_size(),rp.max_branch_size(),rp.max_branch_number(),errors_,current_fsm_name.c_str(),{cmd_data.debug_options.policy_char,nullptr});
        fprintf(cmd_data.debug_options.policy_char,"\n\n");
    }
    if(cmd_data.debug_options.simple_accumulate){
        fprintf(cmd_data.debug_options.simple_accumulate,"%s\n",current_fsm_name.c_str());
        yuki::lex::write_fsm_code(cmd_data.debug_options.simple_accumulate,rp.fsms(),rp.fsms_size(),rp.max_branch_size(),rp.max_branch_number(),errors_,current_fsm_name.c_str(),{nullptr,cmd_data.debug_options.simple_accumulate});
        fprintf(cmd_data.debug_options.simple_accumulate,"\n\n");
    }
    if(cmd_data.debug_options.text){
        fprintf(cmd_data.debug_options.text,"%s\n",current_fsm_name.c_str());
        yuki::lex::write_fsm_code(cmd_data.debug_options.text,rp.fsms(),rp.fsms_size(),rp.max_branch_size(),rp.max_branch_number(),errors_,current_fsm_name.c_str());
        fprintf(cmd_data.debug_options.text,"\n\n");
    }
    #else
    yuki::lex::write_fsm_code(out_cpp,rp.fsms(),rp.fsms_size(),rp.max_branch_size(),rp.max_branch_number(),errors_,current_fsm_name.c_str());
    #endif
    fprintf(out_cpp,
        "} // %s::%s\n"
        "\n\n",
        fsm_codes_nspace.c_str(), current_fsm_name.c_str()
    );
} // write_fsm_code_wrapped


void yuki::lex::Meta_Lexer::write_lex_and_h1(){
    FILE* const out_cpp = cmd_data.fp_out_cpp;
    FILE* const out_h = cmd_data.fp_out_h;

    fprintf(out_h,
        "%s\n"
        "namespace %s{\n",
        nspace_head.c_str(),
        fsm_codes_nspace.c_str()
    );

    fprintf(out_cpp,
        "%s\n"
        "%s %s::lex(%s){\n"
        "while(1){\n"
        "const %s::Pos pos_begin=in.get_pos();\n"
        "switch(state){\n",
        template_decl.c_str(),
        token_type.c_str(), template_decl.empty()?lexer.c_str():templated_lexer.c_str(), lex_params.c_str(),
        input_class.c_str()
    );

    str_temp.clear(); // Used for `State` names.
    const std::unordered_map<std::string,std::string>::const_iterator code_htable_end = code_htable.end();
    const std::unordered_map<std::string,std::string>::const_iterator eof_global_i = code_htable.find("eof");
    const bool eof_global = eof_global_i!=code_htable_end;
    const std::unordered_map<std::string,std::string>::const_iterator default_global_i = code_htable.find("default");
    const bool default_global = default_global_i!=code_htable_end;
    const std::unordered_map<std::string,std::string>::const_iterator before_global_i = code_htable.find("before");
    const bool before_global = before_global_i!=code_htable_end;

    for(const Named_Regex_Codes& nrc : named_regex_codes){
        str_temp.append(nrc.name).push_back(',');
        fprintf(out_h,
            IND "template<typename I>\n"
            IND "size_t %s(I&,typename I::Pos*);\n",
            nrc.name.c_str()
        );

        fprintf(out_cpp,"case State::%s:{\n",nrc.name.c_str());

        if(max_heads!=0)
            fprintf(out_cpp,IND "clear_heads();\n");

        if(!nrc.before_code.empty())
            fprintf(out_cpp,
                IND IND IND "{\n"
                "%s\n"
                IND IND IND "}\n",
                nrc.before_code.c_str()
            );
        else if(before_global)
            fprintf(out_cpp,
                IND IND IND "{\n"
                "%s\n"
                IND IND IND "}\n",
                before_global_i->second.c_str()
            );

        fprintf(out_cpp,
            IND "switch(%s::%s(in,%s)){\n"
            IND "case 0:{\n"
            IND IND "if(!in.getable()){\n"
            IND IND IND "%sO(\"State=%s EOF\\n\");\n",
            fsm_codes_nspace.c_str(), nrc.name.c_str(), max_heads!=0?"heads":"nullptr",
            debug_prefix.c_str(), nrc.name.c_str()
        );

        if(!nrc.eof_code.empty())
            fprintf(out_cpp,
                IND IND IND "{\n"
                "%s\n"
                IND IND IND "}\n",
                nrc.eof_code.c_str()
            );
        else if(eof_global)
            fprintf(out_cpp,
                IND IND IND "{\n"
                "%s\n"
                IND IND IND "}\n",
                eof_global_i->second.c_str()
            );
        else
            fprintf(out_cpp,IND IND IND "return %s();\n",token_type.c_str());

        fprintf(out_cpp,
            IND IND "}else{ // if(!in.getable())\n"
            IND IND IND "%sO(\"State=%s DEFAULT\\n\");\n",
            debug_prefix.c_str(),nrc.name.c_str()
        );

        if(!nrc.default_code.empty())
            fprintf(out_cpp,
                IND IND IND "{\n"
                "%s\n"
                IND IND IND "}\n",
                nrc.default_code.c_str()
            );
        else if(default_global)
            fprintf(out_cpp,
                IND IND IND "{\n"
                "%s\n"
                IND IND IND "}\n",
                default_global_i->second.c_str()
            );
        else
            fprintf(out_cpp,
                IND IND IND "fprintf(stderr,\"YLEX Error: Lexer jammed at state %s!\\n\");\n"
                IND IND IND "exit(EXIT_FAILURE);\n",
                nrc.name.c_str()
            );

        fprintf(out_cpp,
            IND IND "} // if(!in.getable()) else\n"
            IND IND "break;\n"
            IND "} // case 0\n"
        );

        size_t i=1;
        for(const Regex_Code& rc : nrc.regex_codes){
            fprintf(out_cpp,
                IND "case %zu:{ // %s\n"
                IND IND "matched=in.matched(pos_begin);\n"
                IND IND "%sO(\"State=%s cap=%zu matched={} len={}\\n\",matched.substr(0,%s_REGEX_MAX_PRINT),matched.size());\n"
                IND IND "{\n"
                "%s\n"
                IND IND "}\n"
                IND IND "in.clear_matched();\n"
                IND IND "break;\n"
                IND "} // case %zu // %s\n",
                i, rc.regex.c_str(),
                debug_prefix.c_str(), nrc.name.c_str(), i, debug_prefix.c_str(),
                rc.code.c_str(),
                i, rc.regex.c_str()
            );
            ++i;
        }

        fprintf(out_cpp,
            IND "} // switch(%s::%s(in,heads))\n"
            IND "break;\n"
            "} // case State::%s\n",
            fsm_codes_nspace.c_str(), nrc.name.c_str(),
            nrc.name.c_str()
        );
    } // for(const Named_Regex_Codes& nrc : named_regex_codes)

    fprintf(out_cpp,
        "} // switch(state)\n"
        "} // while(1)\n"
        "} // %s %s::lex(%s)\n"
        "%s\n"
        "\n\n\n\n",
        token_type.c_str(), lexer.c_str(), lex_params.c_str(),
        nspace_tail.c_str()
    );

    fprintf(out_h,
        "} // namespace %s\n"
        "\n"
        "%s\n"
        "struct %s{\n"
        IND "enum struct State {%s} state=State::INITIAL;\n"
        IND "std::string_view matched;\n"
        IND "%s in;\n"
        IND "#ifdef %s\n"
        IND "FILE* fp_dbg_=%s_FP;\n"
        IND "#endif\n\n",
        fsm_codes_nspace.c_str(),
        template_decl.c_str(),
        lexer.c_str(),
        str_temp.c_str(),
        input_class.c_str(),
        debug_prefix.c_str(),
        debug_prefix.c_str()
    );
    if(!no_default_ctor)
        fprintf(out_h,
            IND "%s() noexcept=default;\n"
            "\n"
            IND "template<typename... Args>\n"
            IND "explicit %s(Args&&... args) noexcept : in(std::forward<Args>(args)...) {}\n",
            lexer.c_str(),
            lexer.c_str()
        );
    if(max_heads!=0){
        fprintf(out_h,
            HIND "protected:\n"
            IND "%s::Pos heads[%zu];\n"
            IND "void clear_heads(){\n"
            IND IND "static_assert(std::is_trivially_copyable_v<%s::Pos>);\n"
            IND IND "memset(heads,0,sizeof(heads));\n"
            IND "}\n",
            input_class.c_str(), max_heads,
            input_class.c_str()
        );
    }
    fprintf(out_h,HIND "public:\n");
    try{
        fprintf(out_h,"%s\n",code_htable.at("class").c_str());
    }catch(const std::out_of_range&){}
    fprintf(out_h,
        HIND "public:\n"
        IND "%s lex(%s);\n"
        "}; // struct %s\n"
        "%s\n"
        "\n"
        "\n",
        token_type.c_str(), lex_params.c_str(),
        lexer.c_str(),
        nspace_tail.c_str()
    );
} // write_lex_and_h1
