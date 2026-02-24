#ifndef BTC_HPP
#define BTC_HPP
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <map>
#include <cstdlib>
#define	INVALID_CHAR = 1

using std::exception;
using std::cout;
using std::endl;
using std::string;

class BitcoinExchange
{
	private:
		std::map<std::string, float> values;
	public: 
		void addValue(const std::string & date, float value);
		float getValue(const string& date) const;
		class InvalidFormat : public exception
		{
			const char* what() const throw()
			{
				return ("Error: invalid format");
			}
		};
};
#endif