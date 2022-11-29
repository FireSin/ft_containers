#include "stack.hpp"
#include <algorithm> //TODO tmp line
#include <list> //TODO tmp line
#include <vector> //TODO tmp line
#include <iostream>
#include <iomanip>

// template <typename vector_type>
// void print_info(vector_type &v) {
// 	std::cout << "size = " << v.size() << std::endl;
// 	std::cout << "cap = " << v.capacity() << std::endl;
// 	std::cout << "vector: ";
// 	for (size_t i = 0; i < v.size(); i++)
// 		std::cout << v[i] << " ";
// 	std::cout << std::endl << std::endl;
// } //TODO delene func

// class B {
// public:
// 	char *l;
// 	int i;
// 	B():l(nullptr), i(1) {};
// 	B(const int &ex) {
// 		this->i = ex;
// 		this->l = new char('a');
// 	};
// 	virtual ~B() {
// 		delete this->l;
// 		this->l = nullptr;
// 	};
// };

// class A : public B {
// public:
// 	A():B(){};
// 	A(const B* ex){
// 		this->l = new char(*(ex->l));
// 		this->i = ex->i;
// 		if (ex->i == -1) throw "n";
// 	}
// 	~A() {
// 		delete this->l;
// 		this->l = nullptr;
// 	};
// };

// template <typename T>
// std::vector<int> insert_test_3(std::vector<T> vector) {
// 	std::vector<int> v;
// 	std::vector<int> tmp;
// 	tmp.assign(2600 * 1000, 1);
// 	vector.assign(4200 * 1000, 1);
// 	vector.insert(vector.end() - 1000 * 1000, tmp.begin(), tmp.end());
// 	v.push_back(vector[3]);
// 	v.push_back(vector.size());
// 	v.push_back(vector.capacity());

// 	std::unique_ptr<B> k2(new B(3));
// 	std::unique_ptr<B> k3(new B(4));
// 	std::unique_ptr<B> k4(new B(-1));
// 	std::vector<A> vv;
// 	std::vector<B*> v1;

// 	v1.push_back(&(*k2));
// 	v1.push_back(&(*k3));
// 	v1.push_back(&(*k4));
// 	try { vv.insert(vv.begin(), v1.begin(), v1.end()); }
// 	catch (...) {
// 		v.push_back(vv.size());
// 		v.push_back(vv.capacity());
// 	}
// 	print_info(v);
// 	return v;
// }

// template <typename T>
// std::vector<int> insert_test_3(ft::vector<T> vector) {
// 	std::vector<int> v;
// 	ft::vector<int> tmp;
// 	tmp.assign(2600 * 1000, 1);
// 	vector.assign(4200 * 1000, 1);
// 	vector.insert(vector.end() - 1000 * 1000, tmp.begin(), tmp.end());
// 	v.push_back(vector[3]);
// 	v.push_back(vector.size());
// 	v.push_back(vector.capacity());

// 	std::unique_ptr<B> k2(new B(3));
// 	std::unique_ptr<B> k3(new B(4));
// 	std::unique_ptr<B> k4(new B(-1));
// 	ft::vector<A> vv;
// 	ft::vector<B*> v1;

// 	v1.push_back(&(*k2));
// 	v1.push_back(&(*k3));
// 	v1.push_back(&(*k4));
// 	try { vv.insert(vv.begin(), v1.begin(), v1.end()); }
// 	catch (...) {
// 		v.push_back(vv.size());
// 		v.push_back(vv.capacity());
// 	}
// 	print_info(v);
// 	return v;
// }

#include <utility>
#include <set>
#include <map>
#include "rbTree.hpp"
#include "pair.hpp"
#include "map.hpp"

int main() {
	// ft::rbTree<ft::pair<int, std::string> > a;
	// a.insert(ft::pair<int, std::string>(2, "asd"));
	// a.insert(ft::pair<int, std::string>(3, "bsd"));
	// a.insert(ft::pair<int, std::string>(4, "csd"));
	// a.insert(ft::pair<int, std::string>(5, "fsd"));
	// a.insert(ft::pair<int, std::string>(6, "dsd"));
	// a.insert(ft::pair<int, std::string>(7, "esd"));
	// a.insert(ft::pair<int, std::string>(8, "jsd"));
	// // a.erase(ft::pair<int, std::string>(2, "asd"));
	// a.printBT(" ", a.getHead(), false);
	// a.find(3);
	// ft::rbTree<ft::pair<int, std::string> >::const_iterator i = a.cbegin();
	// ft::rbTree<ft::pair<int, std::string> >::const_iterator ie = a.cend();
	// ft::rbTree<ft::pair<int, std::string> > b;
	// b = a;
	// b.printBT(" ", b.getHead(), false);
	// for (; i != ie; ++i){
	// 	std::cout << i.base()->_value._first << std::endl;
	// }
	ft::map<int, std::string> m;
	m.insert(ft::pair<int, std::string>(2, "asd"));
	m.insert(ft::pair<int, std::string>(3, "bsd"));
	m.insert(ft::pair<int, std::string>(4, "csd"));
	m.insert(ft::pair<int, std::string>(6, "dsd"));
	m.insert(ft::pair<int, std::string>(7, "esd"));
	m.insert(ft::pair<int, std::string>(8, "fsd"));
	m.insert(ft::pair<int, std::string>(9, "gsd"));
	ft::map<int, std::string>::iterator s = m.end();
	s--;
	m.printTree();
	m.insert(m.begin(), ft::pair<int, std::string>(5, "zsd"));
	m.printTree();
	// std::map<int, std::string> m;
	// m.insert(std::pair<int, std::string>(2, "asd"));
	// m.insert(std::pair<int, std::string>(3, "asd"));
	// m.insert(std::pair<int, std::string>(4, "asd"));
	// m.insert(std::pair<int, std::string>(5, "asd"));
	// m.insert(std::pair<int, std::string>(6, "asd"));
	// m.insert(std::pair<int, std::string>(7, "asd"));
	// m.insert(std::pair<int, std::string>(8, "asd"));
	// std::map<int, std::string>::iterator s = m.end();
	// m.insert(s, std::pair<int, std::string>(15, "zsd"));

	return 0;
}