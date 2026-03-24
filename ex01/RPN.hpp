#ifndef	RPN_HPP
#define RPN_HPP
#include <iostream>
#include <string>
#include <stack>
#include <exception>
#include <sstream>
#include <stdlib.h>
#include <iomanip>

using std::string;
using std::cout;
using std::endl;
using std::stack;
using std::exception;
using std::stringstream;

class RPN
{
	private:
		stack<double> values;
	public:
		RPN();
		RPN(const RPN &other);
		RPN&	operator=(const RPN &other);
		~RPN();	
		void	addValue(double value);
		void	calculate(char sign);
		float	getValue();

	class	ExcepitionNumberArguments : public exception
	{
		const char* what() const throw()
		{
			return ("Exception: the number of arguments must be 1.");
		}
	};

	class ExceptionInvalidChar : public exception
	{
		const char* what() const throw()
		{
			return ("Excepion: exception among the past values there is at least one invalid character");
		}
	};

	class ExceptionInvalidValue : public exception
	{
		const char* what() const throw()
		{
			return ("Excpetion: Invalid value passed as argument exception ");
		}
	};
};

#endif