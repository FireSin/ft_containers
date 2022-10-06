#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <string>
#include <memory>
#include "iterator.hpp"

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

	private:
		value_type* 	_mas;
		size_type		_capacity;
		size_type		_size;
		allocator_type	_alloc;

	public:

		explicit vector(const allocator_type& alloc = allocator_type()): _mas(NULL), _capacity(0), _size(0), _alloc(alloc){}
		explicit vector(size_type count, const T& value = T(), const allocator_type& alloc = allocator_type()){
			if (count > this->_alloc.max_size())
				throw std::bad_alloc();
			this->_alloc = alloc;
			this->_mas = this->_alloc.allocate(count);
			this->_capacity = count;
			this->_size = count;
			for (size_type i = 0; i < count; i++)
				this->_alloc.construct(this->_mas + i, value);
		}
		~vector(){
			for (size_t i = 0; i < _size; i++)
				_alloc.destroy(_mas + i);
			if (_capacity)
				_alloc.deallocate(_mas, _capacity);
		}

		vector(const vector& other): _capacity(0), _size(0){*this = other;}
		vector& 		operator=(const vector& other){
			if (this == &other)
				return *this;
			for (size_type i = 0; i < _size; i++)
				_alloc.destroy(_mas + i);
			this->_size = other._size;
			if(_capacity < _size){
				if (_capacity != 0)
					_alloc.deallocate(_mas, _capacity);
				_capacity = _size;
				_mas = _alloc.allocate(_capacity);
			}
			for (size_type i = 0; i < _size; i++)
				_alloc.construct(_mas + i, other[i]);
			return *this;
		};
		reference		operator[](size_type i){return this->_mas[i];}
		const_reference operator[](size_type pos) const{return *(cbegin() + pos);}

		bool					empty(){return begin() == end();}
		size_type				size(){return this->_size;}
		size_type				capacity(){return this->_capacity;}
		reference				at(size_type n){
			if (n >= this->_size)
				throw std::bad_alloc();
			return this->_mas[n];
		}
		const_reference			at(size_type pos) const{
			if (pos >= this->_size)
				throw std::out_of_range();
			return *(cbegin() + pos);
		}
		void 					reserve(size_type n){
			if (n > this->_alloc.max_size())
				throw std::bad_alloc();
			if (n < this->_capacity)
				return ;
			size_type i = 0;
			value_type *newMas = this->_alloc.allocate(n);
			if (!newMas)
				throw std::bad_alloc();
			try{
				for (; i < this->_size; i++){
					_alloc.construct(newMas + i, this->_mas[i]);
					this->_alloc.destroy(&(this->_mas[i]));
				}
				if (_capacity)
					this->_alloc.deallocate(this->_mas, this->_capacity);
				this->_mas = newMas;
				this->_capacity = n;
			}
			catch(...){
				for(int j = i - 1; j >= 0; j--)
					_alloc.destroy(&newMas[j]);
				_alloc.deallocate(newMas, n);
				throw std::bad_alloc();
			}
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
		const_pointer			data() const{return static_cast<const_pointer>(this->_mas);};
		allocator_type			get_allocator() const{return allocator_type::allocator_type;}
		size_type				max_size() const{return allocator_type::max_size;}
		void					clear(){
			for (size_t i = 0; i < _size; i++)
				this->_alloc.destroy(&(this->_mas[i]));
			this->_size = 0;
		}
		iterator				erase(iterator pos){
			size_type n = static_cast<size_type>(pos.base() - begin().base());
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
				_size = static_cast<size_type>(first.base() - begin().base());
				for (iterator i = first; i != last; i++)
					_alloc.destroy(i.base());
				return end();
			}
			size_type f = static_cast<size_type>(first.base() - begin().base());
			size_type l = static_cast<size_type>(last.base() - begin().base());
			size_type n = l;
			size_type new_size = _size - static_cast<size_type>(last.base() - first.base());
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
		iterator				insert(iterator pos, const T& value){
			size_type n = static_cast<size_type>(pos.base() - begin().base());
			if (pos > end())
				throw std::length_error("vector");
			insert(pos, 1, value);
			return (begin() + n);
		}
		iterator				insert(iterator pos, size_type count, const T& value){
			if (pos > end())
				throw std::length_error("vector");
			if (count == 0)
				return begin();
			size_type new_cap = _capacity;
			pointer	new_mas;
			size_type n = static_cast<size_type>(pos.base() - begin().base());
			size_type i = 0;
			while(_size + count > new_cap)
				new_cap = new_cap == 0 ? 1 : new_cap * 2;
			new_mas = _alloc.allocate(new_cap);
			try
			{
				for (; i < n; i++){
					_alloc.construct(new_mas + i, _mas[i]);
				}
				for (i = n; i < n + count; i++)
				{
					_alloc.construct(new_mas + i, value);
				}
				for (i = n + count; i < _size + count; i++)
				{
					_alloc.construct(new_mas + i, _mas[i - count]);
				}
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_mas + i);
				_alloc.deallocate(_mas, _capacity);
				_mas = new_mas;
				_capacity = new_cap;
				_size = _size + count;
			}
			catch(...)
			{
				for (size_type j = 0; j < i; j++)
				{
					_alloc.destroy(new_mas + j);
				}
				_alloc.deallocate(new_mas, new_cap);
				throw;
			}
			return begin() + count;	
		}
		template< class InputIt >
		iterator 				insert(iterator pos, InputIt first, InputIt last, typename enable_if<!is_integral<InputIt>::value>::type* = 0){
			if (pos > end())
				throw std::length_error("vector");
			size_type new_cap = _capacity;
			pointer	new_mas;
			size_type n = static_cast<size_type>(pos.base() - begin().base());
			size_type count = static_cast<size_type>(last.base() - first.base());
			size_type i = 0;
			if (count == 0)
				return begin();
			while(_size + count > new_cap)
				new_cap = new_cap == 0 ? 1 : new_cap * 2;
			new_mas = _alloc.allocate(new_cap);
			try
			{
				for (; i < n; i++)
				{
					_alloc.construct(new_mas + i, _mas[i]);
				}
				for (i = n; i < n + count; i++)
				{
					_alloc.construct(new_mas + i, *first);
					first++;
				}
				for (i = n + count; i < _size + count; i++)
				{
					_alloc.construct(new_mas + i, _mas[i - count]);
				}
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_mas + i);
				_alloc.deallocate(_mas, _capacity);
				_mas = new_mas;
				_capacity = new_cap;
				_size = _size + count;
			}
			catch(...)
			{
				for (size_type j = 0; j < i; j++)
				{
					_alloc.destroy(new_mas + j);
				}
				_alloc.deallocate(new_mas, new_cap);
				throw;
			}
			return begin() + n;
		}
		void					swap(vector& other){
			std::swap(this->_alloc, other._alloc);
			std::swap(this->_mas, other._mas);
			std::swap(this->_size, other._size);
			std::swap(this->_capacity, other._capacity);
		}
		void					assign(size_type count, const T& value){
			while(count > _capacity)
				reserve(_capacity == 0 ? 1 : _capacity * 2);
			for (size_t i = 0; i < _size; i++)
				_alloc.destroy(_mas + i);
			for (size_t i = 0; i < count; i++)
				_alloc.construct(_mas + i, value);
			_size = _capacity = count;						
		}
		template< class InputIt >
		void					assign(InputIt first, InputIt last, typename enable_if<!is_integral<InputIt>::value>::type* = 0){
			size_type count = static_cast<size_type>(last.base() - first.base());
			while(count > _capacity)
				reserve(_capacity == 0 ? 1 : _capacity * 2);
			for (size_type i = 0; i < _size; i++)
				_alloc.destroy(_mas + i);
			for (size_type i = 0; i < count; i++)
				_alloc.construct(_mas + i, *first++);
			_size = _capacity = count;
		}
		void					resize(size_type count, T value = T()){
			clear();
			if (_capacity < count)
				reserve(count);
			for (size_t i = 0; i < count; i++)
				_alloc.construct(_mas + i, value);
			_size = count;		
		}
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

	template<class T, class Alloc>
	bool operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
		if (lhs < rhs)
			return true;
		return false;
	}

	template<class T, class Alloc>
	bool operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
		if (lhs > rhs)
			return false;
		return true;
	}

	template<class T, class Alloc>
	bool operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
		if (lhs > rhs)
			return true;
		return false;
	}

	template<class T, class Alloc>

	bool operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
		if (lhs < rhs)
			return false;
		return true;
	}

	template< class T, class Alloc >
	void swap(vector<T,Alloc>& lhs, vector<T,Alloc>& rhs){
		lhs.swap(rhs);
	}
}


#endif