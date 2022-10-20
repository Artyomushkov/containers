#ifndef CONTAINERS_VECTOR_HPP
#define CONTAINERS_VECTOR_HPP

# include <iostream>
# include <memory>
# include <stdexcept>
# include <algorithm>
# include <iterator>
# include <vector>
#include "../utils/utilities.hpp"
#include "../iterators/random_access_iterator.hpp"
#include "../iterators/reverse_iterator.hpp"

namespace ft {

    template <class T, class Allocator = std::allocator<T> >
	class vector {

    public:
        typedef T value_type;
        typedef Allocator allocator_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef typename std::size_t size_type;
        typedef typename std::ptrdiff_t difference_type;
        typedef ft::random_access_iterator<value_type> iterator;
        typedef ft::random_access_iterator<const value_type> const_iterator;
        typedef ft::reverse_iterator<iterator> reverse_iterator;
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

    private:
        pointer _arr;
        size_type _sz;
        size_type _cap;
        allocator_type _alloc;

    public:
        explicit vector(const allocator_type &alloc = allocator_type()) :
                _arr(0), _sz(0), _cap(0), _alloc(alloc) {}

        explicit vector(size_type n, const value_type &val = value_type(),
                        const allocator_type &alloc = allocator_type()) :
                _sz(n), _cap(n), _alloc(alloc) {

            try {
                _arr = _alloc.allocate(n);
            }
            catch (...) {
                throw;
            }
            for (size_type i = 0; i < n; ++i) {
                try {
                    _alloc.construct(_arr + i, val);
                }
                catch (...) {
                    for (size_type j = 0; j < i; ++j)
                        _alloc.destroy(_arr + i);
                    _alloc.deallocate(_arr, n);
                    throw;
                }
            }
        }

        template<class InputIterator>
        vector(InputIterator first, InputIterator last,
               const allocator_type &alloc = allocator_type(), typename
               enable_if<!is_integral<InputIterator>::value>::type *
        = 0) :
                _alloc(alloc) {

            _cap = std::distance(first, last);
            _sz = _cap;
            try {
                _arr = _alloc.allocate(_cap);
            }
            catch (...) {
                throw;
            }
            size_t i = 0;
            for (InputIterator it = first; it != last; ++it) {
                try {
                    _alloc.construct(_arr + i, *it);
                }
                catch (...) {
                    for (size_type j = 0; j < i; ++j)
                        _alloc.destroy(_arr + i);
                    _alloc.deallocate(_arr, _cap);
                    throw;
                }
                ++i;
            }
        }

        vector(const vector &x) : _sz(x._sz), _cap(x._cap), _alloc(x._alloc) {

            try {
                _arr = _alloc.allocate(_cap);
            }
            catch (...) {
                throw;
            }
            for (size_type i = 0; i != _sz; ++i) {
                try {
                    _alloc.construct(_arr + i, x._arr[i]);
                }
                catch (...) {
                    for (size_type j = 0; j < i; ++j)
                        _alloc.destroy(_arr + j);
                    _alloc.deallocate(_arr, _cap);
                    throw;
                }
            }
        }

        ~vector() {

            for (size_type i = 0; i < _sz; ++i) {
                _alloc.destroy(_arr + i);
            }
            _alloc.deallocate(_arr, _cap);
        }

        vector &operator=(const vector &x) {

            if (this == &x)
                return *this;
            if (_sz >= x._sz) {
                for (size_type i = 0; i < x._sz; ++i) {
                    try {
                        _arr[i] = x._arr[i];
                    }
                    catch (...) {
                        throw;
                    }
                }
                for (size_type i = x._sz; i < _sz; ++i)
                    _alloc.destroy(_arr + i);
                _sz = x._sz;
                return *this;
            }
            try {
                this->reserve(x._cap);
            }
            catch (...) {
                throw;
            }
            for (size_type i = 0; i < x._sz; ++i) {
                try {
                    _arr[i] = x._arr[i];
                }
                catch (...) {
                    throw;
                }
            }
            return *this;
        }

        size_type size() const {
            return _sz;
        }

        size_type max_size() const {
            return _alloc.max_size();
        }

        T *data() {
            return _arr;
        }

        const T *data() const {
            return _arr;
        }

        void resize(size_type n, value_type val = value_type()) {

            if (_cap != 0) {
                while (n > _cap) {
                    try {
                        reserve(2 * _cap);
                    }
                    catch (...) {
                        throw;
                    }
                }
            } else {
                try {
                    reserve(n);
                }
                catch (...) {
                    throw;
                }
            }
            for (size_type i = _sz; i < n; ++i) {
                try {
                    _arr[i] = val;
                }
                catch (...) {
                    throw;
                }
            }
            if (n < _sz) {
                for (size_type i = n; i < _sz; ++i) {
                    _alloc.destroy(_arr + i);
                }
            }
            _sz = n;
        }

        size_type capacity() const {
            return _cap;
        }

        bool empty() const {
            if (_sz == 0)
                return true;
            return false;
        };

        void reserve(size_type n) {

            value_type *newarr;
            if (n <= _cap)
                return;
            try {
                newarr = _alloc.allocate(n);
            }
            catch (...) {
                throw;
            }
            try {
                std::uninitialized_copy(_arr, _arr + _sz, newarr);
            }
            catch (...) {
                _alloc.deallocate(newarr, n);
                throw;
            }
            for (size_t i = 0; i < _sz; ++i) {
                _alloc.destroy(_arr + i);
            }
            _alloc.deallocate(_arr, _cap);
            _arr = newarr;
            _cap = n;
        }

        void push_back(const value_type &val) {

            if (_cap == 0) {
                try {
                    reserve(1);
                }
                catch (...) {
                    throw;
                }
            }
            if (_cap == _sz) {
                try {
                    reserve(2 * _sz);
                }
                catch (...) {
                    throw;
                }
            }
            try {
                _alloc.construct(_arr + _sz, val);
            }
            catch (...) {
                throw;
            }
            ++_sz;
        }

        void pop_back() {
            _alloc.destroy(_arr + _sz);
            --_sz;
        }

        reference operator[](size_type n) {
            return _arr[n];
        }

        const_reference operator[](size_type n) const {
            return _arr[n];
        }

        reference at(size_type n) {
            if (n >= _sz)
                throw std::out_of_range("Out of Range error");
            return _arr[n];
        }

        const_reference at(size_type n) const {
            if (n >= _sz)
                throw std::out_of_range("Out of Range error");
            return _arr[n];
        }

        iterator begin() {
            return iterator(_arr);
        }

        const_iterator begin() const {
            return const_iterator(_arr);
        }

        iterator end() {
            return iterator(_arr + _sz);
        }

        const_iterator end() const {
            return const_iterator(_arr + _sz);
        }

        reverse_iterator rbegin() {
            return reverse_iterator(end());
        }

        const_reverse_iterator rbegin() const {
            return const_reverse_iterator(end());
        }

        reverse_iterator rend() {
            return reverse_iterator(begin());
        }

        const_reverse_iterator rend() const {
            return const_reverse_iterator(begin());
        }

        reference front() {
            return *_arr;
        }

        const_reference front() const {
            return *_arr;
        }

        reference back() {
            return *(_arr + _sz - 1);
        }

        const_reference back() const {
            return *(_arr + _sz - 1);
        }

        template<class InputIterator>
        void assign(InputIterator first, InputIterator last, typename
        enable_if<!is_integral<InputIterator>::value>::type * = 0) {

            for (size_type i = 0; i < _sz; ++i) {
                _alloc.destroy(_arr + i);
            }
            size_t n = std::distance(first, last);
            if (n > _cap) {
                try {
                    reserve(n);
                }
                catch (...) {
                    throw;
                }
            }
            size_type i = 0;
            for (InputIterator it = first; it != last; ++it) {
                try {
                    _alloc.construct(_arr + i, *it);
                }
                catch (...) {
                    for (size_type j = 0; j < i; ++j)
                        _alloc.destroy(_arr + j);
                    _alloc.deallocate(_arr, _cap);
                    throw;
                }
                ++i;
            }
            _sz = n;
        }

        void assign(size_type n, const value_type &val) {

            for (size_type i = 0; i < _sz; ++i) {
                _alloc.destroy(_arr + i);
            }
            if (n > _cap) {
                try {
                    reserve(n);
                }
                catch (...) {
                    throw;
                }
            }
            for (size_type i = 0; i < n; ++i) {
                try {
                    _alloc.construct(_arr + i, val);
                }
                catch (...) {
                    for (size_type j = 0; j < i; ++j)
                        _alloc.destroy(_arr + j);
                    _alloc.deallocate(_arr, _cap);
                    throw;
                }
            }
            _sz = n;
        }

        iterator insert(iterator position, const value_type &val) {

            difference_type diff = std::distance(begin(), position);
            insert(position, 1, val);
            return (iterator(_arr + diff));
        }

        void insert(iterator position, size_type n, const value_type &val) {

            difference_type diff = std::distance(begin(), position);
            if (_sz + n > _cap) {
                value_type *newarr;
                size_type new_cap;
                if (n > _sz)
                    new_cap = _sz + n;
                else
                    new_cap = 2 * _cap;
                try {
                    newarr = reserve_for_insert(new_cap, _alloc, _arr, _sz);
                }
                catch (...) {
                    throw;
                }
                try {
                    actions_fill_insert(n, _sz, newarr, diff, _alloc, val);
                }
                catch (...) {
                    _alloc.deallocate(newarr, new_cap);
                    throw;
                }
                _alloc.deallocate(_arr, _cap);
                _sz += n;
                _arr = newarr;
                _cap = new_cap;
                return;
            }
            try {
                actions_fill_insert(n, _sz, _arr, diff, _alloc, val);
            }
            catch (...) {
                throw;
            }
            _sz += n;
        }

        template<class InputIterator>
        void insert(iterator position, InputIterator first, InputIterator
        last, typename enable_if<!is_integral<InputIterator>::value>::type * = 0) {

            difference_type diff = std::distance(begin(), position);
            difference_type n = std::distance(first, last);
            if (_sz + static_cast<size_type>(n) > _cap) {
                T *newarr;
                size_type new_cap;
                if (static_cast<size_type>(n) > _sz)
                    new_cap = _sz + static_cast<size_type>(n);
                else
                    new_cap = 2 * _cap;
                try {
                    newarr = reserve_for_insert(new_cap, _alloc, _arr, _sz);
                }
                catch (...) {
                    throw;
                }
                try {
                    actions_iter_insert(n, _sz, newarr, diff, _alloc,
                                        first);
                }
                catch (...) {
                    _alloc.deallocate(newarr, new_cap);
                    throw;
                }
                _alloc.deallocate(_arr, _cap);
                _sz += n;
                _cap = new_cap;
                _arr = newarr;
                return;
            }
            try {
                actions_iter_insert(n, _sz, _arr, diff, _alloc, first);
            }
            catch (...) {
                throw;
            }
            _sz += n;
        }

        iterator erase(iterator position) {

            difference_type diff = std::distance(begin(), position);
            for (size_type i = diff; i < _sz - 1; ++i) {
                try {
                    _arr[i] = _arr[i + 1];
                }
                catch (...) {
                    throw;
                }
            }
            _alloc.destroy(_arr + _sz - 1);
            --_sz;
            return iterator(_arr + diff);
        }

        iterator erase(iterator first, iterator last) {

            difference_type diff = std::distance(begin(), first);
            difference_type n = std::distance(first, last);

            for (size_type i = diff; i < _sz - n; ++i) {
                try {
                    _arr[i] = _arr[i + n];
                }
                catch (...) {
                    throw;
                }
            }
            for (size_type i = _sz - n; i < _sz; ++i)
                _alloc.destroy(_arr + i);
            _sz -= n;
            return iterator(_arr + diff);
        }

        void clear() {

            for (size_type i = 0; i < _sz; ++i)
                _alloc.destroy(_arr + i);
            _sz = 0;
        }

        void swap(vector &x) {

            pointer tmpPointer = _arr;
            size_type tmpSize = _sz;
            size_type tmpCap = _cap;
            allocator_type tmpAlloc = _alloc;

            _arr = x._arr;
            _sz = x._sz;
            _cap = x._cap;
            _alloc = x._alloc;

            x._arr = tmpPointer;
            x._sz = tmpSize;
            x._cap = tmpCap;
            x._alloc = tmpAlloc;
        }

        allocator_type get_allocator() const {
            return _alloc;
        }

    private:
        T *reserve_for_insert(size_type n, allocator_type alloc, T *arr, size_type
        sz) {

            T *newarr;
            try {
                newarr = alloc.allocate(n);
            }
            catch (...) {
                throw;
            }
            try {
                std::uninitialized_copy(arr, arr + sz, newarr);
            }
            catch (...) {
                alloc.deallocate(newarr, n);
                throw;
            }
            return newarr;
        }

        void actions_fill_insert(size_type n, size_type sz, T *arr, difference_type
        diff, allocator_type alloc, const T &val) {
            for (size_t i = sz + n - 1; i > diff + n - 1; --i) {
                try {
                    if (i > sz)
                        alloc.construct(arr + i, *(arr + i - n));
                    else
                        arr[i] = arr[i - n];
                }
                catch (...) {
                    for (size_type j = sz + n - 1; j > i; --j) {
                        alloc.destroy(arr + j);
                    }
                    throw;
                }
            }
            for (difference_type i = diff + n - 1; i > diff - 1; i--) {
                try {
                    if (static_cast<size_type>(i) > sz)
                        alloc.construct(arr + i, val);
                    else
                        arr[i] = val;
                }
                catch (...) {
                    for (difference_type j = diff + n - 1; j > i; --j) {
                        alloc.destroy(arr + j);
                    }
                    throw;
                }
            }
        }

        template<typename InputIterator>
        void actions_iter_insert(size_type n, size_type sz, T *arr, difference_type diff,
                                 allocator_type alloc, InputIterator first) {

            for (size_t i = sz + n - 1; i > diff + n - 1; --i) {
                try {
                    if (i > sz)
                        alloc.construct(arr + i, *(arr + i - n));
                    else
                        arr[i] = arr[i - n];
                }
                catch (...) {
                    for (size_type j = sz + n - 1; j > i; --j) {
                        alloc.destroy(arr + j);
                    }
                    throw;
                }
            }
            for (size_t i = diff; i < diff + n; i++) {
                try {
                    if (static_cast<size_t>(i) > sz)
                        alloc.construct(arr + i, *first);
                    else
                        arr[i] = *first;
                    first++;
                }
                catch (...) {
                    for (difference_type j = sz + n - 1; j > diff; --j) {
                        alloc.destroy(arr + j);
                    }
                    throw;
                }
            }
        }
	};

	template<class T, class Alloc>
	void swap(ft::vector<T, Alloc>& lhs, ft::vector<T, Alloc>& rhs) {
		lhs.swap(rhs);
	}

	template <class T, class Alloc>
	bool operator== (const ft::vector<T, Alloc>& lhs, const ft::vector<T,Alloc>&
	        rhs) {

		return  (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(),
													 rhs.begin()));
	}

	template <class T, class Alloc>
	bool operator!= (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>&
	        rhs) {

		return (!(lhs == rhs));
	}

	template <class T, class Alloc>
	bool operator<  (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>&
	        rhs) {

		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
											rhs.end()));
	}

	template <class T, class Alloc>
	bool operator<= (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>&
	        rhs) {

		return !(rhs < lhs);
	}

	template <class T, class Alloc>
	bool operator> (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>&
	rhs) {

		return (rhs < lhs);
	}

	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {

		return !(lhs < rhs);
	}
}

#endif