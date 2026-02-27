/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 18:59:50 by aldiaz-u          #+#    #+#             */
/*   Updated: 2026/02/27 12:30:50 by aldiaz-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

std::string*	split(string &line, char delimiter)
{
	int index = 0;
	string *date = new string[3];
	int pos = line.find(delimiter);
	while ( pos != static_cast<int>(string::npos))
	{
		date[index] = line.substr(0, pos);
		line.erase(0, pos + 1);
		index++;
		pos = line.find(delimiter);
	}
	date[index] = line;
	return (date);
}

bool	isValidDate(string &line, char separator)
{
	string date = line.substr(0, line.find(separator));
	string *splitDate;

	splitDate = split(date, '-');
	int day = atoi(splitDate[2].c_str());
	int	month = atoi(splitDate[1].c_str());
	int year = atoi(splitDate[0].c_str());
	delete[] splitDate;
	struct tm t = {};
	t.tm_mday = day;
	t.tm_mon = month - 1;
	t.tm_year = year - 1900;

	time_t result = mktime(&t);
	if (result == -1)
		return (false);
	return(t.tm_mday == day &&
			t.tm_mon == month - 1 &&
			t.tm_year == year - 1900);
}

int	invalidCharErr(string &line, size_t index, char separator, bool requireSpaces)
{
	if (!isdigit(line[index]) && line[index] != '-' && line[index] != '.' && line[index] != separator)
		return (1);
	if (line[index] == '-' && index + 1 < line.length() && !isdigit(line[index + 1]))
		return (1);
	if (requireSpaces && line[index] == separator && (index == 0 || index + 1 >= line.length() || line[index - 1] != ' ' || line[index + 1] != ' '))
		return (1);
	return (0);
}

void	checkInput(std::ifstream &readInput, string &line, string filename, char separator, bool requireSpaces, BitcoinExchange &bt)
{
	int	haveError;
	int	nline = 2;
	getline(readInput, line);
	while (getline(readInput, line))
	{
		int counter = 0;
		int points = 0;
		string date;
		float value;
		haveError = 0;
		for (size_t i = 0; i < line.length() ; i++)
		{
			if ((requireSpaces && i + 1 < line.length() && isspace(line[i]) && line[i + 1] == separator) || (i != 0 && isspace(line[i]) && line[i - 1] == separator))
				continue;
			if (invalidCharErr(line, i, separator, requireSpaces))
			{
				haveError = 1;
				break;
			}
			if (line[i] == separator)
				counter++;
			if (line[i] == '.')
				points++;
		}
		if (haveError == 0 && (counter == 0 || counter > 1 || points > 1))
			haveError = 1, cout << filename << " line: " << nline << " contains an inappropriate number of " << separator << " or . " << endl;
		date = line.substr(0, line.find(separator));
		value = strtof(line.substr(line.find(separator) + 1, line.length()).c_str(), NULL);
		if (haveError)
			cout << filename << " line: " << nline << " invalid format" << endl;
		else if (!isValidDate(line, separator))
			cout << filename << " line: " << nline << " invalid date " << endl;
		else
		{
			if (separator == ',')
				bt.addValue(date, value);
			else
			{
				if (value < 0)
					cout << "Error: not positive value" << endl;
				else if (value > 1000)
					cout << filename << " line: " << nline << " too large a number " << endl;
				else
					cout << std::fixed << std::setprecision(2) << date << " => " << value << " = " << static_cast<double>(value * bt.getValue(date)) << endl;
			}
		}
		nline++;
	}
}

int	main(int argc, char *argv[])
{
	(void)argv;
	try
	{
		string	line;
		BitcoinExchange bt;
		

		if (argc != 2)
			throw BitcoinExchange::InvalidFormat();
		std::ifstream readData("data.csv");
		checkInput(readData, line, "data.csv", ',', false, bt);
		std::ifstream readInput(argv[1]);
		checkInput(readInput, line, argv[1], '|', true, bt);
		readData.close();
		readInput.close();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	return (0);
}