#pragma once
#include<yuki/lex/_debug.hpp>
#include<yuki/lex/AbsLexer.hpp>

namespace yuki::lex{
constexpr unsigned make_meta_flags(std::initializer_list<bool> il){
    unsigned f=0;
    for(const bool b : il){
        f<<=1;
        if(b) f|=1U;
    }
    return f;
}

template<typename I>
struct Lexer : AbsLexer{
    Lexer() noexcept = default;

    template<typename... Args,typename = std::enable_if_t<std::is_constructible_v<I,Args&&...>>>
    explicit Lexer(Args&&... args) noexcept :
        in(std::forward<Args>(args)...)
    {}

    ~Lexer() noexcept {delete[] heads;}

    void reserve_heads(const size_t s){
        if(heads_size<s){
            delete[] heads;
            heads=new typename I::Pos[s];
            heads_size=s;
        }
    }

    auto FSM_CHAR() {return in.get();}

    [[nodiscard]]
    typename I::Pos FSM_TAKE(const size_t cap){
        cap_ = cap+1;
        return in.get_pos();
    }

    [[nodiscard]]
    typename I::Pos FSM_TAIL(const size_t cap,const size_t head){
        cap_ = cap+1;
        return heads[head];
    }

    void FSM_HALT(const typename I::Pos pos_take) {in.set_pos(pos_take);}

    void FSM_HEAD_POST(const size_t idx,const typename I::Pos pos_head) const {heads[idx]=pos_head;}

    bool FSM_META_BOL() const {return in.at_bol();}
    bool FSM_META_EOL() {return in.at_eol();}
    bool FSM_META_BOI() const {return in.at_boi();}
    bool FSM_META_EOI() {return in.at_eoi();}
    bool FSM_META_EoF() const {return in.getable();}
    bool FSM_META_WB() {return in.at_wb();}

    virtual size_t scan() override {
        assert(fsm_code);
        cap_=0;
        if constexpr(std::is_trivially_copyable_v<typename I::Pos>)
            memset(heads,0,heads_size*sizeof(typename I::Pos));
        else
            for(size_t i=0;i<heads_size;++i)
                heads[i].clear();
        const typename I::Pos pos_begin = in.get_pos();
        fsm_code(*this);
        matched = in.take(pos_begin);
        YUKI_LEX_DBGO("Lexer::scan(): cap={} matched={} len={} \n",cap_,matched,matched.size());
        return cap_;
    }
  private:
    typename I::Pos* heads=nullptr;
    size_t heads_size=0;
  public:
    typedef void fsm_code_t(Lexer&) noexcept;
    fsm_code_t* fsm_code = nullptr;
    I in;
}; // struct Lexer
} // namespace yuki::lex
