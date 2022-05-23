#pragma once
#include<yuki/lex/abslexer.hpp>
#include<yuki/lex/_debug.hpp>
#include<yuki/vector.hpp>

namespace yuki::lex{

struct Lexer;

typedef void fsm_code_t(Lexer& l) noexcept;

struct Lexer : AbsLexer {
    struct Option{
        bool W = false; ///< half-check for "whole words", check only left of \< and right of \> for non-word character
        typedef size_t char_col_map_t(char) noexcept;
        char_col_map_t* T = default_char_col_map<4>;
    };

    struct MetaChar{
        static constexpr yuki::U8Char NIL = 0x110000;
        static constexpr yuki::U8Char BOF = 0x110001;
        static constexpr yuki::U8Char BOL = 0x110002;
        static constexpr yuki::U8Char EOL = 0x110003;
        static constexpr yuki::U8Char BWB = 0x110004;
        static constexpr yuki::U8Char EWB = 0x110005;
        static constexpr yuki::U8Char BWE = 0x110006;
        static constexpr yuki::U8Char EWE = 0x110007;
        static constexpr yuki::U8Char NWB = 0x110008;
        static constexpr yuki::U8Char NWE = 0x110009;
    };

    Lexer(Option opt = {false,default_char_col_map<4>}) noexcept :
        option(opt)
    {}

    template<typename T>
    explicit Lexer(T&& t,Option opt = {false,default_char_col_map<4>}) noexcept :
        AbsLexer(std::forward<T>(t)),
        option(opt)
    {}

    template<typename T,typename U>
    explicit Lexer(T&& t,U&& u,Option opt = {false,default_char_col_map<4>}) noexcept :
        AbsLexer(std::forward<T>(t),std::forward<U>(u)),
        option(opt)
    {}

    void reset_got() {got_ = MetaChar::NIL;}

    void reset(){
        AbsLexer::reset();
        reset_got();
        pos_take = {0,in.lineno_p,in.colno_p};
    }

    yuki::U8Char got() const {return got_;}

    yuki::U8Char FSM_CHAR() {return got_ = in.peek_u8_cons();}

    void FSM_TAKE(size_t cap){
        cap_ = cap+1;
        pos_take = in.get_peek();
    }

    void FSM_TAKE(size_t cap,size_t head){
        assert(!heads[head].empty());
        cap_ = cap+1;
        pos_take = heads[head];
    }

    void FSM_HALT() {in.set_peek(pos_take);}

    void FSM_HEAD_POST(size_t idx, BufferedInput::Pos pos) {heads[idx] = pos;}

    bool FSM_META_BOF() {return in.at_begin_p() ? got_=MetaChar::BOF,true : false;}
    bool FSM_META_EOF() {return in.at_eof_p() ? got_=yuki::EOF_U8,true : false;}
    bool FSM_META_BOL() {return in.at_bol_p() ? got_=MetaChar::BOL,true : false;}
    bool FSM_META_EOL() {return in.at_eol_p() ? got_=MetaChar::EOL,true : false;}

    //bool FSM_META_EWE(int c0, int c1)
    //{
    //return (isword(c0) || option.W) && !isword(c1);
    //}
    //bool FSM_META_BWE(int c0, int c1)
    //{
    //return !isword(c0) && isword(c1);
    //}
    //bool FSM_META_EWB()
    //{
    //return isword(got_) && !isword(in.peek_utf8_byte(peek_));
    //}
    //bool FSM_META_BWB()
    //{
    //return !isword(got_) && (option.W || isword(in.peek_utf8_byte(peek_)));
    //}
    //bool FSM_META_NWE(int c0, int c1)
    //{
    //return isword(c0) == isword(c1);
    //}
    //bool FSM_META_NWB()
    //{
    //return isword(got_) == isword(in.peek_utf8_byte(peek_));
    //}

    virtual size_t scan() override {
        assert(fsm_code!=nullptr);
        cap_=0;
        pos_take = {0,in.lineno_p,in.colno_p};
        // heads.clear();
        fsm_code(*this);
        take_matched();
        YUKI_LEX_DBGO("Lexer::scan() : cap={} matched={} len={} \n",cap_,matched,matched.size());
        return cap_;
    }
  protected:
    yuki::U8Char got_ = MetaChar::NIL; ///< last character we looked at (to determine anchors and boundaries)
    BufferedInput::Pos pos_take;
  public:
    yuki::Vector<BufferedInput::Pos> heads;
    Option option = {false,default_char_col_map<4>};
    fsm_code_t* fsm_code = nullptr;
}; // struct Lexer
} // namespace yuki::lex
