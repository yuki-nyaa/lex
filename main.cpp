#include"cconfig"
#include"gen/Meta_Lexer.h"
#include"gen/Regex_Parser.h"
#include<cstdlib>
#include"cmd.hpp"
int main(const int argc,const char*const*const argv){
    if(argc<=1){
        yuki::lex::cmd_impl::version(stdout);
        yuki::cmd_help(stdout,yuki::lex::coarr);
        return EXIT_SUCCESS;
    }
    yuki::lex::Cmd_Data cmd_data;
    if(yuki::Cmd_Option_Table<yuki::lex::coarr>{}.parse(cmd_data,argc,argv)!=0)
        return EXIT_SUCCESS;
    if(!cmd_data.post_process())
        exit(EXIT_FAILURE);

    yuki::lex::Meta_Lexer meta_lexer(std::move(cmd_data));
    meta_lexer.lex();

    if(meta_lexer.errors()!=0){
        fprintf(stderr,"%zu errors encountered.\n",meta_lexer.errors());
        return EXIT_FAILURE;
    }else
        return EXIT_SUCCESS;
}
