%namespace yuki::lex
%lexer Regex_Lexer
%token_type yuki::lex::Regex_Parser_TS::Token_t

%no_default_ctor

%code cpp_top{
#include"cconfig"
#include<cstdlib>
#include<charconv>
#include<yuki/unicode.hpp>
}

%code h_top{
#include"gen/Regex_Parser.token.hpp"
}

%code class{
  private:
    typedef Regex_Parser_TS::Token_Kind Token_Kind;
    typedef Regex_Parser_TS::Token_t Token_t;

    unsigned& errors;
  public:
    Regex_Lexer(unsigned& e) noexcept :
        errors(e)
    {}
}

%%
<INITIAL>{
\(    {return Token_t(yuki::pg::in_place_kind<Token_Kind::paren_l>,{});}
\)    {return Token_t(yuki::pg::in_place_kind<Token_Kind::paren_r>,{});}
\[    {return Token_t(yuki::pg::in_place_kind<Token_Kind::sqparen_l>,{});}
\]    {return Token_t(yuki::pg::in_place_kind<Token_Kind::sqparen_r>,{});}
\*    {return Token_t(yuki::pg::in_place_kind<Token_Kind::ast>,{});}
\+    {return Token_t(yuki::pg::in_place_kind<Token_Kind::plus>,{});}
\?    {return Token_t(yuki::pg::in_place_kind<Token_Kind::qmark>,{});}
\?=    {return Token_t(yuki::pg::in_place_kind<Token_Kind::qe>,{});}
\?l:    {return Token_t(yuki::pg::in_place_kind<Token_Kind::lazy>,{});}
\?d:    {return Token_t(yuki::pg::in_place_kind<Token_Kind::dlazy>,{});}
\|    {return Token_t(yuki::pg::in_place_kind<Token_Kind::vbar>,{});}
\^    {return Token_t(yuki::pg::in_place_kind<Token_Kind::hat>,{});}
\-    {return Token_t(yuki::pg::in_place_kind<Token_Kind::to>,{});}

\$    {return Token_t(yuki::pg::in_place_kind<Token_Kind::meta_char>,{},MetaChar::EOL);}
\\A    {return Token_t(yuki::pg::in_place_kind<Token_Kind::meta_char>,{},MetaChar::BOI);}
\\Z    {return Token_t(yuki::pg::in_place_kind<Token_Kind::meta_char>,{},MetaChar::EOI);}
\\z    {return Token_t(yuki::pg::in_place_kind<Token_Kind::meta_char>,{},MetaChar::EoF);}
\\b    {return Token_t(yuki::pg::in_place_kind<Token_Kind::meta_char>,{},MetaChar::WB);}
\\B    {return Token_t(yuki::pg::in_place_kind<Token_Kind::meta_char>,{},-MetaChar::WB);}

\{[0-9]+,[0-9]+\}    {
    char* next = nullptr;
    const size_t lb = strtoull(matched.data()+1,&next,10);
    return Token_t(yuki::pg::in_place_kind<Token_Kind::amount>,{},lb,strtoull(next+1,nullptr,10));
}
\{[0-9]+,\}    {return Token_t(yuki::pg::in_place_kind<Token_Kind::amount>,{},strtoull(matched.data()+1,nullptr,10),(size_t)-1);}

\\[uUxX][0-9a-fA-F]+    {
    unsigned long ul;
    std::from_chars(matched.cbegin()+2,matched.cend(),ul,16);
    if(ul>yuki::UNICODE_MAX_32){
        fprintf(stderr,"Error: Unicode character %lx exceeds the max!\n",ul);
        return Token_t(yuki::pg::in_place_kind<Token_Kind::character>,{},yuki::UNICODE_MAX_32);
    }else
        return Token_t(yuki::pg::in_place_kind<Token_Kind::character>,{},ul);
}

\\a    {return Token_t(yuki::pg::in_place_kind<Token_Kind::character>,{},U'\a');}
\\f    {return Token_t(yuki::pg::in_place_kind<Token_Kind::character>,{},U'\f');}
\\n    {return Token_t(yuki::pg::in_place_kind<Token_Kind::character>,{},U'\n');}
\\r    {return Token_t(yuki::pg::in_place_kind<Token_Kind::character>,{},U'\r');}
\\t    {return Token_t(yuki::pg::in_place_kind<Token_Kind::character>,{},U'\t');}
\\v    {return Token_t(yuki::pg::in_place_kind<Token_Kind::character>,{},U'\v');}
\\_    {return Token_t(yuki::pg::in_place_kind<Token_Kind::character>,{},U' ');}

\\p\{ASCII\}    {return Token_t(yuki::pg::in_place_kind<Token_Kind::basic_char_class>,{},cc_ascii);}
\\p\{Space\}    {return Token_t(yuki::pg::in_place_kind<Token_Kind::basic_char_class>,{},cc_space);}
\\p\{XDigit\}    {return Token_t(yuki::pg::in_place_kind<Token_Kind::basic_char_class>,{},cc_xdigit);}
\\p\{Cntrl\}    {return Token_t(yuki::pg::in_place_kind<Token_Kind::basic_char_class>,{},cc_cntrl);}
\\p\{Print\}    {return Token_t(yuki::pg::in_place_kind<Token_Kind::basic_char_class>,{},cc_print);}
\\p\{Alnum\}    {return Token_t(yuki::pg::in_place_kind<Token_Kind::basic_char_class>,{},cc_alnum);}
\\p\{Alpha\}    {return Token_t(yuki::pg::in_place_kind<Token_Kind::basic_char_class>,{},cc_alpha);}
\\p\{Blank\}    {return Token_t(yuki::pg::in_place_kind<Token_Kind::basic_char_class>,{},cc_blank);}
\\h    {return Token_t(yuki::pg::in_place_kind<Token_Kind::basic_char_class>,{},cc_blank);}
\\p\{Digit\}    {return Token_t(yuki::pg::in_place_kind<Token_Kind::basic_char_class>,{},cc_digit);}
\\p\{Graph\}    {return Token_t(yuki::pg::in_place_kind<Token_Kind::basic_char_class>,{},cc_graph);}
\\p\{Lower\}    {return Token_t(yuki::pg::in_place_kind<Token_Kind::basic_char_class>,{},cc_lower);}
\\p\{Punct\}    {return Token_t(yuki::pg::in_place_kind<Token_Kind::basic_char_class>,{},cc_punct);}
\\p\{Upper\}    {return Token_t(yuki::pg::in_place_kind<Token_Kind::basic_char_class>,{},cc_upper);}
\\p\{Word\}    {return Token_t(yuki::pg::in_place_kind<Token_Kind::basic_char_class>,{},cc_word);}
\\p\{Dot\}    {return Token_t(yuki::pg::in_place_kind<Token_Kind::basic_char_class>,{},cc_dot_ascii);}
\\p\{BDot\}    {return Token_t(yuki::pg::in_place_kind<Token_Kind::basic_char_class>,{},cc_dot_byte);}
\\p\{Byte\}    {return Token_t(yuki::pg::in_place_kind<Token_Kind::basic_char_class>,{},cc_all_byte);}
\\R    {return Token_t(yuki::pg::in_place_kind<Token_Kind::basic_char_class>,{},cc_newline);}
\\p\{[^\}]\}    {
    fprintf(stderr,"Error: Unknown POSIX character category \"");
    for(const char c: matched.substr(2,matched.size()-3))
        fprintf(stderr,"%c",c);
    fprintf(stderr,"\"!\n");
    assert(errors);
    ++errors;
    return Token_t(yuki::pg::in_place_kind<Token_Kind::basic_char_class>,{},cc_ascii);
}

\.    {return Token_t(yuki::pg::in_place_kind<Token_Kind::basic_char_class>,{},cc_dot);}
\\u\{All\}    {return Token_t(yuki::pg::in_place_kind<Token_Kind::basic_char_class>,{},cc_all);}
\\u\{Space\}    {return Token_t(yuki::pg::in_place_kind<Token_Kind::basic_char_class>,{},cc_uspace);}
\\[uU]\{[^\}]*\}    {
    fprintf(stderr,"Error: Unknown unicode character category \"");
    for(const char c: matched.substr(2,matched.size()-3))
        fprintf(stderr,"%c",c);
    fprintf(stderr,"\"!\n");
    assert(errors);
    ++errors;
    return Token_t(yuki::pg::in_place_kind<Token_Kind::basic_char_class>,{},cc_all);
}

\\N    {return Token_t(yuki::pg::in_place_kind<Token_Kind::esc_N>,{});}

.    {return Token_t(yuki::pg::in_place_kind<Token_Kind::character>,{},static_cast<char32_t>(yuki::U8Char(matched.data())));}
\\.    {return Token_t(yuki::pg::in_place_kind<Token_Kind::character>,{},static_cast<char32_t>(yuki::U8Char(matched.data()+1)));}

<<EOF>>    {return Token_t(yuki::pg::in_place_kind<Token_Kind::EOF_>,{});}
}
%%
