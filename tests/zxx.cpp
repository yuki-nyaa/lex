#define YUKI_LEX_DBG
#define YUKI_LEX_DBG_FP stderr
#include"../include/yuki/lex/lexer.hpp"

// zx*?(?=x*)
void zxqx(yuki::lex::Lexer& l) noexcept{
    using namespace yuki::literals;
    yuki::U8Char c;
    yuki::lex::BufferedInput::Pos pos;

  S0:
    c=l.FSM_CHAR();
    if(c=='z'_u8) goto S1;
    return l.FSM_HALT();

  S1:
    l.FSM_TAKE(1,0);
    pos = l.in.get_peek();
    c=l.FSM_CHAR();
    if(c=='x'_u8) {l.FSM_HEAD(0,pos); goto S2;}
    return l.FSM_HALT();

  S2:
    l.FSM_TAKE(1,0);
    pos = l.in.get_peek();
    c=l.FSM_CHAR();
    if(c=='x'_u8) {l.FSM_HEAD(0,pos); goto S2;}
    return l.FSM_HALT();
}

//// zx*x*
//void zxx(yuki::lex::Lexer& l) noexcept{
//    using namespace yuki::literals;
//    yuki::U8Char c;
//    yuki::lex::BufferedInput::Pos pos;

//  S0:
//    c=l.FSM_CHAR();
//    if(c=='z'_u8) goto S1;
//    return l.FSM_HALT();

//  S1:
//    l.FSM_TAKE(1);
//    c=l.FSM_CHAR();
//    if(c=='x'_u8) goto S2;
//    return l.FSM_HALT();

//  S2:
//    l.FSM_TAKE(1);
//    c=l.FSM_CHAR();
//    if(c=='x'_u8) goto S2;
//    return l.FSM_HALT();
//}

int main(){
    using namespace yuki::lex;
    FILE* f = fopen("zxx.txt","r");
    Lexer lexer(f);
    lexer.heads.emplace_back(0,0,0);
    lexer.fsm_code = &zxqx;
    while(!lexer.in.at_eof() && lexer.scan()!=0)
        ;
}