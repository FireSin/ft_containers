#ifndef ITERATOR_TREE_HPP
#define ITERATOR_TREE_HPP

#include "rbTree.hpp"
#include "iterator_traits.hpp"

namespace ft{

	template <class T>
	class iterTree
	{
		public:		
			typedef	typename	ft::iterator_traits<T*>::value_type					value_type;
			typedef	typename	ft::iterator_traits<T*>::pointer					pointer;
			typedef	typename	ft::iterator_traits<T*>::reference					reference;
			typedef	typename	ft::iterator_traits<T*>::difference_type			difference_type;
			typedef				std::bidirectional_iterator_tag						iterator_category;
			typedef	typename	value_type::pair_type								pair_type;
		private:
			pointer _node;
			pointer _head;
		public:
		iterTree(): _node(){};
		iterTree(pointer ptr, pointer head): _node(ptr), _head(head){};
		iterTree(const iterTree<typename remove_const<value_type>::type> &other){
			*this = other;
		};

		iterTree	&operator=(const iterTree<typename remove_const<value_type>::type> &other){
			this->_node = other._node;
			this->_head = other._head;
			return(*this);
		}
		virtual ~iterTree(){};

		pointer const base() const {return _node;}

		pair_type		operator*() const{return _node->_value;}
		pair_type*		operator->() const{return &(_node->_value);}
		iterTree		operator++() { //preincrement
			if (!_head || !_head->_parent){
				return *this;
			}
			if (_node->_right != _head->_parent){
				_node = _node->_right;
				while (_node->_left != _head->_parent){
					_node = _node->_left;
				}
			} else {
				while (_node->_parent != _head->_parent && _node->_parent->_left != _node){
					_node = _node->_parent;
				}
				_node = _node->_parent;
			}
			return *this;
		}
		iterTree		operator++(int){ //postincrement
			iterTree tmp(*this);
			++(*this);
			return tmp;
		}
		iterTree		operator--() { //preincrement
			if (_head == NULL || _head->_parent == NULL){
				return *this;
			}
			if (_node == _head->_parent){
				// _node = _node->maximum(_head);
				pointer lst = _head;
				while (lst && lst->_right != NULL && lst->_right->_right != NULL)
					lst = lst->_right;
				_node = lst;
				return *this;
			}
			if (_node->_left != _head->_parent){
				_node = _node->_left;
				while (_node->_right != _head->_parent){
					_node = _node->_right;
				}
			} else {
				while (_node->_parent != _head->_parent && _node->_parent->_right != _node){
					_node = _node->_parent;
				}
				_node = _node->_parent;
			}
			return *this;
		}
		iterTree		operator--(int){ //postincrement
			iterTree tmp(*this);
			--(*this);
			return tmp;
		}
	};
	template <class T>  bool operator== (const iterTree<T>& lhs, const iterTree<T>& rhs){return lhs.base() == rhs.base();};
	template <class T>  bool operator!= (const iterTree<T>& lhs, const iterTree<T>& rhs){return lhs.base() != rhs.base();};
	template <class T>  bool operator<  (const iterTree<T>& lhs, const iterTree<T>& rhs){return lhs.base() < rhs.base();};
	template <class T>  bool operator<= (const iterTree<T>& lhs, const iterTree<T>& rhs){return lhs.base() <= rhs.base();};
	template <class T>  bool operator>  (const iterTree<T>& lhs, const iterTree<T>& rhs){return lhs.base() > rhs.base();};
	template <class T>  bool operator>= (const iterTree<T>& lhs, const iterTree<T>& rhs){return lhs.base() >= rhs.base();};


	// template <class Iter>
	// class reverse_iterTree
	// {
	// 	public:		
	// 		typedef Iter iterator_type;
	// 		typedef typename iterator_type::reference reference;
	// 		typedef typename iterator_type::pointer pointer;
	// 		typedef typename iterator_type::difference_type difference_type;
	// 	private:
	// 		iterator_type r_iter;
	// 	public:
	// 	reverse_iterTree(): r_iter(){};
	// 	explicit reverse_iterTree(iterator_type other): r_iter(other){};
	// 	template <class It>
	// 	reverse_iterTree (const reverse_iterTree<It>& other){
	// 		r_iter = other.r_iter;
	// 	}
	// 	virtual ~reverse_iterTree(){};

	// 	iterator_type base() const {return r_iter;}

	// 	iterator_type			operator->() const{return *r_iter;}
	// 	reference				operator*() {return r_iter;}

	// 	reverse_iterTree&	operator--() { //preincrement
	// 		reverse_iterTree tmp(*this);
	// 		this->r_iter++;
	// 		return(tmp);
	// 	}
	// 	reverse_iterTree	operator--(int){ //postincrement
	// 		this->r_iter++;
	// 		return(*this);
	// 	}
	// 	reverse_iterTree&	operator++() { //preincrement
	// 		reverse_iterTree tmp(*this);
	// 		this->r_iter--;
	// 		return(tmp);
	// 	}
	// 	reverse_iterTree		operator++(int){ //postincrement
	// 		this->r_iter--;
	// 		return(*this);
	// 	}
		
	// };
	// template <class T>  bool operator== (const reverse_iterTree<T>& lhs, const reverse_iterTree<T>& rhs){return lhs.base() == rhs.base();};
	// template <class T>  bool operator!= (const reverse_iterTree<T>& lhs, const reverse_iterTree<T>& rhs){return lhs.base() != rhs.base();};
	// template <class T>  bool operator<  (const reverse_iterTree<T>& lhs, const reverse_iterTree<T>& rhs){return lhs.base() < rhs.base();};
	// template <class T>  bool operator<= (const reverse_iterTree<T>& lhs, const reverse_iterTree<T>& rhs){return lhs.base() <= rhs.base();};
	// template <class T>  bool operator>  (const reverse_iterTree<T>& lhs, const reverse_iterTree<T>& rhs){return lhs.base() > rhs.base();};
	// template <class T>  bool operator>= (const reverse_iterTree<T>& lhs, const reverse_iterTree<T>& rhs){return lhs.base() >= rhs.base();};
}

#endif