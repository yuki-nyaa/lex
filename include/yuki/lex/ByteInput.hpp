#pragma once
#include<yuki/lex/Input.hpp>

namespace yuki::lex{
struct ByteInput_Base : protected BufferedInput_Base{
  protected:
    using Input::force_buffering;
    size_t pp_br = 0;
  public:
    using BufferedInput_Base::BufferedInput_Base;

    ByteInput_Base(const ByteInput_Base& other) noexcept :
        BufferedInput_Base(static_cast<const BufferedInput_Base&>(other)),
        pp_br(other.pp_br-other.p_br)
    {}

    ByteInput_Base(ByteInput_Base&& other) noexcept :
        BufferedInput_Base(static_cast<BufferedInput_Base&&>(other)),
        pp_br(other.pp_br)
    {other.pp_br=0;other.force_buffering=false;}

    ByteInput_Base& operator=(const ByteInput_Base& other) noexcept {
        if(this!=&other){
            BufferedInput_Base::operator=(other);
            pp_br = other.pp_br-other.p_br;
        }
        return *this;
    }

    ByteInput_Base& operator=(ByteInput_Base&& other) noexcept {
        if(this!=&other){
            BufferedInput_Base::operator=(static_cast<BufferedInput_Base&&>(other));
            pp_br = other.pp_br;
            other.pp_br=0;
            other.force_buffering=false;
        }
        return *this;
    }

    /// @note Do not resize smaller than `e_br-p_br`!
    void resize_buffer(const size_t size_new){
        const size_t off = pp_br-p_br;
        BufferedInput_Base::resize_buffer(size_new);
        pp_br = off;
    }

    void realign_buffer(){
        const size_t off = pp_br-BufferedInput_Base::p_br;
        BufferedInput_Base::realign_buffer();
        pp_br = off;
    }

    void fill_buffer(){
        assert(needs_buffer());
        BufferedInput_Base::fill_buffer();
    }

    void discard_buffer() {BufferedInput_Base::discard_buffer();pp_br=0;}

    bool needs_buffer() const {return !BufferedInput_Base::no_buffer_needed() || force_buffering;}

    void continue_source(FILE* const f) {assert(needs_buffer());Input::set_source(f);}
    void continue_source(const char* const s) {assert(needs_buffer());force_buffering=true;Input::set_source(s);}
    void continue_source(const char* const s,const size_t sz) {assert(needs_buffer());force_buffering=true;Input::set_source(s,sz);}
    void continue_source(const std::string_view sv) {assert(needs_buffer());force_buffering=true;Input::set_source(sv);}

    bool getable() const {return pp_br<e_br || Input::getable();}

    int peek() const {return pp_br<e_br ? static_cast<int>(static_cast<unsigned char>(br[pp_br])) : Input::peek();}

    bool at_eol() const {
        using namespace yuki::literals;
        switch(peek()){
            case '\r'_uc:
            case '\n'_uc:
            case EOF: return true;
            default: return false;
        }
    }

    template<typename I>
    bool at_eoi(){
        using namespace yuki::literals;
        if(needs_buffer()){
            switch(peek()){
                case '\r'_uc:{
                    static_cast<I*>(this)->get_np();
                    switch(peek()){
                        case 'n'_uc:{
                            static_cast<I*>(this)->get_np();
                            if(peek()==EOF){
                                pp_br-=2;
                                return true;
                            }else{
                                pp_br-=2;
                                return false;
                            }
                        }
                        case EOF: --pp_br;return true;
                        default: --pp_br;return false;
                    }
                }
                case '\n'_uc:{
                    static_cast<I*>(this)->get_np();
                    if(peek()==EOF){
                        --pp_br;
                        return true;
                    }else{
                        --pp_br;
                        return false;
                    }
                }
                case EOF: return true;
                default: return false;
            }
        }else{
            switch(Input::peek()){
                case '\r'_uc:{
                    const Input::Pos pos_orig = Input::get_pos();
                    Input::get();
                    switch(Input::peek()){
                        case 'n'_uc:{
                            Input::get();
                            if(Input::peek()==EOF){
                                Input::set_pos(pos_orig);
                                return true;
                            }else{
                                Input::set_pos(pos_orig);
                                return false;
                            }
                        }
                        case EOF: Input::set_pos(pos_orig);return true;
                        default: Input::set_pos(pos_orig);return false;
                    }
                }
                case '\n'_uc:{
                    const Input::Pos pos_orig = Input::get_pos();
                    Input::get();
                    if(Input::peek()==EOF){
                        Input::set_pos(pos_orig);
                        return true;
                    }else{
                        Input::set_pos(pos_orig);
                        return false;
                    }
                }
                case EOF: return true;
                default: return false;
            }
        }
    } // bool at_eoi()
}; // struct ByteInput_Base


template<typename Ps>
struct ByteInput_Base_With_Pos : protected ByteInput_Base, protected Ps{
    using ByteInput_Base::ByteInput_Base;

    ByteInput_Base_With_Pos(const ByteInput_Base_With_Pos& other) noexcept = default;

    ByteInput_Base_With_Pos(ByteInput_Base_With_Pos&& other) noexcept :
        ByteInput_Base(static_cast<ByteInput_Base&&>(other)),
        Ps(static_cast<Ps&&>(other))
    {other.Ps::reset_poss();}

    ByteInput_Base_With_Pos& operator=(const ByteInput_Base_With_Pos& other) noexcept = default;

    ByteInput_Base_With_Pos& operator=(ByteInput_Base_With_Pos&& other) noexcept {
        if(this!=&other){
            ByteInput_Base::operator=(static_cast<ByteInput_Base&&>(other));
            Ps::operator=(static_cast<Ps&&>(other));
            other.Ps::reset_poss();
        }
        return *this;
    }

    struct Pos{
        friend ByteInput_Base_With_Pos<Ps>;
        constexpr Pos() noexcept = default;
      private:
        union{
        size_t pp_off=0;
        Input::Pos pp_direct;
        };
        Ps ps;
        #ifndef NDEBUG
        bool unbuffered = false;
        constexpr Pos(const size_t pp_off_p,const Ps ps_p,const bool ub_p) noexcept :
            pp_off(pp_off_p),
            ps(ps_p),
            unbuffered(ub_p)
        {}
        constexpr Pos(const Input::Pos pp_direct_p,const Ps ps_p,const bool ub_p) noexcept :
            pp_direct(pp_direct_p),
            ps(ps_p),
            unbuffered(ub_p)
        {}
        #else
        constexpr Pos(const size_t pp_off_p,const Ps ps_p) noexcept :
            pp_off(pp_off_p),
            ps(ps_p)
        {}
        constexpr Pos(const Input::Pos pp_direct_p,const Ps ps_p) noexcept :
            pp_direct(pp_direct_p),
            ps(ps_p)
        {}
        #endif
    };

    Pos get_pos() const {
        #ifndef NDEBUG
        if(needs_buffer())
            return Pos(pp_br-p_br,*this,false);
        else
            return Pos(Input::get_pos(),*this,true);
        #else
        if(needs_buffer())
            return Pos(pp_br-p_br,*this);
        else
            return Pos(Input::get_pos(),*this);
        #endif
    }

    void set_pos(const Pos pos){
        assert(!pos.unbuffered==needs_buffer());
        if(needs_buffer())
            pp_br = p_br+pos.pp_off;
        else
            Input::set_pos(pos.pp_direct);
        Ps::operator=(pos.ps);
    }

    std::string_view matched(const Pos pos_begin) const {
        assert(!pos_begin.unbuffered==needs_buffer());
        return needs_buffer() ? std::string_view{br+p_br,pp_br-p_br} : Input::matched(pos_begin.pp_direct);
    }
    void clear_matched() {if(needs_buffer()) p_br=pp_br;}

    // Note: The following functions discard everything in the buffer.
    void set_source() {discard_buffer();Input::set_source();Ps::reset_poss();}
    void set_source(FILE* const f) {discard_buffer();Input::set_source(f);Ps::reset_poss();}
    void set_source(const char* const s,const bool fb=false) {discard_buffer();Input::set_source(s);Ps::reset_poss();force_buffering=fb;}
    void set_source(const char* const s,const size_t sz,const bool fb=false) {discard_buffer();Input::set_source(s,sz);Ps::reset_poss();force_buffering=fb;}
    void set_source(const std::string_view sv,const bool fb=false) {set_source(sv.data(),sv.size(),fb);}
}; // struct ByteInput_Base_With_Pos


struct Byte_Input_Poss{
    size_t byte_count=0;
    constexpr void reset_poss() {byte_count=0;}
    constexpr bool at_boi() const {return byte_count==0;}
};


template<size_t BYTEINPUT_DEFAULT_SIZE>
struct ByteInput_Tp : private ByteInput_Base_With_Pos<Byte_Input_Poss>{
  private:
    typedef ByteInput_Base_With_Pos<Byte_Input_Poss> BBWP;

    using BufferedInput_Base::br;
    using BufferedInput_Base::s_br;
    using BufferedInput_Base::e_br;
    using BufferedInput_Base::p_br;
    using ByteInput_Base::pp_br;
  public:
    using Byte_Input_Poss::byte_count;

    using BBWP::BBWP;

    using ByteInput_Base::resize_buffer;
    using ByteInput_Base::realign_buffer;
    using ByteInput_Base::fill_buffer;
    using ByteInput_Base::discard_buffer;

    using BufferedInput_Base::buffer_size;
    using BufferedInput_Base::data_size;

    using ByteInput_Base_With_Pos<Byte_Input_Poss>::set_source;
    using ByteInput_Base::continue_source;
  private:
    static constexpr size_t expand_calc(const size_t size,const size_t added){
        const size_t size_pending = size<added ? size+added : 2*size;
        return size_pending<BYTEINPUT_DEFAULT_SIZE ? BYTEINPUT_DEFAULT_SIZE : size_pending;
    }

    void adjust_buffer_for_one(){
        if(e_br==s_br){
            if(p_br!=0)
                realign_buffer();
            else
                resize_buffer(expand_calc(s_br,1));
        }
    }

    int get_np(){
        if(pp_br<e_br){
            assert(ByteInput_Base::needs_buffer());
            return static_cast<unsigned char>(br[pp_br++]);
        }

        if(ByteInput_Base::needs_buffer()){
            if(Input::getable()){
                adjust_buffer_for_one();
                BufferedInput_Base::fill_buffer();
                return static_cast<unsigned char>(br[pp_br++]);
            }else
                return EOF;
        }else
            return Input::get();
    }
  public:
    int get(){
        if(pp_br<e_br){
            assert(ByteInput_Base::needs_buffer());
            ++byte_count;
            return static_cast<unsigned char>(br[pp_br++]);
        }
        if(ByteInput_Base::needs_buffer()){
            if(Input::getable()){
                adjust_buffer_for_one();
                BufferedInput_Base::fill_buffer();
                ++byte_count;
                return static_cast<unsigned char>(br[pp_br++]);
            }else
                return EOF;
        }else{
            const int c = Input::get();
            if(c!=EOF)
                ++byte_count;
            return c;
        }
    }

    using ByteInput_Base::getable;

    using ByteInput_Base::peek;

    using typename ByteInput_Base_With_Pos<Byte_Input_Poss>::Pos;
    using ByteInput_Base_With_Pos<Byte_Input_Poss>::get_pos;
    using ByteInput_Base_With_Pos<Byte_Input_Poss>::set_pos;
    using ByteInput_Base_With_Pos<Byte_Input_Poss>::matched;
    using ByteInput_Base_With_Pos<Byte_Input_Poss>::clear_matched;

    using Byte_Input_Poss::reset_poss;

    // It's unlikely that one needs to check anchors when lexing simple bytes. But the anchor-checking functions that will not incur an overhead are provided anyway.

    bool at_bol() const = delete;
    using ByteInput_Base::at_eol;
    using Byte_Input_Poss::at_boi;
    friend ByteInput_Base;
    bool at_eoi() {return ByteInput_Base::at_eoi<ByteInput_Tp<BYTEINPUT_DEFAULT_SIZE>>();}
    bool at_wb() = delete;
}; // struct ByteInput_Tp

typedef ByteInput_Tp<128*1024> ByteInput;
} // namespace yuki::lex
