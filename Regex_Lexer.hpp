#pragma once
#include"include/yuki/lex/Input.hpp"
#include"include/yuki/lex/get_u8.hpp"
#include"gen/Regex_Parser.token.hpp"
#include<cstdlib>
#include<yuki/CHashTable_Str.hpp>
#include<yuki/Interval.hpp>
#include<yuki/unordered_map_str.hpp>
#include<yuki/unicode/general_category.h>
#include<yuki/unicode/scripts.h>
#include<yuki/unicode/blocks.hpp>
#include<yuki/unicode/binary_properties.h>

namespace yuki::lex{

inline constexpr yuki::CHashTable_Str<yuki::unicode::Name_CC,yuki::unicode::Name_CC::Name,yuki::unicode::Name_CC::Nil,64> posix_cc_table = {
    {"ASCII",yuki::cc_ascii},
    {"Space",yuki::cc_space},
    {"XDigit",yuki::cc_xdigit},
    {"Cntrl",yuki::cc_cntrl},
    {"Print",yuki::cc_print},
    {"Alnum",yuki::cc_alnum},
    {"Alpha",yuki::cc_alpha},
    {"Blank",yuki::cc_blank},
    {"Digit",yuki::cc_digit},
    {"Graph",yuki::cc_graph},
    {"Lower",yuki::cc_lower},
    {"Punct",yuki::cc_punct},
    {"Upper",yuki::cc_upper},
    {"Word",yuki::cc_word},
    {"Dot",yuki::cc_dot_ascii},
    {"BDot",yuki::cc_dot_byte},
    {"Byte",yuki::cc_all_byte},
};

inline constexpr struct Unicode_CC_Table : private yuki::CHashTable_Str<yuki::unicode::Name_CC,yuki::unicode::Name_CC::Name,yuki::unicode::Name_CC::Nil,4096> {
    typedef yuki::CHashTable_Str<yuki::unicode::Name_CC,yuki::unicode::Name_CC::Name,yuki::unicode::Name_CC::Nil,4096> CHT;

    constexpr Unicode_CC_Table() noexcept :
        CHT{{"All",yuki::unicode::All}}
    {
        using namespace yuki::unicode;
        for(const Name_CC_Num<GCategory> nccn : gcategory_table)
            CHT::emplace(Name_CC(nccn.name,nccn.cc,nccn.cc_size));
        for(const Name_CC_Num<Script> nccn : script_table)
            CHT::emplace(Name_CC(nccn.name,nccn.cc,nccn.cc_size));
        for(const Name_CC_Num<Block> nccn : block_table)
            CHT::emplace(Name_CC(nccn.name,nccn.cc,nccn.cc_size));
        for(const Name_CC ncc : bproperty_table)
            CHT::emplace(ncc);
    }

    using CHT::find;
} unicode_cc_table;

#ifndef YUKI_LEX_MAX_MACRO_EXPANSION
#define YUKI_LEX_MAX_MACRO_EXPANSION 128
#endif

struct Regex_Lexer{
SV_Input in;
yuki::unordered_map_str<std::string,std::string> macro_table;
yuki::Vector<std::string_view> macro_stack;
unsigned& errors;

Regex_Lexer(unsigned& e) noexcept : errors(e) {}

yuki::lex::Regex_Parser_TS::Token_t lex(){
    using namespace yuki::literals;
    typedef Regex_Parser_TS::Token_Kind Token_Kind;
    typedef Regex_Parser_TS::Token_t Token_t;

    yuki::U8Char u8c;
  next_char:
    u8c=get_u8(in);
    switch(u8c.raw()){
        case U'('_u8.raw():
            return Token_t(yuki::pg::in_place_kind<Token_Kind::paren_l>,{});
        case U')'_u8.raw():
            return Token_t(yuki::pg::in_place_kind<Token_Kind::paren_r>,{});
        case U'['_u8.raw():
            return Token_t(yuki::pg::in_place_kind<Token_Kind::sqparen_l>,{});
        case U']'_u8.raw():
            return Token_t(yuki::pg::in_place_kind<Token_Kind::sqparen_r>,{});
        case U'*'_u8.raw():
            return Token_t(yuki::pg::in_place_kind<Token_Kind::ast>,{});
        case U'+'_u8.raw():
            return Token_t(yuki::pg::in_place_kind<Token_Kind::plus>,{});
        case U'|'_u8.raw():
            return Token_t(yuki::pg::in_place_kind<Token_Kind::vbar>,{});
        case U'^'_u8.raw():
            return Token_t(yuki::pg::in_place_kind<Token_Kind::hat>,{});
        case U'-'_u8.raw():
            return Token_t(yuki::pg::in_place_kind<Token_Kind::to>,{});
        case U'$'_u8.raw():
            return Token_t(yuki::pg::in_place_kind<Token_Kind::meta_char>,{},MetaChar::EOL);
        case U'?'_u8.raw():{
            switch(in.peek()){
                case '='_uc:{
                    in.remove_prefix(1);
                    return Token_t(yuki::pg::in_place_kind<Token_Kind::qe>,{});
                }
                case 'l'_uc:{
                    in.remove_prefix(1);
                    get_u8(in);
                    return Token_t(yuki::pg::in_place_kind<Token_Kind::lazy>,{});
                }
                case 'd'_uc:{
                    in.remove_prefix(1);
                    get_u8(in);
                    return Token_t(yuki::pg::in_place_kind<Token_Kind::dlazy>,{});
                }
                default: return Token_t(yuki::pg::in_place_kind<Token_Kind::qmark>,{});
            }
        }
        case U'\\'_u8.raw():{
            u8c=get_u8(in);
            switch(u8c.raw()){
                case U'A'_u8.raw():
                    return Token_t(yuki::pg::in_place_kind<Token_Kind::meta_char>,{},MetaChar::BOI);
                case U'Z'_u8.raw():
                    return Token_t(yuki::pg::in_place_kind<Token_Kind::meta_char>,{},MetaChar::EOI);
                case U'z'_u8.raw():
                    return Token_t(yuki::pg::in_place_kind<Token_Kind::meta_char>,{},MetaChar::EoF);
                case U'b'_u8.raw():
                    return Token_t(yuki::pg::in_place_kind<Token_Kind::meta_char>,{},MetaChar::WB);
                case U'B'_u8.raw():
                    return Token_t(yuki::pg::in_place_kind<Token_Kind::meta_char>,{},-MetaChar::WB);
                case U'a'_u8.raw():
                    return Token_t(yuki::pg::in_place_kind<Token_Kind::character>,{},U'\a');
                case U'f'_u8.raw():
                    return Token_t(yuki::pg::in_place_kind<Token_Kind::character>,{},U'\f');
                case U'n'_u8.raw():
                    return Token_t(yuki::pg::in_place_kind<Token_Kind::character>,{},U'\n');
                case U'r'_u8.raw():
                    return Token_t(yuki::pg::in_place_kind<Token_Kind::character>,{},U'\r');
                case U't'_u8.raw():
                    return Token_t(yuki::pg::in_place_kind<Token_Kind::character>,{},U'\t');
                case U'v'_u8.raw():
                    return Token_t(yuki::pg::in_place_kind<Token_Kind::character>,{},U'\v');
                case U'_'_u8.raw():
                    return Token_t(yuki::pg::in_place_kind<Token_Kind::character>,{},U' ');
                case U'h'_u8.raw():
                    return Token_t(yuki::pg::in_place_kind<Token_Kind::basic_char_class>,{},yuki::from_ordered_tag,cc_blank,sizeof(cc_blank)/sizeof(yuki::CInterval<char32_t>));
                case U'R'_u8.raw():
                    return Token_t(yuki::pg::in_place_kind<Token_Kind::basic_char_class>,{},yuki::from_ordered_tag,cc_newline,sizeof(cc_newline)/sizeof(yuki::CInterval<char32_t>));
                case U'N'_u8.raw():
                    return Token_t(yuki::pg::in_place_kind<Token_Kind::esc_N>,{});
                case U'u'_u8.raw():{
                    if(in.peek()=='{'_uc){
                        in.remove_prefix(1);
                        const char* const begin = in.data;
                        const char* const end = strchr(begin,'}'_uc);
                        if(!end){
                            fprintf(stderr,"Error: Incomplete unicode character caterory name \"%s\"!\n",begin);
                            ++errors;
                            if(!macro_stack.empty()){
                                in.set_source(macro_stack.pop_back_v());
                                goto next_char;
                            }else
                                return Token_t(yuki::pg::in_place_kind<Token_Kind::EOF_>,{});
                        }
                        in.set_pos(end+1);
                        if(const yuki::unicode::Name_CC* const ncc=unicode_cc_table.find(std::string_view(begin,end)); ncc)
                            return Token_t(yuki::pg::in_place_kind<Token_Kind::basic_char_class>,{},yuki::from_ordered_tag,ncc->cc,ncc->cc_size);
                        else{
                            fprintf(stderr,"Error: Unknown unicode character caterory name \"");
                            for(const char* i=begin;i!=end;++i)
                                fprintf(stderr,"%c",*i);
                            fprintf(stderr,"\"!\n");
                            ++errors;
                            return Token_t(yuki::pg::in_place_kind<Token_Kind::basic_char_class>,{},yuki::CInterval<char32_t>{0,yuki::UNICODE_MAX_32});
                        }
                    }else
                        goto uUxX;
                }
                case U'U'_u8.raw():
                case U'x'_u8.raw():
                case U'X'_u8.raw():{
                    uUxX:
                    char* end;
                    const unsigned long ul = strtoul(in.data,&end,16);
                    in.set_pos(end);
                    if(ul>yuki::UNICODE_MAX_32){
                        fprintf(stderr,"Error: Unicode character %lx exceeds the max!\n",ul);
                        ++errors;
                        return Token_t(yuki::pg::in_place_kind<Token_Kind::character>,{},yuki::UNICODE_MAX_32);
                    }else
                        return Token_t(yuki::pg::in_place_kind<Token_Kind::character>,{},ul);
                }
                case U'p'_u8.raw():{
                    get_u8(in);
                    const char* const begin = in.data;
                    const char* const end = strchr(begin,'}'_uc);
                    if(!end){
                        fprintf(stderr,"Error: Incomplete POSIX character caterory name \"%s\"!\n",begin);
                        ++errors;
                        if(!macro_stack.empty()){
                            in.set_source(macro_stack.pop_back_v());
                            goto next_char;
                        }else
                            return Token_t(yuki::pg::in_place_kind<Token_Kind::EOF_>,{});
                    }
                    in.set_pos(end+1);
                    if(const yuki::unicode::Name_CC* const ncc=posix_cc_table.find(std::string_view(begin,end)); ncc)
                        return Token_t(yuki::pg::in_place_kind<Token_Kind::basic_char_class>,{},yuki::from_ordered_tag,ncc->cc,ncc->cc_size);
                    else{
                        fprintf(stderr,"Error: Unknown POSIX character caterory name \"");
                        for(const char* i=begin;i!=end;++i)
                            fprintf(stderr,"%c",*i);
                        fprintf(stderr,"\"!\n");
                        ++errors;
                        return Token_t(yuki::pg::in_place_kind<Token_Kind::basic_char_class>,{},yuki::from_ordered_tag,cc_ascii,sizeof(cc_ascii)/sizeof(yuki::CInterval<char32_t>));
                    }
                }
                case yuki::EOF_U8.raw():{
                    fprintf(stderr,"Error: Incomplete escape character at the end!\n");
                    ++errors;
                    if(!macro_stack.empty())
                        in.set_source(macro_stack.pop_back_v());
                    return Token_t(yuki::pg::in_place_kind<Token_Kind::character>,{},U'\\');
                }
                default:
                    return Token_t(yuki::pg::in_place_kind<Token_Kind::character>,{},static_cast<char32_t>(u8c));
            } // switch(u8c.raw())
        } // case U'\\'_u8.raw()
        case U'{'_u8.raw():{
            switch(in.peek()){
                case '0'_uc:
                case '1'_uc:
                case '2'_uc:
                case '3'_uc:
                case '4'_uc:
                case '5'_uc:
                case '6'_uc:
                case '7'_uc:
                case '8'_uc:
                case '9'_uc:{
                    const char* const begin0 = in.data;
                    char* end;
                    const unsigned long long lb = strtoull(in.data,&end,10);
                    in.set_pos(end+1);
                    const char* const begin1 = in.data;
                    const unsigned long long ub = strtoull(in.data,&end,10);
                    in.set_pos(end+1);
                    if(end!=begin1)
                        return Token_t(yuki::pg::in_place_kind<Token_Kind::amount>,{},lb,ub);
                    else
                        return Token_t(yuki::pg::in_place_kind<Token_Kind::amount>,{},lb,(size_t)-1);
                }
                default:{
                    const char* const mbegin = in.data;
                    const char* const end = strchr(mbegin,'}'_uc);
                    if(!end){
                        fprintf(stderr,"Error: Incomplete macro name \"%s\"!\n",mbegin);
                        ++errors;
                        if(!macro_stack.empty()){
                            in.set_source(macro_stack.pop_back_v());
                            goto next_char;
                        }else
                            return Token_t(yuki::pg::in_place_kind<Token_Kind::EOF_>,{});
                    }
                    in.set_pos(end+1);
                    if(in.getable())
                        macro_stack.emplace_back(in.data,in.size);
                    const std::string macro_name(mbegin,end);
                    try{
                        in.set_source(macro_table.at(macro_name));
                    }catch(const std::out_of_range&){
                        fprintf(stderr,"Error: Unknown macro name \"%s\"!\n",macro_name.c_str());
                        ++errors;
                        if(in.getable())
                            macro_stack.pop_back();
                    }
                    goto next_char;
                }
            } // switch(in.peek())
        } // case U'{'_u8.raw()
        case U'.'_u8.raw(): return Token_t(yuki::pg::in_place_kind<Token_Kind::basic_char_class>,{},yuki::from_ordered_tag,yuki::unicode::Dot,sizeof(yuki::unicode::Dot)/sizeof(yuki::CInterval<char32_t>));
        case yuki::EOF_U8.raw():{
            if(!macro_stack.empty()){
                in.set_source(macro_stack.pop_back_v());
                goto next_char;
            }else
                return Token_t(yuki::pg::in_place_kind<Token_Kind::EOF_>,{});
        }
        default: return Token_t(yuki::pg::in_place_kind<Token_Kind::character>,{},static_cast<char32_t>(u8c));
    } // switch(u8c.raw())
} // lex
}; // struct Regex_Lexer

} // namespace yuki::lex