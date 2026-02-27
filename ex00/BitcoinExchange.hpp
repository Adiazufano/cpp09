#ifndef BTC_HPP
#define BTC_HPP
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <map>
#include <cstdlib>
#include <iterator>
#include <iomanip>
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
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &other);
		BitcoinExchange&	operator=(const BitcoinExchange &other);
		~BitcoinExchange();
		void addValue(const std::string &date, float value);
		float getValue(const string& date) const;
		std::map<string, float>	getMap();
		void	print();
		class InvalidFormat : public exception
		{
			const char* what() const throw()
			{
				return ("Error: invalid format");
			}
		};
};
#endif