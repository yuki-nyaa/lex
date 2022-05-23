#pragma once

#ifdef YUKI_LEX_DBG
#include<yuki/print.hpp>
#ifndef YUKI_LEX_DBG_LOG
#define YUKI_LEX_DBG_LOG "YUKI_LEX.log"
#endif
namespace yuki::lex{
#ifndef YUKI_LEX_DBG_FP
inline FILE* const dbg_fp_=fopen(YUKI_LEX_DBG_LOG,"w");
#define YUKI_LEX_DBG_FP yuki::lex::dbg_fp_
#endif
}
#define YUKI_LEX_DBGO(...) yuki::dbgout_base(YUKI_LEX_DBG_FP,"YUKI_LEX",__VA_ARGS__)
#define  CONSTEXPR_YUKI_LEX_DBG // Debug output would render constexpr-functions non-constexpr.
#else
#define YUKI_LEX_DBGO(...)
#define  CONSTEXPR_YUKI_LEX_DBG constexpr
#endif