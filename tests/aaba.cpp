#define YUKI_LEX_DBG
#define YUKI_LEX_DBG_FP stderr
#include"../include/yuki/lex/Lexer.hpp"

// a?[ab](?=a?)
void aaba(yuki::lex::Lexer& l) noexcept{
    using namespace yuki::literals;
    yuki::U8Char c;
    decltype(l.in.get_pos()) pos_head,pos_take=l.in.get_pos();

    static constexpr size_t HEAD_MAP[1] = {0};

  S0:
    c=l.FSM_CHAR();
    if((c==U'b'_u8)) goto S1;
    if((c==U'a'_u8)) goto S2;
    return l.FSM_HALT(pos_take);
  S1:
    pos_head=l.in.get_pos();
    l.FSM_HEAD_POST(HEAD_MAP[0],pos_head);
    pos_take=l.FSM_TAIL(0,HEAD_MAP[0]);
    c=l.FSM_CHAR();
    if((c==U'a'_u8)) goto S3;
    return l.FSM_HALT(pos_take);
  S2:
    pos_head=l.in.get_pos();
    l.FSM_HEAD_POST(HEAD_MAP[0],pos_head);
    pos_take=l.FSM_TAIL(0,HEAD_MAP[0]);
    c=l.FSM_CHAR();
    if((c==U'a'_u8 || c==U'b'_u8)) goto S1;
    return l.FSM_HALT(pos_take);
  S3:
    l.FSM_HEAD_POST(HEAD_MAP[0],pos_head);
    pos_take=l.FSM_TAIL(0,HEAD_MAP[0]);
    return l.FSM_HALT(pos_take);
}

// a?[ab](?=a?)
void aaba2(yuki::lex::Lexer& l) noexcept{
    using namespace yuki::literals;
    yuki::U8Char c;
    decltype(l.in.get_pos()) pos_head,pos_take=l.in.get_pos();

    static constexpr size_t HEAD_MAP[1] = {0};

  S0:
    c=l.FSM_CHAR();
    if((c==U'b'_u8)) goto S1;
    if((c==U'a'_u8)) goto S2;
    return l.FSM_HALT(pos_take);
  S1:
    pos_head=l.in.get_pos();
    l.FSM_HEAD_POST(HEAD_MAP[0],pos_head);
    pos_take=l.FSM_TAIL(0,HEAD_MAP[0]);
    c=l.FSM_CHAR();
    if((c==U'a'_u8)) {l.FSM_HEAD_POST(HEAD_MAP[0],pos_head);goto S3;}
    return l.FSM_HALT(pos_take);
  S2:
    pos_head=l.in.get_pos();
    l.FSM_HEAD_POST(HEAD_MAP[0],pos_head);
    pos_take=l.FSM_TAIL(0,HEAD_MAP[0]);
    c=l.FSM_CHAR();
    if(c==U'a'_u8) {l.FSM_HEAD_POST(HEAD_MAP[0],pos_head);goto S1;}
    if(c==U'b'_u8) goto S1;
    return l.FSM_HALT(pos_take);
  S3:
    pos_take=l.FSM_TAIL(0,HEAD_MAP[0]);
    return l.FSM_HALT(pos_take);
}

int main(){
    using namespace yuki::lex;
    FILE* f = fopen("aaba.txt","r");
    Lexer lexer(f);
    lexer.reserve_heads(8);
    lexer.fsm_code = &aaba2;
    while(lexer.in.getable() && lexer.scan()!=0)
        ;
}
