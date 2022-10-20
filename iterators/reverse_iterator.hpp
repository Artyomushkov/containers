#ifndef CONTAINERS_REVERSE_ITERATOR_HPP
#define CONTAINERS_REVERSE_ITERATOR_HPP

# include "../utils/utilities.hpp"
# include <memory>

namespace ft {

	template<typename Iterator>
	class reverse_iterator {
	private:
		Iterator _iter;

	public:
		typedef Iterator													iterator_type;
		typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
		typedef typename ft::iterator_traits<Iterator>::value_type			value_type;
		typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
		typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
		typedef typename ft::iterator_traits<Iterator>::reference			reference;

		reverse_iterator() : _iter(NULL) {}

		explicit reverse_iterator (iterator_type it) : _iter(it) {}

		template <class Iter>
		reverse_iterator (const reverse_iterator<Iter>& rev_it) : _iter
		(rev_it.base()) {}

		iterator_type base() const {
			return _iter;
		}

		reference operator*() const {
			Iterator copy = _iter;
            reference res = *(--copy);
            return res;
		}

		pointer operator->() const {
			return &(operator*());
		}

		reverse_iterator& operator++() {
			--_iter;
			return *this;
		}

		reverse_iterator& operator--() {
			++_iter;
			return *this;
		}

		reverse_iterator operator++(int) {
			reverse_iterator copy = *this;
			--_iter;
			return copy;
		}

		reverse_iterator operator--(int) {
			reverse_iterator copy = *this;
			++_iter;
			return copy;
		}

		reverse_iterator operator+ (difference_type n) const {
			return reverse_iterator(base() - n);
		}

		reverse_iterator operator-(difference_type n) const {
			return reverse_iterator(base() + n);
		}

		reverse_iterator& operator+=(difference_type n) {
			 _iter -= n;
			 return *this;
		}

		reverse_iterator& operator-=(difference_type n) {
			 _iter += n;
			 return *this;
		}

		reference operator[](difference_type n) const {
			return base()[-n - 1];
		}
	};

	template <typename Iterator1, typename Iterator2>
  	bool operator== (const reverse_iterator<Iterator1>& lhs,
	  const reverse_iterator<Iterator2>& rhs) {
		  return lhs.base() == rhs.base();
	}

	template <typename Iterator1, typename Iterator2>
	bool operator!= (const reverse_iterator<Iterator1>& lhs,
					 const reverse_iterator<Iterator2>& rhs) {
		return lhs.base() != rhs.base();
	}

	template <typename Iterator1, typename Iterator2>
	bool operator< (const reverse_iterator<Iterator1>& lhs,
					 const reverse_iterator<Iterator2>& rhs) {
		return lhs.base() > rhs.base();
	}

	template <typename Iterator1, typename Iterator2>
  	bool operator> (const reverse_iterator<Iterator1>& lhs,
	  const reverse_iterator<Iterator2>& rhs) {
		  return lhs.base() < rhs.base();
	}

	template <typename Iterator1, typename Iterator2>
	bool operator<= (const reverse_iterator<Iterator1>& lhs,
					 const reverse_iterator<Iterator2>& rhs) {
		return lhs.base() >= rhs.base();
	}

	template <typename Iterator1, typename Iterator2>
	bool operator>= (const reverse_iterator<Iterator1>& lhs,
					 const reverse_iterator<Iterator2>& rhs) {
		return lhs.base() <= rhs.base();
	}

	template <class Iterator>
  	reverse_iterator<Iterator> operator+ (
		typename reverse_iterator<Iterator>::difference_type n,
    	const reverse_iterator<Iterator>& rev_it) {
			return rev_it + n;
	}

	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator- (
    	const reverse_iterator<Iterator>& lhs,
    	const reverse_iterator<Iterator>& rhs) {
			return lhs.base() - rhs.base();
	}
}

#endif
