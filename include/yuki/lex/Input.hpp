#pragma once
#include<yuki/unicode.hpp>
#include<cstdio>
#include<cstring>
#include<cassert>
#include<string>

namespace yuki::lex{
/// A simple wrapper for various type of input sources.
struct Input{
    enum struct Source_Type : unsigned {NIL,F,S,SV};

    constexpr Input() noexcept :
        source_type_(Source_Type::NIL),
        source_(nullptr)
    {}

    constexpr Input(FILE* const f) noexcept :
        source_type_(Source_Type::F),
        source_(f)
    {}
    constexpr Input(const char* const s) noexcept :
        source_type_(Source_Type::S),
        source_(s)
    {}
    constexpr Input(const char* const s,const size_t sz) noexcept :
        source_type_(Source_Type::SV),
        source_(s,sz)
    {}
    constexpr Input(const std::string_view sv) noexcept :
        source_type_(Source_Type::SV),
        source_(sv.data(),sv.size())
    {}

    constexpr Source_Type get_source_type() const {return source_type_;}

    constexpr FILE* file() const {
        assert(source_type_==Source_Type::F);
        return source_.f;
    }

    constexpr const char* c_str() const {
        assert(source_type_==Source_Type::S || source_type_==Source_Type::SV);
        switch(source_type_){
            case Source_Type::S: return source_.s;
            case Source_Type::SV: return source_.sv.data;
            default: return nullptr;
        }
    }

    constexpr size_t remaining_size() const {
        assert(source_type_==Source_Type::SV);
        return source_.sv.size;
    }

    constexpr std::string_view string_view() const {
        assert(source_type_==Source_Type::SV);
        return {source_.sv.data,source_.sv.size};
    }

    constexpr void set_source() {source_type_=Source_Type::NIL;}
    constexpr void set_source(FILE* const fp){
        source_type_=Source_Type::F;
        source_.f = fp;
    }
    constexpr void set_source(const char* const sp){
        source_type_=Source_Type::S;
        source_.s = sp;
    }
    constexpr void set_source(const char* const dp,const size_t szp){
        source_type_=Source_Type::SV;
        source_.sv.data = dp;
        source_.sv.size = szp;
    }

    /// Has the same semantics as `fread`.
    /// @pre `size!=0`.
    size_t read(void* const buf,const size_t size,const size_t count){
        assert(size!=0);
        switch(source_type_){
            case Source_Type::F: return fread(buf,size,count,source_.f);
            case Source_Type::S:{
                size_t i=0;
                for(;i<count;++i)
                    for(size_t j=0;j<size;++j)
                        if(source_.s[j]=='\0')
                            goto copy_s;
                copy_s:
                const size_t total = size*i;
                memcpy(buf,source_.s,total);
                source_.s+=total;
                return i;
            }
            case Source_Type::SV:{
                const size_t count_max = source_.sv.size/size;
                const size_t count_real = count_max<count ? count_max : count;
                const size_t total = count_real*size;
                memcpy(buf,source_.sv.data,total);
                source_.sv.data+=total;
                source_.sv.size-=total;
                return count_real;
            }
            default: return 0;
        }
    }

    /// Has the same semantics as `fgetc`.
    int get(){
        switch(source_type_){
            case Source_Type::F:
                return fgetc(source_.f);
            case Source_Type::S:
                return *source_.s!='\0' ? static_cast<unsigned char>(*source_.s++) : EOF;
            case Source_Type::SV:
                return source_.sv.size>0 ? (--source_.sv.size,static_cast<unsigned char>(*source_.sv.data++)) : EOF;
            default:
                return EOF;
        }
    }

    bool getable() const {
        switch(source_type_){
            case Source_Type::F: return feof(source_.f)==0 && ferror(source_.f)==0;
            case Source_Type::S: return *source_.s!='\0';
            case Source_Type::SV: return source_.sv.size>0;
            default: return false;
        }
    }
    explicit operator bool() const {return getable();}

    int peek() const {
        switch(source_type_){
            case Source_Type::F:{
                const int c = fgetc(source_.f);
                return (c!=EOF) ? (ungetc(c,source_.f),c) : EOF;
            }
            case Source_Type::S:
                return *source_.s!='\0' ? static_cast<unsigned char>(*source_.s) : EOF;
            case Source_Type::SV:
                return source_.sv.size>0 ? static_cast<unsigned char>(*source_.sv.data) : EOF;
            default:
                return EOF;
        }
    }

    size_t peek(void* const buf,const size_t count) const {
        switch(source_type_){
            case Source_Type::S:{
                size_t i=0;
                for(;i<count;++i)
                    if(source_.s[i]=='\0')
                        break;
                memcpy(buf,source_.s,i);
                return i;
            }
            case Source_Type::SV:{
                const size_t count_real = count<source_.sv.size ? count : source_.sv.size;
                memcpy(buf,source_.sv.data,count_real);
                return count_real;
            }
            default: return 0;
        }
    }

    typedef const char* Pos;
    constexpr Pos get_pos() const {return c_str();}
    constexpr void set_pos(const Pos pos){
        assert(source_type_==Source_Type::S || source_type_==Source_Type::SV);
        switch(source_type_){
            case Source_Type::S: source_.s=pos;return;
            case Source_Type::SV:{
                assert(source_.sv.data>=pos);
                source_.sv.size += (source_.sv.data-pos);
                source_.sv.data=pos;
                return;
            }
        }
    }
    constexpr std::string_view take(const Pos pos_begin) const {
        assert(source_type_==Source_Type::S || source_type_==Source_Type::SV);
        switch(source_type_){
            case Source_Type::S: assert(source_.s>=pos_begin);return {pos_begin,source_.s};
            case Source_Type::SV: assert(source_.sv.data>=pos_begin);return {pos_begin,source_.sv.data};
            default: return {}; // Unreachable
        }
    }

    bool at_bol() const = delete;
    bool at_eol() const {
        using namespace yuki::literals;
        switch(peek()){
            case '\r'_uc:
            case '\n'_uc:
            case EOF: return true;
            default: return false;
        }
    }
    bool at_boi() const = delete;
    bool at_eoi() = delete;
    bool at_wb() = delete;
  protected:
    Source_Type source_type_;
    yuki::encoding enc_ = yuki::encoding::utf8; /// Well, this really shouldn't appear here. But it does, to save some negligible amount of memory. Used in `Get_U8`.
    bool force_buffering = false; /// Well, this really shouldn't appear here. But it does, to save some negligible amount of memory. Used in `ByteInput_Base`.
    union Source_Union_{
        FILE* f;
        const char* s;
        struct{const char* data; size_t size;} sv;
        constexpr Source_Union_(std::nullptr_t = nullptr) noexcept : f(nullptr) {}
        constexpr Source_Union_(FILE* const fp) noexcept : f(fp) {}
        constexpr Source_Union_(const char* const sp) noexcept : s(sp) {}
        constexpr Source_Union_(const char* const dp,const size_t szp) noexcept : sv{dp,szp} {}
    } source_;
}; // struct Input




struct BufferedInput_Base : protected Input {
    using Input::Input;

    /// @note The size of the buffer remains the same, but the contents become left-aligned.
    BufferedInput_Base(const BufferedInput_Base& other) noexcept :
        Input(other),
        br(new char[other.s_br]),
        s_br(other.s_br),
        e_br(other.e_br-other.p_br),
        p_br(0)
    {memcpy(br,other.br+other.p_br,other.e_br-other.p_br);}

    BufferedInput_Base(BufferedInput_Base&& other) noexcept :
        Input(std::move(other)),
        br(other.br),
        s_br(other.s_br),
        e_br(other.e_br),
        p_br(other.p_br)
    {
        other.br = nullptr;
        other.s_br = 0;
        other.e_br = 0;
        other.p_br = 0;
    }

    /// @note The buffer will NOT be resized if the data in `other` fit. The copied data will become left-aligned.
    BufferedInput_Base& operator=(const BufferedInput_Base& other) noexcept {
        if(this!=&other){
            Input::operator=(other);
            const size_t other_data_size = other.data_size();
            if(s_br<other_data_size){
                delete[] br;
                br = new char[other.s_br];
                s_br = other.s_br;
            }
            e_br=other_data_size;
            p_br=0;
            memcpy(br,other.br+other.p_br,other_data_size);
        }
        return *this;
    }

    BufferedInput_Base& operator=(BufferedInput_Base&& other) noexcept {
        if(this!=&other){
            Input::operator=(std::move(other));
            br=other.br;
            s_br=other.s_br;
            e_br=other.e_br;
            p_br=other.p_br;

            other.br = nullptr;
            other.s_br = 0;
            other.e_br = 0;
            other.p_br = 0;
        }
        return *this;
    }

    ~BufferedInput_Base() noexcept {delete[] br;}

    /// @note Do not resize smaller than `e_br-p_br`!
    void resize_buffer(const size_t size_new){
        if(size_new!=s_br){
            assert(size_new>=e_br-p_br);
            char* const br_new = new char [size_new];
            memcpy(br_new,br+p_br,e_br-p_br);
            br = br_new;
            s_br = size_new;
            e_br -= p_br;
            p_br = 0;
        }
    }

    void realign_buffer(){
        memmove(br,br+p_br,e_br-p_br);
        e_br -= p_br;
        p_br = 0;
    }

    size_t fill_buffer(){
        const size_t read = Input::read(br+e_br,1,s_br-e_br);
        e_br+=read;
        return read;
    }

    void discard_buffer() {e_br=0;p_br=0;}

    size_t buffer_size() const {return s_br;}
    size_t data_size() const {return e_br-p_br;}

    // Note: The following functions discard everything in the buffer.
    void set_source() {discard_buffer();Input::set_source();}
    void set_source(FILE* const f) {discard_buffer();Input::set_source(f);}
    void set_source(const char* const s) {discard_buffer();Input::set_source(s);}
    void set_source(const char* const s,const size_t sz) {discard_buffer();Input::set_source(s,sz);}

    bool getable() const {return p_br<e_br || Input::getable();}
    explicit operator bool() const {return getable();}

    int peek() const {return p_br<e_br ? static_cast<int>(static_cast<unsigned char>(br[p_br])) : Input::peek();}

  protected:
    bool no_buffer_needed() const {
        switch(Input::source_type_){
            case Input::Source_Type::NIL:
            case Input::Source_Type::S:
            case Input::Source_Type::SV: return true;
            default: return false;
        }
    }

    char* br = nullptr;
    size_t s_br = 0;
    size_t e_br = 0;
    size_t p_br = 0;
}; // BufferedInput_Base
} // namespace yuki::lex
