
#include"cconfig"
#include<yuki/algorithm.hpp>
#include<cstdlib>
#include<yuki/lex/common.hpp>
#include<yuki/uchar.hpp>
#include"gen/Meta_Lexer.h"

namespace yuki::lex{
template<typename I>
size_t Meta_Lexer_fsm_codes::INITIAL(I& in,typename I::Pos* const heads) noexcept {
    using namespace yuki::literals;
    decltype(in.get()) c;
    size_t cap=0;
    const typename I::Pos pos_begin=in.get_pos();
    typename I::Pos pos_take=in.get_pos();
    (void)heads;
  S0:
    c=in.get();
    if((c>='\t'_u8 && c<='\r'_u8)
    || (c==' '_u8)
    || (c==0x85_u8/**/)
    || (c==0xA0_u8/* */)
    || (c==0x1680_u8/* */)
    || (c>=0x2000_u8/* */ && c<=0x200A_u8/* */)
    || (c==0x2028_u8/*LS*/ || c==0x2029_u8/*PS*/)
    || (c==0x202F_u8/* */)
    || (c==0x205F_u8/* */)
    || (c==0x3000_u8/*　*/)) goto S1;
    if((c=='%'_u8)) goto S2;
    if((c=='/'_u8)) goto S3;
    if((c>='A'_u8 && c<='Z'_u8)
    || (c=='_'_u8)
    || (c>='a'_u8 && c<='z'_u8)) goto S4;
    in.set_pos(pos_take); return cap;
  S1:
    cap=14; pos_take=in.get_pos();
    c=in.get();
    if((c>='\t'_u8 && c<='\r'_u8)
    || (c==' '_u8)
    || (c==0x85_u8/**/)
    || (c==0xA0_u8/* */)
    || (c==0x1680_u8/* */)
    || (c>=0x2000_u8/* */ && c<=0x200A_u8/* */)
    || (c==0x2028_u8/*LS*/ || c==0x2029_u8/*PS*/)
    || (c==0x202F_u8/* */)
    || (c==0x205F_u8/* */)
    || (c==0x3000_u8/*　*/)) goto S1;
    in.set_pos(pos_take); return cap;
  S2:
    c=in.get();
    if((c=='%'_u8)) goto S5;
    if((c=='c'_u8)) goto S6;
    if((c=='d'_u8)) goto S7;
    if((c=='f'_u8)) goto S8;
    if((c=='i'_u8)) goto S9;
    if((c=='l'_u8)) goto S10;
    if((c=='n'_u8)) goto S11;
    if((c=='t'_u8)) goto S12;
    in.set_pos(pos_take); return cap;
  S3:
    c=in.get();
    if((c=='/'_u8)) goto S13;
    in.set_pos(pos_take); return cap;
  S4:
    cap=12; pos_take=in.get_pos();
    c=in.get();
    if((c>='0'_u8 && c<='9'_u8)
    || (c>='A'_u8 && c<='Z'_u8)
    || (c=='_'_u8)
    || (c>='a'_u8 && c<='z'_u8)) goto S14;
    in.set_pos(pos_take); return cap;
  S5:
    cap=13; pos_take=in.get_pos();
    c=in.get();
    if((c>='\t'_u8 && c<='\r'_u8)
    || (c==' '_u8)
    || (c==0x85_u8/**/)
    || (c==0xA0_u8/* */)
    || (c==0x1680_u8/* */)
    || (c>=0x2000_u8/* */ && c<=0x200A_u8/* */)
    || (c==0x2028_u8/*LS*/ || c==0x2029_u8/*PS*/)
    || (c==0x202F_u8/* */)
    || (c==0x205F_u8/* */)
    || (c==0x3000_u8/*　*/)) goto S15;
    in.set_pos(pos_take); return cap;
  S6:
    c=in.get();
    if((c=='o'_u8)) goto S16;
    in.set_pos(pos_take); return cap;
  S7:
    c=in.get();
    if((c=='e'_u8)) goto S17;
    in.set_pos(pos_take); return cap;
  S8:
    c=in.get();
    if((c=='s'_u8)) goto S18;
    in.set_pos(pos_take); return cap;
  S9:
    c=in.get();
    if((c=='n'_u8)) goto S19;
    in.set_pos(pos_take); return cap;
  S10:
    c=in.get();
    if((c=='e'_u8)) goto S20;
    in.set_pos(pos_take); return cap;
  S11:
    c=in.get();
    if((c=='a'_u8)) goto S21;
    if((c=='o'_u8)) goto S22;
    in.set_pos(pos_take); return cap;
  S12:
    c=in.get();
    if((c=='o'_u8)) goto S23;
    if((c=='e'_u8)) goto S24;
    in.set_pos(pos_take); return cap;
  S13:
    c=in.get();
    if((c<='\t'_u8)
    || (c=='\v'_u8 || c=='\f'_u8)
    || (c>=0xE_u8 && c<=0x10FFFF_u8/*􏿿*/)) goto S25;
    if((c=='\n'_u8)
    || (c=='\r'_u8)) goto S26;
    in.set_pos(pos_take); return cap;
  S14:
    cap=12; pos_take=in.get_pos();
    c=in.get();
    if((c>='0'_u8 && c<='9'_u8)
    || (c>='A'_u8 && c<='Z'_u8)
    || (c=='_'_u8)
    || (c>='a'_u8 && c<='z'_u8)) goto S14;
    in.set_pos(pos_take); return cap;
  S15:
    cap=13; pos_take=in.get_pos();
    c=in.get();
    if((c>='\t'_u8 && c<='\r'_u8)
    || (c==' '_u8)
    || (c==0x85_u8/**/)
    || (c==0xA0_u8/* */)
    || (c==0x1680_u8/* */)
    || (c>=0x2000_u8/* */ && c<=0x200A_u8/* */)
    || (c==0x2028_u8/*LS*/ || c==0x2029_u8/*PS*/)
    || (c==0x202F_u8/* */)
    || (c==0x205F_u8/* */)
    || (c==0x3000_u8/*　*/)) goto S15;
    in.set_pos(pos_take); return cap;
  S16:
    c=in.get();
    if((c=='d'_u8)) goto S27;
    in.set_pos(pos_take); return cap;
  S17:
    c=in.get();
    if((c=='b'_u8)) goto S28;
    in.set_pos(pos_take); return cap;
  S18:
    c=in.get();
    if((c=='m'_u8)) goto S29;
    in.set_pos(pos_take); return cap;
  S19:
    c=in.get();
    if((c=='p'_u8)) goto S30;
    in.set_pos(pos_take); return cap;
  S20:
    c=in.get();
    if((c=='x'_u8)) goto S31;
    in.set_pos(pos_take); return cap;
  S21:
    c=in.get();
    if((c=='m'_u8)) goto S32;
    in.set_pos(pos_take); return cap;
  S22:
    c=in.get();
    if((c=='-'_u8)
    || (c=='_'_u8)) goto S33;
    in.set_pos(pos_take); return cap;
  S23:
    c=in.get();
    if((c=='k'_u8)) goto S34;
    in.set_pos(pos_take); return cap;
  S24:
    c=in.get();
    if((c=='m'_u8)) goto S35;
    in.set_pos(pos_take); return cap;
  S25:
    c=in.get();
    if((c<='\t'_u8)
    || (c=='\v'_u8 || c=='\f'_u8)
    || (c>=0xE_u8 && c<=0x10FFFF_u8/*􏿿*/)) goto S25;
    if((c=='\n'_u8)
    || (c=='\r'_u8)) goto S26;
    in.set_pos(pos_take); return cap;
  S26:
    cap=15; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S27:
    c=in.get();
    if((c=='e'_u8)) goto S36;
    in.set_pos(pos_take); return cap;
  S28:
    c=in.get();
    if((c=='u'_u8)) goto S37;
    in.set_pos(pos_take); return cap;
  S29:
    c=in.get();
    if((c=='-'_u8)
    || (c=='_'_u8)) goto S38;
    in.set_pos(pos_take); return cap;
  S30:
    c=in.get();
    if((c=='u'_u8)) goto S39;
    in.set_pos(pos_take); return cap;
  S31:
    c=in.get();
    if((c=='e'_u8)) goto S40;
    in.set_pos(pos_take); return cap;
  S32:
    c=in.get();
    if((c=='e'_u8)) goto S41;
    in.set_pos(pos_take); return cap;
  S33:
    c=in.get();
    if((c=='d'_u8)) goto S42;
    in.set_pos(pos_take); return cap;
  S34:
    c=in.get();
    if((c=='e'_u8)) goto S43;
    in.set_pos(pos_take); return cap;
  S35:
    c=in.get();
    if((c=='p'_u8)) goto S44;
    in.set_pos(pos_take); return cap;
  S36:
    cap=11; pos_take=in.get_pos();
    c=in.get();
    if((c>='\t'_u8 && c<='\r'_u8)
    || (c==' '_u8)
    || (c==0x85_u8/**/)
    || (c==0xA0_u8/* */)
    || (c==0x1680_u8/* */)
    || (c>=0x2000_u8/* */ && c<=0x200A_u8/* */)
    || (c==0x2028_u8/*LS*/ || c==0x2029_u8/*PS*/)
    || (c==0x202F_u8/* */)
    || (c==0x205F_u8/* */)
    || (c==0x3000_u8/*　*/)) goto S45;
    in.set_pos(pos_take); return cap;
  S37:
    c=in.get();
    if((c=='g'_u8)) goto S46;
    in.set_pos(pos_take); return cap;
  S38:
    c=in.get();
    if((c=='c'_u8)) goto S47;
    in.set_pos(pos_take); return cap;
  S39:
    c=in.get();
    if((c=='t'_u8)) goto S48;
    in.set_pos(pos_take); return cap;
  S40:
    c=in.get();
    if((c=='r'_u8)) goto S49;
    in.set_pos(pos_take); return cap;
  S41:
    c=in.get();
    if((c=='s'_u8)) goto S50;
    in.set_pos(pos_take); return cap;
  S42:
    c=in.get();
    if((c=='e'_u8)) goto S51;
    in.set_pos(pos_take); return cap;
  S43:
    c=in.get();
    if((c=='n'_u8)) goto S52;
    in.set_pos(pos_take); return cap;
  S44:
    c=in.get();
    if((c=='l'_u8)) goto S53;
    in.set_pos(pos_take); return cap;
  S45:
    cap=11; pos_take=in.get_pos();
    c=in.get();
    if((c>='\t'_u8 && c<='\r'_u8)
    || (c==' '_u8)
    || (c==0x85_u8/**/)
    || (c==0xA0_u8/* */)
    || (c==0x1680_u8/* */)
    || (c>=0x2000_u8/* */ && c<=0x200A_u8/* */)
    || (c==0x2028_u8/*LS*/ || c==0x2029_u8/*PS*/)
    || (c==0x202F_u8/* */)
    || (c==0x205F_u8/* */)
    || (c==0x3000_u8/*　*/)) goto S45;
    in.set_pos(pos_take); return cap;
  S46:
    c=in.get();
    if((c=='-'_u8)
    || (c=='_'_u8)) goto S54;
    in.set_pos(pos_take); return cap;
  S47:
    c=in.get();
    if((c=='o'_u8)) goto S55;
    in.set_pos(pos_take); return cap;
  S48:
    c=in.get();
    if((c=='-'_u8)
    || (c=='_'_u8)) goto S56;
    in.set_pos(pos_take); return cap;
  S49:
    cap=2; pos_take=in.get_pos();
    c=in.get();
    if((c>='\t'_u8 && c<='\r'_u8)
    || (c==' '_u8)
    || (c==0x85_u8/**/)
    || (c==0xA0_u8/* */)
    || (c==0x1680_u8/* */)
    || (c>=0x2000_u8/* */ && c<=0x200A_u8/* */)
    || (c==0x2028_u8/*LS*/ || c==0x2029_u8/*PS*/)
    || (c==0x202F_u8/* */)
    || (c==0x205F_u8/* */)
    || (c==0x3000_u8/*　*/)) goto S57;
    in.set_pos(pos_take); return cap;
  S50:
    c=in.get();
    if((c=='p'_u8)) goto S58;
    in.set_pos(pos_take); return cap;
  S51:
    c=in.get();
    if((c=='f'_u8)) goto S59;
    in.set_pos(pos_take); return cap;
  S52:
    c=in.get();
    if((c=='-'_u8)
    || (c=='_'_u8)) goto S60;
    in.set_pos(pos_take); return cap;
  S53:
    c=in.get();
    if((c=='a'_u8)) goto S61;
    in.set_pos(pos_take); return cap;
  S54:
    c=in.get();
    if((c=='p'_u8)) goto S62;
    in.set_pos(pos_take); return cap;
  S55:
    c=in.get();
    if((c=='d'_u8)) goto S63;
    in.set_pos(pos_take); return cap;
  S56:
    c=in.get();
    if((c=='c'_u8)) goto S64;
    if((c=='h'_u8)) goto S65;
    in.set_pos(pos_take); return cap;
  S57:
    cap=2; pos_take=in.get_pos();
    c=in.get();
    if((c>='\t'_u8 && c<='\r'_u8)
    || (c==' '_u8)
    || (c==0x85_u8/**/)
    || (c==0xA0_u8/* */)
    || (c==0x1680_u8/* */)
    || (c>=0x2000_u8/* */ && c<=0x200A_u8/* */)
    || (c==0x2028_u8/*LS*/ || c==0x2029_u8/*PS*/)
    || (c==0x202F_u8/* */)
    || (c==0x205F_u8/* */)
    || (c==0x3000_u8/*　*/)) goto S57;
    in.set_pos(pos_take); return cap;
  S58:
    c=in.get();
    if((c=='a'_u8)) goto S66;
    in.set_pos(pos_take); return cap;
  S59:
    c=in.get();
    if((c=='a'_u8)) goto S67;
    in.set_pos(pos_take); return cap;
  S60:
    c=in.get();
    if((c=='t'_u8)) goto S68;
    in.set_pos(pos_take); return cap;
  S61:
    c=in.get();
    if((c=='t'_u8)) goto S69;
    in.set_pos(pos_take); return cap;
  S62:
    c=in.get();
    if((c=='r'_u8)) goto S70;
    in.set_pos(pos_take); return cap;
  S63:
    c=in.get();
    if((c=='e'_u8)) goto S71;
    in.set_pos(pos_take); return cap;
  S64:
    c=in.get();
    if((c=='l'_u8)) goto S72;
    in.set_pos(pos_take); return cap;
  S65:
    c=in.get();
    if((c=='e'_u8)) goto S73;
    in.set_pos(pos_take); return cap;
  S66:
    c=in.get();
    if((c=='c'_u8)) goto S74;
    in.set_pos(pos_take); return cap;
  S67:
    c=in.get();
    if((c=='u'_u8)) goto S75;
    in.set_pos(pos_take); return cap;
  S68:
    c=in.get();
    if((c=='y'_u8)) goto S76;
    in.set_pos(pos_take); return cap;
  S69:
    c=in.get();
    if((c=='e'_u8)) goto S77;
    in.set_pos(pos_take); return cap;
  S70:
    c=in.get();
    if((c=='e'_u8)) goto S78;
    in.set_pos(pos_take); return cap;
  S71:
    c=in.get();
    if((c=='s'_u8)) goto S79;
    in.set_pos(pos_take); return cap;
  S72:
    c=in.get();
    if((c=='a'_u8)) goto S80;
    in.set_pos(pos_take); return cap;
  S73:
    c=in.get();
    if((c=='a'_u8)) goto S81;
    in.set_pos(pos_take); return cap;
  S74:
    c=in.get();
    if((c=='e'_u8)) goto S82;
    in.set_pos(pos_take); return cap;
  S75:
    c=in.get();
    if((c=='l'_u8)) goto S83;
    in.set_pos(pos_take); return cap;
  S76:
    c=in.get();
    if((c=='p'_u8)) goto S84;
    in.set_pos(pos_take); return cap;
  S77:
    c=in.get();
    if((c>='\t'_u8 && c<='\r'_u8)
    || (c==' '_u8)
    || (c==0x85_u8/**/)
    || (c==0xA0_u8/* */)
    || (c==0x1680_u8/* */)
    || (c>=0x2000_u8/* */ && c<=0x200A_u8/* */)
    || (c==0x2028_u8/*LS*/ || c==0x2029_u8/*PS*/)
    || (c==0x202F_u8/* */)
    || (c==0x205F_u8/* */)
    || (c==0x3000_u8/*　*/)) goto S85;
    if((c=='<'_u8)) goto S86;
    if((c=='d'_u8)) goto S87;
    in.set_pos(pos_take); return cap;
  S78:
    c=in.get();
    if((c=='f'_u8)) goto S88;
    in.set_pos(pos_take); return cap;
  S79:
    c=in.get();
    if((c=='-'_u8)
    || (c=='_'_u8)) goto S89;
    in.set_pos(pos_take); return cap;
  S80:
    c=in.get();
    if((c=='s'_u8)) goto S90;
    in.set_pos(pos_take); return cap;
  S81:
    c=in.get();
    if((c=='d'_u8)) goto S91;
    in.set_pos(pos_take); return cap;
  S82:
    cap=1; pos_take=in.get_pos();
    c=in.get();
    if((c>='\t'_u8 && c<='\r'_u8)
    || (c==' '_u8)
    || (c==0x85_u8/**/)
    || (c==0xA0_u8/* */)
    || (c==0x1680_u8/* */)
    || (c>=0x2000_u8/* */ && c<=0x200A_u8/* */)
    || (c==0x2028_u8/*LS*/ || c==0x2029_u8/*PS*/)
    || (c==0x202F_u8/* */)
    || (c==0x205F_u8/* */)
    || (c==0x3000_u8/*　*/)) goto S92;
    in.set_pos(pos_take); return cap;
  S83:
    c=in.get();
    if((c=='t'_u8)) goto S93;
    in.set_pos(pos_take); return cap;
  S84:
    c=in.get();
    if((c=='e'_u8)) goto S94;
    in.set_pos(pos_take); return cap;
  S85:
    c=in.get();
    if((c>='\t'_u8 && c<='\r'_u8)
    || (c==' '_u8)
    || (c==0x85_u8/**/)
    || (c==0xA0_u8/* */)
    || (c==0x1680_u8/* */)
    || (c>=0x2000_u8/* */ && c<=0x200A_u8/* */)
    || (c==0x2028_u8/*LS*/ || c==0x2029_u8/*PS*/)
    || (c==0x202F_u8/* */)
    || (c==0x205F_u8/* */)
    || (c==0x3000_u8/*　*/)) goto S85;
    if((c=='<'_u8)) goto S86;
    in.set_pos(pos_take); return cap;
  S86:
    cap=9; pos_take=in.get_pos();
    c=in.get();
    if((c<='\t'_u8)
    || (c=='\v'_u8 || c=='\f'_u8)
    || (c>=0xE_u8 && c<=0x10FFFF_u8/*􏿿*/)) goto S95;
    in.set_pos(pos_take); return cap;
  S87:
    c=in.get();
    if((c=='-'_u8)
    || (c=='_'_u8)) goto S96;
    in.set_pos(pos_take); return cap;
  S88:
    c=in.get();
    if((c=='i'_u8)) goto S97;
    in.set_pos(pos_take); return cap;
  S89:
    c=in.get();
    if((c=='n'_u8)) goto S98;
    in.set_pos(pos_take); return cap;
  S90:
    c=in.get();
    if((c=='s'_u8)) goto S99;
    in.set_pos(pos_take); return cap;
  S91:
    c=in.get();
    if((c=='e'_u8)) goto S100;
    in.set_pos(pos_take); return cap;
  S92:
    cap=1; pos_take=in.get_pos();
    c=in.get();
    if((c>='\t'_u8 && c<='\r'_u8)
    || (c==' '_u8)
    || (c==0x85_u8/**/)
    || (c==0xA0_u8/* */)
    || (c==0x1680_u8/* */)
    || (c>=0x2000_u8/* */ && c<=0x200A_u8/* */)
    || (c==0x2028_u8/*LS*/ || c==0x2029_u8/*PS*/)
    || (c==0x202F_u8/* */)
    || (c==0x205F_u8/* */)
    || (c==0x3000_u8/*　*/)) goto S92;
    in.set_pos(pos_take); return cap;
  S93:
    c=in.get();
    if((c=='-'_u8)
    || (c=='_'_u8)) goto S101;
    in.set_pos(pos_take); return cap;
  S94:
    cap=7; pos_take=in.get_pos();
    c=in.get();
    if((c>='\t'_u8 && c<='\r'_u8)
    || (c==' '_u8)
    || (c==0x85_u8/**/)
    || (c==0xA0_u8/* */)
    || (c==0x1680_u8/* */)
    || (c>=0x2000_u8/* */ && c<=0x200A_u8/* */)
    || (c==0x2028_u8/*LS*/ || c==0x2029_u8/*PS*/)
    || (c==0x202F_u8/* */)
    || (c==0x205F_u8/* */)
    || (c==0x3000_u8/*　*/)) goto S102;
    in.set_pos(pos_take); return cap;
  S95:
    cap=9; pos_take=in.get_pos();
    c=in.get();
    if((c<='\t'_u8)
    || (c=='\v'_u8 || c=='\f'_u8)
    || (c>=0xE_u8 && c<=0x10FFFF_u8/*􏿿*/)) goto S95;
    in.set_pos(pos_take); return cap;
  S96:
    c=in.get();
    if((c=='l'_u8)) goto S103;
    in.set_pos(pos_take); return cap;
  S97:
    c=in.get();
    if((c=='x'_u8)) goto S104;
    in.set_pos(pos_take); return cap;
  S98:
    c=in.get();
    if((c=='a'_u8)) goto S105;
    in.set_pos(pos_take); return cap;
  S99:
    cap=3; pos_take=in.get_pos();
    c=in.get();
    if((c>='\t'_u8 && c<='\r'_u8)
    || (c==' '_u8)
    || (c==0x85_u8/**/)
    || (c==0xA0_u8/* */)
    || (c==0x1680_u8/* */)
    || (c>=0x2000_u8/* */ && c<=0x200A_u8/* */)
    || (c==0x2028_u8/*LS*/ || c==0x2029_u8/*PS*/)
    || (c==0x202F_u8/* */)
    || (c==0x205F_u8/* */)
    || (c==0x3000_u8/*　*/)) goto S106;
    in.set_pos(pos_take); return cap;
  S100:
    c=in.get();
    if((c=='r'_u8)) goto S107;
    in.set_pos(pos_take); return cap;
  S101:
    c=in.get();
    if((c=='c'_u8)) goto S108;
    in.set_pos(pos_take); return cap;
  S102:
    cap=7; pos_take=in.get_pos();
    c=in.get();
    if((c>='\t'_u8 && c<='\r'_u8)
    || (c==' '_u8)
    || (c==0x85_u8/**/)
    || (c==0xA0_u8/* */)
    || (c==0x1680_u8/* */)
    || (c>=0x2000_u8/* */ && c<=0x200A_u8/* */)
    || (c==0x2028_u8/*LS*/ || c==0x2029_u8/*PS*/)
    || (c==0x202F_u8/* */)
    || (c==0x205F_u8/* */)
    || (c==0x3000_u8/*　*/)) goto S102;
    in.set_pos(pos_take); return cap;
  S103:
    c=in.get();
    if((c=='e'_u8)) goto S109;
    in.set_pos(pos_take); return cap;
  S104:
    cap=5; pos_take=in.get_pos();
    c=in.get();
    if((c>='\t'_u8 && c<='\r'_u8)
    || (c==' '_u8)
    || (c==0x85_u8/**/)
    || (c==0xA0_u8/* */)
    || (c==0x1680_u8/* */)
    || (c>=0x2000_u8/* */ && c<=0x200A_u8/* */)
    || (c==0x2028_u8/*LS*/ || c==0x2029_u8/*PS*/)
    || (c==0x202F_u8/* */)
    || (c==0x205F_u8/* */)
    || (c==0x3000_u8/*　*/)) goto S110;
    in.set_pos(pos_take); return cap;
  S105:
    c=in.get();
    if((c=='m'_u8)) goto S111;
    in.set_pos(pos_take); return cap;
  S106:
    cap=3; pos_take=in.get_pos();
    c=in.get();
    if((c>='\t'_u8 && c<='\r'_u8)
    || (c==' '_u8)
    || (c==0x85_u8/**/)
    || (c==0xA0_u8/* */)
    || (c==0x1680_u8/* */)
    || (c>=0x2000_u8/* */ && c<=0x200A_u8/* */)
    || (c==0x2028_u8/*LS*/ || c==0x2029_u8/*PS*/)
    || (c==0x202F_u8/* */)
    || (c==0x205F_u8/* */)
    || (c==0x3000_u8/*　*/)) goto S106;
    in.set_pos(pos_take); return cap;
  S107:
    cap=4; pos_take=in.get_pos();
    c=in.get();
    if((c>='\t'_u8 && c<='\r'_u8)
    || (c==' '_u8)
    || (c==0x85_u8/**/)
    || (c==0xA0_u8/* */)
    || (c==0x1680_u8/* */)
    || (c>=0x2000_u8/* */ && c<=0x200A_u8/* */)
    || (c==0x2028_u8/*LS*/ || c==0x2029_u8/*PS*/)
    || (c==0x202F_u8/* */)
    || (c==0x205F_u8/* */)
    || (c==0x3000_u8/*　*/)) goto S112;
    in.set_pos(pos_take); return cap;
  S108:
    c=in.get();
    if((c=='t'_u8)) goto S113;
    in.set_pos(pos_take); return cap;
  S109:
    c=in.get();
    if((c=='x'_u8)) goto S114;
    in.set_pos(pos_take); return cap;
  S110:
    cap=5; pos_take=in.get_pos();
    c=in.get();
    if((c>='\t'_u8 && c<='\r'_u8)
    || (c==' '_u8)
    || (c==0x85_u8/**/)
    || (c==0xA0_u8/* */)
    || (c==0x1680_u8/* */)
    || (c>=0x2000_u8/* */ && c<=0x200A_u8/* */)
    || (c==0x2028_u8/*LS*/ || c==0x2029_u8/*PS*/)
    || (c==0x202F_u8/* */)
    || (c==0x205F_u8/* */)
    || (c==0x3000_u8/*　*/)) goto S110;
    in.set_pos(pos_take); return cap;
  S111:
    c=in.get();
    if((c=='e'_u8)) goto S115;
    in.set_pos(pos_take); return cap;
  S112:
    cap=4; pos_take=in.get_pos();
    c=in.get();
    if((c>='\t'_u8 && c<='\r'_u8)
    || (c==' '_u8)
    || (c==0x85_u8/**/)
    || (c==0xA0_u8/* */)
    || (c==0x1680_u8/* */)
    || (c>=0x2000_u8/* */ && c<=0x200A_u8/* */)
    || (c==0x2028_u8/*LS*/ || c==0x2029_u8/*PS*/)
    || (c==0x202F_u8/* */)
    || (c==0x205F_u8/* */)
    || (c==0x3000_u8/*　*/)) goto S112;
    in.set_pos(pos_take); return cap;
  S113:
    c=in.get();
    if((c=='o'_u8)) goto S116;
    in.set_pos(pos_take); return cap;
  S114:
    c=in.get();
    if((c=='e'_u8)) goto S117;
    in.set_pos(pos_take); return cap;
  S115:
    c=in.get();
    if((c=='s'_u8)) goto S118;
    in.set_pos(pos_take); return cap;
  S116:
    c=in.get();
    if((c=='r'_u8)) goto S119;
    in.set_pos(pos_take); return cap;
  S117:
    c=in.get();
    if((c=='r'_u8)) goto S120;
    in.set_pos(pos_take); return cap;
  S118:
    c=in.get();
    if((c=='p'_u8)) goto S121;
    in.set_pos(pos_take); return cap;
  S119:
    cap=8; pos_take=in.get_pos();
    c=in.get();
    if((c>='\t'_u8 && c<='\r'_u8)
    || (c==' '_u8)
    || (c==0x85_u8/**/)
    || (c==0xA0_u8/* */)
    || (c==0x1680_u8/* */)
    || (c>=0x2000_u8/* */ && c<=0x200A_u8/* */)
    || (c==0x2028_u8/*LS*/ || c==0x2029_u8/*PS*/)
    || (c==0x202F_u8/* */)
    || (c==0x205F_u8/* */)
    || (c==0x3000_u8/*　*/)) goto S122;
    in.set_pos(pos_take); return cap;
  S120:
    cap=10; pos_take=in.get_pos();
    c=in.get();
    if((c>='\t'_u8 && c<='\r'_u8)
    || (c==' '_u8)
    || (c==0x85_u8/**/)
    || (c==0xA0_u8/* */)
    || (c==0x1680_u8/* */)
    || (c>=0x2000_u8/* */ && c<=0x200A_u8/* */)
    || (c==0x2028_u8/*LS*/ || c==0x2029_u8/*PS*/)
    || (c==0x202F_u8/* */)
    || (c==0x205F_u8/* */)
    || (c==0x3000_u8/*　*/)) goto S123;
    in.set_pos(pos_take); return cap;
  S121:
    c=in.get();
    if((c=='a'_u8)) goto S124;
    in.set_pos(pos_take); return cap;
  S122:
    cap=8; pos_take=in.get_pos();
    c=in.get();
    if((c>='\t'_u8 && c<='\r'_u8)
    || (c==' '_u8)
    || (c==0x85_u8/**/)
    || (c==0xA0_u8/* */)
    || (c==0x1680_u8/* */)
    || (c>=0x2000_u8/* */ && c<=0x200A_u8/* */)
    || (c==0x2028_u8/*LS*/ || c==0x2029_u8/*PS*/)
    || (c==0x202F_u8/* */)
    || (c==0x205F_u8/* */)
    || (c==0x3000_u8/*　*/)) goto S122;
    in.set_pos(pos_take); return cap;
  S123:
    cap=10; pos_take=in.get_pos();
    c=in.get();
    if((c>='\t'_u8 && c<='\r'_u8)
    || (c==' '_u8)
    || (c==0x85_u8/**/)
    || (c==0xA0_u8/* */)
    || (c==0x1680_u8/* */)
    || (c>=0x2000_u8/* */ && c<=0x200A_u8/* */)
    || (c==0x2028_u8/*LS*/ || c==0x2029_u8/*PS*/)
    || (c==0x202F_u8/* */)
    || (c==0x205F_u8/* */)
    || (c==0x3000_u8/*　*/)) goto S123;
    in.set_pos(pos_take); return cap;
  S124:
    c=in.get();
    if((c=='c'_u8)) goto S125;
    in.set_pos(pos_take); return cap;
  S125:
    c=in.get();
    if((c=='e'_u8)) goto S126;
    in.set_pos(pos_take); return cap;
  S126:
    cap=6; pos_take=in.get_pos();
    c=in.get();
    if((c>='\t'_u8 && c<='\r'_u8)
    || (c==' '_u8)
    || (c==0x85_u8/**/)
    || (c==0xA0_u8/* */)
    || (c==0x1680_u8/* */)
    || (c>=0x2000_u8/* */ && c<=0x200A_u8/* */)
    || (c==0x2028_u8/*LS*/ || c==0x2029_u8/*PS*/)
    || (c==0x202F_u8/* */)
    || (c==0x205F_u8/* */)
    || (c==0x3000_u8/*　*/)) goto S127;
    in.set_pos(pos_take); return cap;
  S127:
    cap=6; pos_take=in.get_pos();
    c=in.get();
    if((c>='\t'_u8 && c<='\r'_u8)
    || (c==' '_u8)
    || (c==0x85_u8/**/)
    || (c==0xA0_u8/* */)
    || (c==0x1680_u8/* */)
    || (c>=0x2000_u8/* */ && c<=0x200A_u8/* */)
    || (c==0x2028_u8/*LS*/ || c==0x2029_u8/*PS*/)
    || (c==0x202F_u8/* */)
    || (c==0x205F_u8/* */)
    || (c==0x3000_u8/*　*/)) goto S127;
    in.set_pos(pos_take); return cap;
} // Meta_Lexer_fsm_codes::INITIAL


template<typename I>
size_t Meta_Lexer_fsm_codes::O_NSPACE(I& in,typename I::Pos* const heads) noexcept {
    using namespace yuki::literals;
    decltype(in.get()) c;
    size_t cap=0;
    const typename I::Pos pos_begin=in.get_pos();
    typename I::Pos pos_take=in.get_pos();
    (void)heads;
  S0:
    cap=1; pos_take=in.get_pos();
    c=in.get();
    if((c<='\t'_u8)
    || (c=='\v'_u8 || c=='\f'_u8)
    || (c>=0xE_u8 && c<=0x10FFFF_u8/*􏿿*/)) goto S1;
    in.set_pos(pos_take); return cap;
  S1:
    cap=1; pos_take=in.get_pos();
    c=in.get();
    if((c<='\t'_u8)
    || (c=='\v'_u8 || c=='\f'_u8)
    || (c>=0xE_u8 && c<=0x10FFFF_u8/*􏿿*/)) goto S1;
    in.set_pos(pos_take); return cap;
} // Meta_Lexer_fsm_codes::O_NSPACE


template<typename I>
size_t Meta_Lexer_fsm_codes::O_LEXER(I& in,typename I::Pos* const heads) noexcept {
    using namespace yuki::literals;
    decltype(in.get()) c;
    size_t cap=0;
    const typename I::Pos pos_begin=in.get_pos();
    typename I::Pos pos_take=in.get_pos();
    (void)heads;
  S0:
    cap=1; pos_take=in.get_pos();
    c=in.get();
    if((c<='\t'_u8)
    || (c=='\v'_u8 || c=='\f'_u8)
    || (c>=0xE_u8 && c<=0x10FFFF_u8/*􏿿*/)) goto S1;
    in.set_pos(pos_take); return cap;
  S1:
    cap=1; pos_take=in.get_pos();
    c=in.get();
    if((c<='\t'_u8)
    || (c=='\v'_u8 || c=='\f'_u8)
    || (c>=0xE_u8 && c<=0x10FFFF_u8/*􏿿*/)) goto S1;
    in.set_pos(pos_take); return cap;
} // Meta_Lexer_fsm_codes::O_LEXER


template<typename I>
size_t Meta_Lexer_fsm_codes::O_ICLASS(I& in,typename I::Pos* const heads) noexcept {
    using namespace yuki::literals;
    decltype(in.get()) c;
    size_t cap=0;
    const typename I::Pos pos_begin=in.get_pos();
    typename I::Pos pos_take=in.get_pos();
    (void)heads;
  S0:
    cap=1; pos_take=in.get_pos();
    c=in.get();
    if((c<='\t'_u8)
    || (c=='\v'_u8 || c=='\f'_u8)
    || (c>=0xE_u8 && c<=0x10FFFF_u8/*􏿿*/)) goto S1;
    in.set_pos(pos_take); return cap;
  S1:
    cap=1; pos_take=in.get_pos();
    c=in.get();
    if((c<='\t'_u8)
    || (c=='\v'_u8 || c=='\f'_u8)
    || (c>=0xE_u8 && c<=0x10FFFF_u8/*􏿿*/)) goto S1;
    in.set_pos(pos_take); return cap;
} // Meta_Lexer_fsm_codes::O_ICLASS


template<typename I>
size_t Meta_Lexer_fsm_codes::O_IHEADER(I& in,typename I::Pos* const heads) noexcept {
    using namespace yuki::literals;
    decltype(in.get()) c;
    size_t cap=0;
    const typename I::Pos pos_begin=in.get_pos();
    typename I::Pos pos_take=in.get_pos();
    (void)heads;
  S0:
    cap=1; pos_take=in.get_pos();
    c=in.get();
    if((c<='\t'_u8)
    || (c=='\v'_u8 || c=='\f'_u8)
    || (c>=0xE_u8 && c<=0x10FFFF_u8/*􏿿*/)) goto S1;
    in.set_pos(pos_take); return cap;
  S1:
    cap=1; pos_take=in.get_pos();
    c=in.get();
    if((c<='\t'_u8)
    || (c=='\v'_u8 || c=='\f'_u8)
    || (c>=0xE_u8 && c<=0x10FFFF_u8/*􏿿*/)) goto S1;
    in.set_pos(pos_take); return cap;
} // Meta_Lexer_fsm_codes::O_IHEADER


template<typename I>
size_t Meta_Lexer_fsm_codes::O_DPREFIX(I& in,typename I::Pos* const heads) noexcept {
    using namespace yuki::literals;
    decltype(in.get()) c;
    size_t cap=0;
    const typename I::Pos pos_begin=in.get_pos();
    typename I::Pos pos_take=in.get_pos();
    (void)heads;
  S0:
    cap=1; pos_take=in.get_pos();
    c=in.get();
    if((c<='\t'_u8)
    || (c=='\v'_u8 || c=='\f'_u8)
    || (c>=0xE_u8 && c<=0x10FFFF_u8/*􏿿*/)) goto S1;
    in.set_pos(pos_take); return cap;
  S1:
    cap=1; pos_take=in.get_pos();
    c=in.get();
    if((c<='\t'_u8)
    || (c=='\v'_u8 || c=='\f'_u8)
    || (c>=0xE_u8 && c<=0x10FFFF_u8/*􏿿*/)) goto S1;
    in.set_pos(pos_take); return cap;
} // Meta_Lexer_fsm_codes::O_DPREFIX


template<typename I>
size_t Meta_Lexer_fsm_codes::O_FCNSPACE(I& in,typename I::Pos* const heads) noexcept {
    using namespace yuki::literals;
    decltype(in.get()) c;
    size_t cap=0;
    const typename I::Pos pos_begin=in.get_pos();
    typename I::Pos pos_take=in.get_pos();
    (void)heads;
  S0:
    cap=1; pos_take=in.get_pos();
    c=in.get();
    if((c<='\t'_u8)
    || (c=='\v'_u8 || c=='\f'_u8)
    || (c>=0xE_u8 && c<=0x10FFFF_u8/*􏿿*/)) goto S1;
    in.set_pos(pos_take); return cap;
  S1:
    cap=1; pos_take=in.get_pos();
    c=in.get();
    if((c<='\t'_u8)
    || (c=='\v'_u8 || c=='\f'_u8)
    || (c>=0xE_u8 && c<=0x10FFFF_u8/*􏿿*/)) goto S1;
    in.set_pos(pos_take); return cap;
} // Meta_Lexer_fsm_codes::O_FCNSPACE


template<typename I>
size_t Meta_Lexer_fsm_codes::O_TTYPE(I& in,typename I::Pos* const heads) noexcept {
    using namespace yuki::literals;
    decltype(in.get()) c;
    size_t cap=0;
    const typename I::Pos pos_begin=in.get_pos();
    typename I::Pos pos_take=in.get_pos();
    (void)heads;
  S0:
    cap=1; pos_take=in.get_pos();
    c=in.get();
    if((c<='\t'_u8)
    || (c=='\v'_u8 || c=='\f'_u8)
    || (c>=0xE_u8 && c<=0x10FFFF_u8/*􏿿*/)) goto S1;
    in.set_pos(pos_take); return cap;
  S1:
    cap=1; pos_take=in.get_pos();
    c=in.get();
    if((c<='\t'_u8)
    || (c=='\v'_u8 || c=='\f'_u8)
    || (c>=0xE_u8 && c<=0x10FFFF_u8/*􏿿*/)) goto S1;
    in.set_pos(pos_take); return cap;
} // Meta_Lexer_fsm_codes::O_TTYPE


template<typename I>
size_t Meta_Lexer_fsm_codes::O_TPLEXER(I& in,typename I::Pos* const heads) noexcept {
    using namespace yuki::literals;
    decltype(in.get()) c;
    size_t cap=0;
    const typename I::Pos pos_begin=in.get_pos();
    typename I::Pos pos_take=in.get_pos();
    (void)heads;
  S0:
    cap=1; pos_take=in.get_pos();
    c=in.get();
    if((c<='\t'_u8)
    || (c=='\v'_u8 || c=='\f'_u8)
    || (c>=0xE_u8 && c<=0x10FFFF_u8/*􏿿*/)) goto S1;
    in.set_pos(pos_take); return cap;
  S1:
    cap=1; pos_take=in.get_pos();
    c=in.get();
    if((c<='\t'_u8)
    || (c=='\v'_u8 || c=='\f'_u8)
    || (c>=0xE_u8 && c<=0x10FFFF_u8/*􏿿*/)) goto S1;
    in.set_pos(pos_take); return cap;
} // Meta_Lexer_fsm_codes::O_TPLEXER


template<typename I>
size_t Meta_Lexer_fsm_codes::MACRO_DEF_GOBBLE_SPACE(I& in,typename I::Pos* const heads) noexcept {
    using namespace yuki::literals;
    decltype(in.get()) c;
    size_t cap=0;
    const typename I::Pos pos_begin=in.get_pos();
    typename I::Pos pos_take=in.get_pos();
    (void)heads;
  S0:
    c=in.get();
    if((c>='\t'_u8 && c<='\r'_u8)
    || (c==' '_u8)
    || (c==0x85_u8/**/)
    || (c==0xA0_u8/* */)
    || (c==0x1680_u8/* */)
    || (c>=0x2000_u8/* */ && c<=0x200A_u8/* */)
    || (c==0x2028_u8/*LS*/ || c==0x2029_u8/*PS*/)
    || (c==0x202F_u8/* */)
    || (c==0x205F_u8/* */)
    || (c==0x3000_u8/*　*/)) goto S1;
    in.set_pos(pos_take); return cap;
  S1:
    cap=1; pos_take=in.get_pos();
    c=in.get();
    if((c>='\t'_u8 && c<='\r'_u8)
    || (c==' '_u8)
    || (c==0x85_u8/**/)
    || (c==0xA0_u8/* */)
    || (c==0x1680_u8/* */)
    || (c>=0x2000_u8/* */ && c<=0x200A_u8/* */)
    || (c==0x2028_u8/*LS*/ || c==0x2029_u8/*PS*/)
    || (c==0x202F_u8/* */)
    || (c==0x205F_u8/* */)
    || (c==0x3000_u8/*　*/)) goto S1;
    in.set_pos(pos_take); return cap;
} // Meta_Lexer_fsm_codes::MACRO_DEF_GOBBLE_SPACE


template<typename I>
size_t Meta_Lexer_fsm_codes::MACRO_DEF(I& in,typename I::Pos* const heads) noexcept {
    using namespace yuki::literals;
    decltype(in.get()) c;
    size_t cap=0;
    const typename I::Pos pos_begin=in.get_pos();
    typename I::Pos pos_take=in.get_pos();
    typename I::Pos pos_head=in.get_pos();
    static constexpr size_t HEAD_MAP[1]={0,};
  S0:
    pos_head=in.get_pos();
    c=in.get();
    if((c<='\t'_u8)
    || (c=='\v'_u8 || c=='\f'_u8)
    || (c>=0xE_u8 && c<=0x10FFFF_u8/*􏿿*/)) goto S1;
    if((c=='\n'_u8)
    || (c=='\r'_u8)){
        heads[HEAD_MAP[0]]=pos_head;
        goto S2;
    }
    in.set_pos(pos_take); return cap;
  S1:
    pos_head=in.get_pos();
    c=in.get();
    if((c<='\t'_u8)
    || (c=='\v'_u8 || c=='\f'_u8)
    || (c>=0xE_u8 && c<=0x10FFFF_u8/*􏿿*/)) goto S1;
    if((c=='\n'_u8)
    || (c=='\r'_u8)){
        heads[HEAD_MAP[0]]=pos_head;
        goto S2;
    }
    in.set_pos(pos_take); return cap;
  S2:
    cap=1; pos_take=heads[HEAD_MAP[0]];
    in.set_pos(pos_take); return cap;
} // Meta_Lexer_fsm_codes::MACRO_DEF


template<typename I>
size_t Meta_Lexer_fsm_codes::CODE0(I& in,typename I::Pos* const heads) noexcept {
    using namespace yuki::literals;
    decltype(in.get()) c;
    size_t cap=0;
    const typename I::Pos pos_begin=in.get_pos();
    typename I::Pos pos_take=in.get_pos();
    (void)heads;
  S0:
    c=in.get();
    if((c>='\t'_u8 && c<='\r'_u8)
    || (c==' '_u8)
    || (c==0x85_u8/**/)
    || (c==0xA0_u8/* */)
    || (c==0x1680_u8/* */)
    || (c>=0x2000_u8/* */ && c<=0x200A_u8/* */)
    || (c==0x2028_u8/*LS*/ || c==0x2029_u8/*PS*/)
    || (c==0x202F_u8/* */)
    || (c==0x205F_u8/* */)
    || (c==0x3000_u8/*　*/)) goto S1;
    if((c<='\b'_u8)
    || (c>=0xE_u8 && c<=0x1F_u8)
    || (c>='!'_u8 && c<='.'_u8)
    || (c>='0'_u8 && c<='z'_u8)
    || (c>='|'_u8 && c<=0x84_u8/**/)
    || (c>=0x86_u8/**/ && c<=0x9F_u8/**/)
    || (c>=0xA1_u8/*¡*/ && c<=0x167F_u8/*ᙿ*/)
    || (c>=0x1681_u8/*ᚁ*/ && c<=0x1FFF_u8/*῿*/)
    || (c>=0x200B_u8/*​*/ && c<=0x2027_u8/*‧*/)
    || (c>=0x202A_u8/*LRE*/ && c<=0x202E_u8/*RLO*/)
    || (c>=0x2030_u8/*‰*/ && c<=0x205E_u8/*⁞*/)
    || (c>=0x2060_u8/*⁠*/ && c<=0x2FFF_u8/*⿿*/)
    || (c>=0x3001_u8/*、*/ && c<=0x10FFFF_u8/*􏿿*/)) goto S2;
    if((c=='/'_u8)) goto S3;
    if((c=='{'_u8)) goto S4;
    in.set_pos(pos_take); return cap;
  S1:
    cap=1; pos_take=in.get_pos();
    c=in.get();
    if((c>='\t'_u8 && c<='\r'_u8)
    || (c==' '_u8)
    || (c==0x85_u8/**/)
    || (c==0xA0_u8/* */)
    || (c==0x1680_u8/* */)
    || (c>=0x2000_u8/* */ && c<=0x200A_u8/* */)
    || (c==0x2028_u8/*LS*/ || c==0x2029_u8/*PS*/)
    || (c==0x202F_u8/* */)
    || (c==0x205F_u8/* */)
    || (c==0x3000_u8/*　*/)) goto S1;
    in.set_pos(pos_take); return cap;
  S2:
    cap=4; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S3:
    cap=4; pos_take=in.get_pos();
    c=in.get();
    if((c=='/'_u8)) goto S5;
    in.set_pos(pos_take); return cap;
  S4:
    cap=3; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S5:
    c=in.get();
    if((c<='\t'_u8)
    || (c=='\v'_u8 || c=='\f'_u8)
    || (c>=0xE_u8 && c<=0x10FFFF_u8/*􏿿*/)) goto S6;
    if((c=='\n'_u8)
    || (c=='\r'_u8)) goto S7;
    in.set_pos(pos_take); return cap;
  S6:
    c=in.get();
    if((c<='\t'_u8)
    || (c=='\v'_u8 || c=='\f'_u8)
    || (c>=0xE_u8 && c<=0x10FFFF_u8/*􏿿*/)) goto S6;
    if((c=='\n'_u8)
    || (c=='\r'_u8)) goto S7;
    in.set_pos(pos_take); return cap;
  S7:
    cap=2; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
} // Meta_Lexer_fsm_codes::CODE0


template<typename I>
size_t Meta_Lexer_fsm_codes::CODE1(I& in,typename I::Pos* const heads) noexcept {
    using namespace yuki::literals;
    decltype(in.get()) c;
    size_t cap=0;
    const typename I::Pos pos_begin=in.get_pos();
    typename I::Pos pos_take=in.get_pos();
    (void)heads;
  S0:
    c=in.get();
    if((c<='!'_u8)
    || (c>='#'_u8 && c<='&'_u8)
    || (c>='('_u8 && c<='z'_u8)
    || (c=='|'_u8)
    || (c>='~'_u8 && c<=0x10FFFF_u8/*􏿿*/)) goto S1;
    if((c=='{'_u8)) goto S2;
    if((c=='}'_u8)) goto S3;
    if((c=='\''_u8)) goto S4;
    if((c=='\"'_u8)) goto S5;
    in.set_pos(pos_take); return cap;
  S1:
    cap=5; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S2:
    cap=1; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S3:
    cap=2; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S4:
    cap=3; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S5:
    cap=4; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
} // Meta_Lexer_fsm_codes::CODE1


template<typename I>
size_t Meta_Lexer_fsm_codes::C_LIT(I& in,typename I::Pos* const heads) noexcept {
    using namespace yuki::literals;
    decltype(in.get()) c;
    size_t cap=0;
    const typename I::Pos pos_begin=in.get_pos();
    typename I::Pos pos_take=in.get_pos();
    (void)heads;
  S0:
    c=in.get();
    if((c<='&'_u8)
    || (c>='('_u8 && c<='['_u8)
    || (c>=']'_u8 && c<=0x10FFFF_u8/*􏿿*/)) goto S1;
    if((c=='\\'_u8)) goto S2;
    if((c=='\''_u8)) goto S3;
    in.set_pos(pos_take); return cap;
  S1:
    cap=3; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S2:
    cap=3; pos_take=in.get_pos();
    c=in.get();
    if((c<='\t'_u8)
    || (c=='\v'_u8 || c=='\f'_u8)
    || (c>=0xE_u8 && c<=0x10FFFF_u8/*􏿿*/)) goto S4;
    in.set_pos(pos_take); return cap;
  S3:
    cap=2; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S4:
    cap=1; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
} // Meta_Lexer_fsm_codes::C_LIT


template<typename I>
size_t Meta_Lexer_fsm_codes::S_LIT(I& in,typename I::Pos* const heads) noexcept {
    using namespace yuki::literals;
    decltype(in.get()) c;
    size_t cap=0;
    const typename I::Pos pos_begin=in.get_pos();
    typename I::Pos pos_take=in.get_pos();
    (void)heads;
  S0:
    c=in.get();
    if((c<='!'_u8)
    || (c>='#'_u8 && c<='['_u8)
    || (c>=']'_u8 && c<=0x10FFFF_u8/*􏿿*/)) goto S1;
    if((c=='\\'_u8)) goto S2;
    if((c=='\"'_u8)) goto S3;
    in.set_pos(pos_take); return cap;
  S1:
    cap=3; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S2:
    cap=3; pos_take=in.get_pos();
    c=in.get();
    if((c<='\t'_u8)
    || (c=='\v'_u8 || c=='\f'_u8)
    || (c>=0xE_u8 && c<=0x10FFFF_u8/*􏿿*/)) goto S4;
    in.set_pos(pos_take); return cap;
  S3:
    cap=2; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S4:
    cap=1; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
} // Meta_Lexer_fsm_codes::S_LIT


template<typename I>
size_t Meta_Lexer_fsm_codes::SEC1(I& in,typename I::Pos* const heads) noexcept {
    using namespace yuki::literals;
    decltype(in.get()) c;
    size_t cap=0;
    const typename I::Pos pos_begin=in.get_pos();
    typename I::Pos pos_take=in.get_pos();
    (void)heads;
  S0:
    c=in.get();
    if((c>='\t'_u8 && c<='\r'_u8)
    || (c==' '_u8)
    || (c==0x85_u8/**/)
    || (c==0xA0_u8/* */)
    || (c==0x1680_u8/* */)
    || (c>=0x2000_u8/* */ && c<=0x200A_u8/* */)
    || (c==0x2028_u8/*LS*/ || c==0x2029_u8/*PS*/)
    || (c==0x202F_u8/* */)
    || (c==0x205F_u8/* */)
    || (c==0x3000_u8/*　*/)) goto S1;
    if((c=='%'_u8)) goto S2;
    if((c=='/'_u8)) goto S3;
    if((c=='<'_u8)) goto S4;
    in.set_pos(pos_take); return cap;
  S1:
    cap=3; pos_take=in.get_pos();
    c=in.get();
    if((c>='\t'_u8 && c<='\r'_u8)
    || (c==' '_u8)
    || (c==0x85_u8/**/)
    || (c==0xA0_u8/* */)
    || (c==0x1680_u8/* */)
    || (c>=0x2000_u8/* */ && c<=0x200A_u8/* */)
    || (c==0x2028_u8/*LS*/ || c==0x2029_u8/*PS*/)
    || (c==0x202F_u8/* */)
    || (c==0x205F_u8/* */)
    || (c==0x3000_u8/*　*/)) goto S1;
    in.set_pos(pos_take); return cap;
  S2:
    c=in.get();
    if((c=='%'_u8)) goto S5;
    in.set_pos(pos_take); return cap;
  S3:
    c=in.get();
    if((c=='/'_u8)) goto S6;
    in.set_pos(pos_take); return cap;
  S4:
    c=in.get();
    if((c<='='_u8)
    || (c>='?'_u8 && c<=0x10FFFF_u8/*􏿿*/)) goto S7;
    if((c=='>'_u8)) goto S8;
    in.set_pos(pos_take); return cap;
  S5:
    cap=2; pos_take=in.get_pos();
    c=in.get();
    if((c>='\t'_u8 && c<='\r'_u8)
    || (c==' '_u8)
    || (c==0x85_u8/**/)
    || (c==0xA0_u8/* */)
    || (c==0x1680_u8/* */)
    || (c>=0x2000_u8/* */ && c<=0x200A_u8/* */)
    || (c==0x2028_u8/*LS*/ || c==0x2029_u8/*PS*/)
    || (c==0x202F_u8/* */)
    || (c==0x205F_u8/* */)
    || (c==0x3000_u8/*　*/)) goto S9;
    in.set_pos(pos_take); return cap;
  S6:
    c=in.get();
    if((c<='\t'_u8)
    || (c=='\v'_u8 || c=='\f'_u8)
    || (c>=0xE_u8 && c<=0x10FFFF_u8/*􏿿*/)) goto S10;
    if((c=='\n'_u8)
    || (c=='\r'_u8)) goto S11;
    in.set_pos(pos_take); return cap;
  S7:
    c=in.get();
    if((c<='='_u8)
    || (c>='?'_u8 && c<=0x10FFFF_u8/*􏿿*/)) goto S7;
    if((c=='>'_u8)) goto S8;
    in.set_pos(pos_take); return cap;
  S8:
    c=in.get();
    if((c=='{'_u8)) goto S12;
    in.set_pos(pos_take); return cap;
  S9:
    cap=2; pos_take=in.get_pos();
    c=in.get();
    if((c>='\t'_u8 && c<='\r'_u8)
    || (c==' '_u8)
    || (c==0x85_u8/**/)
    || (c==0xA0_u8/* */)
    || (c==0x1680_u8/* */)
    || (c>=0x2000_u8/* */ && c<=0x200A_u8/* */)
    || (c==0x2028_u8/*LS*/ || c==0x2029_u8/*PS*/)
    || (c==0x202F_u8/* */)
    || (c==0x205F_u8/* */)
    || (c==0x3000_u8/*　*/)) goto S9;
    in.set_pos(pos_take); return cap;
  S10:
    c=in.get();
    if((c<='\t'_u8)
    || (c=='\v'_u8 || c=='\f'_u8)
    || (c>=0xE_u8 && c<=0x10FFFF_u8/*􏿿*/)) goto S10;
    if((c=='\n'_u8)
    || (c=='\r'_u8)) goto S11;
    in.set_pos(pos_take); return cap;
  S11:
    cap=4; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S12:
    cap=1; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
} // Meta_Lexer_fsm_codes::SEC1


template<typename I>
size_t Meta_Lexer_fsm_codes::GOBBLE_NEWLINE_TO_REGEX(I& in,typename I::Pos* const heads) noexcept {
    using namespace yuki::literals;
    decltype(in.get()) c;
    size_t cap=0;
    const typename I::Pos pos_begin=in.get_pos();
    typename I::Pos pos_take=in.get_pos();
    (void)heads;
  S0:
    c=in.get();
    if((c=='\n'_u8)
    || (c=='\r'_u8)) goto S1;
    in.set_pos(pos_take); return cap;
  S1:
    cap=1; pos_take=in.get_pos();
    c=in.get();
    if((c=='\n'_u8)
    || (c=='\r'_u8)) goto S1;
    in.set_pos(pos_take); return cap;
} // Meta_Lexer_fsm_codes::GOBBLE_NEWLINE_TO_REGEX


template<typename I>
size_t Meta_Lexer_fsm_codes::REGEX(I& in,typename I::Pos* const heads) noexcept {
    using namespace yuki::literals;
    decltype(in.get()) c;
    size_t cap=0;
    const typename I::Pos pos_begin=in.get_pos();
    typename I::Pos pos_take=in.get_pos();
    (void)heads;
  S0:
    c=in.get();
    if((c=='\n'_u8)
    || (c=='\r'_u8)) goto S1;
    if((c<='\b'_u8)
    || (c>=0xE_u8 && c<=0x1F_u8)
    || (c>='!'_u8 && c<=';'_u8)
    || (c>='='_u8 && c<=0x84_u8/**/)
    || (c>=0x86_u8/**/ && c<=0x9F_u8/**/)
    || (c>=0xA1_u8/*¡*/ && c<=0x167F_u8/*ᙿ*/)
    || (c>=0x1681_u8/*ᚁ*/ && c<=0x1FFF_u8/*῿*/)
    || (c>=0x200B_u8/*​*/ && c<=0x2027_u8/*‧*/)
    || (c>=0x202A_u8/*LRE*/ && c<=0x202E_u8/*RLO*/)
    || (c>=0x2030_u8/*‰*/ && c<=0x205E_u8/*⁞*/)
    || (c>=0x2060_u8/*⁠*/ && c<=0x2FFF_u8/*⿿*/)
    || (c>=0x3001_u8/*、*/ && c<=0x10FFFF_u8/*􏿿*/)) goto S2;
    if((c=='\t'_u8)
    || (c=='\v'_u8 || c=='\f'_u8)
    || (c==' '_u8)
    || (c==0x85_u8/**/)
    || (c==0xA0_u8/* */)
    || (c==0x1680_u8/* */)
    || (c>=0x2000_u8/* */ && c<=0x200A_u8/* */)
    || (c==0x2028_u8/*LS*/ || c==0x2029_u8/*PS*/)
    || (c==0x202F_u8/* */)
    || (c==0x205F_u8/* */)
    || (c==0x3000_u8/*　*/)) goto S3;
    if((c=='<'_u8)) goto S4;
    in.set_pos(pos_take); return cap;
  S1:
    c=in.get();
    if((c>='\t'_u8 && c<='\r'_u8)
    || (c==' '_u8)
    || (c==0x85_u8/**/)
    || (c==0xA0_u8/* */)
    || (c==0x1680_u8/* */)
    || (c>=0x2000_u8/* */ && c<=0x200A_u8/* */)
    || (c==0x2028_u8/*LS*/ || c==0x2029_u8/*PS*/)
    || (c==0x202F_u8/* */)
    || (c==0x205F_u8/* */)
    || (c==0x3000_u8/*　*/)) goto S1;
    if((c=='{'_u8)) goto S5;
    in.set_pos(pos_take); return cap;
  S2:
    cap=5; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S3:
    cap=5; pos_take=in.get_pos();
    c=in.get();
    if((c>='\t'_u8 && c<='\r'_u8)
    || (c==' '_u8)
    || (c==0x85_u8/**/)
    || (c==0xA0_u8/* */)
    || (c==0x1680_u8/* */)
    || (c>=0x2000_u8/* */ && c<=0x200A_u8/* */)
    || (c==0x2028_u8/*LS*/ || c==0x2029_u8/*PS*/)
    || (c==0x202F_u8/* */)
    || (c==0x205F_u8/* */)
    || (c==0x3000_u8/*　*/)) goto S1;
    if((c=='{'_u8)) goto S5;
    in.set_pos(pos_take); return cap;
  S4:
    cap=5; pos_take=in.get_pos();
    c=in.get();
    if((c=='<'_u8)) goto S6;
    in.set_pos(pos_take); return cap;
  S5:
    cap=1; pos_take=in.get_pos();
    c=in.get();
    if((c>='\t'_u8 && c<='\r'_u8)
    || (c==' '_u8)
    || (c==0x85_u8/**/)
    || (c==0xA0_u8/* */)
    || (c==0x1680_u8/* */)
    || (c>=0x2000_u8/* */ && c<=0x200A_u8/* */)
    || (c==0x2028_u8/*LS*/ || c==0x2029_u8/*PS*/)
    || (c==0x202F_u8/* */)
    || (c==0x205F_u8/* */)
    || (c==0x3000_u8/*　*/)) goto S7;
    in.set_pos(pos_take); return cap;
  S6:
    c=in.get();
    if((c=='E'_u8)) goto S8;
    if((c=='D'_u8)) goto S9;
    if((c=='B'_u8)) goto S10;
    in.set_pos(pos_take); return cap;
  S7:
    cap=1; pos_take=in.get_pos();
    c=in.get();
    if((c>='\t'_u8 && c<='\r'_u8)
    || (c==' '_u8)
    || (c==0x85_u8/**/)
    || (c==0xA0_u8/* */)
    || (c==0x1680_u8/* */)
    || (c>=0x2000_u8/* */ && c<=0x200A_u8/* */)
    || (c==0x2028_u8/*LS*/ || c==0x2029_u8/*PS*/)
    || (c==0x202F_u8/* */)
    || (c==0x205F_u8/* */)
    || (c==0x3000_u8/*　*/)) goto S7;
    in.set_pos(pos_take); return cap;
  S8:
    c=in.get();
    if((c=='O'_u8)) goto S11;
    in.set_pos(pos_take); return cap;
  S9:
    c=in.get();
    if((c=='E'_u8)) goto S12;
    in.set_pos(pos_take); return cap;
  S10:
    c=in.get();
    if((c=='E'_u8)) goto S13;
    in.set_pos(pos_take); return cap;
  S11:
    c=in.get();
    if((c=='F'_u8)) goto S14;
    in.set_pos(pos_take); return cap;
  S12:
    c=in.get();
    if((c=='F'_u8)) goto S15;
    in.set_pos(pos_take); return cap;
  S13:
    c=in.get();
    if((c=='F'_u8)) goto S16;
    in.set_pos(pos_take); return cap;
  S14:
    c=in.get();
    if((c=='>'_u8)) goto S17;
    in.set_pos(pos_take); return cap;
  S15:
    c=in.get();
    if((c=='A'_u8)) goto S18;
    in.set_pos(pos_take); return cap;
  S16:
    c=in.get();
    if((c=='O'_u8)) goto S19;
    in.set_pos(pos_take); return cap;
  S17:
    c=in.get();
    if((c=='>'_u8)) goto S20;
    in.set_pos(pos_take); return cap;
  S18:
    c=in.get();
    if((c=='U'_u8)) goto S21;
    in.set_pos(pos_take); return cap;
  S19:
    c=in.get();
    if((c=='R'_u8)) goto S22;
    in.set_pos(pos_take); return cap;
  S20:
    c=in.get();
    if((c>='\t'_u8 && c<='\r'_u8)
    || (c==' '_u8)
    || (c==0x85_u8/**/)
    || (c==0xA0_u8/* */)
    || (c==0x1680_u8/* */)
    || (c>=0x2000_u8/* */ && c<=0x200A_u8/* */)
    || (c==0x2028_u8/*LS*/ || c==0x2029_u8/*PS*/)
    || (c==0x202F_u8/* */)
    || (c==0x205F_u8/* */)
    || (c==0x3000_u8/*　*/)) goto S23;
    in.set_pos(pos_take); return cap;
  S21:
    c=in.get();
    if((c=='L'_u8)) goto S24;
    in.set_pos(pos_take); return cap;
  S22:
    c=in.get();
    if((c=='E'_u8)) goto S25;
    in.set_pos(pos_take); return cap;
  S23:
    c=in.get();
    if((c>='\t'_u8 && c<='\r'_u8)
    || (c==' '_u8)
    || (c==0x85_u8/**/)
    || (c==0xA0_u8/* */)
    || (c==0x1680_u8/* */)
    || (c>=0x2000_u8/* */ && c<=0x200A_u8/* */)
    || (c==0x2028_u8/*LS*/ || c==0x2029_u8/*PS*/)
    || (c==0x202F_u8/* */)
    || (c==0x205F_u8/* */)
    || (c==0x3000_u8/*　*/)) goto S23;
    if((c=='{'_u8)) goto S26;
    in.set_pos(pos_take); return cap;
  S24:
    c=in.get();
    if((c=='T'_u8)) goto S27;
    in.set_pos(pos_take); return cap;
  S25:
    c=in.get();
    if((c=='>'_u8)) goto S28;
    in.set_pos(pos_take); return cap;
  S26:
    cap=2; pos_take=in.get_pos();
    c=in.get();
    if((c>='\t'_u8 && c<='\r'_u8)
    || (c==' '_u8)
    || (c==0x85_u8/**/)
    || (c==0xA0_u8/* */)
    || (c==0x1680_u8/* */)
    || (c>=0x2000_u8/* */ && c<=0x200A_u8/* */)
    || (c==0x2028_u8/*LS*/ || c==0x2029_u8/*PS*/)
    || (c==0x202F_u8/* */)
    || (c==0x205F_u8/* */)
    || (c==0x3000_u8/*　*/)) goto S29;
    in.set_pos(pos_take); return cap;
  S27:
    c=in.get();
    if((c=='>'_u8)) goto S30;
    in.set_pos(pos_take); return cap;
  S28:
    c=in.get();
    if((c=='>'_u8)) goto S31;
    in.set_pos(pos_take); return cap;
  S29:
    cap=2; pos_take=in.get_pos();
    c=in.get();
    if((c>='\t'_u8 && c<='\r'_u8)
    || (c==' '_u8)
    || (c==0x85_u8/**/)
    || (c==0xA0_u8/* */)
    || (c==0x1680_u8/* */)
    || (c>=0x2000_u8/* */ && c<=0x200A_u8/* */)
    || (c==0x2028_u8/*LS*/ || c==0x2029_u8/*PS*/)
    || (c==0x202F_u8/* */)
    || (c==0x205F_u8/* */)
    || (c==0x3000_u8/*　*/)) goto S29;
    in.set_pos(pos_take); return cap;
  S30:
    c=in.get();
    if((c=='>'_u8)) goto S32;
    in.set_pos(pos_take); return cap;
  S31:
    c=in.get();
    if((c>='\t'_u8 && c<='\r'_u8)
    || (c==' '_u8)
    || (c==0x85_u8/**/)
    || (c==0xA0_u8/* */)
    || (c==0x1680_u8/* */)
    || (c>=0x2000_u8/* */ && c<=0x200A_u8/* */)
    || (c==0x2028_u8/*LS*/ || c==0x2029_u8/*PS*/)
    || (c==0x202F_u8/* */)
    || (c==0x205F_u8/* */)
    || (c==0x3000_u8/*　*/)) goto S33;
    in.set_pos(pos_take); return cap;
  S32:
    c=in.get();
    if((c>='\t'_u8 && c<='\r'_u8)
    || (c==' '_u8)
    || (c==0x85_u8/**/)
    || (c==0xA0_u8/* */)
    || (c==0x1680_u8/* */)
    || (c>=0x2000_u8/* */ && c<=0x200A_u8/* */)
    || (c==0x2028_u8/*LS*/ || c==0x2029_u8/*PS*/)
    || (c==0x202F_u8/* */)
    || (c==0x205F_u8/* */)
    || (c==0x3000_u8/*　*/)) goto S34;
    in.set_pos(pos_take); return cap;
  S33:
    c=in.get();
    if((c>='\t'_u8 && c<='\r'_u8)
    || (c==' '_u8)
    || (c==0x85_u8/**/)
    || (c==0xA0_u8/* */)
    || (c==0x1680_u8/* */)
    || (c>=0x2000_u8/* */ && c<=0x200A_u8/* */)
    || (c==0x2028_u8/*LS*/ || c==0x2029_u8/*PS*/)
    || (c==0x202F_u8/* */)
    || (c==0x205F_u8/* */)
    || (c==0x3000_u8/*　*/)) goto S33;
    if((c=='{'_u8)) goto S35;
    in.set_pos(pos_take); return cap;
  S34:
    c=in.get();
    if((c>='\t'_u8 && c<='\r'_u8)
    || (c==' '_u8)
    || (c==0x85_u8/**/)
    || (c==0xA0_u8/* */)
    || (c==0x1680_u8/* */)
    || (c>=0x2000_u8/* */ && c<=0x200A_u8/* */)
    || (c==0x2028_u8/*LS*/ || c==0x2029_u8/*PS*/)
    || (c==0x202F_u8/* */)
    || (c==0x205F_u8/* */)
    || (c==0x3000_u8/*　*/)) goto S34;
    if((c=='{'_u8)) goto S36;
    in.set_pos(pos_take); return cap;
  S35:
    cap=4; pos_take=in.get_pos();
    c=in.get();
    if((c>='\t'_u8 && c<='\r'_u8)
    || (c==' '_u8)
    || (c==0x85_u8/**/)
    || (c==0xA0_u8/* */)
    || (c==0x1680_u8/* */)
    || (c>=0x2000_u8/* */ && c<=0x200A_u8/* */)
    || (c==0x2028_u8/*LS*/ || c==0x2029_u8/*PS*/)
    || (c==0x202F_u8/* */)
    || (c==0x205F_u8/* */)
    || (c==0x3000_u8/*　*/)) goto S37;
    in.set_pos(pos_take); return cap;
  S36:
    cap=3; pos_take=in.get_pos();
    c=in.get();
    if((c>='\t'_u8 && c<='\r'_u8)
    || (c==' '_u8)
    || (c==0x85_u8/**/)
    || (c==0xA0_u8/* */)
    || (c==0x1680_u8/* */)
    || (c>=0x2000_u8/* */ && c<=0x200A_u8/* */)
    || (c==0x2028_u8/*LS*/ || c==0x2029_u8/*PS*/)
    || (c==0x202F_u8/* */)
    || (c==0x205F_u8/* */)
    || (c==0x3000_u8/*　*/)) goto S38;
    in.set_pos(pos_take); return cap;
  S37:
    cap=4; pos_take=in.get_pos();
    c=in.get();
    if((c>='\t'_u8 && c<='\r'_u8)
    || (c==' '_u8)
    || (c==0x85_u8/**/)
    || (c==0xA0_u8/* */)
    || (c==0x1680_u8/* */)
    || (c>=0x2000_u8/* */ && c<=0x200A_u8/* */)
    || (c==0x2028_u8/*LS*/ || c==0x2029_u8/*PS*/)
    || (c==0x202F_u8/* */)
    || (c==0x205F_u8/* */)
    || (c==0x3000_u8/*　*/)) goto S37;
    in.set_pos(pos_take); return cap;
  S38:
    cap=3; pos_take=in.get_pos();
    c=in.get();
    if((c>='\t'_u8 && c<='\r'_u8)
    || (c==' '_u8)
    || (c==0x85_u8/**/)
    || (c==0xA0_u8/* */)
    || (c==0x1680_u8/* */)
    || (c>=0x2000_u8/* */ && c<=0x200A_u8/* */)
    || (c==0x2028_u8/*LS*/ || c==0x2029_u8/*PS*/)
    || (c==0x202F_u8/* */)
    || (c==0x205F_u8/* */)
    || (c==0x3000_u8/*　*/)) goto S38;
    in.set_pos(pos_take); return cap;
} // Meta_Lexer_fsm_codes::REGEX


template<typename I>
size_t Meta_Lexer_fsm_codes::REGEX_CODE(I& in,typename I::Pos* const heads) noexcept {
    using namespace yuki::literals;
    decltype(in.get()) c;
    size_t cap=0;
    const typename I::Pos pos_begin=in.get_pos();
    typename I::Pos pos_take=in.get_pos();
    (void)heads;
  S0:
    c=in.get();
    if((c<='!'_u8)
    || (c>='#'_u8 && c<='&'_u8)
    || (c>='('_u8 && c<='z'_u8)
    || (c=='|'_u8)
    || (c>='~'_u8 && c<=0x10FFFF_u8/*􏿿*/)) goto S1;
    if((c=='{'_u8)) goto S2;
    if((c=='}'_u8)) goto S3;
    if((c=='\''_u8)) goto S4;
    if((c=='\"'_u8)) goto S5;
    in.set_pos(pos_take); return cap;
  S1:
    cap=5; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S2:
    cap=1; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S3:
    cap=2; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S4:
    cap=3; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S5:
    cap=4; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
} // Meta_Lexer_fsm_codes::REGEX_CODE


template<typename I>
size_t Meta_Lexer_fsm_codes::DISCARD_EVERYTHING_UNTIL_NEWLINE_TO_POST_REGEX(I& in,typename I::Pos* const heads) noexcept {
    using namespace yuki::literals;
    decltype(in.get()) c;
    size_t cap=0;
    const typename I::Pos pos_begin=in.get_pos();
    typename I::Pos pos_take=in.get_pos();
    (void)heads;
  S0:
    c=in.get();
    if((c<='\t'_u8)
    || (c=='\v'_u8 || c=='\f'_u8)
    || (c>=0xE_u8 && c<=0x10FFFF_u8/*􏿿*/)) goto S1;
    if((c=='\n'_u8)
    || (c=='\r'_u8)) goto S2;
    in.set_pos(pos_take); return cap;
  S1:
    c=in.get();
    if((c<='\t'_u8)
    || (c=='\v'_u8 || c=='\f'_u8)
    || (c>=0xE_u8 && c<=0x10FFFF_u8/*􏿿*/)) goto S1;
    if((c=='\n'_u8)
    || (c=='\r'_u8)) goto S2;
    in.set_pos(pos_take); return cap;
  S2:
    cap=1; pos_take=in.get_pos();
    c=in.get();
    if((c=='\n'_u8)
    || (c=='\r'_u8)) goto S2;
    in.set_pos(pos_take); return cap;
} // Meta_Lexer_fsm_codes::DISCARD_EVERYTHING_UNTIL_NEWLINE_TO_POST_REGEX


template<typename I>
size_t Meta_Lexer_fsm_codes::REGEX_CODE_EOF(I& in,typename I::Pos* const heads) noexcept {
    using namespace yuki::literals;
    decltype(in.get()) c;
    size_t cap=0;
    const typename I::Pos pos_begin=in.get_pos();
    typename I::Pos pos_take=in.get_pos();
    (void)heads;
  S0:
    c=in.get();
    if((c<='!'_u8)
    || (c>='#'_u8 && c<='&'_u8)
    || (c>='('_u8 && c<='z'_u8)
    || (c=='|'_u8)
    || (c>='~'_u8 && c<=0x10FFFF_u8/*􏿿*/)) goto S1;
    if((c=='{'_u8)) goto S2;
    if((c=='}'_u8)) goto S3;
    if((c=='\''_u8)) goto S4;
    if((c=='\"'_u8)) goto S5;
    in.set_pos(pos_take); return cap;
  S1:
    cap=5; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S2:
    cap=1; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S3:
    cap=2; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S4:
    cap=3; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S5:
    cap=4; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
} // Meta_Lexer_fsm_codes::REGEX_CODE_EOF


template<typename I>
size_t Meta_Lexer_fsm_codes::C_LIT_EOF(I& in,typename I::Pos* const heads) noexcept {
    using namespace yuki::literals;
    decltype(in.get()) c;
    size_t cap=0;
    const typename I::Pos pos_begin=in.get_pos();
    typename I::Pos pos_take=in.get_pos();
    (void)heads;
  S0:
    c=in.get();
    if((c<='&'_u8)
    || (c>='('_u8 && c<='['_u8)
    || (c>=']'_u8 && c<=0x10FFFF_u8/*􏿿*/)) goto S1;
    if((c=='\\'_u8)) goto S2;
    if((c=='\''_u8)) goto S3;
    in.set_pos(pos_take); return cap;
  S1:
    cap=3; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S2:
    cap=3; pos_take=in.get_pos();
    c=in.get();
    if((c<='\t'_u8)
    || (c=='\v'_u8 || c=='\f'_u8)
    || (c>=0xE_u8 && c<=0x10FFFF_u8/*􏿿*/)) goto S4;
    in.set_pos(pos_take); return cap;
  S3:
    cap=2; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S4:
    cap=1; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
} // Meta_Lexer_fsm_codes::C_LIT_EOF


template<typename I>
size_t Meta_Lexer_fsm_codes::S_LIT_EOF(I& in,typename I::Pos* const heads) noexcept {
    using namespace yuki::literals;
    decltype(in.get()) c;
    size_t cap=0;
    const typename I::Pos pos_begin=in.get_pos();
    typename I::Pos pos_take=in.get_pos();
    (void)heads;
  S0:
    c=in.get();
    if((c<='!'_u8)
    || (c>='#'_u8 && c<='['_u8)
    || (c>=']'_u8 && c<=0x10FFFF_u8/*􏿿*/)) goto S1;
    if((c=='\\'_u8)) goto S2;
    if((c=='\"'_u8)) goto S3;
    in.set_pos(pos_take); return cap;
  S1:
    cap=3; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S2:
    cap=3; pos_take=in.get_pos();
    c=in.get();
    if((c<='\t'_u8)
    || (c=='\v'_u8 || c=='\f'_u8)
    || (c>=0xE_u8 && c<=0x10FFFF_u8/*􏿿*/)) goto S4;
    in.set_pos(pos_take); return cap;
  S3:
    cap=2; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S4:
    cap=1; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
} // Meta_Lexer_fsm_codes::S_LIT_EOF


template<typename I>
size_t Meta_Lexer_fsm_codes::REGEX_CODE_DEFAULT(I& in,typename I::Pos* const heads) noexcept {
    using namespace yuki::literals;
    decltype(in.get()) c;
    size_t cap=0;
    const typename I::Pos pos_begin=in.get_pos();
    typename I::Pos pos_take=in.get_pos();
    (void)heads;
  S0:
    c=in.get();
    if((c<='!'_u8)
    || (c>='#'_u8 && c<='&'_u8)
    || (c>='('_u8 && c<='z'_u8)
    || (c=='|'_u8)
    || (c>='~'_u8 && c<=0x10FFFF_u8/*􏿿*/)) goto S1;
    if((c=='{'_u8)) goto S2;
    if((c=='}'_u8)) goto S3;
    if((c=='\''_u8)) goto S4;
    if((c=='\"'_u8)) goto S5;
    in.set_pos(pos_take); return cap;
  S1:
    cap=5; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S2:
    cap=1; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S3:
    cap=2; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S4:
    cap=3; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S5:
    cap=4; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
} // Meta_Lexer_fsm_codes::REGEX_CODE_DEFAULT


template<typename I>
size_t Meta_Lexer_fsm_codes::C_LIT_DEFAULT(I& in,typename I::Pos* const heads) noexcept {
    using namespace yuki::literals;
    decltype(in.get()) c;
    size_t cap=0;
    const typename I::Pos pos_begin=in.get_pos();
    typename I::Pos pos_take=in.get_pos();
    (void)heads;
  S0:
    c=in.get();
    if((c<='&'_u8)
    || (c>='('_u8 && c<='['_u8)
    || (c>=']'_u8 && c<=0x10FFFF_u8/*􏿿*/)) goto S1;
    if((c=='\\'_u8)) goto S2;
    if((c=='\''_u8)) goto S3;
    in.set_pos(pos_take); return cap;
  S1:
    cap=3; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S2:
    cap=3; pos_take=in.get_pos();
    c=in.get();
    if((c<='\t'_u8)
    || (c=='\v'_u8 || c=='\f'_u8)
    || (c>=0xE_u8 && c<=0x10FFFF_u8/*􏿿*/)) goto S4;
    in.set_pos(pos_take); return cap;
  S3:
    cap=2; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S4:
    cap=1; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
} // Meta_Lexer_fsm_codes::C_LIT_DEFAULT


template<typename I>
size_t Meta_Lexer_fsm_codes::S_LIT_DEFAULT(I& in,typename I::Pos* const heads) noexcept {
    using namespace yuki::literals;
    decltype(in.get()) c;
    size_t cap=0;
    const typename I::Pos pos_begin=in.get_pos();
    typename I::Pos pos_take=in.get_pos();
    (void)heads;
  S0:
    c=in.get();
    if((c<='!'_u8)
    || (c>='#'_u8 && c<='['_u8)
    || (c>=']'_u8 && c<=0x10FFFF_u8/*􏿿*/)) goto S1;
    if((c=='\\'_u8)) goto S2;
    if((c=='\"'_u8)) goto S3;
    in.set_pos(pos_take); return cap;
  S1:
    cap=3; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S2:
    cap=3; pos_take=in.get_pos();
    c=in.get();
    if((c<='\t'_u8)
    || (c=='\v'_u8 || c=='\f'_u8)
    || (c>=0xE_u8 && c<=0x10FFFF_u8/*􏿿*/)) goto S4;
    in.set_pos(pos_take); return cap;
  S3:
    cap=2; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S4:
    cap=1; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
} // Meta_Lexer_fsm_codes::S_LIT_DEFAULT


template<typename I>
size_t Meta_Lexer_fsm_codes::REGEX_CODE_BEFORE(I& in,typename I::Pos* const heads) noexcept {
    using namespace yuki::literals;
    decltype(in.get()) c;
    size_t cap=0;
    const typename I::Pos pos_begin=in.get_pos();
    typename I::Pos pos_take=in.get_pos();
    (void)heads;
  S0:
    c=in.get();
    if((c<='!'_u8)
    || (c>='#'_u8 && c<='&'_u8)
    || (c>='('_u8 && c<='z'_u8)
    || (c=='|'_u8)
    || (c>='~'_u8 && c<=0x10FFFF_u8/*􏿿*/)) goto S1;
    if((c=='{'_u8)) goto S2;
    if((c=='}'_u8)) goto S3;
    if((c=='\''_u8)) goto S4;
    if((c=='\"'_u8)) goto S5;
    in.set_pos(pos_take); return cap;
  S1:
    cap=5; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S2:
    cap=1; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S3:
    cap=2; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S4:
    cap=3; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S5:
    cap=4; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
} // Meta_Lexer_fsm_codes::REGEX_CODE_BEFORE


template<typename I>
size_t Meta_Lexer_fsm_codes::C_LIT_BEFORE(I& in,typename I::Pos* const heads) noexcept {
    using namespace yuki::literals;
    decltype(in.get()) c;
    size_t cap=0;
    const typename I::Pos pos_begin=in.get_pos();
    typename I::Pos pos_take=in.get_pos();
    (void)heads;
  S0:
    c=in.get();
    if((c<='&'_u8)
    || (c>='('_u8 && c<='['_u8)
    || (c>=']'_u8 && c<=0x10FFFF_u8/*􏿿*/)) goto S1;
    if((c=='\\'_u8)) goto S2;
    if((c=='\''_u8)) goto S3;
    in.set_pos(pos_take); return cap;
  S1:
    cap=3; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S2:
    cap=3; pos_take=in.get_pos();
    c=in.get();
    if((c<='\t'_u8)
    || (c=='\v'_u8 || c=='\f'_u8)
    || (c>=0xE_u8 && c<=0x10FFFF_u8/*􏿿*/)) goto S4;
    in.set_pos(pos_take); return cap;
  S3:
    cap=2; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S4:
    cap=1; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
} // Meta_Lexer_fsm_codes::C_LIT_BEFORE


template<typename I>
size_t Meta_Lexer_fsm_codes::S_LIT_BEFORE(I& in,typename I::Pos* const heads) noexcept {
    using namespace yuki::literals;
    decltype(in.get()) c;
    size_t cap=0;
    const typename I::Pos pos_begin=in.get_pos();
    typename I::Pos pos_take=in.get_pos();
    (void)heads;
  S0:
    c=in.get();
    if((c<='!'_u8)
    || (c>='#'_u8 && c<='['_u8)
    || (c>=']'_u8 && c<=0x10FFFF_u8/*􏿿*/)) goto S1;
    if((c=='\\'_u8)) goto S2;
    if((c=='\"'_u8)) goto S3;
    in.set_pos(pos_take); return cap;
  S1:
    cap=3; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S2:
    cap=3; pos_take=in.get_pos();
    c=in.get();
    if((c<='\t'_u8)
    || (c=='\v'_u8 || c=='\f'_u8)
    || (c>=0xE_u8 && c<=0x10FFFF_u8/*􏿿*/)) goto S4;
    in.set_pos(pos_take); return cap;
  S3:
    cap=2; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S4:
    cap=1; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
} // Meta_Lexer_fsm_codes::S_LIT_BEFORE


template<typename I>
size_t Meta_Lexer_fsm_codes::POST_REGEX(I& in,typename I::Pos* const heads) noexcept {
    using namespace yuki::literals;
    decltype(in.get()) c;
    size_t cap=0;
    const typename I::Pos pos_begin=in.get_pos();
    typename I::Pos pos_take=in.get_pos();
    (void)heads;
  S0:
    c=in.get();
    if((c>='\t'_u8 && c<='\r'_u8)
    || (c==' '_u8)
    || (c==0x85_u8/**/)
    || (c==0xA0_u8/* */)
    || (c==0x1680_u8/* */)
    || (c>=0x2000_u8/* */ && c<=0x200A_u8/* */)
    || (c==0x2028_u8/*LS*/ || c==0x2029_u8/*PS*/)
    || (c==0x202F_u8/* */)
    || (c==0x205F_u8/* */)
    || (c==0x3000_u8/*　*/)) goto S1;
    if((c=='}'_u8)) goto S2;
    if((c=='%'_u8)) goto S3;
    in.set_pos(pos_take); return cap;
  S1:
    c=in.get();
    if((c>='\t'_u8 && c<='\r'_u8)
    || (c==' '_u8)
    || (c==0x85_u8/**/)
    || (c==0xA0_u8/* */)
    || (c==0x1680_u8/* */)
    || (c>=0x2000_u8/* */ && c<=0x200A_u8/* */)
    || (c==0x2028_u8/*LS*/ || c==0x2029_u8/*PS*/)
    || (c==0x202F_u8/* */)
    || (c==0x205F_u8/* */)
    || (c==0x3000_u8/*　*/)) goto S1;
    if((c=='}'_u8)) goto S2;
    in.set_pos(pos_take); return cap;
  S2:
    cap=1; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S3:
    c=in.get();
    if((c=='%'_u8)) goto S4;
    in.set_pos(pos_take); return cap;
  S4:
    cap=2; pos_take=in.get_pos();
    c=in.get();
    if((c>='\t'_u8 && c<='\r'_u8)
    || (c==' '_u8)
    || (c==0x85_u8/**/)
    || (c==0xA0_u8/* */)
    || (c==0x1680_u8/* */)
    || (c>=0x2000_u8/* */ && c<=0x200A_u8/* */)
    || (c==0x2028_u8/*LS*/ || c==0x2029_u8/*PS*/)
    || (c==0x202F_u8/* */)
    || (c==0x205F_u8/* */)
    || (c==0x3000_u8/*　*/)) goto S5;
    in.set_pos(pos_take); return cap;
  S5:
    cap=2; pos_take=in.get_pos();
    c=in.get();
    if((c>='\t'_u8 && c<='\r'_u8)
    || (c==' '_u8)
    || (c==0x85_u8/**/)
    || (c==0xA0_u8/* */)
    || (c==0x1680_u8/* */)
    || (c>=0x2000_u8/* */ && c<=0x200A_u8/* */)
    || (c==0x2028_u8/*LS*/ || c==0x2029_u8/*PS*/)
    || (c==0x202F_u8/* */)
    || (c==0x205F_u8/* */)
    || (c==0x3000_u8/*　*/)) goto S5;
    in.set_pos(pos_take); return cap;
} // Meta_Lexer_fsm_codes::POST_REGEX


template<typename I>
size_t Meta_Lexer_fsm_codes::SEC2(I& in,typename I::Pos* const heads) noexcept {
    using namespace yuki::literals;
    decltype(in.get()) c;
    size_t cap=0;
    const typename I::Pos pos_begin=in.get_pos();
    typename I::Pos pos_take=in.get_pos();
    (void)heads;
  S0:
    c=in.get();
    if((c<=0x10FFFF_u8/*􏿿*/)) goto S1;
    in.set_pos(pos_take); return cap;
  S1:
    cap=1; pos_take=in.get_pos();
    c=in.get();
    if((c<=0x10FFFF_u8/*􏿿*/)) goto S1;
    in.set_pos(pos_take); return cap;
} // Meta_Lexer_fsm_codes::SEC2



int Meta_Lexer::lex(){
while(1){
const yuki::lex::U8Input::Pos pos_begin=in.get_pos();
switch(state){
case State::INITIAL:{
    clear_heads();
    switch(Meta_Lexer_fsm_codes::INITIAL(in,heads)){
    case 0:{
        if(!in.getable()){
            YUKI_LEX_Meta_Lexer_DBGO("State=INITIAL EOF\n");
            return int();
        }else{ // if(!in.getable())
            YUKI_LEX_Meta_Lexer_DBGO("State=INITIAL DEFAULT\n");
            fprintf(stderr,"YLEX Error: Lexer jammed at state INITIAL!\n");
            exit(EXIT_FAILURE);
        } // if(!in.getable()) else
        break;
    } // case 0
    case 1:{ // \%namespace\u{WSpace}*
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=INITIAL cap=1 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
state=State::O_NSPACE;
        }
        in.clear_matched();
        break;
    } // case 1 // \%namespace\u{WSpace}*
    case 2:{ // \%lexer\u{WSpace}*
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=INITIAL cap=2 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
state=State::O_LEXER;
        }
        in.clear_matched();
        break;
    } // case 2 // \%lexer\u{WSpace}*
    case 3:{ // \%input[_\-]class\u{WSpace}*
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=INITIAL cap=3 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
state=State::O_ICLASS;
        }
        in.clear_matched();
        break;
    } // case 3 // \%input[_\-]class\u{WSpace}*
    case 4:{ // \%input[_\-]header\u{WSpace}*
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=INITIAL cap=4 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
state=State::O_IHEADER;
        }
        in.clear_matched();
        break;
    } // case 4 // \%input[_\-]header\u{WSpace}*
    case 5:{ // \%debug[_\-]prefix\u{WSpace}*
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=INITIAL cap=5 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
state=State::O_DPREFIX;
        }
        in.clear_matched();
        break;
    } // case 5 // \%debug[_\-]prefix\u{WSpace}*
    case 6:{ // \%fsm[_\-]codes[_\-]namespace\u{WSpace}*
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=INITIAL cap=6 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
state=State::O_FCNSPACE;
        }
        in.clear_matched();
        break;
    } // case 6 // \%fsm[_\-]codes[_\-]namespace\u{WSpace}*
    case 7:{ // \%token[_\-]type\u{WSpace}*
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=INITIAL cap=7 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
state=State::O_TTYPE;
        }
        in.clear_matched();
        break;
    } // case 7 // \%token[_\-]type\u{WSpace}*
    case 8:{ // \%no[_\-]default[_\-]ctor\u{WSpace}*
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=INITIAL cap=8 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
no_default_ctor=true;
        }
        in.clear_matched();
        break;
    } // case 8 // \%no[_\-]default[_\-]ctor\u{WSpace}*
    case 9:{ // \%template\u{WSpace}*<.*
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=INITIAL cap=9 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
matched.remove_prefix(1); template_decl=matched;
        }
        in.clear_matched();
        break;
    } // case 9 // \%template\u{WSpace}*<.*
    case 10:{ // \%templated[_\-]lexer\u{WSpace}*
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=INITIAL cap=10 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
state=State::O_TPLEXER;
        }
        in.clear_matched();
        break;
    } // case 10 // \%templated[_\-]lexer\u{WSpace}*
    case 11:{ // \%code\u{WSpace}*
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=INITIAL cap=11 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
current_regex.clear(); state=State::CODE0;
        }
        in.clear_matched();
        break;
    } // case 11 // \%code\u{WSpace}*
    case 12:{ // [a-zA-Z_][0-9a-zA-Z_]*
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=INITIAL cap=12 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
current_regex=matched; state=State::MACRO_DEF_GOBBLE_SPACE;
        }
        in.clear_matched();
        break;
    } // case 12 // [a-zA-Z_][0-9a-zA-Z_]*
    case 13:{ // \%\%\u{WSpace}*
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=INITIAL cap=13 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
if(debug_prefix.empty())
        debug_prefix.append("YUKI_LEX_").append(lexer).append("_DBG");
    if(fsm_codes_nspace.empty())
        fsm_codes_nspace.append(lexer).append("_fsm_codes");
    if(!nspace.empty()){
        nspace_head.append("namespace ").append(nspace).push_back('{');
        nspace_tail.append("} // namespace ").append(nspace);
    }
    if(!template_decl.empty() && templated_lexer.empty()){
        fprintf(stderr,"Error: The lexer is templated but no templated name is given! (Note: Specify it by %%templated_lexer)\n");
        ++errors_;
        templated_lexer = lexer;
    }
    write_h0();
    state=State::SEC1;
        }
        in.clear_matched();
        break;
    } // case 13 // \%\%\u{WSpace}*
    case 14:{ // \u{WSpace}+
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=INITIAL cap=14 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {

        }
        in.clear_matched();
        break;
    } // case 14 // \u{WSpace}+
    case 15:{ // \/\/.*\R
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=INITIAL cap=15 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {

        }
        in.clear_matched();
        break;
    } // case 15 // \/\/.*\R
    } // switch(Meta_Lexer_fsm_codes::INITIAL(in,heads))
    break;
} // case State::INITIAL
case State::O_NSPACE:{
    clear_heads();
    switch(Meta_Lexer_fsm_codes::O_NSPACE(in,heads)){
    case 0:{
        if(!in.getable()){
            YUKI_LEX_Meta_Lexer_DBGO("State=O_NSPACE EOF\n");
            return int();
        }else{ // if(!in.getable())
            YUKI_LEX_Meta_Lexer_DBGO("State=O_NSPACE DEFAULT\n");
            fprintf(stderr,"YLEX Error: Lexer jammed at state O_NSPACE!\n");
            exit(EXIT_FAILURE);
        } // if(!in.getable()) else
        break;
    } // case 0
    case 1:{ // .*
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=O_NSPACE cap=1 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
nspace=matched;state=State::INITIAL;
        }
        in.clear_matched();
        break;
    } // case 1 // .*
    } // switch(Meta_Lexer_fsm_codes::O_NSPACE(in,heads))
    break;
} // case State::O_NSPACE
case State::O_LEXER:{
    clear_heads();
    switch(Meta_Lexer_fsm_codes::O_LEXER(in,heads)){
    case 0:{
        if(!in.getable()){
            YUKI_LEX_Meta_Lexer_DBGO("State=O_LEXER EOF\n");
            return int();
        }else{ // if(!in.getable())
            YUKI_LEX_Meta_Lexer_DBGO("State=O_LEXER DEFAULT\n");
            fprintf(stderr,"YLEX Error: Lexer jammed at state O_LEXER!\n");
            exit(EXIT_FAILURE);
        } // if(!in.getable()) else
        break;
    } // case 0
    case 1:{ // .*
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=O_LEXER cap=1 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
lexer=matched;state=State::INITIAL;
        }
        in.clear_matched();
        break;
    } // case 1 // .*
    } // switch(Meta_Lexer_fsm_codes::O_LEXER(in,heads))
    break;
} // case State::O_LEXER
case State::O_ICLASS:{
    clear_heads();
    switch(Meta_Lexer_fsm_codes::O_ICLASS(in,heads)){
    case 0:{
        if(!in.getable()){
            YUKI_LEX_Meta_Lexer_DBGO("State=O_ICLASS EOF\n");
            return int();
        }else{ // if(!in.getable())
            YUKI_LEX_Meta_Lexer_DBGO("State=O_ICLASS DEFAULT\n");
            fprintf(stderr,"YLEX Error: Lexer jammed at state O_ICLASS!\n");
            exit(EXIT_FAILURE);
        } // if(!in.getable()) else
        break;
    } // case 0
    case 1:{ // .*
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=O_ICLASS cap=1 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
input_class=matched;state=State::INITIAL;
        }
        in.clear_matched();
        break;
    } // case 1 // .*
    } // switch(Meta_Lexer_fsm_codes::O_ICLASS(in,heads))
    break;
} // case State::O_ICLASS
case State::O_IHEADER:{
    clear_heads();
    switch(Meta_Lexer_fsm_codes::O_IHEADER(in,heads)){
    case 0:{
        if(!in.getable()){
            YUKI_LEX_Meta_Lexer_DBGO("State=O_IHEADER EOF\n");
            return int();
        }else{ // if(!in.getable())
            YUKI_LEX_Meta_Lexer_DBGO("State=O_IHEADER DEFAULT\n");
            fprintf(stderr,"YLEX Error: Lexer jammed at state O_IHEADER!\n");
            exit(EXIT_FAILURE);
        } // if(!in.getable()) else
        break;
    } // case 0
    case 1:{ // .*
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=O_IHEADER cap=1 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
input_header=matched;state=State::INITIAL;
        }
        in.clear_matched();
        break;
    } // case 1 // .*
    } // switch(Meta_Lexer_fsm_codes::O_IHEADER(in,heads))
    break;
} // case State::O_IHEADER
case State::O_DPREFIX:{
    clear_heads();
    switch(Meta_Lexer_fsm_codes::O_DPREFIX(in,heads)){
    case 0:{
        if(!in.getable()){
            YUKI_LEX_Meta_Lexer_DBGO("State=O_DPREFIX EOF\n");
            return int();
        }else{ // if(!in.getable())
            YUKI_LEX_Meta_Lexer_DBGO("State=O_DPREFIX DEFAULT\n");
            fprintf(stderr,"YLEX Error: Lexer jammed at state O_DPREFIX!\n");
            exit(EXIT_FAILURE);
        } // if(!in.getable()) else
        break;
    } // case 0
    case 1:{ // .*
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=O_DPREFIX cap=1 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
debug_prefix=matched;state=State::INITIAL;
        }
        in.clear_matched();
        break;
    } // case 1 // .*
    } // switch(Meta_Lexer_fsm_codes::O_DPREFIX(in,heads))
    break;
} // case State::O_DPREFIX
case State::O_FCNSPACE:{
    clear_heads();
    switch(Meta_Lexer_fsm_codes::O_FCNSPACE(in,heads)){
    case 0:{
        if(!in.getable()){
            YUKI_LEX_Meta_Lexer_DBGO("State=O_FCNSPACE EOF\n");
            return int();
        }else{ // if(!in.getable())
            YUKI_LEX_Meta_Lexer_DBGO("State=O_FCNSPACE DEFAULT\n");
            fprintf(stderr,"YLEX Error: Lexer jammed at state O_FCNSPACE!\n");
            exit(EXIT_FAILURE);
        } // if(!in.getable()) else
        break;
    } // case 0
    case 1:{ // .*
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=O_FCNSPACE cap=1 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
fsm_codes_nspace=matched;state=State::INITIAL;
        }
        in.clear_matched();
        break;
    } // case 1 // .*
    } // switch(Meta_Lexer_fsm_codes::O_FCNSPACE(in,heads))
    break;
} // case State::O_FCNSPACE
case State::O_TTYPE:{
    clear_heads();
    switch(Meta_Lexer_fsm_codes::O_TTYPE(in,heads)){
    case 0:{
        if(!in.getable()){
            YUKI_LEX_Meta_Lexer_DBGO("State=O_TTYPE EOF\n");
            return int();
        }else{ // if(!in.getable())
            YUKI_LEX_Meta_Lexer_DBGO("State=O_TTYPE DEFAULT\n");
            fprintf(stderr,"YLEX Error: Lexer jammed at state O_TTYPE!\n");
            exit(EXIT_FAILURE);
        } // if(!in.getable()) else
        break;
    } // case 0
    case 1:{ // .*
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=O_TTYPE cap=1 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
token_type=matched;state=State::INITIAL;
        }
        in.clear_matched();
        break;
    } // case 1 // .*
    } // switch(Meta_Lexer_fsm_codes::O_TTYPE(in,heads))
    break;
} // case State::O_TTYPE
case State::O_TPLEXER:{
    clear_heads();
    switch(Meta_Lexer_fsm_codes::O_TPLEXER(in,heads)){
    case 0:{
        if(!in.getable()){
            YUKI_LEX_Meta_Lexer_DBGO("State=O_TPLEXER EOF\n");
            return int();
        }else{ // if(!in.getable())
            YUKI_LEX_Meta_Lexer_DBGO("State=O_TPLEXER DEFAULT\n");
            fprintf(stderr,"YLEX Error: Lexer jammed at state O_TPLEXER!\n");
            exit(EXIT_FAILURE);
        } // if(!in.getable()) else
        break;
    } // case 0
    case 1:{ // .*
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=O_TPLEXER cap=1 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
templated_lexer=matched;state=State::INITIAL;
        }
        in.clear_matched();
        break;
    } // case 1 // .*
    } // switch(Meta_Lexer_fsm_codes::O_TPLEXER(in,heads))
    break;
} // case State::O_TPLEXER
case State::MACRO_DEF_GOBBLE_SPACE:{
    clear_heads();
    switch(Meta_Lexer_fsm_codes::MACRO_DEF_GOBBLE_SPACE(in,heads)){
    case 0:{
        if(!in.getable()){
            YUKI_LEX_Meta_Lexer_DBGO("State=MACRO_DEF_GOBBLE_SPACE EOF\n");
            return int();
        }else{ // if(!in.getable())
            YUKI_LEX_Meta_Lexer_DBGO("State=MACRO_DEF_GOBBLE_SPACE DEFAULT\n");
            {
state=State::MACRO_DEF;
            }
        } // if(!in.getable()) else
        break;
    } // case 0
    case 1:{ // \u{WSpace}+
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=MACRO_DEF_GOBBLE_SPACE cap=1 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {

        }
        in.clear_matched();
        break;
    } // case 1 // \u{WSpace}+
    } // switch(Meta_Lexer_fsm_codes::MACRO_DEF_GOBBLE_SPACE(in,heads))
    break;
} // case State::MACRO_DEF_GOBBLE_SPACE
case State::MACRO_DEF:{
    clear_heads();
    switch(Meta_Lexer_fsm_codes::MACRO_DEF(in,heads)){
    case 0:{
        if(!in.getable()){
            YUKI_LEX_Meta_Lexer_DBGO("State=MACRO_DEF EOF\n");
            return int();
        }else{ // if(!in.getable())
            YUKI_LEX_Meta_Lexer_DBGO("State=MACRO_DEF DEFAULT\n");
            fprintf(stderr,"YLEX Error: Lexer jammed at state MACRO_DEF!\n");
            exit(EXIT_FAILURE);
        } // if(!in.getable()) else
        break;
    } // case 0
    case 1:{ // .*(?=\R)
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=MACRO_DEF cap=1 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
str_temp.assign("(");
    str_temp.append(matched).push_back(')');
    const std::pair<yuki::unordered_map_str<std::string,std::string>::iterator,bool> emplace_ret = rl.macro_table.try_emplace(std::move(current_regex),std::move(str_temp));
    if(!emplace_ret.second){
        fprintf(stderr,"Error: Multiple definition of macro \"%s\"!\n",emplace_ret.first->first.c_str());
        ++errors_;
    }
    state=State::INITIAL;
        }
        in.clear_matched();
        break;
    } // case 1 // .*(?=\R)
    } // switch(Meta_Lexer_fsm_codes::MACRO_DEF(in,heads))
    break;
} // case State::MACRO_DEF
case State::CODE0:{
    clear_heads();
    switch(Meta_Lexer_fsm_codes::CODE0(in,heads)){
    case 0:{
        if(!in.getable()){
            YUKI_LEX_Meta_Lexer_DBGO("State=CODE0 EOF\n");
            return int();
        }else{ // if(!in.getable())
            YUKI_LEX_Meta_Lexer_DBGO("State=CODE0 DEFAULT\n");
            fprintf(stderr,"YLEX Error: Lexer jammed at state CODE0!\n");
            exit(EXIT_FAILURE);
        } // if(!in.getable()) else
        break;
    } // case 0
    case 1:{ // \u{WSpace}+
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=CODE0 cap=1 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {

        }
        in.clear_matched();
        break;
    } // case 1 // \u{WSpace}+
    case 2:{ // \/\/.*\R
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=CODE0 cap=2 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {

        }
        in.clear_matched();
        break;
    } // case 2 // \/\/.*\R
    case 3:{ // \{
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=CODE0 cap=3 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
brace_level=0;
    str_temp.clear();
    state=State::CODE1;
        }
        in.clear_matched();
        break;
    } // case 3 // \{
    case 4:{ // .
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=CODE0 cap=4 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
current_regex.append(matched);
        }
        in.clear_matched();
        break;
    } // case 4 // .
    } // switch(Meta_Lexer_fsm_codes::CODE0(in,heads))
    break;
} // case State::CODE0
case State::CODE1:{
    clear_heads();
    switch(Meta_Lexer_fsm_codes::CODE1(in,heads)){
    case 0:{
        if(!in.getable()){
            YUKI_LEX_Meta_Lexer_DBGO("State=CODE1 EOF\n");
            return int();
        }else{ // if(!in.getable())
            YUKI_LEX_Meta_Lexer_DBGO("State=CODE1 DEFAULT\n");
            fprintf(stderr,"YLEX Error: Lexer jammed at state CODE1!\n");
            exit(EXIT_FAILURE);
        } // if(!in.getable()) else
        break;
    } // case 0
    case 1:{ // \{
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=CODE1 cap=1 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
++brace_level;str_temp.push_back('{');
        }
        in.clear_matched();
        break;
    } // case 1 // \{
    case 2:{ // \}
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=CODE1 cap=2 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
if(brace_level!=0){
        --brace_level;
        str_temp.push_back('}');
    }else{
        str_temp.resize(yuki::remove_trailing(str_temp.begin(),str_temp.end(),[](const char c){return isspace(static_cast<unsigned char>(c));}));
        const std::pair<yuki::unordered_map_str<std::string,std::string>::iterator,bool> emplace_ret = code_htable.try_emplace(std::move(current_regex),std::move(str_temp));
        if(!emplace_ret.second){
            fprintf(stderr,"Error: Multiple definition of code section \"%s\"!\n",emplace_ret.first->first.c_str());
            ++errors_;
        }
        state=State::INITIAL;
    }
        }
        in.clear_matched();
        break;
    } // case 2 // \}
    case 3:{ // '
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=CODE1 cap=3 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
str_temp.push_back('\''); state_prev=State::CODE1; state=State::C_LIT;
        }
        in.clear_matched();
        break;
    } // case 3 // '
    case 4:{ // "
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=CODE1 cap=4 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
str_temp.push_back('\"'); state_prev=State::CODE1; state=State::S_LIT;
        }
        in.clear_matched();
        break;
    } // case 4 // "
    case 5:{ // \u{All}
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=CODE1 cap=5 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
str_temp.append(matched);
        }
        in.clear_matched();
        break;
    } // case 5 // \u{All}
    } // switch(Meta_Lexer_fsm_codes::CODE1(in,heads))
    break;
} // case State::CODE1
case State::C_LIT:{
    clear_heads();
    switch(Meta_Lexer_fsm_codes::C_LIT(in,heads)){
    case 0:{
        if(!in.getable()){
            YUKI_LEX_Meta_Lexer_DBGO("State=C_LIT EOF\n");
            return int();
        }else{ // if(!in.getable())
            YUKI_LEX_Meta_Lexer_DBGO("State=C_LIT DEFAULT\n");
            fprintf(stderr,"YLEX Error: Lexer jammed at state C_LIT!\n");
            exit(EXIT_FAILURE);
        } // if(!in.getable()) else
        break;
    } // case 0
    case 1:{ // \\.
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=C_LIT cap=1 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
str_temp.append(matched);
        }
        in.clear_matched();
        break;
    } // case 1 // \\.
    case 2:{ // '
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=C_LIT cap=2 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
str_temp.push_back('\''); state=state_prev;
        }
        in.clear_matched();
        break;
    } // case 2 // '
    case 3:{ // \u{All}
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=C_LIT cap=3 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
str_temp.append(matched);
        }
        in.clear_matched();
        break;
    } // case 3 // \u{All}
    } // switch(Meta_Lexer_fsm_codes::C_LIT(in,heads))
    break;
} // case State::C_LIT
case State::S_LIT:{
    clear_heads();
    switch(Meta_Lexer_fsm_codes::S_LIT(in,heads)){
    case 0:{
        if(!in.getable()){
            YUKI_LEX_Meta_Lexer_DBGO("State=S_LIT EOF\n");
            return int();
        }else{ // if(!in.getable())
            YUKI_LEX_Meta_Lexer_DBGO("State=S_LIT DEFAULT\n");
            fprintf(stderr,"YLEX Error: Lexer jammed at state S_LIT!\n");
            exit(EXIT_FAILURE);
        } // if(!in.getable()) else
        break;
    } // case 0
    case 1:{ // \\.
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=S_LIT cap=1 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
str_temp.append(matched);
        }
        in.clear_matched();
        break;
    } // case 1 // \\.
    case 2:{ // "
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=S_LIT cap=2 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
str_temp.push_back('\"'); state=state_prev;
        }
        in.clear_matched();
        break;
    } // case 2 // "
    case 3:{ // \u{All}
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=S_LIT cap=3 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
str_temp.append(matched);
        }
        in.clear_matched();
        break;
    } // case 3 // \u{All}
    } // switch(Meta_Lexer_fsm_codes::S_LIT(in,heads))
    break;
} // case State::S_LIT
case State::SEC1:{
    clear_heads();
    switch(Meta_Lexer_fsm_codes::SEC1(in,heads)){
    case 0:{
        if(!in.getable()){
            YUKI_LEX_Meta_Lexer_DBGO("State=SEC1 EOF\n");
            return int();
        }else{ // if(!in.getable())
            YUKI_LEX_Meta_Lexer_DBGO("State=SEC1 DEFAULT\n");
            fprintf(stderr,"YLEX Error: Lexer jammed at state SEC1!\n");
            exit(EXIT_FAILURE);
        } // if(!in.getable()) else
        break;
    } // case 0
    case 1:{ // <[^>]*>\{
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=SEC1 cap=1 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
current_fsm_name=matched.substr(1,matched.size()-3);
    if(current_fsm_name.compare("INITIAL")==0)
        initial_encountered=true;
    rp.recycle();
    state=State::GOBBLE_NEWLINE_TO_REGEX;
        }
        in.clear_matched();
        break;
    } // case 1 // <[^>]*>\{
    case 2:{ // \%\%\u{WSpace}*
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=SEC1 cap=2 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
if(!initial_encountered){
        fprintf(stderr,"Error: No \"INITIAL\" state found!\n");
        ++errors_;
    }
    write_lex_and_h1();
    state=State::SEC2;
        }
        in.clear_matched();
        break;
    } // case 2 // \%\%\u{WSpace}*
    case 3:{ // \u{WSpace}+
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=SEC1 cap=3 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {

        }
        in.clear_matched();
        break;
    } // case 3 // \u{WSpace}+
    case 4:{ // \/\/.*\R
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=SEC1 cap=4 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {

        }
        in.clear_matched();
        break;
    } // case 4 // \/\/.*\R
    } // switch(Meta_Lexer_fsm_codes::SEC1(in,heads))
    break;
} // case State::SEC1
case State::GOBBLE_NEWLINE_TO_REGEX:{
    clear_heads();
    switch(Meta_Lexer_fsm_codes::GOBBLE_NEWLINE_TO_REGEX(in,heads)){
    case 0:{
        if(!in.getable()){
            YUKI_LEX_Meta_Lexer_DBGO("State=GOBBLE_NEWLINE_TO_REGEX EOF\n");
            return int();
        }else{ // if(!in.getable())
            YUKI_LEX_Meta_Lexer_DBGO("State=GOBBLE_NEWLINE_TO_REGEX DEFAULT\n");
            {
state=State::REGEX;
            }
        } // if(!in.getable()) else
        break;
    } // case 0
    case 1:{ // \R+
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=GOBBLE_NEWLINE_TO_REGEX cap=1 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {

        }
        in.clear_matched();
        break;
    } // case 1 // \R+
    } // switch(Meta_Lexer_fsm_codes::GOBBLE_NEWLINE_TO_REGEX(in,heads))
    break;
} // case State::GOBBLE_NEWLINE_TO_REGEX
case State::REGEX:{
    clear_heads();
    switch(Meta_Lexer_fsm_codes::REGEX(in,heads)){
    case 0:{
        if(!in.getable()){
            YUKI_LEX_Meta_Lexer_DBGO("State=REGEX EOF\n");
            return int();
        }else{ // if(!in.getable())
            YUKI_LEX_Meta_Lexer_DBGO("State=REGEX DEFAULT\n");
            fprintf(stderr,"YLEX Error: Lexer jammed at state REGEX!\n");
            exit(EXIT_FAILURE);
        } // if(!in.getable()) else
        break;
    } // case 0
    case 1:{ // \u{WSpace}+\{\u{WSpace}*
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=REGEX cap=1 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
rl.in.set_source(current_regex);
    rp.parse();
    #ifndef YUKI_LEX_MAX_REGEX_PRINTABLE
    #define YUKI_LEX_MAX_REGEX_PRINTABLE 256
    #endif
    if(current_regex.size()>YUKI_LEX_MAX_REGEX_PRINTABLE)
        current_regex.resize(YUKI_LEX_MAX_REGEX_PRINTABLE);
    brace_level=0;
    state=State::REGEX_CODE;
        }
        in.clear_matched();
        break;
    } // case 1 // \u{WSpace}+\{\u{WSpace}*
    case 2:{ // <<EOF>>\u{WSpace}+\{\u{WSpace}*
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=REGEX cap=2 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
brace_level=0;
    current_eof.clear();
    state=State::REGEX_CODE_EOF;
        }
        in.clear_matched();
        break;
    } // case 2 // <<EOF>>\u{WSpace}+\{\u{WSpace}*
    case 3:{ // <<DEFAULT>>\u{WSpace}+\{\u{WSpace}*
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=REGEX cap=3 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
brace_level=0;
    current_default.clear();
    state=State::REGEX_CODE_DEFAULT;
        }
        in.clear_matched();
        break;
    } // case 3 // <<DEFAULT>>\u{WSpace}+\{\u{WSpace}*
    case 4:{ // <<BEFORE>>\u{WSpace}+\{\u{WSpace}*
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=REGEX cap=4 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
brace_level=0;
    current_before.clear();
    state=State::REGEX_CODE_BEFORE;
        }
        in.clear_matched();
        break;
    } // case 4 // <<BEFORE>>\u{WSpace}+\{\u{WSpace}*
    case 5:{ // .
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=REGEX cap=5 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
current_regex.append(matched);
        }
        in.clear_matched();
        break;
    } // case 5 // .
    } // switch(Meta_Lexer_fsm_codes::REGEX(in,heads))
    break;
} // case State::REGEX
case State::REGEX_CODE:{
    clear_heads();
    switch(Meta_Lexer_fsm_codes::REGEX_CODE(in,heads)){
    case 0:{
        if(!in.getable()){
            YUKI_LEX_Meta_Lexer_DBGO("State=REGEX_CODE EOF\n");
            return int();
        }else{ // if(!in.getable())
            YUKI_LEX_Meta_Lexer_DBGO("State=REGEX_CODE DEFAULT\n");
            fprintf(stderr,"YLEX Error: Lexer jammed at state REGEX_CODE!\n");
            exit(EXIT_FAILURE);
        } // if(!in.getable()) else
        break;
    } // case 0
    case 1:{ // \{
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=REGEX_CODE cap=1 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
++brace_level;str_temp.push_back('{');
        }
        in.clear_matched();
        break;
    } // case 1 // \{
    case 2:{ // \}
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=REGEX_CODE cap=2 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
if(brace_level!=0){
        --brace_level;
        str_temp.push_back('}');
    }else{
        str_temp.resize(yuki::remove_trailing(str_temp.begin(),str_temp.end(),[](const char c){return isspace(static_cast<unsigned char>(c));}));
        current_regex.resize(yuki::remove_trailing(current_regex.begin(),current_regex.end(),[](const char c){return isspace(static_cast<unsigned char>(c));}));
        current_regex_codes.emplace_back(std::move(current_regex),std::move(str_temp));
        state=State::DISCARD_EVERYTHING_UNTIL_NEWLINE_TO_POST_REGEX;
    }
        }
        in.clear_matched();
        break;
    } // case 2 // \}
    case 3:{ // '
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=REGEX_CODE cap=3 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
str_temp.push_back('\''); state_prev=State::REGEX_CODE; state=State::C_LIT;
        }
        in.clear_matched();
        break;
    } // case 3 // '
    case 4:{ // "
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=REGEX_CODE cap=4 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
str_temp.push_back('\"'); state_prev=State::REGEX_CODE; state=State::S_LIT;
        }
        in.clear_matched();
        break;
    } // case 4 // "
    case 5:{ // \u{All}
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=REGEX_CODE cap=5 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
str_temp.append(matched);
        }
        in.clear_matched();
        break;
    } // case 5 // \u{All}
    } // switch(Meta_Lexer_fsm_codes::REGEX_CODE(in,heads))
    break;
} // case State::REGEX_CODE
case State::DISCARD_EVERYTHING_UNTIL_NEWLINE_TO_POST_REGEX:{
    clear_heads();
    switch(Meta_Lexer_fsm_codes::DISCARD_EVERYTHING_UNTIL_NEWLINE_TO_POST_REGEX(in,heads)){
    case 0:{
        if(!in.getable()){
            YUKI_LEX_Meta_Lexer_DBGO("State=DISCARD_EVERYTHING_UNTIL_NEWLINE_TO_POST_REGEX EOF\n");
            return int();
        }else{ // if(!in.getable())
            YUKI_LEX_Meta_Lexer_DBGO("State=DISCARD_EVERYTHING_UNTIL_NEWLINE_TO_POST_REGEX DEFAULT\n");
            fprintf(stderr,"YLEX Error: Lexer jammed at state DISCARD_EVERYTHING_UNTIL_NEWLINE_TO_POST_REGEX!\n");
            exit(EXIT_FAILURE);
        } // if(!in.getable()) else
        break;
    } // case 0
    case 1:{ // .*\R+
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=DISCARD_EVERYTHING_UNTIL_NEWLINE_TO_POST_REGEX cap=1 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
state=State::POST_REGEX;
        }
        in.clear_matched();
        break;
    } // case 1 // .*\R+
    } // switch(Meta_Lexer_fsm_codes::DISCARD_EVERYTHING_UNTIL_NEWLINE_TO_POST_REGEX(in,heads))
    break;
} // case State::DISCARD_EVERYTHING_UNTIL_NEWLINE_TO_POST_REGEX
case State::REGEX_CODE_EOF:{
    clear_heads();
    switch(Meta_Lexer_fsm_codes::REGEX_CODE_EOF(in,heads)){
    case 0:{
        if(!in.getable()){
            YUKI_LEX_Meta_Lexer_DBGO("State=REGEX_CODE_EOF EOF\n");
            return int();
        }else{ // if(!in.getable())
            YUKI_LEX_Meta_Lexer_DBGO("State=REGEX_CODE_EOF DEFAULT\n");
            fprintf(stderr,"YLEX Error: Lexer jammed at state REGEX_CODE_EOF!\n");
            exit(EXIT_FAILURE);
        } // if(!in.getable()) else
        break;
    } // case 0
    case 1:{ // \{
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=REGEX_CODE_EOF cap=1 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
++brace_level;current_eof.push_back('{');
        }
        in.clear_matched();
        break;
    } // case 1 // \{
    case 2:{ // \}
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=REGEX_CODE_EOF cap=2 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
if(brace_level!=0){
        --brace_level;
        current_eof.push_back('}');
    }else{
        current_eof.resize(yuki::remove_trailing(current_eof.begin(),current_eof.end(),[](const char c){return isspace(static_cast<unsigned char>(c));}));
        state=State::DISCARD_EVERYTHING_UNTIL_NEWLINE_TO_POST_REGEX;
    }
        }
        in.clear_matched();
        break;
    } // case 2 // \}
    case 3:{ // '
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=REGEX_CODE_EOF cap=3 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
current_eof.push_back('\''); state=State::C_LIT_EOF;
        }
        in.clear_matched();
        break;
    } // case 3 // '
    case 4:{ // "
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=REGEX_CODE_EOF cap=4 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
current_eof.push_back('\"'); state=State::S_LIT_EOF;
        }
        in.clear_matched();
        break;
    } // case 4 // "
    case 5:{ // \u{All}
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=REGEX_CODE_EOF cap=5 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
current_eof.append(matched);
        }
        in.clear_matched();
        break;
    } // case 5 // \u{All}
    } // switch(Meta_Lexer_fsm_codes::REGEX_CODE_EOF(in,heads))
    break;
} // case State::REGEX_CODE_EOF
case State::C_LIT_EOF:{
    clear_heads();
    switch(Meta_Lexer_fsm_codes::C_LIT_EOF(in,heads)){
    case 0:{
        if(!in.getable()){
            YUKI_LEX_Meta_Lexer_DBGO("State=C_LIT_EOF EOF\n");
            return int();
        }else{ // if(!in.getable())
            YUKI_LEX_Meta_Lexer_DBGO("State=C_LIT_EOF DEFAULT\n");
            fprintf(stderr,"YLEX Error: Lexer jammed at state C_LIT_EOF!\n");
            exit(EXIT_FAILURE);
        } // if(!in.getable()) else
        break;
    } // case 0
    case 1:{ // \\.
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=C_LIT_EOF cap=1 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
current_eof.append(matched);
        }
        in.clear_matched();
        break;
    } // case 1 // \\.
    case 2:{ // '
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=C_LIT_EOF cap=2 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
current_eof.push_back('\''); state=State::REGEX_CODE_EOF;
        }
        in.clear_matched();
        break;
    } // case 2 // '
    case 3:{ // \u{All}
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=C_LIT_EOF cap=3 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
current_eof.append(matched);
        }
        in.clear_matched();
        break;
    } // case 3 // \u{All}
    } // switch(Meta_Lexer_fsm_codes::C_LIT_EOF(in,heads))
    break;
} // case State::C_LIT_EOF
case State::S_LIT_EOF:{
    clear_heads();
    switch(Meta_Lexer_fsm_codes::S_LIT_EOF(in,heads)){
    case 0:{
        if(!in.getable()){
            YUKI_LEX_Meta_Lexer_DBGO("State=S_LIT_EOF EOF\n");
            return int();
        }else{ // if(!in.getable())
            YUKI_LEX_Meta_Lexer_DBGO("State=S_LIT_EOF DEFAULT\n");
            fprintf(stderr,"YLEX Error: Lexer jammed at state S_LIT_EOF!\n");
            exit(EXIT_FAILURE);
        } // if(!in.getable()) else
        break;
    } // case 0
    case 1:{ // \\.
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=S_LIT_EOF cap=1 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
current_eof.append(matched);
        }
        in.clear_matched();
        break;
    } // case 1 // \\.
    case 2:{ // "
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=S_LIT_EOF cap=2 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
current_eof.push_back('\"'); state=State::REGEX_CODE_EOF;
        }
        in.clear_matched();
        break;
    } // case 2 // "
    case 3:{ // \u{All}
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=S_LIT_EOF cap=3 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
current_eof.append(matched);
        }
        in.clear_matched();
        break;
    } // case 3 // \u{All}
    } // switch(Meta_Lexer_fsm_codes::S_LIT_EOF(in,heads))
    break;
} // case State::S_LIT_EOF
case State::REGEX_CODE_DEFAULT:{
    clear_heads();
    switch(Meta_Lexer_fsm_codes::REGEX_CODE_DEFAULT(in,heads)){
    case 0:{
        if(!in.getable()){
            YUKI_LEX_Meta_Lexer_DBGO("State=REGEX_CODE_DEFAULT EOF\n");
            return int();
        }else{ // if(!in.getable())
            YUKI_LEX_Meta_Lexer_DBGO("State=REGEX_CODE_DEFAULT DEFAULT\n");
            fprintf(stderr,"YLEX Error: Lexer jammed at state REGEX_CODE_DEFAULT!\n");
            exit(EXIT_FAILURE);
        } // if(!in.getable()) else
        break;
    } // case 0
    case 1:{ // \{
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=REGEX_CODE_DEFAULT cap=1 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
++brace_level;current_default.push_back('{');
        }
        in.clear_matched();
        break;
    } // case 1 // \{
    case 2:{ // \}
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=REGEX_CODE_DEFAULT cap=2 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
if(brace_level!=0){
        --brace_level;
        current_default.push_back('}');
    }else{
        current_default.resize(yuki::remove_trailing(current_default.begin(),current_default.end(),[](const char c){return isspace(static_cast<unsigned char>(c));}));
        state=State::DISCARD_EVERYTHING_UNTIL_NEWLINE_TO_POST_REGEX;
    }
        }
        in.clear_matched();
        break;
    } // case 2 // \}
    case 3:{ // '
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=REGEX_CODE_DEFAULT cap=3 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
current_default.push_back('\''); state=State::C_LIT_DEFAULT;
        }
        in.clear_matched();
        break;
    } // case 3 // '
    case 4:{ // "
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=REGEX_CODE_DEFAULT cap=4 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
current_default.push_back('\"'); state=State::S_LIT_DEFAULT;
        }
        in.clear_matched();
        break;
    } // case 4 // "
    case 5:{ // \u{All}
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=REGEX_CODE_DEFAULT cap=5 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
current_default.append(matched);
        }
        in.clear_matched();
        break;
    } // case 5 // \u{All}
    } // switch(Meta_Lexer_fsm_codes::REGEX_CODE_DEFAULT(in,heads))
    break;
} // case State::REGEX_CODE_DEFAULT
case State::C_LIT_DEFAULT:{
    clear_heads();
    switch(Meta_Lexer_fsm_codes::C_LIT_DEFAULT(in,heads)){
    case 0:{
        if(!in.getable()){
            YUKI_LEX_Meta_Lexer_DBGO("State=C_LIT_DEFAULT EOF\n");
            return int();
        }else{ // if(!in.getable())
            YUKI_LEX_Meta_Lexer_DBGO("State=C_LIT_DEFAULT DEFAULT\n");
            fprintf(stderr,"YLEX Error: Lexer jammed at state C_LIT_DEFAULT!\n");
            exit(EXIT_FAILURE);
        } // if(!in.getable()) else
        break;
    } // case 0
    case 1:{ // \\.
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=C_LIT_DEFAULT cap=1 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
current_default.append(matched);
        }
        in.clear_matched();
        break;
    } // case 1 // \\.
    case 2:{ // '
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=C_LIT_DEFAULT cap=2 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
current_default.push_back('\''); state=State::REGEX_CODE_DEFAULT;
        }
        in.clear_matched();
        break;
    } // case 2 // '
    case 3:{ // \u{All}
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=C_LIT_DEFAULT cap=3 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
current_default.append(matched);
        }
        in.clear_matched();
        break;
    } // case 3 // \u{All}
    } // switch(Meta_Lexer_fsm_codes::C_LIT_DEFAULT(in,heads))
    break;
} // case State::C_LIT_DEFAULT
case State::S_LIT_DEFAULT:{
    clear_heads();
    switch(Meta_Lexer_fsm_codes::S_LIT_DEFAULT(in,heads)){
    case 0:{
        if(!in.getable()){
            YUKI_LEX_Meta_Lexer_DBGO("State=S_LIT_DEFAULT EOF\n");
            return int();
        }else{ // if(!in.getable())
            YUKI_LEX_Meta_Lexer_DBGO("State=S_LIT_DEFAULT DEFAULT\n");
            fprintf(stderr,"YLEX Error: Lexer jammed at state S_LIT_DEFAULT!\n");
            exit(EXIT_FAILURE);
        } // if(!in.getable()) else
        break;
    } // case 0
    case 1:{ // \\.
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=S_LIT_DEFAULT cap=1 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
current_default.append(matched);
        }
        in.clear_matched();
        break;
    } // case 1 // \\.
    case 2:{ // "
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=S_LIT_DEFAULT cap=2 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
current_default.push_back('\"'); state=State::REGEX_CODE_DEFAULT;
        }
        in.clear_matched();
        break;
    } // case 2 // "
    case 3:{ // \u{All}
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=S_LIT_DEFAULT cap=3 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
current_default.append(matched);
        }
        in.clear_matched();
        break;
    } // case 3 // \u{All}
    } // switch(Meta_Lexer_fsm_codes::S_LIT_DEFAULT(in,heads))
    break;
} // case State::S_LIT_DEFAULT
case State::REGEX_CODE_BEFORE:{
    clear_heads();
    switch(Meta_Lexer_fsm_codes::REGEX_CODE_BEFORE(in,heads)){
    case 0:{
        if(!in.getable()){
            YUKI_LEX_Meta_Lexer_DBGO("State=REGEX_CODE_BEFORE EOF\n");
            return int();
        }else{ // if(!in.getable())
            YUKI_LEX_Meta_Lexer_DBGO("State=REGEX_CODE_BEFORE DEFAULT\n");
            fprintf(stderr,"YLEX Error: Lexer jammed at state REGEX_CODE_BEFORE!\n");
            exit(EXIT_FAILURE);
        } // if(!in.getable()) else
        break;
    } // case 0
    case 1:{ // \{
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=REGEX_CODE_BEFORE cap=1 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
++brace_level;current_before.push_back('{');
        }
        in.clear_matched();
        break;
    } // case 1 // \{
    case 2:{ // \}
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=REGEX_CODE_BEFORE cap=2 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
if(brace_level!=0){
        --brace_level;
        current_before.push_back('}');
    }else{
        current_before.resize(yuki::remove_trailing(current_before.begin(),current_before.end(),[](const char c){return isspace(static_cast<unsigned char>(c));}));
        state=State::DISCARD_EVERYTHING_UNTIL_NEWLINE_TO_POST_REGEX;
    }
        }
        in.clear_matched();
        break;
    } // case 2 // \}
    case 3:{ // '
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=REGEX_CODE_BEFORE cap=3 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
current_before.push_back('\''); state=State::C_LIT_BEFORE;
        }
        in.clear_matched();
        break;
    } // case 3 // '
    case 4:{ // "
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=REGEX_CODE_BEFORE cap=4 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
current_before.push_back('\"'); state=State::S_LIT_BEFORE;
        }
        in.clear_matched();
        break;
    } // case 4 // "
    case 5:{ // \u{All}
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=REGEX_CODE_BEFORE cap=5 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
current_before.append(matched);
        }
        in.clear_matched();
        break;
    } // case 5 // \u{All}
    } // switch(Meta_Lexer_fsm_codes::REGEX_CODE_BEFORE(in,heads))
    break;
} // case State::REGEX_CODE_BEFORE
case State::C_LIT_BEFORE:{
    clear_heads();
    switch(Meta_Lexer_fsm_codes::C_LIT_BEFORE(in,heads)){
    case 0:{
        if(!in.getable()){
            YUKI_LEX_Meta_Lexer_DBGO("State=C_LIT_BEFORE EOF\n");
            return int();
        }else{ // if(!in.getable())
            YUKI_LEX_Meta_Lexer_DBGO("State=C_LIT_BEFORE DEFAULT\n");
            fprintf(stderr,"YLEX Error: Lexer jammed at state C_LIT_BEFORE!\n");
            exit(EXIT_FAILURE);
        } // if(!in.getable()) else
        break;
    } // case 0
    case 1:{ // \\.
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=C_LIT_BEFORE cap=1 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
current_before.append(matched);
        }
        in.clear_matched();
        break;
    } // case 1 // \\.
    case 2:{ // '
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=C_LIT_BEFORE cap=2 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
current_before.push_back('\''); state=State::REGEX_CODE_BEFORE;
        }
        in.clear_matched();
        break;
    } // case 2 // '
    case 3:{ // \u{All}
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=C_LIT_BEFORE cap=3 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
current_before.append(matched);
        }
        in.clear_matched();
        break;
    } // case 3 // \u{All}
    } // switch(Meta_Lexer_fsm_codes::C_LIT_BEFORE(in,heads))
    break;
} // case State::C_LIT_BEFORE
case State::S_LIT_BEFORE:{
    clear_heads();
    switch(Meta_Lexer_fsm_codes::S_LIT_BEFORE(in,heads)){
    case 0:{
        if(!in.getable()){
            YUKI_LEX_Meta_Lexer_DBGO("State=S_LIT_BEFORE EOF\n");
            return int();
        }else{ // if(!in.getable())
            YUKI_LEX_Meta_Lexer_DBGO("State=S_LIT_BEFORE DEFAULT\n");
            fprintf(stderr,"YLEX Error: Lexer jammed at state S_LIT_BEFORE!\n");
            exit(EXIT_FAILURE);
        } // if(!in.getable()) else
        break;
    } // case 0
    case 1:{ // \\.
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=S_LIT_BEFORE cap=1 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
current_before.append(matched);
        }
        in.clear_matched();
        break;
    } // case 1 // \\.
    case 2:{ // "
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=S_LIT_BEFORE cap=2 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
current_before.push_back('\"'); state=State::REGEX_CODE_BEFORE;
        }
        in.clear_matched();
        break;
    } // case 2 // "
    case 3:{ // \u{All}
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=S_LIT_BEFORE cap=3 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
current_before.append(matched);
        }
        in.clear_matched();
        break;
    } // case 3 // \u{All}
    } // switch(Meta_Lexer_fsm_codes::S_LIT_BEFORE(in,heads))
    break;
} // case State::S_LIT_BEFORE
case State::POST_REGEX:{
    clear_heads();
    switch(Meta_Lexer_fsm_codes::POST_REGEX(in,heads)){
    case 0:{
        if(!in.getable()){
            YUKI_LEX_Meta_Lexer_DBGO("State=POST_REGEX EOF\n");
            return int();
        }else{ // if(!in.getable())
            YUKI_LEX_Meta_Lexer_DBGO("State=POST_REGEX DEFAULT\n");
            {
state=State::REGEX;
            }
        } // if(!in.getable()) else
        break;
    } // case 0
    case 1:{ // \u{WSpace}*\}
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=POST_REGEX cap=1 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
if(rp.heads().size()>max_heads)
        max_heads = rp.heads().size();
    write_fsm_code_wrapped();
    named_regex_codes.emplace_back(std::move(current_fsm_name),std::move(current_regex_codes),std::move(current_eof),std::move(current_default),std::move(current_before));
    state=State::SEC1;
        }
        in.clear_matched();
        break;
    } // case 1 // \u{WSpace}*\}
    case 2:{ // \%\%\u{WSpace}*
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=POST_REGEX cap=2 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
fprintf(stderr,"Error: Missing closing brace for fsm \"%s\"!\n",current_fsm_name.c_str());
    ++errors_;
    if(rp.heads().size()>max_heads)
        max_heads = rp.heads().size();
    write_fsm_code_wrapped();
    named_regex_codes.emplace_back(std::move(current_fsm_name),std::move(current_regex_codes),std::move(current_eof),std::move(current_default),std::move(current_before));
    if(!initial_encountered){
        fprintf(stderr,"Error: No \"INITIAL\" state found!\n");
        ++errors_;
    }
    write_lex_and_h1();
    state=State::SEC2;
        }
        in.clear_matched();
        break;
    } // case 2 // \%\%\u{WSpace}*
    } // switch(Meta_Lexer_fsm_codes::POST_REGEX(in,heads))
    break;
} // case State::POST_REGEX
case State::SEC2:{
    clear_heads();
    switch(Meta_Lexer_fsm_codes::SEC2(in,heads)){
    case 0:{
        if(!in.getable()){
            YUKI_LEX_Meta_Lexer_DBGO("State=SEC2 EOF\n");
            return int();
        }else{ // if(!in.getable())
            YUKI_LEX_Meta_Lexer_DBGO("State=SEC2 DEFAULT\n");
            fprintf(stderr,"YLEX Error: Lexer jammed at state SEC2!\n");
            exit(EXIT_FAILURE);
        } // if(!in.getable()) else
        break;
    } // case 0
    case 1:{ // \u{All}+
        matched=in.matched(pos_begin);
        YUKI_LEX_Meta_Lexer_DBGO("State=SEC2 cap=1 matched={} len={}\n",matched.substr(0,YUKI_LEX_Meta_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
for(const char c: matched)
        fprintf(cmd_data.fp_out_cpp,"%c",c);
    return 0;
        }
        in.clear_matched();
        break;
    } // case 1 // \u{All}+
    } // switch(Meta_Lexer_fsm_codes::SEC2(in,heads))
    break;
} // case State::SEC2
} // switch(state)
} // while(1)
} // int Meta_Lexer::lex()
} // namespace yuki::lex




void yuki::lex::Meta_Lexer::write_h0() const {
    #define HIND YUKI_LEX_HIND
    #define IND YUKI_LEX_IND

    FILE* const out_h = cmd_data.fp_out_h;

    fprintf(out_h,"#pragma once\n");
    try{
        fprintf(out_h,"%s\n",code_htable.at("h_top").c_str());
    }catch(const std::out_of_range&){}
    fprintf(out_h,"#include%s\n\n",input_header.c_str());

    #ifndef YUKI_LEX_TARGET_DBG_REGEX_MAX_PRINT
    #define YUKI_LEX_TARGET_DBG_REGEX_MAX_PRINT 128
    #endif
    fprintf(out_h,
        "#ifdef %s\n"
        "#include<yuki/print.hpp>\n"
        "#ifndef %s_LOG\n"
        "#define %s_LOG \"%s.log\"\n"
        "#endif\n"
        "%s\n"
        "#ifndef %s_FP\n"
        "inline FILE* const %s_fp_=fopen(%s_LOG,\"w\");\n"
        "#define %s_FP %s::%s_fp_\n"
        "#endif\n"
        "%s\n"
        "#define %sO(...) yuki::dbgout_base(fp_dbg_,\"%s\",__VA_ARGS__)\n"
        "#define CONSTEXPR_%s // Debug output would render constexpr-functions non-constexpr.\n"
        "#ifndef %s_REGEX_MAX_PRINT\n"
        "#define %s_REGEX_MAX_PRINT %d\n"
        "#endif\n"
        "#else\n"
        "#define %sO(...)\n"
        "#define CONSTEXPR_%s constexpr\n"
        "#endif\n\n",
        debug_prefix.c_str(),
        debug_prefix.c_str(),
        debug_prefix.c_str(),debug_prefix.c_str(),
        nspace_head.c_str(),
        debug_prefix.c_str(),
        debug_prefix.c_str(),debug_prefix.c_str(),
        debug_prefix.c_str(),nspace.c_str(),debug_prefix.c_str(),
        nspace_tail.c_str(),
        debug_prefix.c_str(),debug_prefix.c_str(),
        debug_prefix.c_str(),
        debug_prefix.c_str(),
        debug_prefix.c_str(), YUKI_LEX_TARGET_DBG_REGEX_MAX_PRINT,
        debug_prefix.c_str(),
        debug_prefix.c_str()
    );

    try{
        fprintf(cmd_data.fp_out_cpp,"%s\n",code_htable.at("cpp_top").c_str());
    }catch(const std::out_of_range&){}
    fprintf(cmd_data.fp_out_cpp,
        "#include<cstdlib>\n"
        "#include<yuki/lex/common.hpp>\n"
        "#include<yuki/uchar.hpp>\n"
        "#include\"%s\"\n"
        "\n"
        "%s\n",
        cmd_data.out_h.c_str(),
        nspace_head.c_str()
    );
} // write_h0


void yuki::lex::Meta_Lexer::write_fsm_code_wrapped(){
    FILE* const out_cpp = cmd_data.fp_out_cpp;

    fprintf(out_cpp,
        "template<typename I>\n"
        "size_t %s::%s(I& in,typename I::Pos* const heads) noexcept {\n"
        IND "using namespace yuki::literals;\n"
        IND "decltype(in.get()) c;\n"
        IND "size_t cap=0;\n"
        IND "const typename I::Pos pos_begin=in.get_pos();\n"
        IND "typename I::Pos pos_take=in.get_pos();\n",
        fsm_codes_nspace.c_str(), current_fsm_name.c_str()
    );
    const auto& heads = rp.heads();
    if(!heads.empty()){
        fprintf(out_cpp,
            IND "typename I::Pos pos_head=in.get_pos();\n"
            IND "static constexpr size_t HEAD_MAP[%zu]={",
            rp.total_branches()
        );
        size_t i=0;
        size_t head_counter=0;
        for(const size_t next_head : heads){
            for(;i<next_head;++i)
                fprintf(out_cpp,"0,");
            assert(i==next_head);
            fprintf(out_cpp,"%zu,",head_counter++);
            ++i;
        }
        fprintf(out_cpp,"};\n");
    }else
        fprintf(out_cpp,IND "(void)heads;\n");
    #ifdef YUKI_LEX_META_DBG
    if(!cmd_data.debug_options.no_normal)
        yuki::lex::write_fsm_code(out_cpp,rp.fsms(),rp.fsms_size(),rp.max_branch_size(),rp.max_branch_number(),errors_,current_fsm_name.c_str());
    if(cmd_data.debug_options.policy_char){
        fprintf(cmd_data.debug_options.policy_char,"%s\n",current_fsm_name.c_str());
        yuki::lex::write_fsm_code(cmd_data.debug_options.policy_char,rp.fsms(),rp.fsms_size(),rp.max_branch_size(),rp.max_branch_number(),errors_,current_fsm_name.c_str(),{cmd_data.debug_options.policy_char,nullptr});
        fprintf(cmd_data.debug_options.policy_char,"\n\n");
    }
    if(cmd_data.debug_options.simple_accumulate){
        fprintf(cmd_data.debug_options.simple_accumulate,"%s\n",current_fsm_name.c_str());
        yuki::lex::write_fsm_code(cmd_data.debug_options.simple_accumulate,rp.fsms(),rp.fsms_size(),rp.max_branch_size(),rp.max_branch_number(),errors_,current_fsm_name.c_str(),{nullptr,cmd_data.debug_options.simple_accumulate});
        fprintf(cmd_data.debug_options.simple_accumulate,"\n\n");
    }
    if(cmd_data.debug_options.text){
        fprintf(cmd_data.debug_options.text,"%s\n",current_fsm_name.c_str());
        yuki::lex::write_fsm_code(cmd_data.debug_options.text,rp.fsms(),rp.fsms_size(),rp.max_branch_size(),rp.max_branch_number(),errors_,current_fsm_name.c_str());
        fprintf(cmd_data.debug_options.text,"\n\n");
    }
    #else
    yuki::lex::write_fsm_code(out_cpp,rp.fsms(),rp.fsms_size(),rp.max_branch_size(),rp.max_branch_number(),errors_,current_fsm_name.c_str());
    #endif
    fprintf(out_cpp,
        "} // %s::%s\n"
        "\n\n",
        fsm_codes_nspace.c_str(), current_fsm_name.c_str()
    );
} // write_fsm_code_wrapped


void yuki::lex::Meta_Lexer::write_lex_and_h1(){
    FILE* const out_cpp = cmd_data.fp_out_cpp;
    FILE* const out_h = cmd_data.fp_out_h;

    fprintf(out_h,
        "%s\n"
        "namespace %s{\n",
        nspace_head.c_str(),
        fsm_codes_nspace.c_str()
    );

    fprintf(out_cpp,
        "%s\n"
        "%s %s::lex(%s){\n"
        "while(1){\n"
        "const %s::Pos pos_begin=in.get_pos();\n"
        "switch(state){\n",
        template_decl.c_str(),
        token_type.c_str(), template_decl.empty()?lexer.c_str():templated_lexer.c_str(), lex_params.c_str(),
        input_class.c_str()
    );

    str_temp.clear(); // Used for `State` names.
    const yuki::unordered_map_str<std::string,std::string>::const_iterator code_htable_end = code_htable.end();
    const yuki::unordered_map_str<std::string,std::string>::const_iterator eof_global_i = code_htable.find("eof");
    const bool eof_global = eof_global_i!=code_htable_end;
    const yuki::unordered_map_str<std::string,std::string>::const_iterator default_global_i = code_htable.find("default");
    const bool default_global = default_global_i!=code_htable_end;
    const yuki::unordered_map_str<std::string,std::string>::const_iterator before_global_i = code_htable.find("before");
    const bool before_global = before_global_i!=code_htable_end;

    for(const Named_Regex_Codes& nrc : named_regex_codes){
        str_temp.append(nrc.name).push_back(',');
        fprintf(out_h,
            IND "template<typename I>\n"
            IND "size_t %s(I&,typename I::Pos*) noexcept;\n",
            nrc.name.c_str()
        );

        fprintf(out_cpp,"case State::%s:{\n",nrc.name.c_str());

        if(max_heads!=0)
            fprintf(out_cpp,IND "clear_heads();\n");

        if(!nrc.before_code.empty())
            fprintf(out_cpp,
                IND IND IND "{\n"
                "%s\n"
                IND IND IND "}\n",
                nrc.before_code.c_str()
            );
        else if(before_global)
            fprintf(out_cpp,
                IND IND IND "{\n"
                "%s\n"
                IND IND IND "}\n",
                before_global_i->second.c_str()
            );

        fprintf(out_cpp,
            IND "switch(%s::%s(in,%s)){\n"
            IND "case 0:{\n"
            IND IND "if(!in.getable()){\n"
            IND IND IND "%sO(\"State=%s EOF\\n\");\n",
            fsm_codes_nspace.c_str(), nrc.name.c_str(), max_heads!=0?"heads":"nullptr",
            debug_prefix.c_str(), nrc.name.c_str()
        );

        if(!nrc.eof_code.empty())
            fprintf(out_cpp,
                IND IND IND "{\n"
                "%s\n"
                IND IND IND "}\n",
                nrc.eof_code.c_str()
            );
        else if(eof_global)
            fprintf(out_cpp,
                IND IND IND "{\n"
                "%s\n"
                IND IND IND "}\n",
                eof_global_i->second.c_str()
            );
        else
            fprintf(out_cpp,IND IND IND "return %s();\n",token_type.c_str());

        fprintf(out_cpp,
            IND IND "}else{ // if(!in.getable())\n"
            IND IND IND "%sO(\"State=%s DEFAULT\\n\");\n",
            debug_prefix.c_str(),nrc.name.c_str()
        );

        if(!nrc.default_code.empty())
            fprintf(out_cpp,
                IND IND IND "{\n"
                "%s\n"
                IND IND IND "}\n",
                nrc.default_code.c_str()
            );
        else if(default_global)
            fprintf(out_cpp,
                IND IND IND "{\n"
                "%s\n"
                IND IND IND "}\n",
                default_global_i->second.c_str()
            );
        else
            fprintf(out_cpp,
                IND IND IND "fprintf(stderr,\"YLEX Error: Lexer jammed at state %s!\\n\");\n"
                IND IND IND "exit(EXIT_FAILURE);\n",
                nrc.name.c_str()
            );

        fprintf(out_cpp,
            IND IND "} // if(!in.getable()) else\n"
            IND IND "break;\n"
            IND "} // case 0\n"
        );

        size_t i=1;
        for(const Regex_Code& rc : nrc.regex_codes){
            fprintf(out_cpp,
                IND "case %zu:{ // %s\n"
                IND IND "matched=in.matched(pos_begin);\n"
                IND IND "%sO(\"State=%s cap=%zu matched={} len={}\\n\",matched.substr(0,%s_REGEX_MAX_PRINT),matched.size());\n"
                IND IND "{\n"
                "%s\n"
                IND IND "}\n"
                IND IND "in.clear_matched();\n"
                IND IND "break;\n"
                IND "} // case %zu // %s\n",
                i, rc.regex.c_str(),
                debug_prefix.c_str(), nrc.name.c_str(), i, debug_prefix.c_str(),
                rc.code.c_str(),
                i, rc.regex.c_str()
            );
            ++i;
        }

        fprintf(out_cpp,
            IND "} // switch(%s::%s(in,heads))\n"
            IND "break;\n"
            "} // case State::%s\n",
            fsm_codes_nspace.c_str(), nrc.name.c_str(),
            nrc.name.c_str()
        );
    } // for(const Named_Regex_Codes& nrc : named_regex_codes)

    fprintf(out_cpp,
        "} // switch(state)\n"
        "} // while(1)\n"
        "} // %s %s::lex(%s)\n"
        "%s\n"
        "\n\n\n\n",
        token_type.c_str(), lexer.c_str(), lex_params.c_str(),
        nspace_tail.c_str()
    );

    fprintf(out_h,
        "} // namespace %s\n"
        "\n"
        "%s\n"
        "struct %s{\n"
        IND "enum struct State {%s} state=State::INITIAL;\n"
        IND "std::string_view matched;\n"
        IND "%s in;\n"
        IND "#ifdef %s\n"
        IND "FILE* fp_dbg_=%s_FP;\n"
        IND "#endif\n\n",
        fsm_codes_nspace.c_str(),
        template_decl.c_str(),
        lexer.c_str(),
        str_temp.c_str(),
        input_class.c_str(),
        debug_prefix.c_str(),
        debug_prefix.c_str()
    );
    if(!no_default_ctor)
        fprintf(out_h,
            IND "%s() noexcept=default;\n"
            "\n"
            IND "template<typename... Args>\n"
            IND "explicit %s(Args&&... args) noexcept : in(std::forward<Args>(args)...) {}\n",
            lexer.c_str(),
            lexer.c_str()
        );
    if(max_heads!=0){
        fprintf(out_h,
            HIND "protected:\n"
            IND "%s::Pos heads[%zu];\n"
            IND "void clear_heads(){\n"
            IND IND "static_assert(std::is_trivially_copyable_v<%s::Pos>);\n"
            IND IND "memset(heads,0,sizeof(heads));\n"
            IND "}\n",
            input_class.c_str(), max_heads,
            input_class.c_str()
        );
    }
    fprintf(out_h,HIND "public:\n");
    try{
        fprintf(out_h,"%s\n",code_htable.at("class").c_str());
    }catch(const std::out_of_range&){}
    fprintf(out_h,
        HIND "public:\n"
        IND "%s lex(%s);\n"
        "}; // struct %s\n"
        "%s\n"
        "\n"
        "\n",
        token_type.c_str(), lex_params.c_str(),
        lexer.c_str(),
        nspace_tail.c_str()
    );
} // write_lex_and_h1
