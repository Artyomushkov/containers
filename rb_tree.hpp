#ifndef CONTAINERS_RB_TREE
#define CONTAINERS_RB_TREE

#include <iostream>
#include <memory>
#include <algorithm>

namespace ft {

template <typename T>
struct  RB_Node {
    
    RB_Node*    parent;
    RB_Node*    left;
    RB_Node*    right;
    T*          data;
    bool        red;

	typedef T value_type;

	RB_Node() {}

	RB_Node(const RB_Node& src) : parent(src.parent),
	left (src.left), right(src.right), data(src.data), red(src.red) {}

	~RB_Node() {}

	RB_Node& operator=(const RB_Node& src) {
		if (this == &src)
			return (*this);
		this->parent = src.parent;
		this->left = src.left;
		this->right = src.right;
		this->data = src.data;
		this->red = src.red;
		return *this;
	}
};

template <typename T, typename Compare = std::less<T>, 
typename Allocator = std::allocator<T> >
class RB_tree {
    
public:
    typedef T                                           value_type;
	typedef Compare                                     value_compare;
	typedef Allocator	                                allocator_type;
	typedef typename allocator_type::reference          reference;
	typedef typename allocator_type::const_reference    const_reference;
	typedef typename allocator_type::pointer            pointer;
	typedef typename allocator_type::const_pointer      const_pointer;
	typedef std::ptrdiff_t	                            difference_type;
	typedef std::size_t	                                size_type;
    typedef RB_Node<T>                                  node_type;
	typedef typename Allocator::template 
                rebind<node_type>::other	            node_allocator;
    typedef	typename node_allocator::pointer            node_pointer;

private:
	Compare     	_comp;
    Allocator   	_alloc;
	node_allocator	_node_alloc;
	node_pointer	_root;
	node_pointer 	_nil;
	size_type		_size;

public:

	RB_tree(const value_compare& comp = std::less<T>(),
	        const allocator_type& alloc = allocator_type(),
			const node_allocator& node_alloc = node_allocator()) :
			_comp(comp), _alloc(alloc), _node_alloc(node_alloc), _size(0) {

		try {
			_nil = _node_alloc.allocate(1);
		}
		catch(...) {
			throw;
		}
		_nil->parent = NULL;
		_nil->right = NULL;
		_nil->left = NULL;
		_nil->data = NULL;
		_nil->red = false;
		_root = _nil;
	}

	RB_tree(const RB_tree<T, Compare, Allocator>& src) : _comp(src._comp),
	_alloc(src._alloc), _node_alloc(src._node_alloc), _size(0) {

		try {
			_nil = _node_alloc.allocate(1);
		}
		catch (...) {
			throw;
		}
		_nil->parent = NULL;
		_nil->right = NULL;
		_nil->left = NULL;
		_nil->data = NULL;
		_nil->red = false;
		_root = _nil;
	}

	~RB_tree() {

		clear_tree(_root);
		_node_alloc.deallocate(_nil, 1);
	}

	node_pointer getRoot() const {

		return _root;
	}

	node_pointer getNil() const {

		return _nil;
	}

	size_type getSize() const {

		return _size;
	}

	size_type maxSize() const {

		return _alloc.max_size();
	}

	void clear_tree(node_pointer node) {

		if (node && node != _nil) {
			clear_tree(node->right);
			clear_tree(node->left);
			_alloc.destroy(node->data);
			_alloc.deallocate(node->data, 1);
			_node_alloc.deallocate(node, 1);
		}
		_size = 0;
	}

	void	clear_node(node_pointer node) {

		_alloc.destroy(node->data);
		_alloc.deallocate(node->data, 1);
		_node_alloc.deallocate(node, 1);
	}

    void	inorder_tree_walk(node_pointer x) {

		if (x != _nil) {
			inorder_tree_walk(x->left);
			std::cout << *(x->data) << " ";
			std::cout << x->red << std::endl;
			inorder_tree_walk(x->right);
		}
	}

	node_pointer tree_search(const value_type& k) const {

		node_pointer x = _root;
		while (x != _nil && *(x->data) != k) {
			if (_comp(k, *(x->data)))
				x = x->left;
			else
				x = x->right;
		}
		return x;
	}

	node_pointer tree_minimum(node_pointer x) const {

		while (x->left != _nil)
			x = x->left;
		return x;
	}

	node_pointer tree_maximum(node_pointer x) const {

		while (x->right != _nil)
			x = x->right;
		return x;
	}

	node_pointer tree_successor(node_pointer x) {

		node_pointer y;
		if (x->right != _nil)
			return tree_minimum(x->right);
		y = x->parent;
		while (y != _nil && x == y->right) {
			x = y;
			y = y->parent;
		}
		return y;
	}

	node_pointer tree_predecessor(node_pointer x) {

		node_pointer y;
		if (x->left != _nil)
			return tree_minimum(x->left);
		y = x->parent;
		while (y != _nil && x == y->left) {
			x = y;
			y = y->parent;
		}
		return y;
	}

	void    left_rotate(node_pointer x) {

        node_pointer y = x->right;
        x->right = y->left;
        if (y->left != _nil)
            y->left->parent = x;
        y->parent = x->parent;
        if (x->parent == _nil)
            _root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    void    right_rotate(node_pointer x) {

        node_pointer y = x->left;
        x->left = y->right;
        if (y->right != _nil)
            y->right->parent = x;
        y->parent = x->parent;
        if (x->parent == _nil)
            _root = y;
        else if (x == x->parent->right)
            x->parent->right = y;
        else
            x->parent->left = y;
        y->right = x;
        x->parent = y;
    }

	node_pointer	node_init(const value_type& val, bool root) {

		node_pointer z = _node_alloc.allocate(1);
		z->data = _alloc.allocate(1);
		_alloc.construct(z->data, val);
		z->parent = NULL;
		z->left = NULL;
		z->right = NULL;
		if (root)
			z->red = false;
		else
			z->red = true;
		return z;
	}

	node_pointer	rb_insert(const value_type& val, node_pointer x) {

        node_pointer y = _nil;
		node_pointer z;

		if (_nil == _root)
			z = node_init(val, true);
		else
			z = node_init(val, false);
        while (x != _nil) {
            y = x;
            if (_comp(*(z->data), *(y->data)))
                x = x->left;
            else
                x = x->right;
        }
        z->parent = y;
        if (y == _nil)
            _root = z;
        else if (_comp(*(z->data), *(y->data)))
            y->left = z;
        else
            y->right = z;
        z->left = _nil;
        z->right = _nil;
        z->red = true;
        z = rb_insert_fixup(z);
		++_size;
		return z;
    }

    node_pointer  rb_insert_fixup(node_pointer z) {

        node_pointer y;
        
        while (z->parent->red == true) {
            if (z->parent == z->parent->parent->left) {
				y = z->parent->parent->right;
				if (y->red == true) {
					z->parent->red = false;
					y->red = false;
					z->parent->parent->red = true;
					z = z->parent->parent;
				}
				else {
					if (z == z->parent->right) {
						z = z->parent;
						left_rotate(z);
					}
					z->parent->red = false;
					z->parent->parent->red = true;
					right_rotate(z->parent->parent);
				}
			}
			else {
				y = z->parent->parent->left;
				if (y->red == true) {
					z->parent->red =false;
					y->red = false;
					z->parent->parent->red = true;
					z = z->parent->parent;
				}
				else {
					if (z == z->parent->left) {
						z = z->parent;
						right_rotate(z);
					}
					z->parent->red = false;
					z->parent->parent->red = true;
					left_rotate(z->parent->parent);
				}
			}
		}
		_root->red = false;
		return z;
    }

	 void	rb_transplant(node_pointer u, node_pointer v) {

		if (u->parent == _nil)
			_root = v;
		else if (u == u->parent->left)
			u->parent->left = v;
		else
			u->parent->right = v;
		v->parent = u->parent;
	}

	void	rb_delete(node_pointer z) {

		node_pointer x;
		node_pointer y = z;
		bool y_is_red = y->red;
		if (z->left == _nil) {
			x = z->right;
			rb_transplant(z, z->right);
		}
		else if (z->right == _nil) {
			x = z->left;
			rb_transplant(z, z->left);
		}
		else {
			y = tree_minimum(z->right);
			y_is_red = y->red;
			x = y->right;
			if (y->parent == z)
				x->parent = y;

			else {
				rb_transplant(y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}
			rb_transplant(z, y);
			y->left = z->left;
			y->left->parent = y;
			y->red = z->red;
		}
		if (!y_is_red)
			rb_delete_fixup(x);
		clear_node(z);
		--_size;
	}

	void rb_delete_fixup(node_pointer x) {

		node_pointer w;
		while (x != _root && x->red == false) {
			if (x == x->parent->left) {
				w = x->parent->right;
				if (w->red) {
					w->red = false;
					x->parent->red = true;
					left_rotate(x->parent);
					w = x->parent->right;
				}
				if (w->left->red == false && w->right->red == false) {
					w->red = true;
					x = x->parent;
				}
				else {
					if (!w->right->red) {
						w->left->red = false;
						w->red = true;
						right_rotate(w);
						w = x->parent->right;
					}
					w->red = x->parent->red;
					x->parent->red = false;
					w->right->red = false;
					left_rotate(x->parent);
					x = _root;
				}
			}
			else {
				w = x->parent->left;
				if (w->red) {
					w->red = false;
					x->parent->red = true;
					right_rotate(x->parent);
					w = x->parent->left;
				}
				if (w->right->red == false && w->left->red == false) {
					w->red = true;
					x = x->parent;
				}
				else {
					if (!w->left->red) {
						w->right->red = false;
						w->red = true;
						left_rotate(w);
						w = x->parent->left;
					}
					w->red = x->parent->red;
					x->parent->red = false;
					w->left->red = false;
					right_rotate(x->parent);
					x = _root;
				}
			}
		}
		x->red = false;
	}

	void	swap(RB_tree& other) {

		std::swap(_nil, other._nil);
		std::swap(_root, other._root);
		std::swap(_size, other._size);
	}

	Allocator getAllocator() const {
		return _alloc;
	}

	size_type max_size() const {
		return _alloc.max_size();
	}

};

}

#endif