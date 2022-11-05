#ifndef RBTREE_HPP
#define RBTREE_HPP

#include <functional>
#include "iterator_tree.hpp"
#include "pair.hpp"
#include "algorithm.hpp"

namespace ft{

	enum nodeType{NILL, RED, BLACK};

	template<class T>
	struct Node
	{
		T			_value;
		Node*		_parent;
		Node*		_left;
		Node*		_right;
		nodeType	_nodeType;

		Node(): _value(T()), _parent(NULL), _left(NULL), _right(NULL), _nodeType(RED){}
		Node(const T& val): _value(val), _parent(NULL), _left(NULL), _right(NULL), _nodeType(RED){}
		Node( Node const & other) {
			*this = other;
		}

		Node& operator=(const Node& other){
			this->_value = other._value;
			this->_parent = other._parent;
			this->_left = other._left;
			this->_right = other._right;
			this->_nodeType = other._nodeType;
			return *this;
		}

		Node* maximum(Node* lst){
			while (lst && lst->_right && lst->_right->_nodeType)
				lst = lst->_right;
			return lst;
		}

		Node* minimum(Node* lst){
			while (lst && lst->_left && lst->_left->_nodeType)
				lst = lst->_left;
			return lst;
		}

		~Node(){}
	};
	
	
	template<class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
    class red_black_tree {
    public:
        typedef 			T											value;
        typedef 			Compare 									key_compare;
        typedef 			Alloc 										allocator_type;
		typedef typename	Alloc::template rebind<Node<value> >::other	node_allocator;
        typedef typename 	node_allocator::size_type					size_type;
        typedef typename 	node_allocator::pointer						p_node;
		typedef typename 	node_allocator::reference					r_node;
		typedef				ft::iterTree<p_node>						iterator;
		typedef				ft::iterTree<const p_node>					const_iterator;
		/*
		Compare(2, 1)
		1 rebind
		2 all metods
	private ^ size, compare, main, alloc(rebind)
			node Nill, (node first, node last) - iterator 
		*/
		private:
			p_node			_head;
			p_node			_first;
			p_node			_last;
			size_type		_size;
			Compare			_compare;
			node_allocator	_alloc;
		
		// public:
		// 	red_black_tree(){

		// 	}
    };
}

#endif