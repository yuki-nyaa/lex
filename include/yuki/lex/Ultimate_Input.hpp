#pragma once
#include<yuki/lex/Input.hpp>
#include<yuki/lex/get_u8.hpp>

namespace yuki::lex{

template<size_t RAW_BUFFER_DEFAULT_SIZE>
struct Ultimate_Input_Raw : protected BufferedInput_Base{
    // For debugging
    using BufferedInput_Base::set_source;
    //< For debugging

    using BufferedInput_Base::BufferedInput_Base;

    using BufferedInput_Base::getable;

    using BufferedInput_Base::peek;

    /// @pre `size!=0`.
    size_t read(void* const buf,const size_t size,const size_t count){
        assert(size!=0);

        size_t remaining = count;
        unsigned char* buf_uc = static_cast<unsigned char*>(buf);

        if(const size_t data_size_v=data_size(); data_size_v!=0){
            if(data_size_v>=size){
                const size_t count_max = data_size_v/size;
                const size_t count_real = count_max<count ? count_max : count;
                const size_t total = count_real*size;
                memcpy(buf_uc,br+p_br,total);
                buf_uc+=total;
                p_br+=total;
                remaining-=count_real;
                if(e_br==p_br){
                    e_br=0; p_br=0;
                    goto read_from_input;
                }
            }
            if(remaining!=0){
                const size_t remaining_in_buffer = e_br-p_br;
                const size_t complement = size-remaining_in_buffer;
                if(s_br-e_br<complement){
                    if(s_br>=size)
                        realign_buffer();
                    else
                        resize_buffer(size<RAW_BUFFER_DEFAULT_SIZE ? RAW_BUFFER_DEFAULT_SIZE : size);
                }
                if(Input::read(br+e_br,complement,1)==1){
                    memcpy(buf_uc,br+p_br,size);
                    buf_uc+=size;
                    e_br=0; p_br=0;
                    --remaining;
                    goto read_from_input;
                }else
                    return count-remaining;
            }
            return count;
        } // if(const size_t data_size_v=data_size(); data_size_v!=0)

        read_from_input:
        if(remaining!=0){
            if(no_buffer_needed())
                return (count-remaining)+Input::read(buf_uc,size,remaining);
            else{
                if(s_br<size) [[unlikely]]
                    resize_buffer(size<RAW_BUFFER_DEFAULT_SIZE ? RAW_BUFFER_DEFAULT_SIZE : size);
                while(1){
                    if(const size_t filled=Input::read(br,size,s_br/size); filled<remaining){
                        if(filled!=0){
                            const size_t total = filled*size;
                            memcpy(buf_uc,br,total);
                            buf_uc+=total;
                            remaining-=filled;
                            continue;
                        }else
                            return count-remaining;
                    }else{
                        memcpy(buf_uc,br,remaining*size);
                        if(filled!=remaining){
                            e_br = filled*size;
                            p_br = remaining*size;
                        }else{
                            e_br=0; p_br=0;
                        }
                        return count;
                    }
                }
            }
        }
        return count;
    }

    int get(){
        if(p_br<e_br)
            return static_cast<unsigned char>(br[p_br++]);

        if(no_buffer_needed())
            return Input::get();
        else{
            e_br=0; p_br=0;
            if(Input::getable()){
                if(s_br==0) [[unlikely]]
                    resize_buffer(1<RAW_BUFFER_DEFAULT_SIZE ? RAW_BUFFER_DEFAULT_SIZE : 1);
                fill_buffer();
                return static_cast<unsigned char>(br[p_br++]);
            }else
                return EOF;
        }
    }
}; // struct Ultimate_Input_Raw


struct Ultimate_Input_Poss{
    size_t u_count = 0;
    size_t byte_count = 0;
    size_t lineno = 1;
    size_t colno = 1;
    size_t colno_byte = 1;
    yuki::U8Char c_prev = yuki::EOF_U8;
    constexpr void reset_poss(){
        u_count=0;
        byte_count=0;
        lineno=1;
        colno=1;
        colno_byte=1;
        c_prev=yuki::EOF_U8;
    }
    constexpr bool at_boi() const {return lineno==1 && colno==1;}
    constexpr void advance(const yuki::U8Char c,const unsigned l){
        using namespace yuki::literals;
        assert(c!=yuki::EOF_U8);
        if(c=='\n'_u8){
            ++byte_count;
            ++lineno;
            colno=1;
            colno_byte=1;
        }else{
            byte_count+=l;
            ++colno;
            colno_byte+=l;
        }
        ++u_count;
        c_prev=c;
    }
};


template<size_t U8_BUFFER_DEFAULT_SIZE,size_t RAW_BUFFER_DEFAULT_SIZE>
struct Ultimate_Input_Tp : private With_Enc<Ultimate_Input_Raw<RAW_BUFFER_DEFAULT_SIZE>>, private Ultimate_Input_Poss{
  private:
    typedef Ultimate_Input_Raw<RAW_BUFFER_DEFAULT_SIZE> Raw_;
    typedef With_Enc<Raw_> RwE;
    char* b8 = nullptr;
    size_t s_b8 = 0;
    size_t e_b8 = 0;
    size_t p_b8 = 0;
    size_t pp_b8 = 0;
  public:
    using Ultimate_Input_Poss::u_count;
    using Ultimate_Input_Poss::byte_count;
    using Ultimate_Input_Poss::lineno;
    using Ultimate_Input_Poss::colno;
    using Ultimate_Input_Poss::colno_byte;
    using Ultimate_Input_Poss::c_prev;

    using Input::Source_Type;
    using Input::get_source_type;
    using Input::file;
    using Input::c_str;
    using Input::remaining_size;
    using Input::string_view;
    using With_Enc<Raw_>::get_encoding;
    using With_Enc<Raw_>::set_encoding;
    using With_Enc<Raw_>::get_page;

    using RwE::RwE;

    /// @note The size of the u8 buffer remains the same, but the contents become left-aligned.
    Ultimate_Input_Tp(const Ultimate_Input_Tp& other) noexcept :
        With_Enc<Raw_>(other),
        Ultimate_Input_Poss(other),
        b8(new char[other.s_b8]),
        s_b8(other.s_b8),
        e_b8(other.e_b8-other.p_b8),
        p_b8(0),
        pp_b8(other.pp_b8-other.p_b8)
    {memcpy(b8,other.b8+other.p_b8,other.e_b8-other.p_b8);}

    Ultimate_Input_Tp(Ultimate_Input_Tp&& other) noexcept :
        With_Enc<Raw_>(std::move(other)),
        Ultimate_Input_Poss(other),
        b8(other.b8),
        s_b8(other.s_b8),
        e_b8(other.e_b8),
        p_b8(other.p_b8),
        pp_b8(other.pp_b8)
    {
        other.b8 = nullptr;
        other.s_b8 = 0;
        other.e_b8 = 0;
        other.p_b8 = 0;
        other.pp_b8 = 0;
        other.reset_poss();
    }

    /// @note The u8 buffer will NOT be resized if the data in `other` fit. The copied data will become left-aligned.
    Ultimate_Input_Tp& operator=(const Ultimate_Input_Tp& other) noexcept {
        if(this!=&other){
            With_Enc<Raw_>::operator=(other);
            Ultimate_Input_Poss::operator=(other);
            const size_t other_u8_data_size = other.u8_data_size();
            if(s_b8<other_u8_data_size){
                delete[] b8;
                b8 = new char[other.s_b8];
                s_b8 = other.s_b8;
            }
            e_b8=other_u8_data_size;
            p_b8=0;
            pp_b8=other.pp_b8-other.p_b8;
            memcpy(b8,other.b8+other.p_b8,other.e_b8-other.p_b8);
        }
        return *this;
    }

    Ultimate_Input_Tp& operator=(Ultimate_Input_Tp&& other) noexcept {
        if(this!=&other){
            With_Enc<Raw_>::operator=(std::move(other));
            Ultimate_Input_Poss::operator=(other);
            b8=other.b8;
            s_b8=other.s_b8;
            e_b8=other.e_b8;
            p_b8=other.p_b8;
            pp_b8=other.pp_b8;

            other.b8 = nullptr;
            other.s_b8 = 0;
            other.e_b8 = 0;
            other.p_b8 = 0;
            other.pp_b8 = 0;
            other.reset_poss();
        }
        return *this;
    }

    ~Ultimate_Input_Tp() noexcept {delete[] b8;}

    /// @note Do not resize smaller than `e_br-p_br`!
    void resize_raw_buffer(const size_t size_new) {BufferedInput_Base::resize_buffer(size_new);}

    /// @note Do not resize smaller than `e_b8-p_b8`!
    void resize_u8_buffer(const size_t size_new){
        if(size_new!=s_b8){
            assert(size_new>=e_b8-p_b8);
            char* const b8_new = new char [size_new];
            memcpy(b8_new,b8+p_b8,e_b8-p_b8);
            b8 = b8_new;
            s_b8 = size_new;
            e_b8 -= p_b8;
            pp_b8 -= p_b8;
            p_b8 = 0;
        }
    }

    void realign_raw_buffer() {BufferedInput_Base::realign_buffer();}

    void realign_u8_buffer(){
        memmove(b8,b8+p_b8,e_b8-p_b8);
        e_b8 -= p_b8;
        pp_b8 -= p_b8;
        p_b8 = 0;
    }

    size_t fill_raw_buffer() {return BufferedInput_Base::fill_buffer();}

    void discard_u8_buffer() {e_b8=0;p_b8=0;pp_b8=0;}
    void discard_raw_buffer() {BufferedInput_Base::discard_buffer();}
    void discard_buffer() {BufferedInput_Base::discard_buffer();discard_u8_buffer();}

    size_t raw_buffer_size() const {return BufferedInput_Base::buffer_size();}
    size_t raw_data_size() const {return BufferedInput_Base::data_size();}

    size_t u8_buffer_size() const {return s_b8;}
    size_t u8_data_size() const {return e_b8-p_b8;}

    // Note: The following functions discard everything in the buffer.
  private:
    template<typename... Ts>
    void set_source_impl_(const Ts... ts){
        discard_u8_buffer();
        BufferedInput_Base::set_source(ts...);
        reset_poss();
    }
  public:
    void set_source() {set_source_impl_();}
    void set_source(FILE* const f) {set_source_impl_(f);}
    void set_source(const char* const s) {set_source_impl_(s);}
    void set_source(const char* const s,const size_t sz) {set_source_impl_(s,sz);}
    void set_source(const std::string_view sv) {set_source_impl_(sv);}

    // Unlike `set_source`s, `continue_source`s do not discard the U8 buffer and do not reset the positions. (But the buffer in `BufferedInput_Base` is still discarded.)
    void continue_source(FILE* const f) {BufferedInput_Base::set_source(f);}
    void continue_source(const char* const s) {BufferedInput_Base::set_source(s);}
    void continue_source(const char* const s,const size_t sz) {BufferedInput_Base::set_source(s,sz);}
    void continue_source(const std::string_view sv) {BufferedInput_Base::set_source(sv);}
  private:
    static constexpr size_t expand_u8_calc(const size_t size,const size_t added){
        const size_t size_pending = size<added ? size+added : 2*size;
        return size_pending<U8_BUFFER_DEFAULT_SIZE ? U8_BUFFER_DEFAULT_SIZE : size_pending;
    }

    void adjust_u8_buffer_for(const unsigned to_be_appended){
        if(e_b8+to_be_appended>s_b8){
            if(e_b8-p_b8+to_be_appended<=s_b8)
                realign_u8_buffer();
            else
                resize_u8_buffer(expand_u8_calc(s_b8,to_be_appended));
        }
    }

    template<bool P>
    yuki::U8Char get_impl(){
        if(pp_b8<e_b8){
            const yuki::U8Char c(b8+pp_b8);
            const unsigned l = c.length();
            pp_b8+=l;
            if constexpr(P)
                Ultimate_Input_Poss::advance(c,l);
            return c;
        }else{
            const yuki::U8Char c = With_Enc<Raw_>::get_u8();
            if(c==yuki::EOF_U8)
                return yuki::EOF_U8;
            const unsigned l = c.length();
            adjust_u8_buffer_for(l);
            c.write_to(b8+e_b8);
            e_b8+=l;
            pp_b8=e_b8;
            if constexpr(P)
                Ultimate_Input_Poss::advance(c,l);
            return c;
        }
    }

    yuki::U8Char get_np() {return get_impl<false>();}
  public:
    yuki::U8Char get() {return get_impl<true>();}

    bool getable() const {return pp_b8<e_b8 || BufferedInput_Base::getable();}

    yuki::U8Char peek(){
        if(pp_b8<e_b8)
            return yuki::U8Char(b8+pp_b8);
        else{
            const yuki::U8Char c = With_Enc<Raw_>::get_u8();
            if(c==yuki::EOF_U8)
                return yuki::EOF_U8;
            const unsigned l = c.length();
            adjust_u8_buffer_for(l);
            c.write_to(b8+e_b8);
            e_b8+=l;
            return c;
        }
    }

    struct Pos{
        friend Ultimate_Input_Tp;
        constexpr Pos() noexcept = default;
      private:
        size_t off=0;
        Ultimate_Input_Poss uip;
        constexpr Pos(const size_t off_p,const Ultimate_Input_Poss uip_p) noexcept :
            off(off_p),
            uip(uip_p)
        {}
    };

    Pos get_pos() const {return {pp_b8-p_b8,static_cast<const Ultimate_Input_Poss&>(*this)};}
    void set_pos(const Pos pos){
        pp_b8 = p_b8+pos.off;
        Ultimate_Input_Poss::operator=(pos.uip);
    }

    std::string_view matched(const Pos) const {return {b8+p_b8,pp_b8-p_b8};}
    void clear_matched() {p_b8=pp_b8;}

    using Ultimate_Input_Poss::reset_poss;

    bool at_bol() const {return colno==1;}
    bool at_eol(){
        using namespace yuki::literals;
        switch(peek().raw()){
            case '\r'_u8.raw():
            case '\n'_u8.raw():
            case yuki::EOF_U8.raw(): return true;
            default: return false;
        }
    }
    using Ultimate_Input_Poss::at_boi;
    bool at_eoi(){
        using namespace yuki::literals;
        switch(peek().raw()){
            case '\r'_u8.raw():{
                get_np();
                switch(peek().raw()){
                    case '\n'_u8.raw():{
                        get_np();
                        if(peek()==yuki::EOF_U8){
                            pp_b8-=2;
                            return true;
                        }else{
                            pp_b8-=2;
                            return false;
                        }
                    }
                    case yuki::EOF_U8.raw(): --pp_b8;return true;
                    default: --pp_b8;return false;
                }
            }
            case '\n'_u8.raw():{
                get_np();
                if(peek()==yuki::EOF_U8){
                    --pp_b8;
                    return true;
                }else{
                    --pp_b8;
                    return false;
                }
            }
            case yuki::EOF_U8.raw(): return true;
            default: return false;
        }
    }
    static constexpr bool isword(const yuki::U8Char u8c){
        using namespace yuki::literals;
        return (u8c>='a'_u8 && u8c<='z'_u8)
            || (u8c>='A'_u8 && u8c<='Z'_u8)
            || (u8c>='0'_u8 && u8c<='9'_u8)
            || u8c=='_'_u8;
    }
    bool at_wb() {return isword(c_prev)!=isword(peek());}
}; // struct Ultimate_Input_Tp

typedef Ultimate_Input_Tp<4096,128*1024> Ultimate_Input;
} // namespace yuki::lex
