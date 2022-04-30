#ifndef CONTAINERS_RANDOM_ACCESS_ITERATOR_HPP
#define CONTAINERS_RANDOM_ACCESS_ITERATOR_HPP
# include <cstddef>
# include <iterator>

namespace ft {
	template<typename T>
	class random_access_iterator {

	public:
		typedef std::ptrdiff_t difference_type;
		typedef T value_type;
		typedef value_type* pointer;
		typedef const value_type* const_pointer;
		typedef value_type& reference;
		typedef const value_type& const_reference;
		typedef std::random_access_iterator_tag iterator_category;

	protected:
		pointer _ptr;

	public:
		random_access_iterator() : _ptr(0) {}

		random_access_iterator(pointer ptr) : _ptr(ptr) {}

		random_access_iterator(const random_access_iterator& src) :
		_ptr(src._ptr) {}

		~random_access_iterator() {}

		random_access_iterator& operator=(const random_access_iterator&
		        src) {
			if (this == &src)
				return *this;
			this->_ptr = src._ptr;
			return *this;
		}

		operator random_access_iterator<const value_type>() const {
			return random_access_iterator<const value_type>(_ptr);
		}

		reference operator*() {
			return *_ptr;
		}

		const_reference operator*() const {
			return *_ptr;
		}

		pointer	operator->() {
			return _ptr;
		}

		const_pointer operator->() const {
			return _ptr;
		}

		random_access_iterator& operator+=(const difference_type n) {
			_ptr += n;
			return *this;
		}

		random_access_iterator& operator-=(const difference_type n) {
			_ptr -= n;
			return *this;
		}

		random_access_iterator& operator++(void) {
			*this += 1;
			return *this;
		}

		random_access_iterator operator++(int) {

			random_access_iterator<T>	copy = *this;
			++*this;
			return copy;
		}

		random_access_iterator&	operator--(void) {
			*this -= 1;
			return *this;
		}

		random_access_iterator operator--(int) {

			random_access_iterator<T>	copy = *this;
			--*this;
			return copy;
		}

		random_access_iterator operator+(const difference_type n) {

			random_access_iterator<T>	copy = *this;
			copy += n;
			return copy;
		}

		random_access_iterator operator-(const difference_type n) {

			random_access_iterator<T>	copy = *this;
			copy -= n;
			return copy;
		}

		difference_type operator-(const random_access_iterator&
		other) const {
			return this->_ptr - other._ptr;
		}


		reference operator[](difference_type n) const {
			return *(_ptr + n);
		}

		template<typename U, typename V>
		friend bool operator==(const random_access_iterator<U> &lhs,
							   const random_access_iterator<V> &rhs);

		template<typename U, typename V>
		friend bool operator<(const random_access_iterator<U> &lhs,
							   const random_access_iterator<V> &rhs);

	};

	template <typename T1, typename T2>
	bool operator==(const random_access_iterator<T1> &lhs, const
	random_access_iterator<T2> &rhs) {
		return &(*lhs) == &(*rhs);
	}

	template <typename T1, typename T2>
	bool operator!=(const random_access_iterator<T1> &lhs, const
	random_access_iterator<T2> &rhs) {
		return !(lhs == rhs);
	}

	template <typename T1, typename T2>
	bool operator<(const random_access_iterator<T1> &lhs, const
	random_access_iterator<T2> &rhs) {
		return &(*lhs) < &(*rhs);
	}

	template <typename T1, typename T2>
	bool operator<=(const random_access_iterator<T1> &lhs, const
	random_access_iterator<T2> &rhs) {
		return !(rhs < lhs);
	}

	template <typename T1, typename T2>
	bool operator>(const random_access_iterator<T1> &lhs, const
	random_access_iterator<T2> &rhs) {
		return rhs < lhs;
	}

	template <typename T1, typename T2>
	bool operator>=(const random_access_iterator<T1> &lhs, const
	random_access_iterator<T2> &rhs) {
		return !(lhs < rhs);
	}
	
	template<typename T>
	random_access_iterator<T> operator+(typename ft::random_access_iterator<T>::difference_type n,
										const random_access_iterator<T>& other) {
		return other + n;
	}
}

#endif
