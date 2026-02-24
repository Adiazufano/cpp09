#ifndef BTC_HPP
#define BTC_HPP
#include <iostream>
#include <string>
#include <cstring>

using std::exception;
using std::cout;
using std::endl;
using std::string;

class BitcoinExchange
{
	public: 
		class InvalidFormat : public exception
		{
			const char* what() const throw()
			{
				return ("Error: invalid format");
			}
		};
};
#endif