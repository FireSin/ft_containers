#ifndef SET_HPP
#define SET_HPP

#include "rbTree.hpp"
#include <exception>

namespace ft{

	template<class Key, class Compare = std::less<Key>, class Allocator = std::allocator<Key> >
	class set{
		public:
			typedef				Key			                                key_type;
			typedef				Key                     		            value_type;
			typedef				std::size_t                                 size_type;
			typedef				std::ptrdiff_t                              difference_type;
			typedef				Compare                                     key_compare;
            typedef             Compare                                     value_compare;
			typedef				Allocator                                   allocator_type;
			typedef				value_type&                                 reference;
			typedef typename	Allocator::pointer                          pointer;
			typedef typename	Allocator::const_pointer                    const_pointer;			
			
			
			typedef typename		Allocator::template rebind<ft::Node<value_type> >::other		node_allocator_type;
			typedef					ft::rbTree<value_type, value_compare, node_allocator_type>		rbtree;
			typedef typename		rbtree::iterator												iterator;
			typedef typename		rbtree::const_iterator											const_iterator;
			typedef typename		rbtree::r_iterator												rev_iterator;
			typedef typename		rbtree::const_r_iterator										const_rev_iterator;
        private:
            rbtree      	_data;
            allocator_type  _alloc;
            key_compare     _compare;
            value_compare   _val_compare;

        public:
            explicit set(const Compare& comp = key_compare(), const Allocator& alloc = Allocator()): _data(), _alloc(alloc), _compare(comp), _val_compare(value_compare()){};
            template<class InputIt>
            set(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator()){
                _data.insert(first, last);
            }
            set(const set& other){*this = other;};
            ~set(){};
            
			rbtree&   operator=(const set& other){
				this->_data = other._data;
				return *this;
			}

			iterator					end(){return _data.end();}
			iterator					begin(){return _data.begin();}
			const_iterator				cend() const{return _data.cend();}
			const_iterator				cbegin() const{return _data.cbegin();}
			rev_iterator 				rbegin(){return _data.rbegin();}
			rev_iterator 				rend(){return _data.rend();}
			const_rev_iterator			const_rbegin() const{return _data.const_rbegin();}
			const_rev_iterator			const_rend() const{return _data.const_rend();}

            allocator_type 				get_allocator() const{return _alloc;}
			size_type					size() const{return _data._size;}
			bool						empty() const{return _data.empty();}
			size_type					max_size() const{return _data.max_size();}
			void						clear(){_data.clear_tree();}
			void						erase(iterator pos){_data.erase(pos);}
			void						erase(iterator first, iterator last){return _data.erase(first, last);}
			size_type					erase(const Key& key){return _data.erase(key);}
			void						swap(set& other){
				_data.swap(other._data);
				std::swap(_alloc, other._alloc);
				std::swap(_compare, other._compare);
				std::swap(_val_compare, other._val_compare);
			}
			iterator 					find(const key_type& key){return _data.find(key);}
			const_iterator 				find(const key_type& key) const{return _data.find(key);}
			size_type					count( const Key& key ) const{
				if (find(key).base() == NULL)
					return 0;
				return 1;
			}

			template<class InputIterator>
			void 						insert(InputIterator first, InputIterator last){_data.insert(first, last);}
			void 						insert (iterator position, const value_type& val){_data.insert(position, val);}
			ft::pair<iterator, bool>	insert(const value_type &val) {return _data.insert(val);}

			value_type& 				at(const key_type& key){
				iterator f = _data.find(key);
				if (f.base() == NULL){
					throw std::out_of_range("set::at");
				}
				return *f;
			}
			const value_type&			at( const Key& key ) const{
				const_iterator f = _data.find(key);
				if (f.base() == NULL){
					throw std::out_of_range("set::at");
				}
				return *f;
			}
		

			ft::pair<iterator, iterator>					equal_range(const Key& key){return _data.equal_range(key);}
			ft::pair<const_iterator, const_iterator>		equal_range( const Key& key ) const{return _data.equal_range(key);}
			iterator										lower_bound(const Key& key){return _data.lower_bound(key);}
			const_iterator									lower_bound(const Key& key)const{return _data.lower_bound(key);};
			iterator										upper_bound(const Key& key){return _data.upper_bound(key);}
			const_iterator									upper_bound(const Key& key)const{return _data.upper_bound(key);};

			key_compare 			key_comp() const{return _compare;}
			value_compare			value_comp() const{return _val_compare;};


			void printTree(){
				_data.printBT("ft", _data.getHead(), false);
			}
			template<class _Key, class _Compare, class _Alloc>
			friend bool operator==(const set<_Key, _Compare, _Alloc> & lhs,	const set<_Key, _Compare, _Alloc>& rhs);

			template<class _Key, class _Compare, class _Alloc>
			friend bool operator<(const set<_Key, _Compare, _Alloc> & lhs, const set<_Key, _Compare, _Alloc>& rhs);

    };
	template<class Key, class Compare, class Alloc>
	bool operator==(const set<Key, Compare, Alloc> & lhs, const set<Key, Compare, Alloc> & rhs){return (lhs._data == rhs._data);}

	template<class Key, class Compare, class Alloc>
	bool operator!=(const set<Key, Compare, Alloc> & lhs, const set<Key, Compare, Alloc> & rhs){return !(lhs == rhs);}

	template<class Key, class Compare, class Alloc>
	bool operator<(const set<Key, Compare, Alloc> & lhs, const set<Key, Compare, Alloc> & rhs){return (lhs._data < rhs._data);}

	template<class Key, class Compare, class Alloc>
	bool operator>(const set<Key, Compare, Alloc> & lhs, const set<Key, Compare, Alloc> & rhs){return (rhs < lhs);}

	template<class Key, class Compare, class Alloc>
	bool operator<=(const set<Key, Compare, Alloc> & lhs, const set<Key, Compare, Alloc> & rhs){return !(lhs > rhs);}

	template<class Key, class Compare, class Alloc>
	bool operator>=(const set<Key, Compare, Alloc> & lhs, const set<Key, Compare, Alloc> & rhs){return !(lhs < rhs);}

	template<class Key, class Compare, class Alloc>
	void swap(set<Key, Compare, Alloc> & lhs, set<Key, Compare, Alloc> & rhs){lhs.swap(rhs);}
}


#endif