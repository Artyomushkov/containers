#ifndef CONTAINERS_SET_HPP
#define CONTAINERS_SET_HPP

# include <iostream>
# include <memory>
# include <stdexcept>
# include <algorithm>
# include <iterator>
# include <vector>
#include "type_traits.hpp"
#include "comparement_helpers.hpp"
#include "iterators/iterator_traits.hpp"
#include "iterators/bidirectional_iterator.hpp"
#include "iterators/reverse_iterator.hpp"
#include "rb_tree.hpp"
#include "pair.hpp"
#include "iterators/bidirectional_iterator.hpp"

namespace ft {

	template < class T,
			class Compare = std::less<T>,
			class Alloc = std::allocator<T>
	> class set {

	public:
		typedef T												key_type;
		typedef T												value_type;
		typedef Compare											key_compare;
		typedef Compare											value_compare;
		typedef Alloc											allocator_type;
		typedef typename allocator_type::reference				reference;
		typedef typename allocator_type::const_reference		const_reference;
		typedef typename allocator_type::pointer				pointer;
		typedef typename allocator_type::const_pointer			const_pointer;
		typedef ft::bidirectional_iterator< RB_Node<T> >		iterator;
		typedef ft::bidirectional_iterator< RB_Node<T> >	const_iterator;
		typedef ft::reverse_iterator<iterator>					reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;
		typedef typename iterator_traits<iterator>::difference_type
			difference_type;
		typedef typename allocator_type::size_type				size_type;

	private:
		typedef RB_tree<T, Compare, Alloc>						Tree_type;
		typedef RB_Node<T>										Node;

	public:
		Tree_type 	_tree;

		explicit set (const key_compare& comp = key_compare(),
					  const allocator_type& alloc = allocator_type()) : _tree
					  (comp, alloc) {};

		template <class InputIterator>
		set (InputIterator first, InputIterator last,
			 const key_compare& comp = key_compare(),
			 const allocator_type& alloc = allocator_type()) :
			 _tree(comp, alloc) {

			for (InputIterator it = first; it != last; ++it) {
				_tree.rb_insert(*it, _tree.getRoot());
			}
		}

		set (const set& x) : _tree(x._tree) {

			for (const_iterator it = x.begin(); it != x.end(); ++it) {
				_tree.rb_insert(*it, _tree.getRoot());
			}
		}

		~set() {}

		set& operator= (const set& x) {

			if (this == &x)
				return *this;
			_tree.clear_tree(this->get_root());
			for (iterator it = x.begin(); it != x.end(); ++it) {
				_tree.rb_insert(*it, _tree.getRoot());
			}
		}

		iterator begin() {

			return iterator(_tree.tree_minimum(_tree.getRoot()), _tree
			.getRoot(), _tree.getNil());
		}

		const_iterator begin() const {

			return const_iterator(_tree.tree_minimum(_tree.getRoot()), _tree
			.getRoot(), _tree.getNil());
		}

		iterator end() {

			return iterator(_tree.getNil(), _tree
			.getRoot(), _tree.getNil());
		}

		const_iterator end() const {

			return const_iterator(_tree.getNil(), _tree
			.getRoot(), _tree.getNil());
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

		bool empty() const {
			return _tree.getSize() == 0;
		}

		size_type size() const {
			return _tree.getSize();
		}

		size_type max_size() const {
			return _tree.max_size();
		}

		pair<iterator, bool> insert (const value_type& val) {

			Node*	nodeVal = _tree.tree_search(val);
			if (nodeVal != _tree.getNil()) {
				return ft::make_pair(iterator(nodeVal, _tree.getRoot(),
										  _tree.getNil()), false);
			}
			nodeVal = _tree.rb_insert(val, _tree.getRoot());
			return ft::make_pair(iterator(nodeVal, _tree.getRoot(),
									  _tree.getNil()), true);
		}

		iterator insert (iterator position, const value_type& val) {

			Node*	nodeVal = _tree.tree_search(val);
			if (nodeVal != _tree.getNil()) {
				return iterator(nodeVal, _tree.getRoot(), _tree.getNil());
			}
			nodeVal = _tree.rb_insert(val, position.getBase());
			return iterator(nodeVal, _tree.getRoot(), _tree.getNil());
		}

		template <class InputIterator>
		void insert (InputIterator first, InputIterator last) {

			for (InputIterator it = first; it != last; ++it) {
				insert(*it);
			}
		}

		void erase (iterator position) {

			rb_delete(position.getBase());
		}

		size_type erase (const value_type& val) {

			Node*	nodeVal = _tree.tree_search(val);
			if (nodeVal != _tree.getNil()) {
				_tree.rb_delete(nodeVal);
				return 1;
			}
			return 0;
		}

		void erase (iterator first, iterator last) {

			for (iterator it = first; it != last; ++it) {
				rb_delete(it.getBase());
			}
		}

		void swap (set& x) {
			_tree.swap(x._tree);
		}

		void clear() {

			_tree.clear_tree(_tree.getRoot());
		}

		key_compare key_comp() const {

			return key_compare();
		}

		value_compare value_comp() const {

			return key_compare();
		}

		iterator find (const value_type& val) const {

			return iterator(_tree.tree_search(val), _tree.getRoot(),
							_tree.getNil());
		}

		size_type count (const value_type& val) const {

			if (_tree.tree_search(val) != _tree.getNil())
				return (1);
			return (0);
		}

		iterator lower_bound (const value_type& val) const {

			key_compare comp = key_comp();
			//iterator it = begin();
            const_iterator it = begin();
			while (it != end()) {
				if (!comp(*it, val))
					return it;
				++it;
			}
			return it;
		}

		iterator upper_bound (const value_type& val) const {

			key_compare comp = key_comp();
			const_iterator it = begin();
			while (it != end()) {
				if (comp(*it, val))
					return it;
				++it;
			}
			return it;
		}

		pair<iterator,iterator> equal_range (const value_type& val) const {

			iterator lowIter = lower_bound(val);
			iterator upIter = upper_bound(val);
			return pair<iterator, iterator>(lowIter, upIter);
		}

		allocator_type get_allocator() const {
			return _tree.getAllocator();
		}
	};

	template <class T, class Compare, class Alloc>
	void swap (set<T,Compare,Alloc>& x, set<T,Compare,Alloc>& y) {
		x.swap(y);
	}

	template <class T, class Compare, class Alloc>
	bool operator== ( const set<T,Compare,Alloc>& lhs,
					  const set<T,Compare,Alloc>& rhs) {
		return (lhs.size() == rhs.size() &&
				ft::lexicographical_compare(lhs.begin(), lhs.end(),
											rhs.begin(), rhs.end(),
											lhs.key_comp()));
	}

	template <class T, class Compare, class Alloc>
	bool operator!= ( const set<T,Compare,Alloc>& lhs,
					  const set<T,Compare,Alloc>& rhs) {

		return (!(lhs == rhs));
	}

	template <class T, class Compare, class Alloc>
	bool operator< ( const set<T,Compare,Alloc>& lhs,
					  const set<T,Compare,Alloc>& rhs) {

		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
											rhs.end()));
	}

	template <class T, class Compare, class Alloc>
	bool operator<= ( const set<T,Compare,Alloc>& lhs,
					 const set<T,Compare,Alloc>& rhs) {

		return !(rhs < lhs);
	}

	template <class T, class Compare, class Alloc>
	bool operator> ( const set<T,Compare,Alloc>& lhs,
					  const set<T,Compare,Alloc>& rhs) {

		return (rhs < lhs);
	}

	template <class T, class Compare, class Alloc>
	bool operator>= ( const set<T,Compare,Alloc>& lhs,
					 const set<T,Compare,Alloc>& rhs) {

		return !(lhs < rhs);
	}

}

#endif
