#include"cconfig"
#include<cstdio>
#include<cstdint>
#include<bit>
#include<yuki/RingQueue.hpp>
#include<yuki/Set_OV.hpp>
#include<yuki/Map.hpp>
#include<yuki/print.hpp>
#include"FSM.hpp"

#define HIND YUKI_LEX_HIND
#define IND YUKI_LEX_IND
#define IND2 YUKI_LEX_IND YUKI_LEX_IND

namespace yuki::lex{

struct State_Ex;

/// `State` contains just enough information to determine the equivalence of two "states".
struct State{
    typedef yuki::Set_OV<const FSM_Node*,FSM_Node::Less_By_Number> branch_type;
    typedef yuki::Ordered_Vector<size_t,yuki::Less<size_t>,yuki::Allocator<size_t>,yuki::Default_EC<2,1,1>> post_heads_type;
    friend State_Ex;
  private:
    yuki::Vector<branch_type> branches_;
    const FSM_Node* accept_ = nullptr;
    size_t size_ = 0;
    post_heads_type post_heads_imm_;
  public:
    constexpr State() noexcept = default;

    State(const State&) noexcept = default;

    constexpr State(State&& other) noexcept :
        branches_(std::move(other.branches_)),
        accept_(other.accept_),
        size_(other.size_),
        post_heads_imm_(std::move(other.post_heads_imm_))
    {
        other.accept_=nullptr;
        other.size_=0;
    }

    State& operator=(const State&) noexcept = default;

    State& operator=(State&& other) noexcept {
        if(this!=&other){
            branches_ = std::move(other.branches_);
            accept_ = other.accept_;
            size_ = other.size_;
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
        swap(lhs.post_heads_imm_,rhs.post_heads_imm_);
    };

    bool empty() const {return size_==0;}
    size_t size() const {return size_;}

    void resize_branch(const size_t s) {assert(size_==0);branches_.resize(s);}
    void clear(){
        for(branch_type& b : branches_)
            b.clear();
        accept_=nullptr;
        size_=0;
        post_heads_imm_.clear();
    }

    const FSM_Node* accept() const {return accept_;}

    const post_heads_type& post_heads_imm() const {return post_heads_imm_;}

    struct insert_return_type{
        bool has_inserted;
        bool is_head;
        FSM_Node::Lazy lazy;
    };

    template<bool random = false>
    insert_return_type insert_at_branch(const size_t brc_num,const FSM_Node* const n){
        assert(n->branch==brc_num);
        branch_type& brc = branches_[brc_num];

        if(brc.insert<true>(n).has_inserted){

            if(n->is_accept){
                if(!accept_){
                    accept_ = n;
                    switch(n->lazy){
                        case FSM_Node::Lazy::N:break; // goto below
                        case FSM_Node::Lazy::L:{
                            size_ -= (brc.size()-1);
                            brc.tree_base().reset();
                            return {true,false,FSM_Node::Lazy::L};
                        }
                        case FSM_Node::Lazy::D:{
                            for(branch_type& b : branches_)
                                b.tree_base().reset();
                            size_=0;
                            return {true,false,FSM_Node::Lazy::D};
                        }
                    }
                }else{
                    if constexpr(random){
                        if(brc_num < accept_->branch)
                            accept_=n;
                        switch(n->lazy){
                            case FSM_Node::Lazy::N:break; // goto below
                            case FSM_Node::Lazy::L:{
                                size_ -= (brc.size()-1);
                                brc.tree_base().reset();
                                return {true,false,FSM_Node::Lazy::L};
                            }
                            case FSM_Node::Lazy::D:{
                                for(branch_type& b : branches_)
                                    b.tree_base().reset();
                                size_=0;
                                return {true,false,FSM_Node::Lazy::D};
                            }
                        }
                    }else{
                        assert(n->lazy!=FSM_Node::Lazy::D);
                        if(n->lazy==FSM_Node::Lazy::L){
                            size_ -= (brc.size()-1);
                            brc.tree_base().reset();
                            return {true,false,FSM_Node::Lazy::L};
                        }// else goto below
                    }
                }
            }

            ++size_;
            return {true,n->is_head,FSM_Node::Lazy::N};

        } // if(brc.insert<true>(n).has_inserted)
        return {false,false,FSM_Node::Lazy::N};
    } // insert_return_type insert_at_branch(const size_t brc_num,const FSM_Node* const n)

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

        if(lhs.accept_!=rhs.accept_)
            return false;

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

    void trim(){
        for(branch_type& brc : branches_){
            switch(brc.size()){
                case 0: brc.tree_base().reset();break;
                case 1:{
                    if(brc.tree_base().front()->is_accept)
                        brc.tree_base().reset(),--size_;
                    break;
                }
            }
        }
    }
}; // struct State

/// `State` augmented with non-immediate post-heads and `is_headed` and other temporary info that is only useful when computing the transitions.
/// The non-immediate post-heads are written out immediately after the transitions has been computed. After that there is no need to keep them in memory.
/// `is_headed` is stored in a separate queue to save a negligible amount of memory.
struct State_Ex{
    State state;
    State::post_heads_type post_heads;
    bool is_headed = false;
    FSM_Node::Lazy lazy = FSM_Node::Lazy::N; ///< Only useful with `policy_edge`.
    bool on = false; ///< Generally useless.
    size_t last_branch_num = 0; ///< Only useful with `policy_edge`.

    /// Clear things that do not change after being moved. (Equivalent to a custom move ctor/assignment op.)
    void simple_clear(){
        is_headed = false;
        lazy = FSM_Node::Lazy::N;
        on = false;
        last_branch_num = 0;
    }

    void clear(){
        simple_clear();
        post_heads.clear();
        state.clear();
    }

    bool empty() const {return state.empty() && post_heads.empty() && !is_headed && lazy==FSM_Node::Lazy::N && last_branch_num==0;}

    void init(const FSM* const fsms,const size_t fsms_size){
        assert(empty());
        state.resize_branch(fsms_size);
        for(size_t i=0;i<fsms_size;++i){
            is_headed |= state.insert_at_branch(i,fsms[i].start).is_head;
            is_headed |= epsilon_closure(fsms[i].start,i).zeroth;
        }
    }

    /// @note Since immediate post-heads have a higher precedence, the insertion will not take place if `i` is already among the immediate post-heads.
    template<bool random = false>
    void insert_post_head(const size_t i){
        if constexpr(random){
            if(!state.post_heads_imm_.contains(i))
                post_heads.insert_unique(i);
        }else{
            assert((state.post_heads_imm_.empty() || state.post_heads_imm_.back()<=i) && (post_heads.empty() || post_heads.back()<=i));
            if((state.post_heads_imm_.empty() || state.post_heads_imm_.back()<i) && (post_heads.empty() || post_heads.back()<i))
                post_heads.vec_base().emplace_back(i);
        }
    }

    /// @note Since immediate post-heads have a higher precedence, duplicate non-immediate post-heads will be removed.
    template<bool random = false>
    void insert_post_head_imm(const size_t i){
        if constexpr(random){
            if(state.post_heads_imm_.insert_unique<true>(i).has_inserted){
                const State::post_heads_type::const_iterator it = post_heads.find_any(i);
                if(it!=post_heads.end())
                    post_heads.erase(it);
            }
        }else{
            assert((state.post_heads_imm_.empty() || state.post_heads_imm_.back()<=i) && (post_heads.empty() || post_heads.back()<=i));
            if(state.post_heads_imm_.empty() || state.post_heads_imm_.back()<i){
                state.post_heads_imm_.vec_base().emplace_back(i);
                if(!post_heads.empty() && post_heads.back()==i)
                    post_heads.pop_back();
            }

        }
    }

    /// @pre `n->branch==branch_number`
    /// @return 'true' if a head is encountered.
    template<bool random = false>
    yuki::Pair<bool,FSM_Node::Lazy> epsilon_closure(const FSM_Node* const n,const size_t branch_number){
        assert(n->branch==branch_number);

        #ifndef YUKI_LEX_EC_WORKLIST_RESERVE
        #define YUKI_LEX_EC_WORKLIST_RESERVE 64
        #endif
        static yuki::RingQueue<const FSM_Node*> worklist(yuki::reserve_tag,YUKI_LEX_EC_WORKLIST_RESERVE);

        bool is_headed = false;
        worklist.clear(); // The primary purpose is to reset the internal pointer position. In most cases the worklist should already be empty at this point. (When a lazy accept is encountered, this function would return immediately, possibly leaving the worklist non-empty.)
        worklist.emplace_back(n);
        while(!worklist.empty()){
            const FSM_Node* const current_node = worklist.pop_front_v();
            for(const FSM_Node* e : current_node->edges.epsilons){
                const State::insert_return_type irt = state.insert_at_branch<random>(branch_number,e);
                // Note: The insertion of immediate post-heads takes places even if the node is already in the state. This is NOT a mistake. The intention is to make sure that, if 2 states (produced by the various FSM transition algorithms in this program) have the same accept and the same set of nodes, as determined by `State::state_equal`, then their post-heads (immediate and non-immediate) are also the same.
                if(current_node->is_head)
                    insert_post_head_imm<random>(branch_number);
                if(irt.has_inserted){
                    is_headed |= irt.is_head;
                    if(irt.lazy!=FSM_Node::Lazy::N)
                        return {is_headed,irt.lazy};
                    worklist.emplace_back(e);
                }
            }
            const FSM_Node* const epsilon_back = current_node->edges.epsilon_back;
            if(epsilon_back){
                const State::insert_return_type irt = state.insert_at_branch<random>(branch_number,epsilon_back);
                if(irt.has_inserted){
                    is_headed |= irt.is_head;
                    worklist.emplace_back(epsilon_back);
                }
            }
        }
        return {is_headed,FSM_Node::Lazy::N};
    } // yuki::Pair<bool,FSM_Node::Lazy> epsilon_closure(const FSM_Node* const n,const size_t branch_number)

    void remove_branch(const size_t b){
        assert(!state.accept_ || state.accept_->branch!=b);
        state.size_ -= state.branches_[b].size();
        state.branches_[b].clear();
        if(state.post_heads_imm_.erase_unique(b)==0)
            post_heads.erase_unique(b);
    }
}; // struct State_Ex
} // namespace yuki::lex


namespace yuki::lex{
struct Wrapped_C32 {char32_t c32;};
}

template<>
struct fmt::formatter<yuki::lex::Wrapped_C32,char> : yuki::simple_formatter<yuki::lex::Wrapped_C32,char> {
    template<typename OutputIt>
    static auto format(const yuki::lex::Wrapped_C32 wc32,fmt::basic_format_context<OutputIt,char>& ctx) -> typename fmt::basic_format_context<OutputIt,char>::iterator {
        if(wc32.c32<0x80){
            switch(wc32.c32){
                case U'\'' : return fmt::format_to(ctx.out(),"\'\\\'\'_u8"); // Rather cryptic...
                case U'\"' : return fmt::format_to(ctx.out(),"\'\\\"\'_u8"); // Rather cryptic...
                case U'\\' : return fmt::format_to(ctx.out(),"\'\\\\\'_u8"); // Rather cryptic...
                case U'\a' : return fmt::format_to(ctx.out(),"\'\\a\'_u8");
                case U'\b' : return fmt::format_to(ctx.out(),"\'\\b\'_u8");
                case U'\f' : return fmt::format_to(ctx.out(),"\'\\f\'_u8");
                case U'\n' : return fmt::format_to(ctx.out(),"\'\\n\'_u8");
                case U'\r' : return fmt::format_to(ctx.out(),"\'\\r\'_u8");
                case U'\t' : return fmt::format_to(ctx.out(),"\'\\t\'_u8");
                case U'\v' : return fmt::format_to(ctx.out(),"\'\\v\'_u8");
                default:{
                    if(isprint(static_cast<unsigned char>(wc32.c32)))
                        return fmt::format_to(ctx.out(),"\'{}\'_u8",static_cast<char>(static_cast<unsigned char>(wc32.c32)));
                    else
                        return fmt::format_to(ctx.out(),"0x{:X}_u8",static_cast<unsigned>(wc32.c32));
                }
            }
        }else{
            switch(wc32.c32){
                case 0x2028: return fmt::format_to(ctx.out(),"0x2028_u8/*LS*/");
                case 0x2029: return fmt::format_to(ctx.out(),"0x2029_u8/*PS*/");
                case 0x202A: return fmt::format_to(ctx.out(),"0x202A_u8/*LRE*/");
                case 0x202B: return fmt::format_to(ctx.out(),"0x202B_u8/*RLE*/");
                case 0x202C: return fmt::format_to(ctx.out(),"0x202C_u8/*PDF*/");
                case 0x202D: return fmt::format_to(ctx.out(),"0x202D_u8/*LRO*/");
                case 0x202E: return fmt::format_to(ctx.out(),"0x202E_u8/*RLO*/");
                default:{
                    char buf[5] = {};
                    yuki::U8Char(wc32.c32).write_to(buf);
                    return fmt::format_to(ctx.out(),"0x{:X}_u8/*{}*/",static_cast<uint_least32_t>(wc32.c32),buf);
                }
            }
        }
    }
};


namespace yuki::lex{
struct Transition{
    const size_t target;
    Char_Class cc;
    State::post_heads_type post_heads;

    struct Target{
        static size_t project(const Transition& t) {return t.target;}
    };
};

struct Transition_Table{
  private:
    typedef yuki::Basic_Ordered_Vector<size_t,Transition,Transition::Target,yuki::Less<size_t>,yuki::Allocator<Transition>,yuki::Default_EC<>> OV_;
    OV_ ov_;
  public:
    Transition_Table(yuki::reserve_tag_t,const size_t count) noexcept : ov_(yuki::reserve_tag,count) {}

    bool empty() const {return ov_.empty();}

    void clear() {ov_.clear();}

    void insert(const char32_t c,yuki::Pair<State::post_heads_type&&,const size_t> p){
        const yuki::IB_Pair<OV_::const_iterator> ibp = ov_.emplace_unique_sep<true>(p.first,p.first,Char_Interval{c,c},std::move(p.zeroth));
        if(!ibp.has_inserted){
            using yuki::const_kast;
            const_kast(ibp.iterator)->cc.insert(c);
            p.zeroth.clear();
        }
    }

    template<typename CC,typename PH>
    void insert(CC&& cc,yuki::Pair<PH,const size_t> p){
        assert(!cc.empty());
        const yuki::IB_Pair<OV_::const_iterator> ibp = ov_.emplace_unique_sep<true>(p.first,p.first,std::forward<CC>(cc),std::forward<PH>(p.zeroth));
        if(!ibp.has_inserted){
            using yuki::const_kast;
            const OV_::non_const_iterator it_nc = const_kast(ibp.iterator);
            Char_Class cc_new = (it_nc->cc) + cc;
            swap(cc_new,it_nc->cc);
            if constexpr(std::is_rvalue_reference_v<PH>)
                p.zeroth.clear();
        }
    }

    void write(FILE* const out) const {
        for(const Transition& ts : ov_){
            fmt::print(out,IND "if(");
            Char_Class::const_iterator i = ts.cc.begin();
            const Char_Class::const_iterator e = ts.cc.end();
            {
            const Char_Interval ci = *i;
            switch(ci.ub-ci.lb){
                case 0 : fmt::print(out,"(c=={})",Wrapped_C32{ci.lb});break;
                case 1 : fmt::print(out,"(c=={} || c=={})",Wrapped_C32{ci.lb},Wrapped_C32{ci.ub});break;
                default:{
                    if(ci.lb==0)
                        fmt::print(out,"(");
                    else
                        fmt::print(out,"(c>={} && ",Wrapped_C32{ci.lb});
                    fmt::print(out,"c<={})",Wrapped_C32{ci.ub});
                    break;
                }
            }
            ++i;
            }
            for(;i!=e;++i){
                fmt::print(out,"\n" IND "|| ");
                const Char_Interval ci = *i;
                switch(ci.ub-ci.lb){
                    case 0 : fmt::print(out,"(c=={})",Wrapped_C32{ci.lb});break;
                    case 1 : fmt::print(out,"(c=={} || c=={})",Wrapped_C32{ci.lb},Wrapped_C32{ci.ub});break;
                    default:{
                        if(ci.lb==0)
                            fmt::print(out,"(");
                        else
                            fmt::print(out,"(c>={} && ",Wrapped_C32{ci.lb});
                        fmt::print(out,"c<={})",Wrapped_C32{ci.ub});
                        break;
                    }
                }
            }
            fmt::print(out,")");
            if(!ts.post_heads.empty()){
                fmt::print(out,"{{\n");
                for(const size_t h : ts.post_heads)
                    fmt::print(out,IND2 "heads[HEAD_MAP[{}]]=pos_head;\n",h);
                fmt::print(out,IND2 "goto S{};\n" IND "}}\n",ts.target);
            }else
                fmt::print(out," goto S{};\n",ts.target);
        }
    }
}; // struct Transition_Table


struct FSM_Edge_View{
    size_t branch_num;
    bool source_headed;
    const Char_Class* cc;
    const FSM_Node* target;
};

struct Meta_Edge{
    size_t branch_num;
    bool source_headed;
    const FSM_Node* target;
};

typedef yuki::MultiMap<State,size_t,State::Less> State_Set;

#ifndef YUKI_LEX_STATES_EXPECTED
#define YUKI_LEX_STATES_EXPECTED 4096
#endif

#ifndef YUKI_LEX_CC_UNION_RESERVE
#define YUKI_LEX_CC_UNION_RESERVE 1024
#endif

#ifndef YUKI_LEX_TRANSITION_TABLE_RESERVE
#define YUKI_LEX_TRANSITION_TABLE_RESERVE 256
#endif

State_Set state_set;
Transition_Table transition_table{yuki::reserve_tag,YUKI_LEX_TRANSITION_TABLE_RESERVE};
State_Ex next,next_always_resized,next2;

yuki::RingQueue<State_Set::const_iterator> worklist{yuki::reserve_tag,YUKI_LEX_STATES_EXPECTED};
yuki::RingQueue<bool> is_headed{yuki::reserve_tag,YUKI_LEX_STATES_EXPECTED};

Char_Class cc_union{yuki::reserve_tag,YUKI_LEX_CC_UNION_RESERVE};
Char_Class cc_temp,cc_temp2,cc_temp3;

yuki::Vector<FSM_Edge_View> edge_views{yuki::reserve_tag,YUKI_LEX_MERGE_CC_RESERVE}; // The macro is defined in "Char_Class.hpp".
yuki::Vector<size_t> edge_views_branch_indices{yuki::reserve_tag,YUKI_LEX_MERGE_CC_RESERVE}; // The macro is defined in "Char_Class.hpp".

yuki::IB_Pair<State_Set::const_iterator> insert_state(State_Set& ss,State&& s){
    State_Set::const_iterator feg = ss.first_equiv_greater(s);
    const State_Set::const_iterator fg = ss.first_greater(s);
    for(;feg!=fg;++feg)
        if(state_equal(feg->key,s)){
            return {feg,false};
        }
    return {ss.emplace_sep(s,std::move(s),ss.size()),true};
}

yuki::IB_Pair<State_Set::const_iterator> insert_state(State_Set& ss,const State& s){
    State_Set::const_iterator feg = ss.first_equiv_greater(s);
    const State_Set::const_iterator fg = ss.first_greater(s);
    for(;feg!=fg;++feg)
        if(state_equal(feg->key,s)){
            return {feg,false};
        }
    return {ss.emplace_sep(s,s,ss.size()),true};
}

/// @note All `insert_to_ss` do NOT modify `state_ex.post_heads`.
yuki::Pair<const State::post_heads_type&,const size_t> insert_to_ss(State_Ex& state_ex){
    state_ex.state.trim();
    const yuki::IB_Pair<State_Set::const_iterator> next_ib = insert_state(state_set,state_ex.state);
    if(next_ib.has_inserted){
        worklist.emplace_back(next_ib.iterator);
        is_headed.emplace_back(state_ex.is_headed);
    }
    return {state_ex.post_heads,next_ib.iterator->mapped};
}

/// @note All `insert_to_ss` do NOT modify `state_ex.post_heads`.
/// @note One should resize `state_ex` before reusing it.
yuki::Pair<State::post_heads_type&&,const size_t> insert_to_ss(State_Ex&& state_ex){
    state_ex.state.trim();
    const yuki::IB_Pair<State_Set::const_iterator> next_ib = insert_state(state_set,std::move(state_ex.state));
    if(next_ib.has_inserted){
        worklist.emplace_back(next_ib.iterator);
        is_headed.emplace_back(state_ex.is_headed);
    }else
        state_ex.state.clear();
    state_ex.simple_clear();
    return {std::move(state_ex.post_heads),next_ib.iterator->mapped};
}

/// @note All `insert_to_ss` do NOT modify `state_ex.post_heads`.
yuki::Pair<State::post_heads_type&&,const size_t> insert_next_ar_to_ss(const size_t fsms_size){
    next_always_resized.state.trim();
    const yuki::IB_Pair<State_Set::const_iterator> next_ib = insert_state(state_set,std::move(next_always_resized.state));
    if(next_ib.has_inserted){
        worklist.emplace_back(next_ib.iterator);
        is_headed.emplace_back(next_always_resized.is_headed);
        next_always_resized.state.resize_branch(fsms_size);
    }else
        next_always_resized.state.clear();
    next_always_resized.simple_clear();
    return {std::move(next_always_resized.post_heads),next_ib.iterator->mapped};
}

/// @pre `state_ex` should already have sufficient amount of branches reserved.
template<typename EV>
FSM_Node::Lazy insert_node_to(State_Ex& state_ex,const EV edge_view){
    const State::insert_return_type insert_ret = state_ex.state.insert_at_branch<std::is_same_v<EV,Meta_Edge>>(edge_view.branch_num,edge_view.target);
    if(insert_ret.has_inserted){
        if(edge_view.source_headed)
            state_ex.insert_post_head<std::is_same_v<EV,Meta_Edge>>(edge_view.branch_num);
        state_ex.is_headed |= insert_ret.is_head;
        if(insert_ret.lazy!=FSM_Node::Lazy::N)
            return insert_ret.lazy;
        const yuki::Pair<bool,FSM_Node::Lazy> insert_ret2 = state_ex.epsilon_closure<std::is_same_v<EV,Meta_Edge>>(edge_view.target,edge_view.branch_num);
        state_ex.is_headed |= insert_ret2.zeroth;
        if(insert_ret2.first!=FSM_Node::Lazy::N)
            return insert_ret2.first;
    }
    return FSM_Node::Lazy::N;
}

void policy_edge_init(State_Ex& state_ex,const FSM_Edge_View edge_view,const size_t fsms_size){
    assert(state_ex.state.empty());
    state_ex.state.resize_branch(fsms_size);
    state_ex.lazy=insert_node_to(state_ex,edge_view);
    if(state_ex.lazy==FSM_Node::Lazy::L)
        state_ex.last_branch_num = edge_view.branch_num;
    state_ex.on=true;
}

void policy_edge_insert(State_Ex& state_ex,const FSM_Edge_View edge_view){
    switch(state_ex.lazy){
        case FSM_Node::Lazy::N:{
            state_ex.lazy=insert_node_to(state_ex,edge_view);
            if(state_ex.lazy==FSM_Node::Lazy::L)
                state_ex.last_branch_num=edge_view.branch_num;
            break;
        }
        case FSM_Node::Lazy::L:{
            if(edge_view.branch_num!=state_ex.last_branch_num){
                state_ex.lazy = FSM_Node::Lazy::N;
                insert_node_to(state_ex,edge_view);
            }
            break;
        }
    }
}

/// The last insertion into `state_ex`.
void policy_edge_insert_simple(State_Ex& state_ex,const FSM_Edge_View edge_view){
    switch(state_ex.lazy){
        case FSM_Node::Lazy::N:
            insert_node_to(state_ex,edge_view);break;
        case FSM_Node::Lazy::L:{
            if(edge_view.branch_num!=state_ex.last_branch_num)
                insert_node_to(state_ex,edge_view);
            break;
        }
    }
}

/// @return `true` if `state_ex.lazy==FSM_Node::Lazy::D`.
bool policy_edge_insert_meta(State_Ex& state_ex,const Meta_Edge me){
    // Adapted version of `policy_edge_insert`. The only difference is `case FSM_Node::Lazy::D`.
    switch(state_ex.lazy){
        case FSM_Node::Lazy::N:{
            state_ex.lazy=insert_node_to(state_ex,me);
            if(state_ex.lazy==FSM_Node::Lazy::L)
                state_ex.last_branch_num=me.branch_num;
            return false;
        }
        case FSM_Node::Lazy::L:{
            if(me.branch_num!=state_ex.last_branch_num){
                state_ex.lazy = FSM_Node::Lazy::N;
                insert_node_to(state_ex,me);
            }
            return false;
        }
        case FSM_Node::Lazy::D: return true;
    }
    return false;
}


void policy_edge_3(const size_t fsms_size){
    YUKI_LEX_META_DBGO("S{} policy_edge_3\n",worklist.front()->mapped);
    const FSM_Edge_View edge_view0 = edge_views[0];
    const FSM_Edge_View edge_view1 = edge_views[1];
    const FSM_Edge_View edge_view2 = edge_views[2];

    const Char_Class cc01 = (*edge_view0.cc) + (*edge_view1.cc);
    if(cc01.is_complete())
        cc_union.make_complete();
    else
        cc_union = cc01 + (*edge_view2.cc);

    const Char_Class cc0_1 = (*edge_view0.cc) * (*edge_view1.cc);
    const Char_Class cc0_1_2 = cc0_1.empty() ? Char_Class{} : cc0_1*(*edge_view2.cc);

    cc_temp = (*edge_view0.cc)-((*edge_view1.cc)+(*edge_view2.cc));
    State_Ex s0;
    policy_edge_init(s0,edge_view0,fsms_size);
    if(!cc_temp.empty())
        transition_table.insert(std::move(cc_temp),insert_to_ss(s0));

    cc_temp = (*edge_view1.cc)-((*edge_view0.cc)+(*edge_view2.cc));
    State_Ex s1;
    policy_edge_init(s1,edge_view1,fsms_size);
    if(!cc_temp.empty())
        transition_table.insert(std::move(cc_temp),insert_to_ss(s1));

    cc_temp = (*edge_view2.cc) - cc01;
    if(!cc_temp.empty()){
        assert(next_always_resized.empty());
        insert_node_to(next_always_resized,edge_view2);
        transition_table.insert(std::move(cc_temp),insert_next_ar_to_ss(fsms_size));
    }

    State_Ex s01;

    cc_temp = (*edge_view0.cc)*(*edge_view2.cc)-(*edge_view1.cc);
    if(!cc_temp.empty()){
        s01 = s0;
        policy_edge_insert_simple(s0,edge_view2);
        transition_table.insert(std::move(cc_temp),insert_to_ss(std::move(s0)));
    }else
        s01 = std::move(s0);

    // At this point, `s01` contains `edge_view0`.
    // `s0` is useless afterwards.

    cc_temp = (*edge_view1.cc)*(*edge_view2.cc)-(*edge_view0.cc);
    if(!cc_temp.empty()){
        policy_edge_insert_simple(s1,edge_view2);
        transition_table.insert(std::move(cc_temp),insert_to_ss(std::move(s1)));
    }

    // `s1` is useless afterwards.

    cc_temp = cc0_1 - (*edge_view2.cc);
    if(!cc_temp.empty()){
        policy_edge_insert(s01,edge_view1);

        if(cc0_1_2.empty()){
            transition_table.insert(std::move(cc_temp),insert_to_ss(std::move(s01)));
            return;
        }else{
            transition_table.insert(std::move(cc_temp),insert_to_ss(s01));
            // At this point, `s01` contains `edge_view0` and `edge_view1`.
            policy_edge_insert_simple(s01,edge_view2);
            transition_table.insert(std::move(cc0_1_2),insert_to_ss(std::move(s01)));
        }
    }

    // At this point, `s01` contains (only) `edge_view0`.

    if(!cc0_1_2.empty()){
        policy_edge_insert(s01,edge_view1);
        policy_edge_insert_simple(s01,edge_view2);
        transition_table.insert(std::move(cc0_1_2),insert_to_ss(std::move(s01)));
    }
} // policy_edge_3


struct IEntry{
    uint_least64_t edge_indices; ///< @sa suffix_index
    Char_Class cc;
    union{
    IEntry* stem;
    State_Ex* stem_base;
    };
    State_Ex* state_cached;

    IEntry(const uint_least64_t a,Char_Class&& b,IEntry* const c) noexcept :
        edge_indices(a),
        cc(std::move(b)),
        stem(c),
        state_cached(nullptr)
    {}

    IEntry(const uint_least64_t a,Char_Class&& b,State_Ex* const c) noexcept :
        edge_indices(a),
        cc(std::move(b)),
        stem_base(c),
        state_cached(nullptr)
    {}

    IEntry(const uint_least64_t a,Char_Class&& b) noexcept :
        edge_indices(a),
        cc(std::move(b)),
        stem(nullptr),
        state_cached(nullptr)
    {}

    IEntry(const uint_least64_t a) noexcept :
        edge_indices(a),
        cc(),
        stem(nullptr),
        state_cached(nullptr)
    {}

    ~IEntry() noexcept {delete state_cached;}
};

struct UEntry{
    uint_least64_t edge_indices;
    Char_Class cc;
};

constexpr size_t suffix_index(const unsigned total_edges,const uint_least64_t subset) {return total_edges-1-std::countr_zero(subset);}

constexpr uint_least64_t stem(uint_least64_t subset) {return subset-=1ULL<<std::countr_zero(subset);}

/// @pre `vec->edge_indices` should be arranged in descending order.
template<typename V>
auto first_less_equiv(V& vec,const uint_least64_t subset) -> decltype(vec.begin()) {
    typename V::size_type count = vec.size();
    if(count==0 || vec.back().edge_indices > subset)
        return vec.end();

    typename V::size_type step;
    auto first = vec.begin();
    decltype(first) it;
    while(count>0){
        step = count/2;
        it = first + step;
        if(it->edge_indices <= subset){
            count = step;
        }else{
            first = ++it;
            count -= step+1;
        }
    }
    return first;
}

template<typename V>
auto find(V& vec,const uint_least64_t subset) -> decltype(vec.begin()) {
    const auto fle = first_less_equiv(vec,subset);
    return (fle!=vec.end() && fle->edge_indices==subset) ? fle : vec.end();
}

enum struct AC_Type : unsigned {IU,I,U,E};

struct accumulate_ret_t{
    AC_Type type;
    unsigned height_i;
    unsigned height_u;
};

/*
Definition: An `intersectionss[i]` or `unionss[i]` is said to be empty iff. its `size()` equals 0.
Definition: An `intersectionss[i]` is said to be truely-empty iff. it's empty and a possible calculation of this tier results in empty sets only.
Definition: A `unionss[i]` is said to be truely-empty iff. it's empty and a possible calculation of this tier results in complete sets only.
Note:
    1. {IU,hi,hu}. All `intersectionss[i>=hi]` and all `unioss[i>=hu]` are truely-empty. All tiers below are fully-calculated.
    2. {I,hi,hu}. All `intersectionss[i>=hi]` are truely-empty and all `unioss[i>hu]` are empty. `unionss[hu]` could possibly be non-empty. All tiers below are fully-calculated.
    3. {U,hi,hu}. All `intersectionss[i>hi]` are empty and all `unioss[i>=hu]` are truely-empty. `intersectionss[hi]` could possibly be non-empty. All tiers below are fully-calculated.
    4. {E,hi,hu}. All `intersectionss[i>=hi]` and all `unioss[i>=hu]` are empty. `intersectionss[hi]` and `unioss[hu]` could possibly be half-calculated (including non-calculated). All tiers below are fully-calculated.
*/

#ifndef YUKI_LEX_ACCUMULATE_MAX_INTERSECTIONS
#define YUKI_LEX_ACCUMULATE_MAX_INTERSECTIONS 16384
#endif
static_assert(YUKI_LEX_ACCUMULATE_MAX_INTERSECTIONS>=64*63/2);
#ifndef YUKI_LEX_ACCUMULATE_MAX_UNIONS
#define YUKI_LEX_ACCUMULATE_MAX_UNIONS 16384
#endif
static_assert(YUKI_LEX_ACCUMULATE_MAX_UNIONS>=64*63/2);
#ifndef YUKI_LEX_ACCUMULATE_FORCE_IU_UPPER_THRESHHOLD
#define YUKI_LEX_ACCUMULATE_FORCE_IU_UPPER_THRESHHOLD 7/8
#endif

/// @note As should not be too hard to see, the returned value satisfies the various preconditions of the various `policy_edge` routines.
template<yuki::Vector<IEntry>* intersectionss,yuki::Vector<UEntry>* unionss,State_Ex* base_states>
accumulate_ret_t accumulate(const FSM_Edge_View* const edge_views,const unsigned total_edges){
    struct Acc_Impl{
        const FSM_Edge_View* const edge_views_acc_impl;
        const unsigned total_edges_acc_impl;

        size_t make_intersections(const unsigned hi){
            yuki::Vector<IEntry>& intersections = intersectionss[hi];
            assert(intersections.empty());
            intersections.reserve(intersectionss[hi-1].size()*(total_edges_acc_impl-hi-1)/(hi+2));
            for(IEntry& ie : intersectionss[hi-1]){
                const uint_least64_t stem = ie.edge_indices;
                for(uint_least64_t added=1ULL<<std::countr_zero(stem); added>1;){
                    added>>=1;
                    cc_temp = ie.cc * (*(edge_views_acc_impl[suffix_index(total_edges_acc_impl,added)].cc));
                    if(!cc_temp.empty())
                        intersections.emplace_back(stem+added,std::move(cc_temp),&ie);
                }
            }
            return intersections.size();
        }

        size_t make_unions(const unsigned hu){
            yuki::Vector<UEntry>& unions = unionss[hu];
            assert(unions.empty());
            unions.reserve(unionss[hu-1].size()*(total_edges_acc_impl-hu-1)/(hu+2));
            for(const UEntry& ue : unionss[hu-1]){
                const uint_least64_t stem = ue.edge_indices;
                for(uint_least64_t added=1ULL<<std::countr_zero(stem); added>1;){
                    added>>=1;
                    cc_temp = ue.cc + (*(edge_views_acc_impl[suffix_index(total_edges_acc_impl,added)].cc));
                    if(!cc_temp.is_complete())
                        unions.emplace_back(stem+added,std::move(cc_temp));
                }
            }
            return unions.size();
        }

        void make_unions0(){
            assert(unionss[0].empty());
            uint_least64_t stem=1ULL<<(total_edges_acc_impl-1);
            for(unsigned i=0; stem>1; stem>>=1,++i){
                uint_least64_t added = stem>>1;
                for(unsigned j=i+1; added!=0; added>>=1,++j){
                    cc_temp = (*(edge_views_acc_impl[i].cc))+(*(edge_views_acc_impl[j].cc));
                    if(!cc_temp.is_complete())
                        unionss[0].emplace_back(stem+added,std::move(cc_temp));
                }
            }
        }

        accumulate_ret_t make_intersections_until_max(unsigned hi,const unsigned hu,size_t& total_intersections){
            assert(hi>hu); // So as to meet precondition 1 of `policy_edge_u`.
            for(;hi<total_edges_acc_impl-2;++hi){
                yuki::Vector<IEntry>& intersections = intersectionss[hi];
                assert(intersections.empty());
                intersections.reserve(intersectionss[hi-1].size()*(total_edges_acc_impl-hi-1)/(hi+2));
                for(IEntry& ie : intersectionss[hi-1]){
                    const uint_least64_t stem = ie.edge_indices;
                    for(uint_least64_t added=1ULL<<std::countr_zero(stem); added>1;){
                        added>>=1;
                        cc_temp = ie.cc * (*(edge_views_acc_impl[suffix_index(total_edges_acc_impl,added)].cc));
                        if(!cc_temp.empty()){
                            if(total_intersections<YUKI_LEX_ACCUMULATE_MAX_INTERSECTIONS){
                                intersections.emplace_back(stem+added,std::move(cc_temp),&ie);
                                ++total_intersections;
                            }else
                                return {AC_Type::U,hi,hu};
                        }
                    } // for(uint_least64_t added=1ULL<<std::countr_zero(stem); added>1;)
                } // for(IEntry& ie : intersectionss[hi-1])
                if(intersections.size()==0)
                    return {AC_Type::IU,hi,hu};
            } // for(;hi<total_edges_acc_impl-2;++hi)
            return {AC_Type::IU,total_edges_acc_impl-2,hu};
        }

        accumulate_ret_t make_unions_until_max(const unsigned hi,unsigned hu,size_t& total_unions){
            for(;hu<total_edges_acc_impl-2;++hu){
                yuki::Vector<UEntry>& unions = unionss[hu];
                assert(unions.empty());
                unions.reserve(unionss[hu-1].size()*(total_edges_acc_impl-hu-1)/(hu+2));
                for(const UEntry& ue : unionss[hu-1]){
                    const uint_least64_t stem = ue.edge_indices;
                    for(uint_least64_t added=1ULL<<std::countr_zero(stem); added>1;){
                        added>>=1;
                        cc_temp = ue.cc + (*(edge_views_acc_impl[suffix_index(total_edges_acc_impl,added)].cc));
                        if(!cc_temp.is_complete()){
                            if(total_unions<YUKI_LEX_ACCUMULATE_MAX_UNIONS){
                                unions.emplace_back(stem+added,std::move(cc_temp));
                                ++total_unions;
                            }else
                                return {AC_Type::I,hi,hu};
                        }
                    } // for(uint_least64_t added=1ULL<<std::countr_zero(stem); added>1;)
                    if(unions.size()==0)
                        return {AC_Type::IU,hi,hu};
                } // for(const UEntry& ue : unionss[hu-1])
            } // for(;hu<total_edges_acc_impl-2;++hu)
            return {AC_Type::IU,hi,total_edges_acc_impl-2};
        }

    } acc_impl{edge_views,total_edges};

    // Phase 0
    assert(intersectionss[0].empty());
    uint_least64_t stem0=1ULL<<(total_edges-1);
    for(unsigned i=0; stem0>1; stem0>>=1,++i){
        uint_least64_t added = stem0>>1;
        for(unsigned j=i+1; added!=0; added>>=1,++j){
            cc_temp = (*(edge_views[i].cc))*(*(edge_views[j].cc));
            if(!cc_temp.empty())
                intersectionss[0].emplace_back(stem0+added,std::move(cc_temp),base_states+suffix_index(total_edges,stem0));
        }
    }

    if(intersectionss[0].empty()){
        acc_impl.make_unions0();
        if(!unionss[0].empty()){
            size_t total_unions_local=unionss[0].size();
            return acc_impl.make_unions_until_max(0,1,total_unions_local);
        }
        return {AC_Type::IU,0,0};
    }

    size_t total_intersections = intersectionss[0].size();

    acc_impl.make_unions0();
    if(unionss[0].empty())
        return acc_impl.make_intersections_until_max(1,0,total_intersections);

    size_t total_unions = unionss[0].size();

    // Phase 2
    unsigned h = 1;

    for(;h<(total_edges-2)*YUKI_LEX_ACCUMULATE_FORCE_IU_UPPER_THRESHHOLD;++h){
        yuki::Vector<IEntry>& intersections = intersectionss[h];
        assert(intersections.empty());
        intersections.reserve(intersectionss[h-1].size()*(total_edges-h-1)/(h+2));
        for(IEntry& ie : intersectionss[h-1]){
            const uint_least64_t stem = ie.edge_indices;
            for(uint_least64_t added=1ULL<<std::countr_zero(stem); added>1;){
                added>>=1;
                cc_temp = ie.cc * (*(edge_views[suffix_index(total_edges,added)].cc));
                if(!cc_temp.empty()){
                    if(total_intersections<YUKI_LEX_ACCUMULATE_MAX_INTERSECTIONS){
                        intersections.emplace_back(stem+added,std::move(cc_temp),&ie);
                        ++total_intersections;
                    }else
                        return {AC_Type::E,h+1,h};
                }
            }
        }

        if(intersections.empty())
            return acc_impl.make_unions_until_max(h,h,total_unions);

        yuki::Vector<UEntry>& unions = unionss[h];
        assert(unions.empty());
        unions.reserve(unionss[h-1].size()*(total_edges-h-1)/(h+2));
        for(const UEntry& ue : unionss[h-1]){
            const uint_least64_t stem = ue.edge_indices;
            for(uint_least64_t added=1ULL<<std::countr_zero(stem); added>1;){
                added>>=1;
                cc_temp = ue.cc + (*(edge_views[suffix_index(total_edges,added)].cc));
                if(!cc_temp.is_complete()){
                    if(total_unions<YUKI_LEX_ACCUMULATE_MAX_UNIONS){
                        unions.emplace_back(stem+added,std::move(cc_temp));
                        ++total_unions;
                    }else
                        return {AC_Type::E,h+1,h+1};
                }
            }
        }

        if(unions.empty())
            return acc_impl.make_intersections_until_max(h+1,h,total_intersections);
    } // for(;h<(total_edges-2)*YUKI_LEX_ACCUMULATE_FORCE_IU_THRESHHOLD;++h)

    // Phase 3
    unsigned hi=h,hu=h;

    for(;hi<total_edges-2;++hi)
        if(acc_impl.make_intersections(hi)==0)
            break;

    for(;hu<total_edges-2;++hu)
        if(acc_impl.make_unions(hu)==0)
            break;

    return {AC_Type::IU,hi,hu};
} // accumulate

/// Used for debugging `policy_edge_i` and `policy_edge_u`. The normal `accumulate` favors `AC_Type::IU` which makes debugging the other 2 alternatives rather difficult.
template<yuki::Vector<IEntry>* intersectionss,yuki::Vector<UEntry>* unionss,State_Ex* base_states>
accumulate_ret_t accumulate_simple(const FSM_Edge_View* const edge_views,const unsigned total_edges){
    assert(intersectionss[0].empty());
    uint_least64_t stem0=1ULL<<(total_edges-1);
    for(unsigned i=0; stem0>1; stem0>>=1,++i){
        uint_least64_t added = stem0>>1;
        for(unsigned j=i+1; added!=0; added>>=1,++j){
            cc_temp = (*(edge_views[i].cc))*(*(edge_views[j].cc));
            if(!cc_temp.empty())
                intersectionss[0].emplace_back(stem0+added,std::move(cc_temp),base_states+suffix_index(total_edges,stem0));
        }
    }

    if(intersectionss[0].empty())
        return {AC_Type::I,0,0};
    size_t total_intersections = intersectionss[0].size();

    assert(unionss[0].empty());
    stem0=1ULL<<(total_edges-1);
    for(unsigned i=0; stem0>1; stem0>>=1,++i){
        uint_least64_t added = stem0>>1;
        for(unsigned j=i+1; added!=0; added>>=1,++j){
            cc_temp = (*(edge_views[i].cc))+(*(edge_views[j].cc));
            if(!cc_temp.is_complete())
                unionss[0].emplace_back(stem0+added,std::move(cc_temp));
        }
    }

    if(unionss[0].empty())
        return {AC_Type::U,1,0};
    size_t total_unions = unionss[0].size();

    for(unsigned h=1;h<total_edges-3;++h){
        yuki::Vector<IEntry>& intersections = intersectionss[h];
        assert(intersections.empty());
        intersections.reserve(intersectionss[h-1].size()*(total_edges-h-1)/(h+2));
        for(IEntry& ie : intersectionss[h-1]){
            const uint_least64_t stem = ie.edge_indices;
            for(uint_least64_t added=1ULL<<std::countr_zero(stem); added>1;){
                added>>=1;
                cc_temp = ie.cc * (*(edge_views[suffix_index(total_edges,added)].cc));
                if(!cc_temp.empty()){
                    if(total_intersections<YUKI_LEX_ACCUMULATE_MAX_INTERSECTIONS){
                        intersections.emplace_back(stem+added,std::move(cc_temp),&ie);
                        ++total_intersections;
                    }else
                        return {AC_Type::E,h+1,h};
                }
            }
        }
        if(intersections.empty())
            return {AC_Type::I,h,h};

        yuki::Vector<UEntry>& unions = unionss[h];
        assert(unions.empty());
        unions.reserve(unionss[h-1].size()*(total_edges-h-1)/(h+2));
        for(const UEntry& ue : unionss[h-1]){
            const uint_least64_t stem = ue.edge_indices;
            for(uint_least64_t added=1ULL<<std::countr_zero(stem); added>1;){
                added>>=1;
                cc_temp = ue.cc + (*(edge_views[suffix_index(total_edges,added)].cc));
                if(!cc_temp.is_complete()){
                    if(total_unions<YUKI_LEX_ACCUMULATE_MAX_UNIONS){
                        unions.emplace_back(stem+added,std::move(cc_temp));
                        ++total_unions;
                    }else
                        return {AC_Type::E,h+1,h+1};
                }
            }
        }
        if(unions.empty())
            return {AC_Type::U,h+1,h};
    } // for(unsigned h=1;h<total_edges-3;++h)

    yuki::Vector<IEntry>& intersections = intersectionss[total_edges-3];
    assert(intersections.empty());
    intersections.reserve(intersectionss[total_edges-4].size()*2/(total_edges-1));
    for(IEntry& ie : intersectionss[total_edges-4]){
        const uint_least64_t stem = ie.edge_indices;
        for(uint_least64_t added=1ULL<<std::countr_zero(stem); added>1;){
            added>>=1;
            cc_temp = ie.cc * (*(edge_views[suffix_index(total_edges,added)].cc));
            if(!cc_temp.empty())
                intersections.emplace_back(stem+added,std::move(cc_temp),&ie);
        }
    }
    yuki::Vector<UEntry>& unions = unionss[total_edges-3];
    assert(unions.empty());
    unions.reserve(unionss[total_edges-4].size()*2/(total_edges-1));
    for(const UEntry& ue : unionss[total_edges-4]){
        const uint_least64_t stem = ue.edge_indices;
        for(uint_least64_t added=1ULL<<std::countr_zero(stem); added>1;){
            added>>=1;
            cc_temp = ue.cc + (*(edge_views[suffix_index(total_edges,added)].cc));
            if(!cc_temp.is_complete())
                unions.emplace_back(stem+added,std::move(cc_temp));
        }
    }
    return {AC_Type::IU,total_edges-2,total_edges-2};
} // accumulate_simple


/*
Definition: Let `a` and `b` be 2 unsigned number. I say `a` is recursively less than or equivalent to `b` (abbr. `a` rle `b`), iff. `a` <= `b`, and their stems (i.e. the number produced by removing the least significant "1", if any), stems of stems, stems of stems of stems, etc. also satisfy the <= relation. In the same way I can define the rge relation.

Within each tier of either intersectionss or unionss, `edge_indices`s of consecutive entries satisfy the rge relation.

RLE(RGE) Theorem: For numbers with the same count of "1"s, rle is equivalent to <=. Similarly rge is equivalent to >=.
Proof: (One direction is trivially true, by definition.)
First note that this proposition is inductive. That is, since the 2 numbers have the same count of "1"s, their stems must also have the same count of "1"s. So there is only need to prove a single iteration. That is, `a`<=`b` implies `stem(a)`<=`stem(b)`.
Now first we can remove the common prefix of both numbers. If the remainder is nothing then the 2 numbers are exactly the same, in which case the propsition holds trivially. Now suppose we are left with 2 non-empty numbers, then the msb of the bigger one must be "1" and the same bit of the smaller one must be "0", for otherwise we would either have a longer common prefix or violate the <= relation. Now remove the least significant "1" to compute the stem. If the said bit of the greater one does not get removed then result is obvious. Now suppose the said bit of the greater one does get removed. Since that "1" is the MOST significant "1", the greater number before removal must contain only a single "1". Now because the 2 numbers have the same count of "1"s, the smaller number before removal should also have only a single "1". So after removal both number would equal 0, thus proving the theorem.
*/


template<yuki::Vector<IEntry>* intersectionss,yuki::Vector<UEntry>* unionss,State_Ex* base_states>
void policy_edge_iu(const size_t fsms_size,const unsigned height_i,const unsigned height_u);
template<yuki::Vector<IEntry>* intersectionss,yuki::Vector<UEntry>* unionss,State_Ex* base_states>
void policy_edge_i(const size_t fsms_size,const unsigned height_i,const unsigned height_u);
template<yuki::Vector<IEntry>* intersectionss,yuki::Vector<UEntry>* unionss,State_Ex* base_states>
void policy_edge_u(const size_t fsms_size,const unsigned height_i,const unsigned height_u);


bool policy_edge(
    const size_t fsms_size
    #ifdef YUKI_LEX_META_DBG
    ,FILE* const acc_simple = nullptr
    #endif
){
    static yuki::Vector<IEntry> intersectionss[62]; ///< i.e. 2-63-subsets. `intersectionss[i]` contains `i+2`-subsets.
    static yuki::Vector<UEntry> unionss[62]; ///< Ditto.

    static State_Ex base_states[64]; ///< States for 1-subsets.

    static bool inited=false;
    if(!inited){
        inited=true;
        for(unsigned i=0;i<10;++i){
            static constexpr unsigned combinations[10] = {66,220,495,792,924,792,495,220,66,12};
            intersectionss[i].reserve(combinations[i]);
            unionss[i].reserve(combinations[i]);
        }
    }

    const size_t total_edges = edge_views.size();
    #ifndef YUKI_LEX_META_DBG
    const accumulate_ret_t ac_ret = accumulate<intersectionss,unionss,base_states>(edge_views.begin(),total_edges);
    #else
    const accumulate_ret_t ac_ret = acc_simple ? accumulate_simple<intersectionss,unionss,base_states>(edge_views.begin(),total_edges) : accumulate<intersectionss,unionss,base_states>(edge_views.begin(),total_edges);
    #endif
    switch(ac_ret.type){
        case AC_Type::IU:{
            #ifdef YUKI_LEX_META_DBG
            YUKI_LEX_META_DBGO("policy_edge_iu intersectionss({}): ",ac_ret.height_i);
            for(unsigned h=0;h<ac_ret.height_i;++h)
               fmt::print(YUKI_LEX_META_DBG_FP,"{} ",intersectionss[h].size());
            fmt::print(YUKI_LEX_META_DBG_FP,"\n");
            YUKI_LEX_META_DBGO("policy_edge_iu unionss({}): ",ac_ret.height_u);
            for(unsigned h=0;h<ac_ret.height_u;++h)
                fmt::print(YUKI_LEX_META_DBG_FP,"{} ",unionss[h].size());
            fmt::print(YUKI_LEX_META_DBG_FP,"\n");
            fflush(YUKI_LEX_META_DBG_FP);
            #endif
            policy_edge_iu<intersectionss,unionss,base_states>(fsms_size,ac_ret.height_i,ac_ret.height_u);
            return true;
        }
        case AC_Type::I:{
            #ifdef YUKI_LEX_META_DBG
            YUKI_LEX_META_DBGO("policy_edge_i intersectionss({}): ",ac_ret.height_i);
            for(unsigned h=0;h<ac_ret.height_i;++h)
               fmt::print(YUKI_LEX_META_DBG_FP,"{} ",intersectionss[h].size());
            fmt::print(YUKI_LEX_META_DBG_FP,"\n");
            YUKI_LEX_META_DBGO("policy_edge_i unionss({}): ",ac_ret.height_u);
            for(unsigned h=0;h<ac_ret.height_u;++h)
                fmt::print(YUKI_LEX_META_DBG_FP,"{} ",unionss[h].size());
            fmt::print(YUKI_LEX_META_DBG_FP,"\n");
            fflush(YUKI_LEX_META_DBG_FP);
            #endif
            policy_edge_i<intersectionss,unionss,base_states>(fsms_size,ac_ret.height_i,ac_ret.height_u);
            return true;
        }
        case AC_Type::U:{
            #ifdef YUKI_LEX_META_DBG
            YUKI_LEX_META_DBGO("policy_edge_u intersectionss({}): ",ac_ret.height_i);
            for(unsigned h=0;h<ac_ret.height_i;++h)
               fmt::print(YUKI_LEX_META_DBG_FP,"{} ",intersectionss[h].size());
            fmt::print(YUKI_LEX_META_DBG_FP,"\n");
            YUKI_LEX_META_DBGO("policy_edge_u unionss({}): ",ac_ret.height_u);
            for(unsigned h=0;h<ac_ret.height_u;++h)
                fmt::print(YUKI_LEX_META_DBG_FP,"{} ",unionss[h].size());
            fmt::print(YUKI_LEX_META_DBG_FP,"\n");
            fflush(YUKI_LEX_META_DBG_FP);
            #endif
            policy_edge_u<intersectionss,unionss,base_states>(fsms_size,ac_ret.height_i,ac_ret.height_u);
            return true;
        }
        default:{
            assert(ac_ret.type==AC_Type::E);
            #ifdef YUKI_LEX_META_DBG
            YUKI_LEX_META_DBGO("policy_edge_e intersectionss({}): ",ac_ret.height_i);
            for(unsigned h=0;h<ac_ret.height_i;++h)
               fmt::print(YUKI_LEX_META_DBG_FP,"{} ",intersectionss[h].size());
            fmt::print(YUKI_LEX_META_DBG_FP,"\n");
            YUKI_LEX_META_DBGO("policy_edge_e unionss({}): ",ac_ret.height_u);
            for(unsigned h=0;h<ac_ret.height_u;++h)
                fmt::print(YUKI_LEX_META_DBG_FP,"{} ",unionss[h].size());
            fmt::print(YUKI_LEX_META_DBG_FP,"\n");
            fflush(YUKI_LEX_META_DBG_FP);
            #endif
            for(unsigned i=0;i<ac_ret.height_i;++i)
                intersectionss[i].clear();
            for(unsigned i=0;i<ac_ret.height_u;++i)
                unionss[i].clear();
            return false;
        }
    }

}


template<yuki::Vector<IEntry>* intersectionss,yuki::Vector<UEntry>* unionss,State_Ex* base_states>
void policy_edge_iu(const size_t fsms_size,const unsigned height_i,const unsigned height_u){
    YUKI_LEX_META_DBGO("S{} policy_edge_iu\n",worklist.front()->mapped);

    const unsigned total_edges = edge_views.size();
    const uint_least64_t full = (1ULL<<total_edges)-1;

    for(int h=0;h<=(int)total_edges-4-(int)height_i && h<(int)height_u;++h)
        unionss[h].clear();

    // 1-subsets
    if(height_u==total_edges-2){
        yuki::Vector<UEntry>& complements = unionss[total_edges-3];
        const yuki::Vector<UEntry>::iterator complements_end = complements.end();
        uint_least64_t stem = 1ULL<<(total_edges-1);
        for(unsigned i=0;i<total_edges;++i,stem>>=1){
            const FSM_Edge_View edge_view = edge_views[i];
            const yuki::Vector<UEntry>::iterator complement = find(complements,full-stem);
            if(complement!=complements_end){
                cc_temp = (*edge_view.cc) - (complement->cc);
                complement->cc.reset();
            }else
                cc_temp.clear();
            if(!cc_temp.empty()){
                policy_edge_init(base_states[i],edge_view,fsms_size);
                transition_table.insert(std::move(cc_temp),insert_to_ss(base_states[i]));
            }
        }
        complements.clear();
    }

    // 2-subsets
    if(height_i>0){
        yuki::Vector<UEntry>& complements = unionss[total_edges-4];
        const yuki::Vector<UEntry>::iterator complements_end = complements.end();
        yuki::Vector<IEntry>::iterator b = intersectionss[0].begin();
        yuki::Vector<IEntry>::iterator bb = b;
        const yuki::Vector<IEntry>::iterator e = intersectionss[0].end();
        for(;b!=e;++b){
            ++bb;
            const yuki::Vector<UEntry>::iterator complement = find(complements,full-b->edge_indices);
            if(complement!=complements_end){
                cc_temp = b->cc - (complement->cc);
                complement->cc.reset();
            }else
                cc_temp.clear();
            b->cc.reset();

            State_Ex* const stem_base = b->stem_base;
            assert(stem_base);
            if(!stem_base->on)
                policy_edge_init(*stem_base,edge_views[suffix_index(total_edges,stem(b->edge_indices))],fsms_size);
            State_Ex* const state_ex = (bb!=e && stem_base==bb->stem_base) ? new State_Ex(*stem_base) : new State_Ex(std::move(*stem_base));
            policy_edge_insert(*state_ex,edge_views[suffix_index(total_edges,b->edge_indices)]);
            if(!cc_temp.empty())
                transition_table.insert(std::move(cc_temp),insert_to_ss(*state_ex));
            b->state_cached = state_ex;
        }
    }
    unionss[total_edges-4].clear();
    for(unsigned i=0;i<total_edges;++i)
        base_states[i].clear();

    unsigned h=1;
    // Same as 2-subsets, except for the state calculation part and the cleaning part.
    for(;h<(total_edges-3<height_i?total_edges-3:height_i);++h){
        yuki::Vector<UEntry>& complements = unionss[total_edges-4-h];
        const yuki::Vector<UEntry>::iterator complements_end = complements.end();
        yuki::Vector<IEntry>::iterator b = intersectionss[h].begin();
        yuki::Vector<IEntry>::iterator bb = b;
        const yuki::Vector<IEntry>::iterator e = intersectionss[h].end();
        for(;b!=e;++b){
            ++bb;
            const yuki::Vector<UEntry>::iterator complement = find(complements,full-b->edge_indices);
            if(complement!=complements_end){
                cc_temp = b->cc - (complement->cc);
                complement->cc.reset();
            }else
                cc_temp.clear();
            b->cc.reset();

            State_Ex*& stem_state_cached = b->stem->state_cached;
            assert(stem_state_cached);
            const bool copy = (bb!=e && b->stem==bb->stem);
            State_Ex* const state_ex = copy ? new State_Ex(*stem_state_cached) : new State_Ex(std::move(*stem_state_cached));
            policy_edge_insert(*state_ex,edge_views[suffix_index(total_edges,b->edge_indices)]);
            if(!cc_temp.empty())
                transition_table.insert(std::move(cc_temp),insert_to_ss(*state_ex));
            b->state_cached = state_ex;
            if(!copy){
                delete stem_state_cached;
                stem_state_cached = nullptr;
            }
        }
        complements.clear();
        intersectionss[h-1].clear();
    }

    { // (n-1)-subsets and n-subset.
    const yuki::Vector<IEntry>& intersections = intersectionss[total_edges-3];
    yuki::Vector<IEntry>::const_iterator b = intersections.begin();
    yuki::Vector<IEntry>::const_iterator bb = b;
    const yuki::Vector<IEntry>::const_iterator e = intersections.end();
    for(;b!=e;++b){
        ++bb;
        cc_temp = b->cc - (*edge_views[suffix_index(total_edges,full-b->edge_indices)].cc);
        if(!cc_temp.empty()){
            State_Ex*& stem_state_cached = b->stem->state_cached;
            assert(stem_state_cached!=nullptr);
            const bool copy = (bb!=e && b->stem==bb->stem);
            next = copy ? State_Ex(*stem_state_cached) : State_Ex(std::move(*stem_state_cached));
            policy_edge_insert(next,edge_views[suffix_index(total_edges,b->edge_indices)]);
            if(b->edge_indices==full-1){ // Process the n-subset.
                cc_temp2 = b->cc * (*(edge_views.back().cc));
                if(!cc_temp2.empty()){
                    next2=next;
                    policy_edge_insert_simple(next2,edge_views.back());
                    transition_table.insert(std::move(cc_temp2),insert_to_ss(std::move(next2)));
                }
            }
            transition_table.insert(std::move(cc_temp),insert_to_ss(std::move(next)));
            if(!copy){
                delete stem_state_cached;
                stem_state_cached=nullptr;
            }
        }else if(b->edge_indices==full-1){ // Process the n-subset.
            cc_temp = b->cc * (*(edge_views.back().cc));
            if(!cc_temp.empty()){
                State_Ex*& stem_state_cached = b->stem->state_cached;
                assert(stem_state_cached!=nullptr);
                const bool copy = (bb!=e && b->stem==bb->stem);
                next = copy ? State_Ex(*stem_state_cached) : State_Ex(std::move(*stem_state_cached));
                policy_edge_insert(next,edge_views[total_edges-2]);
                policy_edge_insert_simple(next,edge_views.back());
                transition_table.insert(std::move(cc_temp),insert_to_ss(std::move(next)));
                if(!copy){
                    delete stem_state_cached;
                    stem_state_cached=nullptr;
                }
            }
        }
        b->~IEntry();
    } // for(;b!=e;++b)
    intersectionss[h-1].clear();
    assert(h==total_edges-3 || intersectionss[h].empty());
    intersectionss[h].force_clear();
    } // (n-1)-subsets and n-subset.
} // policy_edge_iu


/// @pre `height_i<total_edges-2 && height_u<total_edges-3`
/// @pre `height_u>=1`
template<yuki::Vector<IEntry>* intersectionss,yuki::Vector<UEntry>* unionss,State_Ex* base_states>
void policy_edge_i(const size_t fsms_size,const unsigned height_i,const unsigned height_u){
    // The codes is much like the codes of `policy_edge_iu`, except that the complementary unions might need to be calculated on the fly.

    const unsigned total_edges = edge_views.size();
    const uint_least64_t full = (1ULL<<total_edges)-1;

    assert(height_i<total_edges-2); // Precondition 0
    assert(height_u<total_edges-3); // Precondition 1
    assert(height_u>=1); // Precondition 2
    YUKI_LEX_META_DBGO("S{} policy_edge_i\n",worklist.front()->mapped);

    unionss[height_u].clear(); // Due to Precondition 1, `height_u` always represents a valid index.

    // Unlike `policy_edge_iu`, unionss[height_u-1] has to be kept, as the base from which higher unions are calculated.
    const int unused_complements_index = int(total_edges)-4-int(height_i);
    const int unionss_last = int(height_u)-1; // Note: Due to Precondition 2 this is always non-negative.
    if(unused_complements_index<unionss_last){
        for(int h=0;h<=unused_complements_index;++h)
            unionss[h].clear();
    }else{
        for(int h=0;h<unionss_last;++h)
            unionss[h].clear();
    }

    static struct{
        struct{
            uint_least64_t edge_indices;
            yuki::Vector<UEntry>::const_iterator insertion_locus;
            size_t suffix_index;
        } arr[64];
        std::remove_reference_t<decltype(*arr)>* e=arr;
        constexpr void push(const uint_least64_t ei_p,const yuki::Vector<UEntry>::const_iterator il_p,const size_t si_p) {*e={ei_p,il_p,si_p};++e;}
        constexpr auto pop() {return *--e;}
        constexpr bool empty() const {return e==arr;}
    } probe_stack;

    /// @pre `h_probe>=height_u`.
    /// @note `h_probe` is one tier higher than the actually probed tier, in case `height_u==0`.
    /// @return If `unionss[h_probe-1]` contains an entry corresponding to `n_probe`, its char class will be returned. Otherwise a new entry will be inserted with its char class calculated and returned. Note: `edge_views` will play the role as the nonexistent `unionss[-1]`.
    auto probe_cc = [height_u,total_edges](unsigned h_probe,uint_least64_t n_probe) -> const Char_Class& {
        assert(h_probe>=height_u);
        #ifndef NDEBUG
        const unsigned h_probe_orig = h_probe; // For assertion.
        #endif
        // Probe char class until the last calculated unions.
        yuki::Vector<UEntry>::const_iterator i_probe;
        while(h_probe>height_u){
            --h_probe;
            const yuki::Vector<UEntry>& unions = unionss[h_probe];
            i_probe = first_less_equiv(unions,n_probe);
            if(i_probe==unions.end() || i_probe->edge_indices<n_probe){
                const int zeros = std::countr_zero(n_probe);
                probe_stack.push(n_probe,i_probe,total_edges-1-zeros);
                n_probe -= 1ULL<<zeros; // compute the stem
            }else{
                ++h_probe;
                goto unwind_cc;
            }
        }
        // `n_probe` remains constant afterwards.
        // Find char class in the last calculated unions or the base, depending on whether the last calculated unions actually exists.
        if(height_u){
            // At this point, `h_probe` should be `height_u`.
            i_probe = find(unionss[height_u-1],n_probe);
            if(i_probe==unionss[height_u-1].end()){
                for(;!probe_stack.empty();++h_probe){
                    const auto top = probe_stack.pop();
                    i_probe = unionss[h_probe].emplace(top.insertion_locus,top.edge_indices,cc_all);
                }
                assert(h_probe==h_probe_orig);
                return i_probe->cc;
            }
        }else{
            // At this point, `h_probe` should be 0.
            assert(std::popcount(n_probe)==1);
            if(!probe_stack.empty()){
                const auto top = probe_stack.pop();
                i_probe = unionss[0].emplace(top.insertion_locus,top.edge_indices,*edge_views[suffix_index(total_edges,n_probe)].cc + *edge_views[top.suffix_index].cc);
                ++h_probe;
            }else
                return *edge_views[suffix_index(total_edges,n_probe)].cc;
        }
        // `n_probe` is useless afterwards.
        unwind_cc:
        // At this time, `i_probe` points to the successfully probed char class and `h_probe` (>=`height_u` && >=1) represents the tier into which a new entry is to be inserted, i.e. one tier higher than `i_probe`.
        for(;!probe_stack.empty();++h_probe){
            const auto top = probe_stack.pop();
            i_probe = unionss[h_probe].emplace(top.insertion_locus,top.edge_indices,i_probe->cc + *edge_views[top.suffix_index].cc);
        }
        assert(h_probe==h_probe_orig);
        return i_probe->cc;
    }; // probe_cc

    // Note: `total_edges-4-height_u` will not underflow due to precondition 1 `height_u<total_edges-3`.
    for(unsigned h=0;h<height_i && h<=total_edges-4-height_u;++h)
        unionss[total_edges-4-h].reserve(intersectionss[h].size());

    { // 1-subsets
    uint_least64_t stem=1;
    for(unsigned i=total_edges;i!=0;stem<<=1){
        --i;
        // The probing is much like `probe_cc`. There are 2 differences.
        // 1. Due to the "RLE(RGE) Theorem" (proved somewhere in this file), the searches and insertions are simply done at the vectors' ends.
        // 2. Because of precondition 1 `height_u<total_edges-3`, the first while loop must be entered at least once. Thus one `if` becomes unnecessary.
        unsigned h_probe = total_edges-3;
        uint_least64_t n_probe = stem!=1 ? full-stem-1 : full-stem-2;
        // Probe char class until the last calculated unions.
        while(h_probe>height_u){
            --h_probe;
            const yuki::Vector<UEntry>& unions = unionss[h_probe];
            assert(unions.empty() || unions.back().edge_indices>=n_probe);
            if(unions.empty() || unions.back().edge_indices>n_probe){
                const int zeros = std::countr_zero(n_probe);
                probe_stack.push(n_probe,yuki::Vector<UEntry>::const_iterator(),total_edges-1-zeros);
                n_probe -= 1ULL<<zeros; // compute the stem
            }else{
                ++h_probe;
                goto unwind_cc;
            }
        }
        // `n_probe` remains constant afterwards.
        // Find char class in the last calculated unions or the base, depending on whether the last calculated unions actually exists.
        if(height_u){
            // At this point, `h_probe` should be `height_u`.
            const yuki::Vector<UEntry>::const_iterator last_probed = find(unionss[height_u-1],n_probe);
            if(last_probed==unionss[height_u-1].end()){
                for(;!probe_stack.empty();++h_probe){
                    const auto top = probe_stack.pop();
                    unionss[h_probe].emplace_back(top.edge_indices,cc_all);
                }
                goto probe_done;
            }else if(!probe_stack.empty()){
                const auto top = probe_stack.pop();
                unionss[h_probe].emplace_back(top.edge_indices,last_probed->cc + *edge_views[top.suffix_index].cc);
                ++h_probe;
            }
        }else{
            // At this point, `h_probe` should be 0.
            assert(std::popcount(n_probe)==1);
            assert(!probe_stack.empty());
            const auto top = probe_stack.pop();
            unionss[0].emplace_back(top.edge_indices,*edge_views[suffix_index(total_edges,n_probe)].cc + *edge_views[top.suffix_index].cc);
            ++h_probe;
        }
        // `n_probe` is useless afterwards.
        unwind_cc:
        // At this time, `h_probe` (>=`height_u` && >=1) represents the tier into which a new entry is to be inserted, i.e. one tier higher than the successfully probed char class.
        for(;!probe_stack.empty();++h_probe){
            const auto top = probe_stack.pop();
            unionss[h_probe].emplace_back(top.edge_indices,unionss[h_probe-1].back().cc + *edge_views[top.suffix_index].cc);
        }
        probe_done:
        assert(h_probe==total_edges-3);
        const FSM_Edge_View edge_view = edge_views[i];
        cc_temp2 = unionss[total_edges-4].back().cc + *edge_views[stem!=1 ? total_edges-1 : total_edges-2].cc;
        cc_temp = *edge_view.cc - cc_temp2;
        if(!cc_temp.empty()){
            policy_edge_init(base_states[i],edge_view,fsms_size);
            transition_table.insert(std::move(cc_temp),insert_to_ss(base_states[i]));
        }
    } // for(unsigned i=total_edges;i!=0;stem<<=1)
    } // 1-subsets

    // The portion whose complementary unions were not calculated.

    // 2-subsets
    // Note: The condition should be `0<height_i && 0<=total_edges-4-height_u`, but because of precondition 1 `height_u<total_edges-3` it is simplified to `0<height_i`.
    if(0<height_i){
        yuki::Vector<UEntry>& complements = unionss[total_edges-4];
        const yuki::Vector<UEntry>::const_iterator complements_end = complements.cend();
        const yuki::Vector<IEntry>::iterator b = intersectionss[0].begin();
        yuki::Vector<IEntry>::iterator e = intersectionss[0].end();
        while(e!=b){
            --e;
            uint_least64_t n_first_probe = full-e->edge_indices;
            const yuki::Vector<UEntry>::iterator i_first_probe = find(complements,n_first_probe);
            if(i_first_probe!=complements_end){
                cc_temp = e->cc - i_first_probe->cc;
                i_first_probe->cc.reset();
            }else{
                const int zeros = std::countr_zero(n_first_probe);
                cc_temp2 = probe_cc(total_edges-4,n_first_probe-=1ULL<<zeros) + *edge_views[total_edges-1-zeros].cc;
                cc_temp = e->cc - cc_temp2;
            }
            e->cc.reset();

            State_Ex* const stem_base = e->stem_base;
            assert(stem_base);
            if(!stem_base->on)
                policy_edge_init(*stem_base,edge_views[suffix_index(total_edges,stem(e->edge_indices))],fsms_size);
            State_Ex* const state_ex = (e!=b && stem_base==(e-1)->stem_base) ? new State_Ex(*stem_base) : new State_Ex(std::move(*stem_base));
            policy_edge_insert(*state_ex,edge_views[suffix_index(total_edges,e->edge_indices)]);
            if(!cc_temp.empty())
                transition_table.insert(std::move(cc_temp),insert_to_ss(*state_ex));
            e->state_cached = state_ex;
        }
    }
    unionss[total_edges-4].clear();
    for(unsigned i=0;i<total_edges;++i)
        base_states[i].clear();

    unsigned h=1;

    // Note: `total_edges-4-height_u` will not underflow due to precondition 1 `height_u<total_edges-3`.
    for(;h<height_i && h<=total_edges-4-height_u;++h){
        yuki::Vector<UEntry>& complements = unionss[total_edges-4-h];
        const yuki::Vector<UEntry>::const_iterator complements_end = complements.cend();
        const yuki::Vector<IEntry>::iterator b = intersectionss[h].begin();
        yuki::Vector<IEntry>::iterator e = intersectionss[h].end();
        while(e!=b){
            --e;
            uint_least64_t n_first_probe = full-e->edge_indices;
            const yuki::Vector<UEntry>::iterator i_first_probe = find(complements,n_first_probe);
            if(i_first_probe!=complements_end){
                cc_temp = e->cc - i_first_probe->cc;
                i_first_probe->cc.reset();
            }else{
                const int zeros = std::countr_zero(n_first_probe);
                cc_temp2 = probe_cc(total_edges-4-h,n_first_probe-=1ULL<<zeros) + *edge_views[total_edges-1-zeros].cc;
                cc_temp = e->cc - cc_temp2;
            }
            e->cc.reset();

            State_Ex*& stem_state_cached = e->stem->state_cached;
            assert(stem_state_cached);
            const bool copy = (e!=b && e->stem==(e-1)->stem);
            State_Ex* const state_ex = copy ? new State_Ex(*stem_state_cached) : new State_Ex(std::move(*stem_state_cached));
            policy_edge_insert(*state_ex,edge_views[suffix_index(total_edges,e->edge_indices)]);
            if(!cc_temp.empty())
                transition_table.insert(std::move(cc_temp),insert_to_ss(*state_ex));
            e->state_cached = state_ex;
            if(!copy){
                delete stem_state_cached;
                stem_state_cached = nullptr;
            }
        }
        complements.clear();
        intersectionss[h-1].clear();
    }

    // The portion whose complementary unions have been calculated.
    for(;h<height_i;++h){
        yuki::Vector<UEntry>& complements = unionss[total_edges-4-h];
        const yuki::Vector<UEntry>::iterator complements_end = complements.end();
        yuki::Vector<IEntry>::iterator b = intersectionss[h].begin();
        yuki::Vector<IEntry>::iterator bb = b;
        const yuki::Vector<IEntry>::iterator e = intersectionss[h].end();
        for(;b!=e;++b){
            ++bb;
            const yuki::Vector<UEntry>::iterator complement = find(complements,full-b->edge_indices);
            if(complement!=complements_end){
                cc_temp = b->cc - (complement->cc);
                complement->cc.reset();
            }else
                cc_temp.clear();
            b->cc.reset();

            State_Ex*& stem_state_cached = b->stem->state_cached;
            assert(stem_state_cached);
            const bool copy = (bb!=e && b->stem==bb->stem);
            State_Ex* const state_ex = copy ? new State_Ex(*stem_state_cached) : new State_Ex(std::move(*stem_state_cached));
            policy_edge_insert(*state_ex,edge_views[suffix_index(total_edges,b->edge_indices)]);
            if(!cc_temp.empty())
                transition_table.insert(std::move(cc_temp),insert_to_ss(*state_ex));
            b->state_cached = state_ex;
            if(!copy){
                delete stem_state_cached;
                stem_state_cached = nullptr;
            }
        }
        complements.clear();
        intersectionss[h-1].clear();
    }

    intersectionss[h-1].clear();

    if(unused_complements_index>=unionss_last)
        for(int h=unionss_last;h<=unused_complements_index;++h)
            unionss[h].clear();

    // There is no need to calculate (n-1)-subsets and the n-subset due to precondition 0 `height_i<total_edges-2`.
} // policy_edge_i


/// @pre `height_i>=1 && height_u<height_i`
/// @pre also `height_u<total_edges-2`, but this is implied by `height_u<height_i` since `height_i<=total_edges-2`.
/// @pre `height_i<total_edges-2` i.e. `height_i` is a valid index of `intersectionss`.
template<yuki::Vector<IEntry>* intersectionss,yuki::Vector<UEntry>* unionss,State_Ex* base_states>
void policy_edge_u(const size_t fsms_size,const unsigned height_i,const unsigned height_u){
    const unsigned total_edges = edge_views.size();
    const uint_least64_t full = (1ULL<<total_edges)-1;

    assert(height_i>=1); // Precondition 0
    assert(height_u<height_i); // Precondition 1
    assert(height_i<total_edges-2); // Precondition 2
    // Also the implied precondition 2 : `height_u<total_edges-2`.
    YUKI_LEX_META_DBGO("S{} policy_edge_u\n",worklist.front()->mapped);

    intersectionss[height_i].clear(); // Valid due to Precondition 2.

    static struct{
        struct{
            uint_least64_t edge_indices;
            yuki::Vector<IEntry>::iterator insertion_locus;
            size_t suffix_index;
        } arr[64];
        std::remove_reference_t<decltype(*arr)>* e=arr;
        constexpr void push(const uint_least64_t ei_p,const yuki::Vector<IEntry>::iterator il_p,const size_t si_p) {*e={ei_p,il_p,si_p};++e;}
        constexpr auto pop() {return *--e;}
        constexpr bool empty() const {return e==arr;}
    } probe_stack;

    /// If `*i_probe` does not have a `State_Ex` cached, then calculates and caches it.
    /// @param h_probe height of `i_probe`
    auto probe_sc = [fsms_size,height_i,total_edges](unsigned h_probe,yuki::Vector<IEntry>::iterator i_probe){
        const unsigned h_probe_orig = h_probe;
        #ifndef NDEBUG
        const yuki::Vector<IEntry>::iterator i_probe_orig = i_probe;
        #endif
        // Probe `state_cached` until tier 0.
        for(;h_probe>0;i_probe=i_probe->stem,--h_probe){
            if(!i_probe->state_cached)
                probe_stack.push(0,i_probe,0);
            else
                goto unwind_state_cached;
        }
        // Initialize base state and tier 0.
        if(!i_probe->state_cached){
            State_Ex* const base_state = i_probe->stem_base;
            const int zeros = std::countr_zero(i_probe->edge_indices);
            if(!base_state->on)
                policy_edge_init(*base_state,edge_views[suffix_index(total_edges,i_probe->edge_indices-(1ULL<<zeros))],fsms_size);
            State_Ex* const state_ex_new = new State_Ex(*base_state);
            policy_edge_insert(*state_ex_new,edge_views[total_edges-1-zeros]);
            i_probe->state_cached = state_ex_new; // The only place where `*i_probe` is modified.
        }
        unwind_state_cached:
        for(;h_probe!=h_probe_orig;++h_probe){
            assert(i_probe->state_cached);
            const yuki::Vector<IEntry>::iterator ie_next = probe_stack.pop().insertion_locus; // Well, this is NOT insertion locus.
            State_Ex* const state_ex_new = new State_Ex(*i_probe->state_cached);
            policy_edge_insert(*state_ex_new,edge_views[suffix_index(total_edges,ie_next->edge_indices)]);
            ie_next->state_cached = state_ex_new;
            i_probe = ie_next;
        }
        assert(i_probe==i_probe_orig);
        assert(i_probe->state_cached);
    };

    // As of 1-subsets, their complements (`unionss[total_edges-3]`) should be empty because precondition 2 `height_u<total_edges-2`, i.e. `height_u<=total_edges-3`.

    unsigned h = height_u;
    // Note: `height_u` could possibly be 0, so the following 2 big loops are arranged in a special way.

    // The portion of unions whose complements have been fully calculated.
    // Note: `height_i-1` will not underflow due to precondition 0.
    while(h>total_edges-4-(height_i-1)){
        --h;
        const yuki::Vector<UEntry>& unions = unionss[h];
        yuki::Vector<IEntry>& intersections = intersectionss[total_edges-4-h]; // Note: this will not underflow because `h<height_u` and precondition 2 `height_u<total_edges-2`.
        yuki::Vector<UEntry>::const_iterator b = unions.begin();
        const yuki::Vector<UEntry>::const_iterator e = unions.end();
        for(;b!=e;++b){
            yuki::Vector<IEntry>::iterator i_probe = find(intersections,full-b->edge_indices);  // There is only one line where `*i_probe` is modified, i.e. when the probe of `state_cached` has reached tier 0.
            if(i_probe!=intersections.end()){
                probe_sc(total_edges-4-h,i_probe); // Note: this will not underflow because `h<height_u` and precondition 2 `height_u<total_edges-2`.
                cc_temp = i_probe->cc - b->cc;
                if(!cc_temp.empty())
                    transition_table.insert(std::move(cc_temp),insert_to_ss(*i_probe->state_cached));
            }
            b->~UEntry();
        }
        unionss[h].force_clear();
    }

    /// @return `const_iterator` pointing to the stem `IEntry`.
    auto probe_uc = [fsms_size,height_i,total_edges,probe_sc](unsigned h_probe,uint_least64_t n_probe) -> yuki::Vector<IEntry>::const_iterator {
        #ifndef NDEBUG
        const unsigned h_probe_orig = h_probe; // For assertion.
        const uint_least64_t n_probe_orig = n_probe; //  For assertion.
        #endif
        // Probe char class until the last calculated intersections.
        yuki::Vector<IEntry>::iterator i_probe; // There is only one line where `*i_probe` is modified, i.e. when the probe of `state_cached` has reached tier 0.
        for(;h_probe>=height_i;--h_probe){
            yuki::Vector<IEntry>& intersections = intersectionss[h_probe];
            i_probe = first_less_equiv(intersections,n_probe);
            if(i_probe==intersections.end() || i_probe->edge_indices<n_probe){
                const int zeros = std::countr_zero(n_probe);
                probe_stack.push(n_probe,i_probe,total_edges-1-zeros);
                n_probe -= 1ULL<<zeros; // compute the stem
            }else
                goto unwind_cc;
        }
        // `n_probe` remains constant afterwards.
        // Find char class in the last calculated intersections.
        // At this point, `h_probe` should be `height_i-1`.
        // Note: `height_i-1` will not overflow due to precondition 0.
        i_probe = first_less_equiv(intersectionss[height_i-1],n_probe);
        if(i_probe!=intersectionss[height_i-1].end() && i_probe->edge_indices==n_probe)
            probe_sc(h_probe,i_probe);
        else
            goto unwind_cc_simple;
        // `n_probe` is useless afterwards.
        unwind_cc:
        // At this time, `i_probe` points to the last probed `Char_Class` and `h_probe` represents its height (>=`height_i-1`).
        while(!probe_stack.empty() && !i_probe->cc.empty()){
            assert(i_probe->state_cached);
            const auto top = probe_stack.pop();
            const yuki::Vector<IEntry>::iterator inserted = intersectionss[++h_probe].emplace(top.insertion_locus,top.edge_indices,i_probe->cc * *edge_views[top.suffix_index].cc);
            if(!inserted->cc.empty()){
                State_Ex* const state_ex_new = new State_Ex(*i_probe->state_cached);
                policy_edge_insert(*state_ex_new,edge_views[top.suffix_index]);
                inserted->state_cached = state_ex_new;
            }
            i_probe=inserted;
        }
        unwind_cc_simple:
        // When an empty `Char_Class` is encountered.
        while(!probe_stack.empty()){
            const auto top = probe_stack.pop();
            i_probe = intersectionss[++h_probe].emplace(top.insertion_locus,top.edge_indices);
        }
        // Process the initial entry.
        assert(h_probe==h_probe_orig);
        assert(i_probe->edge_indices==n_probe_orig);
        return i_probe;
    }; // probe_uc

    // The portion of unions whose complements were not calculated.
    while(h){
        --h;
        intersectionss[total_edges-4-h].reserve(unionss[h].size()); // Note: this will not underflow because `h<height_u` and precondition 2 `height_u<total_edges-2`.
        const yuki::Vector<UEntry>::const_iterator b = unionss[h].begin();
        yuki::Vector<UEntry>::const_iterator e = unionss[h].end();
        while(e!=b){
            --e;
            const uint_least64_t complement = full-e->edge_indices;
            const int complement_zeros = std::countr_zero(complement);
            const yuki::Vector<IEntry>::const_iterator i_probe = probe_uc(total_edges-4-h-1,complement-(1ULL<<complement_zeros));
            //< Note: `total_edges-4-h-1` will not underflow. This is because the previous big while loop's condition is `h>total_edges-4-(height_i-1)`, so in order for THIS while loop to be entered, `total_edges-4-(height_i-1)` must `>0`. So if we can have `h<=height_i-1`, i.e. `h<height_i`, then we can have `total_edges-4-h>0`, i.e. `total_edges-4-h-1>=0`. Now `h<height_i` holds because `h<height_u` and precondition 1 `height_u<height_i`.
            intersectionss[total_edges-4-h].emplace_back(complement,i_probe->cc * *edge_views[total_edges-1-complement_zeros].cc);
            IEntry& inserted = intersectionss[total_edges-4-h].back();
            if(!inserted.cc.empty()){
                assert(i_probe->state_cached);
                State_Ex* const state_ex_new = new State_Ex(*i_probe->state_cached);
                policy_edge_insert(*state_ex_new,edge_views[total_edges-1-complement_zeros]);
                inserted.state_cached = state_ex_new;
                cc_temp = inserted.cc - e->cc;
                if(!cc_temp.empty())
                    transition_table.insert(std::move(cc_temp),insert_to_ss(*state_ex_new));
            }
            e->~UEntry();
        }
        unionss[h].force_clear();
    }

    // (n-1)-subsets as well as n-subset.
    uint_least64_t ei = 1;
    for(unsigned i=total_edges; i!=0; ei<<=1){
        --i;
        const uint_least64_t complement = full-ei;
        const int complement_zeros = std::countr_zero(complement);
        const yuki::Vector<IEntry>::const_iterator i_probe = probe_uc(total_edges-4,complement-(1ULL<<complement_zeros));
        cc_temp3 = i_probe->cc * *edge_views[total_edges-1-complement_zeros].cc;
        if(!cc_temp3.empty()){
            assert(i_probe->state_cached);
            cc_temp = cc_temp3 - *(edge_views[i].cc);
            if(!cc_temp.empty()){
                next = *i_probe->state_cached;
                policy_edge_insert(next,edge_views[total_edges-1-complement_zeros]);
                if(complement_zeros==1){ // Process the entire set.
                    cc_temp2 = cc_temp3 * *(edge_views[i].cc);
                    if(!cc_temp2.empty()){
                        next2=next;
                        policy_edge_insert_simple(next2,edge_views[total_edges-1]);
                        transition_table.insert(std::move(cc_temp2),insert_to_ss(std::move(next2)));
                    }
                }
                transition_table.insert(std::move(cc_temp),insert_to_ss(std::move(next)));
            }else if(complement_zeros==1){ // Process the entire set.
                cc_temp = cc_temp3 * *(edge_views[i].cc);
                if(!cc_temp.empty()){
                    next = *i_probe->state_cached;
                    policy_edge_insert(next,edge_views[total_edges-2]);
                    policy_edge_insert_simple(next,edge_views[total_edges-1]);
                    transition_table.insert(std::move(cc_temp),insert_to_ss(std::move(next)));
                }
            }
        }
    }

    for(unsigned i=0;i<total_edges-3;++i)
        intersectionss[i].clear();
    for(unsigned i=0;i<total_edges;++i)
        if(base_states[i].on)
            base_states[i].clear();
} // policy_edge_u


void policy_char(const size_t fsms_size){
    YUKI_LEX_META_DBGO("S{} policy_char\n",worklist.front()->mapped);

    const auto e = edge_views.cend();
    for(Char_Class::const_char_iterator i_c32=cc_union.begin_char();!i_c32.is_end();++i_c32){
        assert(next_always_resized.empty());

        const char32_t c32 = *i_c32;
        auto b=edge_views.cbegin();

        size_t last_branch_num = b->branch_num;
        auto i_indices = edge_views_branch_indices.cbegin()+1;

        while(b!=e){
            const FSM_Edge_View edge_view = *b;
            if(edge_view.branch_num!=last_branch_num){
                last_branch_num = edge_view.branch_num;
                assert(i_indices!=edge_views_branch_indices.cend());
                ++i_indices;
            }
            if(edge_view.cc->contains(c32)){
                switch(insert_node_to(next_always_resized,edge_view)){
                    case FSM_Node::Lazy::L:{
                        // goto the next branch
                        if(i_indices!=edge_views_branch_indices.cend()){
                            b = edge_views.begin() + *i_indices;
                            break;
                        }else
                            goto insert_transition;
                    }
                    case FSM_Node::Lazy::D: goto insert_transition;
                }
            }
            ++b;
        }
        insert_transition:
        transition_table.insert(c32,insert_next_ar_to_ss(fsms_size));
    }
}


template<const auto* meta_edges_by_char,yuki::Vector<size_t>& list>
void make_remove_list(){
    typedef decltype(meta_edges_by_char[0].positive.cbegin()) const_iterator;
    const_iterator is[12], es[12];

    assert(list.empty());

    for(unsigned i=0;i<6;++i){
        is[2*i] = meta_edges_by_char[i].positive.cbegin();
        es[2*i] = meta_edges_by_char[i].positive.cend();
        is[2*i+1] = meta_edges_by_char[i].negative.cbegin();
        es[2*i+1] = meta_edges_by_char[i].negative.cend();
    }

    const_iterator* i_min = nullptr;
    size_t current;
    bool current_set = false;

    while(1){
        current_set = false;
        for(unsigned i=0;i<12;++i){
            if(is[i]!=es[i] && (!current_set || is[i]->branch_num < current)){
                current_set = true;
                i_min = &(is[i]);
                current = (*i_min)->branch_num;
            }
        }

        if(!current_set)
            return;

        ++*i_min;

        if(list.empty() || list.back()<current)
            list.emplace_back(current);
    }
}
} // namespace yuki::lex

#include"cmd.hpp"
namespace yuki::lex{
void write_fsm_code(
    FILE* const out,
    const FSM* const fsms,
    const size_t fsms_size,
    const size_t max_branch_size,
    const size_t max_branch_number,
    unsigned& errors,
    const char* const fsm_name
    #ifdef YUKI_LEX_META_DBG
    ,Cmd_Data::Debug_Options debug_options
    #endif
){
    (void)max_branch_size;

    struct Meta_Edges_Pair{
        typedef yuki::Vector<Meta_Edge,yuki::Allocator<Meta_Edge>,yuki::Default_EC<>> vec_type;
        vec_type positive;
        vec_type negative;
        Meta_Edges_Pair(const size_t p_res,const size_t n_res) noexcept :
            positive(yuki::reserve_tag,p_res),
            negative(yuki::reserve_tag,n_res)
        {}
        Meta_Edges_Pair(const size_t p_res) noexcept :
            positive(yuki::reserve_tag,p_res),
            negative()
        {}
        vec_type& operator[](const bool neg) {return neg?negative:positive;}
        const vec_type& operator[](const bool neg) const {return neg?negative:positive;}
        bool empty() const {return positive.empty() && negative.empty();}
        void clear() {positive.clear();negative.clear();}
    };
    #ifndef YUKI_LEX_EDGES_RESERVE
    #define YUKI_LEX_EDGES_RESERVE {4,4}
    #endif
    static Meta_Edges_Pair meta_edges_by_char[6] = {YUKI_LEX_EDGES_RESERVE,YUKI_LEX_EDGES_RESERVE,YUKI_LEX_EDGES_RESERVE,YUKI_LEX_EDGES_RESERVE,YUKI_LEX_EDGES_RESERVE,YUKI_LEX_EDGES_RESERVE};

    next_always_resized.init(fsms,fsms_size);
    is_headed.emplace_back(next_always_resized.is_headed);
    state_set.emplace(std::move(next_always_resized.state));
    next_always_resized.state.resize_branch(fsms_size);
    next_always_resized.simple_clear();

    worklist.emplace_back(state_set.begin());

    #ifndef YUKI_LEX_BRANCHES_EXPECTED
    #define YUKI_LEX_BRANCHES_EXPECTED 64
    #endif
    static struct Accepted{
        char* data;
        size_t size;
        size_t cap;
        Accepted(const size_t c) noexcept :
            data(new char[c]),
            size(0),
            cap(c)
        {}
        ~Accepted() noexcept {delete[] data;}
        void resize(const size_t s){
            if(s>cap){
                delete[] data;
                data=new char[s];
                cap=s;
            }
            size=s;
            memset(data,0,s);
        }
    } accepted(YUKI_LEX_BRANCHES_EXPECTED);
    accepted.resize(fsms_size);

    while(!worklist.empty()){
        const State& current_state = worklist.front()->key;

        fprintf(out,HIND "S%zu:\n",worklist.front()->mapped);

        if(is_headed.front())
            fprintf(out,IND "pos_head=in.get_pos();\n");

        for(const size_t head : current_state.post_heads_imm())
            fprintf(out,IND "heads[HEAD_MAP[%zu]]=pos_head;\n",head);

        const FSM_Node* const current_accept = current_state.accept();
        if(current_accept){
            accepted.data[current_accept->branch]=1;
            if(current_accept->is_tail)
                fprintf(out,IND "cap=%zu; pos_take=heads[HEAD_MAP[%zu]];\n",current_accept->branch+1,current_accept->branch);
            else
                fprintf(out,IND "cap=%zu; pos_take=in.get_pos();\n",current_accept->branch+1);
        }

        size_t total_intervals = 0;
        bool edges_has_complete = false;

        {
        assert(edge_views.empty());
        assert(edge_views_branch_indices.empty());
        State::const_branch_iterator bb=current_state.begin_branch();
        const State::const_branch_iterator eb=current_state.end_branch();
        size_t current_branch_num = 0;
        for(; bb!=eb; ++bb,++current_branch_num){
            bool current_branch_indexed = false;
            for(const FSM_Node* const n : *bb){
                const bool is_head = n->is_head;
                const auto& edges = n->edges.normal_edges();
                const auto meta_edge = n->edges.meta;
                if(!edges.empty()){
                    if(!current_branch_indexed){
                        current_branch_indexed = true;
                        edge_views_branch_indices.emplace_back(edge_views.size());
                    }
                    for(const FSM_Edge& e : edges){
                        edges_has_complete |= e.cc.is_complete();
                        edge_views.emplace_back(current_branch_num,is_head,&e.cc,e.node);
                        total_intervals += e.cc.size();
                    }
                }
                if(meta_edge.target){
                    if(meta_edge.c>0)
                        meta_edges_by_char[meta_edge.c-1].positive.emplace_back(current_branch_num,is_head,meta_edge.target);
                    else
                        meta_edges_by_char[-meta_edge.c-1].negative.emplace_back(current_branch_num,is_head,meta_edge.target);
                }
            }
        }
        }

        { // write meta transitions.
        // The processing of meta transitions is like `policy_char`. A character in this context is a conjunction of a lexer's internal states, encoded here as an at-most-6-bits unsigned integer. A meta character in this context now becomes a character class, containing all conjunctions where the corresponding bit is on.

        unsigned meta_actives = 0;
        unsigned to_true_index[6] = {};
        for(unsigned i=0;i<6;++i)
            if(!meta_edges_by_char[i].empty())
                to_true_index[meta_actives++] = i;

        if(meta_actives!=0){
            edge_views.clear();
            edge_views_branch_indices.clear();

            static State_Ex state0;
            assert(state0.post_heads.empty() && state0.lazy==FSM_Node::Lazy::N && state0.last_branch_num==0);
            state0.state = current_state;
            state0.is_headed = is_headed.front();

            #ifndef YUKI_LEX_REMOVE_RESERVE
            #define YUKI_LEX_REMOVE_RESERVE 16
            #endif
            static yuki::Vector<size_t> remove_list(yuki::reserve_tag,YUKI_LEX_REMOVE_RESERVE);
            make_remove_list<meta_edges_by_char,remove_list>();
            while(!remove_list.empty())
                state0.remove_branch(remove_list.pop_back_v());

            switch(meta_actives){
                case 1:{
                    fprintf(out,IND "if(");
                    switch(to_true_index[0]+1){
                        case MetaChar::BOL: fprintf(out,"in.at_bol()");break;
                        case MetaChar::EOL: fprintf(out,"in.at_eol()");break;
                        case MetaChar::BOI: fprintf(out,"in.at_boi()");break;
                        case MetaChar::EOI: fprintf(out,"in.at_eoi()");break;
                        case MetaChar::EoF: fprintf(out,"!in.getable()");break;
                        case MetaChar::WB: fprintf(out,"in.at_wb()");break;
                    }
                    fprintf(out,")");

                    next=state0;

                    for(const Meta_Edge me : meta_edges_by_char[to_true_index[0]].positive){
                        if(policy_edge_insert_meta(state0,me))
                            break;
                    }
                    if(!state0.post_heads.empty()){
                        fprintf(out,"{\n");
                        for(const size_t h : state0.post_heads)
                            fprintf(out,IND2 "heads[HEAD_MAP[%zu]]=pos_head;\n",h);
                        state0.post_heads.clear();
                        fprintf(out,IND2 "goto S%zu;\n",insert_to_ss(std::move(state0)).first);
                    }else
                        fprintf(out," goto S%zu;\n",insert_to_ss(std::move(state0)).first);

                    meta_edges_by_char[to_true_index[0]].positive.clear();

                    fprintf(out,IND "else");

                    for(const Meta_Edge me : meta_edges_by_char[to_true_index[0]].negative){
                        if(policy_edge_insert_meta(next,me))
                            break;
                    }
                    if(!next.post_heads.empty()){
                        fprintf(out,"{\n");
                        for(const size_t h : next.post_heads)
                            fprintf(out,IND2 "heads[HEAD_MAP[%zu]]=pos_head;\n",h);
                        next.post_heads.clear();
                        fprintf(out,IND2 "goto S%zu;\n" IND "}\n",insert_to_ss(std::move(next)).first);
                    }else
                        fprintf(out," goto S%zu;\n",insert_to_ss(std::move(next)).first);

                    meta_edges_by_char[to_true_index[0]].negative.clear();
                    break;
                } // case 1
                default:{
                    fprintf(out,IND "switch(yuki::lex::make_meta_flags({");
                    for(unsigned i=meta_actives;i>0;){
                        switch(to_true_index[--i]+1){
                            case MetaChar::BOL: fprintf(out,"in.at_bol(),");break;
                            case MetaChar::EOL: fprintf(out,"in.at_eol(),");break;
                            case MetaChar::BOI: fprintf(out,"in.at_boi(),");break;
                            case MetaChar::EOI: fprintf(out,"in.at_eoi(),");break;
                            case MetaChar::EoF: fprintf(out,"!in.getable(),");break;
                            case MetaChar::WB: fprintf(out,"in.at_wb(),");break;
                        }
                    }
                    fprintf(out,"})){\n");
                    const unsigned flags_end = 1U<<meta_actives;
                    for(unsigned flags=0;flags<flags_end;++flags){
                        next = state0;
                        for(unsigned flags_working=flags,i=0;i<meta_actives;++i,flags_working>>=1){
                            const auto& meta_edges = flags_working&1U ? meta_edges_by_char[to_true_index[i]].positive : meta_edges_by_char[to_true_index[i]].negative;
                            for(const Meta_Edge me : meta_edges)
                                if(policy_edge_insert_meta(next,me))
                                    goto write_meta_transition;
                        }
                        write_meta_transition:
                        if(!next.post_heads.empty()){
                            fprintf(out,IND2 "case %u:{\n",flags);
                            for(const size_t h : next.post_heads)
                                fprintf(out,IND2 IND "heads[HEAD_MAP[%zu]]=pos_head;\n",h);
                            next.post_heads.clear();
                            fprintf(out,IND2 IND "goto S%zu;\n" IND2 "}\n",insert_to_ss(std::move(next)).first);
                        }else
                            fprintf(out,IND2 "case %u: goto S%zu;\n",flags,insert_to_ss(std::move(next)).first);
                    }
                    fprintf(out,IND "}\n");
                    for(unsigned i=0;i<6;++i)
                        meta_edges_by_char[i].clear();
                    state0.post_heads.clear();
                    state0.simple_clear();
                    break;
                } // default
            } // switch(meta_actives)
            worklist.pop_front();
            is_headed.pop_front();
            continue;
        } // if(meta_actives!=0)
        } // write meta transitions.

        switch(edge_views.size()){
            case 0: YUKI_LEX_META_DBGO("S{} policy_edge_0\n",worklist.front()->mapped);break;
            case 1:{
                YUKI_LEX_META_DBGO("S{} policy_edge_1\n",worklist.front()->mapped);
                assert(next_always_resized.empty());
                const FSM_Edge_View edge_view = edge_views.front();
                insert_node_to(next_always_resized,edge_view);
                transition_table.insert(*edge_view.cc,insert_next_ar_to_ss(fsms_size));
                edge_views.clear();
                edge_views_branch_indices.clear();
                break;
            }
            case 2:{
                YUKI_LEX_META_DBGO("S{} policy_edge_2\n",worklist.front()->mapped);
                const FSM_Edge_View edge_view0 = edge_views[0];
                const FSM_Edge_View edge_view1 = edge_views[1];
                Char_Class cc = (*edge_view0.cc) - (*edge_view1.cc);
                if(!cc.empty()){
                    assert(next_always_resized.empty());
                    insert_node_to(next_always_resized,edge_view0);
                    transition_table.insert(std::move(cc),insert_next_ar_to_ss(fsms_size));
                }
                cc = (*edge_view1.cc) - (*edge_view0.cc);
                if(!cc.empty()){
                    assert(next_always_resized.empty());
                    insert_node_to(next_always_resized,edge_view1);
                    transition_table.insert(std::move(cc),insert_next_ar_to_ss(fsms_size));
                }
                cc = (*edge_view0.cc) * (*edge_view1.cc);
                if(!cc.empty()){
                    assert(next_always_resized.empty());
                    switch(insert_node_to(next_always_resized,edge_view0)){
                        case FSM_Node::Lazy::N:
                            insert_node_to(next_always_resized,edge_view1);break;
                        case FSM_Node::Lazy::L:{
                            if(edge_view1.branch_num!=edge_view0.branch_num)
                                insert_node_to(next_always_resized,edge_view1);
                        }
                    }
                    transition_table.insert(std::move(cc),insert_next_ar_to_ss(fsms_size));
                }
                edge_views.clear();
                edge_views_branch_indices.clear();
                break;
            }
            #ifndef YUKI_LEX_META_DBG
            case 3: policy_edge_3(fsms_size);edge_views.clear();edge_views_branch_indices.clear();break;
            #endif
            default:{
                #ifdef YUKI_LEX_META_DBG
                if(edge_views.size()==3 && !debug_options.policy_char){
                    policy_edge_3(fsms_size);
                    edge_views.clear();
                    edge_views_branch_indices.clear();
                    break;
                }
                #endif
                if(edges_has_complete)
                    cc_union.make_complete();
                else{
                    struct const_cc_iterator{
                        decltype(edge_views.cbegin()) i;
                        const_cc_iterator& operator++() {++i;return *this;}
                        const Char_Class* operator->() const {return i->cc;}
                        const Char_Class& operator*() const {return *(i->cc);}
                    };
                    cc_union.merge_cc(const_cc_iterator{edge_views.cbegin()},edge_views.size());
                }

                #ifndef YUKI_LEX_POLICY_CHAR_MAX_CHAR_COUNT
                #define YUKI_LEX_POLICY_CHAR_MAX_CHAR_COUNT 1024
                #endif

                #ifndef YUKI_LEX_META_DBG
                if(cc_union.char_count()<=YUKI_LEX_POLICY_CHAR_MAX_CHAR_COUNT || edge_views.size()>64 || !policy_edge(fsms_size))
                #else
                const size_t total_chars = cc_union.char_count();
                YUKI_LEX_META_DBGO("S{} edges {} chars {}\n",worklist.front()->mapped,edge_views.size(),total_chars);
                if(debug_options.policy_char || total_chars<=YUKI_LEX_POLICY_CHAR_MAX_CHAR_COUNT || edge_views.size()>64 || !policy_edge(fsms_size,debug_options.simple_accumulate))
                #endif
                    policy_char(fsms_size);

                edge_views.clear();
                edge_views_branch_indices.clear();
            }
        }

        if(!transition_table.empty()){
            fprintf(out,IND "c=in.get();\n");
            transition_table.write(out);
            transition_table.clear();
        }

        fprintf(out,IND "in.set_pos(pos_take); return cap;\n");

        worklist.pop_front();
        is_headed.pop_front();
    } // while(!worklist.empty())

    for(size_t i=0;i<accepted.size;++i){
        if(accepted.data[i]==0){
            fprintf(stderr,"Error: Branch %zu in fsm %s cannot be accepted! (Note: Try moving it up.)\n",i,fsm_name);
            ++errors;
        }
    }

    state_set.clear();
    worklist.clear(); // Should already be clear. Just reset the pointer positions.
    is_headed.clear(); // Should already be clear. Just reset the pointer positions.
} // write
} // namespace yuki::lex
