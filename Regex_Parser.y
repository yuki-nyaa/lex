%nterm Regex {FSM:;};
%nterm Chars {Char_Class:;};
%nterm Char_Class {Char_Class:;};
%nterm Char_Interval {Char_Interval:;};
%nterm Char_Intervals {Char_Class:;};
%term amount {Amount:;};
%term character {char32_t:;};
%term meta_char {int:;};
%term paren_l "(" {};
%term paren_r ")" {};
%term brace_l "{" {};
%term brace_r "}" {};
%term sqparen_l "[" {};
%term sqparen_r "]" {};
%term ast "*" {};
%term plus "+" {};
%term qmark "?" {};
%term eq "=" {};
%term qe "?=" {};
%term lazy "?l:" {};
%term dlazy "?d:" {};
%term vbar "|" {};
%term emark "!" {};
%term hat "^" {};
%term dot "." {};
%term to "-" {};
%term comma "," {};

%default_left
%right amount "*" "+" "?"

%namespace yuki::lex
%parser Regex_Parser
%token_settings Regex_Parser_TS
%lexer Regex_Lexer

%no_default_ctor

%code cpp_top{
#include"cconfig"
}

%code h_top{
#include<yuki/Vector.hpp>
#include"regex_lexer.h"
#ifndef YUKI_LEX_FSM_FACTORY_POOL_BLOCK
#define YUKI_LEX_FSM_FACTORY_POOL_BLOCK 256
#endif
#ifndef YUKI_LEX_FSMS_RESERVE
#define YUKI_LEX_FSMS_RESERVE 64
#endif
}

%code token_top{
#include"FSM.hpp"
}

%code class{
  private:
    FSM_Factory<Node_Pool<FSM_Node,YUKI_LEX_FSM_FACTORY_POOL_BLOCK>> ff;
    size_t branch=0;
    static inline const Char_Class cc_dot{yuki::from_ordered_tag,{{0,static_cast<unsigned char>('\n')-1},{static_cast<unsigned char>('\n')+1,0x10FFFF}}};
  public:
    yuki::Vector<FSM> fsms{yuki::reserve_tag,YUKI_LEX_FSMS_RESERVE};
    size_t max_branch_size = 0;
    size_t max_branch_number = 0;

    void recycle(){
        ff.recycle();
        branch=0;
        fsms.clear();
        max_branch_size=0;
        max_branch_number=0;
    }

    Regex_Parser(Regex_Lexer* const l=nullptr) noexcept : lexer(l) {}
}

%%
Goal_:
    Regex
        {}
        {
            FSM fsm = $0;
            fsm.make_accept();
            if(fsm.size>max_branch_size)
                max_branch_size = fsm.size;
            if(fsm.accept->number > max_branch_number)
                max_branch_number = fsm.accept->number;
            fsms.emplace_back(fsm);
            ++branch;
            ff.reset_number();
        }
    ;

Regex:
    Regex Regex
        {ff.make_seq($0,$1)}
        {}
    |
    Regex "|" Regex
        {ff.make_alt(branch,$0,$2)}
        {}
    |
    "(" Regex ")"
        {$1}
        {}
    |
    Regex "*"
        {ff.make_ast(branch,$0)}
        {}
    |
    Regex "+"
        {ff.make_plus(branch,$0)}
        {}
    |
    Regex "?"
        {ff.make_qmark(branch,$0)}
        {}
    |
    Regex amount
        {ff.make_amount(branch,$0,$1)}
        {}
    |
    "(" "?=" Regex ")"
        {$2.make_head()}
        {}
    |
    "(" "?l:" Regex ")"
        {$2.make_lazy()}
        {}
    |
    "(" "?d:" Regex ")"
        {$2.make_dlazy()}
        {}
    |
    Char_Class
        {ff.make_fsm(branch,std::move($0))}
        {}
    |
    character
        {ff.make_fsm(branch,Char_Interval{$0,$0})}
        {}
    |
    meta_char
        {ff.make_fsm(branch,$0)}
        {}
    |
    "^"
        {ff.make_fsm(branch,MetaChar::BOL)}
        {}
    ;

Char_Class:
    "[" Char_Interval "]"
        {$1}
        {}
    |
    "[" Char_Intervals "]"
        {std::move($1)}
        {}
    |
    "[" Char_Class "+" Char_Class "]"
        {$1+$3}
        {}
    |
    "[" Char_Class "*" Char_Class "]"
        {$1*$3}
        {}
    |
    "[" "^" Char_Class "]"
        {!$2}
        {}
    |
    "[" "^" Char_Intervals "]"
        {!$2}
        {}
    |
    "[" Char_Class "-" Char_Class "]"
        {$1-$3}
        {}
    |
    "."
        {cc_dot}
        {}
    ;

Char_Intervals:
    Char_Intervals Char_Interval
    {std::move(($0.insert($1),$0))}
    {}
    |
    Char_Interval
    {$0}
    {}
    ;

Char_Interval:
    character "-" character
    {$0,$2}
    {}
    |
    character
    {$0,$0}
    {}
    ;
%%
