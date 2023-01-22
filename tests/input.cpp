#include"../include/yuki/lex/Input.hpp"
#include"../include/yuki/lex/get_u8.hpp"
#include"../include/yuki/lex/Ultimate_Input.hpp"
#include"../include/yuki/lex/ByteInput.hpp"
#include"../include/yuki/lex/U8Input.hpp"
void to_utf32be(const char32_t c,char* const p){
    p[0] = (c>>24) & 0xFFU;
    p[1] = (c>>16) & 0xFFU;
    p[2] = (c>>8) & 0xFFU;
    p[3] = c & 0xFFU;
}
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

    printf("%zu %zu %zu %zu\n\n",sizeof(Input),sizeof(With_Enc<Input>),sizeof(Ultimate_Input),sizeof(ByteInput_Tp<0>));

    printf("TEST 1\n");
    FILE* f1 = fopen("test_input_1.txt","r");
    Input input1(f1);
    char arr1[1024];
    size_t arr1_s = input1.read(arr1,1,1024);
    for(size_t i=0;i<arr1_s;++i)
        printf("%x ",static_cast<unsigned char>(arr1[i]));
    fclose(f1);
    input1.set_source();

    printf("\n\n");

    printf("TEST 2\n");
    f1 = fopen("test_input_2.txt","r");
    With_Enc<Input> iwe1(f1,encoding::utf16le);
    char arr2[1024];
    size_t arr2_s = 0;
    {
    char* p = arr2;
    U8Char u8c;
    while((u8c = iwe1.get_u8())!=EOF_U8)
        p = u8c.write_to(p);
    arr2_s = p-arr2;
    }
    for(size_t i=0;i<arr2_s;++i)
        printf("%x ",static_cast<unsigned char>(arr2[i]));
    fclose(f1);

    printf("\n\n");

    printf("TEST 3\n");
    char32_t u32arr1[1024];
    size_t u32arr1_s = 0;
    {
    char* p = arr2;
    char32_t* u32p = u32arr1;
    U8Char u8c;
    for(size_t i=0;i!=arr2_s;){
        u8c.set(p);
        *u32p = static_cast<char32_t>(u8c);
        printf("%x ",*u32p++);
        p+=u8c.length();
        i+=u8c.length();
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
    With_Enc<Input> iwe2(arr3,arr3_s,encoding::utf32be);
    char arr5[1024];
    size_t arr5_s = 0;
    {
    char* p = arr5;
    U8Char u8c;
    while((u8c = iwe2.get_u8())!=EOF_U8)
        p = u8c.write_to(p);
    arr5_s = p-arr5;
    }
    for(size_t i=0;i<arr5_s;++i)
        printf("%x ",static_cast<unsigned char>(arr5[i]));
    input1.set_source();

    printf("\n\n");

    printf("INPUT TEST DONE!\n\n");

    printf("TEST 1\n");
    f1 = fopen("test_input_1.txt","r");
    Ultimate_Input_Raw<0> bi1(f1);
    char barr1[1024];
    size_t barr1_s = bi1.read(barr1,1,1024);
    for(size_t i=0;i<barr1_s;++i)
        printf("%x ",static_cast<unsigned char>(barr1[i]));
    fclose(f1);
    bi1.set_source();

    printf("\n\n");

    printf("TEST 2\n");
    bi1.set_source(barr1,barr1_s);
    char barr2[1024];
    size_t barr2_s = bi1.read(barr2,1,1024);
    for(size_t i=0;i<barr2_s;++i)
        printf("%x ",static_cast<unsigned char>(barr2[i]));
    bi1.set_source();

    printf("\n\n");

    printf("BINPUT TEST DONE!\n\n");

    printf("TEST UINPUT\n");
    f1 = fopen("test_input_2.txt","r");
    Ultimate_Input_Tp<0,0> ui(f1,encoding::utf16le);

    for(unsigned i=0;i<20;++i)
        print_u8(ui.get());
    printf("    %zu %zu %zu %zu    ",ui.u_count,ui.byte_count,ui.lineno,ui.colno);
    print_u8(ui.get());printf("    %zu %zu %zu %zu    ",ui.u_count,ui.byte_count,ui.lineno,ui.colno);
    print_u8(ui.get());printf("    %zu %zu %zu %zu    ",ui.u_count,ui.byte_count,ui.lineno,ui.colno);
    for(unsigned i=0;i<22;++i)
        print_u8(ui.get());
    print_u8(ui.get());printf("    %zu %zu %zu %zu    ",ui.u_count,ui.byte_count,ui.lineno,ui.colno);
    fclose(f1);
    printf("\n\n");

    printf("UINPUT TEST DONE!\n\n");

    printf("TEST BYTEINPUT\n");
    f1 = fopen("test_uinput.txt","r");
    ByteInput_Tp<0> bytei(f1);

    printf("TEST1\n");
    for(unsigned i=0;i<6;++i)
        printf("%x ",bytei.get());
    printf("    %zu    ",bytei.byte_count);
    printf("%x ",bytei.get());printf("    %zu    ",bytei.byte_count);
    printf("%x ",bytei.get());printf("    %zu    ",bytei.byte_count);
    for(unsigned i=0;i<6;++i)
        printf("%x ",bytei.get());
    printf("%x ",bytei.get());printf("    %zu    ",bytei.byte_count);
    printf("%x %x %x ",bytei.peek(),bytei.peek(),bytei.peek());
    fclose(f1);
    printf("\n\n");

    printf("TEST2\n");
    bytei.set_source(arr2,arr2_s);
    for(unsigned i=0;i<6;++i)
        printf("%x ",bytei.get());
    printf("    %zu    ",bytei.byte_count);
    printf("%x ",bytei.get());printf("    %zu    ",bytei.byte_count);
    printf("%x ",bytei.get());printf("    %zu    ",bytei.byte_count);
    for(unsigned i=0;i<6;++i)
        printf("%x ",bytei.get());
    printf("%x ",bytei.get());printf("    %zu    ",bytei.byte_count);
    printf("%x %x %x ",bytei.peek(),bytei.peek(),bytei.peek());
    printf("\n\n");

    printf("TEST3\n");
    bytei.set_source(arr2,arr2_s,true);
    for(unsigned i=0;i<6;++i)
        printf("%x ",bytei.get());
    printf("    %zu    ",bytei.byte_count);
    printf("%x ",bytei.get());printf("    %zu    ",bytei.byte_count);
    printf("%x ",bytei.get());printf("    %zu    ",bytei.byte_count);
    for(unsigned i=0;i<6;++i)
        printf("%x ",bytei.get());
    printf("%x ",bytei.get());printf("    %zu    ",bytei.byte_count);
    printf("%x %x %x ",bytei.peek(),bytei.peek(),bytei.peek());
    printf("\n\n");

    printf("BYTEINPUT TEST DONE!\n\n");

    printf("TEST U8INPUT\n");
    f1 = fopen("test_input_1.txt","r");
    U8Input_Tp<0> u8i(f1);

    for(unsigned i=0;i<20;++i)
        print_u8(u8i.get());
    printf("    %zu %zu %zu %zu    ",u8i.u_count,u8i.byte_count,u8i.lineno,u8i.colno);
    print_u8(u8i.get());printf("    %zu %zu %zu %zu    ",u8i.u_count,u8i.byte_count,u8i.lineno,u8i.colno);
    print_u8(u8i.get());printf("    %zu %zu %zu %zu    ",u8i.u_count,u8i.byte_count,u8i.lineno,u8i.colno);
    for(unsigned i=0;i<22;++i)
        print_u8(u8i.get());
    print_u8(u8i.get());printf("    %zu %zu %zu %zu    ",u8i.u_count,u8i.byte_count,u8i.lineno,u8i.colno);
    print_u8(u8i.peek());
    print_u8(u8i.peek());
    print_u8(u8i.peek());
    fclose(f1);
    printf("\n\n");

    U8Input_Tp<0> u8i2(arr1,arr1_s);
    for(unsigned i=0;i<20;++i)
        print_u8(u8i2.get());
    printf("    %zu %zu %zu %zu    ",u8i2.u_count,u8i2.byte_count,u8i2.lineno,u8i2.colno);
    print_u8(u8i2.get());printf("    %zu %zu %zu %zu    ",u8i2.u_count,u8i2.byte_count,u8i2.lineno,u8i2.colno);
    print_u8(u8i2.get());printf("    %zu %zu %zu %zu    ",u8i2.u_count,u8i2.byte_count,u8i2.lineno,u8i2.colno);
    for(unsigned i=0;i<22;++i)
        print_u8(u8i2.get());
    print_u8(u8i2.get());printf("    %zu %zu %zu %zu    ",u8i2.u_count,u8i2.byte_count,u8i2.lineno,u8i2.colno);
    print_u8(u8i2.peek());
    print_u8(u8i2.peek());
    print_u8(u8i2.peek());
    printf("\n\n");

    printf("U8INPUT TEST DONE!\n\n");
}
