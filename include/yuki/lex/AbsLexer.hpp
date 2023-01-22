#pragma once
#include<string>

namespace yuki::lex{
struct AbsLexer{
    void reset(){
        cap_=0;
        matched={};
    }
    size_t accept() const {return cap_;}
    virtual size_t scan() = 0;
  protected:
    size_t cap_ = 0;
  public:
    std::string_view matched;
};
}
