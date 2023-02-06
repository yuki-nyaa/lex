%namespace xxx
%lexer Blah

%code cpp_top{
    #include"cconfig"
}

%code h_top{
    // code h_top
}

%code class{
    size_t u_count_prev;
}

%code eof{
    // EOFg
    return 100;
}

%code default{
    // DEFAULTg
    return 200;
}

%code before{
    u_count_prev=in.u_count;
}

%token_type size_t

%template<typename T,int i>
%templated_lexer Blah<T,i>

m0    (?=カー)
m1    クゥすみ

%%

<INITIAL>{
a(?=b)    {/*0*/fprintf(stderr,"%zu\n",in.u_count-u_count_prev);}
クゥすみ    {/*1*/fprintf(stderr,"%zu\n",in.u_count-u_count_prev);}
クー(?=カー)    {
    // 2
    fprintf(stderr,"%zu\n",in.u_count-u_count_prev);
}
<<EOF>>    {/*EOF0*/return 0;}
}

<STATE1>{
a(?=b)    {/*3*/fprintf(stderr,"%zu\n",in.u_count-u_count_prev);}
{m1}    {/*4*/fprintf(stderr,"%zu\n",in.u_count-u_count_prev);}
クー{m0}    {
    // 5
    fprintf(stderr,"%zu\n",in.u_count-u_count_prev);
}
<<DEFAULT>>    {
    /*DEFAULT1*/
    return 3;
}
}

%%
namespace xxx{
template size_t Blah<int,0>::lex();
}

