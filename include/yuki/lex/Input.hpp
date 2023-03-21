#pragma once
#include<yuki/uchar.hpp>
#include<cstdio>
#include<cstring>
#include<cassert>
#include<string_view>

namespace yuki::lex{

struct CString_Input{
    const char* cstr=nullptr;

    constexpr void set_source() {cstr=nullptr;}
    constexpr void set_source(const char* const s) {cstr=s;}

    /// Has the same semantics as `fread`.
    /// @pre `size!=0`.
    size_t read(void* const buf,const size_t size,const size_t count){
        if(!cstr)
            return 0;
        assert(size!=0);
        size_t i=0;
        for(;i<count;++i)
            for(size_t j=0;j<size;++j)
                if(cstr[j]=='\0')
                    goto copy_s;
        copy_s:
        const size_t total = size*i;
        memcpy(buf,cstr,total);
        cstr+=total;
        return i;
    }

    constexpr int get(){
        return cstr && *cstr!='\0' ? static_cast<unsigned char>(*cstr++) : EOF;
    }

    constexpr bool getable() const {return cstr && *cstr!='\0';}
    explicit constexpr operator bool() const {return getable();}

    constexpr int peek() const {
        return cstr && *cstr!='\0' ? static_cast<unsigned char>(*cstr) : EOF;
    }

    constexpr int peek(const ptrdiff_t off) const {return cstr ? static_cast<unsigned char>(cstr[off]) : EOF;}

    size_t peek(void* const buf,const size_t count) const {
        if(!cstr)
            return 0;
        size_t i=0;
        for(;i<count;++i)
            if(cstr[i]=='\0')
                break;
        memcpy(buf,cstr,i);
        return i;
    }

    bool at_bol() const = delete;
    constexpr bool at_eol() const {
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

    constexpr void advance_byte(const ptrdiff_t off) {assert(cstr); cstr+=off;}

    constexpr void remove_prefix(const size_t s) {assert(cstr); cstr+=s;}

    typedef const char* Pos;
    constexpr Pos get_pos() const {return cstr;}
    constexpr void set_pos(const Pos pos) {cstr=pos;}
    constexpr std::string_view matched(const Pos pos_begin) const {
        assert(cstr && pos_begin && cstr>=pos_begin);
        return {pos_begin,cstr};
    }
    constexpr void clear_matched() const {}
}; // struct CString_Input


struct SV_Input{
    const char* data=nullptr;
    size_t size=0;

    constexpr SV_Input() noexcept = default;
    constexpr SV_Input(const char* const dp,const size_t sp) noexcept :
        data(dp),
        size(sp)
    {}
    constexpr SV_Input(const std::string_view sv) noexcept : SV_Input(sv.data(),sv.size()) {}

    explicit constexpr operator std::string_view() const {return {data,size};}

    constexpr void set_source() {data=nullptr;size=0;}
    constexpr void set_source(const char* const d,const size_t s) {data=d;size=s;}
    constexpr void set_source(const std::string_view sv) {set_source(sv.data(),sv.size());}

    /// Has the same semantics as `fread`.
    /// @pre `size_p!=0`.
    size_t read(void* const buf,const size_t size_p,const size_t count){
        assert(size_p!=0);
        const size_t count_max = size/size_p;
        const size_t count_real = count_max<count ? count_max : count;
        const size_t total = count_real*size_p;
        memcpy(buf,data,total);
        data+=total;
        size-=total;
        return count_real;
    }

    constexpr int get(){
        return size>0 ? (--size,static_cast<unsigned char>(*data++)) : EOF;
    }

    constexpr bool getable() const {return size>0;}
    explicit operator bool() const {return getable();}

    constexpr int peek() const {
        return size>0 ? static_cast<unsigned char>(*data) : EOF;
    }

    constexpr int peek(const ptrdiff_t off) const {
        assert(data && (off<0 || size_t(off)<=size));
        return static_cast<unsigned char>(data[off]);
    }

    size_t peek(void* const buf,const size_t count) const {
        const size_t count_real = count<size ? count : size;
        memcpy(buf,data,count_real);
        return count_real;
    }

    constexpr void advance_byte(const ptrdiff_t off) {assert(data && (off<0 || size_t(off)<=size)); data+=off; size-=off;}

    constexpr void remove_prefix(const size_t s) {assert(s<=size); data+=s; size-=s;}
    constexpr void remove_suffix(const size_t s) {assert(s<=size); size-=s;}

    typedef const char* Pos;
    constexpr Pos get_pos() const {return data;}
    constexpr void set_pos(const Pos pos){
        assert(data && pos);
        size += (data-pos);
        data=pos;
    }
    constexpr std::string_view matched(const Pos pos_begin) const {
        assert(data && pos_begin && data>=pos_begin);
        return {pos_begin,data};
    }
    constexpr void clear_matched() const {}

    bool at_bol() const = delete;
    constexpr bool at_eol() const {
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
}; // struct SV_Input


struct FILE_Input{
    FILE* file=nullptr;

    constexpr void set_source() {file=nullptr;}
    constexpr void set_source(FILE* const f) {file=f;}

    size_t read(void* const buf,const size_t size,const size_t count) const {return file ? fread(buf,size,count,file) : 0;}

    int get() const {return file ? fgetc(file) : EOF;}

    bool getable() const {return file && feof(file)==0 && ferror(file)==0;}
    explicit operator bool() const {return getable();}

    int peek() const {
        if(!file)
            return EOF;
        const int c = fgetc(file);
        return (c!=EOF) ? (ungetc(c,file),c) : EOF;
    }

    bool at_eol() const {
        using namespace yuki::literals;
        switch(peek()){
            case '\r'_uc:
            case '\n'_uc:
            case EOF: return true;
            default: return false;
        }
    }
};


/// A simple wrapper for various type of input sources.
struct Input{
    enum struct Source_Type : unsigned {NIL,F,S,SV};

    constexpr Input() noexcept :
        source_type_(Source_Type::NIL),
        i_file{nullptr}
    {}

    constexpr Input(FILE* const f) noexcept :
        source_type_(Source_Type::F),
        i_file{f}
    {}
    constexpr Input(const char* const s) noexcept :
        source_type_(Source_Type::S),
        i_cstr{s}
    {}
    constexpr Input(const char* const s,const size_t sz) noexcept :
        source_type_(Source_Type::SV),
        i_sv(s,sz)
    {}
    constexpr Input(const std::string_view sv) noexcept :
        source_type_(Source_Type::SV),
        i_sv(sv.data(),sv.size())
    {}

    constexpr Source_Type get_source_type() const {return source_type_;}

    constexpr FILE* file() const {
        assert(source_type_==Source_Type::F);
        return i_file.file;
    }

    constexpr const char* c_str() const {
        assert(source_type_==Source_Type::S || source_type_==Source_Type::SV);
        switch(source_type_){
            case Source_Type::S: return i_cstr.cstr;
            case Source_Type::SV: return i_sv.data;
            default: return nullptr;
        }
    }

    constexpr size_t remaining_size() const {
        assert(source_type_==Source_Type::SV);
        return i_sv.size;
    }

    constexpr std::string_view string_view() const {
        assert(source_type_==Source_Type::SV);
        return static_cast<std::string_view>(i_sv);
    }

    constexpr FILE_Input& file_input() {assert(source_type_==Source_Type::F); return i_file;}
    constexpr const FILE_Input& file_input() const {assert(source_type_==Source_Type::F); return i_file;}
    constexpr CString_Input& cstring_input() {assert(source_type_==Source_Type::S); return i_cstr;}
    constexpr const CString_Input& cstring_input() const {assert(source_type_==Source_Type::S); return i_cstr;}
    constexpr SV_Input& sv_input() {assert(source_type_==Source_Type::SV); return i_sv;}
    constexpr const SV_Input& sv_input() const {assert(source_type_==Source_Type::SV); return i_sv;}

    constexpr void set_source() {source_type_=Source_Type::NIL;}
    constexpr void set_source(FILE* const fp){
        source_type_=Source_Type::F;
        i_file.file = fp;
    }
    constexpr void set_source(const char* const sp){
        source_type_=Source_Type::S;
        i_cstr.cstr = sp;
    }
    constexpr void set_source(const char* const dp,const size_t szp){
        source_type_=Source_Type::SV;
        i_sv.data = dp;
        i_sv.size = szp;
    }
    constexpr void set_source(const std::string_view sv) {set_source(sv.data(),sv.size());}

    /// Has the same semantics as `fread`.
    /// @pre `size!=0`.
    size_t read(void* const buf,const size_t size,const size_t count){
        assert(size!=0);
        switch(source_type_){
            case Source_Type::F: return i_file.read(buf,size,count);
            case Source_Type::S: return i_cstr.read(buf,size,count);
            case Source_Type::SV: return i_sv.read(buf,size,count);
            default: return 0;
        }
    }

    /// Has the same semantics as `fgetc`.
    int get(){
        switch(source_type_){
            case Source_Type::F: return i_file.get();
            case Source_Type::S: return i_cstr.get();
            case Source_Type::SV: return i_sv.get();
            default: return EOF;
        }
    }

    bool getable() const {
        switch(source_type_){
            case Source_Type::F: return i_file.getable();
            case Source_Type::S: return i_cstr.getable();
            case Source_Type::SV: return i_sv.getable();
            default: return false;
        }
    }
    explicit operator bool() const {return getable();}

    int peek() const {
        switch(source_type_){
            case Source_Type::F: return i_file.peek();
            case Source_Type::S: return i_cstr.peek();
            case Source_Type::SV: return i_sv.peek();
            default: return EOF;
        }
    }

    int peek(const ptrdiff_t a) const {
        switch(source_type_){
            case Source_Type::F:{
                assert(a==1);
                return i_file.peek();
            }
            case Source_Type::S: return i_cstr.peek(a);
            case Source_Type::SV: return i_sv.peek(a);
            default: return EOF;
        }
    }

    size_t peek(void* const buf,const size_t count) const {
        switch(source_type_){
            case Source_Type::F:{
                assert(count==1);
                if(i_file.getable()){
                    *static_cast<unsigned char*>(buf) = i_file.peek();
                    return 1;
                }else
                    return 0;
            }
            case Source_Type::S: return i_cstr.peek(buf,count);
            case Source_Type::SV: return i_sv.peek(buf,count);
            default: return 0;
        }
    }

    typedef const char* Pos;
    constexpr Pos get_pos() const {
        assert(source_type_==Source_Type::S || source_type_==Source_Type::SV);
        switch(source_type_){
            case Source_Type::S: return i_cstr.get_pos();
            case Source_Type::SV: return i_sv.get_pos();
            default: return nullptr;
        }
    }
    constexpr void set_pos(const Pos pos){
        assert(source_type_==Source_Type::S || source_type_==Source_Type::SV);
        switch(source_type_){
            case Source_Type::S: i_cstr.set_pos(pos);return;
            case Source_Type::SV: i_sv.set_pos(pos);return;
            default:;
        }
    }
    constexpr std::string_view matched(const Pos pos_begin) const {
        assert(source_type_==Source_Type::S || source_type_==Source_Type::SV);
        switch(source_type_){
            case Source_Type::S: return i_cstr.matched(pos_begin);
            case Source_Type::SV: return i_sv.matched(pos_begin);
            default: return {};
        }
    }
    constexpr void clear_matched() const {}

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
    union{
    FILE_Input i_file;
    CString_Input i_cstr;
    SV_Input i_sv;
    };
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
    void set_source(const std::string_view sv) {discard_buffer();Input::set_source(sv);}

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
