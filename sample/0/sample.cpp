
    #include"cconfig"
#include<cstdlib>
#include<yuki/lex/common.hpp>
#include<yuki/unicode.hpp>
#include"sample.h"

namespace xxx{
template<typename I>
size_t Blah_fsm_codes::INITIAL(I& in,typename I::Pos* const heads){
    using namespace yuki::literals;
    decltype(in.get()) c;
    size_t cap=0;
    const typename I::Pos pos_begin=in.get_pos();
    typename I::Pos pos_take=in.get_pos();
    typename I::Pos pos_head=in.get_pos();
    static constexpr size_t HEAD_MAP[3]={00,0,1};
  S0:
    c=in.get();
    if((c=='a'_u8)) goto S1;
    if((c==0x30AF_u8/*ク*/)) goto S2;
    in.set_pos(pos_take); return cap;
  S1:
    pos_head=in.get_pos();
    c=in.get();
    if((c=='b'_u8)){
        heads[HEAD_MAP[0]]=pos_head;
        goto S3;
    }
    in.set_pos(pos_take); return cap;
  S2:
    c=in.get();
    if((c==0x30A5_u8/*ゥ*/)) goto S4;
    if((c==0x30FC_u8/*ー*/)) goto S5;
    in.set_pos(pos_take); return cap;
  S3:
    cap=1; pos_take=heads[HEAD_MAP[0]];
    in.set_pos(pos_take); return cap;
  S4:
    c=in.get();
    if((c==0x3059_u8/*す*/)) goto S6;
    in.set_pos(pos_take); return cap;
  S5:
    pos_head=in.get_pos();
    c=in.get();
    if((c==0x30AB_u8/*カ*/)){
        heads[HEAD_MAP[2]]=pos_head;
        goto S7;
    }
    in.set_pos(pos_take); return cap;
  S6:
    c=in.get();
    if((c==0x307F_u8/*み*/)) goto S8;
    in.set_pos(pos_take); return cap;
  S7:
    c=in.get();
    if((c==0x30FC_u8/*ー*/)) goto S9;
    in.set_pos(pos_take); return cap;
  S8:
    cap=2; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S9:
    cap=3; pos_take=heads[HEAD_MAP[2]];
    in.set_pos(pos_take); return cap;
} // Blah_fsm_codes::INITIAL


template<typename I>
size_t Blah_fsm_codes::STATE1(I& in,typename I::Pos* const heads){
    using namespace yuki::literals;
    decltype(in.get()) c;
    size_t cap=0;
    const typename I::Pos pos_begin=in.get_pos();
    typename I::Pos pos_take=in.get_pos();
    typename I::Pos pos_head=in.get_pos();
    static constexpr size_t HEAD_MAP[3]={00,0,1};
  S0:
    c=in.get();
    if((c=='a'_u8)) goto S1;
    if((c==0x30AF_u8/*ク*/)) goto S2;
    in.set_pos(pos_take); return cap;
  S1:
    pos_head=in.get_pos();
    c=in.get();
    if((c=='b'_u8)){
        heads[HEAD_MAP[0]]=pos_head;
        goto S3;
    }
    in.set_pos(pos_take); return cap;
  S2:
    c=in.get();
    if((c==0x30A5_u8/*ゥ*/)) goto S4;
    if((c==0x30FC_u8/*ー*/)) goto S5;
    in.set_pos(pos_take); return cap;
  S3:
    cap=1; pos_take=heads[HEAD_MAP[0]];
    in.set_pos(pos_take); return cap;
  S4:
    c=in.get();
    if((c==0x3059_u8/*す*/)) goto S6;
    in.set_pos(pos_take); return cap;
  S5:
    pos_head=in.get_pos();
    c=in.get();
    if((c==0x30AB_u8/*カ*/)){
        heads[HEAD_MAP[2]]=pos_head;
        goto S7;
    }
    in.set_pos(pos_take); return cap;
  S6:
    c=in.get();
    if((c==0x307F_u8/*み*/)) goto S8;
    in.set_pos(pos_take); return cap;
  S7:
    c=in.get();
    if((c==0x30FC_u8/*ー*/)) goto S9;
    in.set_pos(pos_take); return cap;
  S8:
    cap=2; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S9:
    cap=3; pos_take=heads[HEAD_MAP[2]];
    in.set_pos(pos_take); return cap;
} // Blah_fsm_codes::STATE1


template<typename T,int i>
size_t Blah<T,i>::lex(){
while(1){
const yuki::lex::U8Input::Pos pos_begin=in.get_pos();
switch(state){
case State::INITIAL:{
    clear_heads();
            {

    u_count_prev=in.u_count;
            }
    switch(Blah_fsm_codes::INITIAL(in,heads)){
    case 0:{
        if(!in.getable()){
            YUKI_LEX_Blah_DBGO("State=INITIAL EOF\n");
            {
/*EOF0*/return 0;
            }
        }else{ // if(!in.getable())
            YUKI_LEX_Blah_DBGO("State=INITIAL DEFAULT\n");
            {

    // DEFAULTg
    return 200;
            }
        } // if(!in.getable()) else
        break;
    } // case 0
    case 1:{ // a(?=b)
        matched=in.matched(pos_begin);
        YUKI_LEX_Blah_DBGO("State=INITIAL cap=1 matched={} len={}\n",matched.substr(0,YUKI_LEX_Blah_DBG_REGEX_MAX_PRINT),matched.size());
        {
/*0*/fprintf(stderr,"%zu\n",in.u_count-u_count_prev);
        }
        in.clear_matched();
        break;
    } // case 1 // a(?=b)
    case 2:{ // クゥすみ
        matched=in.matched(pos_begin);
        YUKI_LEX_Blah_DBGO("State=INITIAL cap=2 matched={} len={}\n",matched.substr(0,YUKI_LEX_Blah_DBG_REGEX_MAX_PRINT),matched.size());
        {
/*1*/fprintf(stderr,"%zu\n",in.u_count-u_count_prev);
        }
        in.clear_matched();
        break;
    } // case 2 // クゥすみ
    case 3:{ // クー(?=カー)
        matched=in.matched(pos_begin);
        YUKI_LEX_Blah_DBGO("State=INITIAL cap=3 matched={} len={}\n",matched.substr(0,YUKI_LEX_Blah_DBG_REGEX_MAX_PRINT),matched.size());
        {
// 2
    fprintf(stderr,"%zu\n",in.u_count-u_count_prev);
        }
        in.clear_matched();
        break;
    } // case 3 // クー(?=カー)
    } // switch(Blah_fsm_codes::INITIAL(in,heads))
    break;
} // case State::INITIAL
case State::STATE1:{
    clear_heads();
            {

    u_count_prev=in.u_count;
            }
    switch(Blah_fsm_codes::STATE1(in,heads)){
    case 0:{
        if(!in.getable()){
            YUKI_LEX_Blah_DBGO("State=STATE1 EOF\n");
            {

    // EOFg
    return 100;
            }
        }else{ // if(!in.getable())
            YUKI_LEX_Blah_DBGO("State=STATE1 DEFAULT\n");
            {
/*DEFAULT1*/
    return 3;
            }
        } // if(!in.getable()) else
        break;
    } // case 0
    case 1:{ // a(?=b)
        matched=in.matched(pos_begin);
        YUKI_LEX_Blah_DBGO("State=STATE1 cap=1 matched={} len={}\n",matched.substr(0,YUKI_LEX_Blah_DBG_REGEX_MAX_PRINT),matched.size());
        {
/*3*/fprintf(stderr,"%zu\n",in.u_count-u_count_prev);
        }
        in.clear_matched();
        break;
    } // case 1 // a(?=b)
    case 2:{ // {m1}
        matched=in.matched(pos_begin);
        YUKI_LEX_Blah_DBGO("State=STATE1 cap=2 matched={} len={}\n",matched.substr(0,YUKI_LEX_Blah_DBG_REGEX_MAX_PRINT),matched.size());
        {
/*4*/fprintf(stderr,"%zu\n",in.u_count-u_count_prev);
        }
        in.clear_matched();
        break;
    } // case 2 // {m1}
    case 3:{ // クー{m0}
        matched=in.matched(pos_begin);
        YUKI_LEX_Blah_DBGO("State=STATE1 cap=3 matched={} len={}\n",matched.substr(0,YUKI_LEX_Blah_DBG_REGEX_MAX_PRINT),matched.size());
        {
// 5
    fprintf(stderr,"%zu\n",in.u_count-u_count_prev);
        }
        in.clear_matched();
        break;
    } // case 3 // クー{m0}
    } // switch(Blah_fsm_codes::STATE1(in,heads))
    break;
} // case State::STATE1
} // switch(state)
} // while(1)
} // size_t Blah::lex()
} // namespace xxx




namespace xxx{
template size_t Blah<int,0>::lex();
}

