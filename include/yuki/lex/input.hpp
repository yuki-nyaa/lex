#pragma once
#include<yuki/utf8.hpp>
#include<cstdio>
#include<cstring>
#include<cassert>
#include<string>

namespace yuki::lex{
/// A simple wrapper for various input sources.
struct Input {
  public:
    /// Input type
    enum struct Source_Type : unsigned {NIL,FILE_P,CCHAR_P,SV,CUCHAR_P,USV,INPUT};
    static constexpr size_t get_raw_temp_default_size = 4; // Size just enough for normal use. You might increase it if you have special needs.
  private:
    template<typename T>
    constexpr Input(Source_Type st,T t,yuki::encoding enc,yuki::codepage_t* cp) noexcept :
        source_type_(st),
        source_(t)
        #ifdef YUKI_CHAR_ABNORMAL
        ,get_raw_temp_(nullptr), // Allocated when needed
        get_raw_temp_size_(0)
        #endif
    {
        set_encoding(enc,cp);
    }
  public:
    /// Construct empty input character sequence.
    constexpr Input() noexcept : Input(Source_Type::NIL,nullptr,encoding::utf8,nullptr) {}
    constexpr Input(const Input& other) noexcept :
        source_type_(other.source_type_),
        source_(other.source_),
        enc_(other.enc_),
        cp_(other.cp_)
        #ifdef YUKI_CHAR_ABNORMAL
        ,get_raw_temp_(nullptr),
        get_raw_temp_size_(0)
        #endif
    {}
    constexpr Input(Input&& other) noexcept :
        source_type_(other.source_type_),
        source_(other.source_),
        enc_(other.enc_),
        cp_(other.cp_)
        #ifdef YUKI_CHAR_ABNORMAL
        ,get_raw_temp_(other.get_raw_temp_),
        get_raw_temp_size_(other.get_raw_temp_size_)
        #endif
    {
        other.set_source();
        #ifdef YUKI_CHAR_ABNORMAL
        other.get_raw_temp_=nullptr;
        other.get_raw_temp_size_=0;
        #endif
    }
    /// Construct input character sequence from a char* string and a size.
    constexpr Input(
        const char* cstring, ///< char string
        size_t size,    ///< length of the string
        encoding enc = encoding::utf8,
        yuki::codepage_t* cp = nullptr) noexcept
    :
        source_type_(Source_Type::SV),
        source_(cstring,size)
        #ifdef YUKI_CHAR_ABNORMAL
        ,get_raw_temp_(nullptr), // Allocated when needed
        get_raw_temp_size_(0)
        #endif
    {
        set_encoding(enc,cp);
    }
    /// Construct input character sequence from a NUL-terminated string.
    constexpr Input(const char *cstring, ///< NUL-terminated char* string
        encoding enc = encoding::utf8,
        yuki::codepage_t* cp = nullptr) noexcept
    :
        Input(Source_Type::CCHAR_P,cstring,enc,cp)
    {}
    /// Construct input character sequence from a std::string.
    Input(const std::string& string,
        encoding enc = encoding::utf8,
        yuki::codepage_t* cp = nullptr) noexcept
    :
        Input(string.c_str(),string.size(),enc,cp)
    {}
    /// Construct input character sequence from an open FILE* file descriptor.
    constexpr Input(FILE *file,
        encoding enc = encoding::utf8,
        yuki::codepage_t* cp = nullptr) noexcept
    :
        Input(Source_Type::FILE_P,file,enc,cp)
    {}
    /// Construct input character sequence from a unsigned char* string and a size.
    constexpr Input(
        const unsigned char* ucstring, ///< char string
        size_t size,    ///< length of the string
        encoding enc = encoding::utf8,
        yuki::codepage_t* cp = nullptr) noexcept
    :
        source_type_(Source_Type::USV),
        source_(ucstring,size)
        #ifdef YUKI_CHAR_ABNORMAL
        ,get_raw_temp_(nullptr), // Allocated when needed
        get_raw_temp_size_(0)
        #endif
    {
        set_encoding(enc,cp);
    }
    /// Construct input character sequence from a NUL-terminated string.
    constexpr Input(const unsigned char* ucstring, ///< NUL-terminated char* string
        encoding enc = encoding::utf8,
        yuki::codepage_t* cp = nullptr) noexcept
    :
        Input(Source_Type::CUCHAR_P,ucstring,enc,cp)
    {}
    /// Construct input character sequence from a std::basic_string<unsigned char>.
    Input(const std::basic_string<unsigned char>& ustring,
        encoding enc = encoding::utf8,
        yuki::codepage_t* cp = nullptr) noexcept
    :
        Input(ustring.c_str(),ustring.size(),enc,cp)
    {}
    /// Construct input character sequence from another `Input`.
    constexpr Input(Input& in,
        encoding enc = encoding::utf8,
        yuki::codepage_t* cp = nullptr) noexcept
    :
        Input(Source_Type::INPUT,&in,enc,cp)
    {}
    constexpr Input& operator=(const Input& other) noexcept
    {
        source_type_= other.source_type_;
        source_ = other.source_;
        enc_ = other.enc_;
        cp_ = other.cp_;
        #ifdef YUKI_CHAR_ABNORMAL
        get_raw_temp_=nullptr;
        get_raw_temp_size_=0;
        #endif
        return *this;
    }
    constexpr Input& operator=(Input&& other) noexcept
    {
        source_type_= other.source_type_;
        source_ = other.source_;
        enc_ = other.enc_;
        cp_ = other.cp_;
        other.set_source();
        #ifdef YUKI_CHAR_ABNORMAL
        get_raw_temp_=other.get_raw_temp_;
        get_raw_temp_size_=other.get_raw_temp_size_;
        other.get_raw_temp_=nullptr;
        other.get_raw_temp_size_=0;
        #endif
        return *this;
    }

    #ifdef YUKI_CHAR_ABNORMAL
    ~Input() noexcept {
        free_get_raw_temp(get_raw_temp_);
    }
    #endif

    constexpr Source_Type get_source_type() const {return source_type_;}

    /// Get the `const char*` of this Input object.
    constexpr const char* c_str() const
    {
        assert(source_type_==Source_Type::CCHAR_P || source_type_==Source_Type::SV);
        switch(source_type_){
            case Source_Type::CCHAR_P : return source_.cstring_;
            case Source_Type::SV : return source_.sv_.data_;
            default : return nullptr;
        }
    }

    /// Get the `FILE*` of this Input object.
    constexpr FILE* file() const
    {
        assert(source_type_==Source_Type::FILE_P);
        return source_.file_;
    }

    /// Get the `const unsigned char*` of this Input object.
    constexpr const unsigned char* u_c_str() const
    {
        assert(source_type_==Source_Type::CUCHAR_P || source_type_==Source_Type::USV);
        switch(source_type_){
            case Source_Type::CUCHAR_P : return source_.ucstring_;
            case Source_Type::USV : return source_.usv_.data_;
            default : return nullptr;
        }
    }

    /// Get the `reflex::Input` of this Input object.
    constexpr Input& input() const
    {
        assert(source_type_==Source_Type::INPUT);
        return *(source_.input_);
    }

    /// Get the remaining input size. Only meaningful for string view.
    constexpr size_t remaining_size() const {
        assert(source_type_==Source_Type::SV || source_type_==Source_Type::USV);
        switch(source_type_){
            case Source_Type::SV : return source_.sv_.size_;
            case Source_Type::USV : return source_.usv_.size_;
            default : return 0;
        }
    }

    /// Check if `get_raw()` can be performed.
    bool get_raw_able() const;
    explicit operator bool() const {return get_raw_able();}

    /// Get unconverted bytes to `buf`. Has the same semantics as `fread`, except that a cast may be performed when the source type and `C` differ.
    template<typename C>
    size_t get_raw(C* buf,size_t size,size_t count);

    /// Get one unconverted byte. Has the same semantics as `fgetc`.
    int get_raw();

    /// Peek one unconverted byte.
    int peek_raw();

    yuki::U8Char get_u8();

    constexpr encoding get_encoding() const {return enc_;}

    constexpr void set_encoding(
        yuki::encoding enc, ///< encoding
        yuki::codepage_t* cp = nullptr) ///< custom code page for encoding::custom
    {
        assert(enc == encoding::custom || cp == nullptr); // Predefined encoding must NOT come with custom codepage.
        assert(enc != encoding::custom || cp != nullptr); // Custom encoding must come with custom codepage.
        assert(source_type_!=Source_Type::CCHAR_P || (enc!=encoding::utf32be && enc!=encoding::utf32le)); // Since UTF-32 naturally contains lots of null bytes, determining end of input by null byte does not work.
        enc_ = enc;
        cp_  = cp;
    }

    void detect_encoding() {}

    constexpr yuki::codepage_t* get_page() const {return cp_;}

    constexpr void set_source() {source_type_ = Source_Type::NIL;}
    constexpr void set_source(FILE* f){
        source_type_ = Source_Type::FILE_P;
        source_.file_ = f;
    }
    constexpr void set_source(const char* s){
        source_type_ = Source_Type::CCHAR_P;
        source_.cstring_ = s;
    }
    constexpr void set_source(const char* s,size_t sz){
        source_type_ = Source_Type::SV;
        source_.sv_.data_ = s;
        source_.sv_.size_ = sz;
    }
    constexpr void set_source(const unsigned char* s){
        source_type_ = Source_Type::CUCHAR_P;
        source_.ucstring_ = s;
    }
    constexpr void set_source(const unsigned char* s,size_t sz){
        source_type_ = Source_Type::USV;
        source_.usv_.data_ = s;
        source_.usv_.size_ = sz;
    }
    constexpr void set_source(Input& in){
        source_type_ = Source_Type::INPUT;
        source_.input_ = &in;
    }
  protected:
    Source_Type source_type_;
    yuki::encoding enc_;  ///< encoding
    yuki::codepage_t* cp_; ///< custom code page
    union Source_Union_{
        FILE* file_;
        const char* cstring_;
        struct{const char* data_; size_t size_;} sv_;
        const unsigned char* ucstring_;
        struct{const unsigned char* data_; size_t size_;} usv_;
        Input* input_;
        constexpr Source_Union_(FILE* file_other) noexcept : file_(file_other) {}
        constexpr Source_Union_(const char* cstring_other) noexcept : cstring_(cstring_other) {}
        constexpr Source_Union_(const char* d,size_t s) noexcept : sv_{d,s} {}
        constexpr Source_Union_(const unsigned char* ucstring_other) noexcept : ucstring_(ucstring_other) {}
        constexpr Source_Union_(const unsigned char* d,size_t s) noexcept : usv_{d,s} {}
        constexpr Source_Union_(Input* i) noexcept : input_(i) {}
        constexpr Source_Union_(std::nullptr_t = nullptr) noexcept : Source_Union_((FILE*)nullptr) {}
    } source_;

    unsigned char utf8_buf_[4]; ///< Temp storage for `get_u8()`.
  private:
    #ifdef YUKI_CHAR_ABNORMAL
    unsigned char* get_raw_temp_; ///< Temporary storage for `get_raw(C*,size_t,size_t)` in the case of `FILE*`.
    size_t get_raw_temp_size_;

    unsigned char* allocate_get_raw_temp(size_t s) {return new unsigned char[s];}
    void free_get_raw_temp(unsigned char* p) {delete[] p;}
    void resize_get_raw_temp(size_t s){
        if(get_raw_temp_size_==s)
            return;
        else{
            free_get_raw_temp(get_raw_temp_);
            get_raw_temp_=allocate_get_raw_temp(s);
            get_raw_temp_size_=s;
        }
    }
    #endif
}; // struct Input

inline bool Input::get_raw_able() const
{
    switch(source_type_){
        case Source_Type::CCHAR_P :
            return *source_.cstring_!='\0';
        case Source_Type::SV :
            return source_.sv_.size_>0;
        case Source_Type::FILE_P :
            return feof(source_.file_)==0 && ferror(source_.file_)==0;
        case Source_Type::CUCHAR_P :
            return *source_.ucstring_!='\0';
        case Source_Type::USV :
            return source_.usv_.size_>0;
        case Source_Type::INPUT :
            return source_.input_->get_raw_able();
        default :
            return false;
    }
}

template<typename C>
size_t Input::get_raw(C* buf,size_t size,size_t count){
    static_assert(yuki::is_char_or_uchar_v_<C>);

    switch(source_type_){
        case Source_Type::CCHAR_P:{
            for(size_t i = 0;i<count;++i){
                for(size_t j = 0;j<size;++j)
                    if(source_.cstring_[j]=='\0')
                        return i;
                yuki::char_copy(buf,source_.cstring_,size);
                buf+=size;
                source_.cstring_+=size;
            }
            return count;
        }
        case Source_Type::SV:{
            for(size_t i = 0;i<count;++i){
                if(size>source_.sv_.size_)
                    return i;
                else{
                    yuki::char_copy(buf,source_.sv_.data_,size);
                    buf+=size;
                    source_.sv_.data_+=size;
                    source_.sv_.size_-=size;
                }
            }
            return count;
        }
        case Source_Type::FILE_P:{
            #ifndef YUKI_CHAR_ABNORMAL
            return fread(buf,size,count,source_.file_);
            #else
            if constexpr(std::is_same_v<C,unsigned char>)
                return fread(buf,size,count,source_.file_);
            else{
                if(get_raw_temp_size_<size)
                    resize_get_raw_temp(size>get_raw_temp_default_size ? size : get_raw_temp_default_size);
                for(size_t i=0;i<count;++i){
                    if(fread(get_raw_temp_,size,1,source_.file_)==1){
                        yuki::char_copy(buf,get_raw_temp_,size);
                        buf+=size;
                    }else
                        return i;
                }
                return count;
            }
            #endif
        }
        case Source_Type::CUCHAR_P:{
            for(size_t i = 0;i<count;++i){
                for(size_t j = 0;j<size;++j)
                    if(source_.ucstring_[j]=='\0')
                        return i;
                yuki::char_copy(buf,source_.ucstring_,size);
                buf+=size;
                source_.ucstring_+=size;
            }
            return count;
        }
        case Source_Type::USV:{
            for(size_t i = 0;i<count;++i){
                if(size>source_.usv_.size_)
                    return i;
                else{
                    yuki::char_copy(buf,source_.usv_.data_,size);
                    buf+=size;
                    source_.usv_.data_+=size;
                    source_.usv_.size_-=size;
                }
            }
            return count;
        }
        case Source_Type::INPUT:{
            return source_.input_->get_raw(buf,size,count);
        }
        default : return 0;
    }
} // size_t Input::get_raw(C* buf,size_t size,size_t count)

/// Get one unconverted byte. Has the same semantics as `fgetc`.
inline int Input::get_raw(){
    switch(source_type_){
        case Source_Type::CCHAR_P:
            if(source_.cstring_[0]!='\0')
                return static_cast<unsigned char>(*source_.cstring_++);
            else
                return EOF;
        case Source_Type::SV:
            if(source_.sv_.size_>0)
                return --source_.sv_.size_,static_cast<unsigned char>(*source_.sv_.data_++);
            else
                return EOF;
        case Source_Type::FILE_P:
            return fgetc(source_.file_);
        case Source_Type::CUCHAR_P:
            if(source_.ucstring_[0]!=0)
                return *source_.ucstring_++;
            else
                return EOF;
        case Source_Type::USV:
            if(source_.usv_.size_>0)
                return --source_.usv_.size_,*source_.usv_.data_++;
            else
                return EOF;
        case Source_Type::INPUT:
                return source_.input_->get_raw();
        default: return EOF;
    }
}

/// Peek one unconverted byte.
inline int Input::peek_raw(){
    switch(source_type_){
        case Source_Type::CCHAR_P :
            return (*source_.cstring_!='\0') ? static_cast<unsigned char>(*source_.cstring_) : EOF;
        case Source_Type::SV :
            return (source_.sv_.size_>0) ? static_cast<unsigned char>(*source_.sv_.data_) : EOF;
        case Source_Type::FILE_P:{
            int c = fgetc(source_.file_);
            return (c!=EOF) ? (ungetc(c,source_.file_),c) : EOF;
        }
        case Source_Type::CUCHAR_P :
            return (*source_.ucstring_!=0) ? *source_.ucstring_ : EOF;
        case Source_Type::USV :
            return (source_.usv_.size_>0) ? *source_.usv_.data_ : EOF;
        case Source_Type::INPUT :
            return source_.input_->peek_raw();
        default:
            return EOF;
    }
}

yuki::U8Char Input::get_u8(){
    using yuki::U8Char;
    using yuki::to_u8;
    using yuki::encoding;
    switch (enc_){
        case encoding::utf8:{
            int c = get_raw();
            if(c==EOF || c>=0xF8)
                return yuki::EOF_U8;
            else{
                switch(yuki::u8_length(c)){
                    case 1 : return U8Char(0,0,0,c);
                    case 2 : {
                        int c1 = get_raw();
                        if(c1!=EOF)
                            return U8Char(0,0,c,c1);
                        break;
                    }
                    case 3 :{
                        if(get_raw(utf8_buf_, 2, 1) == 1)
                            return U8Char(0,c,utf8_buf_[0],utf8_buf_[1]);
                        break;
                    }
                    case 4 : {
                        if(get_raw(utf8_buf_, 3, 1) == 1)
                            return U8Char(c,utf8_buf_[0],utf8_buf_[1],utf8_buf_[2]);
                        break;
                    }
                }
            }
            break;
        }
        case encoding::utf16be:{
            if (get_raw(utf8_buf_, 2, 1) == 1){
                switch(yuki::u16_length(utf8_buf_[0])){
                    case 1 : return to_u8<encoding::utf16be>::convert(0,0,utf8_buf_[0],utf8_buf_[1]);
                    case 2 : {
                        if(get_raw(utf8_buf_+2, 2, 1) == 1)
                            return to_u8<encoding::utf16be>::convert(utf8_buf_[0],utf8_buf_[1],utf8_buf_[2],utf8_buf_[3]);
                        break;
                    }
                }
            }
            break;
        }
        case encoding::utf16le:{
            if (get_raw(utf8_buf_, 2, 1) == 1){
                switch(yuki::u16_length(utf8_buf_[1])){
                    case 1 : return to_u8<encoding::utf16le>::convert(0,0,utf8_buf_[0],utf8_buf_[1]);
                    case 2 : {
                        if(get_raw(utf8_buf_+2, 2, 1) == 1)
                            return to_u8<encoding::utf16le>::convert(utf8_buf_[0],utf8_buf_[1],utf8_buf_[2],utf8_buf_[3]);
                        break;
                    }
                }
            }
            break;
        }
        case encoding::utf32be:{
            if (get_raw(utf8_buf_, 4, 1) == 1)
                return to_u8<encoding::utf32be>::convert(utf8_buf_[0],utf8_buf_[1],utf8_buf_[2],utf8_buf_[3]);
            break;
        }
        case encoding::utf32le:{
            if (get_raw(utf8_buf_, 4, 1) == 1)
                return to_u8<encoding::utf32le>::convert(utf8_buf_[0],utf8_buf_[1],utf8_buf_[2],utf8_buf_[3]);
            break;
        }
        case encoding::latin1:{
            int c = get_raw();
            if(c!=EOF)
                return to_u8<encoding::latin1>::convert(c);
            break;
        }
        case encoding::custom:{
            int c = get_raw();
            if(c!=EOF)
                return to_u8<encoding::custom>::convert(c,cp_);
            break;
        }
        #ifdef YUKI_LEX_WITH_RARE_ENCODINGS
        case encoding::cp437:
        case encoding::cp850:
        case encoding::cp858:
        case encoding::ebcdic:
        case encoding::cp1250:
        case encoding::cp1251:
        case encoding::cp1252:
        case encoding::cp1253:
        case encoding::cp1254:
        case encoding::cp1255:
        case encoding::cp1256:
        case encoding::cp1257:
        case encoding::cp1258:
        case encoding::iso8859_2:
        case encoding::iso8859_3:
        case encoding::iso8859_4:
        case encoding::iso8859_5:
        case encoding::iso8859_6:
        case encoding::iso8859_7:
        case encoding::iso8859_8:
        case encoding::iso8859_9:
        case encoding::iso8859_10:
        case encoding::iso8859_11:
        case encoding::iso8859_13:
        case encoding::iso8859_14:
        case encoding::iso8859_15:
        case encoding::iso8859_16:
        case encoding::macroman:
        case encoding::koi8_r:
        case encoding::koi8_u:
        case encoding::koi8_ru:
        #endif
        default:;
    }
    return yuki::EOF_U8;
} // yuki::U8Char Input::get_u8()




/// Augmented `Input` capable of doing unget, lookahead, and position tracking.
struct BufferedInput : private Input{
  public:
    using Input::Source_Type;
    using Input::get_source_type;
    using Input::c_str;
    using Input::file;
    using Input::u_c_str;
    using Input::input;
    using Input::remaining_size;
    using Input::get_encoding;
    using Input::set_encoding;
    using Input::get_page;
  private:
    static unsigned char* allocate_br(size_t s) {return new unsigned char[s];}
    static char* allocate_b8(size_t s) {return new char[s];}
    static void free_br(unsigned char* p) {delete[] p;}
    static void free_b8(char* p) {delete[] p;}
    bool no_br_needed() const {
        return Input::source_type_==Source_Type::CCHAR_P
            || Input::source_type_==Source_Type::SV
            || Input::source_type_==Source_Type::CUCHAR_P
            || Input::source_type_==Source_Type::USV;
    }
    bool no_b8_needed() const {return Input::enc_==yuki::encoding::utf8;}
    bool read_directly() const {return no_br_needed() && s_br==0;}
    yuki::U8Char get_u8_from_br_input();
  public:
    BufferedInput() noexcept :
        Input(),
        br(nullptr),
        s_br(0),
        e_br(0),
        p_br(0),
        b8(nullptr),
        s_b8(0),
        e_b8(0),
        p_b8(0),
        pp_b8(0),
        lineno(1),
        colno(1),
        lineno_p(1),
        colno_p(1)
    {}

    template<typename... Args>
    explicit BufferedInput(Args&&... args) noexcept :
        Input(std::forward<Args>(args)...),
        br(nullptr),
        s_br(0),
        e_br(0),
        p_br(0),
        b8(nullptr),
        s_b8(0),
        e_b8(0),
        p_b8(0),
        pp_b8(0),
        lineno(1),
        colno(1),
        lineno_p(1),
        colno_p(1)
    {}

    BufferedInput(const BufferedInput& other) noexcept :
        Input(other),
        br(allocate_br(other.s_br)),
        s_br(other.s_br),
        e_br(other.e_br),
        p_br(other.p_br),
        b8(allocate_b8(other.s_b8)),
        s_b8(other.s_b8),
        e_b8(other.e_b8),
        p_b8(other.p_b8),
        pp_b8(other.pp_b8),
        lineno(other.lineno),
        colno(other.colno),
        lineno_p(other.lineno_p),
        colno_p(other.colno_p)
    {
        std::memcpy(br,other.br,s_br);
        std::memcpy(b8,other.b8,s_b8);
    }

    BufferedInput(BufferedInput&& other) noexcept :
        Input(std::move(other)),
        br(other.br),
        s_br(other.s_br),
        e_br(other.e_br),
        p_br(other.p_br),
        b8(other.b8),
        s_b8(other.s_b8),
        e_b8(other.e_b8),
        p_b8(other.p_b8),
        pp_b8(other.pp_b8),
        lineno(other.lineno),
        colno(other.colno),
        lineno_p(other.lineno_p),
        colno_p(other.colno_p)
    {
        other.br = nullptr;
        other.s_br = 0;
        other.e_br = 0;
        other.p_br = 0;
        other.b8 = nullptr;
        other.s_b8 = 0;
        other.e_b8 = 0;
        other.p_b8 = 0;
        other.pp_b8 = 0;
        other.reset_pos();
        other.reset_pos_p();
    }

    BufferedInput& operator=(const BufferedInput& other) noexcept {
        if(this!=&other){
            Input::operator=(other);
            br=allocate_br(other.s_br);
            s_br=other.s_br;
            e_br=other.e_br;
            p_br=other.p_br;
            b8=allocate_b8(other.s_b8);
            s_b8=other.s_b8;
            e_b8=other.e_b8;
            p_b8=other.p_b8;
            pp_b8=other.pp_b8;
            lineno=other.lineno;
            colno=other.colno;
            lineno_p=other.lineno_p;
            colno_p=other.colno_p;

            std::memcpy(br,other.br,s_br);
            std::memcpy(b8,other.b8,s_b8);
        }
        return *this;
    }

    BufferedInput& operator=(BufferedInput&& other) noexcept {
        if(this!=&other){
            Input::operator=(std::move(other));
            br=other.br;
            s_br=other.s_br;
            e_br=other.e_br;
            p_br=other.p_br;
            b8=other.b8;
            s_b8=other.s_b8;
            e_b8=other.e_b8;
            p_b8=other.p_b8;
            pp_b8=other.pp_b8;
            lineno=other.lineno;
            colno=other.colno;
            lineno_p=other.lineno_p;
            colno_p=other.colno_p;

            other.br = nullptr;
            other.s_br = 0;
            other.e_br = 0;
            other.p_br = 0;
            other.b8 = nullptr;
            other.s_b8 = 0;
            other.e_b8 = 0;
            other.p_b8 = 0;
            other.pp_b8 = 0;
            other.reset_pos();
            other.reset_pos_p();
        }
        return *this;
    }

    ~BufferedInput() noexcept {free_br(br);free_b8(b8);}

    /// @note Do not resize smaller than `e_br-p_br`!
    void resize_raw_buffer(size_t size_new){
        if(size_new!=s_br){
            assert(size_new>=e_br-p_br);
            unsigned char* br_new = allocate_br(size_new);
            std::memcpy(br_new, br+p_br, e_br-p_br);
            e_br -= p_br;
            p_br = 0;
            br = br_new;
            s_br = size_new;
        }
    }

    /// @note Do not resize smaller than `e_b8-p_b8`!
    void resize_u8_buffer(size_t size_new){
        if(size_new!=s_b8){
            assert(size_new>=e_b8-p_b8);
            char* b8_new = allocate_b8(size_new);
            std::memcpy(b8_new, b8+p_b8, e_b8-p_b8);
            if(pp_b8<p_b8)
                pp_b8 = p_b8;
            e_b8 -= p_b8;
            pp_b8 -= p_b8;
            p_b8 = 0;
            b8 = b8_new;
            s_b8 = size_new;
        }
    }

    size_t fill_raw_buffer(){
        std::memmove(br, br+p_br, e_br-p_br);
        e_br -= p_br;
        p_br = 0;
        return e_br+=Input::get_raw(br+e_br, 1, s_br-e_br);
    }

    void realign_u8_buffer(){
        if(pp_b8<p_b8)
            pp_b8 = p_b8;
        std::memmove(b8, b8+p_b8, e_b8-p_b8);
        e_b8 -= p_b8;
        pp_b8 -= p_b8;
        p_b8 = 0;
    }

    size_t raw_buffer_size() const {return s_br;}
    size_t raw_data_size() const {return e_br-p_br;}

    size_t u8_buffer_size() const {return s_b8;}
    size_t u8_data_size() const {return e_b8-p_b8;}

    static constexpr size_t RAW_BUFFER_SIZE_DEFAULT = 256*1024;
    static constexpr size_t U8_BUFFER_SIZE_DEFAULT = 4096;
  public:
    template<typename C>
    size_t get_raw(C* buf,size_t size,size_t count){
        static_assert(yuki::is_char_or_uchar_v_<C>);

        if(read_directly())
            return Input::get_raw(buf,size,count);
        else{
            if(s_br<size)
                resize_raw_buffer(size<RAW_BUFFER_SIZE_DEFAULT ? RAW_BUFFER_SIZE_DEFAULT : size);
            for(size_t i = 0;i<count;++i){
                if(size>e_br-p_br && fill_raw_buffer()<size)
                    return i;
                else{
                    yuki::char_copy(buf, br+p_br ,size);
                    buf+=size;
                    p_br+=size;
                }
            }
            return count;
        }
    }

    int get_raw(){
        if(read_directly())
            return Input::get_raw();
        else if(e_br-p_br>0 || fill_raw_buffer()!=0)
            return br[p_br++];
        else
            return EOF;
    }

    int peek_raw(){
        if(read_directly())
            return Input::peek_raw();
        else if(e_br-p_br>0 || fill_raw_buffer()!=0)
            return br[p_br];
        else
            return EOF;
    }

    yuki::U8Char get_u8(){
        using namespace yuki::literals;
        yuki::U8Char u8c;
        if(p_b8!=e_b8){
            unsigned l = yuki::u8_length(b8[p_b8]);
            p_b8+=l;
            u8c.set(b8+(p_b8-l));
        }else{
            u8c = get_u8_from_br_input();
        }

        if(u8c!=yuki::EOF_U8){
            if(u8c=='\n'_u8){
                ++lineno;
                colno=1;
            }else
                ++colno;
        }
        return u8c;
    }

    yuki::U8Char peek_u8(){
        if(p_b8!=e_b8)
            return yuki::U8Char(b8+p_b8);

        yuki::U8Char u8c = get_u8_from_br_input();
        if(u8c==yuki::EOF_U8)
            return yuki::EOF_U8;

        if(e_b8+u8c.length()>s_b8)
            resize_u8_buffer(2*s_b8 < U8_BUFFER_SIZE_DEFAULT ? U8_BUFFER_SIZE_DEFAULT : 2*s_b8);
        u8c.write_to(b8+e_b8);
        e_b8+=u8c.length();
        return u8c;
    }

    yuki::U8Char peek_u8_cons(){
        if(pp_b8<p_b8)
            pp_b8 = p_b8;

        yuki::U8Char u8c;

        if(pp_b8!=e_b8){
            u8c.set(b8+pp_b8);
            pp_b8+=u8c.length();
        }else{
            u8c = get_u8_from_br_input();
            if(u8c==yuki::EOF_U8)
                return yuki::EOF_U8;

            if(e_b8+u8c.length()>s_b8)
                resize_u8_buffer(2*s_b8 < U8_BUFFER_SIZE_DEFAULT ? U8_BUFFER_SIZE_DEFAULT : 2*s_b8);
            u8c.write_to(b8+e_b8);
            e_b8+=u8c.length();
            pp_b8 = e_b8;
        }

        using namespace yuki::literals;
        assert(u8c!=yuki::EOF_U8);
        if(u8c=='\n'_u8){
            ++lineno_p;
            colno_p=1;
        }else
            ++colno_p;
        return u8c;
    }



    void reset_peek() {pp_b8 = p_b8;lineno_p=lineno;colno_p=colno;}

    std::string_view peeked_so_far_sv() const {return {b8+p_b8,pp_b8-p_b8};}
    std::string peeked_so_far_s() const {return {b8+p_b8,pp_b8-p_b8};}

    /// @note The line terminator is NOT included in the returned string.
    std::string get_line(){
        using namespace yuki::literals;
        yuki::U8Char u8c;
        std::string str;
        char buf[4] = {};
        while(1){
            u8c = get_u8();
            if(u8c==yuki::EOF_U8 || u8c=='\n'_u8)
                return str;
            if(u8c=='\r'_u8){
                u8c = get_u8();
                assert(u8c=='\n'_u8);
                return str;
            }
            std::memset(buf,0,4);
            u8c.write_to(buf);
            str.append(buf,u8c.length());
        }
        return str;
    }

    void reset_lineno() {lineno=1;}
    void reset_colno() {colno=1;}
    void reset_pos() {lineno=1;colno=1;}

    bool at_bol() const {return colno==1;}
    bool at_eol(){
        using namespace yuki::literals;
        yuki::U8Char c = peek_u8();
        return c==yuki::EOF_U8
            || c=='\n'_u8
            || c=='\r'_u8;
    }
    bool at_begin() const {return lineno==1 && colno==1;}
    bool at_eof(){
        if(p_b8=e_b8){
            yuki::U8Char u8c=get_u8_from_br_input();
            if(u8c==yuki::EOF_U8)
                return true;

            if(e_b8+u8c.length()>s_b8)
                resize_u8_buffer(2*s_b8 < U8_BUFFER_SIZE_DEFAULT ? U8_BUFFER_SIZE_DEFAULT : 2*s_b8);
            u8c.write_to(b8+e_b8);
            e_b8+=u8c.length();
        }
        return false;
    }

    void reset_lineno_p() {lineno_p=1;}
    void reset_colno_p() {colno_p=1;}
    void reset_pos_p() {lineno_p=1;colno_p=1;}

    bool at_bol_p() const {return colno_p==1;}
    bool at_eol_p(){
        using namespace yuki::literals;
        yuki::U8Char c = peek_u8_cons();
        if(c==yuki::EOF_U8)
            return true;
        if(c=='\n'_u8 || c=='\r'_u8){
            assert(pp_b8>p_b8);
            --pp_b8;
            return true;
        }
        return false;
    }
    bool at_begin_p() const {return lineno_p==1 && colno_p==1;}
    bool at_eof_p(){
        if(pp_b8==e_b8){
            yuki::U8Char u8c=get_u8_from_br_input();
            if(u8c==yuki::EOF_U8)
                return true;

            if(e_b8+u8c.length()>s_b8)
                resize_u8_buffer(2*s_b8 < U8_BUFFER_SIZE_DEFAULT ? U8_BUFFER_SIZE_DEFAULT : 2*s_b8);
            u8c.write_to(b8+e_b8);
            e_b8+=u8c.length();
            pp_b8 = e_b8;
        }
        return false;
    }

    // The following functions does not affect the current buffer. Better use when EOF is hit.
    void set_source(bool if_reset_pos=true) {Input::source_type_ = Source_Type::NIL; if(if_reset_pos) reset_pos();}
    void set_source(FILE* f,bool if_reset_pos=true) {Input::set_source(f); if(if_reset_pos) reset_pos();}
    void set_source(const char* s,bool if_reset_pos=true) {p_br = e_br;resize_raw_buffer(0);Input::set_source(s); if(if_reset_pos) reset_pos();}
    void set_source(const char* s,size_t sz,bool if_reset_pos=true) {p_br = e_br;resize_raw_buffer(0);Input::set_source(s,sz); if(if_reset_pos) reset_pos();}
    void set_source(const unsigned char* s,bool if_reset_pos=true) {p_br = e_br;resize_raw_buffer(0);Input::set_source(s); if(if_reset_pos) reset_pos();}
    void set_source(const unsigned char* s,size_t sz,bool if_reset_pos=true) {p_br = e_br;resize_raw_buffer(0);Input::set_source(s,sz); if(if_reset_pos) reset_pos();}
    void set_source(Input& in,bool if_reset_pos=true) {Input::set_source(in); if(if_reset_pos) reset_pos();}
  private:
    unsigned char* br;
    size_t s_br;
    size_t e_br;
    size_t p_br;

    char* b8;
    size_t s_b8;
    size_t e_b8;
    size_t p_b8;
    size_t pp_b8;
  public:
    size_t lineno;
    size_t colno;
    size_t lineno_p;
    size_t colno_p;
}; // struct BufferedInput

yuki::U8Char BufferedInput::get_u8_from_br_input(){
    using yuki::U8Char;
    using yuki::to_u8;
    using yuki::encoding;
    using yuki::EOF_U8;

    switch (enc_){
        case encoding::utf8:{
            int c = get_raw();
            if(c==EOF || c>=0xF8)
                return yuki::EOF_U8;
            else{
                switch(yuki::u8_length(c)){
                    case 1 : return U8Char(0,0,0,c);
                    case 2 : {
                        int c1 = get_raw();
                        if(c1!=EOF)
                            return U8Char(0,0,c,c1);
                        break;
                    }
                    case 3 :{
                        if(get_raw(utf8_buf_, 2, 1) == 1)
                            return U8Char(0,c,utf8_buf_[0],utf8_buf_[1]);
                        break;
                    }
                    case 4 : {
                        if(get_raw(utf8_buf_, 3, 1) == 1)
                            return U8Char(c,utf8_buf_[0],utf8_buf_[1],utf8_buf_[2]);
                        break;
                    }
                }
            }
            break;
        }
        case encoding::utf16be:{
            if (get_raw(utf8_buf_, 2, 1) == 1){
                switch(yuki::u16_length(utf8_buf_[0])){
                    case 1 : return to_u8<encoding::utf16be>::convert(0,0,utf8_buf_[0],utf8_buf_[1]);
                    case 2 : {
                        if(get_raw(utf8_buf_+2, 2, 1) == 1)
                            return to_u8<encoding::utf16be>::convert(utf8_buf_[0],utf8_buf_[1],utf8_buf_[2],utf8_buf_[3]);
                        break;
                    }
                }
            }
            break;
        }
        case encoding::utf16le:{
            if (get_raw(utf8_buf_, 2, 1) == 1){
                switch(yuki::u16_length(utf8_buf_[1])){
                    case 1 : return to_u8<encoding::utf16le>::convert(0,0,utf8_buf_[0],utf8_buf_[1]);
                    case 2 : {
                        if(get_raw(utf8_buf_+2, 2, 1) == 1)
                            return to_u8<encoding::utf16le>::convert(utf8_buf_[0],utf8_buf_[1],utf8_buf_[2],utf8_buf_[3]);
                        break;
                    }
                }
            }
            break;
        }
        case encoding::utf32be:{
            if (get_raw(utf8_buf_, 4, 1) == 1)
                return to_u8<encoding::utf32be>::convert(utf8_buf_[0],utf8_buf_[1],utf8_buf_[2],utf8_buf_[3]);
            break;
        }
        case encoding::utf32le:{
            if (get_raw(utf8_buf_, 4, 1) == 1)
                return to_u8<encoding::utf32le>::convert(utf8_buf_[0],utf8_buf_[1],utf8_buf_[2],utf8_buf_[3]);
            break;
        }
        case encoding::latin1:{
            int c = get_raw();
            if(c!=EOF)
                return to_u8<encoding::latin1>::convert(c);
            break;
        }
        case encoding::custom:{
            int c = get_raw();
            if(c!=EOF)
                return to_u8<encoding::custom>::convert(c,cp_);
            break;
        }
        #ifdef YUKI_LEX_WITH_RARE_ENCODINGS
        case encoding::cp437:
        case encoding::cp850:
        case encoding::cp858:
        case encoding::ebcdic:
        case encoding::cp1250:
        case encoding::cp1251:
        case encoding::cp1252:
        case encoding::cp1253:
        case encoding::cp1254:
        case encoding::cp1255:
        case encoding::cp1256:
        case encoding::cp1257:
        case encoding::cp1258:
        case encoding::iso8859_2:
        case encoding::iso8859_3:
        case encoding::iso8859_4:
        case encoding::iso8859_5:
        case encoding::iso8859_6:
        case encoding::iso8859_7:
        case encoding::iso8859_8:
        case encoding::iso8859_9:
        case encoding::iso8859_10:
        case encoding::iso8859_11:
        case encoding::iso8859_13:
        case encoding::iso8859_14:
        case encoding::iso8859_15:
        case encoding::iso8859_16:
        case encoding::macroman:
        case encoding::koi8_r:
        case encoding::koi8_u:
        case encoding::koi8_ru:
        #endif
        default:;
    }
    return yuki::EOF_U8;
} // yuki::U8Char BufferedInput::get_u8_from_br_input()
} // namespace yuki::lex
