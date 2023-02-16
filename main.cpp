#include"cconfig"
#include"gen/Meta_Lexer.h"
#include"gen/Regex_Parser.h"
#include<cstdlib>
int main(int argc,char** argv){
    namespace ylex=yuki::lex;
    static ylex::Cmd_Data cmd_data;
    yuki::Cmd_Lexer<ylex::Cmd_Data> cmd_lexer(std::move(ylex::opt_table));
    cmd_lexer.process(cmd_data,argc,argv);
    if(!cmd_data.post_process())
        exit(EXIT_FAILURE);

    ylex::Meta_Lexer meta_lexer(std::move(cmd_data));
    meta_lexer.lex();

    if(meta_lexer.errors()!=0){
        fprintf(stderr,"%zu errors encountered.\n",meta_lexer.errors());
        return EXIT_FAILURE;
    }else
        return EXIT_SUCCESS;
}
