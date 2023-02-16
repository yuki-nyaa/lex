#pragma once
#include<yuki/unicode.hpp>
#include<yuki/lex/ByteInput.hpp>

namespace yuki::lex{

struct U8Input_Poss{
    size_t u_count = 0;
    size_t byte_count = 0;
    size_t lineno = 1;
    size_t colno = 1;
    size_t colno_byte = 1;
    yuki::U8Char c_prev = yuki::EOF_U8;
    constexpr void reset_poss(){
        u_count = 0;
        byte_count = 0;
        lineno = 1;
        colno = 1;
        colno_byte = 1;
        c_prev = yuki::EOF_U8;
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

template<size_t U8INPUT_DEFAULT_SIZE>
struct U8Input_Tp : private ByteInput_Base_With_Pos<U8Input_Poss>{
  private:
    typedef ByteInput_Base_With_Pos<U8Input_Poss> BBWP;

    using BufferedInput_Base::br;
    using BufferedInput_Base::s_br;
    using BufferedInput_Base::e_br;
    using BufferedInput_Base::p_br;
    using ByteInput_Base::pp_br;
  public:
    using U8Input_Poss::u_count;
    using U8Input_Poss::byte_count;
    using U8Input_Poss::lineno;
    using U8Input_Poss::colno;
    using U8Input_Poss::colno_byte;
    using U8Input_Poss::c_prev;

    using BBWP::BBWP;

    using ByteInput_Base::resize_buffer;
    using ByteInput_Base::realign_buffer;
    using ByteInput_Base::fill_buffer;
    using ByteInput_Base::discard_buffer;

    using BufferedInput_Base::buffer_size;
    using BufferedInput_Base::data_size;

    using ByteInput_Base_With_Pos<U8Input_Poss>::set_source;
    using ByteInput_Base::continue_source;
  private:
    static constexpr size_t expand_calc(const size_t size,const size_t added){
        const size_t size_pending = size<added ? size+added : 2*size;
        return size_pending<U8INPUT_DEFAULT_SIZE ? U8INPUT_DEFAULT_SIZE : size_pending;
    }

    void adjust_buffer_for(const unsigned to_be_appended){
        if(e_br+to_be_appended>s_br){
            if(e_br-p_br+to_be_appended<=s_br)
                realign_buffer();
            else
                resize_buffer(expand_calc(s_br,to_be_appended));
        }
    }

    template<bool P>
    yuki::U8Char get_impl(){
        if(pp_br<e_br){
            assert(ByteInput_Base::needs_buffer());
            const unsigned u8l = yuki::u8_length(static_cast<unsigned char>(br[pp_br]));
            const size_t after = e_br-pp_br;
            if(u8l>after){
                const unsigned remaining = u8l-after;
                adjust_buffer_for(remaining);
                const size_t filled=BufferedInput_Base::fill_buffer();
                assert(filled>=remaining);
            }
            const yuki::U8Char u8c(br+pp_br);
            pp_br+=u8l;
            if constexpr(P)
                U8Input_Poss::advance(u8c,u8l);
            return u8c;
        }

        if(ByteInput_Base::needs_buffer()){
            if(Input::getable()){
                const unsigned u8l = yuki::u8_length(Input::peek());
                adjust_buffer_for(u8l);
                const size_t filled = BufferedInput_Base::fill_buffer();
                assert(filled>=u8l);
                const yuki::U8Char u8c(br+pp_br);
                pp_br+=u8l;
                if constexpr(P)
                    U8Input_Poss::advance(u8c,u8l);
                return u8c;
            }
        }else{
            if(const int p=Input::peek(); p!=EOF){
                const unsigned u8l = yuki::u8_length(p);
                unsigned char buf[4];
                const size_t read = Input::read(buf,1,u8l);
                assert(read==u8l);
                const yuki::U8Char u8c(buf);
                if constexpr(P)
                    U8Input_Poss::advance(u8c,u8l);
                return u8c;
            }
        }

        return yuki::EOF_U8;
    } // yuki:::U8Char get_impl()

    yuki::U8Char get_np() {return get_impl<false>();}
  public:
    yuki::U8Char get() {return get_impl<true>();}

    using ByteInput_Base::getable;

    int peek_byte() const {return ByteInput_Base::peek();}

    yuki::U8Char peek(){
        if(pp_br<e_br){
            assert(ByteInput_Base::needs_buffer());
            const unsigned u8l = yuki::u8_length(static_cast<unsigned char>(br[pp_br]));
            const size_t after = e_br-pp_br;
            if(u8l>after){
                const unsigned remaining = u8l-after;
                adjust_buffer_for(remaining);
                const size_t filled=BufferedInput_Base::fill_buffer();
                assert(filled>=remaining);
            }
            return yuki::U8Char(br+pp_br);
        }

        if(ByteInput_Base::needs_buffer()){
            if(Input::getable()){
                const unsigned u8l = yuki::u8_length(Input::peek());
                adjust_buffer_for(u8l);
                const size_t filled = BufferedInput_Base::fill_buffer();
                assert(filled>=u8l);
                return yuki::U8Char(br+pp_br);
            }
        }else{
            if(const int p=Input::peek(); p!=EOF){
                const unsigned u8l = yuki::u8_length(p);
                unsigned char buf[4];
                const size_t peeked = Input::peek(buf,u8l);
                assert(peeked==u8l);
                return yuki::U8Char(buf);
            }
        }

        return yuki::EOF_U8;
    }

    using typename ByteInput_Base_With_Pos<U8Input_Poss>::Pos;
    using ByteInput_Base_With_Pos<U8Input_Poss>::get_pos;
    using ByteInput_Base_With_Pos<U8Input_Poss>::set_pos;
    using ByteInput_Base_With_Pos<U8Input_Poss>::matched;
    using ByteInput_Base_With_Pos<U8Input_Poss>::clear_matched;

    using U8Input_Poss::reset_poss;

    bool at_bol() const {return colno==1;}
    using ByteInput_Base::at_eol;
    using U8Input_Poss::at_boi;
    friend ByteInput_Base;
    bool at_eoi() {return ByteInput_Base::at_eoi<U8Input_Tp<U8INPUT_DEFAULT_SIZE>>();}
    static constexpr bool isword(const yuki::U8Char u8c){
        using namespace yuki::literals;
        return (u8c>='a'_u8 && u8c<='z'_u8)
            || (u8c>='A'_u8 && u8c<='Z'_u8)
            || (u8c>='0'_u8 && u8c<='9'_u8)
            || u8c=='_'_u8;
    }
    bool at_wb() {return isword(c_prev)!=isword(peek());}
}; // struct U8Input_Tp

typedef U8Input_Tp<128*1024> U8Input;
} // namespace yuki::lex
