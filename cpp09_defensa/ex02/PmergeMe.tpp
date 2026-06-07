#ifndef PMERGEME_TPP
#define PMERGEME_TPP

#include "PmergeMe.hpp"
#include <algorithm>

// Busqueda binaria del sitio de insercion (cualquier iterador random-access)
template <typename Iterator>
Iterator PmergeMe::binarySearchInsertPos(Iterator begin, Iterator end, int value)
{
	while (begin < end)
	{
		Iterator mid = begin + (end - begin) / 2;
		if (*mid <= value)
			begin = mid + 1;
		else
			end = mid;
	}
	return begin;
}

// Ford-Johnson generico: vale para std::vector<int> y std::deque<int>
template <typename Container>
void PmergeMe::mergeInsertSort(Container& sequence)
{
	if (sequence.size() <= 1)
		return;

	// Si la cantidad es impar, apartamos el ultimo (suelto)
	int pendingImpar = -1;
	if (sequence.size() % 2 != 0)
	{
		pendingImpar = sequence.back();
		sequence.pop_back();
	}

	// Formamos parejas (usamos un vector temporal para reutilizar los helpers)
	std::vector<int> tmp(sequence.begin(), sequence.end());
	std::vector<std::pair<int, int> > pairs = createOrderedPairs(tmp);

	std::vector<int> aVec = extractA(pairs);
	std::vector<int> bVec = extractB(pairs);

	// Ordenamos recursivamente solo los grandes (la cadena principal)
	Container aNumbers(aVec.begin(), aVec.end());
	mergeInsertSort(aNumbers);

	// Realineamos los pequenos con los grandes ya ordenados
	aVec.assign(aNumbers.begin(), aNumbers.end());
	reorderBNumbersAndPairs(aVec, bVec, pairs);

	// La cadena empieza con los grandes; el primer pequeno entra gratis al frente
	Container mainChain = aNumbers;
	if (!bVec.empty())
		mainChain.insert(mainChain.begin(), bVec[0]);

	// Insertamos el resto de pequenos en orden de Jacobsthal
	std::vector<int> jacobSeq = createJacobsthalSequence(
		static_cast<int>(bVec.size()));
	std::vector<int> order = buildJacobsthalInsertionOrder(
		jacobSeq, static_cast<int>(bVec.size()));

	for (size_t i = 0; i < order.size(); ++i)
	{
		int idx = order[i];
		int valueToInsert = bVec[idx - 1];
		int targetNumLarger = pairs[idx - 1].first;

		// Buscamos solo hasta su pareja grande (el pequeno nunca va a su derecha)
		typename Container::iterator posLimit =
			std::find(mainChain.begin(), mainChain.end(), targetNumLarger);
		typename Container::iterator insertPos =
			binarySearchInsertPos(mainChain.begin(), posLimit, valueToInsert);
		mainChain.insert(insertPos, valueToInsert);
	}

	// Por ultimo, insertamos el suelto si lo habia
	if (pendingImpar >= 0)
	{
		typename Container::iterator insertPos =
			binarySearchInsertPos(mainChain.begin(), mainChain.end(), pendingImpar);
		mainChain.insert(insertPos, pendingImpar);
	}

	sequence = mainChain;
}

#endif
