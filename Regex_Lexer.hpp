#pragma once
#include"include/yuki/lex/Input.hpp"
#include"include/yuki/lex/get_u8.hpp"
#include"gen/Regex_Parser.token.hpp"
#include<cstdlib>
#include<unordered_map>
#include<yuki/CHashTable.hpp>
#include<yuki/mmhash3.hpp>
#include<yuki/Interval.hpp>

namespace yuki::lex{

constexpr yuki::CInterval<char32_t> cc_dot[] = {{0,U'\n'-1},{U'\n'+1,U'\r'-1},{U'\r'+1,0x10FFFF}};
constexpr yuki::CInterval<char32_t> cc_dot_ascii[] = {{0,U'\n'-1},{U'\n'+1,U'\r'-1},{U'\r'+1,127}};
constexpr yuki::CInterval<char32_t> cc_dot_byte[] = {{0,U'\n'-1},{U'\n'+1,U'\r'-1},{U'\r'+1,255}};
constexpr yuki::CInterval<char32_t> cc_all[] = {{0,0x10FFFF}};
constexpr yuki::CInterval<char32_t> cc_all_byte[] = {{0,255}};
constexpr yuki::CInterval<char32_t> cc_newline[] = {{U'\n',U'\n'},{U'\r',U'\r'}};
// POSIX catetories
constexpr yuki::CInterval<char32_t> cc_ascii[] = {{0,127}};
constexpr yuki::CInterval<char32_t> cc_space[] = {{U'\t',U'\r'},{U' ',U' '}};
constexpr yuki::CInterval<char32_t> cc_xdigit[] = {{U'0',U'9'},{U'A',U'F'},{U'a',U'f'}};
constexpr yuki::CInterval<char32_t> cc_cntrl[] = {{0,0x1F},{127,127}};
constexpr yuki::CInterval<char32_t> cc_print[] = {{0x20,0x7E}};
constexpr yuki::CInterval<char32_t> cc_alnum[] = {{U'0',U'9'},{U'A',U'Z'},{U'a',U'z'}};
constexpr yuki::CInterval<char32_t> cc_alpha[] = {{U'A',U'Z'},{U'a',U'z'}};
constexpr yuki::CInterval<char32_t> cc_blank[] = {{U'\t',U'\t'},{U' ',U' '}};
constexpr yuki::CInterval<char32_t> cc_digit[] = {{U'0',U'9'}};
constexpr yuki::CInterval<char32_t> cc_graph[] = {{0x21,0x7E}};
constexpr yuki::CInterval<char32_t> cc_lower[] = {{U'a',U'z'}};
constexpr yuki::CInterval<char32_t> cc_punct[] = {{0x21,0x2F},{0x3A,0x40},{0x5B,0x60},{0x7B,0x7E}};
constexpr yuki::CInterval<char32_t> cc_upper[] = {{U'A',U'Z'}};
constexpr yuki::CInterval<char32_t> cc_word[] = {{U'0',U'9'},{U'A',U'Z'},{U'_',U'_'},{U'a',U'z'}};
// One unicode category
constexpr yuki::CInterval<char32_t> cc_uspace[] = {{U'\t',U'\r'},{U' ',U' '},{0x85,0x85},{0xA0,0xA0},{0x1680,0x1680},{0x2000,0x200A},{0x2028,0x2029},{0x202F,0x202F},{0x205F,0x205F},{0x3000,0x3000}};

struct Name_CC{
    std::string_view name;
    struct CC_View{
        const yuki::CInterval<char32_t>* data;
        size_t size;
    } ccv;

    struct Name{
        constexpr std::string_view operator()(const Name_CC ncc) const {return ncc.name;}
    };
};

struct MMHash3_SV{
    constexpr size_t operator()(const std::string_view sv) const {return yuki::mmhash3(sv.data(),sv.size());}
};

struct Name_CC_Nil{
    constexpr bool operator()(const Name_CC ncc) const {return ncc.ccv.size==0;}
};

constexpr yuki::CHashTable<std::string_view,Name_CC,Name_CC::Name,MMHash3_SV,yuki::Equal_To<std::string_view>,Name_CC_Nil,64> posix_cc_table = {
    {"ASCII",{cc_ascii,sizeof(cc_ascii)/sizeof(yuki::CInterval<char32_t>)}},
    {"Space",{cc_space,sizeof(cc_space)/sizeof(yuki::CInterval<char32_t>)}},
    {"XDigit",{cc_xdigit,sizeof(cc_xdigit)/sizeof(yuki::CInterval<char32_t>)}},
    {"Cntrl",{cc_cntrl,sizeof(cc_cntrl)/sizeof(yuki::CInterval<char32_t>)}},
    {"Print",{cc_print,sizeof(cc_print)/sizeof(yuki::CInterval<char32_t>)}},
    {"Alnum",{cc_alnum,sizeof(cc_alnum)/sizeof(yuki::CInterval<char32_t>)}},
    {"Alpha",{cc_alpha,sizeof(cc_alpha)/sizeof(yuki::CInterval<char32_t>)}},
    {"Blank",{cc_blank,sizeof(cc_blank)/sizeof(yuki::CInterval<char32_t>)}},
    {"Digit",{cc_digit,sizeof(cc_digit)/sizeof(yuki::CInterval<char32_t>)}},
    {"Graph",{cc_graph,sizeof(cc_graph)/sizeof(yuki::CInterval<char32_t>)}},
    {"Lower",{cc_lower,sizeof(cc_lower)/sizeof(yuki::CInterval<char32_t>)}},
    {"Punct",{cc_punct,sizeof(cc_punct)/sizeof(yuki::CInterval<char32_t>)}},
    {"Upper",{cc_upper,sizeof(cc_upper)/sizeof(yuki::CInterval<char32_t>)}},
    {"Word",{cc_word,sizeof(cc_word)/sizeof(yuki::CInterval<char32_t>)}},
    {"Dot",{cc_dot_ascii,sizeof(cc_dot_ascii)/sizeof(yuki::CInterval<char32_t>)}},
    {"BDot",{cc_dot_byte,sizeof(cc_dot_byte)/sizeof(yuki::CInterval<char32_t>)}},
    {"Byte",{cc_all_byte,sizeof(cc_all_byte)/sizeof(yuki::CInterval<char32_t>)}},
};

constexpr yuki::CHashTable<std::string_view,Name_CC,Name_CC::Name,MMHash3_SV,yuki::Equal_To<std::string_view>,Name_CC_Nil,8> unicode_cc_table={
    {"All",{cc_all,sizeof(cc_all)/sizeof(yuki::CInterval<char32_t>)}},
    {"Space",{cc_uspace,sizeof(cc_uspace)/sizeof(yuki::CInterval<char32_t>)}},
};

#ifndef YUKI_LEX_MAX_MACRO_EXPANSION
#define YUKI_LEX_MAX_MACRO_EXPANSION 128
#endif

struct Regex_Lexer{
SV_Input in;
std::unordered_map<std::string,std::string> macro_table;
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
                        if(const Name_CC ncc=unicode_cc_table[std::string_view(begin,end)]; ncc.ccv.size!=0)
                            return Token_t(yuki::pg::in_place_kind<Token_Kind::basic_char_class>,{},yuki::from_ordered_tag,ncc.ccv.data,ncc.ccv.size);
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
                    if(const Name_CC ncc=posix_cc_table[std::string_view(begin,end)]; ncc.ccv.size!=0)
                        return Token_t(yuki::pg::in_place_kind<Token_Kind::basic_char_class>,{},yuki::from_ordered_tag,ncc.ccv.data,ncc.ccv.size);
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
        case U'.'_u8.raw(): return Token_t(yuki::pg::in_place_kind<Token_Kind::basic_char_class>,{},yuki::from_ordered_tag,cc_dot,sizeof(cc_dot)/sizeof(yuki::CInterval<char32_t>));
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