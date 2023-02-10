
#include"cconfig"
#include<cstdlib>
#include<charconv>
#include<yuki/unicode.hpp>
#include<cstdlib>
#include<yuki/lex/common.hpp>
#include<yuki/unicode.hpp>
#include"gen/Regex_Lexer.h"

namespace yuki::lex{
template<typename I>
size_t Regex_Lexer_fsm_codes::INITIAL(I& in,typename I::Pos* const heads){
    using namespace yuki::literals;
    decltype(in.get()) c;
    size_t cap=0;
    const typename I::Pos pos_begin=in.get_pos();
    typename I::Pos pos_take=in.get_pos();
    (void)heads;
  S0:
    c=in.get();
    if((c>=0x0_u8 && c<='\t'_u8)
    || (c=='\v'_u8 || c=='\f'_u8)
    || (c>=0xE_u8 && c<='#'_u8)
    || (c>='%'_u8 && c<='\''_u8)
    || (c==','_u8)
    || (c>='/'_u8 && c<='>'_u8)
    || (c>='@'_u8 && c<='Z'_u8)
    || (c>='_'_u8 && c<='z'_u8)
    || (c>='}'_u8 && c<=0x10FFFF_u8/*􏿿*/)) goto S1;
    if((c=='$'_u8)) goto S2;
    if((c=='('_u8)) goto S3;
    if((c==')'_u8)) goto S4;
    if((c=='*'_u8)) goto S5;
    if((c=='+'_u8)) goto S6;
    if((c=='-'_u8)) goto S7;
    if((c=='.'_u8)) goto S8;
    if((c=='?'_u8)) goto S9;
    if((c=='['_u8)) goto S10;
    if((c=='\\'_u8)) goto S11;
    if((c==']'_u8)) goto S12;
    if((c=='^'_u8)) goto S13;
    if((c=='{'_u8)) goto S14;
    if((c=='|'_u8)) goto S15;
    in.set_pos(pos_take); return cap;
  S1:
    cap=55; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S2:
    cap=14; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S3:
    cap=1; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S4:
    cap=2; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S5:
    cap=5; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S6:
    cap=6; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S7:
    cap=13; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S8:
    cap=50; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S9:
    cap=7; pos_take=in.get_pos();
    c=in.get();
    if((c=='='_u8)) goto S16;
    if((c=='l'_u8)) goto S17;
    if((c=='d'_u8)) goto S18;
    in.set_pos(pos_take); return cap;
  S10:
    cap=3; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S11:
    cap=55; pos_take=in.get_pos();
    c=in.get();
    if((c>=0x0_u8 && c<='\t'_u8)
    || (c=='\v'_u8 || c=='\f'_u8)
    || (c>=0xE_u8 && c<='@'_u8)
    || (c>='C'_u8 && c<='M'_u8)
    || (c>='O'_u8 && c<='Q'_u8)
    || (c=='S'_u8 || c=='T'_u8)
    || (c=='V'_u8 || c=='W'_u8)
    || (c=='Y'_u8)
    || (c>='['_u8 && c<='^'_u8)
    || (c=='`'_u8)
    || (c>='c'_u8 && c<='e'_u8)
    || (c=='g'_u8)
    || (c>='i'_u8 && c<='m'_u8)
    || (c=='o'_u8)
    || (c=='q'_u8)
    || (c=='s'_u8)
    || (c=='w'_u8)
    || (c=='y'_u8)
    || (c>='{'_u8 && c<=0x10FFFF_u8/*􏿿*/)) goto S19;
    if((c=='A'_u8)) goto S20;
    if((c=='B'_u8)) goto S21;
    if((c=='N'_u8)) goto S22;
    if((c=='R'_u8)) goto S23;
    if((c=='U'_u8)) goto S24;
    if((c=='X'_u8)
    || (c=='x'_u8)) goto S25;
    if((c=='Z'_u8)) goto S26;
    if((c=='_'_u8)) goto S27;
    if((c=='a'_u8)) goto S28;
    if((c=='b'_u8)) goto S29;
    if((c=='f'_u8)) goto S30;
    if((c=='h'_u8)) goto S31;
    if((c=='n'_u8)) goto S32;
    if((c=='p'_u8)) goto S33;
    if((c=='r'_u8)) goto S34;
    if((c=='t'_u8)) goto S35;
    if((c=='u'_u8)) goto S36;
    if((c=='v'_u8)) goto S37;
    if((c=='z'_u8)) goto S38;
    in.set_pos(pos_take); return cap;
  S12:
    cap=4; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S13:
    cap=12; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S14:
    cap=55; pos_take=in.get_pos();
    c=in.get();
    if((c>='0'_u8 && c<='9'_u8)) goto S39;
    in.set_pos(pos_take); return cap;
  S15:
    cap=11; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S16:
    cap=8; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S17:
    c=in.get();
    if((c==':'_u8)) goto S40;
    in.set_pos(pos_take); return cap;
  S18:
    c=in.get();
    if((c==':'_u8)) goto S41;
    in.set_pos(pos_take); return cap;
  S19:
    cap=56; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S20:
    cap=15; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S21:
    cap=19; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S22:
    cap=54; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S23:
    cap=48; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S24:
    cap=56; pos_take=in.get_pos();
    c=in.get();
    if((c>='0'_u8 && c<='9'_u8)
    || (c>='A'_u8 && c<='F'_u8)
    || (c>='a'_u8 && c<='f'_u8)) goto S42;
    if((c=='{'_u8)) goto S43;
    in.set_pos(pos_take); return cap;
  S25:
    cap=56; pos_take=in.get_pos();
    c=in.get();
    if((c>='0'_u8 && c<='9'_u8)
    || (c>='A'_u8 && c<='F'_u8)
    || (c>='a'_u8 && c<='f'_u8)) goto S42;
    in.set_pos(pos_take); return cap;
  S26:
    cap=16; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S27:
    cap=29; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S28:
    cap=23; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S29:
    cap=18; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S30:
    cap=24; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S31:
    cap=38; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S32:
    cap=25; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S33:
    cap=56; pos_take=in.get_pos();
    c=in.get();
    if((c=='{'_u8)) goto S44;
    in.set_pos(pos_take); return cap;
  S34:
    cap=26; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S35:
    cap=27; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S36:
    cap=56; pos_take=in.get_pos();
    c=in.get();
    if((c>='0'_u8 && c<='9'_u8)
    || (c>='A'_u8 && c<='F'_u8)
    || (c>='a'_u8 && c<='f'_u8)) goto S42;
    if((c=='{'_u8)) goto S45;
    in.set_pos(pos_take); return cap;
  S37:
    cap=28; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S38:
    cap=17; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S39:
    c=in.get();
    if((c>='0'_u8 && c<='9'_u8)) goto S39;
    if((c==','_u8)) goto S46;
    in.set_pos(pos_take); return cap;
  S40:
    cap=9; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S41:
    cap=10; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S42:
    cap=22; pos_take=in.get_pos();
    c=in.get();
    if((c>='0'_u8 && c<='9'_u8)
    || (c>='A'_u8 && c<='F'_u8)
    || (c>='a'_u8 && c<='f'_u8)) goto S42;
    in.set_pos(pos_take); return cap;
  S43:
    c=in.get();
    if((c>=0x0_u8 && c<='|'_u8)
    || (c>='~'_u8 && c<=0x10FFFF_u8/*􏿿*/)) goto S47;
    if((c=='}'_u8)) goto S48;
    in.set_pos(pos_take); return cap;
  S44:
    c=in.get();
    if((c>=0x0_u8 && c<='@'_u8)
    || (c=='E'_u8 || c=='F'_u8)
    || (c>='H'_u8 && c<='K'_u8)
    || (c>='M'_u8 && c<='O'_u8)
    || (c=='Q'_u8 || c=='R'_u8)
    || (c=='T'_u8)
    || (c=='V'_u8)
    || (c>='Y'_u8 && c<='|'_u8)
    || (c>='~'_u8 && c<=0x10FFFF_u8/*􏿿*/)) goto S49;
    if((c=='W'_u8)) goto S50;
    if((c=='U'_u8)) goto S51;
    if((c=='L'_u8)) goto S52;
    if((c=='G'_u8)) goto S53;
    if((c=='C'_u8)) goto S54;
    if((c=='X'_u8)) goto S55;
    if((c=='S'_u8)) goto S56;
    if((c=='D'_u8)) goto S57;
    if((c=='P'_u8)) goto S58;
    if((c=='B'_u8)) goto S59;
    if((c=='A'_u8)) goto S60;
    in.set_pos(pos_take); return cap;
  S45:
    c=in.get();
    if((c>=0x0_u8 && c<='@'_u8)
    || (c>='B'_u8 && c<='R'_u8)
    || (c>='T'_u8 && c<='|'_u8)
    || (c>='~'_u8 && c<=0x10FFFF_u8/*􏿿*/)) goto S47;
    if((c=='}'_u8)) goto S48;
    if((c=='A'_u8)) goto S61;
    if((c=='S'_u8)) goto S62;
    in.set_pos(pos_take); return cap;
  S46:
    c=in.get();
    if((c>='0'_u8 && c<='9'_u8)) goto S63;
    if((c=='}'_u8)) goto S64;
    in.set_pos(pos_take); return cap;
  S47:
    c=in.get();
    if((c>=0x0_u8 && c<='|'_u8)
    || (c>='~'_u8 && c<=0x10FFFF_u8/*􏿿*/)) goto S47;
    if((c=='}'_u8)) goto S48;
    in.set_pos(pos_take); return cap;
  S48:
    cap=53; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S49:
    c=in.get();
    if((c=='}'_u8)) goto S65;
    in.set_pos(pos_take); return cap;
  S50:
    c=in.get();
    if((c=='}'_u8)) goto S65;
    if((c=='o'_u8)) goto S66;
    in.set_pos(pos_take); return cap;
  S51:
    c=in.get();
    if((c=='}'_u8)) goto S65;
    if((c=='p'_u8)) goto S67;
    in.set_pos(pos_take); return cap;
  S52:
    c=in.get();
    if((c=='}'_u8)) goto S65;
    if((c=='o'_u8)) goto S68;
    in.set_pos(pos_take); return cap;
  S53:
    c=in.get();
    if((c=='}'_u8)) goto S65;
    if((c=='r'_u8)) goto S69;
    in.set_pos(pos_take); return cap;
  S54:
    c=in.get();
    if((c=='}'_u8)) goto S65;
    if((c=='n'_u8)) goto S70;
    in.set_pos(pos_take); return cap;
  S55:
    c=in.get();
    if((c=='}'_u8)) goto S65;
    if((c=='D'_u8)) goto S71;
    in.set_pos(pos_take); return cap;
  S56:
    c=in.get();
    if((c=='}'_u8)) goto S65;
    if((c=='p'_u8)) goto S72;
    in.set_pos(pos_take); return cap;
  S57:
    c=in.get();
    if((c=='}'_u8)) goto S65;
    if((c=='i'_u8)) goto S73;
    if((c=='o'_u8)) goto S74;
    in.set_pos(pos_take); return cap;
  S58:
    c=in.get();
    if((c=='}'_u8)) goto S65;
    if((c=='r'_u8)) goto S75;
    if((c=='u'_u8)) goto S76;
    in.set_pos(pos_take); return cap;
  S59:
    c=in.get();
    if((c=='}'_u8)) goto S65;
    if((c=='D'_u8)) goto S77;
    if((c=='l'_u8)) goto S78;
    if((c=='y'_u8)) goto S79;
    in.set_pos(pos_take); return cap;
  S60:
    c=in.get();
    if((c=='}'_u8)) goto S65;
    if((c=='S'_u8)) goto S80;
    if((c=='l'_u8)) goto S81;
    in.set_pos(pos_take); return cap;
  S61:
    c=in.get();
    if((c>=0x0_u8 && c<='k'_u8)
    || (c>='m'_u8 && c<='|'_u8)
    || (c>='~'_u8 && c<=0x10FFFF_u8/*􏿿*/)) goto S47;
    if((c=='}'_u8)) goto S48;
    if((c=='l'_u8)) goto S82;
    in.set_pos(pos_take); return cap;
  S62:
    c=in.get();
    if((c>=0x0_u8 && c<='o'_u8)
    || (c>='q'_u8 && c<='|'_u8)
    || (c>='~'_u8 && c<=0x10FFFF_u8/*􏿿*/)) goto S47;
    if((c=='}'_u8)) goto S48;
    if((c=='p'_u8)) goto S83;
    in.set_pos(pos_take); return cap;
  S63:
    c=in.get();
    if((c>='0'_u8 && c<='9'_u8)) goto S63;
    if((c=='}'_u8)) goto S84;
    in.set_pos(pos_take); return cap;
  S64:
    cap=21; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S65:
    cap=49; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S66:
    c=in.get();
    if((c=='r'_u8)) goto S85;
    in.set_pos(pos_take); return cap;
  S67:
    c=in.get();
    if((c=='p'_u8)) goto S86;
    in.set_pos(pos_take); return cap;
  S68:
    c=in.get();
    if((c=='w'_u8)) goto S87;
    in.set_pos(pos_take); return cap;
  S69:
    c=in.get();
    if((c=='a'_u8)) goto S88;
    in.set_pos(pos_take); return cap;
  S70:
    c=in.get();
    if((c=='t'_u8)) goto S89;
    in.set_pos(pos_take); return cap;
  S71:
    c=in.get();
    if((c=='i'_u8)) goto S90;
    in.set_pos(pos_take); return cap;
  S72:
    c=in.get();
    if((c=='a'_u8)) goto S91;
    in.set_pos(pos_take); return cap;
  S73:
    c=in.get();
    if((c=='g'_u8)) goto S92;
    in.set_pos(pos_take); return cap;
  S74:
    c=in.get();
    if((c=='t'_u8)) goto S93;
    in.set_pos(pos_take); return cap;
  S75:
    c=in.get();
    if((c=='i'_u8)) goto S94;
    in.set_pos(pos_take); return cap;
  S76:
    c=in.get();
    if((c=='n'_u8)) goto S95;
    in.set_pos(pos_take); return cap;
  S77:
    c=in.get();
    if((c=='o'_u8)) goto S96;
    in.set_pos(pos_take); return cap;
  S78:
    c=in.get();
    if((c=='a'_u8)) goto S97;
    in.set_pos(pos_take); return cap;
  S79:
    c=in.get();
    if((c=='t'_u8)) goto S98;
    in.set_pos(pos_take); return cap;
  S80:
    c=in.get();
    if((c=='C'_u8)) goto S99;
    in.set_pos(pos_take); return cap;
  S81:
    c=in.get();
    if((c=='n'_u8)) goto S100;
    if((c=='p'_u8)) goto S101;
    in.set_pos(pos_take); return cap;
  S82:
    c=in.get();
    if((c>=0x0_u8 && c<='k'_u8)
    || (c>='m'_u8 && c<='|'_u8)
    || (c>='~'_u8 && c<=0x10FFFF_u8/*􏿿*/)) goto S47;
    if((c=='}'_u8)) goto S48;
    if((c=='l'_u8)) goto S102;
    in.set_pos(pos_take); return cap;
  S83:
    c=in.get();
    if((c>=0x0_u8 && c<='`'_u8)
    || (c>='b'_u8 && c<='|'_u8)
    || (c>='~'_u8 && c<=0x10FFFF_u8/*􏿿*/)) goto S47;
    if((c=='}'_u8)) goto S48;
    if((c=='a'_u8)) goto S103;
    in.set_pos(pos_take); return cap;
  S84:
    cap=20; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S85:
    c=in.get();
    if((c=='d'_u8)) goto S104;
    in.set_pos(pos_take); return cap;
  S86:
    c=in.get();
    if((c=='e'_u8)) goto S105;
    in.set_pos(pos_take); return cap;
  S87:
    c=in.get();
    if((c=='e'_u8)) goto S106;
    in.set_pos(pos_take); return cap;
  S88:
    c=in.get();
    if((c=='p'_u8)) goto S107;
    in.set_pos(pos_take); return cap;
  S89:
    c=in.get();
    if((c=='r'_u8)) goto S108;
    in.set_pos(pos_take); return cap;
  S90:
    c=in.get();
    if((c=='g'_u8)) goto S109;
    in.set_pos(pos_take); return cap;
  S91:
    c=in.get();
    if((c=='c'_u8)) goto S110;
    in.set_pos(pos_take); return cap;
  S92:
    c=in.get();
    if((c=='i'_u8)) goto S111;
    in.set_pos(pos_take); return cap;
  S93:
    c=in.get();
    if((c=='}'_u8)) goto S112;
    in.set_pos(pos_take); return cap;
  S94:
    c=in.get();
    if((c=='n'_u8)) goto S113;
    in.set_pos(pos_take); return cap;
  S95:
    c=in.get();
    if((c=='c'_u8)) goto S114;
    in.set_pos(pos_take); return cap;
  S96:
    c=in.get();
    if((c=='t'_u8)) goto S115;
    in.set_pos(pos_take); return cap;
  S97:
    c=in.get();
    if((c=='n'_u8)) goto S116;
    in.set_pos(pos_take); return cap;
  S98:
    c=in.get();
    if((c=='e'_u8)) goto S117;
    in.set_pos(pos_take); return cap;
  S99:
    c=in.get();
    if((c=='I'_u8)) goto S118;
    in.set_pos(pos_take); return cap;
  S100:
    c=in.get();
    if((c=='u'_u8)) goto S119;
    in.set_pos(pos_take); return cap;
  S101:
    c=in.get();
    if((c=='h'_u8)) goto S120;
    in.set_pos(pos_take); return cap;
  S102:
    c=in.get();
    if((c>=0x0_u8 && c<='|'_u8)
    || (c>='~'_u8 && c<=0x10FFFF_u8/*􏿿*/)) goto S47;
    if((c=='}'_u8)) goto S121;
    in.set_pos(pos_take); return cap;
  S103:
    c=in.get();
    if((c>=0x0_u8 && c<='b'_u8)
    || (c>='d'_u8 && c<='|'_u8)
    || (c>='~'_u8 && c<=0x10FFFF_u8/*􏿿*/)) goto S47;
    if((c=='}'_u8)) goto S48;
    if((c=='c'_u8)) goto S122;
    in.set_pos(pos_take); return cap;
  S104:
    c=in.get();
    if((c=='}'_u8)) goto S123;
    in.set_pos(pos_take); return cap;
  S105:
    c=in.get();
    if((c=='r'_u8)) goto S124;
    in.set_pos(pos_take); return cap;
  S106:
    c=in.get();
    if((c=='r'_u8)) goto S125;
    in.set_pos(pos_take); return cap;
  S107:
    c=in.get();
    if((c=='h'_u8)) goto S126;
    in.set_pos(pos_take); return cap;
  S108:
    c=in.get();
    if((c=='l'_u8)) goto S127;
    in.set_pos(pos_take); return cap;
  S109:
    c=in.get();
    if((c=='i'_u8)) goto S128;
    in.set_pos(pos_take); return cap;
  S110:
    c=in.get();
    if((c=='e'_u8)) goto S129;
    in.set_pos(pos_take); return cap;
  S111:
    c=in.get();
    if((c=='t'_u8)) goto S130;
    in.set_pos(pos_take); return cap;
  S112:
    cap=45; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S113:
    c=in.get();
    if((c=='t'_u8)) goto S131;
    in.set_pos(pos_take); return cap;
  S114:
    c=in.get();
    if((c=='t'_u8)) goto S132;
    in.set_pos(pos_take); return cap;
  S115:
    c=in.get();
    if((c=='}'_u8)) goto S133;
    in.set_pos(pos_take); return cap;
  S116:
    c=in.get();
    if((c=='k'_u8)) goto S134;
    in.set_pos(pos_take); return cap;
  S117:
    c=in.get();
    if((c=='}'_u8)) goto S135;
    in.set_pos(pos_take); return cap;
  S118:
    c=in.get();
    if((c=='I'_u8)) goto S136;
    in.set_pos(pos_take); return cap;
  S119:
    c=in.get();
    if((c=='m'_u8)) goto S137;
    in.set_pos(pos_take); return cap;
  S120:
    c=in.get();
    if((c=='a'_u8)) goto S138;
    in.set_pos(pos_take); return cap;
  S121:
    cap=51; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S122:
    c=in.get();
    if((c>=0x0_u8 && c<='d'_u8)
    || (c>='f'_u8 && c<='|'_u8)
    || (c>='~'_u8 && c<=0x10FFFF_u8/*􏿿*/)) goto S47;
    if((c=='}'_u8)) goto S48;
    if((c=='e'_u8)) goto S139;
    in.set_pos(pos_take); return cap;
  S123:
    cap=44; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S124:
    c=in.get();
    if((c=='}'_u8)) goto S140;
    in.set_pos(pos_take); return cap;
  S125:
    c=in.get();
    if((c=='}'_u8)) goto S141;
    in.set_pos(pos_take); return cap;
  S126:
    c=in.get();
    if((c=='}'_u8)) goto S142;
    in.set_pos(pos_take); return cap;
  S127:
    c=in.get();
    if((c=='}'_u8)) goto S143;
    in.set_pos(pos_take); return cap;
  S128:
    c=in.get();
    if((c=='t'_u8)) goto S144;
    in.set_pos(pos_take); return cap;
  S129:
    c=in.get();
    if((c=='}'_u8)) goto S145;
    in.set_pos(pos_take); return cap;
  S130:
    c=in.get();
    if((c=='}'_u8)) goto S146;
    in.set_pos(pos_take); return cap;
  S131:
    c=in.get();
    if((c=='}'_u8)) goto S147;
    in.set_pos(pos_take); return cap;
  S132:
    c=in.get();
    if((c=='}'_u8)) goto S148;
    in.set_pos(pos_take); return cap;
  S133:
    cap=46; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S134:
    c=in.get();
    if((c=='}'_u8)) goto S149;
    in.set_pos(pos_take); return cap;
  S135:
    cap=47; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S136:
    c=in.get();
    if((c=='}'_u8)) goto S150;
    in.set_pos(pos_take); return cap;
  S137:
    c=in.get();
    if((c=='}'_u8)) goto S151;
    in.set_pos(pos_take); return cap;
  S138:
    c=in.get();
    if((c=='}'_u8)) goto S152;
    in.set_pos(pos_take); return cap;
  S139:
    c=in.get();
    if((c>=0x0_u8 && c<='|'_u8)
    || (c>='~'_u8 && c<=0x10FFFF_u8/*􏿿*/)) goto S47;
    if((c=='}'_u8)) goto S153;
    in.set_pos(pos_take); return cap;
  S140:
    cap=43; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S141:
    cap=41; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S142:
    cap=40; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S143:
    cap=33; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S144:
    c=in.get();
    if((c=='}'_u8)) goto S154;
    in.set_pos(pos_take); return cap;
  S145:
    cap=31; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S146:
    cap=39; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S147:
    cap=34; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S148:
    cap=42; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S149:
    cap=37; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S150:
    cap=30; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S151:
    cap=35; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S152:
    cap=36; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S153:
    cap=52; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
  S154:
    cap=32; pos_take=in.get_pos();
    in.set_pos(pos_take); return cap;
} // Regex_Lexer_fsm_codes::INITIAL



yuki::lex::Regex_Parser_TS::Token_t Regex_Lexer::lex(){
while(1){
const yuki::lex::U8Input::Pos pos_begin=in.get_pos();
switch(state){
case State::INITIAL:{
    switch(Regex_Lexer_fsm_codes::INITIAL(in,nullptr)){
    case 0:{
        if(!in.getable()){
            YUKI_LEX_Regex_Lexer_DBGO("State=INITIAL EOF\n");
            {
return Token_t(yuki::pg::in_place_kind<Token_Kind::EOF_>,{});
            }
        }else{ // if(!in.getable())
            YUKI_LEX_Regex_Lexer_DBGO("State=INITIAL DEFAULT\n");
            fprintf(stderr,"YLEX Error: Lexer jammed at state INITIAL!\n");
            exit(EXIT_FAILURE);
        } // if(!in.getable()) else
        break;
    } // case 0
    case 1:{ // \(
        matched=in.matched(pos_begin);
        YUKI_LEX_Regex_Lexer_DBGO("State=INITIAL cap=1 matched={} len={}\n",matched.substr(0,YUKI_LEX_Regex_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
return Token_t(yuki::pg::in_place_kind<Token_Kind::paren_l>,{});
        }
        in.clear_matched();
        break;
    } // case 1 // \(
    case 2:{ // \)
        matched=in.matched(pos_begin);
        YUKI_LEX_Regex_Lexer_DBGO("State=INITIAL cap=2 matched={} len={}\n",matched.substr(0,YUKI_LEX_Regex_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
return Token_t(yuki::pg::in_place_kind<Token_Kind::paren_r>,{});
        }
        in.clear_matched();
        break;
    } // case 2 // \)
    case 3:{ // \[
        matched=in.matched(pos_begin);
        YUKI_LEX_Regex_Lexer_DBGO("State=INITIAL cap=3 matched={} len={}\n",matched.substr(0,YUKI_LEX_Regex_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
return Token_t(yuki::pg::in_place_kind<Token_Kind::sqparen_l>,{});
        }
        in.clear_matched();
        break;
    } // case 3 // \[
    case 4:{ // \]
        matched=in.matched(pos_begin);
        YUKI_LEX_Regex_Lexer_DBGO("State=INITIAL cap=4 matched={} len={}\n",matched.substr(0,YUKI_LEX_Regex_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
return Token_t(yuki::pg::in_place_kind<Token_Kind::sqparen_r>,{});
        }
        in.clear_matched();
        break;
    } // case 4 // \]
    case 5:{ // \*
        matched=in.matched(pos_begin);
        YUKI_LEX_Regex_Lexer_DBGO("State=INITIAL cap=5 matched={} len={}\n",matched.substr(0,YUKI_LEX_Regex_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
return Token_t(yuki::pg::in_place_kind<Token_Kind::ast>,{});
        }
        in.clear_matched();
        break;
    } // case 5 // \*
    case 6:{ // \+
        matched=in.matched(pos_begin);
        YUKI_LEX_Regex_Lexer_DBGO("State=INITIAL cap=6 matched={} len={}\n",matched.substr(0,YUKI_LEX_Regex_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
return Token_t(yuki::pg::in_place_kind<Token_Kind::plus>,{});
        }
        in.clear_matched();
        break;
    } // case 6 // \+
    case 7:{ // \?
        matched=in.matched(pos_begin);
        YUKI_LEX_Regex_Lexer_DBGO("State=INITIAL cap=7 matched={} len={}\n",matched.substr(0,YUKI_LEX_Regex_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
return Token_t(yuki::pg::in_place_kind<Token_Kind::qmark>,{});
        }
        in.clear_matched();
        break;
    } // case 7 // \?
    case 8:{ // \?=
        matched=in.matched(pos_begin);
        YUKI_LEX_Regex_Lexer_DBGO("State=INITIAL cap=8 matched={} len={}\n",matched.substr(0,YUKI_LEX_Regex_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
return Token_t(yuki::pg::in_place_kind<Token_Kind::qe>,{});
        }
        in.clear_matched();
        break;
    } // case 8 // \?=
    case 9:{ // \?l:
        matched=in.matched(pos_begin);
        YUKI_LEX_Regex_Lexer_DBGO("State=INITIAL cap=9 matched={} len={}\n",matched.substr(0,YUKI_LEX_Regex_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
return Token_t(yuki::pg::in_place_kind<Token_Kind::lazy>,{});
        }
        in.clear_matched();
        break;
    } // case 9 // \?l:
    case 10:{ // \?d:
        matched=in.matched(pos_begin);
        YUKI_LEX_Regex_Lexer_DBGO("State=INITIAL cap=10 matched={} len={}\n",matched.substr(0,YUKI_LEX_Regex_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
return Token_t(yuki::pg::in_place_kind<Token_Kind::dlazy>,{});
        }
        in.clear_matched();
        break;
    } // case 10 // \?d:
    case 11:{ // \|
        matched=in.matched(pos_begin);
        YUKI_LEX_Regex_Lexer_DBGO("State=INITIAL cap=11 matched={} len={}\n",matched.substr(0,YUKI_LEX_Regex_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
return Token_t(yuki::pg::in_place_kind<Token_Kind::vbar>,{});
        }
        in.clear_matched();
        break;
    } // case 11 // \|
    case 12:{ // \^
        matched=in.matched(pos_begin);
        YUKI_LEX_Regex_Lexer_DBGO("State=INITIAL cap=12 matched={} len={}\n",matched.substr(0,YUKI_LEX_Regex_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
return Token_t(yuki::pg::in_place_kind<Token_Kind::hat>,{});
        }
        in.clear_matched();
        break;
    } // case 12 // \^
    case 13:{ // \-
        matched=in.matched(pos_begin);
        YUKI_LEX_Regex_Lexer_DBGO("State=INITIAL cap=13 matched={} len={}\n",matched.substr(0,YUKI_LEX_Regex_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
return Token_t(yuki::pg::in_place_kind<Token_Kind::to>,{});
        }
        in.clear_matched();
        break;
    } // case 13 // \-
    case 14:{ // \$
        matched=in.matched(pos_begin);
        YUKI_LEX_Regex_Lexer_DBGO("State=INITIAL cap=14 matched={} len={}\n",matched.substr(0,YUKI_LEX_Regex_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
return Token_t(yuki::pg::in_place_kind<Token_Kind::meta_char>,{},MetaChar::EOL);
        }
        in.clear_matched();
        break;
    } // case 14 // \$
    case 15:{ // \\A
        matched=in.matched(pos_begin);
        YUKI_LEX_Regex_Lexer_DBGO("State=INITIAL cap=15 matched={} len={}\n",matched.substr(0,YUKI_LEX_Regex_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
return Token_t(yuki::pg::in_place_kind<Token_Kind::meta_char>,{},MetaChar::BOI);
        }
        in.clear_matched();
        break;
    } // case 15 // \\A
    case 16:{ // \\Z
        matched=in.matched(pos_begin);
        YUKI_LEX_Regex_Lexer_DBGO("State=INITIAL cap=16 matched={} len={}\n",matched.substr(0,YUKI_LEX_Regex_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
return Token_t(yuki::pg::in_place_kind<Token_Kind::meta_char>,{},MetaChar::EOI);
        }
        in.clear_matched();
        break;
    } // case 16 // \\Z
    case 17:{ // \\z
        matched=in.matched(pos_begin);
        YUKI_LEX_Regex_Lexer_DBGO("State=INITIAL cap=17 matched={} len={}\n",matched.substr(0,YUKI_LEX_Regex_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
return Token_t(yuki::pg::in_place_kind<Token_Kind::meta_char>,{},MetaChar::EoF);
        }
        in.clear_matched();
        break;
    } // case 17 // \\z
    case 18:{ // \\b
        matched=in.matched(pos_begin);
        YUKI_LEX_Regex_Lexer_DBGO("State=INITIAL cap=18 matched={} len={}\n",matched.substr(0,YUKI_LEX_Regex_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
return Token_t(yuki::pg::in_place_kind<Token_Kind::meta_char>,{},MetaChar::WB);
        }
        in.clear_matched();
        break;
    } // case 18 // \\b
    case 19:{ // \\B
        matched=in.matched(pos_begin);
        YUKI_LEX_Regex_Lexer_DBGO("State=INITIAL cap=19 matched={} len={}\n",matched.substr(0,YUKI_LEX_Regex_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
return Token_t(yuki::pg::in_place_kind<Token_Kind::meta_char>,{},-MetaChar::WB);
        }
        in.clear_matched();
        break;
    } // case 19 // \\B
    case 20:{ // \{[0-9]+,[0-9]+\}
        matched=in.matched(pos_begin);
        YUKI_LEX_Regex_Lexer_DBGO("State=INITIAL cap=20 matched={} len={}\n",matched.substr(0,YUKI_LEX_Regex_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
char* next = nullptr;
    const size_t lb = strtoull(matched.data()+1,&next,10);
    return Token_t(yuki::pg::in_place_kind<Token_Kind::amount>,{},lb,strtoull(next+1,nullptr,10));
        }
        in.clear_matched();
        break;
    } // case 20 // \{[0-9]+,[0-9]+\}
    case 21:{ // \{[0-9]+,\}
        matched=in.matched(pos_begin);
        YUKI_LEX_Regex_Lexer_DBGO("State=INITIAL cap=21 matched={} len={}\n",matched.substr(0,YUKI_LEX_Regex_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
return Token_t(yuki::pg::in_place_kind<Token_Kind::amount>,{},strtoull(matched.data()+1,nullptr,10),(size_t)-1);
        }
        in.clear_matched();
        break;
    } // case 21 // \{[0-9]+,\}
    case 22:{ // \\[uUxX][0-9a-fA-F]+
        matched=in.matched(pos_begin);
        YUKI_LEX_Regex_Lexer_DBGO("State=INITIAL cap=22 matched={} len={}\n",matched.substr(0,YUKI_LEX_Regex_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
unsigned long ul;
    std::from_chars(matched.cbegin()+2,matched.cend(),ul,16);
    if(ul>yuki::UNICODE_MAX_32){
        fprintf(stderr,"Error: Unicode character %lx exceeds the max!\n",ul);
        return Token_t(yuki::pg::in_place_kind<Token_Kind::character>,{},yuki::UNICODE_MAX_32);
    }else
        return Token_t(yuki::pg::in_place_kind<Token_Kind::character>,{},ul);
        }
        in.clear_matched();
        break;
    } // case 22 // \\[uUxX][0-9a-fA-F]+
    case 23:{ // \\a
        matched=in.matched(pos_begin);
        YUKI_LEX_Regex_Lexer_DBGO("State=INITIAL cap=23 matched={} len={}\n",matched.substr(0,YUKI_LEX_Regex_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
return Token_t(yuki::pg::in_place_kind<Token_Kind::character>,{},U'\a');
        }
        in.clear_matched();
        break;
    } // case 23 // \\a
    case 24:{ // \\f
        matched=in.matched(pos_begin);
        YUKI_LEX_Regex_Lexer_DBGO("State=INITIAL cap=24 matched={} len={}\n",matched.substr(0,YUKI_LEX_Regex_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
return Token_t(yuki::pg::in_place_kind<Token_Kind::character>,{},U'\f');
        }
        in.clear_matched();
        break;
    } // case 24 // \\f
    case 25:{ // \\n
        matched=in.matched(pos_begin);
        YUKI_LEX_Regex_Lexer_DBGO("State=INITIAL cap=25 matched={} len={}\n",matched.substr(0,YUKI_LEX_Regex_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
return Token_t(yuki::pg::in_place_kind<Token_Kind::character>,{},U'\n');
        }
        in.clear_matched();
        break;
    } // case 25 // \\n
    case 26:{ // \\r
        matched=in.matched(pos_begin);
        YUKI_LEX_Regex_Lexer_DBGO("State=INITIAL cap=26 matched={} len={}\n",matched.substr(0,YUKI_LEX_Regex_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
return Token_t(yuki::pg::in_place_kind<Token_Kind::character>,{},U'\r');
        }
        in.clear_matched();
        break;
    } // case 26 // \\r
    case 27:{ // \\t
        matched=in.matched(pos_begin);
        YUKI_LEX_Regex_Lexer_DBGO("State=INITIAL cap=27 matched={} len={}\n",matched.substr(0,YUKI_LEX_Regex_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
return Token_t(yuki::pg::in_place_kind<Token_Kind::character>,{},U'\t');
        }
        in.clear_matched();
        break;
    } // case 27 // \\t
    case 28:{ // \\v
        matched=in.matched(pos_begin);
        YUKI_LEX_Regex_Lexer_DBGO("State=INITIAL cap=28 matched={} len={}\n",matched.substr(0,YUKI_LEX_Regex_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
return Token_t(yuki::pg::in_place_kind<Token_Kind::character>,{},U'\v');
        }
        in.clear_matched();
        break;
    } // case 28 // \\v
    case 29:{ // \\_
        matched=in.matched(pos_begin);
        YUKI_LEX_Regex_Lexer_DBGO("State=INITIAL cap=29 matched={} len={}\n",matched.substr(0,YUKI_LEX_Regex_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
return Token_t(yuki::pg::in_place_kind<Token_Kind::character>,{},U' ');
        }
        in.clear_matched();
        break;
    } // case 29 // \\_
    case 30:{ // \\p\{ASCII\}
        matched=in.matched(pos_begin);
        YUKI_LEX_Regex_Lexer_DBGO("State=INITIAL cap=30 matched={} len={}\n",matched.substr(0,YUKI_LEX_Regex_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
return Token_t(yuki::pg::in_place_kind<Token_Kind::basic_char_class>,{},cc_ascii);
        }
        in.clear_matched();
        break;
    } // case 30 // \\p\{ASCII\}
    case 31:{ // \\p\{Space\}
        matched=in.matched(pos_begin);
        YUKI_LEX_Regex_Lexer_DBGO("State=INITIAL cap=31 matched={} len={}\n",matched.substr(0,YUKI_LEX_Regex_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
return Token_t(yuki::pg::in_place_kind<Token_Kind::basic_char_class>,{},cc_space);
        }
        in.clear_matched();
        break;
    } // case 31 // \\p\{Space\}
    case 32:{ // \\p\{XDigit\}
        matched=in.matched(pos_begin);
        YUKI_LEX_Regex_Lexer_DBGO("State=INITIAL cap=32 matched={} len={}\n",matched.substr(0,YUKI_LEX_Regex_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
return Token_t(yuki::pg::in_place_kind<Token_Kind::basic_char_class>,{},cc_xdigit);
        }
        in.clear_matched();
        break;
    } // case 32 // \\p\{XDigit\}
    case 33:{ // \\p\{Cntrl\}
        matched=in.matched(pos_begin);
        YUKI_LEX_Regex_Lexer_DBGO("State=INITIAL cap=33 matched={} len={}\n",matched.substr(0,YUKI_LEX_Regex_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
return Token_t(yuki::pg::in_place_kind<Token_Kind::basic_char_class>,{},cc_cntrl);
        }
        in.clear_matched();
        break;
    } // case 33 // \\p\{Cntrl\}
    case 34:{ // \\p\{Print\}
        matched=in.matched(pos_begin);
        YUKI_LEX_Regex_Lexer_DBGO("State=INITIAL cap=34 matched={} len={}\n",matched.substr(0,YUKI_LEX_Regex_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
return Token_t(yuki::pg::in_place_kind<Token_Kind::basic_char_class>,{},cc_print);
        }
        in.clear_matched();
        break;
    } // case 34 // \\p\{Print\}
    case 35:{ // \\p\{Alnum\}
        matched=in.matched(pos_begin);
        YUKI_LEX_Regex_Lexer_DBGO("State=INITIAL cap=35 matched={} len={}\n",matched.substr(0,YUKI_LEX_Regex_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
return Token_t(yuki::pg::in_place_kind<Token_Kind::basic_char_class>,{},cc_alnum);
        }
        in.clear_matched();
        break;
    } // case 35 // \\p\{Alnum\}
    case 36:{ // \\p\{Alpha\}
        matched=in.matched(pos_begin);
        YUKI_LEX_Regex_Lexer_DBGO("State=INITIAL cap=36 matched={} len={}\n",matched.substr(0,YUKI_LEX_Regex_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
return Token_t(yuki::pg::in_place_kind<Token_Kind::basic_char_class>,{},cc_alpha);
        }
        in.clear_matched();
        break;
    } // case 36 // \\p\{Alpha\}
    case 37:{ // \\p\{Blank\}
        matched=in.matched(pos_begin);
        YUKI_LEX_Regex_Lexer_DBGO("State=INITIAL cap=37 matched={} len={}\n",matched.substr(0,YUKI_LEX_Regex_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
return Token_t(yuki::pg::in_place_kind<Token_Kind::basic_char_class>,{},cc_blank);
        }
        in.clear_matched();
        break;
    } // case 37 // \\p\{Blank\}
    case 38:{ // \\h
        matched=in.matched(pos_begin);
        YUKI_LEX_Regex_Lexer_DBGO("State=INITIAL cap=38 matched={} len={}\n",matched.substr(0,YUKI_LEX_Regex_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
return Token_t(yuki::pg::in_place_kind<Token_Kind::basic_char_class>,{},cc_blank);
        }
        in.clear_matched();
        break;
    } // case 38 // \\h
    case 39:{ // \\p\{Digit\}
        matched=in.matched(pos_begin);
        YUKI_LEX_Regex_Lexer_DBGO("State=INITIAL cap=39 matched={} len={}\n",matched.substr(0,YUKI_LEX_Regex_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
return Token_t(yuki::pg::in_place_kind<Token_Kind::basic_char_class>,{},cc_digit);
        }
        in.clear_matched();
        break;
    } // case 39 // \\p\{Digit\}
    case 40:{ // \\p\{Graph\}
        matched=in.matched(pos_begin);
        YUKI_LEX_Regex_Lexer_DBGO("State=INITIAL cap=40 matched={} len={}\n",matched.substr(0,YUKI_LEX_Regex_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
return Token_t(yuki::pg::in_place_kind<Token_Kind::basic_char_class>,{},cc_graph);
        }
        in.clear_matched();
        break;
    } // case 40 // \\p\{Graph\}
    case 41:{ // \\p\{Lower\}
        matched=in.matched(pos_begin);
        YUKI_LEX_Regex_Lexer_DBGO("State=INITIAL cap=41 matched={} len={}\n",matched.substr(0,YUKI_LEX_Regex_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
return Token_t(yuki::pg::in_place_kind<Token_Kind::basic_char_class>,{},cc_lower);
        }
        in.clear_matched();
        break;
    } // case 41 // \\p\{Lower\}
    case 42:{ // \\p\{Punct\}
        matched=in.matched(pos_begin);
        YUKI_LEX_Regex_Lexer_DBGO("State=INITIAL cap=42 matched={} len={}\n",matched.substr(0,YUKI_LEX_Regex_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
return Token_t(yuki::pg::in_place_kind<Token_Kind::basic_char_class>,{},cc_punct);
        }
        in.clear_matched();
        break;
    } // case 42 // \\p\{Punct\}
    case 43:{ // \\p\{Upper\}
        matched=in.matched(pos_begin);
        YUKI_LEX_Regex_Lexer_DBGO("State=INITIAL cap=43 matched={} len={}\n",matched.substr(0,YUKI_LEX_Regex_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
return Token_t(yuki::pg::in_place_kind<Token_Kind::basic_char_class>,{},cc_upper);
        }
        in.clear_matched();
        break;
    } // case 43 // \\p\{Upper\}
    case 44:{ // \\p\{Word\}
        matched=in.matched(pos_begin);
        YUKI_LEX_Regex_Lexer_DBGO("State=INITIAL cap=44 matched={} len={}\n",matched.substr(0,YUKI_LEX_Regex_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
return Token_t(yuki::pg::in_place_kind<Token_Kind::basic_char_class>,{},cc_word);
        }
        in.clear_matched();
        break;
    } // case 44 // \\p\{Word\}
    case 45:{ // \\p\{Dot\}
        matched=in.matched(pos_begin);
        YUKI_LEX_Regex_Lexer_DBGO("State=INITIAL cap=45 matched={} len={}\n",matched.substr(0,YUKI_LEX_Regex_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
return Token_t(yuki::pg::in_place_kind<Token_Kind::basic_char_class>,{},cc_dot_ascii);
        }
        in.clear_matched();
        break;
    } // case 45 // \\p\{Dot\}
    case 46:{ // \\p\{BDot\}
        matched=in.matched(pos_begin);
        YUKI_LEX_Regex_Lexer_DBGO("State=INITIAL cap=46 matched={} len={}\n",matched.substr(0,YUKI_LEX_Regex_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
return Token_t(yuki::pg::in_place_kind<Token_Kind::basic_char_class>,{},cc_dot_byte);
        }
        in.clear_matched();
        break;
    } // case 46 // \\p\{BDot\}
    case 47:{ // \\p\{Byte\}
        matched=in.matched(pos_begin);
        YUKI_LEX_Regex_Lexer_DBGO("State=INITIAL cap=47 matched={} len={}\n",matched.substr(0,YUKI_LEX_Regex_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
return Token_t(yuki::pg::in_place_kind<Token_Kind::basic_char_class>,{},cc_all_byte);
        }
        in.clear_matched();
        break;
    } // case 47 // \\p\{Byte\}
    case 48:{ // \\R
        matched=in.matched(pos_begin);
        YUKI_LEX_Regex_Lexer_DBGO("State=INITIAL cap=48 matched={} len={}\n",matched.substr(0,YUKI_LEX_Regex_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
return Token_t(yuki::pg::in_place_kind<Token_Kind::basic_char_class>,{},cc_newline);
        }
        in.clear_matched();
        break;
    } // case 48 // \\R
    case 49:{ // \\p\{[^\}]\}
        matched=in.matched(pos_begin);
        YUKI_LEX_Regex_Lexer_DBGO("State=INITIAL cap=49 matched={} len={}\n",matched.substr(0,YUKI_LEX_Regex_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
fprintf(stderr,"Error: Unknown POSIX character category \"");
    for(const char c: matched.substr(2,matched.size()-3))
        fprintf(stderr,"%c",c);
    fprintf(stderr,"\"!\n");
    assert(errors);
    ++errors;
    return Token_t(yuki::pg::in_place_kind<Token_Kind::basic_char_class>,{},cc_ascii);
        }
        in.clear_matched();
        break;
    } // case 49 // \\p\{[^\}]\}
    case 50:{ // \.
        matched=in.matched(pos_begin);
        YUKI_LEX_Regex_Lexer_DBGO("State=INITIAL cap=50 matched={} len={}\n",matched.substr(0,YUKI_LEX_Regex_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
return Token_t(yuki::pg::in_place_kind<Token_Kind::basic_char_class>,{},cc_dot);
        }
        in.clear_matched();
        break;
    } // case 50 // \.
    case 51:{ // \\u\{All\}
        matched=in.matched(pos_begin);
        YUKI_LEX_Regex_Lexer_DBGO("State=INITIAL cap=51 matched={} len={}\n",matched.substr(0,YUKI_LEX_Regex_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
return Token_t(yuki::pg::in_place_kind<Token_Kind::basic_char_class>,{},cc_all);
        }
        in.clear_matched();
        break;
    } // case 51 // \\u\{All\}
    case 52:{ // \\u\{Space\}
        matched=in.matched(pos_begin);
        YUKI_LEX_Regex_Lexer_DBGO("State=INITIAL cap=52 matched={} len={}\n",matched.substr(0,YUKI_LEX_Regex_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
return Token_t(yuki::pg::in_place_kind<Token_Kind::basic_char_class>,{},cc_uspace);
        }
        in.clear_matched();
        break;
    } // case 52 // \\u\{Space\}
    case 53:{ // \\[uU]\{[^\}]*\}
        matched=in.matched(pos_begin);
        YUKI_LEX_Regex_Lexer_DBGO("State=INITIAL cap=53 matched={} len={}\n",matched.substr(0,YUKI_LEX_Regex_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
fprintf(stderr,"Error: Unknown unicode character category \"");
    for(const char c: matched.substr(2,matched.size()-3))
        fprintf(stderr,"%c",c);
    fprintf(stderr,"\"!\n");
    assert(errors);
    ++errors;
    return Token_t(yuki::pg::in_place_kind<Token_Kind::basic_char_class>,{},cc_all);
        }
        in.clear_matched();
        break;
    } // case 53 // \\[uU]\{[^\}]*\}
    case 54:{ // \\N
        matched=in.matched(pos_begin);
        YUKI_LEX_Regex_Lexer_DBGO("State=INITIAL cap=54 matched={} len={}\n",matched.substr(0,YUKI_LEX_Regex_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
return Token_t(yuki::pg::in_place_kind<Token_Kind::esc_N>,{});
        }
        in.clear_matched();
        break;
    } // case 54 // \\N
    case 55:{ // .
        matched=in.matched(pos_begin);
        YUKI_LEX_Regex_Lexer_DBGO("State=INITIAL cap=55 matched={} len={}\n",matched.substr(0,YUKI_LEX_Regex_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
return Token_t(yuki::pg::in_place_kind<Token_Kind::character>,{},static_cast<char32_t>(yuki::U8Char(matched.data())));
        }
        in.clear_matched();
        break;
    } // case 55 // .
    case 56:{ // \\.
        matched=in.matched(pos_begin);
        YUKI_LEX_Regex_Lexer_DBGO("State=INITIAL cap=56 matched={} len={}\n",matched.substr(0,YUKI_LEX_Regex_Lexer_DBG_REGEX_MAX_PRINT),matched.size());
        {
return Token_t(yuki::pg::in_place_kind<Token_Kind::character>,{},static_cast<char32_t>(yuki::U8Char(matched.data()+1)));
        }
        in.clear_matched();
        break;
    } // case 56 // \\.
    } // switch(Regex_Lexer_fsm_codes::INITIAL(in,heads))
    break;
} // case State::INITIAL
} // switch(state)
} // while(1)
} // yuki::lex::Regex_Parser_TS::Token_t Regex_Lexer::lex()
} // namespace yuki::lex




