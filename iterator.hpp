#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "containers.hpp"

namespace ft{

	template <class T>
	class iterator
	{
		public:
			typedef	typename	ft::iterator_traits<T*>::value_type			value_type;
			typedef	typename	ft::iterator_traits<T*>::pointer			pointer;
			typedef	typename	ft::iterator_traits<T*>::reference			reference;
			typedef	typename	ft::iterator_traits<T*>::difference_type	difference_type;
			typedef				std::random_access_iterator_tag				iterator_category;
			
		private:
			pointer _ptr;
		public:
		iterator(): _ptr(){};
		iterator(pointer ptr): _ptr(ptr){};
		iterator(const iterator<typename remove_const<value_type>::type > &other): _ptr(other.base()){};
		iterator<value_type>	&operator=(const iterator<typename remove_const<value_type>::type > &other){
			this->_ptr = other._ptr;
			return(*this);
		}
		virtual ~iterator(){};

		pointer const base() const {return this->_ptr;}

		reference 		operator[](difference_type n) {return *(_ptr + n);}
		reference		operator*(){return *(this->_ptr);}
		iterator		operator++() {++_ptr; return *this;}
		iterator		operator++(int) {
			iterator tmp(*this);
			this->_ptr++;
			return tmp;
		}
		iterator		operator--() {--_ptr; return *this;}
		iterator		operator--(int) {
			iterator tmp(*this);
			this->_ptr--;
			return tmp;
		}
		iterator 		&operator+=(difference_type n){this->_ptr += n; return *this;}
		iterator 		&operator-=(difference_type n){this->_ptr -= n; return *this;}
		iterator 		operator+(difference_type n) const {
			iterator tmp(*this);
			tmp._ptr += n;
			return tmp;
		}
		iterator 		operator-(difference_type n) const {
			iterator tmp(*this);
			tmp._ptr -= n;
			return tmp;
		}
		pointer 		operator->(){return this->_ptr;}
		difference_type	operator-(iterator &it){return _ptr - it._ptr;}
	};

	template <class T>  bool operator== (const iterator<T>& lhs, const iterator<T>& rhs){return lhs.base() == rhs.base();};
	template <class T>  bool operator!= (const iterator<T>& lhs, const iterator<T>& rhs){return lhs.base() != rhs.base();};
	template <class T>  bool operator<  (const iterator<T>& lhs, const iterator<T>& rhs){return lhs.base() < rhs.base();};
	template <class T>  bool operator<= (const iterator<T>& lhs, const iterator<T>& rhs){return lhs.base() <= rhs.base();};
	template <class T>  bool operator>  (const iterator<T>& lhs, const iterator<T>& rhs){return lhs.base() > rhs.base();};
	template <class T>  bool operator>= (const iterator<T>& lhs, const iterator<T>& rhs){return lhs.base() >= rhs.base();};

	template <class Iterator>
	class reverse_iterator
	{
		public:
			typedef				Iterator												iterator_type;
			typedef	typename	ft::iterator_traits<iterator_type>::value_type			value_type;
			typedef	typename	ft::iterator_traits<iterator_type>::pointer				pointer;
			typedef	typename	ft::iterator_traits<iterator_type>::reference			reference;
			typedef	typename	ft::iterator_traits<iterator_type>::difference_type		difference_type;
		private:
			iterator_type	r_iter;
		public:
			reverse_iterator():r_iter(){};
			explicit reverse_iterator(const iterator_type& other):r_iter(other){};
			template <class Iterat>
			reverse_iterator (const reverse_iterator<Iterat>& other){
				r_iter = other.r_iter;
			}
			
			iterator_type base() const{return (r_iter);}

			reverse_iterator operator+(difference_type n) const {
				reverse_iterator tmp(*this);
				tmp.r_iter -= n;
				return tmp;
			}
			reverse_iterator operator-(difference_type n) const {
				reverse_iterator tmp(*this);
				tmp.r_iter += n;
				return tmp;
			}
			reverse_iterator operator++(){
				reverse_iterator tmp(*this);
				this->r_iter--;
				return tmp;
			}
			reverse_iterator&  operator++(int){
				--this->r_iter;
				return *this;
			}
			reverse_iterator operator--(){
				reverse_iterator tmp(*this);
				this->r_iter++;
				return tmp;
			}
			reverse_iterator&  operator--(int){
				this->r_iter++;
				return *this;
			}
			reverse_iterator& operator+= (difference_type n){
				this->r_iter -= n;
				return *this;
			}
			reverse_iterator& operator-= (difference_type n){
				this->r_iter += n;
				return *this;
			}
        	reference operator*(){
				return *r_iter;
			}
			pointer operator->(){
				return &(operator*());
			}
			reference operator[] (difference_type n) const{return this->base()[n - 1];}
	};

	template <class Iterator>  bool operator== (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs){return lhs.base() == rhs.base();};
	template <class Iterator>  bool operator!= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs){return lhs.base() != rhs.base();};
	template <class Iterator>  bool operator<  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs){return lhs.base() < rhs.base();};
	template <class Iterator>  bool operator<= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs){return lhs.base() <= rhs.base();};
	template <class Iterator>  bool operator>  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs){return lhs.base() > rhs.base();};
	template <class Iterator>  bool operator>= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs){return lhs.base() >= rhs.base();};
};
#endif