#include"cconfig"
#include<yuki/print.hpp>
#include<yuki/pg/lr1.hpp>
#include"gen/Regex_Parser.h"
namespace yuki::lex{
yuki::pg::lr1_action_return_type Regex_Parser_Tables::Action_Table::operator()(yuki::pg::AbsLR1Parser<Regex_Parser_TS>& p_,Regex_Lexer& l_){
    using enum Regex_Parser_TS::Token_Kind::enum_t;
    switch(p_.state()){
    case 0: CC0: switch(t_.kind()){
        case character: p_.SHIFT_(std::move(t_),3); t_=l_.lex(); goto CC3;
        case meta_char: p_.SHIFT_(std::move(t_),4); t_=l_.lex(); goto CC4;
        case basic_char_class: p_.SHIFT_(std::move(t_),5); t_=l_.lex(); goto CC5;
        case paren_l: p_.SHIFT_(std::move(t_),6); t_=l_.lex(); goto CC6;
        case sqparen_l: p_.SHIFT_(std::move(t_),7); t_=l_.lex(); goto CC7;
        case hat: p_.SHIFT_(std::move(t_),8); t_=l_.lex(); goto CC8;
        case esc_N: p_.SHIFT_(std::move(t_),9); t_=l_.lex(); goto CC9;
        default : return {(size_t)-1,(size_t)-1};
    }
    case 1: CC1: switch(t_.kind()){
        case amount: p_.SHIFT_(std::move(t_),11); t_=l_.lex(); goto CC11;
        case character: p_.SHIFT_(std::move(t_),3); t_=l_.lex(); goto CC3;
        case meta_char: p_.SHIFT_(std::move(t_),4); t_=l_.lex(); goto CC4;
        case basic_char_class: p_.SHIFT_(std::move(t_),5); t_=l_.lex(); goto CC5;
        case paren_l: p_.SHIFT_(std::move(t_),6); t_=l_.lex(); goto CC6;
        case sqparen_l: p_.SHIFT_(std::move(t_),7); t_=l_.lex(); goto CC7;
        case ast: p_.SHIFT_(std::move(t_),12); t_=l_.lex(); goto CC12;
        case plus: p_.SHIFT_(std::move(t_),13); t_=l_.lex(); goto CC13;
        case qmark: p_.SHIFT_(std::move(t_),14); t_=l_.lex(); goto CC14;
        case vbar: p_.SHIFT_(std::move(t_),15); t_=l_.lex(); goto CC15;
        case hat: p_.SHIFT_(std::move(t_),8); t_=l_.lex(); goto CC8;
        case esc_N: p_.SHIFT_(std::move(t_),9); t_=l_.lex(); goto CC9;
        case EOF_: p_.SET_STATE(1); return {EOF_,0};
        default : return {(size_t)-1,(size_t)-1};
    }
    case 2: CC2: switch(t_.kind()){
        case amount: p_.SET_STATE(2); return {amount,11};
        case character: p_.SET_STATE(2); return {character,11};
        case meta_char: p_.SET_STATE(2); return {meta_char,11};
        case basic_char_class: p_.SET_STATE(2); return {basic_char_class,11};
        case paren_l: p_.SET_STATE(2); return {paren_l,11};
        case sqparen_l: p_.SET_STATE(2); return {sqparen_l,11};
        case ast: p_.SET_STATE(2); return {ast,11};
        case plus: p_.SET_STATE(2); return {plus,11};
        case qmark: p_.SET_STATE(2); return {qmark,11};
        case vbar: p_.SET_STATE(2); return {vbar,11};
        case hat: p_.SET_STATE(2); return {hat,11};
        case esc_N: p_.SET_STATE(2); return {esc_N,11};
        case EOF_: p_.SET_STATE(2); return {EOF_,11};
        default : return {(size_t)-1,(size_t)-1};
    }
    case 3: CC3: switch(t_.kind()){
        case amount: p_.SET_STATE(3); return {amount,12};
        case character: p_.SET_STATE(3); return {character,12};
        case meta_char: p_.SET_STATE(3); return {meta_char,12};
        case basic_char_class: p_.SET_STATE(3); return {basic_char_class,12};
        case paren_l: p_.SET_STATE(3); return {paren_l,12};
        case sqparen_l: p_.SET_STATE(3); return {sqparen_l,12};
        case ast: p_.SET_STATE(3); return {ast,12};
        case plus: p_.SET_STATE(3); return {plus,12};
        case qmark: p_.SET_STATE(3); return {qmark,12};
        case vbar: p_.SET_STATE(3); return {vbar,12};
        case hat: p_.SET_STATE(3); return {hat,12};
        case esc_N: p_.SET_STATE(3); return {esc_N,12};
        case EOF_: p_.SET_STATE(3); return {EOF_,12};
        default : return {(size_t)-1,(size_t)-1};
    }
    case 4: CC4: switch(t_.kind()){
        case amount: p_.SET_STATE(4); return {amount,13};
        case character: p_.SET_STATE(4); return {character,13};
        case meta_char: p_.SET_STATE(4); return {meta_char,13};
        case basic_char_class: p_.SET_STATE(4); return {basic_char_class,13};
        case paren_l: p_.SET_STATE(4); return {paren_l,13};
        case sqparen_l: p_.SET_STATE(4); return {sqparen_l,13};
        case ast: p_.SET_STATE(4); return {ast,13};
        case plus: p_.SET_STATE(4); return {plus,13};
        case qmark: p_.SET_STATE(4); return {qmark,13};
        case vbar: p_.SET_STATE(4); return {vbar,13};
        case hat: p_.SET_STATE(4); return {hat,13};
        case esc_N: p_.SET_STATE(4); return {esc_N,13};
        case EOF_: p_.SET_STATE(4); return {EOF_,13};
        default : return {(size_t)-1,(size_t)-1};
    }
    case 5: CC5: switch(t_.kind()){
        case amount: p_.SET_STATE(5); return {amount,23};
        case character: p_.SET_STATE(5); return {character,23};
        case meta_char: p_.SET_STATE(5); return {meta_char,23};
        case basic_char_class: p_.SET_STATE(5); return {basic_char_class,23};
        case paren_l: p_.SET_STATE(5); return {paren_l,23};
        case sqparen_l: p_.SET_STATE(5); return {sqparen_l,23};
        case ast: p_.SET_STATE(5); return {ast,23};
        case plus: p_.SET_STATE(5); return {plus,23};
        case qmark: p_.SET_STATE(5); return {qmark,23};
        case vbar: p_.SET_STATE(5); return {vbar,23};
        case hat: p_.SET_STATE(5); return {hat,23};
        case esc_N: p_.SET_STATE(5); return {esc_N,23};
        case EOF_: p_.SET_STATE(5); return {EOF_,23};
        default : return {(size_t)-1,(size_t)-1};
    }
    case 6: CC6: switch(t_.kind()){
        case character: p_.SHIFT_(std::move(t_),18); t_=l_.lex(); goto CC18;
        case meta_char: p_.SHIFT_(std::move(t_),19); t_=l_.lex(); goto CC19;
        case basic_char_class: p_.SHIFT_(std::move(t_),20); t_=l_.lex(); goto CC20;
        case paren_l: p_.SHIFT_(std::move(t_),21); t_=l_.lex(); goto CC21;
        case sqparen_l: p_.SHIFT_(std::move(t_),22); t_=l_.lex(); goto CC22;
        case qe: p_.SHIFT_(std::move(t_),23); t_=l_.lex(); goto CC23;
        case lazy: p_.SHIFT_(std::move(t_),24); t_=l_.lex(); goto CC24;
        case dlazy: p_.SHIFT_(std::move(t_),25); t_=l_.lex(); goto CC25;
        case hat: p_.SHIFT_(std::move(t_),26); t_=l_.lex(); goto CC26;
        case esc_N: p_.SHIFT_(std::move(t_),27); t_=l_.lex(); goto CC27;
        default : return {(size_t)-1,(size_t)-1};
    }
    case 7: CC7: switch(t_.kind()){
        case character: p_.SHIFT_(std::move(t_),31); t_=l_.lex(); goto CC31;
        case basic_char_class: p_.SHIFT_(std::move(t_),32); t_=l_.lex(); goto CC32;
        case sqparen_l: p_.SHIFT_(std::move(t_),33); t_=l_.lex(); goto CC33;
        case hat: p_.SHIFT_(std::move(t_),34); t_=l_.lex(); goto CC34;
        default : return {(size_t)-1,(size_t)-1};
    }
    case 8: CC8: switch(t_.kind()){
        case amount: p_.SET_STATE(8); return {amount,14};
        case character: p_.SET_STATE(8); return {character,14};
        case meta_char: p_.SET_STATE(8); return {meta_char,14};
        case basic_char_class: p_.SET_STATE(8); return {basic_char_class,14};
        case paren_l: p_.SET_STATE(8); return {paren_l,14};
        case sqparen_l: p_.SET_STATE(8); return {sqparen_l,14};
        case ast: p_.SET_STATE(8); return {ast,14};
        case plus: p_.SET_STATE(8); return {plus,14};
        case qmark: p_.SET_STATE(8); return {qmark,14};
        case vbar: p_.SET_STATE(8); return {vbar,14};
        case hat: p_.SET_STATE(8); return {hat,14};
        case esc_N: p_.SET_STATE(8); return {esc_N,14};
        case EOF_: p_.SET_STATE(8); return {EOF_,14};
        default : return {(size_t)-1,(size_t)-1};
    }
    case 9: CC9: switch(t_.kind()){
        case amount: p_.SET_STATE(9); return {amount,15};
        case character: p_.SET_STATE(9); return {character,15};
        case meta_char: p_.SET_STATE(9); return {meta_char,15};
        case basic_char_class: p_.SET_STATE(9); return {basic_char_class,15};
        case paren_l: p_.SET_STATE(9); return {paren_l,15};
        case sqparen_l: p_.SET_STATE(9); return {sqparen_l,15};
        case ast: p_.SET_STATE(9); return {ast,15};
        case plus: p_.SET_STATE(9); return {plus,15};
        case qmark: p_.SET_STATE(9); return {qmark,15};
        case vbar: p_.SET_STATE(9); return {vbar,15};
        case hat: p_.SET_STATE(9); return {hat,15};
        case esc_N: p_.SET_STATE(9); return {esc_N,15};
        case EOF_: p_.SET_STATE(9); return {EOF_,15};
        default : return {(size_t)-1,(size_t)-1};
    }
    case 10: CC10: switch(t_.kind()){
        case amount: p_.SHIFT_(std::move(t_),11); t_=l_.lex(); goto CC11;
        case character: p_.SET_STATE(10); return {character,1};
        case meta_char: p_.SET_STATE(10); return {meta_char,1};
        case basic_char_class: p_.SET_STATE(10); return {basic_char_class,1};
        case paren_l: p_.SET_STATE(10); return {paren_l,1};
        case sqparen_l: p_.SET_STATE(10); return {sqparen_l,1};
        case ast: p_.SHIFT_(std::move(t_),12); t_=l_.lex(); goto CC12;
        case plus: p_.SHIFT_(std::move(t_),13); t_=l_.lex(); goto CC13;
        case qmark: p_.SHIFT_(std::move(t_),14); t_=l_.lex(); goto CC14;
        case vbar: p_.SET_STATE(10); return {vbar,1};
        case hat: p_.SET_STATE(10); return {hat,1};
        case esc_N: p_.SET_STATE(10); return {esc_N,1};
        case EOF_: p_.SET_STATE(10); return {EOF_,1};
        default : return {(size_t)-1,(size_t)-1};
    }
    case 11: CC11: switch(t_.kind()){
        case amount: p_.SET_STATE(11); return {amount,7};
        case character: p_.SET_STATE(11); return {character,7};
        case meta_char: p_.SET_STATE(11); return {meta_char,7};
        case basic_char_class: p_.SET_STATE(11); return {basic_char_class,7};
        case paren_l: p_.SET_STATE(11); return {paren_l,7};
        case sqparen_l: p_.SET_STATE(11); return {sqparen_l,7};
        case ast: p_.SET_STATE(11); return {ast,7};
        case plus: p_.SET_STATE(11); return {plus,7};
        case qmark: p_.SET_STATE(11); return {qmark,7};
        case vbar: p_.SET_STATE(11); return {vbar,7};
        case hat: p_.SET_STATE(11); return {hat,7};
        case esc_N: p_.SET_STATE(11); return {esc_N,7};
        case EOF_: p_.SET_STATE(11); return {EOF_,7};
        default : return {(size_t)-1,(size_t)-1};
    }
    case 12: CC12: switch(t_.kind()){
        case amount: p_.SET_STATE(12); return {amount,4};
        case character: p_.SET_STATE(12); return {character,4};
        case meta_char: p_.SET_STATE(12); return {meta_char,4};
        case basic_char_class: p_.SET_STATE(12); return {basic_char_class,4};
        case paren_l: p_.SET_STATE(12); return {paren_l,4};
        case sqparen_l: p_.SET_STATE(12); return {sqparen_l,4};
        case ast: p_.SET_STATE(12); return {ast,4};
        case plus: p_.SET_STATE(12); return {plus,4};
        case qmark: p_.SET_STATE(12); return {qmark,4};
        case vbar: p_.SET_STATE(12); return {vbar,4};
        case hat: p_.SET_STATE(12); return {hat,4};
        case esc_N: p_.SET_STATE(12); return {esc_N,4};
        case EOF_: p_.SET_STATE(12); return {EOF_,4};
        default : return {(size_t)-1,(size_t)-1};
    }
    case 13: CC13: switch(t_.kind()){
        case amount: p_.SET_STATE(13); return {amount,5};
        case character: p_.SET_STATE(13); return {character,5};
        case meta_char: p_.SET_STATE(13); return {meta_char,5};
        case basic_char_class: p_.SET_STATE(13); return {basic_char_class,5};
        case paren_l: p_.SET_STATE(13); return {paren_l,5};
        case sqparen_l: p_.SET_STATE(13); return {sqparen_l,5};
        case ast: p_.SET_STATE(13); return {ast,5};
        case plus: p_.SET_STATE(13); return {plus,5};
        case qmark: p_.SET_STATE(13); return {qmark,5};
        case vbar: p_.SET_STATE(13); return {vbar,5};
        case hat: p_.SET_STATE(13); return {hat,5};
        case esc_N: p_.SET_STATE(13); return {esc_N,5};
        case EOF_: p_.SET_STATE(13); return {EOF_,5};
        default : return {(size_t)-1,(size_t)-1};
    }
    case 14: CC14: switch(t_.kind()){
        case amount: p_.SET_STATE(14); return {amount,6};
        case character: p_.SET_STATE(14); return {character,6};
        case meta_char: p_.SET_STATE(14); return {meta_char,6};
        case basic_char_class: p_.SET_STATE(14); return {basic_char_class,6};
        case paren_l: p_.SET_STATE(14); return {paren_l,6};
        case sqparen_l: p_.SET_STATE(14); return {sqparen_l,6};
        case ast: p_.SET_STATE(14); return {ast,6};
        case plus: p_.SET_STATE(14); return {plus,6};
        case qmark: p_.SET_STATE(14); return {qmark,6};
        case vbar: p_.SET_STATE(14); return {vbar,6};
        case hat: p_.SET_STATE(14); return {hat,6};
        case esc_N: p_.SET_STATE(14); return {esc_N,6};
        case EOF_: p_.SET_STATE(14); return {EOF_,6};
        default : return {(size_t)-1,(size_t)-1};
    }
    case 15: CC15: switch(t_.kind()){
        case character: p_.SHIFT_(std::move(t_),3); t_=l_.lex(); goto CC3;
        case meta_char: p_.SHIFT_(std::move(t_),4); t_=l_.lex(); goto CC4;
        case basic_char_class: p_.SHIFT_(std::move(t_),5); t_=l_.lex(); goto CC5;
        case paren_l: p_.SHIFT_(std::move(t_),6); t_=l_.lex(); goto CC6;
        case sqparen_l: p_.SHIFT_(std::move(t_),7); t_=l_.lex(); goto CC7;
        case hat: p_.SHIFT_(std::move(t_),8); t_=l_.lex(); goto CC8;
        case esc_N: p_.SHIFT_(std::move(t_),9); t_=l_.lex(); goto CC9;
        default : return {(size_t)-1,(size_t)-1};
    }
    case 16: CC16: switch(t_.kind()){
        case amount: p_.SHIFT_(std::move(t_),37); t_=l_.lex(); goto CC37;
        case character: p_.SHIFT_(std::move(t_),18); t_=l_.lex(); goto CC18;
        case meta_char: p_.SHIFT_(std::move(t_),19); t_=l_.lex(); goto CC19;
        case basic_char_class: p_.SHIFT_(std::move(t_),20); t_=l_.lex(); goto CC20;
        case paren_l: p_.SHIFT_(std::move(t_),21); t_=l_.lex(); goto CC21;
        case paren_r: p_.SHIFT_(std::move(t_),38); t_=l_.lex(); goto CC38;
        case sqparen_l: p_.SHIFT_(std::move(t_),22); t_=l_.lex(); goto CC22;
        case ast: p_.SHIFT_(std::move(t_),39); t_=l_.lex(); goto CC39;
        case plus: p_.SHIFT_(std::move(t_),40); t_=l_.lex(); goto CC40;
        case qmark: p_.SHIFT_(std::move(t_),41); t_=l_.lex(); goto CC41;
        case vbar: p_.SHIFT_(std::move(t_),42); t_=l_.lex(); goto CC42;
        case hat: p_.SHIFT_(std::move(t_),26); t_=l_.lex(); goto CC26;
        case esc_N: p_.SHIFT_(std::move(t_),27); t_=l_.lex(); goto CC27;
        default : return {(size_t)-1,(size_t)-1};
    }
    case 17: CC17: switch(t_.kind()){
        case amount: p_.SET_STATE(17); return {amount,11};
        case character: p_.SET_STATE(17); return {character,11};
        case meta_char: p_.SET_STATE(17); return {meta_char,11};
        case basic_char_class: p_.SET_STATE(17); return {basic_char_class,11};
        case paren_l: p_.SET_STATE(17); return {paren_l,11};
        case paren_r: p_.SET_STATE(17); return {paren_r,11};
        case sqparen_l: p_.SET_STATE(17); return {sqparen_l,11};
        case ast: p_.SET_STATE(17); return {ast,11};
        case plus: p_.SET_STATE(17); return {plus,11};
        case qmark: p_.SET_STATE(17); return {qmark,11};
        case vbar: p_.SET_STATE(17); return {vbar,11};
        case hat: p_.SET_STATE(17); return {hat,11};
        case esc_N: p_.SET_STATE(17); return {esc_N,11};
        default : return {(size_t)-1,(size_t)-1};
    }
    case 18: CC18: switch(t_.kind()){
        case amount: p_.SET_STATE(18); return {amount,12};
        case character: p_.SET_STATE(18); return {character,12};
        case meta_char: p_.SET_STATE(18); return {meta_char,12};
        case basic_char_class: p_.SET_STATE(18); return {basic_char_class,12};
        case paren_l: p_.SET_STATE(18); return {paren_l,12};
        case paren_r: p_.SET_STATE(18); return {paren_r,12};
        case sqparen_l: p_.SET_STATE(18); return {sqparen_l,12};
        case ast: p_.SET_STATE(18); return {ast,12};
        case plus: p_.SET_STATE(18); return {plus,12};
        case qmark: p_.SET_STATE(18); return {qmark,12};
        case vbar: p_.SET_STATE(18); return {vbar,12};
        case hat: p_.SET_STATE(18); return {hat,12};
        case esc_N: p_.SET_STATE(18); return {esc_N,12};
        default : return {(size_t)-1,(size_t)-1};
    }
    case 19: CC19: switch(t_.kind()){
        case amount: p_.SET_STATE(19); return {amount,13};
        case character: p_.SET_STATE(19); return {character,13};
        case meta_char: p_.SET_STATE(19); return {meta_char,13};
        case basic_char_class: p_.SET_STATE(19); return {basic_char_class,13};
        case paren_l: p_.SET_STATE(19); return {paren_l,13};
        case paren_r: p_.SET_STATE(19); return {paren_r,13};
        case sqparen_l: p_.SET_STATE(19); return {sqparen_l,13};
        case ast: p_.SET_STATE(19); return {ast,13};
        case plus: p_.SET_STATE(19); return {plus,13};
        case qmark: p_.SET_STATE(19); return {qmark,13};
        case vbar: p_.SET_STATE(19); return {vbar,13};
        case hat: p_.SET_STATE(19); return {hat,13};
        case esc_N: p_.SET_STATE(19); return {esc_N,13};
        default : return {(size_t)-1,(size_t)-1};
    }
    case 20: CC20: switch(t_.kind()){
        case amount: p_.SET_STATE(20); return {amount,23};
        case character: p_.SET_STATE(20); return {character,23};
        case meta_char: p_.SET_STATE(20); return {meta_char,23};
        case basic_char_class: p_.SET_STATE(20); return {basic_char_class,23};
        case paren_l: p_.SET_STATE(20); return {paren_l,23};
        case paren_r: p_.SET_STATE(20); return {paren_r,23};
        case sqparen_l: p_.SET_STATE(20); return {sqparen_l,23};
        case ast: p_.SET_STATE(20); return {ast,23};
        case plus: p_.SET_STATE(20); return {plus,23};
        case qmark: p_.SET_STATE(20); return {qmark,23};
        case vbar: p_.SET_STATE(20); return {vbar,23};
        case hat: p_.SET_STATE(20); return {hat,23};
        case esc_N: p_.SET_STATE(20); return {esc_N,23};
        default : return {(size_t)-1,(size_t)-1};
    }
    case 21: CC21: switch(t_.kind()){
        case character: p_.SHIFT_(std::move(t_),18); t_=l_.lex(); goto CC18;
        case meta_char: p_.SHIFT_(std::move(t_),19); t_=l_.lex(); goto CC19;
        case basic_char_class: p_.SHIFT_(std::move(t_),20); t_=l_.lex(); goto CC20;
        case paren_l: p_.SHIFT_(std::move(t_),21); t_=l_.lex(); goto CC21;
        case sqparen_l: p_.SHIFT_(std::move(t_),22); t_=l_.lex(); goto CC22;
        case qe: p_.SHIFT_(std::move(t_),44); t_=l_.lex(); goto CC44;
        case lazy: p_.SHIFT_(std::move(t_),45); t_=l_.lex(); goto CC45;
        case dlazy: p_.SHIFT_(std::move(t_),46); t_=l_.lex(); goto CC46;
        case hat: p_.SHIFT_(std::move(t_),26); t_=l_.lex(); goto CC26;
        case esc_N: p_.SHIFT_(std::move(t_),27); t_=l_.lex(); goto CC27;
        default : return {(size_t)-1,(size_t)-1};
    }
    case 22: CC22: switch(t_.kind()){
        case character: p_.SHIFT_(std::move(t_),31); t_=l_.lex(); goto CC31;
        case basic_char_class: p_.SHIFT_(std::move(t_),32); t_=l_.lex(); goto CC32;
        case sqparen_l: p_.SHIFT_(std::move(t_),33); t_=l_.lex(); goto CC33;
        case hat: p_.SHIFT_(std::move(t_),50); t_=l_.lex(); goto CC50;
        default : return {(size_t)-1,(size_t)-1};
    }
    case 23: CC23: switch(t_.kind()){
        case character: p_.SHIFT_(std::move(t_),18); t_=l_.lex(); goto CC18;
        case meta_char: p_.SHIFT_(std::move(t_),19); t_=l_.lex(); goto CC19;
        case basic_char_class: p_.SHIFT_(std::move(t_),20); t_=l_.lex(); goto CC20;
        case paren_l: p_.SHIFT_(std::move(t_),21); t_=l_.lex(); goto CC21;
        case sqparen_l: p_.SHIFT_(std::move(t_),22); t_=l_.lex(); goto CC22;
        case hat: p_.SHIFT_(std::move(t_),26); t_=l_.lex(); goto CC26;
        case esc_N: p_.SHIFT_(std::move(t_),27); t_=l_.lex(); goto CC27;
        default : return {(size_t)-1,(size_t)-1};
    }
    case 24: CC24: switch(t_.kind()){
        case character: p_.SHIFT_(std::move(t_),18); t_=l_.lex(); goto CC18;
        case meta_char: p_.SHIFT_(std::move(t_),19); t_=l_.lex(); goto CC19;
        case basic_char_class: p_.SHIFT_(std::move(t_),20); t_=l_.lex(); goto CC20;
        case paren_l: p_.SHIFT_(std::move(t_),21); t_=l_.lex(); goto CC21;
        case sqparen_l: p_.SHIFT_(std::move(t_),22); t_=l_.lex(); goto CC22;
        case hat: p_.SHIFT_(std::move(t_),26); t_=l_.lex(); goto CC26;
        case esc_N: p_.SHIFT_(std::move(t_),27); t_=l_.lex(); goto CC27;
        default : return {(size_t)-1,(size_t)-1};
    }
    case 25: CC25: switch(t_.kind()){
        case character: p_.SHIFT_(std::move(t_),18); t_=l_.lex(); goto CC18;
        case meta_char: p_.SHIFT_(std::move(t_),19); t_=l_.lex(); goto CC19;
        case basic_char_class: p_.SHIFT_(std::move(t_),20); t_=l_.lex(); goto CC20;
        case paren_l: p_.SHIFT_(std::move(t_),21); t_=l_.lex(); goto CC21;
        case sqparen_l: p_.SHIFT_(std::move(t_),22); t_=l_.lex(); goto CC22;
        case hat: p_.SHIFT_(std::move(t_),26); t_=l_.lex(); goto CC26;
        case esc_N: p_.SHIFT_(std::move(t_),27); t_=l_.lex(); goto CC27;
        default : return {(size_t)-1,(size_t)-1};
    }
    case 26: CC26: switch(t_.kind()){
        case amount: p_.SET_STATE(26); return {amount,14};
        case character: p_.SET_STATE(26); return {character,14};
        case meta_char: p_.SET_STATE(26); return {meta_char,14};
        case basic_char_class: p_.SET_STATE(26); return {basic_char_class,14};
        case paren_l: p_.SET_STATE(26); return {paren_l,14};
        case paren_r: p_.SET_STATE(26); return {paren_r,14};
        case sqparen_l: p_.SET_STATE(26); return {sqparen_l,14};
        case ast: p_.SET_STATE(26); return {ast,14};
        case plus: p_.SET_STATE(26); return {plus,14};
        case qmark: p_.SET_STATE(26); return {qmark,14};
        case vbar: p_.SET_STATE(26); return {vbar,14};
        case hat: p_.SET_STATE(26); return {hat,14};
        case esc_N: p_.SET_STATE(26); return {esc_N,14};
        default : return {(size_t)-1,(size_t)-1};
    }
    case 27: CC27: switch(t_.kind()){
        case amount: p_.SET_STATE(27); return {amount,15};
        case character: p_.SET_STATE(27); return {character,15};
        case meta_char: p_.SET_STATE(27); return {meta_char,15};
        case basic_char_class: p_.SET_STATE(27); return {basic_char_class,15};
        case paren_l: p_.SET_STATE(27); return {paren_l,15};
        case paren_r: p_.SET_STATE(27); return {paren_r,15};
        case sqparen_l: p_.SET_STATE(27); return {sqparen_l,15};
        case ast: p_.SET_STATE(27); return {ast,15};
        case plus: p_.SET_STATE(27); return {plus,15};
        case qmark: p_.SET_STATE(27); return {qmark,15};
        case vbar: p_.SET_STATE(27); return {vbar,15};
        case hat: p_.SET_STATE(27); return {hat,15};
        case esc_N: p_.SET_STATE(27); return {esc_N,15};
        default : return {(size_t)-1,(size_t)-1};
    }
    case 28: CC28: switch(t_.kind()){
        case ast: p_.SHIFT_(std::move(t_),54); t_=l_.lex(); goto CC54;
        case plus: p_.SHIFT_(std::move(t_),55); t_=l_.lex(); goto CC55;
        case to: p_.SHIFT_(std::move(t_),56); t_=l_.lex(); goto CC56;
        default : return {(size_t)-1,(size_t)-1};
    }
    case 29: CC29: switch(t_.kind()){
        case character: p_.SET_STATE(29); return {character,25};
        case sqparen_r: p_.SET_STATE(29); return {sqparen_r,25};
        default : return {(size_t)-1,(size_t)-1};
    }
    case 30: CC30: switch(t_.kind()){
        case character: p_.SHIFT_(std::move(t_),31); t_=l_.lex(); goto CC31;
        case sqparen_r: p_.SHIFT_(std::move(t_),59); t_=l_.lex(); goto CC59;
        default : return {(size_t)-1,(size_t)-1};
    }
    case 31: CC31: switch(t_.kind()){
        case character: p_.SET_STATE(31); return {character,27};
        case sqparen_r: p_.SET_STATE(31); return {sqparen_r,27};
        case to: p_.SHIFT_(std::move(t_),60); t_=l_.lex(); goto CC60;
        default : return {(size_t)-1,(size_t)-1};
    }
    case 32: CC32: switch(t_.kind()){
        case ast: p_.SET_STATE(32); return {ast,23};
        case plus: p_.SET_STATE(32); return {plus,23};
        case to: p_.SET_STATE(32); return {to,23};
        default : return {(size_t)-1,(size_t)-1};
    }
    case 33: CC33: switch(t_.kind()){
        case character: p_.SHIFT_(std::move(t_),31); t_=l_.lex(); goto CC31;
        case basic_char_class: p_.SHIFT_(std::move(t_),32); t_=l_.lex(); goto CC32;
        case sqparen_l: p_.SHIFT_(std::move(t_),33); t_=l_.lex(); goto CC33;
        case hat: p_.SHIFT_(std::move(t_),64); t_=l_.lex(); goto CC64;
        default : return {(size_t)-1,(size_t)-1};
    }
    case 34: CC34: switch(t_.kind()){
        case character: p_.SHIFT_(std::move(t_),31); t_=l_.lex(); goto CC31;
        case basic_char_class: p_.SHIFT_(std::move(t_),68); t_=l_.lex(); goto CC68;
        case sqparen_l: p_.SHIFT_(std::move(t_),69); t_=l_.lex(); goto CC69;
        default : return {(size_t)-1,(size_t)-1};
    }
    case 35: CC35: switch(t_.kind()){
        case amount: p_.SHIFT_(std::move(t_),11); t_=l_.lex(); goto CC11;
        case character: p_.SET_STATE(35); return {character,2};
        case meta_char: p_.SET_STATE(35); return {meta_char,2};
        case basic_char_class: p_.SET_STATE(35); return {basic_char_class,2};
        case paren_l: p_.SET_STATE(35); return {paren_l,2};
        case sqparen_l: p_.SET_STATE(35); return {sqparen_l,2};
        case ast: p_.SHIFT_(std::move(t_),12); t_=l_.lex(); goto CC12;
        case plus: p_.SHIFT_(std::move(t_),13); t_=l_.lex(); goto CC13;
        case qmark: p_.SHIFT_(std::move(t_),14); t_=l_.lex(); goto CC14;
        case vbar: p_.SET_STATE(35); return {vbar,2};
        case hat: p_.SET_STATE(35); return {hat,2};
        case esc_N: p_.SET_STATE(35); return {esc_N,2};
        case EOF_: p_.SET_STATE(35); return {EOF_,2};
        default : return {(size_t)-1,(size_t)-1};
    }
    case 36: CC36: switch(t_.kind()){
        case amount: p_.SHIFT_(std::move(t_),37); t_=l_.lex(); goto CC37;
        case character: p_.SET_STATE(36); return {character,1};
        case meta_char: p_.SET_STATE(36); return {meta_char,1};
        case basic_char_class: p_.SET_STATE(36); return {basic_char_class,1};
        case paren_l: p_.SET_STATE(36); return {paren_l,1};
        case paren_r: p_.SET_STATE(36); return {paren_r,1};
        case sqparen_l: p_.SET_STATE(36); return {sqparen_l,1};
        case ast: p_.SHIFT_(std::move(t_),39); t_=l_.lex(); goto CC39;
        case plus: p_.SHIFT_(std::move(t_),40); t_=l_.lex(); goto CC40;
        case qmark: p_.SHIFT_(std::move(t_),41); t_=l_.lex(); goto CC41;
        case vbar: p_.SET_STATE(36); return {vbar,1};
        case hat: p_.SET_STATE(36); return {hat,1};
        case esc_N: p_.SET_STATE(36); return {esc_N,1};
        default : return {(size_t)-1,(size_t)-1};
    }
    case 37: CC37: switch(t_.kind()){
        case amount: p_.SET_STATE(37); return {amount,7};
        case character: p_.SET_STATE(37); return {character,7};
        case meta_char: p_.SET_STATE(37); return {meta_char,7};
        case basic_char_class: p_.SET_STATE(37); return {basic_char_class,7};
        case paren_l: p_.SET_STATE(37); return {paren_l,7};
        case paren_r: p_.SET_STATE(37); return {paren_r,7};
        case sqparen_l: p_.SET_STATE(37); return {sqparen_l,7};
        case ast: p_.SET_STATE(37); return {ast,7};
        case plus: p_.SET_STATE(37); return {plus,7};
        case qmark: p_.SET_STATE(37); return {qmark,7};
        case vbar: p_.SET_STATE(37); return {vbar,7};
        case hat: p_.SET_STATE(37); return {hat,7};
        case esc_N: p_.SET_STATE(37); return {esc_N,7};
        default : return {(size_t)-1,(size_t)-1};
    }
    case 38: CC38: switch(t_.kind()){
        case amount: p_.SET_STATE(38); return {amount,3};
        case character: p_.SET_STATE(38); return {character,3};
        case meta_char: p_.SET_STATE(38); return {meta_char,3};
        case basic_char_class: p_.SET_STATE(38); return {basic_char_class,3};
        case paren_l: p_.SET_STATE(38); return {paren_l,3};
        case sqparen_l: p_.SET_STATE(38); return {sqparen_l,3};
        case ast: p_.SET_STATE(38); return {ast,3};
        case plus: p_.SET_STATE(38); return {plus,3};
        case qmark: p_.SET_STATE(38); return {qmark,3};
        case vbar: p_.SET_STATE(38); return {vbar,3};
        case hat: p_.SET_STATE(38); return {hat,3};
        case esc_N: p_.SET_STATE(38); return {esc_N,3};
        case EOF_: p_.SET_STATE(38); return {EOF_,3};
        default : return {(size_t)-1,(size_t)-1};
    }
    case 39: CC39: switch(t_.kind()){
        case amount: p_.SET_STATE(39); return {amount,4};
        case character: p_.SET_STATE(39); return {character,4};
        case meta_char: p_.SET_STATE(39); return {meta_char,4};
        case basic_char_class: p_.SET_STATE(39); return {basic_char_class,4};
        case paren_l: p_.SET_STATE(39); return {paren_l,4};
        case paren_r: p_.SET_STATE(39); return {paren_r,4};
        case sqparen_l: p_.SET_STATE(39); return {sqparen_l,4};
        case ast: p_.SET_STATE(39); return {ast,4};
        case plus: p_.SET_STATE(39); return {plus,4};
        case qmark: p_.SET_STATE(39); return {qmark,4};
        case vbar: p_.SET_STATE(39); return {vbar,4};
        case hat: p_.SET_STATE(39); return {hat,4};
        case esc_N: p_.SET_STATE(39); return {esc_N,4};
        default : return {(size_t)-1,(size_t)-1};
    }
    case 40: CC40: switch(t_.kind()){
        case amount: p_.SET_STATE(40); return {amount,5};
        case character: p_.SET_STATE(40); return {character,5};
        case meta_char: p_.SET_STATE(40); return {meta_char,5};
        case basic_char_class: p_.SET_STATE(40); return {basic_char_class,5};
        case paren_l: p_.SET_STATE(40); return {paren_l,5};
        case paren_r: p_.SET_STATE(40); return {paren_r,5};
        case sqparen_l: p_.SET_STATE(40); return {sqparen_l,5};
        case ast: p_.SET_STATE(40); return {ast,5};
        case plus: p_.SET_STATE(40); return {plus,5};
        case qmark: p_.SET_STATE(40); return {qmark,5};
        case vbar: p_.SET_STATE(40); return {vbar,5};
        case hat: p_.SET_STATE(40); return {hat,5};
        case esc_N: p_.SET_STATE(40); return {esc_N,5};
        default : return {(size_t)-1,(size_t)-1};
    }
    case 41: CC41: switch(t_.kind()){
        case amount: p_.SET_STATE(41); return {amount,6};
        case character: p_.SET_STATE(41); return {character,6};
        case meta_char: p_.SET_STATE(41); return {meta_char,6};
        case basic_char_class: p_.SET_STATE(41); return {basic_char_class,6};
        case paren_l: p_.SET_STATE(41); return {paren_l,6};
        case paren_r: p_.SET_STATE(41); return {paren_r,6};
        case sqparen_l: p_.SET_STATE(41); return {sqparen_l,6};
        case ast: p_.SET_STATE(41); return {ast,6};
        case plus: p_.SET_STATE(41); return {plus,6};
        case qmark: p_.SET_STATE(41); return {qmark,6};
        case vbar: p_.SET_STATE(41); return {vbar,6};
        case hat: p_.SET_STATE(41); return {hat,6};
        case esc_N: p_.SET_STATE(41); return {esc_N,6};
        default : return {(size_t)-1,(size_t)-1};
    }
    case 42: CC42: switch(t_.kind()){
        case character: p_.SHIFT_(std::move(t_),18); t_=l_.lex(); goto CC18;
        case meta_char: p_.SHIFT_(std::move(t_),19); t_=l_.lex(); goto CC19;
        case basic_char_class: p_.SHIFT_(std::move(t_),20); t_=l_.lex(); goto CC20;
        case paren_l: p_.SHIFT_(std::move(t_),21); t_=l_.lex(); goto CC21;
        case sqparen_l: p_.SHIFT_(std::move(t_),22); t_=l_.lex(); goto CC22;
        case hat: p_.SHIFT_(std::move(t_),26); t_=l_.lex(); goto CC26;
        case esc_N: p_.SHIFT_(std::move(t_),27); t_=l_.lex(); goto CC27;
        default : return {(size_t)-1,(size_t)-1};
    }
    case 43: CC43: switch(t_.kind()){
        case amount: p_.SHIFT_(std::move(t_),37); t_=l_.lex(); goto CC37;
        case character: p_.SHIFT_(std::move(t_),18); t_=l_.lex(); goto CC18;
        case meta_char: p_.SHIFT_(std::move(t_),19); t_=l_.lex(); goto CC19;
        case basic_char_class: p_.SHIFT_(std::move(t_),20); t_=l_.lex(); goto CC20;
        case paren_l: p_.SHIFT_(std::move(t_),21); t_=l_.lex(); goto CC21;
        case paren_r: p_.SHIFT_(std::move(t_),71); t_=l_.lex(); goto CC71;
        case sqparen_l: p_.SHIFT_(std::move(t_),22); t_=l_.lex(); goto CC22;
        case ast: p_.SHIFT_(std::move(t_),39); t_=l_.lex(); goto CC39;
        case plus: p_.SHIFT_(std::move(t_),40); t_=l_.lex(); goto CC40;
        case qmark: p_.SHIFT_(std::move(t_),41); t_=l_.lex(); goto CC41;
        case vbar: p_.SHIFT_(std::move(t_),42); t_=l_.lex(); goto CC42;
        case hat: p_.SHIFT_(std::move(t_),26); t_=l_.lex(); goto CC26;
        case esc_N: p_.SHIFT_(std::move(t_),27); t_=l_.lex(); goto CC27;
        default : return {(size_t)-1,(size_t)-1};
    }
    case 44: CC44: switch(t_.kind()){
        case character: p_.SHIFT_(std::move(t_),18); t_=l_.lex(); goto CC18;
        case meta_char: p_.SHIFT_(std::move(t_),19); t_=l_.lex(); goto CC19;
        case basic_char_class: p_.SHIFT_(std::move(t_),20); t_=l_.lex(); goto CC20;
        case paren_l: p_.SHIFT_(std::move(t_),21); t_=l_.lex(); goto CC21;
        case sqparen_l: p_.SHIFT_(std::move(t_),22); t_=l_.lex(); goto CC22;
        case hat: p_.SHIFT_(std::move(t_),26); t_=l_.lex(); goto CC26;
        case esc_N: p_.SHIFT_(std::move(t_),27); t_=l_.lex(); goto CC27;
        default : return {(size_t)-1,(size_t)-1};
    }
    case 45: CC45: switch(t_.kind()){
        case character: p_.SHIFT_(std::move(t_),18); t_=l_.lex(); goto CC18;
        case meta_char: p_.SHIFT_(std::move(t_),19); t_=l_.lex(); goto CC19;
        case basic_char_class: p_.SHIFT_(std::move(t_),20); t_=l_.lex(); goto CC20;
        case paren_l: p_.SHIFT_(std::move(t_),21); t_=l_.lex(); goto CC21;
        case sqparen_l: p_.SHIFT_(std::move(t_),22); t_=l_.lex(); goto CC22;
        case hat: p_.SHIFT_(std::move(t_),26); t_=l_.lex(); goto CC26;
        case esc_N: p_.SHIFT_(std::move(t_),27); t_=l_.lex(); goto CC27;
        default : return {(size_t)-1,(size_t)-1};
    }
    case 46: CC46: switch(t_.kind()){
        case character: p_.SHIFT_(std::move(t_),18); t_=l_.lex(); goto CC18;
        case meta_char: p_.SHIFT_(std::move(t_),19); t_=l_.lex(); goto CC19;
        case basic_char_class: p_.SHIFT_(std::move(t_),20); t_=l_.lex(); goto CC20;
        case paren_l: p_.SHIFT_(std::move(t_),21); t_=l_.lex(); goto CC21;
        case sqparen_l: p_.SHIFT_(std::move(t_),22); t_=l_.lex(); goto CC22;
        case hat: p_.SHIFT_(std::move(t_),26); t_=l_.lex(); goto CC26;
        case esc_N: p_.SHIFT_(std::move(t_),27); t_=l_.lex(); goto CC27;
        default : return {(size_t)-1,(size_t)-1};
    }
    case 47: CC47: switch(t_.kind()){
        case ast: p_.SHIFT_(std::move(t_),75); t_=l_.lex(); goto CC75;
        case plus: p_.SHIFT_(std::move(t_),76); t_=l_.lex(); goto CC76;
        case to: p_.SHIFT_(std::move(t_),77); t_=l_.lex(); goto CC77;
        default : return {(size_t)-1,(size_t)-1};
    }
    case 48: CC48: switch(t_.kind()){
        case character: p_.SET_STATE(48); return {character,25};
        case sqparen_r: p_.SET_STATE(48); return {sqparen_r,25};
        default : return {(size_t)-1,(size_t)-1};
    }
    case 49: CC49: switch(t_.kind()){
        case character: p_.SHIFT_(std::move(t_),31); t_=l_.lex(); goto CC31;
        case sqparen_r: p_.SHIFT_(std::move(t_),79); t_=l_.lex(); goto CC79;
        default : return {(size_t)-1,(size_t)-1};
    }
    case 50: CC50: switch(t_.kind()){
        case character: p_.SHIFT_(std::move(t_),31); t_=l_.lex(); goto CC31;
        case basic_char_class: p_.SHIFT_(std::move(t_),68); t_=l_.lex(); goto CC68;
        case sqparen_l: p_.SHIFT_(std::move(t_),69); t_=l_.lex(); goto CC69;
        default : return {(size_t)-1,(size_t)-1};
    }
    case 51: CC51: switch(t_.kind()){
        case amount: p_.SHIFT_(std::move(t_),37); t_=l_.lex(); goto CC37;
        case character: p_.SHIFT_(std::move(t_),18); t_=l_.lex(); goto CC18;
        case meta_char: p_.SHIFT_(std::move(t_),19); t_=l_.lex(); goto CC19;
        case basic_char_class: p_.SHIFT_(std::move(t_),20); t_=l_.lex(); goto CC20;
        case paren_l: p_.SHIFT_(std::move(t_),21); t_=l_.lex(); goto CC21;
        case paren_r: p_.SHIFT_(std::move(t_),82); t_=l_.lex(); goto CC82;
        case sqparen_l: p_.SHIFT_(std::move(t_),22); t_=l_.lex(); goto CC22;
        case ast: p_.SHIFT_(std::move(t_),39); t_=l_.lex(); goto CC39;
        case plus: p_.SHIFT_(std::move(t_),40); t_=l_.lex(); goto CC40;
        case qmark: p_.SHIFT_(std::move(t_),41); t_=l_.lex(); goto CC41;
        case vbar: p_.SHIFT_(std::move(t_),42); t_=l_.lex(); goto CC42;
        case hat: p_.SHIFT_(std::move(t_),26); t_=l_.lex(); goto CC26;
        case esc_N: p_.SHIFT_(std::move(t_),27); t_=l_.lex(); goto CC27;
        default : return {(size_t)-1,(size_t)-1};
    }
    case 52: CC52: switch(t_.kind()){
        case amount: p_.SHIFT_(std::move(t_),37); t_=l_.lex(); goto CC37;
        case character: p_.SHIFT_(std::move(t_),18); t_=l_.lex(); goto CC18;
        case meta_char: p_.SHIFT_(std::move(t_),19); t_=l_.lex(); goto CC19;
        case basic_char_class: p_.SHIFT_(std::move(t_),20); t_=l_.lex(); goto CC20;
        case paren_l: p_.SHIFT_(std::move(t_),21); t_=l_.lex(); goto CC21;
        case paren_r: p_.SHIFT_(std::move(t_),83); t_=l_.lex(); goto CC83;
        case sqparen_l: p_.SHIFT_(std::move(t_),22); t_=l_.lex(); goto CC22;
        case ast: p_.SHIFT_(std::move(t_),39); t_=l_.lex(); goto CC39;
        case plus: p_.SHIFT_(std::move(t_),40); t_=l_.lex(); goto CC40;
        case qmark: p_.SHIFT_(std::move(t_),41); t_=l_.lex(); goto CC41;
        case vbar: p_.SHIFT_(std::move(t_),42); t_=l_.lex(); goto CC42;
        case hat: p_.SHIFT_(std::move(t_),26); t_=l_.lex(); goto CC26;
        case esc_N: p_.SHIFT_(std::move(t_),27); t_=l_.lex(); goto CC27;
        default : return {(size_t)-1,(size_t)-1};
    }
    case 53: CC53: switch(t_.kind()){
        case amount: p_.SHIFT_(std::move(t_),37); t_=l_.lex(); goto CC37;
        case character: p_.SHIFT_(std::move(t_),18); t_=l_.lex(); goto CC18;
        case meta_char: p_.SHIFT_(std::move(t_),19); t_=l_.lex(); goto CC19;
        case basic_char_class: p_.SHIFT_(std::move(t_),20); t_=l_.lex(); goto CC20;
        case paren_l: p_.SHIFT_(std::move(t_),21); t_=l_.lex(); goto CC21;
        case paren_r: p_.SHIFT_(std::move(t_),84); t_=l_.lex(); goto CC84;
        case sqparen_l: p_.SHIFT_(std::move(t_),22); t_=l_.lex(); goto CC22;
        case ast: p_.SHIFT_(std::move(t_),39); t_=l_.lex(); goto CC39;
        case plus: p_.SHIFT_(std::move(t_),40); t_=l_.lex(); goto CC40;
        case qmark: p_.SHIFT_(std::move(t_),41); t_=l_.lex(); goto CC41;
        case vbar: p_.SHIFT_(std::move(t_),42); t_=l_.lex(); goto CC42;
        case hat: p_.SHIFT_(std::move(t_),26); t_=l_.lex(); goto CC26;
        case esc_N: p_.SHIFT_(std::move(t_),27); t_=l_.lex(); goto CC27;
        default : return {(size_t)-1,(size_t)-1};
    }
    case 54: CC54: switch(t_.kind()){
        case basic_char_class: p_.SHIFT_(std::move(t_),68); t_=l_.lex(); goto CC68;
        case sqparen_l: p_.SHIFT_(std::move(t_),69); t_=l_.lex(); goto CC69;
        default : return {(size_t)-1,(size_t)-1};
    }
    case 55: CC55: switch(t_.kind()){
        case basic_char_class: p_.SHIFT_(std::move(t_),68); t_=l_.lex(); goto CC68;
        case sqparen_l: p_.SHIFT_(std::move(t_),69); t_=l_.lex(); goto CC69;
        default : return {(size_t)-1,(size_t)-1};
    }
    case 56: CC56: switch(t_.kind()){
        case basic_char_class: p_.SHIFT_(std::move(t_),68); t_=l_.lex(); goto CC68;
        case sqparen_l: p_.SHIFT_(std::move(t_),69); t_=l_.lex(); goto CC69;
        default : return {(size_t)-1,(size_t)-1};
    }
    case 57: CC57: switch(t_.kind()){
        case amount: p_.SET_STATE(57); return {amount,16};
        case character: p_.SET_STATE(57); return {character,16};
        case meta_char: p_.SET_STATE(57); return {meta_char,16};
        case basic_char_class: p_.SET_STATE(57); return {basic_char_class,16};
        case paren_l: p_.SET_STATE(57); return {paren_l,16};
        case sqparen_l: p_.SET_STATE(57); return {sqparen_l,16};
        case ast: p_.SET_STATE(57); return {ast,16};
        case plus: p_.SET_STATE(57); return {plus,16};
        case qmark: p_.SET_STATE(57); return {qmark,16};
        case vbar: p_.SET_STATE(57); return {vbar,16};
        case hat: p_.SET_STATE(57); return {hat,16};
        case esc_N: p_.SET_STATE(57); return {esc_N,16};
        case EOF_: p_.SET_STATE(57); return {EOF_,16};
        default : return {(size_t)-1,(size_t)-1};
    }
    case 58: CC58: switch(t_.kind()){
        case character: p_.SET_STATE(58); return {character,24};
        case sqparen_r: p_.SET_STATE(58); return {sqparen_r,24};
        default : return {(size_t)-1,(size_t)-1};
    }
    case 59: CC59: switch(t_.kind()){
        case amount: p_.SET_STATE(59); return {amount,17};
        case character: p_.SET_STATE(59); return {character,17};
        case meta_char: p_.SET_STATE(59); return {meta_char,17};
        case basic_char_class: p_.SET_STATE(59); return {basic_char_class,17};
        case paren_l: p_.SET_STATE(59); return {paren_l,17};
        case sqparen_l: p_.SET_STATE(59); return {sqparen_l,17};
        case ast: p_.SET_STATE(59); return {ast,17};
        case plus: p_.SET_STATE(59); return {plus,17};
        case qmark: p_.SET_STATE(59); return {qmark,17};
        case vbar: p_.SET_STATE(59); return {vbar,17};
        case hat: p_.SET_STATE(59); return {hat,17};
        case esc_N: p_.SET_STATE(59); return {esc_N,17};
        case EOF_: p_.SET_STATE(59); return {EOF_,17};
        default : return {(size_t)-1,(size_t)-1};
    }
    case 60: CC60: switch(t_.kind()){
        case character: p_.SHIFT_(std::move(t_),88); t_=l_.lex(); goto CC88;
        default : return {(size_t)-1,(size_t)-1};
    }
    case 61: CC61: switch(t_.kind()){
        case ast: p_.SHIFT_(std::move(t_),89); t_=l_.lex(); goto CC89;
        case plus: p_.SHIFT_(std::move(t_),90); t_=l_.lex(); goto CC90;
        case to: p_.SHIFT_(std::move(t_),91); t_=l_.lex(); goto CC91;
        default : return {(size_t)-1,(size_t)-1};
    }
    case 62: CC62: switch(t_.kind()){
        case character: p_.SET_STATE(62); return {character,25};
        case sqparen_r: p_.SET_STATE(62); return {sqparen_r,25};
        default : return {(size_t)-1,(size_t)-1};
    }
    case 63: CC63: switch(t_.kind()){
        case character: p_.SHIFT_(std::move(t_),31); t_=l_.lex(); goto CC31;
        case sqparen_r: p_.SHIFT_(std::move(t_),93); t_=l_.lex(); goto CC93;
        default : return {(size_t)-1,(size_t)-1};
    }
    case 64: CC64: switch(t_.kind()){
        case character: p_.SHIFT_(std::move(t_),31); t_=l_.lex(); goto CC31;
        case basic_char_class: p_.SHIFT_(std::move(t_),68); t_=l_.lex(); goto CC68;
        case sqparen_l: p_.SHIFT_(std::move(t_),69); t_=l_.lex(); goto CC69;
        default : return {(size_t)-1,(size_t)-1};
    }
    case 65: CC65: switch(t_.kind()){
        case sqparen_r: p_.SHIFT_(std::move(t_),96); t_=l_.lex(); goto CC96;
        default : return {(size_t)-1,(size_t)-1};
    }
    case 66: CC66: switch(t_.kind()){
        case character: p_.SET_STATE(66); return {character,25};
        case sqparen_r: p_.SET_STATE(66); return {sqparen_r,25};
        default : return {(size_t)-1,(size_t)-1};
    }
    case 67: CC67: switch(t_.kind()){
        case character: p_.SHIFT_(std::move(t_),31); t_=l_.lex(); goto CC31;
        case sqparen_r: p_.SHIFT_(std::move(t_),97); t_=l_.lex(); goto CC97;
        default : return {(size_t)-1,(size_t)-1};
    }
    case 68: CC68: switch(t_.kind()){
        case sqparen_r: p_.SET_STATE(68); return {sqparen_r,23};
        default : return {(size_t)-1,(size_t)-1};
    }
    case 69: CC69: switch(t_.kind()){
        case character: p_.SHIFT_(std::move(t_),31); t_=l_.lex(); goto CC31;
        case basic_char_class: p_.SHIFT_(std::move(t_),32); t_=l_.lex(); goto CC32;
        case sqparen_l: p_.SHIFT_(std::move(t_),33); t_=l_.lex(); goto CC33;
        case hat: p_.SHIFT_(std::move(t_),101); t_=l_.lex(); goto CC101;
        default : return {(size_t)-1,(size_t)-1};
    }
    case 70: CC70: switch(t_.kind()){
        case amount: p_.SHIFT_(std::move(t_),37); t_=l_.lex(); goto CC37;
        case character: p_.SET_STATE(70); return {character,2};
        case meta_char: p_.SET_STATE(70); return {meta_char,2};
        case basic_char_class: p_.SET_STATE(70); return {basic_char_class,2};
        case paren_l: p_.SET_STATE(70); return {paren_l,2};
        case paren_r: p_.SET_STATE(70); return {paren_r,2};
        case sqparen_l: p_.SET_STATE(70); return {sqparen_l,2};
        case ast: p_.SHIFT_(std::move(t_),39); t_=l_.lex(); goto CC39;
        case plus: p_.SHIFT_(std::move(t_),40); t_=l_.lex(); goto CC40;
        case qmark: p_.SHIFT_(std::move(t_),41); t_=l_.lex(); goto CC41;
        case vbar: p_.SET_STATE(70); return {vbar,2};
        case hat: p_.SET_STATE(70); return {hat,2};
        case esc_N: p_.SET_STATE(70); return {esc_N,2};
        default : return {(size_t)-1,(size_t)-1};
    }
    case 71: CC71: switch(t_.kind()){
        case amount: p_.SET_STATE(71); return {amount,3};
        case character: p_.SET_STATE(71); return {character,3};
        case meta_char: p_.SET_STATE(71); return {meta_char,3};
        case basic_char_class: p_.SET_STATE(71); return {basic_char_class,3};
        case paren_l: p_.SET_STATE(71); return {paren_l,3};
        case paren_r: p_.SET_STATE(71); return {paren_r,3};
        case sqparen_l: p_.SET_STATE(71); return {sqparen_l,3};
        case ast: p_.SET_STATE(71); return {ast,3};
        case plus: p_.SET_STATE(71); return {plus,3};
        case qmark: p_.SET_STATE(71); return {qmark,3};
        case vbar: p_.SET_STATE(71); return {vbar,3};
        case hat: p_.SET_STATE(71); return {hat,3};
        case esc_N: p_.SET_STATE(71); return {esc_N,3};
        default : return {(size_t)-1,(size_t)-1};
    }
    case 72: CC72: switch(t_.kind()){
        case amount: p_.SHIFT_(std::move(t_),37); t_=l_.lex(); goto CC37;
        case character: p_.SHIFT_(std::move(t_),18); t_=l_.lex(); goto CC18;
        case meta_char: p_.SHIFT_(std::move(t_),19); t_=l_.lex(); goto CC19;
        case basic_char_class: p_.SHIFT_(std::move(t_),20); t_=l_.lex(); goto CC20;
        case paren_l: p_.SHIFT_(std::move(t_),21); t_=l_.lex(); goto CC21;
        case paren_r: p_.SHIFT_(std::move(t_),102); t_=l_.lex(); goto CC102;
        case sqparen_l: p_.SHIFT_(std::move(t_),22); t_=l_.lex(); goto CC22;
        case ast: p_.SHIFT_(std::move(t_),39); t_=l_.lex(); goto CC39;
        case plus: p_.SHIFT_(std::move(t_),40); t_=l_.lex(); goto CC40;
        case qmark: p_.SHIFT_(std::move(t_),41); t_=l_.lex(); goto CC41;
        case vbar: p_.SHIFT_(std::move(t_),42); t_=l_.lex(); goto CC42;
        case hat: p_.SHIFT_(std::move(t_),26); t_=l_.lex(); goto CC26;
        case esc_N: p_.SHIFT_(std::move(t_),27); t_=l_.lex(); goto CC27;
        default : return {(size_t)-1,(size_t)-1};
    }
    case 73: CC73: switch(t_.kind()){
        case amount: p_.SHIFT_(std::move(t_),37); t_=l_.lex(); goto CC37;
        case character: p_.SHIFT_(std::move(t_),18); t_=l_.lex(); goto CC18;
        case meta_char: p_.SHIFT_(std::move(t_),19); t_=l_.lex(); goto CC19;
        case basic_char_class: p_.SHIFT_(std::move(t_),20); t_=l_.lex(); goto CC20;
        case paren_l: p_.SHIFT_(std::move(t_),21); t_=l_.lex(); goto CC21;
        case paren_r: p_.SHIFT_(std::move(t_),103); t_=l_.lex(); goto CC103;
        case sqparen_l: p_.SHIFT_(std::move(t_),22); t_=l_.lex(); goto CC22;
        case ast: p_.SHIFT_(std::move(t_),39); t_=l_.lex(); goto CC39;
        case plus: p_.SHIFT_(std::move(t_),40); t_=l_.lex(); goto CC40;
        case qmark: p_.SHIFT_(std::move(t_),41); t_=l_.lex(); goto CC41;
        case vbar: p_.SHIFT_(std::move(t_),42); t_=l_.lex(); goto CC42;
        case hat: p_.SHIFT_(std::move(t_),26); t_=l_.lex(); goto CC26;
        case esc_N: p_.SHIFT_(std::move(t_),27); t_=l_.lex(); goto CC27;
        default : return {(size_t)-1,(size_t)-1};
    }
    case 74: CC74: switch(t_.kind()){
        case amount: p_.SHIFT_(std::move(t_),37); t_=l_.lex(); goto CC37;
        case character: p_.SHIFT_(std::move(t_),18); t_=l_.lex(); goto CC18;
        case meta_char: p_.SHIFT_(std::move(t_),19); t_=l_.lex(); goto CC19;
        case basic_char_class: p_.SHIFT_(std::move(t_),20); t_=l_.lex(); goto CC20;
        case paren_l: p_.SHIFT_(std::move(t_),21); t_=l_.lex(); goto CC21;
        case paren_r: p_.SHIFT_(std::move(t_),104); t_=l_.lex(); goto CC104;
        case sqparen_l: p_.SHIFT_(std::move(t_),22); t_=l_.lex(); goto CC22;
        case ast: p_.SHIFT_(std::move(t_),39); t_=l_.lex(); goto CC39;
        case plus: p_.SHIFT_(std::move(t_),40); t_=l_.lex(); goto CC40;
        case qmark: p_.SHIFT_(std::move(t_),41); t_=l_.lex(); goto CC41;
        case vbar: p_.SHIFT_(std::move(t_),42); t_=l_.lex(); goto CC42;
        case hat: p_.SHIFT_(std::move(t_),26); t_=l_.lex(); goto CC26;
        case esc_N: p_.SHIFT_(std::move(t_),27); t_=l_.lex(); goto CC27;
        default : return {(size_t)-1,(size_t)-1};
    }
    case 75: CC75: switch(t_.kind()){
        case basic_char_class: p_.SHIFT_(std::move(t_),68); t_=l_.lex(); goto CC68;
        case sqparen_l: p_.SHIFT_(std::move(t_),69); t_=l_.lex(); goto CC69;
        default : return {(size_t)-1,(size_t)-1};
    }
    case 76: CC76: switch(t_.kind()){
        case basic_char_class: p_.SHIFT_(std::move(t_),68); t_=l_.lex(); goto CC68;
        case sqparen_l: p_.SHIFT_(std::move(t_),69); t_=l_.lex(); goto CC69;
        default : return {(size_t)-1,(size_t)-1};
    }
    case 77: CC77: switch(t_.kind()){
        case basic_char_class: p_.SHIFT_(std::move(t_),68); t_=l_.lex(); goto CC68;
        case sqparen_l: p_.SHIFT_(std::move(t_),69); t_=l_.lex(); goto CC69;
        default : return {(size_t)-1,(size_t)-1};
    }
    case 78: CC78: switch(t_.kind()){
        case amount: p_.SET_STATE(78); return {amount,16};
        case character: p_.SET_STATE(78); return {character,16};
        case meta_char: p_.SET_STATE(78); return {meta_char,16};
        case basic_char_class: p_.SET_STATE(78); return {basic_char_class,16};
        case paren_l: p_.SET_STATE(78); return {paren_l,16};
        case paren_r: p_.SET_STATE(78); return {paren_r,16};
        case sqparen_l: p_.SET_STATE(78); return {sqparen_l,16};
        case ast: p_.SET_STATE(78); return {ast,16};
        case plus: p_.SET_STATE(78); return {plus,16};
        case qmark: p_.SET_STATE(78); return {qmark,16};
        case vbar: p_.SET_STATE(78); return {vbar,16};
        case hat: p_.SET_STATE(78); return {hat,16};
        case esc_N: p_.SET_STATE(78); return {esc_N,16};
        default : return {(size_t)-1,(size_t)-1};
    }
    case 79: CC79: switch(t_.kind()){
        case amount: p_.SET_STATE(79); return {amount,17};
        case character: p_.SET_STATE(79); return {character,17};
        case meta_char: p_.SET_STATE(79); return {meta_char,17};
        case basic_char_class: p_.SET_STATE(79); return {basic_char_class,17};
        case paren_l: p_.SET_STATE(79); return {paren_l,17};
        case paren_r: p_.SET_STATE(79); return {paren_r,17};
        case sqparen_l: p_.SET_STATE(79); return {sqparen_l,17};
        case ast: p_.SET_STATE(79); return {ast,17};
        case plus: p_.SET_STATE(79); return {plus,17};
        case qmark: p_.SET_STATE(79); return {qmark,17};
        case vbar: p_.SET_STATE(79); return {vbar,17};
        case hat: p_.SET_STATE(79); return {hat,17};
        case esc_N: p_.SET_STATE(79); return {esc_N,17};
        default : return {(size_t)-1,(size_t)-1};
    }
    case 80: CC80: switch(t_.kind()){
        case sqparen_r: p_.SHIFT_(std::move(t_),108); t_=l_.lex(); goto CC108;
        default : return {(size_t)-1,(size_t)-1};
    }
    case 81: CC81: switch(t_.kind()){
        case character: p_.SHIFT_(std::move(t_),31); t_=l_.lex(); goto CC31;
        case sqparen_r: p_.SHIFT_(std::move(t_),109); t_=l_.lex(); goto CC109;
        default : return {(size_t)-1,(size_t)-1};
    }
    case 82: CC82: switch(t_.kind()){
        case amount: p_.SET_STATE(82); return {amount,8};
        case character: p_.SET_STATE(82); return {character,8};
        case meta_char: p_.SET_STATE(82); return {meta_char,8};
        case basic_char_class: p_.SET_STATE(82); return {basic_char_class,8};
        case paren_l: p_.SET_STATE(82); return {paren_l,8};
        case sqparen_l: p_.SET_STATE(82); return {sqparen_l,8};
        case ast: p_.SET_STATE(82); return {ast,8};
        case plus: p_.SET_STATE(82); return {plus,8};
        case qmark: p_.SET_STATE(82); return {qmark,8};
        case vbar: p_.SET_STATE(82); return {vbar,8};
        case hat: p_.SET_STATE(82); return {hat,8};
        case esc_N: p_.SET_STATE(82); return {esc_N,8};
        case EOF_: p_.SET_STATE(82); return {EOF_,8};
        default : return {(size_t)-1,(size_t)-1};
    }
    case 83: CC83: switch(t_.kind()){
        case amount: p_.SET_STATE(83); return {amount,9};
        case character: p_.SET_STATE(83); return {character,9};
        case meta_char: p_.SET_STATE(83); return {meta_char,9};
        case basic_char_class: p_.SET_STATE(83); return {basic_char_class,9};
        case paren_l: p_.SET_STATE(83); return {paren_l,9};
        case sqparen_l: p_.SET_STATE(83); return {sqparen_l,9};
        case ast: p_.SET_STATE(83); return {ast,9};
        case plus: p_.SET_STATE(83); return {plus,9};
        case qmark: p_.SET_STATE(83); return {qmark,9};
        case vbar: p_.SET_STATE(83); return {vbar,9};
        case hat: p_.SET_STATE(83); return {hat,9};
        case esc_N: p_.SET_STATE(83); return {esc_N,9};
        case EOF_: p_.SET_STATE(83); return {EOF_,9};
        default : return {(size_t)-1,(size_t)-1};
    }
    case 84: CC84: switch(t_.kind()){
        case amount: p_.SET_STATE(84); return {amount,10};
        case character: p_.SET_STATE(84); return {character,10};
        case meta_char: p_.SET_STATE(84); return {meta_char,10};
        case basic_char_class: p_.SET_STATE(84); return {basic_char_class,10};
        case paren_l: p_.SET_STATE(84); return {paren_l,10};
        case sqparen_l: p_.SET_STATE(84); return {sqparen_l,10};
        case ast: p_.SET_STATE(84); return {ast,10};
        case plus: p_.SET_STATE(84); return {plus,10};
        case qmark: p_.SET_STATE(84); return {qmark,10};
        case vbar: p_.SET_STATE(84); return {vbar,10};
        case hat: p_.SET_STATE(84); return {hat,10};
        case esc_N: p_.SET_STATE(84); return {esc_N,10};
        case EOF_: p_.SET_STATE(84); return {EOF_,10};
        default : return {(size_t)-1,(size_t)-1};
    }
    case 85: CC85: switch(t_.kind()){
        case sqparen_r: p_.SHIFT_(std::move(t_),110); t_=l_.lex(); goto CC110;
        default : return {(size_t)-1,(size_t)-1};
    }
    case 86: CC86: switch(t_.kind()){
        case sqparen_r: p_.SHIFT_(std::move(t_),111); t_=l_.lex(); goto CC111;
        default : return {(size_t)-1,(size_t)-1};
    }
    case 87: CC87: switch(t_.kind()){
        case sqparen_r: p_.SHIFT_(std::move(t_),112); t_=l_.lex(); goto CC112;
        default : return {(size_t)-1,(size_t)-1};
    }
    case 88: CC88: switch(t_.kind()){
        case character: p_.SET_STATE(88); return {character,26};
        case sqparen_r: p_.SET_STATE(88); return {sqparen_r,26};
        default : return {(size_t)-1,(size_t)-1};
    }
    case 89: CC89: switch(t_.kind()){
        case basic_char_class: p_.SHIFT_(std::move(t_),68); t_=l_.lex(); goto CC68;
        case sqparen_l: p_.SHIFT_(std::move(t_),69); t_=l_.lex(); goto CC69;
        default : return {(size_t)-1,(size_t)-1};
    }
    case 90: CC90: switch(t_.kind()){
        case basic_char_class: p_.SHIFT_(std::move(t_),68); t_=l_.lex(); goto CC68;
        case sqparen_l: p_.SHIFT_(std::move(t_),69); t_=l_.lex(); goto CC69;
        default : return {(size_t)-1,(size_t)-1};
    }
    case 91: CC91: switch(t_.kind()){
        case basic_char_class: p_.SHIFT_(std::move(t_),68); t_=l_.lex(); goto CC68;
        case sqparen_l: p_.SHIFT_(std::move(t_),69); t_=l_.lex(); goto CC69;
        default : return {(size_t)-1,(size_t)-1};
    }
    case 92: CC92: switch(t_.kind()){
        case ast: p_.SET_STATE(92); return {ast,16};
        case plus: p_.SET_STATE(92); return {plus,16};
        case to: p_.SET_STATE(92); return {to,16};
        default : return {(size_t)-1,(size_t)-1};
    }
    case 93: CC93: switch(t_.kind()){
        case ast: p_.SET_STATE(93); return {ast,17};
        case plus: p_.SET_STATE(93); return {plus,17};
        case to: p_.SET_STATE(93); return {to,17};
        default : return {(size_t)-1,(size_t)-1};
    }
    case 94: CC94: switch(t_.kind()){
        case sqparen_r: p_.SHIFT_(std::move(t_),116); t_=l_.lex(); goto CC116;
        default : return {(size_t)-1,(size_t)-1};
    }
    case 95: CC95: switch(t_.kind()){
        case character: p_.SHIFT_(std::move(t_),31); t_=l_.lex(); goto CC31;
        case sqparen_r: p_.SHIFT_(std::move(t_),117); t_=l_.lex(); goto CC117;
        default : return {(size_t)-1,(size_t)-1};
    }
    case 96: CC96: switch(t_.kind()){
        case amount: p_.SET_STATE(96); return {amount,20};
        case character: p_.SET_STATE(96); return {character,20};
        case meta_char: p_.SET_STATE(96); return {meta_char,20};
        case basic_char_class: p_.SET_STATE(96); return {basic_char_class,20};
        case paren_l: p_.SET_STATE(96); return {paren_l,20};
        case sqparen_l: p_.SET_STATE(96); return {sqparen_l,20};
        case ast: p_.SET_STATE(96); return {ast,20};
        case plus: p_.SET_STATE(96); return {plus,20};
        case qmark: p_.SET_STATE(96); return {qmark,20};
        case vbar: p_.SET_STATE(96); return {vbar,20};
        case hat: p_.SET_STATE(96); return {hat,20};
        case esc_N: p_.SET_STATE(96); return {esc_N,20};
        case EOF_: p_.SET_STATE(96); return {EOF_,20};
        default : return {(size_t)-1,(size_t)-1};
    }
    case 97: CC97: switch(t_.kind()){
        case amount: p_.SET_STATE(97); return {amount,21};
        case character: p_.SET_STATE(97); return {character,21};
        case meta_char: p_.SET_STATE(97); return {meta_char,21};
        case basic_char_class: p_.SET_STATE(97); return {basic_char_class,21};
        case paren_l: p_.SET_STATE(97); return {paren_l,21};
        case sqparen_l: p_.SET_STATE(97); return {sqparen_l,21};
        case ast: p_.SET_STATE(97); return {ast,21};
        case plus: p_.SET_STATE(97); return {plus,21};
        case qmark: p_.SET_STATE(97); return {qmark,21};
        case vbar: p_.SET_STATE(97); return {vbar,21};
        case hat: p_.SET_STATE(97); return {hat,21};
        case esc_N: p_.SET_STATE(97); return {esc_N,21};
        case EOF_: p_.SET_STATE(97); return {EOF_,21};
        default : return {(size_t)-1,(size_t)-1};
    }
    case 98: CC98: switch(t_.kind()){
        case ast: p_.SHIFT_(std::move(t_),118); t_=l_.lex(); goto CC118;
        case plus: p_.SHIFT_(std::move(t_),119); t_=l_.lex(); goto CC119;
        case to: p_.SHIFT_(std::move(t_),120); t_=l_.lex(); goto CC120;
        default : return {(size_t)-1,(size_t)-1};
    }
    case 99: CC99: switch(t_.kind()){
        case character: p_.SET_STATE(99); return {character,25};
        case sqparen_r: p_.SET_STATE(99); return {sqparen_r,25};
        default : return {(size_t)-1,(size_t)-1};
    }
    case 100: CC100: switch(t_.kind()){
        case character: p_.SHIFT_(std::move(t_),31); t_=l_.lex(); goto CC31;
        case sqparen_r: p_.SHIFT_(std::move(t_),122); t_=l_.lex(); goto CC122;
        default : return {(size_t)-1,(size_t)-1};
    }
    case 101: CC101: switch(t_.kind()){
        case character: p_.SHIFT_(std::move(t_),31); t_=l_.lex(); goto CC31;
        case basic_char_class: p_.SHIFT_(std::move(t_),68); t_=l_.lex(); goto CC68;
        case sqparen_l: p_.SHIFT_(std::move(t_),69); t_=l_.lex(); goto CC69;
        default : return {(size_t)-1,(size_t)-1};
    }
    case 102: CC102: switch(t_.kind()){
        case amount: p_.SET_STATE(102); return {amount,8};
        case character: p_.SET_STATE(102); return {character,8};
        case meta_char: p_.SET_STATE(102); return {meta_char,8};
        case basic_char_class: p_.SET_STATE(102); return {basic_char_class,8};
        case paren_l: p_.SET_STATE(102); return {paren_l,8};
        case paren_r: p_.SET_STATE(102); return {paren_r,8};
        case sqparen_l: p_.SET_STATE(102); return {sqparen_l,8};
        case ast: p_.SET_STATE(102); return {ast,8};
        case plus: p_.SET_STATE(102); return {plus,8};
        case qmark: p_.SET_STATE(102); return {qmark,8};
        case vbar: p_.SET_STATE(102); return {vbar,8};
        case hat: p_.SET_STATE(102); return {hat,8};
        case esc_N: p_.SET_STATE(102); return {esc_N,8};
        default : return {(size_t)-1,(size_t)-1};
    }
    case 103: CC103: switch(t_.kind()){
        case amount: p_.SET_STATE(103); return {amount,9};
        case character: p_.SET_STATE(103); return {character,9};
        case meta_char: p_.SET_STATE(103); return {meta_char,9};
        case basic_char_class: p_.SET_STATE(103); return {basic_char_class,9};
        case paren_l: p_.SET_STATE(103); return {paren_l,9};
        case paren_r: p_.SET_STATE(103); return {paren_r,9};
        case sqparen_l: p_.SET_STATE(103); return {sqparen_l,9};
        case ast: p_.SET_STATE(103); return {ast,9};
        case plus: p_.SET_STATE(103); return {plus,9};
        case qmark: p_.SET_STATE(103); return {qmark,9};
        case vbar: p_.SET_STATE(103); return {vbar,9};
        case hat: p_.SET_STATE(103); return {hat,9};
        case esc_N: p_.SET_STATE(103); return {esc_N,9};
        default : return {(size_t)-1,(size_t)-1};
    }
    case 104: CC104: switch(t_.kind()){
        case amount: p_.SET_STATE(104); return {amount,10};
        case character: p_.SET_STATE(104); return {character,10};
        case meta_char: p_.SET_STATE(104); return {meta_char,10};
        case basic_char_class: p_.SET_STATE(104); return {basic_char_class,10};
        case paren_l: p_.SET_STATE(104); return {paren_l,10};
        case paren_r: p_.SET_STATE(104); return {paren_r,10};
        case sqparen_l: p_.SET_STATE(104); return {sqparen_l,10};
        case ast: p_.SET_STATE(104); return {ast,10};
        case plus: p_.SET_STATE(104); return {plus,10};
        case qmark: p_.SET_STATE(104); return {qmark,10};
        case vbar: p_.SET_STATE(104); return {vbar,10};
        case hat: p_.SET_STATE(104); return {hat,10};
        case esc_N: p_.SET_STATE(104); return {esc_N,10};
        default : return {(size_t)-1,(size_t)-1};
    }
    case 105: CC105: switch(t_.kind()){
        case sqparen_r: p_.SHIFT_(std::move(t_),125); t_=l_.lex(); goto CC125;
        default : return {(size_t)-1,(size_t)-1};
    }
    case 106: CC106: switch(t_.kind()){
        case sqparen_r: p_.SHIFT_(std::move(t_),126); t_=l_.lex(); goto CC126;
        default : return {(size_t)-1,(size_t)-1};
    }
    case 107: CC107: switch(t_.kind()){
        case sqparen_r: p_.SHIFT_(std::move(t_),127); t_=l_.lex(); goto CC127;
        default : return {(size_t)-1,(size_t)-1};
    }
    case 108: CC108: switch(t_.kind()){
        case amount: p_.SET_STATE(108); return {amount,20};
        case character: p_.SET_STATE(108); return {character,20};
        case meta_char: p_.SET_STATE(108); return {meta_char,20};
        case basic_char_class: p_.SET_STATE(108); return {basic_char_class,20};
        case paren_l: p_.SET_STATE(108); return {paren_l,20};
        case paren_r: p_.SET_STATE(108); return {paren_r,20};
        case sqparen_l: p_.SET_STATE(108); return {sqparen_l,20};
        case ast: p_.SET_STATE(108); return {ast,20};
        case plus: p_.SET_STATE(108); return {plus,20};
        case qmark: p_.SET_STATE(108); return {qmark,20};
        case vbar: p_.SET_STATE(108); return {vbar,20};
        case hat: p_.SET_STATE(108); return {hat,20};
        case esc_N: p_.SET_STATE(108); return {esc_N,20};
        default : return {(size_t)-1,(size_t)-1};
    }
    case 109: CC109: switch(t_.kind()){
        case amount: p_.SET_STATE(109); return {amount,21};
        case character: p_.SET_STATE(109); return {character,21};
        case meta_char: p_.SET_STATE(109); return {meta_char,21};
        case basic_char_class: p_.SET_STATE(109); return {basic_char_class,21};
        case paren_l: p_.SET_STATE(109); return {paren_l,21};
        case paren_r: p_.SET_STATE(109); return {paren_r,21};
        case sqparen_l: p_.SET_STATE(109); return {sqparen_l,21};
        case ast: p_.SET_STATE(109); return {ast,21};
        case plus: p_.SET_STATE(109); return {plus,21};
        case qmark: p_.SET_STATE(109); return {qmark,21};
        case vbar: p_.SET_STATE(109); return {vbar,21};
        case hat: p_.SET_STATE(109); return {hat,21};
        case esc_N: p_.SET_STATE(109); return {esc_N,21};
        default : return {(size_t)-1,(size_t)-1};
    }
    case 110: CC110: switch(t_.kind()){
        case amount: p_.SET_STATE(110); return {amount,19};
        case character: p_.SET_STATE(110); return {character,19};
        case meta_char: p_.SET_STATE(110); return {meta_char,19};
        case basic_char_class: p_.SET_STATE(110); return {basic_char_class,19};
        case paren_l: p_.SET_STATE(110); return {paren_l,19};
        case sqparen_l: p_.SET_STATE(110); return {sqparen_l,19};
        case ast: p_.SET_STATE(110); return {ast,19};
        case plus: p_.SET_STATE(110); return {plus,19};
        case qmark: p_.SET_STATE(110); return {qmark,19};
        case vbar: p_.SET_STATE(110); return {vbar,19};
        case hat: p_.SET_STATE(110); return {hat,19};
        case esc_N: p_.SET_STATE(110); return {esc_N,19};
        case EOF_: p_.SET_STATE(110); return {EOF_,19};
        default : return {(size_t)-1,(size_t)-1};
    }
    case 111: CC111: switch(t_.kind()){
        case amount: p_.SET_STATE(111); return {amount,18};
        case character: p_.SET_STATE(111); return {character,18};
        case meta_char: p_.SET_STATE(111); return {meta_char,18};
        case basic_char_class: p_.SET_STATE(111); return {basic_char_class,18};
        case paren_l: p_.SET_STATE(111); return {paren_l,18};
        case sqparen_l: p_.SET_STATE(111); return {sqparen_l,18};
        case ast: p_.SET_STATE(111); return {ast,18};
        case plus: p_.SET_STATE(111); return {plus,18};
        case qmark: p_.SET_STATE(111); return {qmark,18};
        case vbar: p_.SET_STATE(111); return {vbar,18};
        case hat: p_.SET_STATE(111); return {hat,18};
        case esc_N: p_.SET_STATE(111); return {esc_N,18};
        case EOF_: p_.SET_STATE(111); return {EOF_,18};
        default : return {(size_t)-1,(size_t)-1};
    }
    case 112: CC112: switch(t_.kind()){
        case amount: p_.SET_STATE(112); return {amount,22};
        case character: p_.SET_STATE(112); return {character,22};
        case meta_char: p_.SET_STATE(112); return {meta_char,22};
        case basic_char_class: p_.SET_STATE(112); return {basic_char_class,22};
        case paren_l: p_.SET_STATE(112); return {paren_l,22};
        case sqparen_l: p_.SET_STATE(112); return {sqparen_l,22};
        case ast: p_.SET_STATE(112); return {ast,22};
        case plus: p_.SET_STATE(112); return {plus,22};
        case qmark: p_.SET_STATE(112); return {qmark,22};
        case vbar: p_.SET_STATE(112); return {vbar,22};
        case hat: p_.SET_STATE(112); return {hat,22};
        case esc_N: p_.SET_STATE(112); return {esc_N,22};
        case EOF_: p_.SET_STATE(112); return {EOF_,22};
        default : return {(size_t)-1,(size_t)-1};
    }
    case 113: CC113: switch(t_.kind()){
        case sqparen_r: p_.SHIFT_(std::move(t_),128); t_=l_.lex(); goto CC128;
        default : return {(size_t)-1,(size_t)-1};
    }
    case 114: CC114: switch(t_.kind()){
        case sqparen_r: p_.SHIFT_(std::move(t_),129); t_=l_.lex(); goto CC129;
        default : return {(size_t)-1,(size_t)-1};
    }
    case 115: CC115: switch(t_.kind()){
        case sqparen_r: p_.SHIFT_(std::move(t_),130); t_=l_.lex(); goto CC130;
        default : return {(size_t)-1,(size_t)-1};
    }
    case 116: CC116: switch(t_.kind()){
        case ast: p_.SET_STATE(116); return {ast,20};
        case plus: p_.SET_STATE(116); return {plus,20};
        case to: p_.SET_STATE(116); return {to,20};
        default : return {(size_t)-1,(size_t)-1};
    }
    case 117: CC117: switch(t_.kind()){
        case ast: p_.SET_STATE(117); return {ast,21};
        case plus: p_.SET_STATE(117); return {plus,21};
        case to: p_.SET_STATE(117); return {to,21};
        default : return {(size_t)-1,(size_t)-1};
    }
    case 118: CC118: switch(t_.kind()){
        case basic_char_class: p_.SHIFT_(std::move(t_),68); t_=l_.lex(); goto CC68;
        case sqparen_l: p_.SHIFT_(std::move(t_),69); t_=l_.lex(); goto CC69;
        default : return {(size_t)-1,(size_t)-1};
    }
    case 119: CC119: switch(t_.kind()){
        case basic_char_class: p_.SHIFT_(std::move(t_),68); t_=l_.lex(); goto CC68;
        case sqparen_l: p_.SHIFT_(std::move(t_),69); t_=l_.lex(); goto CC69;
        default : return {(size_t)-1,(size_t)-1};
    }
    case 120: CC120: switch(t_.kind()){
        case basic_char_class: p_.SHIFT_(std::move(t_),68); t_=l_.lex(); goto CC68;
        case sqparen_l: p_.SHIFT_(std::move(t_),69); t_=l_.lex(); goto CC69;
        default : return {(size_t)-1,(size_t)-1};
    }
    case 121: CC121: switch(t_.kind()){
        case sqparen_r: p_.SET_STATE(121); return {sqparen_r,16};
        default : return {(size_t)-1,(size_t)-1};
    }
    case 122: CC122: switch(t_.kind()){
        case sqparen_r: p_.SET_STATE(122); return {sqparen_r,17};
        default : return {(size_t)-1,(size_t)-1};
    }
    case 123: CC123: switch(t_.kind()){
        case sqparen_r: p_.SHIFT_(std::move(t_),134); t_=l_.lex(); goto CC134;
        default : return {(size_t)-1,(size_t)-1};
    }
    case 124: CC124: switch(t_.kind()){
        case character: p_.SHIFT_(std::move(t_),31); t_=l_.lex(); goto CC31;
        case sqparen_r: p_.SHIFT_(std::move(t_),135); t_=l_.lex(); goto CC135;
        default : return {(size_t)-1,(size_t)-1};
    }
    case 125: CC125: switch(t_.kind()){
        case amount: p_.SET_STATE(125); return {amount,19};
        case character: p_.SET_STATE(125); return {character,19};
        case meta_char: p_.SET_STATE(125); return {meta_char,19};
        case basic_char_class: p_.SET_STATE(125); return {basic_char_class,19};
        case paren_l: p_.SET_STATE(125); return {paren_l,19};
        case paren_r: p_.SET_STATE(125); return {paren_r,19};
        case sqparen_l: p_.SET_STATE(125); return {sqparen_l,19};
        case ast: p_.SET_STATE(125); return {ast,19};
        case plus: p_.SET_STATE(125); return {plus,19};
        case qmark: p_.SET_STATE(125); return {qmark,19};
        case vbar: p_.SET_STATE(125); return {vbar,19};
        case hat: p_.SET_STATE(125); return {hat,19};
        case esc_N: p_.SET_STATE(125); return {esc_N,19};
        default : return {(size_t)-1,(size_t)-1};
    }
    case 126: CC126: switch(t_.kind()){
        case amount: p_.SET_STATE(126); return {amount,18};
        case character: p_.SET_STATE(126); return {character,18};
        case meta_char: p_.SET_STATE(126); return {meta_char,18};
        case basic_char_class: p_.SET_STATE(126); return {basic_char_class,18};
        case paren_l: p_.SET_STATE(126); return {paren_l,18};
        case paren_r: p_.SET_STATE(126); return {paren_r,18};
        case sqparen_l: p_.SET_STATE(126); return {sqparen_l,18};
        case ast: p_.SET_STATE(126); return {ast,18};
        case plus: p_.SET_STATE(126); return {plus,18};
        case qmark: p_.SET_STATE(126); return {qmark,18};
        case vbar: p_.SET_STATE(126); return {vbar,18};
        case hat: p_.SET_STATE(126); return {hat,18};
        case esc_N: p_.SET_STATE(126); return {esc_N,18};
        default : return {(size_t)-1,(size_t)-1};
    }
    case 127: CC127: switch(t_.kind()){
        case amount: p_.SET_STATE(127); return {amount,22};
        case character: p_.SET_STATE(127); return {character,22};
        case meta_char: p_.SET_STATE(127); return {meta_char,22};
        case basic_char_class: p_.SET_STATE(127); return {basic_char_class,22};
        case paren_l: p_.SET_STATE(127); return {paren_l,22};
        case paren_r: p_.SET_STATE(127); return {paren_r,22};
        case sqparen_l: p_.SET_STATE(127); return {sqparen_l,22};
        case ast: p_.SET_STATE(127); return {ast,22};
        case plus: p_.SET_STATE(127); return {plus,22};
        case qmark: p_.SET_STATE(127); return {qmark,22};
        case vbar: p_.SET_STATE(127); return {vbar,22};
        case hat: p_.SET_STATE(127); return {hat,22};
        case esc_N: p_.SET_STATE(127); return {esc_N,22};
        default : return {(size_t)-1,(size_t)-1};
    }
    case 128: CC128: switch(t_.kind()){
        case ast: p_.SET_STATE(128); return {ast,19};
        case plus: p_.SET_STATE(128); return {plus,19};
        case to: p_.SET_STATE(128); return {to,19};
        default : return {(size_t)-1,(size_t)-1};
    }
    case 129: CC129: switch(t_.kind()){
        case ast: p_.SET_STATE(129); return {ast,18};
        case plus: p_.SET_STATE(129); return {plus,18};
        case to: p_.SET_STATE(129); return {to,18};
        default : return {(size_t)-1,(size_t)-1};
    }
    case 130: CC130: switch(t_.kind()){
        case ast: p_.SET_STATE(130); return {ast,22};
        case plus: p_.SET_STATE(130); return {plus,22};
        case to: p_.SET_STATE(130); return {to,22};
        default : return {(size_t)-1,(size_t)-1};
    }
    case 131: CC131: switch(t_.kind()){
        case sqparen_r: p_.SHIFT_(std::move(t_),136); t_=l_.lex(); goto CC136;
        default : return {(size_t)-1,(size_t)-1};
    }
    case 132: CC132: switch(t_.kind()){
        case sqparen_r: p_.SHIFT_(std::move(t_),137); t_=l_.lex(); goto CC137;
        default : return {(size_t)-1,(size_t)-1};
    }
    case 133: CC133: switch(t_.kind()){
        case sqparen_r: p_.SHIFT_(std::move(t_),138); t_=l_.lex(); goto CC138;
        default : return {(size_t)-1,(size_t)-1};
    }
    case 134: CC134: switch(t_.kind()){
        case sqparen_r: p_.SET_STATE(134); return {sqparen_r,20};
        default : return {(size_t)-1,(size_t)-1};
    }
    case 135: CC135: switch(t_.kind()){
        case sqparen_r: p_.SET_STATE(135); return {sqparen_r,21};
        default : return {(size_t)-1,(size_t)-1};
    }
    case 136: CC136: switch(t_.kind()){
        case sqparen_r: p_.SET_STATE(136); return {sqparen_r,19};
        default : return {(size_t)-1,(size_t)-1};
    }
    case 137: CC137: switch(t_.kind()){
        case sqparen_r: p_.SET_STATE(137); return {sqparen_r,18};
        default : return {(size_t)-1,(size_t)-1};
    }
    case 138: CC138: switch(t_.kind()){
        case sqparen_r: p_.SET_STATE(138); return {sqparen_r,22};
        default : return {(size_t)-1,(size_t)-1};
    }
    default: return {(size_t)-1,(size_t)-1};
    } // switch(p_.state())
} // yuki::pg::lr1_action_return_type Regex_Parser_Tables::Action_Table::operator()(yuki::pg::AbsLR1Parser<Regex_Parser_TS>& p_,Regex_Lexer& l_)

constinit Regex_Parser_Tables::Goto_Table Regex_Parser_Tables::goto_table = {
    {0,0,1},{0,1,2},
    {1,0,10},{1,1,2},
    {6,0,16},{6,1,17},
    {7,1,28},{7,2,29},{7,3,30},
    {10,0,10},{10,1,2},
    {15,0,35},{15,1,2},
    {16,0,36},{16,1,17},
    {21,0,43},{21,1,17},
    {22,1,47},{22,2,48},{22,3,49},
    {23,0,51},{23,1,17},
    {24,0,52},{24,1,17},
    {25,0,53},{25,1,17},
    {30,2,58},
    {33,1,61},{33,2,62},{33,3,63},
    {34,1,65},{34,2,66},{34,3,67},
    {35,0,10},{35,1,2},
    {36,0,36},{36,1,17},
    {42,0,70},{42,1,17},
    {43,0,36},{43,1,17},
    {44,0,72},{44,1,17},
    {45,0,73},{45,1,17},
    {46,0,74},{46,1,17},
    {49,2,58},
    {50,1,80},{50,2,66},{50,3,81},
    {51,0,36},{51,1,17},
    {52,0,36},{52,1,17},
    {53,0,36},{53,1,17},
    {54,1,85},
    {55,1,86},
    {56,1,87},
    {63,2,58},
    {64,1,94},{64,2,66},{64,3,95},
    {67,2,58},
    {69,1,98},{69,2,99},{69,3,100},
    {70,0,36},{70,1,17},
    {72,0,36},{72,1,17},
    {73,0,36},{73,1,17},
    {74,0,36},{74,1,17},
    {75,1,105},
    {76,1,106},
    {77,1,107},
    {81,2,58},
    {89,1,113},
    {90,1,114},
    {91,1,115},
    {95,2,58},
    {100,2,58},
    {101,1,123},{101,2,66},{101,3,124},
    {118,1,131},
    {119,1,132},
    {120,1,133},
    {124,2,58},
}; // constinit Regex_Parser_Tables::Goto_Table Regex_Parser_Tables::goto_table

int Regex_Parser::parse(Regex_Lexer& l_){
    reset();
    stack_.reserve(128);
    Action_Table action_table(l_);

    while(true){
        yuki::pg::lr1_action_return_type art_ = action_table(*this,l_);
        switch(art_.rule){
            case 11:{ // Regex -> Char_Class
                assert(stack_.size()>=1);
                const size_t start_ = stack_.size()-1;
                yuki::IntegralCIs_OV<char32_t>& token0_ = stack_[start_+0].token.get<2>();
                Token_t token_target_complete_(yuki::pg::in_place_kind<Token_Kind::Regex>,{stack_[start_].token.location_range().begin,stack_[start_+0].token.location_range().end},ff.make_fsm(branch,std::move(token0_)));
                FSM& token_target_ = token_target_complete_.get<1>();

                {
                }

                stack_.pop_back(1);
                state_ = goto_table(stack_.empty() ? 0 : stack_.back().state,Token_Kind::Regex);
                stack_.emplace_back(std::move(token_target_complete_),state_);
                YUKI_PG_DBGO("REDUCE Regex -> Char_Class\n");
                break;
            } // case 11 //Regex -> Char_Class
            case 12:{ // Regex -> character
                assert(stack_.size()>=1);
                const size_t start_ = stack_.size()-1;
                char32_t& token0_ = stack_[start_+0].token.get<5>();
                Token_t token_target_complete_(yuki::pg::in_place_kind<Token_Kind::Regex>,{stack_[start_].token.location_range().begin,stack_[start_+0].token.location_range().end},ff.make_fsm(branch,yuki::CInterval<char32_t>{token0_,token0_}));
                FSM& token_target_ = token_target_complete_.get<1>();

                {
                }

                stack_.pop_back(1);
                state_ = goto_table(stack_.empty() ? 0 : stack_.back().state,Token_Kind::Regex);
                stack_.emplace_back(std::move(token_target_complete_),state_);
                YUKI_PG_DBGO("REDUCE Regex -> character\n");
                break;
            } // case 12 //Regex -> character
            case 13:{ // Regex -> meta_char
                assert(stack_.size()>=1);
                const size_t start_ = stack_.size()-1;
                int& token0_ = stack_[start_+0].token.get<6>();
                Token_t token_target_complete_(yuki::pg::in_place_kind<Token_Kind::Regex>,{stack_[start_].token.location_range().begin,stack_[start_+0].token.location_range().end},ff.make_fsm(branch,token0_));
                FSM& token_target_ = token_target_complete_.get<1>();

                {
                }

                stack_.pop_back(1);
                state_ = goto_table(stack_.empty() ? 0 : stack_.back().state,Token_Kind::Regex);
                stack_.emplace_back(std::move(token_target_complete_),state_);
                YUKI_PG_DBGO("REDUCE Regex -> meta_char\n");
                break;
            } // case 13 //Regex -> meta_char
            case 14:{ // Regex -> "^"
                assert(stack_.size()>=1);
                const size_t start_ = stack_.size()-1;
                Token_t token_target_complete_(yuki::pg::in_place_kind<Token_Kind::Regex>,{stack_[start_].token.location_range().begin,stack_[start_+0].token.location_range().end},ff.make_fsm(branch,MetaChar::BOL));
                FSM& token_target_ = token_target_complete_.get<1>();

                {
                }

                stack_.pop_back(1);
                state_ = goto_table(stack_.empty() ? 0 : stack_.back().state,Token_Kind::Regex);
                stack_.emplace_back(std::move(token_target_complete_),state_);
                YUKI_PG_DBGO("REDUCE Regex -> \"^\"\n");
                break;
            } // case 14 //Regex -> "^"
            case 15:{ // Regex -> esc_N
                assert(stack_.size()>=1);
                const size_t start_ = stack_.size()-1;
                Token_t token_target_complete_(yuki::pg::in_place_kind<Token_Kind::Regex>,{stack_[start_].token.location_range().begin,stack_[start_+0].token.location_range().end},ff.make_esc_N(branch));
                FSM& token_target_ = token_target_complete_.get<1>();

                {
                }

                stack_.pop_back(1);
                state_ = goto_table(stack_.empty() ? 0 : stack_.back().state,Token_Kind::Regex);
                stack_.emplace_back(std::move(token_target_complete_),state_);
                YUKI_PG_DBGO("REDUCE Regex -> esc_N\n");
                break;
            } // case 15 //Regex -> esc_N
            case 1:{ // Regex -> Regex Regex
                assert(stack_.size()>=2);
                const size_t start_ = stack_.size()-2;
                FSM& token0_ = stack_[start_+0].token.get<1>();
                FSM& token1_ = stack_[start_+1].token.get<1>();
                Token_t token_target_complete_(yuki::pg::in_place_kind<Token_Kind::Regex>,{stack_[start_].token.location_range().begin,stack_[start_+1].token.location_range().end},ff.make_seq(token0_,token1_));
                FSM& token_target_ = token_target_complete_.get<1>();

                {
                }

                stack_.pop_back(2);
                state_ = goto_table(stack_.empty() ? 0 : stack_.back().state,Token_Kind::Regex);
                stack_.emplace_back(std::move(token_target_complete_),state_);
                YUKI_PG_DBGO("REDUCE Regex -> Regex Regex\n");
                break;
            } // case 1 //Regex -> Regex Regex
            case 4:{ // Regex -> Regex "*"
                assert(stack_.size()>=2);
                const size_t start_ = stack_.size()-2;
                FSM& token0_ = stack_[start_+0].token.get<1>();
                Token_t token_target_complete_(yuki::pg::in_place_kind<Token_Kind::Regex>,{stack_[start_].token.location_range().begin,stack_[start_+1].token.location_range().end},ff.make_ast(branch,token0_));
                FSM& token_target_ = token_target_complete_.get<1>();

                {
                }

                stack_.pop_back(2);
                state_ = goto_table(stack_.empty() ? 0 : stack_.back().state,Token_Kind::Regex);
                stack_.emplace_back(std::move(token_target_complete_),state_);
                YUKI_PG_DBGO("REDUCE Regex -> Regex \"*\"\n");
                break;
            } // case 4 //Regex -> Regex "*"
            case 5:{ // Regex -> Regex "+"
                assert(stack_.size()>=2);
                const size_t start_ = stack_.size()-2;
                FSM& token0_ = stack_[start_+0].token.get<1>();
                Token_t token_target_complete_(yuki::pg::in_place_kind<Token_Kind::Regex>,{stack_[start_].token.location_range().begin,stack_[start_+1].token.location_range().end},ff.make_plus(branch,token0_));
                FSM& token_target_ = token_target_complete_.get<1>();

                {
                }

                stack_.pop_back(2);
                state_ = goto_table(stack_.empty() ? 0 : stack_.back().state,Token_Kind::Regex);
                stack_.emplace_back(std::move(token_target_complete_),state_);
                YUKI_PG_DBGO("REDUCE Regex -> Regex \"+\"\n");
                break;
            } // case 5 //Regex -> Regex "+"
            case 6:{ // Regex -> Regex "?"
                assert(stack_.size()>=2);
                const size_t start_ = stack_.size()-2;
                FSM& token0_ = stack_[start_+0].token.get<1>();
                Token_t token_target_complete_(yuki::pg::in_place_kind<Token_Kind::Regex>,{stack_[start_].token.location_range().begin,stack_[start_+1].token.location_range().end},ff.make_qmark(branch,token0_));
                FSM& token_target_ = token_target_complete_.get<1>();

                {
                }

                stack_.pop_back(2);
                state_ = goto_table(stack_.empty() ? 0 : stack_.back().state,Token_Kind::Regex);
                stack_.emplace_back(std::move(token_target_complete_),state_);
                YUKI_PG_DBGO("REDUCE Regex -> Regex \"?\"\n");
                break;
            } // case 6 //Regex -> Regex "?"
            case 7:{ // Regex -> Regex amount
                assert(stack_.size()>=2);
                const size_t start_ = stack_.size()-2;
                FSM& token0_ = stack_[start_+0].token.get<1>();
                Amount& token1_ = stack_[start_+1].token.get<4>();
                Token_t token_target_complete_(yuki::pg::in_place_kind<Token_Kind::Regex>,{stack_[start_].token.location_range().begin,stack_[start_+1].token.location_range().end},ff.make_amount(branch,token0_,token1_));
                FSM& token_target_ = token_target_complete_.get<1>();

                {
                }

                stack_.pop_back(2);
                state_ = goto_table(stack_.empty() ? 0 : stack_.back().state,Token_Kind::Regex);
                stack_.emplace_back(std::move(token_target_complete_),state_);
                YUKI_PG_DBGO("REDUCE Regex -> Regex amount\n");
                break;
            } // case 7 //Regex -> Regex amount
            case 2:{ // Regex -> Regex "|" Regex
                assert(stack_.size()>=3);
                const size_t start_ = stack_.size()-3;
                FSM& token0_ = stack_[start_+0].token.get<1>();
                FSM& token2_ = stack_[start_+2].token.get<1>();
                Token_t token_target_complete_(yuki::pg::in_place_kind<Token_Kind::Regex>,{stack_[start_].token.location_range().begin,stack_[start_+2].token.location_range().end},ff.make_alt(branch,token0_,token2_));
                FSM& token_target_ = token_target_complete_.get<1>();

                {
                }

                stack_.pop_back(3);
                state_ = goto_table(stack_.empty() ? 0 : stack_.back().state,Token_Kind::Regex);
                stack_.emplace_back(std::move(token_target_complete_),state_);
                YUKI_PG_DBGO("REDUCE Regex -> Regex \"|\" Regex\n");
                break;
            } // case 2 //Regex -> Regex "|" Regex
            case 3:{ // Regex -> "(" Regex ")"
                assert(stack_.size()>=3);
                const size_t start_ = stack_.size()-3;
                FSM& token1_ = stack_[start_+1].token.get<1>();
                Token_t token_target_complete_(yuki::pg::in_place_kind<Token_Kind::Regex>,{stack_[start_].token.location_range().begin,stack_[start_+2].token.location_range().end},token1_);
                FSM& token_target_ = token_target_complete_.get<1>();

                {
                }

                stack_.pop_back(3);
                state_ = goto_table(stack_.empty() ? 0 : stack_.back().state,Token_Kind::Regex);
                stack_.emplace_back(std::move(token_target_complete_),state_);
                YUKI_PG_DBGO("REDUCE Regex -> \"(\" Regex \")\"\n");
                break;
            } // case 3 //Regex -> "(" Regex ")"
            case 8:{ // Regex -> "(" "?=" Regex ")"
                assert(stack_.size()>=4);
                const size_t start_ = stack_.size()-4;
                FSM& token2_ = stack_[start_+2].token.get<1>();
                Token_t token_target_complete_(yuki::pg::in_place_kind<Token_Kind::Regex>,{stack_[start_].token.location_range().begin,stack_[start_+3].token.location_range().end},token2_.make_head());
                FSM& token_target_ = token_target_complete_.get<1>();

                {
            if(!heads_.empty() && heads_.back()==branch){
                fprintf(stderr,"Error: Multiple lookaheads in branch %zu!\n",branch);
                ++errors;
            }else
                heads_.emplace_back(branch);
                }

                stack_.pop_back(4);
                state_ = goto_table(stack_.empty() ? 0 : stack_.back().state,Token_Kind::Regex);
                stack_.emplace_back(std::move(token_target_complete_),state_);
                YUKI_PG_DBGO("REDUCE Regex -> \"(\" \"?=\" Regex \")\"\n");
                break;
            } // case 8 //Regex -> "(" "?=" Regex ")"
            case 9:{ // Regex -> "(" "?l:" Regex ")"
                assert(stack_.size()>=4);
                const size_t start_ = stack_.size()-4;
                FSM& token2_ = stack_[start_+2].token.get<1>();
                Token_t token_target_complete_(yuki::pg::in_place_kind<Token_Kind::Regex>,{stack_[start_].token.location_range().begin,stack_[start_+3].token.location_range().end},token2_.make_lazy());
                FSM& token_target_ = token_target_complete_.get<1>();

                {
                }

                stack_.pop_back(4);
                state_ = goto_table(stack_.empty() ? 0 : stack_.back().state,Token_Kind::Regex);
                stack_.emplace_back(std::move(token_target_complete_),state_);
                YUKI_PG_DBGO("REDUCE Regex -> \"(\" \"?l:\" Regex \")\"\n");
                break;
            } // case 9 //Regex -> "(" "?l:" Regex ")"
            case 10:{ // Regex -> "(" "?d:" Regex ")"
                assert(stack_.size()>=4);
                const size_t start_ = stack_.size()-4;
                FSM& token2_ = stack_[start_+2].token.get<1>();
                Token_t token_target_complete_(yuki::pg::in_place_kind<Token_Kind::Regex>,{stack_[start_].token.location_range().begin,stack_[start_+3].token.location_range().end},token2_.make_dlazy());
                FSM& token_target_ = token_target_complete_.get<1>();

                {
                }

                stack_.pop_back(4);
                state_ = goto_table(stack_.empty() ? 0 : stack_.back().state,Token_Kind::Regex);
                stack_.emplace_back(std::move(token_target_complete_),state_);
                YUKI_PG_DBGO("REDUCE Regex -> \"(\" \"?d:\" Regex \")\"\n");
                break;
            } // case 10 //Regex -> "(" "?d:" Regex ")"
            case 23:{ // Char_Class -> basic_char_class
                assert(stack_.size()>=1);
                const size_t start_ = stack_.size()-1;
                yuki::IntegralCIs_OV<char32_t>& token0_ = stack_[start_+0].token.get<2>();
                Token_t token_target_complete_(yuki::pg::in_place_kind<Token_Kind::Char_Class>,{stack_[start_].token.location_range().begin,stack_[start_+0].token.location_range().end},std::move(token0_));
                yuki::IntegralCIs_OV<char32_t>& token_target_ = token_target_complete_.get<2>();

                {
                }

                stack_.pop_back(1);
                state_ = goto_table(stack_.empty() ? 0 : stack_.back().state,Token_Kind::Char_Class);
                stack_.emplace_back(std::move(token_target_complete_),state_);
                YUKI_PG_DBGO("REDUCE Char_Class -> basic_char_class\n");
                break;
            } // case 23 //Char_Class -> basic_char_class
            case 16:{ // Char_Class -> "[" Char_Interval "]"
                assert(stack_.size()>=3);
                const size_t start_ = stack_.size()-3;
                yuki::CInterval<char32_t>& token1_ = stack_[start_+1].token.get<3>();
                Token_t token_target_complete_(yuki::pg::in_place_kind<Token_Kind::Char_Class>,{stack_[start_].token.location_range().begin,stack_[start_+2].token.location_range().end},token1_);
                yuki::IntegralCIs_OV<char32_t>& token_target_ = token_target_complete_.get<2>();

                {
                }

                stack_.pop_back(3);
                state_ = goto_table(stack_.empty() ? 0 : stack_.back().state,Token_Kind::Char_Class);
                stack_.emplace_back(std::move(token_target_complete_),state_);
                YUKI_PG_DBGO("REDUCE Char_Class -> \"[\" Char_Interval \"]\"\n");
                break;
            } // case 16 //Char_Class -> "[" Char_Interval "]"
            case 17:{ // Char_Class -> "[" Char_Intervals "]"
                assert(stack_.size()>=3);
                const size_t start_ = stack_.size()-3;
                yuki::IntegralCIs_OV<char32_t>& token1_ = stack_[start_+1].token.get<2>();
                Token_t token_target_complete_(yuki::pg::in_place_kind<Token_Kind::Char_Class>,{stack_[start_].token.location_range().begin,stack_[start_+2].token.location_range().end},std::move(token1_));
                yuki::IntegralCIs_OV<char32_t>& token_target_ = token_target_complete_.get<2>();

                {
                }

                stack_.pop_back(3);
                state_ = goto_table(stack_.empty() ? 0 : stack_.back().state,Token_Kind::Char_Class);
                stack_.emplace_back(std::move(token_target_complete_),state_);
                YUKI_PG_DBGO("REDUCE Char_Class -> \"[\" Char_Intervals \"]\"\n");
                break;
            } // case 17 //Char_Class -> "[" Char_Intervals "]"
            case 20:{ // Char_Class -> "[" "^" Char_Class "]"
                assert(stack_.size()>=4);
                const size_t start_ = stack_.size()-4;
                yuki::IntegralCIs_OV<char32_t>& token2_ = stack_[start_+2].token.get<2>();
                Token_t token_target_complete_(yuki::pg::in_place_kind<Token_Kind::Char_Class>,{stack_[start_].token.location_range().begin,stack_[start_+3].token.location_range().end},yuki::negate<{U'\0',yuki::UNICODE_MAX_32}>(token2_));
                yuki::IntegralCIs_OV<char32_t>& token_target_ = token_target_complete_.get<2>();

                {
                }

                stack_.pop_back(4);
                state_ = goto_table(stack_.empty() ? 0 : stack_.back().state,Token_Kind::Char_Class);
                stack_.emplace_back(std::move(token_target_complete_),state_);
                YUKI_PG_DBGO("REDUCE Char_Class -> \"[\" \"^\" Char_Class \"]\"\n");
                break;
            } // case 20 //Char_Class -> "[" "^" Char_Class "]"
            case 21:{ // Char_Class -> "[" "^" Char_Intervals "]"
                assert(stack_.size()>=4);
                const size_t start_ = stack_.size()-4;
                yuki::IntegralCIs_OV<char32_t>& token2_ = stack_[start_+2].token.get<2>();
                Token_t token_target_complete_(yuki::pg::in_place_kind<Token_Kind::Char_Class>,{stack_[start_].token.location_range().begin,stack_[start_+3].token.location_range().end},yuki::negate<{U'\0',yuki::UNICODE_MAX_32}>(token2_));
                yuki::IntegralCIs_OV<char32_t>& token_target_ = token_target_complete_.get<2>();

                {
                }

                stack_.pop_back(4);
                state_ = goto_table(stack_.empty() ? 0 : stack_.back().state,Token_Kind::Char_Class);
                stack_.emplace_back(std::move(token_target_complete_),state_);
                YUKI_PG_DBGO("REDUCE Char_Class -> \"[\" \"^\" Char_Intervals \"]\"\n");
                break;
            } // case 21 //Char_Class -> "[" "^" Char_Intervals "]"
            case 18:{ // Char_Class -> "[" Char_Class "+" Char_Class "]"
                assert(stack_.size()>=5);
                const size_t start_ = stack_.size()-5;
                yuki::IntegralCIs_OV<char32_t>& token1_ = stack_[start_+1].token.get<2>();
                yuki::IntegralCIs_OV<char32_t>& token3_ = stack_[start_+3].token.get<2>();
                Token_t token_target_complete_(yuki::pg::in_place_kind<Token_Kind::Char_Class>,{stack_[start_].token.location_range().begin,stack_[start_+4].token.location_range().end},token1_+token3_);
                yuki::IntegralCIs_OV<char32_t>& token_target_ = token_target_complete_.get<2>();

                {
                }

                stack_.pop_back(5);
                state_ = goto_table(stack_.empty() ? 0 : stack_.back().state,Token_Kind::Char_Class);
                stack_.emplace_back(std::move(token_target_complete_),state_);
                YUKI_PG_DBGO("REDUCE Char_Class -> \"[\" Char_Class \"+\" Char_Class \"]\"\n");
                break;
            } // case 18 //Char_Class -> "[" Char_Class "+" Char_Class "]"
            case 19:{ // Char_Class -> "[" Char_Class "*" Char_Class "]"
                assert(stack_.size()>=5);
                const size_t start_ = stack_.size()-5;
                yuki::IntegralCIs_OV<char32_t>& token1_ = stack_[start_+1].token.get<2>();
                yuki::IntegralCIs_OV<char32_t>& token3_ = stack_[start_+3].token.get<2>();
                Token_t token_target_complete_(yuki::pg::in_place_kind<Token_Kind::Char_Class>,{stack_[start_].token.location_range().begin,stack_[start_+4].token.location_range().end},token1_*token3_);
                yuki::IntegralCIs_OV<char32_t>& token_target_ = token_target_complete_.get<2>();

                {
                }

                stack_.pop_back(5);
                state_ = goto_table(stack_.empty() ? 0 : stack_.back().state,Token_Kind::Char_Class);
                stack_.emplace_back(std::move(token_target_complete_),state_);
                YUKI_PG_DBGO("REDUCE Char_Class -> \"[\" Char_Class \"*\" Char_Class \"]\"\n");
                break;
            } // case 19 //Char_Class -> "[" Char_Class "*" Char_Class "]"
            case 22:{ // Char_Class -> "[" Char_Class "-" Char_Class "]"
                assert(stack_.size()>=5);
                const size_t start_ = stack_.size()-5;
                yuki::IntegralCIs_OV<char32_t>& token1_ = stack_[start_+1].token.get<2>();
                yuki::IntegralCIs_OV<char32_t>& token3_ = stack_[start_+3].token.get<2>();
                Token_t token_target_complete_(yuki::pg::in_place_kind<Token_Kind::Char_Class>,{stack_[start_].token.location_range().begin,stack_[start_+4].token.location_range().end},token1_-token3_);
                yuki::IntegralCIs_OV<char32_t>& token_target_ = token_target_complete_.get<2>();

                {
                }

                stack_.pop_back(5);
                state_ = goto_table(stack_.empty() ? 0 : stack_.back().state,Token_Kind::Char_Class);
                stack_.emplace_back(std::move(token_target_complete_),state_);
                YUKI_PG_DBGO("REDUCE Char_Class -> \"[\" Char_Class \"-\" Char_Class \"]\"\n");
                break;
            } // case 22 //Char_Class -> "[" Char_Class "-" Char_Class "]"
            case 27:{ // Char_Interval -> character
                assert(stack_.size()>=1);
                const size_t start_ = stack_.size()-1;
                char32_t& token0_ = stack_[start_+0].token.get<5>();
                Token_t token_target_complete_(yuki::pg::in_place_kind<Token_Kind::Char_Interval>,{stack_[start_].token.location_range().begin,stack_[start_+0].token.location_range().end},token0_,token0_);
                yuki::CInterval<char32_t>& token_target_ = token_target_complete_.get<3>();

                {
                }

                stack_.pop_back(1);
                state_ = goto_table(stack_.empty() ? 0 : stack_.back().state,Token_Kind::Char_Interval);
                stack_.emplace_back(std::move(token_target_complete_),state_);
                YUKI_PG_DBGO("REDUCE Char_Interval -> character\n");
                break;
            } // case 27 //Char_Interval -> character
            case 26:{ // Char_Interval -> character "-" character
                assert(stack_.size()>=3);
                const size_t start_ = stack_.size()-3;
                char32_t& token0_ = stack_[start_+0].token.get<5>();
                char32_t& token2_ = stack_[start_+2].token.get<5>();
                Token_t token_target_complete_(yuki::pg::in_place_kind<Token_Kind::Char_Interval>,{stack_[start_].token.location_range().begin,stack_[start_+2].token.location_range().end},token0_,token2_);
                yuki::CInterval<char32_t>& token_target_ = token_target_complete_.get<3>();

                {
                }

                stack_.pop_back(3);
                state_ = goto_table(stack_.empty() ? 0 : stack_.back().state,Token_Kind::Char_Interval);
                stack_.emplace_back(std::move(token_target_complete_),state_);
                YUKI_PG_DBGO("REDUCE Char_Interval -> character \"-\" character\n");
                break;
            } // case 26 //Char_Interval -> character "-" character
            case 25:{ // Char_Intervals -> Char_Interval
                assert(stack_.size()>=1);
                const size_t start_ = stack_.size()-1;
                yuki::CInterval<char32_t>& token0_ = stack_[start_+0].token.get<3>();
                Token_t token_target_complete_(yuki::pg::in_place_kind<Token_Kind::Char_Intervals>,{stack_[start_].token.location_range().begin,stack_[start_+0].token.location_range().end},token0_);
                yuki::IntegralCIs_OV<char32_t>& token_target_ = token_target_complete_.get<2>();

                {
                }

                stack_.pop_back(1);
                state_ = goto_table(stack_.empty() ? 0 : stack_.back().state,Token_Kind::Char_Intervals);
                stack_.emplace_back(std::move(token_target_complete_),state_);
                YUKI_PG_DBGO("REDUCE Char_Intervals -> Char_Interval\n");
                break;
            } // case 25 //Char_Intervals -> Char_Interval
            case 24:{ // Char_Intervals -> Char_Intervals Char_Interval
                assert(stack_.size()>=2);
                const size_t start_ = stack_.size()-2;
                yuki::IntegralCIs_OV<char32_t>& token0_ = stack_[start_+0].token.get<2>();
                yuki::CInterval<char32_t>& token1_ = stack_[start_+1].token.get<3>();
                Token_t token_target_complete_(yuki::pg::in_place_kind<Token_Kind::Char_Intervals>,{stack_[start_].token.location_range().begin,stack_[start_+1].token.location_range().end},std::move((token0_.insert(token1_),token0_)));
                yuki::IntegralCIs_OV<char32_t>& token_target_ = token_target_complete_.get<2>();

                {
                }

                stack_.pop_back(2);
                state_ = goto_table(stack_.empty() ? 0 : stack_.back().state,Token_Kind::Char_Intervals);
                stack_.emplace_back(std::move(token_target_complete_),state_);
                YUKI_PG_DBGO("REDUCE Char_Intervals -> Char_Intervals Char_Interval\n");
                break;
            } // case 24 //Char_Intervals -> Char_Intervals Char_Interval
            case 0:{ // Goal_ -> Regex
                assert(stack_.size()>=1);
                const size_t start_ = stack_.size()-1;
                FSM& token0_ = stack_[start_+0].token.get<1>();
                {
            FSM fsm = token0_;
            fsm.make_accept();
            if(fsm.size>max_branch_size_)
                max_branch_size_ = fsm.size;
            if(fsm.accept->number > max_branch_number_)
                max_branch_number_ = fsm.accept->number;
            fsms_.emplace_back(fsm);
            ++branch;
            ff.reset_number();
                }

                stack_.pop_back(1);
                return 0;
            }
            default:{
                yuki::print_error(stderr,"Syntax Error!\n");
                reset();
                yuki::print_error(stderr,"Stack Clear!\n");
                return 1;
            }
        } // switch(art_.rule)
    } // while(true)
} // int Regex_Parser::parse(Regex_Lexer&)
} // namespace yuki::lex


