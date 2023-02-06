#include"cconfig"
#include"sample.h"

int main(){
    xxx::Blah<int,0> blah(fopen("test.txt","r"));
    blah.fp_dbg_=stderr;
    blah.lex();
}