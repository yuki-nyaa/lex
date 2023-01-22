%option fast unicode nodefault noline
%option outfile="Regex_Lexer.cpp" header-file="Regex_Lexer.h"
%option namespace="yuki::lex" prefix="yuki_lex_regex" lexer="Regex_Lexer" lex="lex" token-type="yuki::lex::Regex_Parser_TS::Token_t"

%code_cpptop{
#include"cconfig"
#include<cstdlib>
}

%code_htop{
#include"regex_parser.token.hpp"
}

%code_class{
  private:
    typedef Regex_Parser_TS::Token_Kind Token_Kind;
    typedef Regex_Parser_TS::Token_t Token_t;
}

%%
<INITIAL>{
\(    {return Token_t(yuki::pg::in_place_kind<Token_Kind::paren_l>,{});}
\)    {return Token_t(yuki::pg::in_place_kind<Token_Kind::paren_r>,{});}
\{    {return Token_t(yuki::pg::in_place_kind<Token_Kind::brace_l>,{});}
\}    {return Token_t(yuki::pg::in_place_kind<Token_Kind::brace_r>,{});}
\[    {return Token_t(yuki::pg::in_place_kind<Token_Kind::sqparen_l>,{});}
\]    {return Token_t(yuki::pg::in_place_kind<Token_Kind::sqparen_r>,{});}
\*    {return Token_t(yuki::pg::in_place_kind<Token_Kind::ast>,{});}
\+    {return Token_t(yuki::pg::in_place_kind<Token_Kind::plus>,{});}
\?    {return Token_t(yuki::pg::in_place_kind<Token_Kind::qmark>,{});}
=    {return Token_t(yuki::pg::in_place_kind<Token_Kind::eq>,{});}
\?=    {return Token_t(yuki::pg::in_place_kind<Token_Kind::qe>,{});}
\?l:    {return Token_t(yuki::pg::in_place_kind<Token_Kind::lazy>,{});}
\?d:    {return Token_t(yuki::pg::in_place_kind<Token_Kind::dlazy>,{});}
\|    {return Token_t(yuki::pg::in_place_kind<Token_Kind::vbar>,{});}
!    {return Token_t(yuki::pg::in_place_kind<Token_Kind::emark>,{});}
\^    {return Token_t(yuki::pg::in_place_kind<Token_Kind::hat>,{});}
\.    {return Token_t(yuki::pg::in_place_kind<Token_Kind::dot>,{});}
-    {return Token_t(yuki::pg::in_place_kind<Token_Kind::to>,{});}
,    {return Token_t(yuki::pg::in_place_kind<Token_Kind::comma>,{});}
\n    {return Token_t(yuki::pg::in_place_kind<Token_Kind::EOF_>,{});}
\$    {return Token_t(yuki::pg::in_place_kind<Token_Kind::meta_char>,{},MetaChar::EOL);}
\\A    {return Token_t(yuki::pg::in_place_kind<Token_Kind::meta_char>,{},MetaChar::BOI);}
\\Z    {return Token_t(yuki::pg::in_place_kind<Token_Kind::meta_char>,{},MetaChar::EOI);}
\\z    {return Token_t(yuki::pg::in_place_kind<Token_Kind::meta_char>,{},MetaChar::EoF);}
\\b    {return Token_t(yuki::pg::in_place_kind<Token_Kind::meta_char>,{},MetaChar::WB);}
\\B    {return Token_t(yuki::pg::in_place_kind<Token_Kind::meta_char>,{},-MetaChar::WB);}
.    {return Token_t(yuki::pg::in_place_kind<Token_Kind::character>,{},u32chr());}
\{[0-9]+,[0-9]+\}    {
    char* next = nullptr;
    const size_t lb = strtoull(text()+1,&next,10);
    return Token_t(yuki::pg::in_place_kind<Token_Kind::amount>,{},lb,strtoull(next+1,nullptr,10));
}
\{[0-9]+,\}    {return Token_t(yuki::pg::in_place_kind<Token_Kind::amount>,{},strtoull(text()+1,nullptr,10),(size_t)-1);}
\\[uUxX][0-9a-fA-F]+    {return Token_t(yuki::pg::in_place_kind<Token_Kind::character>,{},strtoul(text()+2,nullptr,16));}
<<EOF>>    {return Token_t(yuki::pg::in_place_kind<Token_Kind::EOF_>,{});}
}
%%
