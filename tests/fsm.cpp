#include"../FSM.hpp"
int main(){
    using namespace yuki::lex;
    FSM_Factory<> ff;
    FSM fsm = ff.make_fsm(1,Char_Class{{U'a',U'a'}});
    assert(fsm.size==2);
    fsm.concat({{U'a',U'a'}},ff.make_node(1));
    assert(fsm.size==3);
}
