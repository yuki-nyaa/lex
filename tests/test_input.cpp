#include"../include/yuki/lex/input.hpp"
void to_utf32be(char32_t c,char* p){
    p[0] = (c >> 24) & 0xFF;
    p[1] = (c >> 16) & 0xFF;
    p[2] = (c >> 8) & 0xFF;
    p[3] = c & 0xFF;
}
void print_u8(yuki::U8Char u8c,FILE* fp = stdout){
    unsigned char arr[4] = {};
    u8c.write_to(arr);
    for(unsigned i = 0;i<4;++i)
        if(arr[i]!=0)
            fprintf(fp,"%x ",arr[i]);
}
int main(){
    using namespace yuki::lex;
    using yuki::encoding;
    using yuki::U8Char;
    using yuki::EOF_U8;

    printf("%u %u\n\n",sizeof(Input),sizeof(BufferedInput));

    printf("TEST 1\n");
    FILE* f1 = fopen("test_input_1.txt","r");
    Input input1(f1,encoding::utf8);
    char arr1[1024];
    size_t arr1_s = input1.get_raw(arr1,1,1024);
    for(size_t i=0;i<arr1_s;++i)
        printf("%x ",static_cast<unsigned char>(arr1[i]));
    fclose(f1);
    input1.set_source();

    printf("\n\n");

    printf("TEST 2\n");
    f1 = fopen("test_input_2.txt","r");
    input1.set_source(f1);
    input1.set_encoding(encoding::utf16le);
    char arr2[1024];
    size_t arr2_s = 0;
    {
    char* p = arr2;
    U8Char u8c;
    while((u8c = input1.get_u8())!=EOF_U8)
        p = u8c.write_to(p);
    arr2_s = p-arr2;
    }
    for(size_t i = 0;i<arr2_s;++i)
        printf("%x ",static_cast<unsigned char>(arr2[i]));
    fclose(f1);
    input1.set_source();

    printf("\n\n");

    printf("TEST 3\n");
    char32_t u32arr1[1024];
    size_t u32arr1_s = 0;
    {
    char* p = arr2;
    char32_t* u32p = u32arr1;
    U8Char u8c;
    while(u8c.set(p),*u32p = static_cast<char32_t>(u8c)){
        printf("%x ",*u32p++);
        p+=u8c.length();
        ++u32arr1_s;
    }
    }

    printf("\n\n");

    printf("TEST 4\n");
    char arr3[1024];
    size_t arr3_s = 0;
    {
    char* p = arr3;
    for(size_t i=0;i<u32arr1_s;++i){
        to_utf32be(u32arr1[i],p);
        p+=4;
        arr3_s+=4;
    }
    }
    for(size_t i=0;i<arr3_s;++i)
        printf("%x ",static_cast<unsigned char>(arr3[i]));

    printf("\n\n");

    printf("TEST 5\n");
    input1.set_source(arr3,arr3_s);
    input1.set_encoding(encoding::utf32be);
    char arr4[1024];
    size_t arr4_s = input1.get_raw(arr4,1,1024);
    for(size_t i=0;i<arr4_s;++i)
        printf("%x ",static_cast<unsigned char>(arr4[i]));
    input1.set_source();

    printf("\n\n");

    printf("TEST 6\n");
    input1.set_source(arr3,arr3_s);
    input1.set_encoding(encoding::utf32be);
    char arr5[1024];
    size_t arr5_s = 0;
    {
    char* p = arr5;
    U8Char u8c;
    while((u8c = input1.get_u8())!=EOF_U8)
        p = u8c.write_to(p);
    arr5_s = p-arr5;
    }
    for(size_t i = 0;i<arr5_s;++i)
        printf("%x ",static_cast<unsigned char>(arr5[i]));
    input1.set_source();

    printf("\n\n");

    printf("TEST7\n");
    char arr6[1024];
    f1 = fopen("test_input_2.txt","r");
    input1.set_source(f1);
    input1.set_encoding(encoding::utf16le);
    size_t arr6_s = input1.get_raw(arr6,1,1024);
    fclose(f1);
    input1.set_source(arr6);
    char arr7[1024];
    size_t arr7_s = 0;
    // Note: because utf-16 `\r` and `\n` contain zero byte, the following test should only print a single line.
    {
    char* p = arr7;
    U8Char u8c;
    while((u8c = input1.get_u8())!=EOF_U8)
        p = u8c.write_to(p);
    arr7_s = p-arr7;
    }
    for(size_t i = 0;i<arr7_s;++i)
        printf("%x ",static_cast<unsigned char>(arr7[i]));
    input1.set_source();

    printf("\n\n");

    printf("INPUT TEST DONE!\n\n");

    printf("TEST 1\n");
    FILE* bf1 = fopen("test_input_1.txt","r");
    BufferedInput bi1(bf1,encoding::utf8);
    char barr1[1024];
    size_t barr1_s = bi1.get_raw(barr1,1,1024);
    for(size_t i=0;i<barr1_s;++i)
        printf("%x ",static_cast<unsigned char>(barr1[i]));
    fclose(bf1);
    bi1.set_source();

    printf("\n\n");

    printf("TEST 2\n");
    bi1.set_source(barr1,barr1_s);
    char barr2[1024];
    size_t barr2_s = bi1.get_raw(barr2,1,1024);
    for(size_t i=0;i<barr2_s;++i)
        printf("%x ",static_cast<unsigned char>(barr2[i]));
    bi1.set_source();

    printf("\n\n");

    printf("TEST 3\n");
    bf1 = fopen("test_input_2.txt","r");
    bi1.set_source(bf1);
    bi1.set_encoding(encoding::utf16le);
    print_u8(bi1.peek_u8());
    printf("\n");

    for(unsigned i = 0;i<20;++i)
        print_u8(bi1.peek_u8_cons());
    printf("    %zu %zu %zu %zu    ",bi1.lineno,bi1.colno,bi1.lineno_p,bi1.colno_p);
    print_u8(bi1.peek_u8_cons());printf("    %zu %zu %zu %zu    ",bi1.lineno,bi1.colno,bi1.lineno_p,bi1.colno_p);
    print_u8(bi1.peek_u8_cons());printf("    %zu %zu %zu %zu    ",bi1.lineno,bi1.colno,bi1.lineno_p,bi1.colno_p);
    bi1.reset_peek();printf("%zu %zu %zu %zu\n",bi1.lineno,bi1.colno,bi1.lineno_p,bi1.colno_p);
    for(unsigned i = 0;i<22;++i)
        print_u8(bi1.peek_u8_cons());
    bi1.reset_peek();
    printf("\n");

    char barr3[1024];
    size_t barr3_s = 0;
    {
    char* p = barr3;
    U8Char u8c;
    while((u8c = bi1.get_u8())!=EOF_U8)
        p = u8c.write_to(p);
    barr3_s = p-barr3;
    }
    for(size_t i = 0;i<barr3_s;++i)
        printf("%x ",static_cast<unsigned char>(barr3[i]));
    fclose(bf1);
    bi1.set_source();

    printf("\n\n");

    printf("BINPUT TEST DONE!\n\n");
}