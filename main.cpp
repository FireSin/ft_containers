#include <iostream>
#include <string>
#include "vector.hpp"
#include <vector>

int main(){
	ft::vector<std::string> v1;
	v1.push_back("1");
	v1.push_back("2");
	v1.push_back("3");
	v1.push_back("4");
	v1.push_back("5");
	v1.push_back("6");
	v1.push_back("7");
	v1.push_back("8");
	v1.push_back("9");
	v1.push_back("0");
	std::cout << *(v1.insert(v1.cbegin() + 2, "HELLO")) << "\n\n";
	// std::vector<std::string> v2;
	// v2.push_back("1");
	// v2.push_back("2");
	// v2.push_back("3");
	// v2.push_back("4");
	// v2.push_back("5");
	// v2.push_back("6");
	// v2.push_back("7");
	// v2.push_back("8");
	// v2.push_back("9");
	// v2.push_back("0");
	// std::cout << *(v1.insert(v1.cbegin() + 12, "HELLO")) << "\n\n";
	// std::cout << *(v1.erase(v1.begin() + 1, v1.end() - 1)) << "\n\n";
	// v1.pop_back();
	// v1.pop_back();
	// v1.pop_back();
	// std::vector<std::string>::reverse_iterator it_std_begin = v2.rbegin();
	ft::vector<std::string>::iterator it_begin = v1.begin();
	ft::vector<std::string>::iterator it_end = v1.end();
	// ft::vector<std::string>::const_reverse_iterator it_rbegin = v1.crbegin();
	// std::cout << std::distance(v1.begin() + 5, v1.end()) << std::endl;
	// std::cout << std::distance(v1.begin(), v1.end()) << std::endl;

	// std::cout << *it_std_begin << std::endl;
	// std::cout << *it_rbegin << std::endl;
	// ft::vector<std::string>::const_reverse_iterator it_rend = v1.crend();
	// std::cout << std::distance(it_begin, it_end);
	// it_rbegin++;
	// std::cout << *it_rbegin << "\n";
	// std::cout << *it_rend << "\n";
	// for (ft::vector<std::string>::const_reverse_iterator i = it_rbegin; i > it_rend; i++)
	// {
	// 	std::cout << *i << "\n";
	// 	// *i = "2";
	// }
	for (ft::vector<std::string>::iterator i = it_begin; i != it_end; i++)
	{
		std::cout << *i << "\n";
	}

	return 0;
}