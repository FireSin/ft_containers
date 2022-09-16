#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>

template<class T, class A = std::allocator<T>>
class vector<T>
{
	typedef				T					value_type;
	typedef				A					allocator_type;
	typedef typename	std::size_t			size_type;
	typedef typename	std::ptrdiff_t		difference_type;
	typedef				value_type&			reference;
	typedef				const value_type&	const_reference;
	typedef				value_type*			pointer;
	typedef				const value_type*	const_pointer;
private:
	value_type* 	_mas;
	size_type		_capasity;
	allocator_type	_alloc;
	size_type		_size;
public:
	vector(/* args */);
	~vector();

	bool	empty(){return this._arr == NULL;}
};

vector::vector(/* args */)
{
}

vector::~vector()
{
}

#endif