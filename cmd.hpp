#pragma once
#include<string>
#include<yuki/string_split.hpp>
#include<yuki/cmd.hpp>

namespace yuki::lex{
struct Cmd_Data{
    std::string_view in; ///< Should be null-terminated.
    std::string_view out_cpp; ///< Should be null-terminated.
    std::string out_h;

    // Members for later process.
    FILE* fp_in = nullptr;
    FILE* fp_out_cpp = nullptr;
    FILE* fp_out_h = nullptr;

    #ifdef YUKI_LEX_META_DBG
    struct Debug_Options{
        FILE* policy_char = nullptr;
        FILE* simple_accumulate = nullptr;
        bool no_normal = false;
        FILE* text = nullptr;
    } debug_options;
    #endif

    bool post_process();
};

namespace cmd_impl{
    inline void i(Cmd_Data& cmd_data,const char*const*const argv,const size_t argc){
        switch(argc){
            case 0:
                fprintf(stderr,"Warning: Empty input filepath.\n");
                break;
            default:
                fprintf(stderr,"Warning: Multiple outputs specified. (Note: Enclose the path in quotes if it contains spaces.)\n");
                [[fallthrough]];
            case 1:
                cmd_data.fp_in = fopen(argv[0],"r");
                if(!cmd_data.fp_in)
                    fprintf(stderr,"Error: The input file \"%s\" somehow cannot be opened!\n",argv[0]);
                else
                    cmd_data.in = argv[0];
                break;
        }
    }

    inline void o(Cmd_Data& cmd_data,const char*const*const argv,const size_t argc){
        switch(argc){
            case 0:
                fprintf(stderr,"Warning: Empty output filepath.\n");
                break;
            default:
                fprintf(stderr,"Warning: Multiple outputs specified. (Note: Enclose the path in quotes if it contains spaces.)\n");
                [[fallthrough]];
            case 1:
                cmd_data.out_cpp = argv[0];
                break;
        }
    }

    inline void h(Cmd_Data& cmd_data,const char*const*const argv,const size_t argc){
        switch(argc){
            case 0:
                fprintf(stderr,"Warning: Empty output header filepath.\n");
                break;
            default:
                fprintf(stderr,"Warning: Multiple output headers specified. (Note: Enclose the path in quotes if it contains spaces.)\n");
                [[fallthrough]];
            case 1:
                cmd_data.out_h = argv[0];
                break;
        }
    }

    inline void version(FILE* const out) {fprintf(out,"lex by Yuki, version 1.0\n");}
    inline void version(Cmd_Data&,const char*const*,size_t) {version(stderr); exit(EXIT_SUCCESS);}

    #ifdef YUKI_LEX_META_DBG
    inline void pc(Cmd_Data& cmd_data,const char*const*,size_t){
        cmd_data.debug_options.policy_char = fopen("out_char.txt","w");
    }
    inline void sa(Cmd_Data& cmd_data,const char*const*,size_t){
        cmd_data.debug_options.simple_accumulate = fopen("out_sa.txt","w");
    }
    inline void nn(Cmd_Data& cmd_data,const char*const*,size_t){
        cmd_data.debug_options.no_normal = true;
    }
    inline void text(Cmd_Data& cmd_data,const char*const*,size_t){
        cmd_data.debug_options.text = fopen("out.txt","w");
    }
    #endif
}

inline constexpr yuki::Cmd_Option<Cmd_Data> coarr[] = {
    {"version",U'v',cmd_impl::version,"Print version information."},
    {"",U'i',cmd_impl::i,"The input file."},
    {"",U'o',cmd_impl::o,"The output cpp file."},
    {"",U'h',cmd_impl::h,"The output header file."}
    #ifdef YUKI_LEX_META_DBG
    {"pc",0,cmd_impl::pc,"Generate FSM codes by `policy_char` and write to \"out_char.txt\"."},
    {"sa",0,cmd_impl::sa,"Generate FSM codes by `policy_edge` with `simple_accumualte` and write to \"out_sa.txt\"."},
    {"nn",0,cmd_impl::nn,"Disable normal output."},
    {"text",0,cmd_impl::text,"Write only the FSM codes into \"out.txt\"."},
    #endif
};

inline bool Cmd_Data::post_process(){
    if(!fp_in){
        fprintf(stderr,"Error: No input is specified! (Note: use \"-i\" to specify input file.)\n");
        return false;
    }

    // Check for input file-ext collision.
    const auto [input_no_ext,input_ext] = yuki::vsplit_filename(in);

    if(input_ext=="cpp" || input_ext=="h" || input_ext=="hpp"){
        fprintf(stderr,"Error: The input file has extension \".cpp\", \".h\", or \".hpp\", which might collide with the output files!\n");
        return false;
    }

    // Set default values;

    std::string out_cpp_default;
    if(out_cpp.empty()){
        // The default cpp-out filename is the same as the input file.
        out_cpp_default.reserve(input_no_ext.size()+4);
        out_cpp_default.append(input_no_ext);
        out_cpp_default.append(".cpp");
        out_cpp = out_cpp_default;
    }
    fp_out_cpp=fopen(out_cpp.data(),"w");
    if(!fp_out_cpp){
        fprintf(stderr,"Error: The out file \"%s\" somehow cannot be created!\n",out_cpp.data());
        return false;
    }

    if(out_h.empty()){
        const std::string_view out_cpp_no_ext=yuki::vsplit_filename(out_cpp).zeroth;
        // The default h-out filename is the same as the CPP-OUT file.
        out_h.reserve(out_cpp_no_ext.size()+2);
        out_h.append(out_cpp_no_ext);
        out_h.append(".h");
    }
    out_cpp = std::string_view{};
    fp_out_h=fopen(out_h.c_str(),"w");
    if(!fp_out_h){
        fprintf(stderr,"Error: The out header \"%s\" somehow cannot be created!\n",out_h.c_str());
        return false;
    }

    return true;
} // bool Cmd_Data::post_process()
} // namespace yuki::lex
