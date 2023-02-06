#pragma once
#include<yuki/Allocator.hpp>

namespace yuki::lex{

template<typename T,size_t DEFAULT_BLOCK_SIZE_P>
struct Node_Pool{
    [[nodiscard]]
    T* allocate(){
        if(current==nullptr){
            allocate_new_block:
            Node* const block = yuki::Allocator<Node>::allocate();
            block->next_node = nullptr;
            if(head==nullptr)
                head = block;
            else
                current->next_node = block;
            current=block;
            next=1;
            return std::launder(reinterpret_cast<T*>(block->data));
        }else if(next==DEFAULT_BLOCK_SIZE_P){
            if(!current->next_node)
                goto allocate_new_block;
            else{
                current = current->next_node;
                next=1;
                return std::launder(reinterpret_cast<T*>(current->data));
            }
        }else
            return std::launder(reinterpret_cast<T*>((current->data)+(next++)));
    }

    void clear(){
        if(head!=nullptr){
            for(;head!=current;head=head->next_node){
                yuki::destroy(std::launder(reinterpret_cast<T*>(head->data)),DEFAULT_BLOCK_SIZE_P);
                yuki::Allocator<Node>::deallocate(head);
            }
            Node* next_node = current->next_node;
            yuki::destroy(std::launder(reinterpret_cast<T*>(current->data)),next);
            yuki::Allocator<Node>::deallocate(current);
            next=0;
            head=current=nullptr;
            while(next_node){
                Node* const nnext_node = next_node->next_node;
                yuki::Allocator<Node>::deallocate(next_node);
                next_node=nnext_node;
            }
        }
    }

    void recycle(){
        if(head!=nullptr){
            for(Node* n=head;n!=current;n=n->next_node)
                yuki::destroy(std::launder(reinterpret_cast<T*>(n->data)),DEFAULT_BLOCK_SIZE_P);
            yuki::destroy(std::launder(reinterpret_cast<T*>(current->data)),next);
            next=0;
            current=head;
        }
    }

    ~Node_Pool() noexcept {clear();}

    Node_Pool() noexcept = default;
    Node_Pool(const Node_Pool&) = delete;
    Node_Pool(Node_Pool&& other) noexcept :
        head(other.head),
        current(other.current),
        next(other.next)
    {
        other.head = nullptr;
        other.current = nullptr;
        other.next = 0;
    }
    Node_Pool& operator=(const Node_Pool&) = delete;
    Node_Pool& operator=(Node_Pool&& other) noexcept {
        if(this!=&other){
            clear();
            head = other.head;
            current = other.current;
            next = other.next;
            other.head = nullptr;
            other.current = nullptr;
            other.next = 0;
        }
    }
    friend void swap(Node_Pool& lhs,Node_Pool& rhs) noexcept {
        using std::swap;
        swap(lhs.head,rhs.head);
        swap(lhs.current,rhs.current);
        swap(lhs.next,rhs.next);
    }
  private:
    struct Node{
        struct{alignas(alignof(T)) unsigned char data[sizeof(T)];} data[DEFAULT_BLOCK_SIZE_P];
        Node* next_node = nullptr;
    };
    Node* head = nullptr;
    Node* current = nullptr;
    size_t next = 0;
}; // struct Node_Pool<T,s>
} // namespace yuki::lex




#include<yuki/Map_OV.hpp>
#include"Char_Class.hpp"

namespace yuki::lex{

namespace MetaChar{enum : int {BOL=1,EOL,BOI,EOI,EoF,WB,};}

struct Amount{
    size_t lb;
    size_t ub;
    enum : unsigned {NIL,AST,PLUS,QMARK} special = NIL;
};

struct FSM_Node;

struct FSM_Edge{
    Char_Class cc;
    const FSM_Node* node;
};

struct FSM_Edges{
  private:
    typedef yuki::Vector<FSM_Edge,yuki::Allocator<FSM_Edge>,yuki::Default_EC<2,1,1>> vec_type;
    vec_type vec_;
  public:
    yuki::Vector<const FSM_Node*,yuki::Allocator<const FSM_Node*>,yuki::Default_EC<2,1,1>> epsilons;
    const FSM_Node* epsilon_back = nullptr; // Unlike normal epsilons, there can be at most only 1 epsilon_back.
    struct{
        int c;
        const FSM_Node* target;
        void clear(){
            c=0;
            target=nullptr;
        }
    } meta = {0,nullptr};

    constexpr FSM_Edges() noexcept = default;

    FSM_Edges(const FSM_Edges&) noexcept = default;

    FSM_Edges(FSM_Edges&& other) noexcept :
        vec_(std::move(other.vec_)),
        epsilons(std::move(other.epsilons)),
        epsilon_back(other.epsilon_back),
        meta{other.meta}
    {
        other.epsilon_back = nullptr;
        other.meta.clear();
    }

    FSM_Edges& operator=(const FSM_Edges&) noexcept = default;

    FSM_Edges& operator=(FSM_Edges&& other) noexcept {
        if(this!=&other){
            vec_ = std::move(other.vec_);
            epsilons = std::move(other.epsilons);
            epsilon_back = other.epsilon_back;
            other.epsilon_back = nullptr;
            meta = other.meta;
            other.meta.clear();
        }
        return *this;
    }

    FSM_Edges(Char_Class&& cc,const FSM_Node* const n) noexcept {vec_.emplace_back(std::move(cc),n);}
    FSM_Edges(const int mc,const FSM_Node* const n) noexcept : meta{mc,n} {}

    const vec_type& normal_edges() const {return vec_;}

    void emplace(Char_Class&& cc,const FSM_Node* const n) {vec_.emplace_back(std::move(cc),n);}

    /// @pre `*this` and `other` cannot both have an epsilon_back edge at the same time.
    /// @pre `*this` and `other` cannot both have a meta edge at the same time.
    void merge(FSM_Edges&& other){
        for(FSM_Edge& e : other.vec_)
            vec_.emplace_back(std::move(e)), e.~FSM_Edge();
        other.vec_.deallocate();
        epsilons.insert(epsilons.end(),other.epsilons.begin(),other.epsilons.size());
        other.epsilons.reset();
        assert(!(epsilon_back && other.epsilon_back));
        if(!epsilon_back)
            epsilon_back = other.epsilon_back;
        other.epsilon_back = nullptr;
        assert(!(meta.target && other.meta.target));
        meta = other.meta;
        other.meta.clear();
    }
}; // struct FSM_Edges

struct FSM_Node{
    size_t branch;
    size_t number;
    FSM_Edges edges;
    bool is_head = false;
    bool is_tail = false;
    enum struct Lazy : unsigned char {N=0,L,D} lazy = Lazy::N;
    bool is_accept = false;

    // There are 6 kinds of accepts. Let "T" denote `is_tail`, "L" or "D" denote `lazy`, and "A" denote `is_accept`, we have "DTA", "DA", "LTA", "LA", "TA", and simple "A".
    // (Note: THIS FSM construction algorithm will never produce a node that is both an accept and a head.)
    // The non-accepts will have the latter 3 flags all false, with "H" being either true or false. So in total there are only 8 meaningful combinations of the flags.
    enum struct Kind : unsigned {DTA,DA,LTA,LA,TA,A,  H,N}; // Do not change the order!!

    struct Less_By_Number{
        static bool compare(const FSM_Node* const lhs,const FSM_Node* const rhs) {return lhs->number < rhs->number;}
    };
};

struct FSM{
    FSM_Node* start;
    FSM_Node* accept;
    size_t size;

    FSM& concat(Char_Class&& cc,FSM_Node* const n){
        accept->edges.emplace(std::move(cc),n);
        accept = n;
        ++size;
        return *this;
    }

    FSM& concat(const int mc,FSM_Node* const n){
        accept->edges.meta = {mc,n};
        accept = n;
        ++size;
        return *this;
    }

    FSM& make_head(){
        start->is_head = true;
        accept->is_tail = true;
        accept->is_accept = true;
        return *this;
    }

    FSM& make_accept() {accept->is_accept = true; return *this;}

    FSM& make_lazy() {accept->lazy = FSM_Node::Lazy::L; accept->is_accept = true; return *this;}
    FSM& make_dlazy() {accept->lazy = FSM_Node::Lazy::D; accept->is_accept = true; return *this;}
};

template<typename A>
struct FSM_Factory : private A{
  private:
    size_t num_next=0;
    ///< The number is so arranged that `fsm.accept->number` is always the biggest among the entire fsm.
  public:
    void reset_number() {num_next=0;}
    void recycle() {A::recycle();num_next=0;}

    template<typename... Args>
    FSM_Node* make_node(const size_t branch,Args&&... args){
        FSM_Node* const n = A::allocate();
        ::new(n) FSM_Node{branch,num_next++,std::forward<Args>(args)...};
        return n;
    }

    template<typename... CC_Args,typename=std::enable_if_t<std::is_constructible_v<Char_Class,CC_Args&&...>>>
    FSM make_fsm(const size_t branch,CC_Args&&... cc_args){
        FSM_Node* const start = A::allocate();
        FSM_Node* const accept = A::allocate();
        ::new(start) FSM_Node{branch,num_next++,{{std::forward<CC_Args>(cc_args)...},accept}};
        ::new(accept) FSM_Node{branch,num_next++};
        return {start,accept,2};
    }

    FSM make_fsm(const size_t branch,const int mc){
        FSM_Node* const start = A::allocate();
        FSM_Node* const accept = A::allocate();
        ::new(start) FSM_Node{branch,num_next++,{mc,accept}};
        ::new(accept) FSM_Node{branch,num_next++};
        return {start,accept,2};
    }

    /// @pre 'lhs' and 'rhs' should not intersect.
    FSM make_seq(const FSM lhs,const FSM rhs){
        // Discards `rhs.start`.
        lhs.accept->is_head = rhs.start->is_head;
        lhs.accept->edges.merge(std::move(rhs.start->edges));
        return {lhs.start,rhs.accept,lhs.size+rhs.size-1};
    }

    /// @pre 'lhs' and 'rhs' should not intersect.
    FSM make_alt(const size_t branch,const FSM lhs,const FSM rhs){
        // Discards `rhs.start`.
        lhs.start->edges.merge(std::move(rhs.start->edges));
        FSM_Node* const accept_new = A::allocate();
        ::new(accept_new) FSM_Node{branch,num_next++};
        lhs.accept->edges.epsilons.emplace_back(accept_new);
        rhs.accept->edges.epsilons.emplace_back(accept_new);
        return {lhs.start,accept_new,lhs.size+rhs.size};
    }

    /// @pre The `fsms` should not intersect.
    FSM make_alt(const size_t branch,FSM* fsms,size_t fsms_size){
        FSM_Node* const accept_new = A::allocate();
        ::new(accept_new) FSM_Node{branch,num_next++};
        // Except for the first fsm all other fsms' `.start` will be discarded.
        fsms->accept->edges.epsilons.emplace_back(accept_new);
        FSM_Node* const start = fsms->start;
        size_t total = fsms->size;
        assert(fsms_size>1);
        --fsms_size; ++fsms;
        for(;fsms_size;--fsms_size,++fsms){
            start->edges.merge(std::move(fsms->start->edges));
            fsms->accept->edges.epsilons.emplace_back(accept_new);
            total += fsms->size;
        }
        return {start,accept_new,total};
    }

    // number change: 0->1  -->  1->0->2
    FSM make_ast(const size_t branch,const FSM fsm){
        FSM_Node* const start_new = A::allocate();
        ::new(start_new) FSM_Node{branch,fsm.accept->number};
        fsm.accept->number=num_next++;
        start_new->edges.epsilons.emplace_back(fsm.accept); // The only difference with `make_plus`.
        assert(!(fsm.accept->edges.epsilon_back));
        fsm.accept->edges.epsilon_back=fsm.start;
        return {start_new,fsm.accept,fsm.size+1};
    }

    // number change: 0->1  -->  1->0->2
    FSM make_plus(const size_t branch,const FSM fsm){
        FSM_Node* const start_new = A::allocate();
        ::new(start_new) FSM_Node{branch,fsm.accept->number};
        fsm.accept->number=num_next++;
        start_new->edges.epsilons.emplace_back(fsm.start); // The only difference with `make_ast`.
        assert(!(fsm.accept->edges.epsilon_back));
        fsm.accept->edges.epsilon_back=fsm.start;
        return {start_new,fsm.accept,fsm.size+1};
    }

    FSM make_qmark(const size_t branch,const FSM fsm){
        fsm.start->edges.epsilons.emplace_back(fsm.accept);
        return fsm;
    }

    FSM make_amount(const size_t branch,const FSM fsm,const Amount amount){
        (void)branch;(void)amount;
        return fsm;
    }

    /// \r?\n
    FSM make_esc_N(const size_t branch){
        FSM fsm = make_fsm(branch,Char_Class({U'\r',U'\r'}));
        fsm = make_qmark(branch,fsm);
        return fsm.concat(Char_Class({U'\n',U'\n'}),make_node(branch));
    }
}; // struct FSM_Factory<A>

} // namespace yuki::lex

// Notable properties of THIS FSM construction algorithm:
// 1. No 2 non-epsilon edges point to a same node.
