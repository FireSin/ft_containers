#ifndef RBTREE_HPP
#define RBTREE_HPP

#include <functional>
#include "iterator_tree.hpp"
#include "pair.hpp"
#include "algorithm.hpp"

namespace ft{

	enum nodeColor{RED, BLACK};

	template<class T>
	struct Node
	{
		T			_value;
		Node*		_parent;
		Node*		_left;
		Node*		_right;
		nodeColor	_color;

		Node(): _value(T()), _parent(NULL), _left(NULL), _right(NULL), _color(RED){}
		Node(const T& val): _value(val), _parent(NULL), _left(NULL), _right(NULL), _color(RED){}
		Node( Node const & other) {
			*this = other;
		}

		Node& operator=(const Node& other){
			this->_value = other._value;
			this->_parent = other._parent;
			this->_left = other._left;
			this->_right = other._right;
			this->_color = other._color;
			return *this;
		}

		Node* maximum(Node* lst){
			while (lst && lst->_right != NULL)
				lst = lst->_right;
			return lst;
		}

		Node* minimum(Node* lst){
			while (lst && lst->_left != NULL)
				lst = lst->_left;
			return lst;
		}

		~Node(){}
	};
	
	
	template<class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
    class rbTree {
    public:
        typedef 			T											value;
		typedef				Node<value>									node_type;
        typedef 			Compare 									key_compare;
		typedef typename	Alloc::template rebind<Node<value> >::other	node_alloc;
        typedef typename 	node_alloc::size_type						size_type;
        typedef typename 	node_alloc::pointer							p_node;
		typedef				ft::iterTree<node_type>						iterator;
		typedef				ft::iterTree<const node_type>				const_iterator;

		private:
			p_node			_head;
			key_compare		_key_comp;
			node_alloc		_node_alloc;
			size_type		_size;
		
		public:
			rbTree(): _head(NULL), _size(0){}
			explicit rbTree(const key_compare& comp, const node_alloc& allc = node_alloc()):
				_head(NULL), _node_alloc(allc), _key_comp(comp), _size(0) {}
			rbTree(const rbTree& other): _head(NULL), _node_alloc(other._node_alloc), _key_comp(other._key_comp){
				copyRBTree(_head, NULL, other._head);
				_size = other._size;
			}
			rbTree& operator=(const rbTree& other){
				p_node tmp = NULL;
				copyRBTree(tmp, NULL, other._head);
				clear(_head);
				_head = tmp;
				_size = other._size;
				return *this;
			}
			~rbTree(){
				clear(_head);
			}

			size_type size(){return _size;}

			size_type max_size(){return node_alloc().max_size();}

			iterator begin(){
				p_node tmp = _head;
				return iterator(tmp->minimum(_head), _head);				
			}

			const_iterator begin() const{
				p_node *tmp = _head;
				return const_iterator(tmp->maximum(_head), _head);			
			}

			iterator end(){return iterator(NULL, _head);}

			const_iterator end() const{return const_iterator(NULL, _head);}

			p_node newNode(const value& val){
				p_node newNode = _node_alloc.allocate(1);
				_node_alloc.construct(newNode, node_type(val));
				return newNode;
			}

			void copyRBTree(p_node *&current, p_node curr_parent, p_node other_node){
				if (other_node == NULL){
					return ;
				}
				current = newNode(other_node->_value);
				current->_parent = curr_parent;
				copyRBTree(current->_left, current, other_node->_left);
				copyRBTree(current->_right, current, other_node->_right);
			}

			bool is_Red(p_node node){
				if (node == NULL){
					return false;
				}
				return node->_color == RED;
			}

			void rotate_left(p_node node){
				p_node grandp = node->_parent->_parent;
				p_node parnt = node->_parent;
				p_node tmp = node->_left;
				if (grandp != NULL){
					if (grandp->_left == parnt){
						grandp->_left = node;
					} else {
						grandp->_right = node;
					}
				}
				node->_parent = grandp;
				parnt->_parent = node;
				node->_left = parnt;
				parnt->_right = tmp;
				if (grandp == NULL){
					_head = node;
				}
			}

			void rotate_right(p_node node){
				p_node grandp = node->_parent->_parent;
				p_node parnt = node->_parent;
				p_node tmp = node->_right;
				if (grandp != NULL){
					if (grandp->_left == parnt){
						grandp->_left = node;
					} else {
						grandp->_right = node;
					}
				}
				node->_parent = grandp;
				parnt->_parent = node;
				node->_right = parnt;
				parnt->_left = tmp;
				if (grandp == NULL){
					_head = node;
				}
			}

			// void balance(p_node node){

			// }

			pair<p_node, bool> insert_to_tree(p_node *tree, const value& key){
				p_node parent;
				if (*tree == NULL){
					parent = NULL;
				} else {
					parent = (*tree)->_parent;
				}
				while (*tree != NULL){
					if(_key_comp(key, (*tree)->_value)){
						parent = *tree;
						tree = &((*tree)->_left);
					} else if (_key_comp((*tree)->_value, key)){
						parent = *tree;
						tree = &((*tree)->_right);
					} else {
						return ft::make_pair(*tree, false);
					}
				}
				*tree = newNode(key);
				(*tree)->_parent = parent;
				// balance(*tree);
				_size++;
				return ft::make_pair(*tree, true);
			}

			pair<iterator, bool> insert(const value& val){
				ft::pair<p_node, bool> tmp = insert_to_tree(&_head, val);
				return ft::make_pair(iterator(tmp._first, _head), tmp._second);
			}

			iterator insert(iterator hint, const value& val){
				if (hint == lower_bound(val)){
					p_node node = newNode(val);
					(*hint)->_right = node;
					node->_parent = hint;
					balance(node);
					return iterator(node, _head);
				}
				ft::pair<p_node, bool> tmp  = insert_to_tree(&_head, val);
				return iterator(tmp._first);
			}

			template <class InputIterator>
			void insert(InputIterator first, InputIterator last){
				for (InputIterator i = first; i != last; ++i){
					insert(*i);
				}
			}

			void swapNode(p_node a, p_node b){
				std::swap(a->_color, b->_color);
				if (a->_left){
					a->_left->_parent = b;
				}
				if (b->_left){
					b->_left->_parent = a;
				}
				std::swap(a->_left, b->_left);
				if (a->_right){
					a->_right->_parent = b;
				}
				if (b->_right){
					b->_right->_parent = a;
				}
				std::swap(a->_right, b->_right);
				if (a->_parent){
					if (a->_parent->_left == a){
						a->_parent->_left = b;
					} else {
						a->_parent->_right = b;
					}
				} else {
					_head = b;
				}
				if (b->_parent){
					if (b->_parent->_left == b){
						b->_parent->_left = a;
					} else {
						b->_parent->_right = a;
					}
				} else{
					_head = a;
				}
				std::swap(a->_parent, b->_parent);
			}
    
		void eraseNode(p_node node){
			p_node del = node;
			if (node->_left && node->_right){
				del = node->_right;
				while (del->_left){
					del = del->_left;
				}
				swapNode(node, del);
				eraseNode(node);				
			} else if (node->_left){
				node->_left->_color = BLACK;
				node->_left->_parent = node->_parent;
				if (node->_parent){
					if (node->_parent->_left == node){
						node->_parent->_left = node->_left;
					} else {
						node->_parent->_right = node->_left;
					}
				} else {
					_head = node->_left;
				}
				deleteNode(del);
				return;
			} else if (node->_right){
				node->_right->_color = BLACK;
				node->_right->_parent = node->_parent;
				if (node->_parent){
					if (node->_parent->_right == node){
						node->_parent->_right = node->_right;
					} else{
						node->_parent->_left = node->_right;
					}
				} else {
					_head = node->_right;
					deleteNode(del);
					return;
				}
			} else {
				if (node->_color == RED){
					p_node *tmp;
					if (node->_parent->_right == node){
						tmp = &node->_parent->_right;
					} else {
						tmp = &node->_parent->_left;
					}
					deleteNode(*tmp);
					*tmp = NULL;
				} else {
					p_node *tmp;
					// p_node parent = node->_parent;
					if (node->_parent){
						if (node->_parent->_right == node){
							tmp = &node->_parent->_right;
						} else {
							tmp = &node->_parent->_left;
						}
					} else {
						tmp = &_head;
					}
					deleteNode(*tmp);
					*tmp = NULL;
					// balanceEr(tmp, parent);
				}
			}
		}

		void balanceEr(p_node *del, p_node parent){
			
		}

		void erase(iterator pos){
			eraseNode(pos._node);
		}

		size_type erase(const value& key){
			p_node node = findNode(key);
			if (node){
				eraseNode(node);
				return 1;
			}
			return 0;
		}

		void erase(iterator first, iterator last){
			for (; first != last; first++){
				eraseNode(first.base);
			}
		}

		p_node findNode(const value& key) const{
			p_node tmp = _head;
			while (tmp != NULL){
				if (_key_comp(key, tmp->_value)){
					tmp = tmp->_left;
				} else if (_key_comp(tmp->_value, key)){
					tmp = tmp->_right;
				} else {
					return tmp;
				}
			}
			return NULL;
		}

		iterator find(const value& key){
			return iterator(findNode(key), _head);
		}

		iterator lower_bound(const value& key){
			p_node tmp = _head;
			p_node res = NULL;
			while (tmp != NULL){
				if (_key_comp(key, tmp->_value)){
					res = tmp;
					tmp = tmp->_left;
				} else if (!_key_comp(tmp->_value, key)){
					res = tmp;
					tmp = tmp->_left;
				} else {
					tmp = tmp->_right;
				}
			}
			return iterator(tmp, _head);
		}

		const_iterator lower_bound(const value& key) const{
			p_node tmp = _head;
			p_node res = NULL;
			while (tmp != NULL){
				if (_key_comp(key, tmp->_value)){
					res = tmp;
					tmp = tmp->_left;
				} else if (!_key_comp(tmp->_value, key)){
					res = tmp;
					tmp = tmp->_left;
				} else {
					tmp = tmp->_right;
				}
			}
			return const_iterator(tmp, _head);
		}

		iterator upper_bound(const value& key){
			p_node tmp = _head;
			p_node res = NULL;
			while (tmp != NULL){
				if (_key_comp(key, tmp->_value)){
					res = tmp;
					tmp = tmp->_left;
				} else {
					tmp = tmp->_right;
				}
			}
			return iterator(tmp, _head);			
		}

		const_iterator upper_bound(const value& key) const{
			p_node tmp = _head;
			p_node res = NULL;
			while (tmp != NULL){
				if (_key_comp(key, tmp->_value)){
					res = tmp;
					tmp = tmp->_left;
				} else {
					tmp = tmp->_right;
				}
			}
			return const_iterator(tmp, _head);			
		}

		ft::pair<iterator, iterator> equal_range(const value& val){
			return ft::make_pair(lower_bound(val), uper_bound(val));
		}

		ft::pair<const_iterator, const_iterator> equal_range(const value& val) const{
			return ft::make_pair(lower_bound(val), uper_bound(val));
		}

		void deleteNode(p_node node){
			_node_alloc.destroy(node);
			_node_alloc.deallocate(node, 1);
			_size--;
		}

		void clear(p_node node){
			if (node == NULL){
				return;
			}
			clear(node->_right);
			clear(node->_left);
			deleteNode(node);
		}

		void clear_tree(){
			clear(_head);
			_head = NULL;
		}

		p_node getHead(){
			return _head;
		}

		void printBT(const std::string& prefix, const p_node nodeV, bool isLeft) const {
			std::cout << prefix;
			std::cout << (isLeft ? "├──" : "└──" );
			if (nodeV == NULL) {
				std::cout <<"\033[0;36m"<< "nil" << "\033[0m"<<std::endl;
				return ;
			}
			// print the value of the node
			if (nodeV->_color == BLACK)
				std::cout <<"\033[0;36m"<< nodeV->_value._first<<"\033[0m"<<std::endl;
			else
				std::cout <<"\033[0;31m"<< nodeV->_value._first << "\033[0m"<<std::endl;
			printBT( prefix + (isLeft ? "│   " : "    "), nodeV->_right, true);
			printBT( prefix + (isLeft ? "│   " : "    "), nodeV->_left, false);
		}
	};
}

#endif