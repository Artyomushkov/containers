#ifndef CONTAINERS_STACK_H
#define CONTAINERS_STACK_H
#include <iostream>
#include "../vector/vector.hpp"

namespace ft
{
	template<class T, class Container = ft::vector<T> >
	class stack {

	public:
		typedef Container container_type;
		typedef T value_type;
		typedef typename Container::size_type size_type;


	protected:
		Container c;

	public:
		explicit stack(const container_type &ctnr = container_type()) :
				c(ctnr) {}

		bool empty() const {
			return c.empty();
		}

		size_type size() const {
			return c.size();
		}

		value_type& top() {
			return c.back();
		}

		const value_type& top() const {
			return c.back();
		}

		void push(const value_type& val) {
			c.push_back(val);
		}

		void pop() {
			c.pop_back();
		}

		template<class A, class Cont>
		friend bool operator==(const stack<A, Cont> &lhs, const
		stack<A, Cont> &rhs);

		template<class A, class Cont>
		friend bool operator!=(const stack<A, Cont> &lhs, const
		stack<A, Cont> &rhs);

		template<class A, class Cont>
		friend bool operator<(const stack<A, Cont> &lhs, const
		stack<A, Cont> &rhs);

		template<class A, class Cont>
		friend bool operator<=(const stack<A, Cont> &lhs, const
		stack<A, Cont> &rhs);

		template<class A, class Cont>
		friend bool operator>(const stack<A, Cont> &lhs, const
		stack<A, Cont> &rhs);

		template<class A, class Cont>
		friend bool operator>=(const stack<A, Cont> &lhs, const
		stack<A, Cont> &rhs);
	};

	template <class T, class Container>
	bool operator== (const ft::stack<T,Container>& lhs, const ft::stack<T,
			Container>& rhs) {
		return lhs.c == rhs.c;
	}

	template <class T, class Container>
	bool operator!= (const ft::stack<T,Container>& lhs, const ft::stack<T,
			Container>& rhs) {
		return lhs.c != rhs.c;
	}

	template <class T, class Container>
	bool operator< (const ft::stack<T,Container>& lhs, const ft::stack<T,
			Container>& rhs) {
		return lhs.c < rhs.c;
	}

	template <class T, class Container>
	bool operator<= (const ft::stack<T,Container>& lhs, const ft::stack<T,
			Container>& rhs) {
		return lhs.c <= rhs.c;
	}

	template <class T, class Container>
	bool operator> (const ft::stack<T,Container>& lhs, const ft::stack<T,
					Container>& rhs) {
		return lhs.c > rhs.c;
	}

	template <class T, class Container>
	bool operator>= (const ft::stack<T,Container>& lhs, const ft::stack<T,
			Container>& rhs) {
		return lhs.c >= rhs.c;
	}
}

#endif
