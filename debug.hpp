#pragma once

#ifdef YUKI_LEX_META_DBG
    #include<yuki/print.hpp>
    #ifndef YUKI_LEX_META_DBG_LOG
    #define YUKI_LEX_META_DBG_LOG "YUKI_LEX_META.log"
    #endif
    namespace yuki::lex{
    #ifndef YUKI_LEX_META_DBG_FP
    inline FILE* const meta_dbg_fp_=fopen(YUKI_LEX_META_DBG_LOG,"w");
    #define YUKI_LEX_META_DBG_FP yuki::lex::meta_dbg_fp_
    #endif
    }
    #define YUKI_LEX_META_DBGO(...) yuki::dbgout_base(YUKI_LEX_META_DBG_FP,"YUKI_LEX_META",__VA_ARGS__)
    #undef NDEBUG
    #define DEBUG_REFLEX YUKI_LEX_META_REFLEX
#else
    #define YUKI_LEX_META_DBGO(...)
    #define NDEBUG
    #undef DEBUG_REFLEX
#endif
