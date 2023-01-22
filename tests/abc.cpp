#define YUKI_LEX_DBG
#define YUKI_LEX_DBG_FP stderr
#include"../include/yuki/lex/Lexer.hpp"

// a(?=b|c)
void abc(yuki::lex::Lexer& l) noexcept{
    using namespace yuki::literals;
    yuki::U8Char c;
    decltype(l.in.get_pos()) pos_head,pos_take=l.in.get_pos();

  S0:
    c=l.FSM_CHAR();
    if(c=='a'_u8) goto S1;
    return l.FSM_HALT(pos_take);

  S1:
    pos_head=l.in.get_pos();
    c=l.FSM_CHAR();
    if(c=='b'_u8) {l.FSM_HEAD_POST(0,pos_head); goto S2;}
    if(c=='c'_u8) {l.FSM_HEAD_POST(0,pos_head); goto S3;}
    return l.FSM_HALT(pos_take);

  S2:
    pos_take=l.FSM_TAIL(1,0);
    return l.FSM_HALT(pos_take);

  S3:
    pos_take=l.FSM_TAIL(1,0);
    return l.FSM_HALT(pos_take);
}

int main(){
    using namespace yuki::lex;
    FILE* f = fopen("abc.txt","r");
    Lexer lexer(f);
    lexer.reserve_heads(8);
    lexer.fsm_code = &abc;
    while(lexer.in.getable() && lexer.scan()!=0)
        ;
}
