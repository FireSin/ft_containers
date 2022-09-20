#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "vector.hpp"
#include "iterator_traits.hpp"

namespace ft{

	// struct input_iterator_tag: std::input_iterator_tag { };
	// struct output_iterator_tag { };
	// struct forward_iterator_tag : public input_iterator_tag { };
	// struct bidirectional_iterator_tag : public forward_iterator_tag { };
	// struct random_access_iterator_tag : public bidirectional_iterator_tag { };

	// template <class Category, class T, class Distance = std::ptrdiff_t,
    //       class Pointer = T*, class Reference = T&>
	// struct iterator {
	// 	typedef T         value_type;
	// 	typedef Distance  difference_type;
	// 	typedef Pointer   pointer;
	// 	typedef Reference reference;
	// 	typedef Category  iterator_category;
	// };

	template <class T>
	class vectorIter: ft::iterator<ft::random_access_iterator_tag, T>
	{
		public:
			typedef	typename	ft::iterator_traits<T*>::value_type			value_type;
			typedef	typename	ft::iterator_traits<T*>::pointer			pointer;
			typedef	typename	ft::iterator_traits<T*>::reference			reference;
			typedef	typename	ft::iterator_traits<T*>::difference_type	difference_type;
			typedef	typename	ft::iterator_traits<T*>::iterator_category	iterator_category;
		private:
			pointer _ptr;
		public:
		vectorIter(): _ptr(){};
		vectorIter(pointer ptr): _ptr(ptr){};
		virtual ~vectorIter(){};

		pointer const base() const {return this->_ptr;}

		reference 		operator[](difference_type n) const {return *(_ptr + n);}
		reference		operator*() {return *(this->_ptr);}
		vectorIter		operator++(int) {++_ptr; return *this;}
		vectorIter		operator--(int) {--_ptr; return *this;}
	};

	template <typename T>
    bool	operator==(const ft::vectorIter<T> lhs,
              const ft::vectorIter<T> rhs)
    {
        return (lhs.base() == rhs.base());
    }
	
	template <typename T>
    bool	operator!=(const ft::vectorIter<T> lhs,
              const ft::vectorIter<T> rhs)
    {
        return (lhs.base() != rhs.base());
    }
};
#endif