#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "vector.hpp"
#include "iterator_traits.hpp"

namespace ft{

	template <class T>
	class iterator
	{
		public:
			typedef	typename	ft::iterator_traits<T*>::value_type			value_type;
			typedef	typename	ft::iterator_traits<T*>::pointer			pointer;
			typedef	typename	ft::iterator_traits<T*>::reference			reference;
			typedef	typename	ft::iterator_traits<T*>::difference_type	difference_type;
			typedef				ft::random_access_iterator_tag				iterator_category;
		private:
			pointer _ptr;
		public:
		iterator(): _ptr(){};
		iterator(pointer ptr): _ptr(ptr){};
		iterator(const iterator &other): _ptr(other._ptr){};
		iterator	&operator=(const iterator &other){
			this->_ptr = other._ptr;
			return(*this);
		}
		virtual ~iterator(){};

		pointer const base() const {return this->_ptr;}

		reference 	operator[](difference_type n) {return *(_ptr + n);}
		reference	operator*() {return *(this->_ptr);}
		iterator	operator++() {++_ptr; return *this;}
		iterator	operator++(int) {
			iterator tmp(*this);
			this->_ptr++;
			return tmp;
		}
		iterator	operator--() {--_ptr; return *this;}
		iterator	operator--(int) {
			iterator tmp(*this);
			this->_ptr--;
			return tmp;
		}
		iterator 	&operator+=(difference_type n){this->_ptr += n; return *this;}
		iterator 	&operator-=(difference_type n){this->_ptr -= n; return *this;}
		iterator 	operator+(difference_type n) const {
			iterator tmp(*this);
			tmp._ptr += n;
			return tmp;
		}
		iterator 	operator-(difference_type n) const {
			iterator tmp(*this);
			tmp._ptr -= n;
			return tmp;
		}
		pointer 	operator->() const{return this->_ptr;}
	};

	template <class iterator>
	class reverse_iterator
	{
		public:
			typedef	typename	ft::iterator_traits<iterator*>::value_type		value_type;
			typedef	typename	ft::iterator_traits<iterator*>::pointer			pointer;
			typedef	typename	ft::iterator_traits<iterator*>::reference		reference;
			typedef	typename	ft::iterator_traits<iterator*>::difference_type	difference_type;
			typedef				ft::random_access_iterator_tag					iterator_category;
		private:
			pointer _ptr;
		public:
		reverse_iterator(): _ptr(){};
		// reverse_iterator(pointer ptr): _ptr(ptr){};
		reverse_iterator(const reverse_iterator &other): _ptr(other._ptr){};
		reverse_iterator	&operator=(const reverse_iterator &other){
			this->_ptr = other._ptr;
			return(*this);
		}
		virtual ~reverse_iterator(){};

		reverse_iterator base() const {return *this;}

		reference 	operator[](difference_type n) {return base()[-n-1];}
		reference	operator*() const {return *(_ptr - 1);}
		reverse_iterator	&operator++() {--_ptr; return *this;}
		reverse_iterator	operator++(int) {
			reverse_iterator tmp(*this);
			this->_ptr--;
			return tmp;
		}
		reverse_iterator	&operator--() {++_ptr; return *this;}
		reverse_iterator	operator--(int) {
			reverse_iterator tmp(*this);
			this->_ptr++;
			return tmp;
		}
		reverse_iterator 	&operator+=(difference_type n){this->_ptr -= n; return *this;}
		reverse_iterator 	&operator-=(difference_type n){this->_ptr += n; return *this;}
		reverse_iterator 	operator+(difference_type n) const {return this->base() - n;}
		reverse_iterator 	operator-(difference_type n) const {return this->base() + n;}
		pointer 	operator->() const{return --this->_ptr;}
	};

	template <typename T>
    bool	operator==(const ft::iterator<T> lhs, const ft::iterator<T> rhs)
    {
        return (lhs.base() == rhs.base());
    }
	
	template <typename T>
    bool	operator!=(const ft::iterator<T> lhs,
              const ft::iterator<T> rhs)
    {
        return (lhs.base() != rhs.base());
    }
	template <typename T>
    bool	operator==(const ft::reverse_iterator<T> lhs, const ft::reverse_iterator<T> rhs)
    {
        return (lhs.base() == rhs.base());
    }
	
	template <typename T>
    bool	operator!=(const ft::reverse_iterator<T> lhs,
              const ft::reverse_iterator<T> rhs)
    {
        return (lhs.base() != rhs.base());
    }
};
#endif