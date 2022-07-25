#include "rb_tree.hpp"
#include <set>
#include <iostream>

int main()
{
	std::set<int> s;
	std::set<int>::iterator it;
	for (it = s.begin(); it != s.end(); ++it) {
		std::cout << *it << std::endl;
        *it = 2;
	}
	return 0;
}
