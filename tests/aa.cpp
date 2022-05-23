#define YUKI_LEX_DBG
#define YUKI_LEX_DBG_FP stderr
#include"../include/yuki/lex/lexer.hpp"

// a?(?=a?)
void aa(yuki::lex::Lexer& l) noexcept{
    using namespace yuki::literals;
    yuki::U8Char c;
    yuki::lex::BufferedInput::Pos pos;

    static constexpr size_t HEAD_MAP[1] = {0};

  S0:
    pos=l.in.get_peek();
    l.FSM_HEAD_POST(HEAD_MAP[0],pos);
    l.FSM_TAKE(1,HEAD_MAP[0]);
    c=l.FSM_CHAR();
    if(c==U'a'_u8) goto S1;
    return l.FSM_HALT();
  S1:
    //l.FSM_HEAD_POST(HEAD_MAP[0],pos);
    pos=l.in.get_peek();
    l.FSM_HEAD_POST(HEAD_MAP[0],pos);
    l.FSM_TAKE(1,HEAD_MAP[0]);
    c=l.FSM_CHAR();
    if(c==U'a'_u8) goto S2;
    return l.FSM_HALT();
  S2:
    l.FSM_HEAD_POST(HEAD_MAP[0],pos);
    l.FSM_TAKE(1,HEAD_MAP[0]);
    return l.FSM_HALT();
}

int main(){
    using namespace yuki::lex;
    FILE* f = fopen("aa.txt","r");
    Lexer lexer(f);
    lexer.heads.emplace_back(0,0,0);
    lexer.fsm_code = &aa;
    while(!lexer.in.at_eof() && lexer.scan()!=0)
        ;
}