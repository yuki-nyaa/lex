#define YUKI_LEX_DBG
#define YUKI_LEX_DBG_FP stderr
#include"../include/yuki/lex/lexer.hpp"

// zx*(?=xy*)
void zxy(yuki::lex::Lexer& l) noexcept{
    using namespace yuki::literals;
    yuki::U8Char c;
    yuki::lex::BufferedInput::Pos pos = {0,0,0};

    static constexpr size_t HEAD_MAP[1] = {0};

  S0:
    c=l.FSM_CHAR();
    if(c==0x7A_u8r) goto S1;
    return l.FSM_HALT();

  S1:
    pos = l.in.get_peek();
    c=l.FSM_CHAR();
    if(c==0x78_u8r) goto S2;
    return l.FSM_HALT();

  S2:
    l.FSM_HEAD_POST(HEAD_MAP[0],pos);
    pos = l.in.get_peek();
    l.FSM_TAKE(0,HEAD_MAP[0]);
    c=l.FSM_CHAR();
    if(c==0x78_u8r) goto S2;
    if(c==0x79_u8r) goto S3;
    return l.FSM_HALT();

  S3:
    l.FSM_TAKE(0,HEAD_MAP[0]);
    c=l.FSM_CHAR();
    if(c==0x79_u8r) goto S3;
    return l.FSM_HALT();
}

int main(){
    using namespace yuki::lex;
    FILE* f = fopen("zxy.txt","r");
    Lexer lexer(f);
    lexer.heads.emplace_back(0,0,0);
    lexer.fsm_code = &zxy;
    while(!lexer.in.at_eof() && lexer.scan()!=0)
        ;
}