#pragma once
#include<initializer_list>

namespace yuki::lex{
constexpr unsigned make_meta_flags(std::initializer_list<bool> il){
    unsigned f=0;
    for(const bool b : il){
        f<<=1;
        if(b) f|=1U;
    }
    return f;
}
}