#include "PmergeMe.hpp"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <climits>
#include <ctime>

// Inicializo todo a valores por defecto
PmergeMe::PmergeMe() : timeVector_(0), timeDeque_(0), sizeSequence_(-1) {}

PmergeMe::PmergeMe(const PmergeMe& other)
{
	*this = other;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
	if (this != &other)
	{
		vectorInteger_ = other.vectorInteger_;
		dequeInteger_ = other.dequeInteger_;
		timeVector_ = other.timeVector_;
		timeDeque_ = other.timeDeque_;
		sizeSequence_ = other.sizeSequence_;
	}
	return *this;
}

PmergeMe::~PmergeMe() {}

/**
 * @brief Lee y valida los argumentos de entrada.
 *
 * Comprueba que:
 * - solo contienen caracteres numericos,
 * - son mayores que cero,
 * - no desbordan INT_MAX,
 * - no hay numeros duplicados,
 * - la secuencia no viene ya ordenada.
 */
bool PmergeMe::parseArguments(int argc, char** argv)
{
	vectorInteger_.clear();
	for (int i = 0; i < argc; ++i)
	{
		char* endptr;
		long value = std::strtol(argv[i], &endptr, 10);
		
		// Valido que sea un numero, positivo, sin letras y que quepa en un int
		if (*endptr != '\0' || argv[i] == endptr) {
			std::cerr << "Error: invalid characters in '" << argv[i] << "'\n";
			return false;
		}
		if (value <= 0)
		{
			std::cerr << "Error: only positive integers are allowed (found: " << argv[i] << ")\n";
			return false;
		}
		if (value > INT_MAX)
		{
			std::cerr << "Error: value overflows integer limit '" << argv[i] << "'\n";
			return false;
		}
		int	num = static_cast<int>(value);
		if (std::find(vectorInteger_.begin(), vectorInteger_.end(), num) != vectorInteger_.end())
		{
			std::cerr << "Error: duplicate number '" << argv[i] << "'\n";
			return false;
		}
		vectorInteger_.push_back(num);
	}
	if (vectorInteger_.size() >= 2 && isSorted(vectorInteger_))
	{
		std::cerr << "Error: sequence is already sorted." << std::endl;
		vectorInteger_.clear();
		return false;
	}
	sizeSequence_ = vectorInteger_.size();
	return true;
}

void PmergeMe::run()
{
	// Copiamos la misma secuencia al deque
	dequeInteger_ = std::deque<int>(vectorInteger_.begin(), vectorInteger_.end());

	// Imprimimos la secuencia original
	std::cout << "Before: ";
	for (size_t i = 0; i < vectorInteger_.size(); ++i)
		std::cout << vectorInteger_[i] << " ";
	std::cout << std::endl;

	sortVector();
	sortDeque();

	// Imprimimos la secuencia ya ordenada
	std::cout << "After:  ";
	for (size_t i = 0; i < vectorInteger_.size(); ++i)
		std::cout << vectorInteger_[i] << " ";
	std::cout << std::endl;

	std::cout << "Time to process a range of " << sizeSequence_
		<< " elements with std::vector : " << timeVector_ << " us\n";
	std::cout << "Time to process a range of " << sizeSequence_
		<< " elements with std::deque  : " << timeDeque_ << " us" << std::endl;
}

void PmergeMe::sortVector()
{
	// clock() da los ticks de CPU; los pasamos a microsegundos con CLOCKS_PER_SEC
	std::clock_t start = std::clock();

	// Llamamos al algoritmo generico con el vector
	mergeInsertSort(vectorInteger_);

	std::clock_t end = std::clock();
	timeVector_ = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000.0;
}

void PmergeMe::sortDeque()
{
	std::clock_t start = std::clock();

	// El MISMO algoritmo, ahora con el deque
	mergeInsertSort(dequeInteger_);
	std::clock_t end = std::clock();
	timeDeque_ = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000.0;
}

// Genero el orden de insercion basado en los grupos de Jacobsthal
std::vector<int> PmergeMe::buildJacobsthalInsertionOrder(const std::vector<int>& jacobSequence, int sizePendientList)
{
	std::vector<int> insertionOrder;
	if (sizePendientList <= 1) return insertionOrder;

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

	// Formamos parejas y dejamos el grande primero (first) y el pequeno segundo
	for (size_t i = 0; i < sequence.size(); i += 2)
	{
		int num1 = sequence.at(i);
		int num2 = sequence.at(i + 1);

		if (num1 > num2)
			pairs.push_back(std::make_pair(num1, num2));
		else
			pairs.push_back(std::make_pair(num2, num1));
	}
	return pairs;
}

/**
 * @brief Reordena BNumbers y pairs para que sigan alineados con ANumbers ordenado.
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
 * @brief Formula de Jacobsthal: J_n = J_(n-1) + 2 * J_(n-2)
 * (con J_0 = 0 y J_1 = 1).
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

// Saca los grandes (first) de cada pareja
std::vector<int> PmergeMe::extractA(const std::vector<std::pair<int, int> >& pairs)
{
	std::vector<int> a;
	for (size_t i = 0; i < pairs.size(); ++i)
		a.push_back(pairs[i].first);
	return a;
}

// Saca los pequenos (second) de cada pareja
std::vector<int> PmergeMe::extractB(const std::vector<std::pair<int, int> >& pairs)
{
	std::vector<int> b;
	for (size_t i = 0; i < pairs.size(); ++i)
		b.push_back(pairs[i].second);
	return b;
}

// Comprueba si la secuencia ya viene ordenada de menor a mayor
bool PmergeMe::isSorted(const std::vector<int>& sequence) const
{
	for (size_t i = 1; i < sequence.size(); ++i)
	{
		if (sequence[i] < sequence[i - 1])
			return false;
	}
	return true;
}
