#pragma once
#include<yuki/Ordered_Vector.hpp>
#include<yuki/unicode.hpp>

namespace yuki::lex{

struct Char_Interval{
    char32_t lb;
    char32_t ub;

    friend constexpr bool operator==(Char_Interval,Char_Interval) noexcept = default;

    constexpr bool empty() const {return lb>ub;}

    constexpr bool contains(const char32_t c) const {return c>=lb && c<=ub;}

    constexpr size_t size() const {return ub-lb+1;}

    struct Less;
};

struct Char_Interval::Less{
    static constexpr bool compare(const Char_Interval lhs, const Char_Interval rhs) noexcept {return lhs.lb<rhs.lb;}

    static constexpr Less select_on_container_copy_construction(Less) {return {};}
};


struct Char_Class : private yuki::Ordered_Vector<Char_Interval,Char_Interval::Less> {
  private:
    typedef yuki::Ordered_Vector<Char_Interval,Char_Interval::Less> OV_;
  public:
    constexpr Char_Class() noexcept = default;

    Char_Class(yuki::reserve_tag_t,const size_type count) noexcept :
        OV_(yuki::reserve_tag,count)
    {}

    template<typename It>
    Char_Class(yuki::from_ordered_tag_t,const It it,const size_type count) noexcept :
        OV_(yuki::from_ordered_tag,it,count)
    {}

    Char_Class(yuki::from_ordered_tag_t,std::initializer_list<Char_Interval> il) noexcept :
        OV_(yuki::from_ordered_tag,il.begin(),il.size())
    {}

    Char_Class(const Char_Interval ci) noexcept :
        OV_(1,ci)
    {}

    Char_Class& operator=(const Char_Interval ci) noexcept {
        clear();
        recapacity(1);
        emplace_back(ci);
        return *this;
    }

    Char_Class& assign(yuki::from_ordered_tag_t,std::initializer_list<Char_Interval> il){
        clear();
        recapacity(il.size());
        Vec_Base::insert(end(),il.begin(),il.size());
        return *this;
    }

    friend void swap(Char_Class& lhs,Char_Class& rhs) noexcept {swap(static_cast<OV_&>(lhs),static_cast<OV_&>(rhs));}

    using OV_::clear;
    using OV_::reset;
    using OV_::empty;
    using OV_::size;
    using OV_::capacity;

    /// For debugging.
    Char_Interval operator[](const size_t i) const {return OV_::operator[](i);}

    using OV_::const_iterator;
    const_iterator begin() const {return OV_::begin();}
    const_iterator end() const {return OV_::end();}

    size_t char_count() const {
        size_t c = 0;
        const OV_::const_iterator e = OV_::end();
        for(OV_::const_iterator b = OV_::begin();b!=e;++b)
            c += b->size();
        return c;
    }

    bool is_complete() const {return OV_::size()==1 && OV_::front()==Char_Interval{0,yuki::UNICODE_MAX_32};}

    void make_complete() {clear();OV_::emplace_back(0,yuki::UNICODE_MAX_32);}

    const_iterator find(char32_t c) const {
        const_iterator fg = OV_::first_greater({c,c});
        if(fg!=begin()){
            if((--fg)->ub >= c) // i.e. last_less_equiv
                return fg;
        }
        return end();
    }

    bool contains(char32_t c) const {
        const_iterator fg = OV_::first_greater({c,c});
        if(fg!=begin())
            return (--fg)->ub >= c; // i.e. last_less_equiv
        return false;
    }

    void insert(const char32_t c){
        const OV_::Vec_Base::iterator b = OV_::Vec_Base::begin();
        using yuki::const_kast;
        const OV_::Vec_Base::iterator fg = const_kast(OV_::first_greater({c,c}));

        if(fg==b){
            if(b!=end() && b->lb==c+1)
                --b->lb;
            else
                OV_::Vec_Base::emplace(b,c,c);
        }else{
            const iterator prev = fg-1;
            if(prev->ub<c){
                unsigned flag=0;
                if(prev->ub+1==c)
                    flag |= 0b10U;
                if(fg!=end() && fg->lb==c+1)
                    flag |= 1U;
                switch(flag){
                    case 0: OV_::Vec_Base::emplace(fg,c,c);break;
                    case 1: --fg->lb;break;
                    case 2: ++prev->ub;break;
                    case 3: OV_::erase_then_emplace(prev,2,Char_Interval{prev->lb,fg->ub});break;
                }
            }
        }
    }

    void insert(const Char_Interval ci){
        assert(!ci.empty());

        if(ci.lb==ci.ub)
            return insert(ci.lb);

        const const_iterator b=begin(), e=end();
        const const_iterator left_fg = OV_::first_greater({ci.lb,ci.lb});
        const const_iterator right_fg = OV_::first_greater({ci.ub,ci.ub});

        const_iterator left=e, right=e;

        if(left_fg!=b && (left_fg-1)->ub >= ci.lb)
            left = left_fg-1;

        if(right_fg!=b && (right_fg-1)->ub >= ci.ub)
            right = right_fg-1;

        Char_Interval ci_new = ci;

        if(left!=e){
            if(right!=e){ // 1
                if(left!=right)
                    ci_new={left->lb,right->ub}, ++right;
                else // Same as the previous branch, actually.
                    return;
            }else{ // 2
                ci_new={left->lb,ci.ub}, right=right_fg;
                if(right!=e){
                    if(ci_new.ub+1==right->lb)
                        ci_new.ub=right->ub, ++right;
                }
            }
        }else{
            if(right!=e){ // 3 (2 with left and right reversed)
                ci_new={ci.lb,right->ub}, left=left_fg, ++right;
                if(left!=b){
                    if((left-1)->ub+1 == ci_new.lb)
                        --left, ci_new.lb=left->lb;
                }
            }else{ // 4
                left=left_fg, right=right_fg;
                if(right!=e){
                    if(ci_new.ub+1==right->lb)
                        ci_new.ub=right->ub, ++right;
                }
                if(left!=b){
                    if((left-1)->ub+1 == ci_new.lb)
                        --left, ci_new.lb=left->lb;
                }
            }
        }
        OV_::erase_then_emplace(left,right-left,ci_new);
    } // void insert(const Char_Interval ci)

    friend Char_Class operator*(const Char_Class&,const Char_Class&);
    friend Char_Class operator+(const Char_Class&,const Char_Class&);
    friend Char_Class operator!(const Char_Class&);
    friend Char_Class operator-(const Char_Class&,const Char_Class&);

    template<typename It>
    void merge_cc(It it,const size_t count);

    struct const_char_iterator{
        friend Char_Class;
      private:
        char32_t c;
        Char_Interval ci;
        const_iterator i;
        const_iterator i_end;

        const_char_iterator(const const_iterator ip,const const_iterator iep) noexcept :
            i(ip),i_end(iep)
        {
            if(i!=i_end){
                ci=*i;
                c=ci.lb;
            }
        }
      public:
        const_char_iterator() noexcept = default;

        char32_t operator*() const {return c;}

        bool is_end() const {return i==i_end;}

        const_char_iterator& operator++(){
            ++c;
            if(c>ci.ub){
                ++i;
                if(i!=i_end){
                    ci=*i;
                    c=ci.lb;
                }
            }
            return *this;
        }
    }; // struct const_char_iterator

    const_char_iterator begin_char() const {return {begin(),end()};}
}; // struct Char_Class

// A*(B0+...+Bm) = (A*B0)+...+(A*Bm)
inline Char_Class operator*(const Char_Class& lhs_p,const Char_Class& rhs_p){
    typedef Char_Class::Vec_Base::iterator iterator;
    typedef Char_Class::const_iterator const_iterator;

    const Char_Class* lhs = &lhs_p;
    const Char_Class* rhs = &rhs_p;
    if(lhs_p.size()<rhs_p.size())
        lhs=&rhs_p, rhs=&lhs_p;

    if(rhs->empty())
        return {};

    auto append_back = [](Char_Class& cc_p,const const_iterator l,const const_iterator r) -> iterator {
        const Char_Class::size_type s = r-l;
        assert(cc_p.capacity()>=cc_p.size()+s);
        const iterator e = cc_p.Vec_Base::end();
        yuki::uninitialized_copy_no_overlap(e,l,s);
        cc_p.force_resize(cc_p.size()+s);
        return e;
    };

    Char_Class cc(yuki::reserve_tag, lhs->size() + rhs->size() - 1);

    for(const Char_Interval ci : *rhs){
        const const_iterator b = lhs->begin();
        const const_iterator e = lhs->end();
        const const_iterator left_fg = lhs->OV_::first_greater({ci.lb,ci.lb});
        const const_iterator right_fg = lhs->OV_::first_greater({ci.ub,ci.ub});

        const_iterator left = e;
        const_iterator right = e;

        if(left_fg!=b && (left_fg-1)->ub >= ci.lb)
            left = left_fg-1;

        if(right_fg!=b && (right_fg-1)->ub >= ci.ub)
            right = right_fg-1;

        // `left==e` iff. everything in `lhs` is greater than `ci.lb`, or the previous interval of `left_fg` does not contain `ci.lb`.
        // Otherwise `left` denotes the interval that contains `ci.lb`.
        // Ditto for `right`.

        if(left!=e){
            if(right!=e){ // 1
                if(left==right){
                    assert(cc.size()!=cc.capacity());
                    cc.emplace_back(ci);
                }else{ // Same as the previous branch, actually.
                    ++right;
                    append_back(cc,left,right) -> lb = ci.lb;
                    cc.Vec_Base::back().ub = ci.ub;
                }
            }else{ // 2
                right = right_fg;
                append_back(cc,left,right) -> lb = ci.lb;
            }
        }else{
            if(right!=e){ // 3 (2 with left and right reversed)
                left=left_fg, ++right;
                append_back(cc,left,right);
                cc.Vec_Base::back().ub = ci.ub;
            }else{ // 4
                left=left_fg, right=right_fg;
                if(left!=right){ // Same without this `if`, actually. `append_back` will do nothing if `left==right`.
                    append_back(cc,left,right);
                }
                // else do nothing
            }
        }
    } // for(const Char_Interval ci : *rhs)
    return cc;
} // Char_Class operator*(const Char_Class& lhs_p,const Char_Class& rhs_p)

inline Char_Class operator+(const Char_Class& lhs,const Char_Class& rhs){
    typedef Char_Class::const_iterator const_iterator;

    Char_Class cc(yuki::reserve_tag,lhs.size()+rhs.size());

    const_iterator l = lhs.begin();
    const_iterator r = rhs.begin();
    const const_iterator le = lhs.end();
    const const_iterator re = rhs.end();

    Char_Interval ci;

    while(1){
        if(l==le){
            if(r==re)
                return cc;
            else
               ci = *r++;
        }else{
            if(r==re)
                ci = *l++;
            else{
                if(r->lb < l->lb)
                    ci = *r++;
                else
                    ci = *l++;
            }
        }

        if(!cc.empty()){
            Char_Interval& cib = cc.Vec_Base::back();
            if(ci.ub>cib.ub){
                if(ci.lb<=cib.ub+1)
                    cib.ub=ci.ub;
                else
                    cc.emplace_back(ci);
            }
        }else
            cc.emplace_back(ci);
    }
} // Char_Class operator+(const Char_Class& lhs,const Char_Class& rhs)

template<typename It>
void Char_Class::merge_cc(It it,const size_t count){
    #ifndef YUKI_LEX_MERGE_CC_RESERVE
    #define YUKI_LEX_MERGE_CC_RESERVE 64
    #endif
    static yuki::Vector<const_iterator> is(yuki::reserve_tag,YUKI_LEX_MERGE_CC_RESERVE),es(yuki::reserve_tag,YUKI_LEX_MERGE_CC_RESERVE);

    clear();
    is.clear();
    es.clear();

    for(size_t i=0;i<count;++i,++it){
        is.emplace_back(it->begin());
        es.emplace_back(it->end());
    }

    const_iterator* i_min = nullptr;
    Char_Interval ci;
    bool ci_set = false;

    while(!is_complete()){
        ci_set = false;
        for(size_t i=0;i<count;++i){
            if(is[i]!=es[i] && (!ci_set || is[i]->lb < ci.lb)){
                ci_set = true;
                i_min = &(is[i]);
                ci = **i_min;
            }
        }

        if(!ci_set)
            return;

        ++*i_min;

        if(!empty()){
            Char_Interval& cib = OV_::Vec_Base::back();
            if(ci.ub>cib.ub){
                if(ci.lb<=cib.ub+1)
                    cib.ub=ci.ub;
                else
                    OV_::Vec_Base::emplace_back(ci);
            }
        }else
            OV_::Vec_Base::emplace_back(ci);
    }
} // void Char_Class::merge_cc(It it,const size_t count)

inline Char_Class operator!(const Char_Class& ccp){
    if(ccp.empty()) // This is necessary, not just an optimization.
        return Char_Class(Char_Interval{0,yuki::UNICODE_MAX_32});

    typedef Char_Class::const_iterator const_iterator;

    Char_Class cc(yuki::reserve_tag,ccp.size()+1);

    const_iterator i1 = ccp.begin();
    const_iterator i2 = i1+1;
    const const_iterator e = ccp.end();

    if(i1->lb!=0)
        cc.emplace_back(Char_Interval{0,(i1->lb)-1});

    for(;i2!=e;++i1,++i2)
        cc.emplace_back(Char_Interval{i1->ub+1,i2->lb-1});

    if(i1->ub!=yuki::UNICODE_MAX_32)
        cc.emplace_back(Char_Interval{(i1->ub)+1,yuki::UNICODE_MAX_32});
    return cc;
}

// (A0+...+An)-B = (A0-B)+...+(An-B)
inline Char_Class operator-(const Char_Class& lhs,const Char_Class& rhs){
    typedef Char_Class::const_iterator const_iterator;

    Char_Class cc(yuki::reserve_tag,lhs.size()+rhs.size());

    for(const Char_Interval ci : lhs){
        const const_iterator b = rhs.begin();
        const const_iterator e = rhs.end();
        const const_iterator left_fg = rhs.OV_::first_greater({ci.lb,ci.lb});
        const const_iterator right_fg = rhs.OV_::first_greater({ci.ub,ci.ub});

        const_iterator left = e;
        const_iterator right = e;

        if(left_fg!=b && (left_fg-1)->ub >= ci.lb)
            left = left_fg-1;

        if(right_fg!=b && (right_fg-1)->ub >= ci.ub)
            right = right_fg-1;

        // `left==e` iff. everything in `lhs` is greater than `ci.lb`, or the previous interval of `left_fg` does not contain `ci.lb`.
        // Otherwise `left` denotes the interval that contains `ci.lb`.
        // Ditto for `right`.

        if(left!=e){
            if(right!=e){ // 1
                assert(cc.capacity()>=cc.size()+(right-left));
                for(const_iterator i=left+1; left!=right; ++left,++i)
                    cc.emplace_back(Char_Interval{left->ub+1,i->lb-1});
            }else{ // 2
                right = right_fg;
                assert(cc.capacity()>=cc.size()+(right-left));
                for(const_iterator i=left+1; left!=right; ++left,++i)
                    cc.emplace_back(Char_Interval{left->ub+1,i->lb-1});
                cc.Vec_Base::back().ub = ci.ub;
            }
        }else{
            if(right!=e){ // 3 (2 with left and right reversed)
                left=left_fg;
                assert(cc.capacity()>=cc.size()+(right-left+1));
                cc.emplace_back(Char_Interval{ci.lb,left->lb-1});
                for(const_iterator i=left+1; left!=right; ++left,++i)
                    cc.emplace_back(Char_Interval{left->ub+1,i->lb-1});
            }else{ // 4
                left=left_fg, right=right_fg;
                assert(cc.capacity()>=cc.size()+(right-left+1));
                if(left!=right){
                    cc.emplace_back(Char_Interval{ci.lb,left->lb-1});
                    for(const_iterator i=left+1; left!=right; ++left,++i)
                        cc.emplace_back(Char_Interval{left->ub+1,i->lb-1});
                    cc.Vec_Base::back().ub = ci.ub;
                }else
                    cc.emplace_back(ci);
            }
        }
    } // for(const Char_Interval ci : lhs)
    return cc;
} // Char_Class operator-(const Char_Class& lhs,const Char_Class& rhs)


inline const Char_Class cc_dot{yuki::from_ordered_tag,{{0,U'\n'-1},{U'\n'+1,U'\r'-1},{U'\r'+1,0x10FFFF}}};
inline const Char_Class cc_dot_ascii{yuki::from_ordered_tag,{{0,U'\n'-1},{U'\n'+1,U'\r'-1},{U'\r'+1,127}}};
inline const Char_Class cc_dot_byte{yuki::from_ordered_tag,{{0,U'\n'-1},{U'\n'+1,U'\r'-1},{U'\r'+1,255}}};
inline const Char_Class cc_all = Char_Interval{0,0x10FFFF};
inline const Char_Class cc_all_byte = Char_Interval{0,255};
inline const Char_Class cc_newline{yuki::from_ordered_tag,{{U'\n',U'\n'},{U'\r',U'\r'}}};
// POSIX catetories
inline const Char_Class cc_ascii = Char_Interval{0,127};
inline const Char_Class cc_space{yuki::from_ordered_tag,{{U'\t',U'\r'},{U' ',U' '}}};
inline const Char_Class cc_xdigit{yuki::from_ordered_tag,{{U'0',U'9'},{U'A',U'F'},{U'a',U'f'}}};
inline const Char_Class cc_cntrl{yuki::from_ordered_tag,{{0,0x1F},{127,127}}};
inline const Char_Class cc_print = Char_Interval{0x20,0x7E};
inline const Char_Class cc_alnum{yuki::from_ordered_tag,{{U'0',U'9'},{U'A',U'Z'},{U'a',U'z'}}};
inline const Char_Class cc_alpha{yuki::from_ordered_tag,{{U'A',U'Z'},{U'a',U'z'}}};
inline const Char_Class cc_blank{yuki::from_ordered_tag,{{U'\t',U'\t'},{U' ',U' '}}};
inline const Char_Class cc_digit = Char_Interval{U'0',U'9'};
inline const Char_Class cc_graph = Char_Interval{0x21,0x7E};
inline const Char_Class cc_lower = Char_Interval{U'a',U'z'};
inline const Char_Class cc_punct{yuki::from_ordered_tag,{{0x21,0x2F},{0x3A,0x40},{0x5B,0x60},{0x7B,0x7E}}};
inline const Char_Class cc_upper = Char_Interval{U'A',U'Z'};
inline const Char_Class cc_word{yuki::from_ordered_tag,{{U'0',U'9'},{U'A',U'Z'},{U'_',U'_'},{U'a',U'z'}}};
// One unicode category
inline const Char_Class cc_uspace{yuki::from_ordered_tag,{{U'\t',U'\r'},{U' ',U' '},{0x85,0x85},{0xA0,0xA0},{0x1680,0x1680},{0x2000,0x200A},{0x2028,0x2029},{0x202F,0x202F},{0x205F,0x205F},{0x3000,0x3000}}};
} // namespace yuki::lex

#ifdef YUKI_LEX_META_DBG
#include<cstdio>
namespace yuki::lex{
inline void print_cc(FILE* const out,const Char_Class& cc){
    for(const Char_Interval ci : cc)
        fprintf(out,"[%zx,%zx] ",(size_t)ci.lb,(size_t)ci.ub);
}
}
#endif