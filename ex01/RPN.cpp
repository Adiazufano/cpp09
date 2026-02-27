#include "RPN.hpp"

RPN::RPN(){}

RPN::RPN(const RPN &other) : values(other.values){};

RPN&	RPN::operator=(const RPN &other)
{
	if (this != &other)
		values = other.values;
	return (*this);
}

RPN::~RPN(){};

void	RPN::addValue(double value)
{
	values.push(value);
}


void	RPN::calculate(char sign)
{
	if (values.size() < 2)//compreuba que haya la menos 2 numero evito exceso de operadores
		throw RPN::ExceptionInvalidValue();
	double firstValue;
	double secondValue;
	
	secondValue = values.top();
	values.pop();
	firstValue = values.top();
	values.pop();

	if (sign == '/' && secondValue == 0)
		throw RPN::ExceptionInvalidValue();
	double result;
	if (sign == '+')
		result = firstValue + secondValue;
	else if(sign == '-')
		result = firstValue - secondValue;
	else if(sign == '*')
		result = firstValue * secondValue;
	else if(sign == '/')
		result = firstValue / secondValue;
	values.push(result);
}

float	RPN::getValue()
{
	if (values.size() != 1)//compruebo que no uede mas de 1 numero al devolver el resulatdo evito exceso de numeros
		throw RPN::ExceptionInvalidValue();
	return values.top();
}