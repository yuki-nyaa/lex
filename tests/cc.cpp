#include"../Char_Class.hpp"
#include<cstdio>

void print_ci(const yuki::lex::Char_Interval ci) {printf("[%u %u]",ci.lb,ci.ub);}
void print_cc(const yuki::lex::Char_Class& cc){
    for(const  yuki::lex::Char_Interval ci : cc){
        print_ci(ci);
        printf(" ");
    }
    printf("\n");
}

int main(){
    using namespace yuki::lex;
    {
    Char_Class cc;
    cc.insert({0,100});
    cc.insert({200,300});
    cc.insert({400,500});

    cc.insert({50,120});

    // [0 120] [200 300] [400 500]
    print_cc(cc);

    cc.insert({600,700});

    // [0 120] [200 300] [400 500] [600 700]
    print_cc(cc);

    cc.insert({250,650});

    // [0 120] [200 700]
    print_cc(cc);

    cc.insert({800,900});
    cc.insert({1000,1100});
    cc.insert({250,950});

    // [0 120] [200 950] [1000,1100]
    print_cc(cc);

    cc.insert({130,250});

    // [0 120] [130 950] [1000 1100]
    print_cc(cc);

    cc.insert({121,999});

    // [0 1100]
    print_cc(cc);

    cc.clear();

    cc.insert({0,100});
    cc.insert({200,300});
    cc.insert({400,500});

    cc.insert({101,101});

    // [0 101] [200 300] [400 500]
    print_cc(cc);

    cc.insert({100,199});

    // [0 300] [400 500]
    print_cc(cc);
    }

    printf("TEST1 DONE!\n\n");

    {
    Char_Class cc;
    cc.insert({0,300});
    cc.insert({400,450});

    // [100 300] [400 450]
    {
    Char_Class cc2({100,450});
    print_cc(cc*cc2);
    }

    // [101 102] [400 400]
    {
    Char_Class cc2(yuki::from_ordered_tag,{{101,102},{400,400}});
    print_cc(cc*cc2);
    }

    cc.assign(yuki::from_ordered_tag,{{100,300},{400,450}});

    // [150 300]
    {
    Char_Class cc2({150,350});
    print_cc(cc=cc*cc2);
    }

    cc.insert({320,330});

    // [150 350]
    {
    Char_Class cc2({301,350});
    print_cc(cc=cc+cc2);
    }

    // [0 149] [351 1114111]
    // [150 350]
    {
    Char_Class cc2 = !cc;
    print_cc(cc2);
    print_cc(!cc2);
    }

    {
    print_cc(cc);
    Char_Class cc2({0,0x10FFFF});
    print_cc(cc2-cc);
    }
    }

    printf("TEST2 DONE!\n\n");

    {
    Char_Class ccs[10];
    ccs[0].insert({100,120});
    ccs[0].insert({200,220});

    ccs[1].insert({110,150});
    ccs[1].insert({210,210});
    ccs[1].insert({300,300});

    // [100 150] [200 220] [300 300]
    Char_Class merged; merged.merge_cc(ccs,2);
    print_cc(merged);
    }

    printf("TEST3 DONE!\n\n");

    {
    Char_Class cc;
    cc.insert({10,15});
    cc.insert({100,100});
    cc.insert({120,130});
    for(Char_Class::const_char_iterator i = cc.begin_char();!i.is_end();++i)
        printf("%u ",*i);
    printf("\n");
    }

    printf("TEST4 DONE!\n\n");

    {
    Char_Class cc({0,0x10FFFF});
    cc = cc-Char_Class({U'\n',U'\n'});
    print_cc(cc);

    Char_Class cc2 = cc-Char_Class({U'\"',U'\"'});
    print_cc(cc2);

    Char_Class cc3({10,34});
    print_cc(cc3-cc2);

    Char_Class cc4 = cc+cc;
    print_cc(cc4);
    print_cc(Char_Class({U'\"',U'\"'})-cc4);
    }
    printf("TEST5 DONE!\n\n");

    {
    Char_Class cc;
    cc.insert(100);
    cc.insert(102);
    cc.insert(101);
    cc.insert(50);
    cc.insert(51);
    cc.insert(99);
    cc.insert(70);
    cc.insert(200);
    cc.insert(25);
    print_cc(cc);
    }
    printf("TEST6 DONE!\n\n");
}
