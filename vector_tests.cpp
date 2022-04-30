#include "vector.hpp"
#include <vector>
#include <iostream>
#include <time.h>

#define GREEN "\x1b[1;32m"
#define WHITE "\x1b[37m"
#define RED "\x1b[1;31m"
#define YEL "\x1b[1;33m"
#define MAG "\x1b[1;35m"
#define CYAN "\x1b[1;36m"
#define REST "\x1b[0m"
#define CLEAR "\e[1;1H\e[2J"

template<class T>
void vec_print(const T& vec, int num) {

	if (num == 1) {
		std::cout << CYAN "ft::vector<T>  " REST << "[ ";
	} else {
		std::cout << YEL "std::vector<T> " REST << "[ ";
	}
	for (size_t i = 0; i < vec.size(); ++i) {
		std::cout << vec[i] << " ";
	}
	std::cout << "]" <<std::endl;
}

template<class T>
void vec_compare(const ft::vector<T>& ft_vec, const std::vector<T>& std_vec) {

	std::cout << std::endl << MAG "compare: " REST << std::endl;
	vec_print(ft_vec, 1);
	vec_print(std_vec, 2);
	bool flag = true;
	for (size_t i = 0; i < std_vec.size() && i < ft_vec.size(); ++i) {
		if (std_vec[i] != ft_vec[i]) {
			std::cout << RED "KO :(" REST << std::endl;
			flag = false;
		}
	}
	if (flag) {
		std::cout << GREEN "OK :)" REST << std::endl;
	}
	//size
	if (std_vec.size() == ft_vec.size()) {
		std::cout << "size:  " GREEN << std_vec.size() << "==" << ft_vec.size() << REST <<
				  GREEN " OK :)" REST << std::endl;
	} else {
		std::cout << "size:  " RED << std_vec.size() << "!=" << ft_vec.size() << REST <<
				  RED " KO :(" REST << std::endl;
	}
	//capacity
	if (std_vec.capacity() == ft_vec.capacity()) {
		std::cout << "capacity:  " GREEN << std_vec.capacity() << "==" << ft_vec.capacity() << REST <<
				  GREEN " OK :)" REST << std::endl;
	} else {
		std::cout << "capacity:  " RED << std_vec.capacity() << "!=" << ft_vec.capacity() << REST <<
				  RED " KO :(" REST << std::endl;
	}
	// front
	if (ft_vec.size()) {
		if (std_vec.front() == ft_vec.front()) {
			std::cout << "front: " GREEN << std_vec.front() << "==" << ft_vec.front() << REST <<
					  GREEN " OK :)" REST << std::endl;
		} else {
			std::cout << "front: " RED << std_vec.front() << "!=" << ft_vec.front() << REST <<
					  RED " KO :(" REST << std::endl;
		}
	}
	//back
	if (ft_vec.size()) {
		if (std_vec.back() == ft_vec.back()) {
			std::cout << "back:  " GREEN << std_vec.back() << "==" << ft_vec.back() << REST <<
					  GREEN " OK :)" REST << std::endl;
		} else {
			std::cout << "back:  " RED << std_vec.back() << "!=" << ft_vec.back() << REST <<
					  RED " KO :(" REST << std::endl;
		}
	}
	std::cout << "=================================================================================="
			  << std::endl << std::endl;
}

int main() {

	ft::vector<int> my_vector(10, 21);
	std::vector<int> vector(10,21);
	my_vector.push_back(12);
	my_vector.assign(2, 10);
	vector.push_back(12);
	vector.assign(2, 10);
	vec_print(my_vector, 1);
	vec_print(vector, 2);
	vec_compare(my_vector, vector);
}
