#pragma once

namespace yuki::lex{

template<typename T,size_t DEFAULT_BLOCK_SIZE_P = 64>
struct Node_Pool{
    [[nodiscard]]
    T* allocate() noexcept {
        if(current==nullptr || next==DEFAULT_BLOCK_SIZE_P){
            Node* block = yuki::Allocator<Node>::allocate();
            ::new(block) Node{yuki::Allocator<T>::allocate(DEFAULT_BLOCK_SIZE_P),nullptr};
            if(head==nullptr)
                head = block;
            else
                current->next_node  = block;
            current = block;
            next = 1;
            return block->data;
        }else
            return (current->data)+(next+=1);
    }

    bool empty() const noexcept {return head==nullptr;}
    size_t free_in_current_block() const noexcept {return DEFAULT_BLOCK_SIZE_P-next;}

    void clear() noexcept {
        if(head!=nullptr){
            Node* const current_orig = current;
            yuki::destroy(current->data,next);
            yuki::Allocator<T>::deallocate(current->data);
            yuki::Allocator<Node>::deallocate(current);
            next = 0;
            while(head!=current_orig){
                current = head->next_node;
                yuki::destroy(current->data,DEFAULT_BLOCK_SIZE_P);
                yuki::Allocator<T>::deallocate(head->data);
                yuki::Allocator<Node>::deallocate(head);
                head = current;
            }
            head=current=nullptr;
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
    friend bool operator==(const Node_Pool& lhs,const Node_Pool& rhs) noexcept
        {return lhs.head==rhs.head;}
  private:
    struct Node{
        T* data;
        Node* next_node = nullptr;
    };
    Node* head = nullptr; // 1
    Node* current = nullptr; // 2
    size_t next = 0; // 3
}; // struct Node_Pool<T,s>
} // namespace yuki::lex




#include<yuki/map_ov.hpp>
#include"char_class.hpp"

namespace yuki::lex{

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
    yuki::Vector<FSM_Edge,yuki::Allocator<FSM_Edge>,yuki::Default_EC<2,1,1>> vec_;
  public:
    yuki::Vector<const FSM_Node*,yuki::Allocator<const FSM_Node*>,yuki::Default_EC<2,1,1>> epsilons;
    const FSM_Node* epsilon_back = nullptr; // Unlike normal epsilons, there can be at most only 1 epsilon_back.
    struct {char32_t c; const FSM_Node* node;} meta = {0,nullptr};

    constexpr FSM_Edges() noexcept = default;

    FSM_Edges(const FSM_Edges&) noexcept = default;

    FSM_Edges(FSM_Edges&& other) noexcept :
        vec_(std::move(other.vec_)),
        epsilons(std::move(other.epsilons)),
        epsilon_back(other.epsilon_back),
        meta{other.meta}
    {
        other.epsilon_back = nullptr;
        other.meta = {0,nullptr};
    }

    FSM_Edges& operator=(const FSM_Edges&) noexcept = default;

    FSM_Edges& operator=(FSM_Edges&& other) noexcept {
        if(this!=&other){
            vec_ = std::move(other.vec_);
            epsilons = std::move(other.epsilons);
            epsilon_back = other.epsilon_back;
            other.epsilon_back = nullptr;
            meta = other.meta;
            other.meta = {0,nullptr};
        }
        return *this;
    }

    FSM_Edges(Char_Class&& cc,const FSM_Node* n) noexcept {vec_.emplace_back(std::move(cc),n);}

    void emplace(Char_Class&& cc,const FSM_Node* n) {vec_.emplace_back(std::move(cc),n);}

    void merge(FSM_Edges&& other){
        for(FSM_Edge& e : other.vec_)
            vec_.emplace_back(std::move(e)), e.~FSM_Edge();
        other.vec_.deallocate();
        epsilons.insert(epsilons.end(),other.epsilons.begin(),other.epsilons.size());
        other.epsilons.reset();
        if(!epsilon_back)
            epsilon_back = other.epsilon_back;
        other.epsilon_back = nullptr;
        meta = other.meta;
        other.meta = {0,nullptr};
    }

    Char_Class cc_sum() const {
        struct cc_const_iterator{
            yuki::Vector<FSM_Edge>::const_iterator i;
            cc_const_iterator& operator++() {++i; return *this;}
            const Char_Class& operator*() const {return i->cc;}
            const Char_Class* operator->() const {
                static_assert(std::is_standard_layout_v<FSM_Edge>); //TODO replace with `std::is_pointer_interconvertible_with_class`, which is currently unavailable.
                return reinterpret_cast<const Char_Class*>(i);
            }
        };
        return merge_cc(cc_const_iterator{vec_.begin()},vec_.size());
    }

    struct const_at_iterator{
        friend FSM_Edges;
      private:
        yuki::Vector<FSM_Edge>::const_iterator i;
        yuki::Vector<FSM_Edge>::const_iterator e;
        char32_t c;

        const_at_iterator(yuki::Vector<FSM_Edge>::const_iterator ip,yuki::Vector<FSM_Edge>::const_iterator ep,char32_t cp) noexcept :
            i(ip),e(ep),c(cp)
        {
            while(i!=e && !(i->cc.contains(c)))
                ++i;
        }
      public:
        bool is_end() const {return i==e;}
        const FSM_Node* operator*() const {return i->node;}
        const_at_iterator& operator++(){
            do{
                ++i;
            }while(i!=e && !(i->cc.contains(c)));
            return *this;
        }
    };

    const_at_iterator begin(char32_t c) const {return const_at_iterator(vec_.begin(),vec_.end(),c);}
}; // struct FSM_Edges

struct FSM_Node{
    size_t route;
    size_t number;
    FSM_Edges edges;
    bool is_head = false;
    bool is_tail = false;
    enum struct Lazy : unsigned char {N=0,L,D} is_lazy = Lazy::N;
    bool is_accept = false;

    // There are 6 kinds of accepts. Let "T" denote `is_tail`, "L" or "D" denote `is_lazy`, and "A" denote `is_accept`, we have "DTA", "DA", "LTA", "LA", "TA", and simple "A".
    // (Note: THIS FSM construction algorithm will never produce a node that is both an accept and a head.)
    // The non-accepts will have the latter 3 flags all false, with "H" being either true or false. So in total there are only 8 meaningful combinations of the flags.
    enum struct Kind : unsigned {DTA,DA,LTA,LA,TA,A,  H,N}; // Do not change the order!!

    struct Less_By_Number{
        static bool compare(const FSM_Node* lhs,const FSM_Node* rhs) {return lhs->number < rhs->number;}
    };
};

struct FSM{
    FSM_Node* start;
    FSM_Node* accept;
    size_t size;

    FSM& concat(Char_Class&& cc,FSM_Node* n){
        accept->edges.emplace(std::move(cc),n);
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

    FSM& make_lazy() {accept->is_lazy = FSM_Node::Lazy::L; accept->is_accept = true; return *this;}
    FSM& make_dlazy() {accept->is_lazy = FSM_Node::Lazy::D; accept->is_accept = true; return *this;}
};

template<typename A = Node_Pool<FSM_Node,64>>
struct FSM_Factory : private A{
  private:
    size_t num_next=0;
    ///< The number is so arranged that `fsm.accept->number` is always the biggest among the entire fsm.
  public:
    void reset_number() {num_next=0;}

    template<typename... Args>
    FSM_Node* make_node(size_t route,Args&&... args){
        FSM_Node* n = A::allocate();
        ::new(n) FSM_Node{route,num_next++,std::forward<Args>(args)...};
        return n;
    }

    template<typename... CC_Args>
    FSM make_fsm(size_t route,CC_Args&&... cc_args){
        FSM_Node* start = A::allocate();
        FSM_Node* accept = A::allocate();
        ::new(start) FSM_Node{route,num_next++,{{std::forward<CC_Args>(cc_args)...},accept}};
        ::new(accept) FSM_Node{route,num_next++};
        return {start,accept,2};
    }

    /// @pre 'lhs' and 'rhs' should not intersect.
    FSM make_seq(FSM lhs,FSM rhs){
        // Discards `rhs.start`.
        lhs.accept->is_head = rhs.start->is_head;
        lhs.accept->edges.merge(std::move(rhs.start->edges));
        return {lhs.start,rhs.accept,lhs.size+rhs.size-1};
    }

    /// @pre 'lhs' and 'rhs' should not intersect.
    FSM make_alt(size_t route,FSM lhs,FSM rhs){
        // Discards `rhs.start`.
        lhs.start->edges.merge(std::move(rhs.start->edges));
        FSM_Node* accept_new = A::allocate();
        ::new(accept_new) FSM_Node{route,num_next++};
        lhs.accept->edges.epsilons.emplace_back(accept_new);
        rhs.accept->edges.epsilons.emplace_back(accept_new);
        return {lhs.start,accept_new,lhs.size+rhs.size};
    }

    FSM make_ast(size_t route,FSM fsm){
        FSM_Node* start_new = A::allocate();
        ::new(start_new) FSM_Node{route,fsm.accept->number};
        fsm.accept->number=num_next++;
        start_new->edges.epsilons.emplace_back(fsm.accept);
        assert(!(fsm.accept->edges.epsilon_back));
        fsm.accept->edges.epsilon_back=fsm.start;
        return {start_new,fsm.accept,fsm.size+1};
    }

    FSM make_plus(size_t route,FSM fsm){
        FSM_Node* start_new = A::allocate();
        ::new(start_new) FSM_Node{route,fsm.accept->number};
        fsm.accept->number=num_next++;
        start_new->edges.epsilons.emplace_back(fsm.start);
        assert(!(fsm.accept->edges.epsilon_back));
        fsm.accept->edges.epsilon_back=fsm.start;
        return {start_new,fsm.accept,fsm.size+1};
    }

    FSM make_qmark(size_t route,FSM fsm){
        fsm.start->edges.epsilons.emplace_back(fsm.accept);
        return fsm;
    }
}; // struct FSM_Factory<A>

} // namespace yuki::lex