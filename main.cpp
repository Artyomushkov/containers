#include "rb_tree.hpp"
#include <set>
#include <iostream>

int main()
{
	std::set<int> s;
	s.insert(10);
	s.insert(1);
	s.insert(20);
	s.insert(7);
	s.insert(6);
	s.insert(5);
	s.insert(4);
	std::set<int>::iterator it;
	for (it = s.begin(); it != s.end(); ++it) {
		std::cout << *it << std::endl;
	}
	return 0;
}
