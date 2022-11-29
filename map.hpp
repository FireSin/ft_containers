#ifndef MAP_HPP
#define MAP_HPP

#include "rbTree.hpp"
#include <exception>

namespace ft{

	template<class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<std::pair<const Key, T> > >
	class map{
		public:
			typedef				Key			                                key_type;
			typedef				T                                           mapped_type;
			typedef				ft::pair<const key_type, T>		            value_type;
			typedef				std::size_t                                 size_type;
			typedef				std::ptrdiff_t                              difference_type;
			typedef				Compare                                     key_compare;
			typedef				Allocator                                   allocator_type;
			typedef				value_type&                                 reference;
			typedef typename	Allocator::pointer                          pointer;
			typedef typename	Allocator::const_pointer                    const_pointer;
			// typedef    			ft::iterTree<Node<value_type> >             iterator;
			// typedef    			ft::iterTree<const Node<value_type> >       const_iterator;
			// typedef    			ft::reverse_iterTree<iterator>              rev_iterator;
			// typedef    			ft::reverse_iterTree<const iterator>        const_rev_iterator;
			
			
			class value_compare{
				template<class T1, class T2, class T3>
				friend class rbTree;
				template<class T1, class T2, class T3, class T4>
				friend class map;
				public:
					typedef     bool        result_type;
					typedef     value_type  first_argument_type;
					typedef     value_type  second_argument_type;
				protected:
					Compare comp;
					value_compare(): comp(Compare()){};
					value_compare(Compare& c): comp(c){};
					bool operator()( const value_type& lhs, const value_type& rhs ) const{
						return comp(lhs._first, rhs._first);
					};
			};
			
			typedef typename		Allocator::template rebind<ft::Node<value_type> >::other node_allocator_type;
			typedef					ft::rbTree<value_type, value_compare, node_allocator_type> rbtree;
			typedef typename		rbtree::iterator				iterator;
			typedef typename		rbtree::const_iterator			const_iterator;
			typedef typename		rbtree::r_iterator				rev_iterator;
			typedef typename		rbtree::const_r_iterator		const_rev_iterator;
        private:
            rbtree      	_data;
            allocator_type  _alloc;
            key_compare     _compare;
            value_compare   _val_compare;

        public:
            explicit map(const Compare& comp = key_compare(), const Allocator& alloc = Allocator()): _data(), _alloc(alloc), _compare(comp), _val_compare(value_compare()){};
            template<class InputIt>
            map(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator()){
                _data.insert(first, last);
            }
            map(const map& other){*this = other;};
            ~map(){};
            rbtree&   operator=(const map& other){
				this->_data = other._data;
				return *this;
			}

			iterator			end(){return _data.end();}
			iterator			begin(){return _data.begin();}
			const_iterator		cend() const{return _data.cend();}
			const_iterator		cbegin() const{return _data.cbegin();}
			rev_iterator 		rbegin(){return _data.rbegin();}
			rev_iterator 		rend(){return _data.rend();}
			const_rev_iterator	const_rbegin() const{return _data.const_rbegin();}
			const_rev_iterator	const_rend() const{return _data.const_rend();}

            allocator_type 		get_allocator() const{return _alloc;}
			size_type			size() const{return _data._size;}
			bool				empty() const{return _data.empty();}
			size_type			max_size() const{return _data.max_size();}
			void				clear(){_data.clear_tree();}
			iterator			erase(iterator pos){
				iterator tmp = pos;
				pos++;
				_data.erase(tmp);
				return pos;
			}


			void insert (iterator position, const value_type& val)
			{
				_data.insert(position, val);
			}

			ft::pair<iterator, bool> insert(const value_type &val) {
            	return _data.insert(val);
        	}

			mapped_type& operator[] (const key_type& key)
			{
				iterator f = find(key);

				if (f.base() == NULL)
					return insert(ft::make_pair(key, mapped_type()))._first->_second;
				return f->_second;
			}

			mapped_type& at(const key_type& key){
				iterator f = _data.find(value_type(key, mapped_type()));
				if (f.base() == NULL){
					throw std::out_of_range("map::at");
				}
				return (*f)._second;
			}

			const mapped_type& at( const Key& key ) const{
				const_iterator f = _data.find(value_type(key, T()));
				if (f.base() == NULL){
					throw std::out_of_range("map::at");
				}
				return (*f)._second;
			}

			iterator find(const key_type& key)
			{
				iterator f = _data.find(value_type(key, T()));
				return f;
			}



			void printTree(){
				_data.printBT("ft", _data.getHead(), false);
			}

    };
}


#endif