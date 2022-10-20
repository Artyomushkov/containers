#ifndef FT_CONTAINERS_MAP_HPP
#define FT_CONTAINERS_MAP_HPP

# include <iostream>
# include <memory>
# include <stdexcept>
# include <algorithm>
#include "../utils/utilities.hpp"
#include "../iterators/bidirectional_iterator.hpp"
#include "../iterators/reverse_iterator.hpp"
#include "../tree/rb_tree.hpp"
#include "../iterators/bidirectional_iterator.hpp"

namespace ft {

    template < class Key,
            class T,
            class Compare = std::less<Key>,
            class Alloc = std::allocator<pair<const Key,T> >
    > class map {

    public:
        typedef ft::pair<const Key, T> value_type;
        typedef Key key_type;
        typedef T mapped_type;
        typedef Compare key_compare;
        typedef Alloc allocator_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef ft::bidirectional_iterator<RB_Node<value_type> > iterator;
        typedef ft::bidirectional_iterator<RB_Node<value_type> > const_iterator;
        typedef ft::reverse_iterator<iterator> reverse_iterator;
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
        typedef typename allocator_type::size_type size_type;
        typedef ptrdiff_t difference_type;

        class value_compare : public std::binary_function<value_type, value_type, bool>
        {
        public:
            Compare comp;
            value_compare (Compare c) : comp(c) {}
        public:
            typedef bool result_type;
            typedef value_type first_argument_type;
            typedef value_type second_argument_type;
            bool operator() (const value_type& x, const value_type& y) const
            {
                return comp(x.first, y.first);
            }
        };

    private:
        typedef RB_tree<value_type, value_compare, Alloc> Tree_type;
        typedef RB_Node<value_type> Node;

    private:
        Tree_type _tree;
        key_compare _comp;

    public:
        explicit map (const key_compare& comp = key_compare(),
                      const allocator_type& alloc = allocator_type()) :
                      _tree(comp, alloc), _comp(comp) {};

        template <class InputIterator>
        map (InputIterator first, InputIterator last,
             const key_compare& comp = key_compare(),
             const allocator_type& alloc = allocator_type()) :
             _tree(comp, alloc), _comp(comp) {

            for (InputIterator it = first; it != last; ++it) {
                _tree.rb_insert(*it);
            }
        }

        map (const map& x) : _tree(x._tree), _comp(x._comp) {

            for (const_iterator it = x.begin(); it != x.end(); ++it) {
                _tree.rb_insert(*it);
            }
        }

        ~map() {}

        map& operator= (const map& x) {

            if (this == &x)
                return *this;
            if (this == &x)
                return *this;
            _comp = x._comp;
            _tree.clear_tree(_tree.getRoot());
            for (iterator it = x.begin(); it != x.end(); ++it) {
                _tree.rb_insert(*it);
            }
            return *this;
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

        mapped_type& operator[] (const key_type& k) {
            iterator it_find = this->find(k);
            if (it_find != this->end()) {
                return (*it_find).second;
            }
            ft::pair<key_type, mapped_type> newPair(k, mapped_type());
            iterator it_ins = iterator(_tree.rb_insert(newPair),
                                       _tree.getRoot(), _tree.getNil());
            return (*it_ins).second;
        }

        mapped_type& at (const key_type& k) {
            iterator it_find = this->find(k);
            if (it_find != this->end()) {
                return (*it_find).second;
            }
            else {
                throw std::out_of_range("out of range!");
            }
        }

        const mapped_type& at (const key_type& k) const {
            iterator it_find = this->find(k);
            if (it_find != this->end()) {
                return (*it_find).second;
            }
            else {
                throw std::out_of_range("out of range!");
            }
        }

        pair<iterator, bool> insert (const value_type& val) {

            Node*	nodeVal = _tree.tree_search(val);
            if (nodeVal != _tree.getNil()) {
                return ft::make_pair(iterator(nodeVal, _tree.getRoot(),
                                              _tree.getNil()), false);
            }
            nodeVal = _tree.rb_insert(val);
            return ft::make_pair(iterator(nodeVal, _tree.getRoot(),
                                          _tree.getNil()), true);
        }

        iterator insert (iterator position, const value_type& val) {

            Node*	nodeVal = _tree.tree_search(val);
            if (nodeVal != _tree.getNil()) {
                return iterator(nodeVal, _tree.getRoot(), _tree.getNil());
            }
            (void)position;
            nodeVal = _tree.rb_insert(val);
            return iterator(nodeVal, _tree.getRoot(), _tree.getNil());
        }

        template <class InputIterator>
        void insert (InputIterator first, InputIterator last) {

            for (InputIterator it = first; it != last; ++it) {
                insert(*it);
            }
        }

        void erase (iterator position) {

            _tree.rb_delete(position.getBase());
        }

        size_type erase (const key_type& k) {

            iterator it = find(k);
            if (it == end()) {
                return 0;
            }
            _tree.rb_delete(it.getBase());
            return 1;
            /*pair<key_type, mapped_type> val(k, mapped_type());
            Node*    nodeVal = _tree.tree_search(val);
            if (nodeVal != _tree.getNil()) {
                _tree.rb_delete(nodeVal);
                return 1;
            }
            return 0;*/
        }

        void erase (iterator first, iterator last) {

            while (first != last)
                this->erase((*(first++)).first);
        }

        void swap (map& x) {
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

        iterator find (const key_type& k) {

            pair<key_type, mapped_type> val(k, mapped_type());
            return iterator(_tree.tree_search(val), _tree.getRoot(),
                            _tree.getNil());
        }

        const_iterator find (const key_type& k) const {

            pair<key_type, mapped_type> val(k, mapped_type());
            return const_iterator(_tree.tree_search(val), _tree.getRoot(),
                            _tree.getNil());
        }

        size_type count (const key_type& k) const {

            if (find(k) != end())
                return (1);
            return (0);
        }

        iterator lower_bound (const key_type& k) {

            Node*	tmp = _tree.getRoot();
            Node*	tmp2 = _tree.getNil();

            while (tmp != _tree.getNil()) {
                tmp2 = tmp;
                if (tmp->data->first == k)
                    return iterator(tmp, _tree.getRoot(), _tree.getNil());
                if (_comp(k, tmp->data->first))
                    tmp = tmp->left;
                else
                    tmp = tmp->right;
            }
            if (tmp2 == _tree.getNil())
                return end();
            if (_comp(tmp2->data->first, k))
                return iterator(_tree.tree_successor(tmp2), _tree.getRoot(), _tree.getNil());
            return iterator(tmp2, _tree.getRoot(), _tree.getNil());
        }

        const_iterator lower_bound (const key_type& k) const {

            return const_iterator(this->lower_bound(k));
        }

        iterator upper_bound (const key_type& k) {

            Node*	tmp = _tree.getRoot();
            Node*	tmp2 = _tree.getNil();

            while (tmp != _tree.getNil()) {
                tmp2 = tmp;
                if (tmp->data->first == k)
                    return iterator(_tree.tree_successor(tmp), _tree.getRoot(), _tree.getNil());
                if (_comp(k, tmp->data->first))
                    tmp = tmp->left;
                else
                    tmp = tmp->right;
            }
            if (tmp2 == _tree.getNil())
                return end();
            if (_comp(tmp2->data->first, k))
                return iterator(_tree.tree_successor(tmp2), _tree.getRoot(), _tree.getNil());
            return iterator(tmp2, _tree.getRoot(), _tree.getNil());
        }

        const_iterator upper_bound (const key_type& k) const {

            return const_iterator(upper_bound(k));
        }

        pair<iterator,iterator> equal_range (const key_type& k) {

            iterator lowIter = lower_bound(k);
            iterator upIter = upper_bound(k);
            return make_pair(lowIter, upIter);
        }

        pair<const_iterator, const_iterator> equal_range (const key_type& k) const {

            const_iterator lowIter = lower_bound(k);
            const_iterator upIter = upper_bound(k);
            return ft::make_pair(lowIter, upIter);
        }

        allocator_type get_allocator() const {
            return _tree.getAllocator();
        }
    };

    template <class Key, class T, class Compare, class Alloc>
    void swap (map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y) {
        x.swap(y);
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator== ( const map<Key,T,Compare,Alloc>& lhs,
                      const map<Key,T,Compare,Alloc>& rhs) {
        if (lhs.size() != rhs.size())
            return false;
        typename map<Key,T,Compare,Alloc>::const_iterator itl = lhs.begin();
        typename map<Key,T,Compare,Alloc>::const_iterator itr = rhs.begin();
        for (; itl != lhs.end(); ++itl, ++itr) {
            if (*itl != *itr) {
                return false;
            }
        }
        return true;
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator!= ( const map<Key,T,Compare,Alloc>& lhs,
                      const map<Key,T,Compare,Alloc>& rhs) {

        return (!(lhs == rhs));
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator< ( const map<Key,T,Compare,Alloc>& lhs,
                     const map<Key,T,Compare,Alloc>& rhs) {

        return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
                                            rhs.end()));
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator<= ( const map<Key,T,Compare,Alloc>& lhs,
                      const map<Key,T,Compare,Alloc>& rhs) {

        return !(rhs < lhs);
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator> ( const map<Key,T,Compare,Alloc>& lhs,
                     const map<Key,T,Compare,Alloc>& rhs) {

        return (rhs < lhs);
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator>= (const map<Key,T,Compare,Alloc>& lhs,
                      const map<Key,T,Compare,Alloc>& rhs) {

        return !(lhs < rhs);
    }
}

#endif
