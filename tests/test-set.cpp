#include "containers.hpp"
#include <set>

#include <string>
#include <iostream>
#include <cstddef>

void print_set(std::set<std::string>std_set, ft::set<std::string>ft_set)
{
	std::set<std::string>::iterator iter;
	ft::set<std::string>::iterator ft_iter;
	
	for (iter = std_set.begin(); iter != std_set.end(); iter++)
	{
		std::cout << "STD    " << *iter << std::endl;
	}
	std::cout << std::endl;
	for (ft_iter = ft_set.begin(); ft_iter != ft_set.end(); ++ft_iter)
	{
		std::cout << "FT     "  << *ft_iter << '\n';
	}
	
	std::cout << std::endl;
}

int main()
{
	std::cout << std::endl << "-------- set ----------" << std::endl;
	
	std::set<std::string> std_set;
	ft::set<std::string> ft_set;
	
	std_set.insert("alpha");
	std_set.insert("bravo");
	std_set.insert("charlie");
	std_set.insert("delta");
	
	ft_set.insert("alpha");
	ft_set.insert("bravo");
	ft_set.insert("charlie");
	ft_set.insert("delta");
	
	print_set(std_set, ft_set);
	
	std::cout << std::endl << "- Iterators: " << std::endl;
	std::cout << "begin: " << *(std_set.begin()) << " - \n";
//	std::cout << std_set.begin()->second << std::endl;
	std::cout << "begin: " << *(ft_set.begin()) << " - \n";
//	std::cout << ft_set.begin()->second << std::endl;
	std::cout << "end-1: " << *(--std_set.end()) << " - \n";
//	std::cout << (--std_set.end())->second << std::endl;
	std::cout << "end-1: " << *(--ft_set.end()) << " - \n";
//	std::cout << (--ft_set.end())->second << std::endl;
	std::cout << "rbegin: " << *(std_set.rbegin()) << " - \n";
//	std::cout << std_set.rbegin()->second << std::endl;
	std::cout << "rbegin: " << *(ft_set.rbegin()) << " - \n";
//	std::cout << ft_set.rbegin()->second << std::endl;
	std::cout << "rend-1: " << *(--std_set.rend()) << " - \n";
//	std::cout << (--std_set.rend())->second << std::endl;
	std::cout << "rend-1: " << *(--ft_set.rend()) << " - \n";
//	std::cout << (--ft_set.rend())->second << std::endl;
	
	std::cout  << std::endl << "- Capacity: " << std::endl;
	std::cout << "size: " << std_set.size() << std::endl;
	std::cout << "size: " << ft_set.size() << std::endl;
	std::cout << "empty: " << std_set.empty() << std::endl;
	std::cout << "empty: " << ft_set.empty() << std::endl;
	
	std::cout << std::endl << "- Modifiers: " << std::endl;
	std::cout << std::endl << "insert: " << std::endl;
	std_set.insert( "echo");
	ft_set.insert( "echo");
	print_set(std_set, ft_set);
	
	std::cout << "erase begin+1: " << std::endl;
	std_set.erase(++std_set.begin());
	ft_set.erase(++ft_set.begin());
	print_set(std_set, ft_set);
	
	std::cout << "swap: " << std::endl;
	std::set<std::string> std_set2;
	ft::set<std::string> ft_set2;
	std_set2.insert("foxtrot");
	ft_set2.insert("foxtrot");
	std_set.swap(std_set2);
	ft_set.swap(ft_set2);
	print_set(std_set, ft_set);
	
	std::cout << "clear: " << std::endl;
	std_set.clear();
	ft_set.clear();
	print_set(std_set, ft_set);
	std::cout << "size: " << std_set.size() << std::endl;
	std::cout << "size: " << ft_set.size() << std::endl;
	std_set.swap(std_set2);
	ft_set.swap(ft_set2);
	
	
	std::cout << std::endl << "- Observers: " << std::endl << std::endl;
	
	std::string std_p1 ("alpha");
	std::string std_p2 = *std_set.begin();
	std::string std_p3 = *std_set.rbegin();

	std::string ft_p1 ("alpha");
	std::string ft_p2 = *ft_set.begin();
	std::string ft_p3 = *ft_set.rbegin();

	std::cout << "value compare: " << std_set.value_comp()(std_p1, std_p2) << std::endl;
	std::cout << "value compare: " << ft_set.value_comp()(ft_p1, ft_p2) << std::endl;
	std::cout << "value compare: " << std_set.value_comp()(std_p1, std_p3) << std::endl;
	std::cout << "value compare: " << ft_set.value_comp()(ft_p1, ft_p3) << std::endl;
//
	std::cout << std::endl << "- Operations: " << std::endl << std::endl;
	
	print_set(std_set, ft_set);
	
	std::cout << "find charlie: " << *std_set.find("charlie") << std::endl;
	std::cout << "find charlie: " << *ft_set.find("charlie") << std::endl;
	
	std::cout << "count delta: " << std_set.count("delta") << std::endl;
	std::cout << "count delta: " << ft_set.count("delta") << std::endl;
	std::cout << "count gamma: " << std_set.count("gamma") << std::endl;
	std::cout << "count gamma: " << ft_set.count("gamma") << std::endl;

	std::cout << "lower bound charlie: " << *std_set.lower_bound("charlie") << std::endl;
	std::cout << "lower bound charlie: " << *ft_set.lower_bound("charlie") << std::endl;
	std::cout << "upper bound charlie: " << *std_set.upper_bound("charlie") << std::endl;
	std::cout << "upper bound charlie: " << *ft_set.upper_bound("charlie") << std::endl;

	std::cout << "equal_range e: " << *std_set.equal_range("echo").first << std::endl;
	std::cout << "equal_range e: " << *ft_set.equal_range("echo")._first << std::endl;
	
}