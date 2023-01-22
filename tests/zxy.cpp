#define YUKI_LEX_DBG
#define YUKI_LEX_DBG_FP stderr
#include"../include/yuki/lex/Input.hpp"
#include"../include/yuki/lex/Lexer.hpp"

using namespace yuki::lex;

// zx*(?=xy*)
void zxy(Lexer<Input>& l) noexcept{
    using namespace yuki::literals;
    yuki::U8Char c;
    decltype(l.in.get_pos()) pos_head,pos_take=l.in.get_pos();

    static constexpr size_t HEAD_MAP[1] = {0};

  S0:
    c=l.FSM_CHAR();
    if(c==0x7A) goto S1;
    return l.FSM_HALT(pos_take);

  S1:
    pos_head=l.in.get_pos();
    c=l.FSM_CHAR();
    if(c==0x78) goto S2;
    return l.FSM_HALT(pos_take);

  S2:
    l.FSM_HEAD_POST(HEAD_MAP[0],pos_head);
    pos_head=l.in.get_pos();
    pos_take=l.FSM_TAIL(0,HEAD_MAP[0]);
    c=l.FSM_CHAR();
    if(c==0x78) goto S2;
    if(c==0x79) goto S3;
    return l.FSM_HALT(pos_take);

  S3:
    pos_take=l.FSM_TAIL(0,HEAD_MAP[0]);
    c=l.FSM_CHAR();
    if(c==0x79) goto S3;
    return l.FSM_HALT(pos_take);
}

int main(){
    //FILE* f = fopen("zxy.txt","r");
    static constexpr const char text[] = "zxxxyyy";
    Lexer<Input> lexer(text);
    lexer.reserve_heads(8);
    lexer.fsm_code = &zxy;
    while(lexer.in.getable() && lexer.scan()!=0)
        ;
}
