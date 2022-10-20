#ifndef CONTAINERS_BIDIRECTIONAL_ITERATOR_HPP
#define CONTAINERS_BIDIRECTIONAL_ITERATOR_HPP

# include <cstddef>
# include <iterator>
# include "../utils/utilities.hpp"
//# include "iterator_traits.hpp"
//# include "../utils/type_traits.hpp"
//# include "../tree/rb_tree.hpp"

namespace ft {
	template <typename Node>
	class bidirectional_iterator {

	public:

		typedef typename Node::value_type value_type;
        typedef Node*                   node_pointer;
        typedef const Node*             const_node_pointer;
		typedef value_type* 			pointer;
		typedef const value_type*		const_pointer;
		typedef value_type& 			reference;
		typedef const value_type& 		const_reference;
		typedef std::ptrdiff_t 			difference_type;
		typedef std::bidirectional_iterator_tag iterator_category;

	protected:
		node_pointer _ptr;

	private:
		node_pointer	_nil;
		node_pointer	_root;

	public:
		bidirectional_iterator() : _ptr(0), _nil(0), _root(0) {}

		bidirectional_iterator(node_pointer ptr, node_pointer root,
							   node_pointer nil) :
		_ptr(ptr), _nil(nil), _root(root) {}

		 bidirectional_iterator(const bidirectional_iterator& src) :
		_ptr(src._ptr), _nil(src._nil), _root(src._root) {}

		~bidirectional_iterator() {}

		/*operator bidirectional_iterator<Node> () const {
			return bidirectional_iterator(_ptr, _root, _nil);
		}*/

		bidirectional_iterator& operator=(const bidirectional_iterator&
		src) {
			if (this == &src)
				return *this;
			this->_ptr = src._ptr;
			this->_nil = src._nil;
			this->_root = src._root;
			return *this;
		}

		reference operator*() {
			return *(_ptr->data);
		}

		const_reference operator*() const {
			return *(_ptr->data);
		}

		pointer	operator->() {
			return _ptr->data;
		}

		const_pointer operator->() const {
			return _ptr->data;
		}

		bidirectional_iterator& operator++(void) {

            if (_ptr->right != _nil) {
				_ptr = _ptr->right;
				while (_ptr->left != _nil)
					_ptr = _ptr->left;
				return *this;
			}
			node_pointer y = _ptr->parent;
			while (y != _nil && _ptr == y->right) {
				_ptr = y;
				y = y->parent;
			}
            _ptr = y;
			return *this;
		}

		bidirectional_iterator operator++(int) {

			bidirectional_iterator	copy = *this;
			++(*this);
			return copy;
		}

		bidirectional_iterator&	operator--(void) {

            if (_ptr == _nil) {
                _ptr = _root;
                while (_ptr->right != _nil) {
                    _ptr = _ptr->right;
                }
                return *this;
            }
            if (_ptr->left != _nil) {
				_ptr = _ptr->left;
				while (_ptr->right != _nil)
					_ptr = _ptr->right;
				return *this;
			}
			node_pointer y = _ptr->parent;
			while (y != _nil && _ptr == y->left) {
				_ptr = y;
				y = y->parent;
			}
            _ptr = y;
			return *this;
		}

		bidirectional_iterator	operator--(int) {

			bidirectional_iterator	copy = *this;
			--(*this);
			return copy;
		}

		node_pointer getBase() const {
			return _ptr;
		}

		template<typename U, typename V>
		friend bool operator==(const bidirectional_iterator<U>& lhs,
							   const bidirectional_iterator<V>& rhs);
	};

	template <typename Node1, typename Node2>
	bool operator==(const bidirectional_iterator<Node1>& lhs, const
	bidirectional_iterator<Node2>& rhs) {
		return lhs._ptr == rhs._ptr;
	}

	template <typename Node1, typename Node2>
	bool operator!=(const bidirectional_iterator<Node1>& lhs, const
	bidirectional_iterator<Node2>& rhs) {
		return !(lhs == rhs);
	}
}

#endif
