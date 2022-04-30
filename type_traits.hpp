#ifndef TYPETRAITS_HPP
#define TYPETRAITS_HPP

# include <limits>

namespace ft {

	template<typename T > struct remove_const {
		typedef T type;
	};

	template<typename T > struct remove_const<const T> {
		typedef T type;
	};

	template<bool B, class T = void>
	struct enable_if {};

	template<class T>
	struct enable_if<true, T> {
		typedef T type;
	};

	template <class T, T v>
	struct integral_constant {

		typedef T						value_type;
		typedef integral_constant<T, v> type;

		const static T value = v;

		operator value_type() const {
			return value;
		}
	};

	typedef integral_constant<bool, true> true_type;
	typedef integral_constant<bool, false> false_type;

	template <class T>
	struct is_integral : false_type {};

	template <>
	struct is_integral<bool> : true_type {};

	template <>
	struct is_integral<char> : true_type {};

	template <>
	struct is_integral<char16_t> : true_type {};

	template <>
	struct is_integral<char32_t> : true_type {};

	template <>
	struct is_integral<wchar_t> : true_type {};

	template <>
	struct is_integral<signed char> : true_type {};

	template <>
	struct is_integral<short int> : true_type {};

	template <>
	struct is_integral<int> : true_type {};

	template <>
	struct is_integral<long int> : true_type {};

	template <>
	struct is_integral<long long int> : true_type {};

	template <>
	struct is_integral<unsigned char> : true_type {};

	template <>
	struct is_integral<unsigned short int> : true_type {};

	template <>
	struct is_integral<unsigned int> : true_type {};

	template <>
	struct is_integral<unsigned long int> : true_type {};

	template <>
	struct is_integral<unsigned long long int> : true_type {};
}


#endif