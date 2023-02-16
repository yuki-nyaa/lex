#pragma once
#include<yuki/unicode.hpp>

namespace yuki::lex{

template<typename I>
yuki::U8Char get_u8(I& input){
    if(const int c=input.get(); c!=EOF){
        unsigned char utf8_buf[4];
        switch(yuki::u8_length(c)){
            case 1: return yuki::U8Char(0,0,0,c);
            case 2:{
                assert(input.getable());
                return yuki::U8Char(0,0,c,input.get());
            }
            case 3:{
                const size_t read=input.read(utf8_buf,1,2);
                assert(read==2);
                return yuki::U8Char(0,c,utf8_buf[0],utf8_buf[1]);
            }
            case 4:{
                const size_t read=input.read(utf8_buf,1,3);
                assert(read==3);
                return yuki::U8Char(c,utf8_buf[0],utf8_buf[1],utf8_buf[2]);
            }
            default: assert(false);
        }
    }
    return yuki::EOF_U8;
}

template<typename I>
yuki::U8Char get_u8(I& input,const yuki::encoding enc,yuki::codepage_t* const cp){
    using yuki::U8Char;
    using yuki::to_u8;
    using yuki::encoding;
    unsigned char utf8_buf[4];
    switch(enc){
        case encoding::utf8: return get_u8(input);
        case encoding::utf16be:{
            switch(input.read(utf8_buf,1,2)){
                case 0: return yuki::EOF_U8;
                case 1: assert(false);
                case 2:{
                    switch(yuki::u16_length(utf8_buf[0])){
                        case 1: return to_u8<encoding::utf16be>::convert(0,0,utf8_buf[0],utf8_buf[1]);
                        case 2:{
                            const size_t read1 = input.read(utf8_buf+2,1,2);
                            assert(read1==2);
                            return to_u8<encoding::utf16be>::convert(utf8_buf[0],utf8_buf[1],utf8_buf[2],utf8_buf[3]);
                        }
                        default: assert(false);
                    }
                }
            }
            break;
        }
        case encoding::utf16le:{
            switch(input.read(utf8_buf,1,2)){
                case 0: return yuki::EOF_U8;
                case 1: assert(false);
                case 2:{
                    switch(yuki::u16_length(utf8_buf[1])){
                        case 1: return to_u8<encoding::utf16le>::convert(0,0,utf8_buf[0],utf8_buf[1]);
                        case 2:{
                            const size_t read1 = input.read(utf8_buf+2,1,2);
                            assert(read1==2);
                            return to_u8<encoding::utf16le>::convert(utf8_buf[0],utf8_buf[1],utf8_buf[2],utf8_buf[3]);
                        }
                        default: assert(false);
                    }
                }
            }
            break;
        }
        case encoding::utf32be:{
            switch(input.read(utf8_buf,1,4)){
                case 0: return yuki::EOF_U8;
                case 4: return to_u8<encoding::utf32be>::convert(utf8_buf[0],utf8_buf[1],utf8_buf[2],utf8_buf[3]);
                default: assert(false);
            }
            break;
        }
        case encoding::utf32le:{
            switch(input.read(utf8_buf,1,4)){
                case 0: return yuki::EOF_U8;
                case 4: return to_u8<encoding::utf32le>::convert(utf8_buf[0],utf8_buf[1],utf8_buf[2],utf8_buf[3]);
                default: assert(false);
            }
            break;
        }
        case encoding::latin1:{
            if(const int c=input.get(); c!=EOF)
                return to_u8<encoding::latin1>::convert(c);
            break;
        }
        case encoding::custom:{
            if(const int c=input.get(); c!=EOF)
                return to_u8<encoding::custom>::convert(c,cp);
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
} // yuki::U8Char get_u8(I& input,const yuki::encoding enc,yuki::codepage_t* const cp)


template<typename I>
struct With_Enc : protected I{
  protected:
    using I::enc_;
    yuki::codepage_t* cp_;
  private:
    struct private_ctor_tag_ {};
    template<typename... Args>
    constexpr With_Enc(private_ctor_tag_,const yuki::encoding enc,yuki::codepage_t* const cp,Args&&... args) noexcept :
        I(std::forward<Args>(args)...),
        cp_(cp)
    {
        assert(enc==yuki::encoding::custom || cp==nullptr); // Predefined encoding must NOT come with custom codepage.
        assert(enc!=yuki::encoding::custom || cp!=nullptr); // Custom encoding must come with custom codepage.
        assert((enc!=yuki::encoding::utf32be && enc!=yuki::encoding::utf32le) || I::get_source_type()!=I::Source_Type::S); // Since UTF-32 naturally contains lots of null bytes, determining end of input by null byte does not work.
        enc_=enc;
    }
  public:
    constexpr With_Enc() noexcept :
        I(),
        cp_(nullptr)
    {}

    constexpr With_Enc(const yuki::encoding enc,yuki::codepage_t* const cp=nullptr) noexcept :
        With_Enc(private_ctor_tag_{},enc,cp)
    {}

    template<typename T,typename=std::enable_if_t<std::is_constructible_v<I,T&&>>>
    constexpr With_Enc(T&& t,const yuki::encoding enc=yuki::encoding::utf8,yuki::codepage_t* const cp=nullptr) noexcept :
        With_Enc(private_ctor_tag_{},enc,cp,std::forward<T>(t))
    {}

    template<typename T,typename U,typename=std::enable_if_t<std::is_constructible_v<I,T&&,U&&>>>
    constexpr With_Enc(T&& t,U&& u,const yuki::encoding enc=yuki::encoding::utf8,yuki::codepage_t* const cp=nullptr) noexcept :
        With_Enc(private_ctor_tag_{},enc,cp,std::forward<T>(t),std::forward<U>(u))
    {}

    constexpr yuki::encoding get_encoding() const {return enc_;}

    constexpr void set_encoding(const yuki::encoding enc,yuki::codepage_t* const cp=nullptr){
        assert(enc==yuki::encoding::custom || cp==nullptr); // Predefined encoding must NOT come with custom codepage.
        assert(enc!=yuki::encoding::custom || cp!=nullptr); // Custom encoding must come with custom codepage.
        assert((enc!=yuki::encoding::utf32be && enc!=yuki::encoding::utf32le) || I::get_source_type()!=I::Source_Type::S); // Since UTF-32 naturally contains lots of null bytes, determining end of input by null byte does not work.
        enc_=enc;
        cp_ =cp;
    }

    constexpr yuki::codepage_t* get_page() const {return cp_;}

    yuki::U8Char get_u8() {return yuki::lex::get_u8(static_cast<I&>(*this),enc_,cp_);}
}; // struct With_Enc
} // namespace yuki::lex
