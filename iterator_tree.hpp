#ifndef ITERATOR_TREE_HPP
#define ITERATOR_TREE_HPP

#include "containers.hpp"

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

		pair_type		operator*(){return _node->_value;}
		pair_type*		operator->(){return &(_node->_value);}
		iterTree		operator++() { //preincrement
			if (!_head || !_head->_parent || !_node){
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

	template <class Iterator>
	class reverse_iterator_tree
	{
		public:
			typedef				Iterator												iterator_type;
			typedef	typename	ft::iterator_traits<iterator_type>::value_type			value_type;
			typedef	typename	ft::iterator_traits<iterator_type>::pointer				pointer;
			typedef	typename	ft::iterator_traits<iterator_type>::reference			reference;
			typedef	typename	ft::iterator_traits<iterator_type>::difference_type		difference_type;
			typedef typename	value_type::pair_type									pair_type;
		private:
			iterator_type	r_iter;
		public:
			reverse_iterator_tree():r_iter(){};
			explicit reverse_iterator_tree(const iterator_type& other):r_iter(other){};
			template <class Iterat>
			reverse_iterator_tree (const reverse_iterator_tree<Iterat>& other){
				r_iter = other.r_iter;
			}
			
			iterator_type base() const{return (r_iter);}

			reverse_iterator_tree operator++(){
				reverse_iterator_tree tmp(*this);
				this->r_iter--;
				return tmp;
			}
			reverse_iterator_tree&  operator++(int){
				--this->r_iter;
				return *this;
			}
			reverse_iterator_tree operator--(){
				reverse_iterator_tree tmp(*this);
				this->r_iter++;
				return tmp;
			}
			reverse_iterator_tree&  operator--(int){
				this->r_iter++;
				return *this;
			}

        	pair_type operator*(){
				return *r_iter;
			}
			iterator_type operator->(){
				return r_iter;
			}
	};

	template <class Iterator>  bool operator== (const reverse_iterator_tree<Iterator>& lhs, const reverse_iterator_tree<Iterator>& rhs){return lhs.base() == rhs.base();};
	template <class Iterator>  bool operator!= (const reverse_iterator_tree<Iterator>& lhs, const reverse_iterator_tree<Iterator>& rhs){return lhs.base() != rhs.base();};
	template <class Iterator>  bool operator<  (const reverse_iterator_tree<Iterator>& lhs, const reverse_iterator_tree<Iterator>& rhs){return lhs.base() < rhs.base();};
	template <class Iterator>  bool operator<= (const reverse_iterator_tree<Iterator>& lhs, const reverse_iterator_tree<Iterator>& rhs){return lhs.base() <= rhs.base();};
	template <class Iterator>  bool operator>  (const reverse_iterator_tree<Iterator>& lhs, const reverse_iterator_tree<Iterator>& rhs){return lhs.base() > rhs.base();};
	template <class Iterator>  bool operator>= (const reverse_iterator_tree<Iterator>& lhs, const reverse_iterator_tree<Iterator>& rhs){return lhs.base() >= rhs.base();};
}

#endif