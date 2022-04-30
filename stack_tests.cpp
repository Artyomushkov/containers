#include "stack.h"
#include <vector>

int main() {
	std::vector<int> vec;
	vec.push_back(5);
	vec.push_back(2);
	std::vector<int> vec2;
	vec2.push_back(11);
	ft::stack<int, std::vector<int> > my_stack(vec);
	ft::stack<int, std::vector<int> > my_stack2(vec2);
	if (my_stack == my_stack2)
		std::cout << 1;
};