#pragma once
#include<yuki/lex/input.hpp>
#include<cassert>
#include<string>
#include<stdexcept>

namespace yuki::lex{

struct Lexer_Error : std::runtime_error {
  private:
    std::string message;
    std::string m;
    size_t l;
    size_t c;
    int n;
  public:
    Lexer_Error(const std::string& matched_so_far,size_t lineno,size_t colno,int next) noexcept :
        std::runtime_error(""),
        m(matched_so_far),
        l(lineno),
        c(colno),
        n(next)
    {
        message.append("Lexer jammed at ").append(std::to_string(lineno)).append(":").append(std::to_string(colno)).append(" ! The matched text so far: ").append(matched_so_far).append(" . The next char is ");
        if(next==EOF)
            message.append("EOF");
        else
            message.push_back(static_cast<unsigned char>(next));
        message.push_back('\n');
    }
    virtual const char* what() const noexcept override {return message.c_str();}
};

struct AbsLexer{

    AbsLexer() noexcept = default;

    template<typename... Args,typename = std::enable_if_t<std::is_constructible_v<Input,Args&&...>>>
    explicit AbsLexer(Args&&... args) noexcept :
        cap_(0),
        matched(),
        in(std::forward<Args>(args)...)
    {}

    void reset(){
        cap_ = 0;
        matched.clear();
    }

    size_t accept() const {return cap_;}

    virtual size_t scan() = 0;
  protected:
    void take_matched(){
        matched.assign(in.peeked_so_far_ptr(),in.peeked_so_far_size());
        in.advance_to_peek();
    }
  protected:
    size_t cap_ = 0;
  public:
    std::string matched;
    BufferedInput in;
}; // struct AbsLexer

template<size_t tab_size>
constexpr size_t default_char_col_map(char c) noexcept {return c=='\t' ? tab_size : 1;}
} // namespace yuki::lex
