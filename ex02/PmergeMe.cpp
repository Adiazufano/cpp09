#include "PmergeMe.hpp"

PmergeMe::PmergeMe(){}

PmergeMe::PmergeMe(const PmergeMe& other)
{
	(void)other;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
	(void)other;
	return(*this);
}

std::vector<long> PmergeMe::addToVector(char *argv[])
{
	std::vector<long> secuenceV;
	
	for (long index = 1; argv[index] != NULL; index++)
	{
		int count = 0;
		std::string split(argv[index]);
		std::stringstream ss(split);
		long num;
		while (ss >> num)
		{
			if (num < 0)
				throw PmergeMe::ExceptionIvalidArg();
			secuenceV.push_back(num);
			count++;
		}
		if (!ss.eof() || count == 0)
			throw PmergeMe::ExceptionIvalidArg();
	}
	return(secuenceV);
}

std::list<long> PmergeMe::addToList(char *argv[])
{
	std::list<long> secuenceL;

	for (long index = 1; argv[index] != NULL; index++)
	{
		std::string split(argv[index]);
		std::stringstream ss(split);
		long num;
		while (ss >> num)
		{
			if (num < 0)
				throw PmergeMe::ExceptionIvalidArg();
			secuenceL.push_back(num);
		}
		if (!ss.eof())
			throw PmergeMe::ExceptionIvalidArg();
	}
	return(secuenceL);
}

std::vector<size_t>	PmergeMe::jacobsthal(size_t n)
{
	std::vector<size_t> seq;
	size_t a = 1;
	size_t b = 3;
	seq.push_back(1);//el primer termino de la secuencia siempre es 1 y el siguiente 3
	while (b < n)
	{
		seq.push_back(b);
		size_t tmp = b + 2 * a;
		a = b;
		b = tmp;
	}
	return (seq);
}

PmergeMe::~PmergeMe(){}