#include "PmergeMe.hpp"

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		cout << "Error: necesitas al menos 1 argumento" << endl;
		return(1);
	}
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
		return 1;
	}
	
	cout << "before: ";
	for (size_t index = 0; index < secuenceV.size() ; index++)
		cout << secuenceV[index] << " ";
	cout << endl;

	clock_t tStartV = clock();
	p.fordJohnson(secuenceV);
	double timeV = (double)(clock() - tStartV) / CLOCKS_PER_SEC * 1000;

	clock_t tStartL = clock();
	p.fordJohnson(secuenceL);
	double timeL = (double)(clock() - tStartL) / CLOCKS_PER_SEC * 1000;
	
	cout << "after: ";
	for (size_t index = 0; index < secuenceV.size() ; index++)
		cout << secuenceV[index] << " ";
	cout << endl;

	cout << "Time to process a range of " << secuenceV.size() << " elements with std::vector: " << timeV << "ms" << endl;
	cout << "Time to process a range of " << secuenceV.size() << " elements with std::list: " << timeL << "ms" << endl;

	return(0);
}