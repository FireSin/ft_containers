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
		typedef typename T::first_type  Key;
        typedef typename T::second_type Val;
        typedef T pair_type;
		
		T			_value;
		Node*		_parent;
		Node*		_left;
		Node*		_right;
		nodeColor	_color;

		Node(): _value(T()), _parent(NULL), _left(NULL), _right(NULL), _color(RED){}
		Node(const T& val): _value(val), _parent(NULL), _left(NULL), _right(NULL), _color(RED){}

		Node& operator=(const Node& other){
			this->_value = other._value;
			this->_parent = other._parent;
			this->_left = other._left;
			this->_right = other._right;
			this->_color = other._color;
			return *this;
		}

		Node* maximum(Node* lst){
			while (lst && lst->_right != NULL && lst->_right->_right != NULL)
				lst = lst->_right;
			return lst;
		}

		Node* minimum(Node* lst){
			while (lst && lst->_left != NULL && lst->_left->_left != NULL)
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
		typedef				ft::reverse_iterTree<node_type>				r_iterator;
		typedef				ft::reverse_iterTree<const node_type>		const_r_iterator;

		private:
			p_node			_head;
			key_compare		_key_comp;
			node_alloc		_node_alloc;
			size_type		_size;
			p_node			_nil;
		
		public:
			rbTree(const key_compare& comp = Compare(), const node_alloc& allc = node_alloc()):	_head(NULL), _key_comp(comp), _node_alloc(allc), _size(0), _nil(initNil()) {}

			rbTree(const rbTree& other): _head(NULL), _node_alloc(other._node_alloc), _key_comp(other._key_comp){
				*this = other;
			}
			rbTree& operator=(const rbTree& other){
				clear(_head);
				for (const_iterator i = other.cbegin(); i != other.cend(); i++){
					insert(i.base()->_value);
				}
				_size = other._size;
				return *this;
			}
			~rbTree(){
				clear_tree();
				deleteNode(_nil);
			}

			p_node	initNil(){
			p_node nil = node_alloc().allocate(1);
            nil->_left = NULL;
            nil->_right = NULL;
            nil->_parent = NULL;
            nil->_color = BLACK;
            return nil;
			}

			bool empty(){return _size == 0};

			size_type size(){return _size;}

			size_type max_size(){return node_alloc().max_size();}

			iterator begin(){return iterator(treeMin(_head), _head);}
			iterator end(){return iterator(_nil, _head);}

			r_iterator rbegin(){return r_iterator(treeMax(_head), _head);}
			r_iterator rend(){return r_iterator(_nil, _head);}

			const_iterator cbegin() const{return const_iterator(const_treeMin(_head), _head);}
			const_iterator cend() const{return const_iterator(_nil, _head);}

			p_node newNode(const value& val){
				p_node newNode = _node_alloc.allocate(1);
				_node_alloc.construct(newNode, node_type(val));
				newNode->_left = _nil;
				newNode->_right = _nil;
				newNode->_parent = _nil;
				return newNode;
			}

			bool is_Red(p_node node){
				if (node == NULL){
					return false;
				}
				return node->_color == RED;
			}

			p_node treeMin(p_node node){
				while (node->_left != _nil){
					node = node->_left;
				}
				return node;
			}

			p_node treeMax(p_node node){
				while (node->_right != _nil){
					node = node->_right;
				}
				return node;
			}

			const p_node const_treeMin(p_node node) const{
				while (node->_left != _nil){
					node = node->_left;
				}
				return node;
			}

			const p_node const_treeMax(p_node node) const{
				while (node->_right != _nil){
					node = node->_right;
				}
				return node;
			}

			void rotate_left(p_node node){
				p_node tmp = node->_right;
				node->_right = tmp->_left;
				if (tmp->_left != _nil){
					tmp->_left->_parent = node;
				}
				tmp->_parent = node->_parent;
				if (node->_parent == _nil){
					_head = tmp;
				} else if (node == node->_parent->_left){
					node->_parent->_left = tmp;
				} else {
					node->_parent->_right = tmp;
				}
				tmp->_left = node;
				node->_parent = tmp;
			}

			void rotate_right(p_node node){
				p_node tmp = node->_left;
				node->_left = tmp->_right;
				if (tmp->_right != _nil){
					tmp->_right->_parent = node;
				}
				tmp->_parent = node->_parent;
				if (node->_parent == _nil){
					_head = tmp;
				} else if (node == node->_parent->_right){
					node->_parent->_right = tmp;
				} else {
					node->_parent->_left = tmp;
				}
				tmp->_right = node;
				node->_parent = tmp;
			}

			void balance(p_node node){
               while (node->_parent->_color == RED){
					if (node->_parent == node->_parent->_parent->_left){
						p_node tmp = node->_parent->_parent->_right;
						if (tmp->_color == RED){
							node->_parent->_color = BLACK;
							tmp->_color = BLACK;
							node->_parent->_parent->_color = RED;
							node = node->_parent->_parent;
						} else {
							if(node == node->_parent->_right){
								node = node->_parent;
								rotate_left(node);
							}
							node->_parent->_color = BLACK;
							node->_parent->_parent->_color = RED;
							rotate_right(node->_parent->_parent);
						}
					} else {
						p_node tmp = node->_parent->_parent->_left;
						if (tmp->_color == RED){
							node->_parent->_color = BLACK;
							tmp->_color = BLACK;
							node->_parent->_parent->_color = RED;
							node = node->_parent->_parent;
						} else {
							if(node == node->_parent->_left){
								node = node->_parent;
								rotate_right(node);
							}
							node->_parent->_color = BLACK;
							node->_parent->_parent->_color = RED;
							rotate_left(node->_parent->_parent);
						}
					}
					_head->_color = BLACK;
			   }
			   
			}

			pair<p_node, bool> insert_to_tree(const value& key, p_node* head){
				p_node parent = NULL;
				p_node tmp = *head;
				if (*head == NULL){
					*head = newNode(key);
					(*head)->_color = BLACK;
					_size++;
					return ft::make_pair(*head, true);
				}
				while (tmp != _nil){
					if (_key_comp(key, tmp->_value)){
						parent = tmp;
						tmp = tmp->_left;
					} else if (_key_comp(tmp->_value, key)){
						parent = tmp;
						tmp = tmp->_right;
					} else {
						return ft::make_pair(*head, false);
					}
				}
				tmp = newNode(key);
				tmp->_parent = parent;
				if (tmp->_value != _head->_value){
					if (_key_comp(key, parent->_value)){
						parent->_left = tmp;
					} else if (_key_comp(parent->_value, key)){
						parent->_right = tmp;
					}
				}
				balance(tmp);
				_size++;
				return ft::make_pair(tmp, true);
			}

			pair<iterator, bool> insert(const value& val){
				ft::pair<p_node, bool> tmp = insert_to_tree(val, &_head);
				return ft::make_pair(iterator(tmp._first, _head), tmp._second);
			}

			iterator insert(iterator hint, const value& val){
				if (hint == lower_bound(val)){
					p_node node = newNode(val);
					hint.base()->_right = node;
					node->_parent = hint.base();
					balance(node);
					return iterator(node, _head);
				}
				ft::pair<p_node, bool> tmp  = insert_to_tree(val, &_head);
				return iterator(tmp._first, _head);
			}

			template <class InputIterator>
			void insert(InputIterator first, InputIterator last){
				for (InputIterator i = first; i != last; i++){
					insert(i.base()->_value);
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


			void transplant(p_node u, p_node v){
				if (u->_parent == _nil){
					_head = v;
				} else if (u == u->_parent->_left){
					u->_parent->_left = v;
				} else {
					u->_parent->_right = v;
				}
				v->_parent = u->_parent;
			}
    
			void eraseNode(p_node node){
				p_node tmpX = NULL;
				p_node tmpY = node;
				nodeColor orig_tmp = tmpY->_color;
				if (node->_left == _nil){
					tmpX = node->_right;
					transplant(node, node->_right);
				} else if (node->_right == _nil){
					tmpX = node->_left;
					transplant(node, node->_left);
				} else {
					tmpY = treeMin(node->_right);
					orig_tmp = tmpY->_color;
					tmpX = tmpY->_right;
					if (tmpY->_parent == node){
						tmpX->_parent = tmpY;
					} else {
						transplant(tmpY, tmpY->_right);
						tmpY->_right = node->_right;
						tmpY->_right->_parent = tmpY;
					}
					transplant(node, tmpY);
					tmpY->_left = node->_left;
					tmpY->_left->_parent = tmpY;
					tmpY->_color = node->_color;
				}
				if (orig_tmp == BLACK){
					balanceEr(tmpX);
				}
				deleteNode(node);
			}

			void balanceEr(p_node del){
				while (del != _head && del->_color == BLACK){
					if (del == del->_parent->_left){
						p_node tmp = del->_parent->_right;
						if (tmp->_color == RED){
							tmp->_color = BLACK;
							del->_parent->_color = RED;
							rotate_left(del->_parent);
							tmp = del->_parent->_right;
						}
						if (tmp->_left->_color == BLACK && tmp->_right->_color == BLACK){
							tmp->_color = RED;
							del = del->_parent;
						} else {
							if (tmp->_right->_color == BLACK){
								tmp->_left->_color = BLACK;
								tmp->_color = RED;
								rotate_right(tmp);
								tmp = del->_parent->_right;
							}
						tmp->_color = del->_parent->_color;
						del->_parent->_color = BLACK;
						rotate_left(del->_parent);
						del = _head;
						}
					} else {
						p_node tmp = del->_parent->_left;
						if (tmp->_color == RED){
							tmp->_color = BLACK;
							del->_parent->_color = RED;
							rotate_right(del->_parent);
							tmp = del->_parent->_left;
						}
						if (tmp->_right->_color == BLACK && tmp->_left->_color == BLACK){
							tmp->_color = RED;
							del = del->_parent;
						} else {
							if (tmp->_left->_color == BLACK){
								tmp->_right->_color = BLACK;
								tmp->_color = RED;
								rotate_left(tmp);
								tmp = del->_parent->_left;
							}
							tmp->_color = del->_parent->_color;
							del->_parent->_color = BLACK;
							rotate_right(del->_parent);
							del = _head;
						}
					}
				}
				del->_color = BLACK;
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
				// p_node res;
				while (tmp != NULL){
					if (_key_comp(key, tmp->_value)){
						// p_node res = tmp;
						tmp = tmp->_left;
					} else if (!_key_comp(tmp->_value, key)){
						// p_node res = tmp;
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
				if (node != _nil){
					_node_alloc.destroy(node);
				}
				_node_alloc.deallocate(node, 1);
				_size--;
			}

			void clear(p_node node){
				if (node == NULL || node == _nil){
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
				if (nodeV == _nil) {
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