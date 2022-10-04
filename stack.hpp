#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft{
	template <class T, class Container = ft::vector<T> >
	class stack
	{
	public:
		typedef	Container 					container_type;
		typedef typename	Container::size_type		size_type;
		typedef 	typename		Container::value_type		value_type;
		typedef		typename		Container::reference		reference;
		typedef		typename		Container::const_reference	const_reference;


		explicit stack(const container_type& cont = container_type()): _mas(cont){};
		stack(const stack& other): _mas(other._mas){};
		stack& operator=(const stack& other){
			_mas = other._mas;
			return (*this);
		}
		// ~stack();
		
		
		reference		top(){return _mas.back();}
		const_reference	top() const{return _mas.back();}
		bool			empty() const{return _mas.empty();}
		size_type		size() const{return _mas.size();}
		void			push(const value_type& value){_mas.push_back(value);}
		void			pop(){_mas.pop_back();}
	
	
	private:
		container_type _mas;
	};

	template< class T, class Container >
	bool operator==(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs){return lhs == rhs;}

	template< class T, class Container >
	bool operator!=(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs){return !(lhs == rhs);};

	template< class T, class Container >
	bool operator<(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs){return lhs < rhs;};

	template< class T, class Container >
	bool operator<=(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs){return lhs <= rhs;};

	template< class T, class Container >
	bool operator>(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs){return lhs > rhs;};

	template< class T, class Container >
	bool operator>=(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs){return lhs >= rhs;};

}

#endif