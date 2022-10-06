#include "stack.hpp"
#include <algorithm> //TODO tmp line
#include <list> //TODO tmp line
#include <vector> //TODO tmp line
#include <iostream>
#include <iomanip>

template <typename vector_type>
void print_info(vector_type &v) {
	std::cout << "size = " << v.size() << std::endl;
	std::cout << "cap = " << v.capacity() << std::endl;
	std::cout << "vector: ";
	for (size_t i = 0; i < v.size(); i++)
		std::cout << v[i] << " ";
	std::cout << std::endl << std::endl;
} //TODO delene func

class B {
public:
	char *l;
	int i;
	B():l(nullptr), i(1) {};
	B(const int &ex) {
		this->i = ex;
		this->l = new char('a');
	};
	virtual ~B() {
		delete this->l;
		this->l = nullptr;
	};
};

class A : public B {
public:
	A():B(){};
	A(const B* ex){
		this->l = new char(*(ex->l));
		this->i = ex->i;
		if (ex->i == -1) throw "n";
	}
	~A() {
		delete this->l;
		this->l = nullptr;
	};
};

template <typename T>
std::vector<int> insert_test_3(std::vector<T> vector) {
	std::vector<int> v;
	std::vector<int> tmp;
	tmp.assign(2600 * 1000, 1);
	vector.assign(4200 * 1000, 1);
	vector.insert(vector.end() - 1000 * 1000, tmp.begin(), tmp.end());
	v.push_back(vector[3]);
	v.push_back(vector.size());
	v.push_back(vector.capacity());

	std::unique_ptr<B> k2(new B(3));
	std::unique_ptr<B> k3(new B(4));
	std::unique_ptr<B> k4(new B(-1));
	std::vector<A> vv;
	std::vector<B*> v1;

	v1.push_back(&(*k2));
	v1.push_back(&(*k3));
	v1.push_back(&(*k4));
	try { vv.insert(vv.begin(), v1.begin(), v1.end()); }
	catch (...) {
		v.push_back(vv.size());
		v.push_back(vv.capacity());
	}
	print_info(v);
	return v;
}

template <typename T>
std::vector<int> insert_test_3(ft::vector<T> vector) {
	std::vector<int> v;
	ft::vector<int> tmp;
	tmp.assign(2600 * 1000, 1);
	vector.assign(4200 * 1000, 1);
	vector.insert(vector.end() - 1000 * 1000, tmp.begin(), tmp.end());
	v.push_back(vector[3]);
	v.push_back(vector.size());
	v.push_back(vector.capacity());

	std::unique_ptr<B> k2(new B(3));
	std::unique_ptr<B> k3(new B(4));
	std::unique_ptr<B> k4(new B(-1));
	ft::vector<A> vv;
	ft::vector<B*> v1;

	v1.push_back(&(*k2));
	v1.push_back(&(*k3));
	v1.push_back(&(*k4));
	try { vv.insert(vv.begin(), v1.begin(), v1.end()); }
	catch (...) {
		v.push_back(vv.size());
		v.push_back(vv.capacity());
	}
	print_info(v);
	return v;
}

int main() {
	// {
	//     ft::vector<int> v;
	//     insert_test_3(v);
	// }
	// {
	//     std::vector<int> v;
	//     insert_test_3(v);
	// }	
	ft::vector<int> st;
    ft::vector<int> st2;
    st.push_back(10);
    st.push_back(12);
	st.push_back(12);
	st.push_back(13);
	st2.push_back(10);
    st2.push_back(12);
    st2.push_back(12);
    std::cout << (st >= st2) << std::endl;

	return 0;
}
