#pragma once
#include<string>
#include<fmt/core.h>
#include<yuki/string_split.hpp>
#include<yuki/cmd.hpp>

namespace yuki::lex{
struct Cmd_Data{
    std::string in;
    std::string out_cpp;
    std::string out_h;

    // Members for later process.
    FILE* fp_in = nullptr;
    FILE* fp_out_cpp = nullptr;
    FILE* fp_out_h = nullptr;

    #ifdef YUKI_LEX_META_DBG
    struct Debug_Options{
        FILE* force_policy_char = nullptr;
        FILE* simple_accumulate = nullptr;
        bool no_normal = false;
        FILE* text = nullptr;
    } debug_options;
    #endif

    void close_all(){
        if(fp_in!=nullptr && fp_in!=stdin) {fclose(fp_in);fp_in=nullptr;}
        if(fp_out_cpp!=nullptr && fp_out_cpp!=stdout && fp_out_cpp!=stderr) {fclose(fp_out_cpp);fp_out_cpp=nullptr;}
        if(fp_out_h!=nullptr && fp_out_h!=stdout && fp_out_h!=stderr) {fclose(fp_out_h);fp_out_h=nullptr;}
        #ifdef YUKI_LEX_META_DBG
        if(debug_options.force_policy_char!=nullptr) {fclose(debug_options.force_policy_char);debug_options.force_policy_char=nullptr;}
        if(debug_options.simple_accumulate!=nullptr) {fclose(debug_options.simple_accumulate);debug_options.simple_accumulate=nullptr;}
        if(debug_options.text!=nullptr) {fclose(debug_options.text);debug_options.text=nullptr;}
        #endif
    }

    bool post_process();
};

namespace cmd_impl{
    inline void i(Cmd_Data& cmd_data,yuki::Vector<std::string>& args){
        cmd_data.in=std::move(args[0]);
    }
    inline void o(Cmd_Data& cmd_data,yuki::Vector<std::string>& args){
        cmd_data.out_cpp=std::move(args[0]);
    }
    inline void h(Cmd_Data& cmd_data,yuki::Vector<std::string>& args){
        cmd_data.out_h=std::move(args[0]);
    }
    inline void version(Cmd_Data&,yuki::Vector<std::string>&){
        fmt::print(stdout,"lex by Yuki, version {}.{}\n",1,0);
        exit(EXIT_SUCCESS);
    }
    #ifdef YUKI_LEX_META_DBG
    inline void fpc(Cmd_Data& cmd_data,yuki::Vector<std::string>&){
        cmd_data.debug_options.force_policy_char = fopen("out_char.txt","w");
    }
    inline void sa(Cmd_Data& cmd_data,yuki::Vector<std::string>&){
        cmd_data.debug_options.simple_accumulate = fopen("out_sa.txt","w");
    }
    inline void nn(Cmd_Data& cmd_data,yuki::Vector<std::string>&){
        cmd_data.debug_options.no_normal = true;
    }
    inline void text(Cmd_Data& cmd_data,yuki::Vector<std::string>&){
        cmd_data.debug_options.text = fopen("out.txt","w");
    }
    #endif
}

inline yuki::cmd_opt_table_t<Cmd_Data> opt_table={ // Option property table
    {"version",{yuki::Cmd_Token::L, 0, 0, &cmd_impl::version}},
    {"v",{yuki::Cmd_Token::Sa, 0, 0, &cmd_impl::version}},

    {"i",{yuki::Cmd_Token::Sa,1,1, &cmd_impl::i}},
    {"o",{yuki::Cmd_Token::Sa,1,1, &cmd_impl::o}},
    {"h",{yuki::Cmd_Token::Sa,1,1, &cmd_impl::h}},
    #ifdef YUKI_LEX_META_DBG
    {"fpc",{yuki::Cmd_Token::L, 0, 0, &cmd_impl::fpc}},
    {"sa",{yuki::Cmd_Token::L, 0, 0, &cmd_impl::sa}},
    {"nn",{yuki::Cmd_Token::L, 0, 0, &cmd_impl::nn}},
    {"text",{yuki::Cmd_Token::L, 0, 0, &cmd_impl::text}},
    #endif
};

inline bool Cmd_Data::post_process(){
    // Check for empty input.
    if(in.empty()){
        yuki::print_error(stderr,"no input is specified.\n");
        yuki::print_note(stderr,"use \'-i\' to specify input file.\n");
        return false;
    }
    fp_in=fopen(in.c_str(),"r");
    if(!fp_in){
        yuki::print_error(stderr,"the input file \'{}\' cannot be opened!\n",in);
        return false;
    }

    // Check for input file-ext collision.
    const auto [input_no_ext,input_ext] = yuki::vsplit_filename(in);

    if(input_ext=="cpp" || input_ext=="h" || input_ext=="hpp"){
        yuki::print_error(stderr,"input file has extension \'cpp\', \'h\', or \'hpp\', which might collide with the output files.\n");
        return false;
    }

    // Set default values;
    // The default cpp-out filename is the same as the input file.
    if(out_cpp.empty()){
        out_cpp.reserve(input_no_ext.size()+4);
        out_cpp.append(input_no_ext);
        out_cpp.append(".cpp");
    }
    fp_out_cpp=fopen(out_cpp.c_str(),"w");
    // The default h-out filename is the same as the CPP-OUT file.
    const std::string_view out_cpp_no_ext=yuki::vsplit_filename(out_cpp).zeroth;
    if(out_h.empty()){
        out_h.reserve(out_cpp_no_ext.size()+2);
        out_h.append(out_cpp_no_ext);
        out_h.append(".h");
    }
    fp_out_h=fopen(out_h.c_str(),"w");

    return true;
} // bool Cmd_Data::post_process()
} // namespace yuki::lex
