#ifndef CONTAINERS_PAIR_HPP
#define CONTAINERS_PAIR_HPP

#include <iostream>

namespace ft {

   template <class T1, class T2> 
   struct pair {

        T1   first;
        T2   second;

        typedef T1  first_type;
        typedef T2  second_type;

        pair() : first(NULL), second(NULL) {}

        template<class U, class V> 
        pair (const pair<U, V>& pr) : first(pr.first), second(pr.second) {}

        pair (const first_type& a, const second_type& b) : first(a), second(b) {}

        pair& operator= (const pair& pr) {
            
            if (this == &pr)
                return *this;
            this->first = pr.first;
            this->second = pr.second;
            return *this;
        }
   };

    template <class T1, class T2>
    bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
        return lhs.first==rhs.first && lhs.second==rhs.second;
    }

    template <class T1, class T2>
    bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
        return !(lhs==rhs);
    }

    template <class T1, class T2>
    bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
        return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second); 
    }

    template <class T1, class T2>
    bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
        return !(rhs<lhs);
    }

    template <class T1, class T2>
    bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
        return rhs<lhs;
    }

    template <class T1, class T2>
    bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
        return !(lhs<rhs); 
    }

    template <class T1,class T2>
    pair<T1,T2> make_pair (T1 x, T2 y) {
        return pair<T1, T2>(x, y);
    }
}

#endif