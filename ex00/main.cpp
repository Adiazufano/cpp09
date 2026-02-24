#include "BitcoinExchange.hpp"

int	main(int argc, char *argv[])
{
	(void)argv;
	try
	{
		string filename;
		string extension;
		filename = argv[1];

		size_t found = filename.find_last_of(".");
		if (found != string::npos)
			extension = filename.substr(found);
		if (argc != 2 || extension != ".txt")
			throw BitcoinExchange::InvalidFormat();
		//comprobar si la extension del archivo que se pasa es txt

	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	return (0);
}