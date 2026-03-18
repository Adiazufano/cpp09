#include "PmergeMe.hpp"

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		cout << "Error: necesitas al menos 1 argumento" << endl;
		return(1);
	}
	/*PARSEO*/
	PmergeMe p;
	std::vector<long> secuenceV;
	std::list<long> secuenceL;
	try
	{
		secuenceV = p.addToVector(argv);
		secuenceL = p.addToList(argv);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	p.fordJohnson(secuenceV);
	p.fordJohnson(secuenceL);
	std::vector<long> temp = secuenceV;
	for (size_t index = 0; index < temp.size(); index++)
		cout << secuenceV[index] << endl;
	cout << endl;
	std::list<long>::iterator it;
	for (it = secuenceL.begin(); it != secuenceL.end() ; ++it)
		cout << *it << endl;
	return(0);
}