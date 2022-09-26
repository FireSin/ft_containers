#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <string>
#include "iterator.hpp"
// #include <vector>

namespace ft{
	template<typename T, typename Allocator = std::allocator<T> >
	class vector
	{
	public:
		typedef				T										value_type;
		typedef				Allocator								allocator_type;
		typedef typename	std::size_t								size_type;
		typedef typename	std::ptrdiff_t							difference_type;
		typedef				value_type&								reference;
		typedef				const value_type&						const_reference;
		typedef				value_type*								pointer;
		typedef				const value_type*						const_pointer;
		typedef				ft::iterator<T>							iterator;
		typedef				ft::iterator<const T>					const_iterator;
		typedef				ft::reverse_iterator<iterator>			reverse_iterator;
		typedef				ft::reverse_iterator<const_iterator>	const_reverse_iterator;

		explicit vector(const Allocator& alloc = Allocator()): _mas(NULL), _capacity(0), _size(0), _alloc(alloc){}
		explicit vector(size_type count, const T& value = T(), const Allocator& alloc = Allocator()){
			if (count > this->_alloc.max_size())
				throw std::bad_alloc();
			this->_alloc = alloc;
			this->_mas = this->_alloc.allocate(count);
			this->_capacity = count;
			this->_size = count;
			for (size_type i = 0; i < count; i++)
				this->_mas[i] = value;
		}
		vector(const vector& other){*this = other;}
		~vector(){
			if (this->_mas){
				for (size_t i = 0; i < this->_size; i++)
					this->_alloc.destroy(&(this->_mas[i]));
				this->_alloc.deallocate(this->_mas, this->_capacity);
			}
		}

		vector& 		operator=(const vector& other){
			this->_capacity = other._capacity;
			if (this->_mas){
				for (size_t i = 0; i < this->_size; i++)
					this->_alloc.destroy(&(this->_mas[i]));
				this->_alloc.deallocate(this->_mas, this->_capacity);
			}
			this->_mas = this->_alloc.allocate(other._capacity);
			this->_size = other._size;
			for (size_type i = 0; i < this->_capacity ; i++)
				this->_mas[i] = other._mas[i];
			return *this;
		};
		value_type& 	operator[](size_type i){return this->_mas[i];}

		bool					empty(){return this->_mas == NULL;}
		size_type				size(){return this->_size;}
		size_type				capacity(){return this->_capacity;}
		reference				at(size_type n){
			if (n >= this->_size)
				throw std::bad_alloc();
			return this->_mas[n];
		}
		void 					reserve(std::size_t n){
			if (n > this->_alloc.max_size())
				throw std::bad_alloc();
			if (n < this->_capacity)
				return ;
			value_type *newMas = this->_alloc.allocate(n);
			for (std::size_t i = 0; i < this->_size; i++){
				newMas[i] = this->_mas[i];
				this->_alloc.destroy(&(this->_mas[i]));
			}
			this->_alloc.deallocate(this->_mas, this->_size);
			this->_mas = newMas;
			this->_capacity = n;
		}
		iterator				begin(){return iterator(this->_mas);}
		iterator				end(){return iterator(this->_mas + this->_size);}
		const_iterator			cbegin() const{
			return const_iterator(this->_mas);
		}
		const_iterator			cend() const{
			return const_iterator(this->_mas + this->_size);
		}
		reverse_iterator		rbegin(){return reverse_iterator(end());}
		reverse_iterator		rend(){return reverse_iterator(begin());}
		const_reverse_iterator	crbegin() const {return const_reverse_iterator(cend());}
		const_reverse_iterator	crend() const {return const_reverse_iterator(cbegin());}
		reference				front(){return *(this->begin());}
		const_reference			front() const{return *(this->cbegin());}
		reference				back(){return *(this->end() - 1);}
		const_reference			back() const{return *(this->cend() - 1);}
		pointer					data(){return this->_mas;}
		const_pointer			data() const{return this->_mas;};
		allocator_type			get_allocator() const{return allocator_type::allocator_type;}
		size_type				max_size() const{return allocator_type::max_size;}
		void					clear(){
			for (size_t i = 0; this->_size > 0 && i < _capacity; i++)
				this->_alloc.destroy(&(this->_mas[i]));
			this->_size = 0;
		}
		iterator				erase(iterator pos){
			size_type n = pos.base() - begin().base();
			for (size_type i = n; i < _size; i++)
			{
				_alloc.destroy(_mas + i);
				_alloc.construct(_mas + i, _mas[i + 1]);
			}
			_alloc.destroy(_mas + n);
			_size--;
			return (begin() + n); 				
		}
		iterator				erase(iterator first, iterator last){
			if(first == last)
				return last;
			if(last == end()){
				_size = first.base() - begin().base();
				for (iterator i = first; i != last; i++)
					_alloc.destroy(i.base());
				return end();
			}
			size_type f = first.base() - begin().base();
			size_type l = last.base() - begin().base();
			size_type n = l;
			size_type new_size = _size - (last.base() - first.base());
			for (size_type i = f; i < l; i++){
				_alloc.destroy(_mas + i);
				if (n < _size)
					_alloc.construct(_mas + i, _mas[n++]);
			}
			_size = new_size;
			return iterator(_mas + n - 1);
		}
		void					push_back(const T& value){
			if(_size == _capacity)
				reserve(_capacity == 0 ? 1 : _capacity * 2);
			_alloc.construct(_mas + _size, value);
			_size++;
		}
		void					pop_back(){
			if (_size > 0){
				_size--;
				_alloc.destroy(_mas + _size);
			}
		}
		iterator				insert(const_iterator pos, const T& value){
			if (pos == cend()){
				push_back(value);
				return end();
			}
			if(_size == _capacity)
				reserve(_capacity == 0 ? 1 : _capacity * 2);
			size_type n = pos.base() - begin().base();
			_alloc.construct(_mas + _size, _mas[_size - 1]);
			for (size_type i = _size - 1; i != n; i--){
				_alloc.destroy(_mas + i);
				_alloc.construct(_mas + i, _mas[i - 1]);
			}
			_alloc.construct(_mas + n, value);
			_size++;
			return (begin() + n);
		}
	private:
		value_type* 	_mas;
		size_type		_capacity;
		size_type		_size;
		allocator_type	_alloc;
	};

	template<class T, class Alloc>
	bool operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs ){
		if (lhs._size != rhs._size)
			return false;
		for (size_t i = 0; i < lhs._size; i++)
		{
			if(lhs[i] != rhs[i])
				return false;
		}
		return true;
	}

	template<class T, class Alloc>
	bool operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
		if (lhs == rhs)
			return false;
		return true;
	}

	// template<class T, class Alloc>
	// bool operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){

	// }

	// template<class T, class Alloc>
	// bool operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){

	// }

	// template<class T, class Alloc>
	// bool operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){

	// }

	// template<class T, class Alloc>

	// bool operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){

	// }
}


#endif