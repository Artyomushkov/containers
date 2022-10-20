#ifndef FT_CONTAINERS_UTILITIES_HPP
#define FT_CONTAINERS_UTILITIES_HPP

#include <cstddef>
#include <iterator>
#include <limits>
#include <iostream>
#include <vector>

namespace ft {

    template <bool B, class T = void, class U = void>
    struct conditional {};

    template <class T, class U>
    struct conditional<true, T, U> { typedef T type; };

    template <class T, class U>
    struct conditional<false, T, U> { typedef U type; };

    template<class InputIterator1, class InputIterator2>
    bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
                                 InputIterator2 first2, InputIterator2 last2) {

        while (first1 != last1) {
            if (first2 == last2 || *first2 < *first1)
                return false;
            else if (*first1 < *first2)
                return true;
            ++first1;
            ++first2;
        }
        return (first2 != last2);
    }

    template<class InputIterator1, class InputIterator2, class Compare>
    bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
                                 InputIterator2 first2, InputIterator2 last2,
                                 Compare comp) {

        while (first1 != last1) {
            if (first2 == last2 || comp(*first2, *first1))
                return false;
            else if (comp(*first1, *first2))
                return true;
            ++first1;
            ++first2;
        }
        return (first2 != last2);
    }

    template<class InputIterator1, class InputIterator2>
    bool equal(InputIterator1 first1, InputIterator1 last1,
               InputIterator2 first2) {

        while (first1 != last1) {
            if (!(*first1 == *first2))
                return false;
            ++first1;
            ++first2;
        }
        return true;
    }

    template<class InputIterator1, class InputIterator2, class BinaryPredicate>
    bool equal(InputIterator1 first1, InputIterator1 last1,
               InputIterator2 first2, BinaryPredicate pred) {

        while (first1 != last1) {
            if (!pred(*first1, *first2))
                return false;
            ++first1;
            ++first2;
        }
        return true;
    }

    template <class T1, class T2>
    struct pair {

        T1   first;
        T2   second;

        typedef T1  first_type;
        typedef T2  second_type;

        pair() : first(), second() {}

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

    template<typename T >
    struct remove_const {
        typedef T type;
    };

    template<typename T >
    struct remove_const<const T> {
        typedef T type;
    };

    template<bool B, class T = void>
    struct enable_if {};

    template<class T>
    struct enable_if<true, T> {
        typedef T type;
    };

    template <class T, T v>
    struct integral_constant {

        typedef T						value_type;
        typedef integral_constant<T, v> type;

        const static T value = v;

        operator value_type() const {
            return value;
        }
    };

    typedef integral_constant<bool, true> true_type;
    typedef integral_constant<bool, false> false_type;

    template <class T>
    struct is_integral : false_type {};

    template <>
    struct is_integral<bool> : true_type {};

    template <>
    struct is_integral<char> : true_type {};

    template <>
    struct is_integral<wchar_t> : true_type {};

    template <>
    struct is_integral<signed char> : true_type {};

    template <>
    struct is_integral<short int> : true_type {};

    template <>
    struct is_integral<int> : true_type {};

    template <>
    struct is_integral<long int> : true_type {};

    template <>
    struct is_integral<long long int> : true_type {};

    template <>
    struct is_integral<unsigned char> : true_type {};

    template <>
    struct is_integral<unsigned short int> : true_type {};

    template <>
    struct is_integral<unsigned int> : true_type {};

    template <>
    struct is_integral<unsigned long int> : true_type {};

    template <>
    struct is_integral<unsigned long long int> : true_type {};

    template<typename Iterator>
    struct iterator_traits {
        typedef typename Iterator::value_type value_type;
        typedef typename Iterator::difference_type difference_type;
        typedef typename Iterator::pointer pointer;
        typedef typename Iterator::reference reference;
        typedef typename Iterator::iterator_category iterator_category;
    };

    template<typename T>
    struct iterator_traits<T*> {
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef T* pointer;
        typedef T& reference;
        typedef std::random_access_iterator_tag iterator_category;
    };

    template<typename T>
    struct iterator_traits<const T*> {
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef const T* pointer;
        typedef const T& reference;
        typedef std::random_access_iterator_tag iterator_category;
    };
}

struct s_time_res
{
    time_t std_start;
    time_t std_end;
    time_t ft_start;
    time_t ft_end;
};

time_t timer();
void print_res(std::string test, std::vector<int> &s,
               std::vector<int> &u, struct s_time_res &res);
void print_header();

void vector_test(void);
void stack_test(void);
void pair_test(void);
void map_test(void);
void set_test(void);

#endif //FT_CONTAINERS_UTILITIES_HPP
