#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include "iterator.hpp"

namespace ft{
	template<typename T, typename Allocator = std::allocator<T> >
	class vector
	{
	public:
		typedef				T					value_type;
		typedef				Allocator			allocator_type;
		typedef typename	std::size_t			size_type;
		typedef typename	std::ptrdiff_t		difference_type;
		typedef				value_type&			reference;
		typedef				const value_type&	const_reference;
		typedef				value_type*			pointer;
		typedef				const value_type*	const_pointer;
		typedef				ft::vectorIter<T>	iterator;

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

		vector& 	operator=(const vector& other){
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
		value_type& operator[](size_type i){return this->_mas[i];}

		bool		empty(){return this->_mas == NULL;}
		size_type	size(){return this->_size;}
		size_type	capacity(){return this->_capacity;}
		value_type&	at(size_type n){
			if (n >= this->_size)
				throw std::bad_alloc();
			return this->_mas[n];
		}
		void 		reserve(std::size_t n){
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
		iterator	begin(){return iterator(this->_mas);}
		iterator	end(){return iterator(this->_mas + this->_size);}
		void		insert(T val, int n){this->_mas[n] = val;}

	private:
		value_type* 	_mas;
		size_type		_capacity;
		size_type		_size;
		allocator_type	_alloc;
	};
}

#endif