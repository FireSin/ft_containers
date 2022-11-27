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
		private:;
			pointer _node;
			pointer _head;
		public:
		iterTree(): _node(){};
		iterTree(pointer ptr, pointer head): _node(ptr), _head(head){};
		iterTree(const iterTree<typename remove_const<value_type>::type > &other): _node(other._node){};
		iterTree	&operator=(const iterTree<typename remove_const<value_type>::type > &other){
			this->_node = other._node;
			return(*this);
		}
		virtual ~iterTree(){};

		pointer const base() const {return _node;}

		reference		operator*() {return _node->_value;}
		pointer			operator->() const{return &_node->_value;}
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
				while (_node->_parent != _head->_parent && _node->_parent->_left == _node){
					_node = _node->_parent;
				}
			}
			return *this;
		}
		iterTree		operator++(int){ //postincrement
			iterTree tmp(*this);
			++(*this);
			return tmp;
		}
		iterTree		operator--() { //preincrement
			return *this;
		}
		iterTree		operator--(int){ //postincrement
			iterTree tmp(*this);
			--_node;
			return tmp;
		}
	};
	template <class T>  bool operator== (const iterTree<T>& lhs, const iterTree<T>& rhs){return lhs.base() == rhs.base();};
	template <class T>  bool operator!= (const iterTree<T>& lhs, const iterTree<T>& rhs){return lhs.base() != rhs.base();};
}

#endif