#ifndef	RPN_HPP
#define RPN_HPP
#include <iostream>
#include <string>
#include <stack>

using std::string;
using std::cout;
using std::endl;
using std::stack;

class RPN
{
	private:
		stack<int> values;
	public:
		RPN();
		RPN(const RPN &other);
		RPN&	operator=(const RPN &other);
		~RPN();
};

#endif