/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 18:59:57 by aldiaz-u          #+#    #+#             */
/*   Updated: 2026/03/24 15:00:25 by aldiaz-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(){};

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) : values(other.values){}

BitcoinExchange&	BitcoinExchange::operator=(const BitcoinExchange &other)
{
	if (this != &other)
		values = other.values;
	return  (*this);
}

BitcoinExchange::~BitcoinExchange(){}

void	BitcoinExchange::addValue(const string& date, float value)
{
	values[date] = value;
}

float BitcoinExchange::getValue(const string& date) const
{
	std::map<string, float>::const_iterator it = values.lower_bound(date);

	if (it != values.end() && it -> first == date)
		return it -> second;
	if (it == values.begin())
		return -1;
	--it;
	return it -> second;
}

std::map<string, float>	BitcoinExchange::getMap()
{
	return (values);
}

void	BitcoinExchange::print()
{
	for (std::map<string, float>::iterator it = values.begin(); it != values.end(); ++it)
	{
		cout << "Key: " << it -> first << " Value: " << it -> second << endl;
	}
}