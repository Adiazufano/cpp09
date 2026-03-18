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
	
	cout << "after: ";
	for (size_t index = 0; index < 5; index++)
		cout << secuenceV[index] << " ";
	cout << "[...]" << endl;

	p.fordJohnson(secuenceV);
	p.fordJohnson(secuenceL);
	
	cout << "before: ";
	for (size_t index = 0; index < 5; index++)
		cout << secuenceV[index] << " ";
	cout << "[...]" << endl;

	return(0);
}