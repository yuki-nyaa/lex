#pragma once
#include<yuki/ordered_vector.hpp>
#include<yuki/unicode.hpp>

namespace yuki::lex{

namespace MetaChar{
    enum : char32_t {
        BEGIN_ = yuki::EOF_32,
        EPSILON,
    };
}

struct Char_Interval{
    char32_t lb;
    char32_t ub;

    friend constexpr bool operator==(Char_Interval,Char_Interval) noexcept = default;

    constexpr bool empty() const {return lb>ub;}

    constexpr bool contains(char32_t c) const {return c>=lb && c<=ub;}

    struct Less;
};

struct Char_Interval::Less{
    static constexpr bool compare(Char_Interval lhs, Char_Interval rhs) noexcept {return lhs.lb<rhs.lb;}

    static constexpr Less select_on_container_copy_construction(Less) {return {};}
};


struct Char_Class : private yuki::Ordered_Vector<Char_Interval,Char_Interval::Less> {
  private:
    typedef yuki::Ordered_Vector<Char_Interval,Char_Interval::Less> OV_;
  public:
    constexpr Char_Class() noexcept = default;

    Char_Class(yuki::reserve_tag_t,size_type count) noexcept :
        OV_(yuki::reserve_tag,count)
    {}

    template<typename It>
    Char_Class(yuki::from_ordered_tag_t,It it,size_type count) noexcept :
        OV_(yuki::from_ordered_tag,it,count)
    {}

    Char_Class(yuki::from_ordered_tag_t,std::initializer_list<Char_Interval> il) noexcept :
        OV_(yuki::from_ordered_tag,il.begin(),il.size())
    {}

    Char_Class(Char_Interval ci) noexcept :
        OV_(1,ci)
    {}

    Char_Class& operator=(Char_Interval ci) noexcept {
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

    using OV_::front;
    using OV_::back;
    using OV_::operator[];

    typedef OV_::const_iterator const_interval_iterator;
    const_interval_iterator begin_interval() const {return OV_::begin();}
    const_interval_iterator end_interval() const {return OV_::end();}

    using OV_::first_equiv_greater;
    using OV_::first_greater;
    using OV_::last_smaller;
    using OV_::last_smaller_equiv;
    using OV_::contains;

    const_interval_iterator find(char32_t c) const {
        const_interval_iterator fg = first_greater({c,c});
        if(fg!=begin_interval()){
            if((--fg)->ub >= c) // i.e. last_smaller_equiv
                return fg;
        }
        return end_interval();
    }

    bool contains(char32_t c) const {
        const_interval_iterator fg = first_greater({c,c});
        if(fg!=begin_interval())
            return (--fg)->ub >= c; // i.e. last_smaller_equiv
        return false;
    }

    //void insert(const char32_t c){
    //    const const_interval_iterator b = begin_interval();
    //    const const_interval_iterator e = end_interval();
    //    const const_interval_iterator fg = first_greater({c,c});
    //    const const_interval_iterator prev = (fg!=b && (fg-1)->ub >= c) ? fg-1 : e;

    //}

    void insert(const Char_Interval ci){
        assert(!ci.empty());

        //if(ci.lb==ci.ub)
        //    return insert(ci.lb);

        const const_interval_iterator b = begin_interval();
        const const_interval_iterator e = end_interval();
        const const_interval_iterator left_fg = first_greater({ci.lb,ci.lb});
        const const_interval_iterator right_fg = first_greater({ci.ub,ci.ub});

        const_interval_iterator left = e;
        const_interval_iterator right = e;

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
    friend Char_Class merge_cc(It it,size_t count);

    struct const_iterator{
        friend Char_Class;
      private:
        char32_t c;
        Char_Interval ci;
        const_interval_iterator i;
        const_interval_iterator i_end;

        constexpr const_iterator(const_interval_iterator ip,const_interval_iterator iep) noexcept :
            i(ip),i_end(iep)
        {
            if(i!=i_end){
                ci=*i;
                c=ci.lb;
            }
        }
      public:
        constexpr const_iterator() noexcept = default;

        char32_t operator*() const {return c;}

        constexpr bool is_end() const {return i==i_end;}

        const_iterator& operator++(){
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
    }; // struct const_iterator

    const_iterator begin() const {return {begin_interval(),end_interval()};}
}; // struct Char_Class

inline Char_Class operator*(const Char_Class& lhs_p,const Char_Class& rhs_p){
    typedef Char_Class::Vec_Base::iterator interval_iterator;
    typedef Char_Class::const_interval_iterator const_interval_iterator;

    const Char_Class* lhs = &lhs_p;
    const Char_Class* rhs = &rhs_p;
    if(lhs_p.size()<rhs_p.size())
        lhs=&rhs_p, rhs=&lhs_p;

    if(rhs->empty())
        return {};

    auto append_back = [](Char_Class& cc_p,const_interval_iterator l,const_interval_iterator r) -> interval_iterator {
        Char_Class::size_type s = r-l;
        assert(cc_p.capacity()>=cc_p.size()+s);
        interval_iterator e = cc_p.Vec_Base::end();
        yuki::uninitialized_copy_no_overlap(e,l,s);
        cc_p.force_resize(cc_p.size()+s);
        return e;
    };

    Char_Class cc(yuki::reserve_tag, lhs->size() + rhs->size() - 1);

    {
    Char_Class::const_interval_iterator ii=rhs->begin_interval();
    Char_Class::const_interval_iterator iie=rhs->end_interval();
    for(;ii!=iie;++ii){
        const Char_Interval ci = *ii;
        const const_interval_iterator b = lhs->begin_interval();
        const const_interval_iterator e = lhs->end_interval();
        const const_interval_iterator left_fg = lhs->first_greater({ci.lb,ci.lb});
        const const_interval_iterator right_fg = lhs->first_greater({ci.ub,ci.ub});

        const_interval_iterator left = e;
        const_interval_iterator right = e;

        if(left_fg!=b && (left_fg-1)->ub >= ci.lb)
            left = left_fg-1;

        if(right_fg!=b && (right_fg-1)->ub >= ci.ub)
            right = right_fg-1;

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
    } // for(;ii!=iie;++ii)
    }
    return cc;
} // Char_Class operator*(const Char_Class& lhs_p,const Char_Class& rhs_p)

inline Char_Class operator+(const Char_Class& lhs,const Char_Class& rhs){
    typedef Char_Class::const_interval_iterator const_interval_iterator;

    Char_Class cc(yuki::reserve_tag,lhs.size()+rhs.size());

    const_interval_iterator l = lhs.begin_interval();
    const_interval_iterator r = rhs.begin_interval();
    const const_interval_iterator le = lhs.end_interval();
    const const_interval_iterator re = rhs.end_interval();

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
Char_Class merge_cc(It it,const size_t count){
    typedef Char_Class::const_interval_iterator const_interval_iterator;

    size_t total=0;
    static yuki::Vector<const_interval_iterator> is(yuki::reserve_tag,32),es(yuki::reserve_tag,32);
    is.reserve(count);
    es.reserve(count);

    {
    It it2 = it;
    for(size_t i=0;i<count;++i,++it2){
        total+=(it2->size());
        is.emplace_back(it2->begin_interval());
        es.emplace_back(it2->end_interval());
    }
    }

    Char_Class cc(yuki::reserve_tag,total);

    const_interval_iterator* i_min;
    Char_Interval ci;
    bool ci_set = false;

    while(1){
        ci_set = false;
        for(size_t i=0;i<count;++i){
            if(is[i]!=es[i] && (!ci_set || is[i]->lb < ci.lb)){
                ci_set = true;
                i_min = &(is[i]);
                ci = **i_min;
            }
        }

        if(!ci_set){
            is.clear();
            es.clear();
            return cc;
        }

        ++*i_min;

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
} // Char_Class merge_cc(It it,const size_t count)

inline Char_Class operator!(const Char_Class& ccp){
    if(ccp.empty())
        return Char_Class(Char_Interval{0,yuki::UNICODE_MAX_32});

    typedef Char_Class::const_interval_iterator const_interval_iterator;

    Char_Class cc(yuki::reserve_tag,ccp.size()+1);

    const_interval_iterator i1 = ccp.begin_interval();
    const_interval_iterator i2 = i1+1;
    const const_interval_iterator e = ccp.end_interval();

    if(i1->lb!=0)
        cc.emplace_back(Char_Interval{0,(i1->lb)-1});

    for(;i2!=e;++i1,++i2)
        cc.emplace_back(Char_Interval{i1->ub+1,i2->lb-1});

    if(i1->ub!=yuki::UNICODE_MAX_32)
        cc.emplace_back(Char_Interval{(i1->ub)+1,yuki::UNICODE_MAX_32});
    return cc;
}

inline Char_Class operator-(const Char_Class& lhs,const Char_Class& rhs){
    typedef Char_Class::const_interval_iterator const_interval_iterator;

    Char_Class cc(yuki::reserve_tag,lhs.size()+rhs.size());

    {
    Char_Class::const_interval_iterator ii=lhs.begin_interval();
    Char_Class::const_interval_iterator iie=lhs.end_interval();
    for(;ii!=iie;++ii){
        const Char_Interval ci=*ii;
        const const_interval_iterator b = rhs.begin_interval();
        const const_interval_iterator e = rhs.end_interval();
        const const_interval_iterator left_fg = rhs.first_greater({ci.lb,ci.lb});
        const const_interval_iterator right_fg = rhs.first_greater({ci.ub,ci.ub});

        const_interval_iterator left = e;
        const_interval_iterator right = e;

        if(left_fg!=b && (left_fg-1)->ub >= ci.lb)
            left = left_fg-1;

        if(right_fg!=b && (right_fg-1)->ub >= ci.ub)
            right = right_fg-1;

        if(left!=e){
            if(right!=e){ // 1
                assert(cc.capacity()>=cc.size()+(right-left));
                for(const_interval_iterator i=left+1; left!=right; ++left,++i)
                    cc.emplace_back(Char_Interval{left->ub+1,i->lb-1});
            }else{ // 2
                right = right_fg;
                assert(cc.capacity()>=cc.size()+(right-left));
                for(const_interval_iterator i=left+1; left!=right; ++left,++i)
                    cc.emplace_back(Char_Interval{left->ub+1,i->lb-1});
                cc.Vec_Base::back().ub = ci.ub;
            }
        }else{
            if(right!=e){ // 3 (2 with left and right reversed)
                left=left_fg;
                assert(cc.capacity()>=cc.size()+(right-left+1));
                cc.emplace_back(Char_Interval{ci.lb,left->lb-1});
                for(const_interval_iterator i=left+1; left!=right; ++left,++i)
                    cc.emplace_back(Char_Interval{left->ub+1,i->lb-1});
            }else{ // 4
                left=left_fg, right=right_fg;
                if(left!=right){
                    assert(cc.capacity()>=cc.size()+(right-left+1));
                    cc.emplace_back(Char_Interval{ci.lb,left->lb-1});
                    for(const_interval_iterator i=left+1; left!=right; ++left,++i)
                        cc.emplace_back(Char_Interval{left->ub+1,i->lb-1});
                    cc.Vec_Base::back().ub = ci.ub;
                }
                // else do nothing
            }
        }
    } // for(;ii!=iie;++ii)
    }
    return cc;
} // Char_Class operator-(const Char_Class& lhs,const Char_Class& rhs)

} // namespace yuki::lex