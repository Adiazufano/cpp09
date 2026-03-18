#ifndef PMERGEME_HPP
#define PMERGEME_HPP
#include <iostream>
#include <string.h>
#include <vector>
#include <stdlib.h>
#include <list>
#include <sstream>
#include <exception>
#include <utility>

using std::cout;
using std::endl;
using std::pair;

class PmergeMe
{
	public:
		PmergeMe();
		std::vector<long> addToVector(char *argv[]);
		std::list<long> addToList(char *argv[]);
		~PmergeMe();
		template<typename T>
		void binaryInsert(std::vector<T>& sorted, T value)
		{
			typename std::vector<T>::iterator pos = std::lower_bound(sorted.begin(), sorted.end(), value);
			sorted.insert(pos, value);
		}
		template<typename T>
		void binaryInsert(std::list<T>& sorted, T value)
		{
			typename std::list<T>::iterator pos = std::lower_bound(sorted.begin(), sorted.end(), value);
			sorted.insert(pos, value);
		}
		std::vector<size_t> jacobsthal(size_t n);
		template<typename T>
		void	fordJohnson(std::vector<T>& secuenceV)
		{
			size_t size = secuenceV.size();
			if (size <= 1)
				return;
			T leftover = T();
			bool hasLeftover = false;
			if (secuenceV.size() % 2 != 0)
			{
				leftover = secuenceV[size - 1];
				hasLeftover = true;
				secuenceV.pop_back();
				size = secuenceV.size();
			}
			//se crean pares y se ordenan
			std::vector<pair<T,T> > vectorX;
			for (size_t index = 0; index < size ; index+=2)
			{
				pair<T, T> p = std::make_pair(secuenceV[index], secuenceV[index + 1]);
				if (p.first > p.second)
					std::swap(p.first, p.second);
				vectorX.push_back(p);
			}
			//se extraen los mayores y se ordenan
			std::vector<T> mainChain;
			for (size_t index = 0; index < vectorX.size(); index++)
				mainChain.push_back(vectorX[index].second);
			
			fordJohnson(mainChain);
			/*Insertar el primer menor (par del menor mainchain[0])
			  encontrar e par cuyo mayor es mainChain[0]*/
			std::vector<T> pending;
			for (size_t index = 0; index < vectorX.size(); index++)
			{
				for (size_t j = 0; j < vectorX.size(); j++)
				{
					if (vectorX[j].second == mainChain[index] && vectorX[j].first != -1)
					{
						pending.push_back(vectorX[j].first);
						vectorX[j].first = -1;
						break;
					}
				}
			}
			//el primero siempre se inserta al principio
			mainChain.insert(mainChain.begin(), pending[0]);
			//insertar el resto con Jacobsthal
			std::vector<size_t> jSeq = jacobsthal(pending.size());
			std::vector<bool> inserted(pending.size(), false);
			inserted[0] = true;
			for (size_t j = 0; j < jSeq.size(); j++)
			{
				size_t idx= jSeq[j]  - 1;
				if (idx < pending.size() && !inserted[idx])
				{
					binaryInsert(mainChain, pending[idx]);
					inserted[idx] = true;
				}
			}
			//insertar lso que quedaron sin insertar en orden
			for (size_t index = 0; index < pending.size(); index++)
			{
				if (!inserted[index])
					binaryInsert(mainChain, pending[index]);
			}
			//insertar el leftover
			if (hasLeftover)
				binaryInsert(mainChain, leftover);
			secuenceV = mainChain;
		}
		template <typename T>
		T getListValue(std::list<T> l, long index)
		{
			typename std::list<T>::iterator it = l.begin();
			if (index  < 0 || index >= static_cast<long>(l.size()))
				throw std::out_of_range("indeice fuera de rango");
			for (int i = 0; i < index; i++)
				++it;
			return (*it);
		}
		template <typename T>
		void setListValue(std::list<T> l, long index, T value)
		{
			typename std::list<T>::iterator it = l.begin();
			if (index  < 0 || index >= static_cast<long>(l.size()))
				throw std::out_of_range("indeice fuera de rango");
			for (int i = 0; i < index; i++)
				++it;
			*it = value;
		}
		template<typename T>
		void	fordJohnson(std::list<T>& secuenceL)
		{
			size_t size = secuenceL.size();
			if (size <= 1)
				return ;
			T leftover = T();
			bool hasLeftover = false;
			if (secuenceL.size() % 2 != 0)
			{
				leftover = getListValue(secuenceL, size - 1);
				hasLeftover = true;
				secuenceL.pop_back();
				size = secuenceL.size();
			}
			//crear pares y ordenarlos
			typename std::list<std::pair<T, T> > listX;
			for (size_t index = 0; index < size; index += 2)
			{
				std::pair<T, T> p = std::make_pair(getListValue(secuenceL, index), getListValue(secuenceL, index + 1));
				if (p.first > p.second)
					std::swap(p.first, p.second);
				listX.push_back(p);
			}
			//extraer mayores y ordenarlos
			std::list<T> mainChain;
			for (size_t index = 0; index < listX.size(); index++)
			{
				std::pair<T, T> value = getListValue(listX, index);
				mainChain.push_back(value.second);
			}
			fordJohnson(mainChain);
			std::list<T> pending;
			std::vector<bool> marked(listX.size(), false);
			for (size_t index = 0; index < mainChain.size(); index++)
			{
				T mainChainValue = getListValue(mainChain, index);
				for (size_t j = 0; j < listX.size(); j++)  // Busca en listX
				{
					std::pair<T, T> vectorXValue = getListValue(listX, j);
					if (vectorXValue.second == mainChainValue && !marked[j])
					{
						pending.push_back(vectorXValue.first);
						marked[j] = true;
						break;
					}
				}
			}
			mainChain.insert(mainChain.begin(), pending.front());
			std::vector<size_t> jSeq = jacobsthal(pending.size() - 1);  
			std::vector<bool> inserted(pending.size(), false);
			inserted[0] = true;  
			for (size_t j = 0; j < jSeq.size(); j++)
			{
				size_t idx = jSeq[j];
				if (idx < pending.size() && !inserted[idx])
				{
					binaryInsert(mainChain, getListValue(pending, idx));
					inserted[idx] = true;
				}
			}
			//insertar lso que quedaron sin insertar en orden
			for (size_t index = 0; index < pending.size(); index++)
			{
				if (!inserted[index])
					binaryInsert(mainChain, getListValue(pending, index));
			}
			//insertar el leftover
			if (hasLeftover)
				binaryInsert(mainChain, leftover);
			secuenceL = mainChain;
		}
	class ExceptionIvalidArg : public std::exception
	{
		const char* what() const throw()
		{
			return ("Exception: inavlid arg");
		}
	};
};
#endif