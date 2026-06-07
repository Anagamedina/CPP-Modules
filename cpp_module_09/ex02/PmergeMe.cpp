#include "PmergeMe.hpp"

#include <algorithm>
#include <cctype>
#include <iostream>
#include <climits>
#include <ostream>
#include <sys/time.h>

PmergeMe::PmergeMe() : timeVector_(0), timeList_(0), sizeSequence_(-1)
{
}

PmergeMe::PmergeMe(const PmergeMe& other)
{
	*this = other;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
	if (this != &other)
	{
		vectorInteger_ = other.vectorInteger_;
		listInteger_ = other.listInteger_;
		timeVector_ = other.timeVector_;
		timeList_ = other.timeList_;
		sizeSequence_ = other.sizeSequence_;
	}
	return *this;
}

PmergeMe::~PmergeMe()
{
}

const std::vector<int>& PmergeMe::getSortedVector()
{
	return vectorInteger_;
}

const std::list<int>& PmergeMe::getSortedList()
{
	return listInteger_;
}

/**
 * @brief Parse and validate input arguments.
 *
 * Validates info:
 * - check contains only numeric characters,
 * - check is greater than zero,
 * - it does not overflow INT_MAX,
 * - not duplicated numbers,
 * - the whole sequence is not already sorted.
 *
 * if valid numbers are stored in vectorInteger_ and update sequence size
 * is saved in sizeSequence_.
 *
 * @param argc Number of args to process.
 * @param argv Array of string.
 *
 * @return true all arguments are valid.
 * @return false if any validation fails.
 */
bool PmergeMe::parseArguments(int argc, char** argv)
{
	vectorInteger_.clear();

	for (int i = 0; i < argc; ++i)
	{
		char* endptr;

		long value = std::strtol(argv[i], &endptr, 10);
		if (*endptr != '\0' || argv[i] == endptr)
		{
			std::cerr << utils::ErrorInvalidChar << argv[i] << "'\n";
			return false;
		}
		if (value <= 0)
		{
			std::cerr << utils::ErrorNegativeNumber << argv[i] << ")\n";
			return false;
		}
		if (value > INT_MAX)
		{
			std::cerr << utils::ErrorOverflowNumber << argv[i] << "'\n";
			return false;
		}
		int	num = static_cast<int>(value);
		if (std::find(vectorInteger_.begin(), vectorInteger_.end(), num) != vectorInteger_.end())
		{
			std::cerr << utils::ErrorDuplicateNumber << argv[i] << "'\n";
			return false;
		}
		vectorInteger_.push_back(num);
	}
	if (vectorInteger_.size() >= 2
		&& utils::isSortedContainer(vectorInteger_))
	{
		std::cerr << utils::ErrorAlreadySorted << std::endl;
		vectorInteger_.clear();
		return false;
	}
	sizeSequence_ = vectorInteger_.size();
	return true;
}

void PmergeMe::run()
{
	listInteger_ = std::list<int>(vectorInteger_.begin(), vectorInteger_.end());

	std::cout << "Before: ";
	utils::printContainer(vectorInteger_, "");

	sortVector();
	sortList();

	std::cout << "\nAfter:  ";
	utils::printContainer(vectorInteger_, "");

	std::cout << "Time to process a range of " << sizeSequence_
		<< " elements with std::vector : " << timeVector_ << " us\n";
	std::cout << "Time to process a range of " << sizeSequence_
		<< " elements with std::list   : " << timeList_ << " us" << std::endl;

	if (!utils::isSortedContainer(vectorInteger_) || !utils::isSortedContainer(listInteger_))
	{
		std::cout << "Sequence is NOT ORDERED correct. :(" << std::endl;
	}
	else
	{
		std::cout << "Sequence correct. :)" << std::endl;
	}
}

/**
 * @brief
 * get the vector fill with sequence of numbers.
 * check if size of vector is even or odd
 * if odd save the last number in variable
 * get a pair of number in sequence.
 *
 */
void PmergeMe::sortVector()
{
	struct timeval start, end;
	gettimeofday(&start, NULL);

	fordJohnsonVector(vectorInteger_);

	gettimeofday(&end, NULL);
	long seconds = end.tv_sec - start.tv_sec;
	long microseconds = end.tv_usec - start.tv_usec;
	timeVector_ = (seconds * 1000000.0) + microseconds;
}

void PmergeMe::sortList()
{
	struct timeval start, end;
	gettimeofday(&start, NULL);

	fordJohnsonList(listInteger_);

	gettimeofday(&end, NULL);
	long seconds = end.tv_sec - start.tv_sec;
	long microseconds = end.tv_usec - start.tv_usec;
	timeList_ = (seconds * 1000000.0) + microseconds;
}

/**
 * @brief this function builds the insertion order based on Jacobsthal sequence
 *
 * @param jacobSequence Jacobsthal numbers used as insertion boundaries.
 * @param sizePendientList number of pending elements.
 * @return Insertion order indices (1-based).
 */
std::vector<int> PmergeMe::buildJacobsthalInsertionOrder(const std::vector<int>& jacobSequence, int sizePendientList)
{
	std::vector<int> insertionOrder;

	if (sizePendientList <= 1)
		return insertionOrder;

	int lastJacobNumber = 1;
	for (size_t i = 0; i < jacobSequence.size(); ++i)
	{
		int j = jacobSequence[i];
		if (j <= lastJacobNumber)
			continue;
		if (j > sizePendientList)
			j = sizePendientList;
		for (int k = j; k > lastJacobNumber; --k)
			insertionOrder.push_back(k);
		lastJacobNumber = j;
		if (lastJacobNumber >= sizePendientList)
			break;
	}
	for (int k = sizePendientList; k > lastJacobNumber; --k)
		insertionOrder.push_back(k);

	return insertionOrder;
}

std::vector<std::pair<int, int> > PmergeMe::createOrderedPairs(const std::vector<int>& sequence)
{
	std::vector<std::pair<int, int> > pairs;

	for (size_t i = 0; i < sequence.size(); i += 2)
	{
		int num1 = sequence.at(i);
		int num2 = sequence.at(i + 1);

		if (num1 > num2)
		{
			pairs.push_back(std::make_pair(num1, num2));
		}
		else
		{
			pairs.push_back(std::make_pair(num2, num1));
		}
	}
	return pairs;
}

/**
 * @brief
 * To update data in 'BNumbers and pairs', we need to ANumbers info
 *
 * Before:
 *		A : [9, 12, 15]
 *		B no-order: [ 3, 7, 2]
 *		pairs: (12,3)(9,7)(15,2)
 * After:
 *		A: [9, 12, 15]
 *		B: [7, 3, 2]
 *		pairs: [(9,7), (12,3), (15,2)]
 */
void PmergeMe::reorderBNumbersAndPairs(const std::vector<int>& ANumbers,
										std::vector<int>& BNumbers,
										std::vector<std::pair<int, int> >& pairs)
{
	std::vector<int> newReorderB;
	std::vector<std::pair<int, int> > reorderedPairs;

	newReorderB.reserve(ANumbers.size());
	reorderedPairs.reserve(ANumbers.size());

	for (size_t i = 0; i < ANumbers.size(); ++i)
	{
		int currentA = ANumbers[i];
		bool found = false;
		for (size_t j = 0; j < pairs.size(); ++j)
		{
			if (pairs[j].first == currentA)
			{
				reorderedPairs.push_back(pairs[j]);
				newReorderB.push_back(pairs[j].second);
				found = true;
				break;
			}
		}
		if (!found)
			return;
	}
	BNumbers = newReorderB;
	pairs = reorderedPairs;
}

/**
 * @brief
 * @param sequence
 * Crear parejas,
 * separar en mayores ANumbers y menores en BNumbers,
 * ordenar recursivamente los mayores,
 * usar la secuencia de inserción para reintegrar los menores mediante búsqueda binaria.
 * Crear pairs y rellenar ANumbers / BNumbers
 * ordena solo la cadena de a (mayores).
 * reordenar pairs y BNumbers para que sigan alineados con ANumbers ordenado.
 * Insertar BNumbers[0] al inicio de ANumbers
 * Bucle Jacobsthal usando BNumbers[idx-1] y pairs[idx-1].first.
 */
void PmergeMe::fordJohnsonVector(std::vector<int>& sequence)
{
	if (sequence.size() <= 1)
		return;

	int pendingImpar = -1;
	if (sequence.size() % 2 != 0)
	{
		pendingImpar = sequence.back();
		sequence.pop_back();
	}
	std::vector<std::pair<int, int> > pairs = createOrderedPairs(sequence);

	std::vector<int> ANumbers = utils::extractA(pairs);
	std::vector<int> BNumbers = utils::extractB(pairs);

	fordJohnsonVector(ANumbers);

	reorderBNumbersAndPairs(ANumbers, BNumbers, pairs);

	std::vector<int> mainChain = ANumbers;
	if (!BNumbers.empty())
	{
		mainChain.insert(mainChain.begin(), BNumbers[0]);
	}

	// 5. Jacobsthal insertion order
	std::vector<int> jacobSeq = createJacobsthalSequence(
		static_cast<int>(BNumbers.size()));

	std::vector<int> order = buildJacobsthalInsertionOrder(
		jacobSeq, static_cast<int>(BNumbers.size()));

	for (size_t i = 0; i < order.size(); ++i)
	{
		int idx = order[i];
		int valueToInsert = BNumbers[idx - 1];

		int targetNumLarger = pairs[idx - 1].first;

		std::vector<int>::iterator posLimit = std::find(mainChain.begin(), mainChain.end(), targetNumLarger);

		std::vector<int>::iterator insertPos = binarySearchInsertPos(mainChain.begin(), posLimit, valueToInsert);

		mainChain.insert(insertPos, valueToInsert);
	}
	if (pendingImpar >= 0)
	{
		std::vector<int>::iterator insertPos = binarySearchInsertPos(mainChain.begin(), mainChain.end(), pendingImpar);

		mainChain.insert(insertPos, pendingImpar);
	}

	sequence = mainChain;
}

/**
 * @brief Ford-Johnson algorithm implemented for std::list.
 *
 * Same phases as fordJohnsonVector; only insertion uses listUpperBound
 */
void PmergeMe::fordJohnsonList(std::list<int>& sequence)
{
	if (sequence.size() <= 1)
		return;

	int pendingImpar = -1;
	if (sequence.size() % 2 != 0)
	{
		pendingImpar = sequence.back();
		sequence.pop_back();
	}

	std::vector<int> tmp(sequence.begin(), sequence.end());
	std::vector<std::pair<int, int> > pairs = createOrderedPairs(tmp);

	std::vector<int> aVec = utils::extractA(pairs);
	std::vector<int> bVec = utils::extractB(pairs);

	std::list<int> ANumbers(aVec.begin(), aVec.end());
	std::list<int> BNumbers(bVec.begin(), bVec.end());

	fordJohnsonList(ANumbers);

	aVec.assign(ANumbers.begin(), ANumbers.end());
	bVec.assign(BNumbers.begin(), BNumbers.end());
	reorderBNumbersAndPairs(aVec, bVec, pairs);
	BNumbers.assign(bVec.begin(), bVec.end());

	std::list<int> mainChain = ANumbers;
	if (!BNumbers.empty())
		mainChain.insert(mainChain.begin(), BNumbers.front());

	std::vector<int> jacobSeq = createJacobsthalSequence(
		static_cast<int>(BNumbers.size()));
	std::vector<int> order = buildJacobsthalInsertionOrder(
		jacobSeq, static_cast<int>(BNumbers.size()));

	for (size_t i = 0; i < order.size(); ++i)
	{
		int idx = order[i];
		int valueToInsert = bVec[idx - 1];
		int targetNumLarger = pairs[idx - 1].first;

		std::list<int>::iterator posLimit = std::find(
			mainChain.begin(), mainChain.end(), targetNumLarger);
		std::list<int>::iterator insertPos = listUpperBound(
			mainChain.begin(), posLimit, valueToInsert);
		mainChain.insert(insertPos, valueToInsert);
	}

	if (pendingImpar >= 0)
	{
		std::list<int>::iterator insertPos = listUpperBound(
			mainChain.begin(), mainChain.end(), pendingImpar);
		mainChain.insert(insertPos, pendingImpar);
	}

	sequence = mainChain;
}

std::list<int>::iterator PmergeMe::listUpperBound(std::list<int>::iterator begin,
												std::list<int>::iterator end,
												int value)
{
	size_t len = static_cast<size_t>(std::distance(begin, end));
	size_t low = 0;
	size_t high = len;

	while (low < high)
	{
		size_t mid = low + (high - low) / 2;
		std::list<int>::iterator midIt = begin;
		std::advance(midIt, static_cast<long>(mid));
		if (*midIt <= value)
			low = mid + 1;
		else
			high = mid;
	}
	std::advance(begin, static_cast<long>(low));
	return begin;
}


std::vector<int>::iterator PmergeMe::binarySearchInsertPos(
	std::vector<int>::iterator begin, std::vector<int>::iterator end, int value)
{
	while (begin < end)
	{
		std::vector<int>::iterator mid = begin + (end - begin) / 2;
		if (*mid <= value)
			begin = mid + 1;
		else
			end = mid;
	}
	return begin;
}

/**
 * @brief
 * Fórmula de Jacobsthal: $J_n = J_{n-1} + 2J_{n-2}$
 * (donde $J_0 = 0$ y $J_1 = 1$).
 */
std::vector<int> PmergeMe::createJacobsthalSequence(int sizePendientList)
{
	std::vector<int> jacobSequence;

	if (sizePendientList <= 0)
		return jacobSequence;

	int a = 0;
	int b = 1;
	jacobSequence.push_back(a);
	jacobSequence.push_back(b);

	while (b < sizePendientList)
	{
		int nextNumber = b + 2 * a;
		jacobSequence.push_back(nextNumber);
		a = b;
		b = nextNumber;
	}
	return jacobSequence;
}
