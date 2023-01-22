#include"../include/yuki/lex/Ultimate_Input.hpp"

void print_u8(const yuki::U8Char u8c,FILE* const fp = stdout){
    unsigned char arr[4] = {};
    u8c.write_to(arr);
    for(unsigned i=0;i<4;++i)
        if(arr[i]!=0)
            fprintf(fp,"%x ",arr[i]);
}

int main(){
    using namespace yuki::lex;
    using yuki::encoding;
    using yuki::U8Char;
    using yuki::EOF_U8;

    FILE* const f = fopen("test_uinput.txt","r");
    Ultimate_Input_Tp<0,0> ui(f,encoding::utf16le);

    printf(">");

    for(int c;(c=getchar())!=EOF;){
        switch(static_cast<char>(static_cast<unsigned char>(c))){
            case '\n': continue;
            case 'g': print_u8(ui.get());printf("\n");break;
            case 'p': print_u8(ui.peek());printf("\n");break;
            case '1': printf("%u\n",static_cast<unsigned>(ui.at_bol()));break;
            case '2': printf("%u\n",static_cast<unsigned>(ui.at_eol()));break;
            case '3': printf("%u\n",static_cast<unsigned>(ui.at_boi()));break;
            case '4': printf("%u\n",static_cast<unsigned>(ui.at_eoi()));break;
            case '5': printf("%u\n",static_cast<unsigned>(!ui.getable()));break;
            case '6': printf("%u\n",static_cast<unsigned>(ui.at_wb()));break;
            case 'm':{
                printf("%u %u %u %u %u %u\n",
                    static_cast<unsigned>(ui.at_bol()),
                    static_cast<unsigned>(ui.at_eol()),
                    static_cast<unsigned>(ui.at_boi()),
                    static_cast<unsigned>(ui.at_eoi()),
                    static_cast<unsigned>(!ui.getable()),
                    static_cast<unsigned>(ui.at_wb())
                );
                break;
            }
            case 'l': printf("%zu %zu %zu %zu %zu ",ui.u_count,ui.byte_count,ui.lineno,ui.colno,ui.colno_byte);print_u8(ui.c_prev);printf("\n");break;
            default: printf("Unrecognizable instruction %c.\n",c);break;
        }
        printf(">");
    }
}
