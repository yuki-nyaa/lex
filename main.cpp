#include<cstdio>
#include<yuki/ring_queue.hpp>
#include<yuki/set_ov.hpp>
#include<yuki/map.hpp>
#include<yuki/print.hpp>
#include"fsm.hpp"

#ifndef YUKI_LEX_HALF_IND
#define YUKI_LEX_HALF_IND "  "
#endif

#ifndef YUKI_LEX_IND
#define YUKI_LEX_IND "    "
#endif

#define HIND YUKI_LEX_HALF_IND
#define IND YUKI_LEX_IND


template<>
struct fmt::formatter<char32_t,char> : yuki::simple_formatter<char32_t,char> {
    template<typename OutputIt>
    static auto format(char32_t c,fmt::basic_format_context<OutputIt,char>& ctx) -> typename fmt::basic_format_context<OutputIt,char>::iterator {
        if(c<0x80){
            switch(c){
                case U'\'' :
                case U'\"' :
                case U'\\' :
                    return fmt::format_to(ctx.out(),"0x{:X}_u8r/*\\{}*/",static_cast<unsigned>(c),static_cast<char>(static_cast<unsigned char>(c)));
                case U'\a' : return fmt::format_to(ctx.out(),"0x{:X}_u8r/*\\a*/",static_cast<unsigned>(c));
                case U'\b' : return fmt::format_to(ctx.out(),"0x{:X}_u8r/*\\b*/",static_cast<unsigned>(c));
                case U'\f' : return fmt::format_to(ctx.out(),"0x{:X}_u8r/*\\f*/",static_cast<unsigned>(c));
                case U'\n' : return fmt::format_to(ctx.out(),"0x{:X}_u8r/*\\n*/",static_cast<unsigned>(c));
                case U'\r' : return fmt::format_to(ctx.out(),"0x{:X}_u8r/*\\r*/",static_cast<unsigned>(c));
                case U'\t' : return fmt::format_to(ctx.out(),"0x{:X}_u8r/*\\t*/",static_cast<unsigned>(c));
                case U'\v' : return fmt::format_to(ctx.out(),"0x{:X}_u8r/*\\v*/",static_cast<unsigned>(c));
                default : {
                    fmt::format_to(ctx.out(),"0x{:X}_u8r",static_cast<unsigned>(c));
                    if(isprint(static_cast<unsigned char>(c)))
                        fmt::format_to(ctx.out(),"/*{}*/",static_cast<char>(static_cast<unsigned char>(c)));
                    return ctx.out();
                }
            }
        }
        char buf[5] = {};
        yuki::U8Char(c).write_to(buf);
        return fmt::format_to(ctx.out(),"0x{:X}_u8r/*{}*/",static_cast<uint_least32_t>(c),buf);
    }
};


namespace yuki::lex{

struct Transition_Table{
  private:
    yuki::Map_OV<size_t,Char_Class> map_;
  public:
    void clear() {map_.clear();}

    void insert(char32_t c,size_t n){
        yuki::IB_Pair<yuki::Map_OV<size_t,Char_Class>::iterator> ibp = map_.emplace<true>(n,Char_Interval{c,c});
        if(!ibp.has_inserted)
            ibp.iterator->mapped.insert({c,c});
    }

    void write(FILE* out) const {
        for(const yuki::KM_Pair<const size_t,Char_Class>& kmp : map_){
            fmt::print(out,IND "if(");
            Char_Class::const_interval_iterator i = kmp.mapped.begin_interval();
            const Char_Class::const_interval_iterator e = kmp.mapped.end_interval();
            {
            const Char_Interval ci = *i;
            switch(ci.ub-ci.lb){
                case 0 : fmt::print(out,"(c=={})",ci.lb);break;
                case 1 : fmt::print(out,"(c=={} || c=={})",ci.lb,ci.ub);break;
                default: fmt::print(out,"(c>={} && c<={})",ci.lb,ci.ub);break;
            }
            ++i;
            }
            for(;i!=e;++i){
                fmt::print(out,"\n" IND "|| ");
                const Char_Interval ci = *i;
                switch(ci.ub-ci.lb){
                    case 0 : fmt::print(out,"(c=={})",ci.lb);break;
                    case 1 : fmt::print(out,"(c=={} || c=={})",ci.lb,ci.ub);break;
                    default: fmt::print(out,"(c>={} && c<={})",ci.lb,ci.ub);break;
                }
            }
            fmt::print(out,") goto S{};\n",kmp.key);
        }
    }
};




struct Epsilon_Closure;

struct State{
    friend Epsilon_Closure;
    typedef yuki::MultiSet_OV<const FSM_Node*,FSM_Node::Less_By_Number> branch_type;
  private:
    yuki::Vector<branch_type> branches_;
    const FSM_Node* accept_ = nullptr;
    size_t size_ = 0;
    typedef yuki::Set_OV<size_t,yuki::Less<size_t>,yuki::Allocator<size_t>,yuki::Default_EC<2,1,2>> post_heads_type;
    post_heads_type post_heads_;
    post_heads_type post_heads_imm_;;
  public:

    constexpr State() noexcept = default;

    State(const State&) = delete; // Just useless, not senseless.

    constexpr State(State&& other) noexcept :
        branches_(std::move(other.branches_)),
        accept_(other.accept_),
        size_(other.size_),
        post_heads_(std::move(other.post_heads_)),
        post_heads_imm_(std::move(other.post_heads_imm_))
    {
        other.accept_=nullptr;
        other.size_=0;
    }

    State& operator=(const State&) = delete;

    State& operator=(State&& other) noexcept {
        if(this!=&other){
            branches_ = std::move(other.branches_);
            accept_ = other.accept_;
            size_ = other.size_;
            post_heads_ = std::move(other.post_heads_);
            post_heads_imm_ = std::move(other.post_heads_imm_);
            other.accept_=nullptr;
            other.size_=0;
        }
        return *this;
    }

    friend constexpr void swap(State& lhs,State& rhs) noexcept {
        using std::swap;
        swap(lhs.branches_,rhs.branches_);
        swap(lhs.accept_,rhs.accept_);
        swap(lhs.size_,rhs.size_);
        swap(lhs.post_heads_,rhs.post_heads_);
        swap(lhs.post_heads_imm_,rhs.post_heads_imm_);
    };

    bool empty() const {return size_==0;}
    size_t size() const {return size_;}

    void resize_branch(size_t s) {branches_.resize(s);}
    void clear(){
        for(branch_type& b : branches_)
            b.clear();
        accept_=nullptr;
        size_=0;
        post_heads_.clear();
        post_heads_imm_.clear();
    }

    const FSM_Node* accept() const {return accept_;}

    const post_heads_type& post_heads() const {return post_heads_;}
    const post_heads_type& post_heads_imm() const {return post_heads_imm_;}

    void insert_post_head(size_t i){
        if(!post_heads_imm_.contains(i))
            post_heads_.insert(i);
    }

    void insert_post_head_imm(size_t i){
        post_heads_imm_.insert(i);
    }

    struct insert_return_type{
        bool is_head;
        FSM_Node::Lazy is_lazy;
        bool has_inserted;
    };

    insert_return_type insert_at_branch(const FSM_Node* n,branch_type& brc){
        typedef FSM_Node::Lazy Lazy;
        yuki::IB_Pair<branch_type::const_iterator> ibp = brc.insert_unique<true>(n);
        if(ibp.has_inserted){

            if(n->is_accept){
                if(!accept_){
                    accept_ = n;
                    switch(n->is_lazy){
                        case Lazy::D : {
                            for(branch_type& b : branches_)
                                b.clear();
                            size_=0;
                            return {false,Lazy::D,true};
                        }
                        case Lazy::L : {
                            size_ -= (brc.size()-1);
                            brc.clear();
                            return {false,Lazy::L,true};
                        }
                    }
                }else{
                    switch(n->is_lazy){
                        case Lazy::D : {
                            if(accept_->is_lazy!=FSM_Node::Lazy::D){
                                accept_ = n;
                                for(branch_type& b : branches_)
                                    b.clear();
                                size_=0;
                                return {false,Lazy::D,true};
                            }
                            [[fallthrough]];
                        }
                        case Lazy::L : {
                            size_ -= (brc.size()-1);
                            brc.clear();
                            return {false,Lazy::L,true};
                        }
                    }
                }
            }

            ++size_;
            return {n->is_head,Lazy::N,true};

        } // if(ibp.has_inserted)
        return {false,Lazy::N,false};
    } // insert_return_type insert_at_branch(const FSM_Node* n,branch_type& brc)

    /// @return `pair.zeroth` is 'true' if headed.
    bool init(const FSM fsms[],const size_t fsms_size,Epsilon_Closure& ec);

    typedef yuki::Vector<branch_type>::iterator branch_iterator;
    typedef yuki::Vector<branch_type>::const_iterator const_branch_iterator;
    branch_iterator begin_branch() {return branches_.begin();}
    branch_iterator end_branch() {return branches_.end();}
    const_branch_iterator begin_branch() const {return branches_.begin();}
    const_branch_iterator end_branch() const {return branches_.end();}

    struct Less{
        static std::strong_ordering compare3(const State& lhs,const State& rhs){
            if(std::strong_ordering cmp = lhs.size()<=>rhs.size();cmp!=0) return cmp;
            if(std::strong_ordering cmp = lhs.branches_.front().size()<=>rhs.branches_.front().size();cmp!=0) return cmp;
            return std::strong_ordering::equal;
        }
        static bool compare(const State& lhs,const State& rhs) {return compare3(lhs,rhs)==std::strong_ordering::less;}
    };

    friend bool state_equal(const State& lhs,const State& rhs){
        assert(lhs.branches_.size()==rhs.branches_.size());

        yuki::Vector<branch_type>::const_iterator l = lhs.branches_.begin();
        const yuki::Vector<branch_type>::const_iterator le = lhs.branches_.end();
        yuki::Vector<branch_type>::const_iterator r = rhs.branches_.begin();
        for(;l!=le;++l,++r)
            if(l->size()!=r->size())
                return false;

        l=lhs.branches_.begin();
        r=rhs.branches_.begin();
        for(;l!=le;++l,++r){
            branch_type::const_iterator lb = l->begin();
            const branch_type::const_iterator le = l->end();
            branch_type::const_iterator rb = r->begin();
            for(;lb!=le;++lb,++rb){
                if(*lb!=*rb)
                    return false;
            }
        }

        return true;
    }
    /*
    Prop: If 2 states contain the same set of nodes, then their non-immediate (abbr. NI) post-heads are also the same.
    Proof:
        Suppose one state `s1` contains a NI post-head `i`. This is true iff. there is a state such that its i-th branch contains a headed node having its (unique) non-epsilon edges pointing to some node in `s1`. That is :
            `hn` --ne--> `n`(in state `s1` branch `i`)
        Now by the assumption `s1=s2`, `n` is also in state `s2`. A node is added to a state either by a non-epsilon transition or by epsilon-closure. In the former case, since THIS FSM construction algorithm never produces a node pointed to by 2 non-epsilon edges (not necessarily from a same node), this node must be added via the same route as in state `s1`.
        So now suppose `n` is added by epsilon-closure. Where could be the source of that epsilon edge? The only possibility is `hn`, if consecutive quantifiers and quantified lookahead (e.g. (?=aaa)*) are forbidden. Since `n` is added by epsilon-closure, the node `hn` must also be contained in state `s2`, and by the assumption of equality, in state `s1` too. But this is impossible.

    */
}; // struct State


struct Epsilon_Closure{
  private:
    yuki::RingQueue<const FSM_Node*> worklist;
    char8_t* processed;
    size_t processed_size;
  public:
    Epsilon_Closure(size_t max_branch_size,size_t max_branch_number) noexcept :
        worklist(yuki::reserve_tag,max_branch_size),
        processed(new char8_t[max_branch_number+1]),
        processed_size(max_branch_number+1)
    {}

    ~Epsilon_Closure() noexcept {delete[] processed;}

    void clear_processed() const {memset(processed,0,processed_size);}

    /// @pre 'n' should be on `branches_[branch_number]` (potentially).
    /// @return 'true' if a head is encountered.
    yuki::Pair<bool,FSM_Node::Lazy> operator()(const FSM_Node* n,State& state,size_t branch_number){
        State::branch_type& brc = state.branches_[branch_number];
        yuki::Pair<bool,FSM_Node::Lazy> ret = {false,FSM_Node::Lazy::N};
        worklist.clear(); // The worklist should already be empty at this point. The real purpose is to reset the internal pointer position.
        worklist.emplace_back(n);
        while(!worklist.empty()){
            const FSM_Node* current_node = worklist.front();
            if(processed[current_node->number]==0){
                processed[current_node->number]=1;
                const bool current_node_is_head = current_node->is_head;
                for(const FSM_Node* e : current_node->edges.epsilons){
                    State::insert_return_type irt = state.insert_at_branch(e,brc);
                    if(irt.has_inserted){
                        if(current_node_is_head)
                            state.insert_post_head_imm(branch_number);
                        ret.zeroth |= irt.is_head;
                        worklist.emplace_back(e);
                    }
                }
                const FSM_Node* epsilon_back = current_node->edges.epsilon_back;
                if(epsilon_back){
                    State::insert_return_type irt = state.insert_at_branch(epsilon_back,brc);
                    if(irt.has_inserted){
                        ret.zeroth |= irt.is_head;
                        worklist.emplace_back(epsilon_back);
                    }
                }
            }
            worklist.pop_front();
        }
        return ret;
    } // yuki::Pair<bool,FSM_Node::Lazy> operator()(const FSM_Node* n,State& state,size_t branch_number)
}; // struct Epsilon_Closure

/// @return `pair.zeroth` is 'true' if headed.
bool State::init(const FSM fsms[],const size_t fsms_size,Epsilon_Closure& ec){
    bool is_headed = false;
    resize_branch(fsms_size);
    for(size_t i=0;i<fsms_size;++i){
        is_headed |= insert_at_branch(fsms[i].start,branches_[i]).is_head;
        is_headed |= ec(fsms[i].start,*this,i).zeroth;
    }
    return is_headed;
}


void write_main(FILE* out,const FSM fsms[],const size_t fsms_size,const size_t max_branch_size,const size_t max_branch_number){
    Epsilon_Closure epsilon_closure(max_branch_size,max_branch_number);

    typedef yuki::MultiMap<State,size_t,State::Less> State_Set;
    auto insert_state = [](State_Set& ss,State&& s) -> yuki::IB_Pair<State_Set::const_iterator> {
        State_Set::const_iterator feg = ss.first_equiv_greater(s);
        const State_Set::const_iterator fg = ss.first_greater(s);
        for(;feg!=fg;++feg)
            if(state_equal(feg->key,s)){
                return {feg,false};
            }
        return {ss.emplace_sep(s,std::move(s),ss.size()),true};
    };
    State_Set state_set;

    Char_Class cc_total;
    yuki::Vector<Char_Class> ccs;

    Transition_Table transition_table;

    #ifndef YUKI_LEX_STATES_EXPECTED
    #define YUKI_LEX_STATES_EXPECTED 65535
    #endif

    yuki::Vector<bool> is_headed(yuki::reserve_tag,YUKI_LEX_STATES_EXPECTED);
    State next;
    is_headed.emplace_back(next.init(fsms,fsms_size,epsilon_closure));
    state_set.emplace(std::move(next));

    yuki::RingQueue<State_Set::const_iterator> worklist(yuki::reserve_tag,YUKI_LEX_STATES_EXPECTED);
    worklist.emplace_back(state_set.begin());

    while(!worklist.empty()){
        const State& current_state = worklist.front()->key;

        ccs.clear();
        ccs.reserve(current_state.size());
        {
        State::const_branch_iterator bb=current_state.begin_branch();
        const State::const_branch_iterator eb=current_state.end_branch();
        for(;bb!=eb;++bb){
            for(const FSM_Node* const n : *bb)
                ccs.emplace_back(n->edges.cc_sum());
        }
        }
        cc_total = merge_cc(ccs.cbegin(),ccs.size());

        transition_table.clear();

        next.resize_branch(fsms_size);
        for(Char_Class::const_iterator i_c32=cc_total.begin();!i_c32.is_end();++i_c32){
            assert(next.empty());
            bool next_headed = false;
            const char32_t c32 = *i_c32;
            {
            size_t n_num = 0;
            State::const_branch_iterator bb=current_state.begin_branch();
            const State::const_branch_iterator eb=current_state.end_branch();
            State::branch_iterator nbb=next.begin_branch();
            size_t current_branch_number = 0;
            for(;bb!=eb;++bb,++nbb,++current_branch_number){
                epsilon_closure.clear_processed();
                for(const FSM_Node* const n : *bb){
                    if(ccs[n_num].contains(c32)){
                        FSM_Edges::const_at_iterator cai = n->edges.begin(c32);
                        if(!cai.is_end()){
                            if(n->is_head)
                                next.insert_post_head(current_branch_number);
                            do{
                                State::insert_return_type insert_ret = next.insert_at_branch(*cai,*nbb);
                                next_headed |= insert_ret.is_head;
                                switch(insert_ret.is_lazy){
                                    case FSM_Node::Lazy::D : goto insert_next;
                                    case FSM_Node::Lazy::L : goto branch_loop_end;
                                }
                                yuki::Pair<bool,FSM_Node::Lazy> insert_ret2 = epsilon_closure(*cai,next,current_branch_number);
                                next_headed |= insert_ret2.zeroth;
                                switch(insert_ret2.first){
                                    case FSM_Node::Lazy::D : goto insert_next;
                                    case FSM_Node::Lazy::L : goto branch_loop_end;
                                }
                                ++cai;
                            }while(!cai.is_end());
                        }
                    }
                    ++n_num;
                }
                branch_loop_end:;
            }
            }
            insert_next:
            yuki::IB_Pair<State_Set::const_iterator> next_ib = insert_state(state_set,std::move(next));
            if(next_ib.has_inserted){
                worklist.emplace_back(next_ib.iterator);
                is_headed.emplace_back(next_headed);
                next.resize_branch(fsms_size);
            }else
                next.clear();
            transition_table.insert(c32,next_ib.iterator->mapped);
        }

        fprintf(out,HIND "S%zu:\n",worklist.front()->mapped);

        for(const size_t head : current_state.post_heads())
            fprintf(out,IND "FSM_HEAD_POST(HEAD_MAP[%zu],pos);\n",head);

        if(is_headed[worklist.front()->mapped])
            fprintf(out,IND "pos=l.in.get_peek();\n");

        for(const size_t head : current_state.post_heads_imm())
            fprintf(out,IND "FSM_HEAD_POST(HEAD_MAP[%zu],pos);\n",head);

        const FSM_Node* const current_accept = current_state.accept();
        if(current_accept){
            if(current_accept->is_tail)
                fprintf(out,IND "l.FSM_TAKE(%zu,HEAD_MAP[%zu]);\n",current_accept->route,current_accept->route);
            else
                fprintf(out,IND "l.FSM_TAKE(%zu);\n",current_accept->route);
        }

        fprintf(out,IND "c=l.FSM_CHAR();\n");
        transition_table.write(out);
        fprintf(out,IND "return l.FSM_HALT();\n");

        worklist.pop_front();
    } // while(!worklist.empty())
} // write_main

} // namespace yuki::lex

int main(){
    using namespace yuki::lex;

    //bool is_headed = false;
    //FSM_Factory<> ff;
    //FSM fsm = ff.make_fsm(1);
    //fsm.start->edges.emplace_epsilon(fsm.accept);
    //State s;
    //s.resize_branch(1);
    //s.insert(fsm.start,is_headed);

    //Epsilon_Closure epsilon_closure(fsm.size,fsm.accept->number);
    //epsilon_closure(s,is_headed);
    //printf("%zu ",s.size());

    //s.clear();
    //printf("%zu",s.size());

    //fmt::print("{} {} {} {} {} {} {} {}",U'\\',U'\n',U'你',U'あ',U'，',U'\xE',U'\0',U'\x7F');

    //FILE* out = fopen("tt.txt","w");
    //Transition_Table tt;
    //tt.insert(U'a',1);
    //tt.insert(U'b',1);
    //tt.insert(U'a',2);
    //tt.insert(U'b',2);
    //tt.insert(U'c',2);
    //tt.insert(U'e',2);
    //tt.insert(U'f',2);
    //tt.write(out);

    FSM_Factory<> ff;

    FILE* out = fopen("zxy.txt","w");
    FSM fsm = ff.make_fsm(0,Char_Interval{U'z',U'z'}); // z

    FSM temp1 = ff.make_fsm(0,Char_Interval{U'x',U'x'});
    temp1 = ff.make_ast(0,temp1); // x*

    fsm = ff.make_seq(fsm,temp1); // zx*

    FSM temp2 = ff.make_fsm(0,Char_Interval{U'x',U'x'}); // x

    FSM temp3 = ff.make_fsm(0,Char_Interval{U'y',U'y'});
    temp3 = ff.make_ast(0,temp3); // y*

    temp2 = ff.make_seq(temp2,temp3).make_head(); // (?=xy*)

    fsm = ff.make_seq(fsm,temp2).make_accept(); // zx*(?=xy*)




    //FILE* out = fopen("abc.txt","w");
    //FSM fsm = ff.make_fsm(0,Char_Interval{U'a',U'a'});
    //FSM temp1 = ff.make_fsm(0,Char_Interval{U'b',U'b'});
    //FSM temp2 = ff.make_fsm(0,Char_Interval{U'c',U'c'});
    //temp1 = ff.make_alt(0,temp1,temp2).make_head();
    //fsm = ff.make_seq(fsm,temp1).make_accept();




    //FILE* out = fopen("zxx.txt","w");
    //FSM fsm = ff.make_fsm(0,Char_Interval{U'x',U'x'});
    //fsm = ff.make_ast(0,fsm).make_lazy(); // x*?




    printf("%zu %zu",fsm.size,fsm.accept->number);

    write_main(out,&fsm,1,fsm.size,fsm.accept->number);
}
