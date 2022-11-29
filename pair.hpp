#ifndef PAIR_HPP
#define PAIR_HPP


namespace ft{
	template <class T1, class T2>
	struct pair
	{
		typedef	T1	first_type;
		typedef	T2	second_type;

		first_type	_first;
		second_type	_second;

		pair(){};
		pair(const first_type& x, const second_type& y):_first(x), _second(y){};
		template<class U, class V>
		pair(const pair<U,V>& pr): _first(pr._first), _second(pr._second){};
		~pair(){};
	};

	template <class T1,class T2>
	pair<T1,T2> make_pair (T1 x, T2 y){return pair<T1,T2>(x,y);}

	template <class T1,class T2>
	bool operator==(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs){return (lhs._first == rhs._first && lhs._second == rhs._second);}

	template< class T1, class T2 >
	bool operator!=(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs){return (!(lhs == rhs));}

	template< class T1, class T2 >
	bool operator<(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs){return (lhs._first < rhs._first || (!(rhs._first < lhs._first) && lhs._second < rhs._second));}

	template< class T1, class T2 >
	bool operator<=(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs){return (!(rhs < lhs));}

	template< class T1, class T2 >
	bool operator>(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs){return (rhs < lhs);}

	template< class T1, class T2 >
	bool operator>=(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs){return (!(lhs < rhs));}
}

#endif