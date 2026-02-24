/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 18:59:50 by aldiaz-u          #+#    #+#             */
/*   Updated: 2026/02/24 19:12:44 by aldiaz-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"


bool	isValidDate(int day, int month, int year)
{
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

void	checkInput(std::ifstream &readInput, string &line, string filename, char separator, bool requireSpaces, BitcoinExchange &b)
{
	int	haveError;
	int	nline = 1;
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
		else
		{
			b.addValue(date, value);
		}
		nline++;
	}
}

/* void	checkDataCsv(std::ifstream &readInput, string &line, string filename)
{
	int	haveError;
	int	nline = 0;
	string extension;
	getline(readInput, line);
	while (getline(readInput, line))
	{
		int counter = 0;
		int points = 0;
		haveError = 0;
		for (size_t i = 0; i < line.length() ; i++)
		{
			if (!isdigit(line[i]) && (line[i] != '-' && line[i] != ',' && line[i] != '.'))
			{
				haveError++;
				cout << filename << " line: " << nline << " contain invalid chars" << endl;
				break;
			}
			else if (i + 1 < line.length() && (line[i] == '-' && !isdigit(line[i + 1])))
			{
				haveError++;
				cout << filename << " line: " << nline << " contain invalid chars" << endl;
				break;
			}
			if (line[i] == ',')
				counter++;
			if (line[i] == '.')
				points++;
		}
		if (haveError == 0 && (counter == 0 || counter > 1 || points > 1))
		{
			haveError++;
			cout << filename << "line: " << nline << " contains an inappropriate number of , or . " << endl;
		}
		if (haveError == 0)
			cout << line << endl;
		nline++;
	}
} */


int	main(int argc, char *argv[])
{
	(void)argv;
	try
	{
		string	line;
		BitcoinExchange bt;
		

		if (argc != 2)
			throw BitcoinExchange::InvalidFormat();
		std::ifstream readInput(argv[1]);
		checkInput(readInput, line, argv[1], '|', true, bt);
		cout << endl;
		std::ifstream readData("data.csv");
		checkInput(readData, line, "data.csv", ',', false, bt);
		readInput.close();
		readData.close();
		string t = "2022-03-29,47115.93";
		float f = bt.getValue("2022-03-29");
		cout << f << endl;
		/* int i = t.find(",");
		string k = t.substr(0, i);
		string k2 = t.substr(i + 1, k.length());
		string date[3] = split
		cout << k2 << endl; */
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	return (0);
}