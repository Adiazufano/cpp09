#include "RPN.hpp"

bool	isSign(char c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/')
		return (true);
	return (false);
}

void	tokenizer(string &arg, RPN &rpn)
{
	stringstream ss(arg);
	string value;

	while (ss >> value)
	{
		if (isSign(value[0]) && value[1] == '\0')
		{
			rpn.calculate(value[0]);
			continue;
		}
		double	num = atof(value.c_str());
		if (num < 0 || num > 9)
			throw RPN::ExceptionInvalidValue();
		else
			rpn.addValue(static_cast<double>(num));
	}
	cout << std::fixed << std::setprecision(2) << rpn.getValue()  << endl;
}

int	main(int argc, char *argv[])
{
	try
	{
		RPN rpn;
		if (argc != 2)
			throw RPN::ExcepitionNumberArguments();
		string arg = argv[1];
		for (size_t index = 0; index < arg.length(); index++)
		{
			if (isspace(arg[index]))
				continue;
			if (!isdigit(arg[index]) && !isSign(arg[index]))
				throw RPN::ExceptionInvalidChar();
		}
		tokenizer(arg, rpn);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	return (0);
}