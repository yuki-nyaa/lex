#pragma once

    // code h_top
#include<yuki/lex/U8Input.hpp>

#ifdef YUKI_LEX_Blah_DBG
#include<yuki/print.hpp>
#ifndef YUKI_LEX_Blah_DBG_LOG
#define YUKI_LEX_Blah_DBG_LOG "YUKI_LEX_Blah_DBG.log"
#endif
namespace xxx{
#ifndef YUKI_LEX_Blah_DBG_FP
inline FILE* const YUKI_LEX_Blah_DBG_fp_=fopen(YUKI_LEX_Blah_DBG_LOG,"w");
#define YUKI_LEX_Blah_DBG_FP xxx::YUKI_LEX_Blah_DBG_fp_
#endif
} // namespace xxx
#define YUKI_LEX_Blah_DBGO(...) yuki::dbgout_base(fp_dbg_,"YUKI_LEX_Blah_DBG",__VA_ARGS__)
#define CONSTEXPR_YUKI_LEX_Blah_DBG // Debug output would render constexpr-functions non-constexpr.
#ifndef YUKI_LEX_Blah_DBG_REGEX_MAX_PRINT
#define YUKI_LEX_Blah_DBG_REGEX_MAX_PRINT 128
#endif
#else
#define YUKI_LEX_Blah_DBGO(...)
#define CONSTEXPR_YUKI_LEX_Blah_DBG constexpr
#endif

namespace xxx{
namespace Blah_fsm_codes{
    template<typename I>
    size_t INITIAL(I&,typename I::Pos*);
    template<typename I>
    size_t STATE1(I&,typename I::Pos*);
    template<typename I>
    size_t STATE2(I&,typename I::Pos*);
} // namespace Blah_fsm_codes

template<typename T,int i>
struct Blah{
    enum struct State {INITIAL,STATE1,STATE2,} state=State::INITIAL;
    std::string_view matched;
    yuki::lex::U8Input in;
    #ifdef YUKI_LEX_Blah_DBG
    FILE* fp_dbg_=YUKI_LEX_Blah_DBG_FP;
    #endif

    Blah() noexcept=default;

    template<typename... Args>
    explicit Blah(Args&&... args) noexcept : in(std::forward<Args>(args)...) {}
  protected:
    yuki::lex::U8Input::Pos heads[2];
    void clear_heads(){
        static_assert(std::is_trivially_copyable_v<yuki::lex::U8Input::Pos>);
        memset(heads,0,sizeof(heads));
    }
  public:

    size_t u_count_prev;
  public:
    size_t lex();
}; // struct Blah
} // namespace xxx


