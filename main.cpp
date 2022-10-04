#include <iostream>
#include <string>
#include "vector.hpp"
#include "stack.hpp"
#include <vector>
#include <stack>

int main(){
	std::stack<int> st;
	st.push(1);
	st.push(2);
	std::cout << st.top() << std::endl;
	st.pop();
	std::cout << st.top() << std::endl;
	st.pop();
	std::cout << st.top() << std::endl;
	// st.pop();
	// std::cout << st.top() << std::endl;
	return 0;
}