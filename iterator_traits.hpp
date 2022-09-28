#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

namespace ft{

	template<class Iter>
    struct iterator_traits{
		typedef typename Iter::difference_type		difference_type;
		typedef typename Iter::value_type 			value_type;
		typedef typename Iter::pointer 				pointer;
		typedef typename Iter::reference			reference;
		typedef typename Iter::iterator_category	iterator_category;
    };

	template<class T>
    struct iterator_traits<T*> {
		typedef std::ptrdiff_t					difference_type;
		typedef T								value_type;
		typedef T*								pointer;
		typedef T&								reference;
		typedef std::random_access_iterator_tag	iterator_category;
    };

	template<class T>
    struct iterator_traits<const T*> {
		typedef std::ptrdiff_t							difference_type;
		typedef const T									value_type;
		typedef const T*								pointer;
		typedef const T&								reference;
		typedef std::random_access_iterator_tag	iterator_category;
    };

	template<bool, typename T = void>
    struct enable_if{};

	template<typename T>
    struct enable_if<true, T>{typedef T type;};


	template<typename T, bool v>
	struct integral_constant {
    	typedef	T	type;
		static const bool value = v;  
	};

	template<typename> struct is_integral				: public ft::integral_constant<bool, false> {};
	template <> struct is_integral<bool>				: public ft::integral_constant<bool, true> {};
	template <> struct is_integral<char>				: public ft::integral_constant<bool, true> {};
	template <> struct is_integral<signed char>			: public ft::integral_constant<bool, true> {};
	template <> struct is_integral<unsigned char>		: public ft::integral_constant<bool, true> {};
	template <> struct is_integral<wchar_t>				: public ft::integral_constant<bool, true> {};
	template <> struct is_integral<short>				: public ft::integral_constant<bool, true> {};
	template <> struct is_integral<unsigned short>		: public ft::integral_constant<bool, true> {};
	template <> struct is_integral<int>					: public ft::integral_constant<bool, true> {};
	template <> struct is_integral<unsigned int>		: public ft::integral_constant<bool, true> {};
	template <> struct is_integral<long>				: public ft::integral_constant<bool, true> {};
	template <> struct is_integral<unsigned long> 		: public ft::integral_constant<bool, true> {};
	template <> struct is_integral<long long>			: public ft::integral_constant<bool, true> {};
	template <> struct is_integral<unsigned long long>	: public ft::integral_constant<bool, true> {};

}

#endif