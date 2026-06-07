#include "PmergeMe.hpp"
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <cstdlib>
#include <cctype>
#include <ctime>

// --- Forma Canonica Ortodoxa ---

PmergeMe::PmergeMe()
{
}

PmergeMe::PmergeMe(const PmergeMe& other)
{
	_vector = other._vector;
	_deque = other._deque;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
	if (this != &other)
	{
		_vector = other._vector;
		_deque = other._deque;
	}
	return (*this);
}

PmergeMe::~PmergeMe()
{
}

// --- Lectura y validacion de los argumentos ---

void PmergeMe::parseArguments(int argc, char** argv)
{
	if (argc < 2)
		throw std::runtime_error("Error");

	for (int i = 1; i < argc; i++)
	{
		std::string arg = argv[i];
		if (arg.empty())
			throw std::runtime_error("Error");

		// Todos los caracteres deben ser digitos (asi no entran negativos)
		for (std::size_t j = 0; j < arg.size(); j++)
		{
			if (!std::isdigit(arg[j]))
				throw std::runtime_error("Error");
		}

		// Comprobamos que no se salga del rango de int
		long number = std::strtol(arg.c_str(), NULL, 10);
		if (number > 2147483647)
			throw std::runtime_error("Error");

		// Guardamos el numero en los dos contenedores
		_vector.push_back(static_cast<int>(number));
		_deque.push_back(static_cast<int>(number));
	}
}

// --- Numeros de Jacobsthal: definen el orden de insercion ---

std::vector<size_t> PmergeMe::jacobsthalOrder(size_t n)
{
	std::vector<size_t> order;
	if (n == 0)
		return (order);

	// Generamos la serie de Jacobsthal: 1, 3, 5, 11, 21, 43, ...
	std::vector<size_t> jacob;
	jacob.push_back(1);
	jacob.push_back(3);
	while (jacob.back() < n)
		jacob.push_back(jacob[jacob.size() - 1] + 2 * jacob[jacob.size() - 2]);

	// Para cada grupo, insertamos los indices de mayor a menor
	size_t prev = 0;
	for (size_t i = 0; i < jacob.size(); i++)
	{
		size_t start = jacob[i];
		if (start > n)
			start = n;
		for (size_t k = start; k > prev; k--)
			order.push_back(k - 1);
		prev = jacob[i];
		if (prev >= n)
			break ;
	}
	return (order);
}

// --- Ford-Johnson para std::vector ---

void PmergeMe::sortVector(std::vector<int>& v)
{
	// Caso base: con 0 o 1 elemento ya esta ordenado
	if (v.size() < 2)
		return ;

	// 1. Si la cantidad es impar, separamos el ultimo elemento (suelto)
	bool hasStraggler = (v.size() % 2 == 1);
	int straggler = 0;
	if (hasStraggler)
		straggler = v.back();
	size_t limit = v.size() - (hasStraggler ? 1 : 0);

	// 2. Formamos parejas: el grande va a 'larges', el pequeno a 'smalls'
	std::vector<int> larges;
	std::vector<int> smalls;
	for (size_t i = 0; i < limit; i += 2)
	{
		if (v[i] > v[i + 1])
		{
			larges.push_back(v[i]);
			smalls.push_back(v[i + 1]);
		}
		else
		{
			larges.push_back(v[i + 1]);
			smalls.push_back(v[i]);
		}
	}

	// 3. Ordenamos recursivamente solo los grandes (la cadena principal)
	sortVector(larges);

	// 4. La cadena principal arranca con los grandes ya ordenados
	std::vector<int> result = larges;

	// 5. Insertamos los pequenos con busqueda binaria, en orden de Jacobsthal
	std::vector<size_t> order = jacobsthalOrder(smalls.size());
	for (size_t i = 0; i < order.size(); i++)
	{
		int value = smalls[order[i]];
		std::vector<int>::iterator pos = std::lower_bound(result.begin(), result.end(), value);
		result.insert(pos, value);
	}

	// 6. Por ultimo insertamos el elemento suelto si lo habia
	if (hasStraggler)
	{
		std::vector<int>::iterator pos = std::lower_bound(result.begin(), result.end(), straggler);
		result.insert(pos, straggler);
	}

	v = result;
}

// --- Ford-Johnson para std::deque (identico, pero con deque) ---

void PmergeMe::sortDeque(std::deque<int>& d)
{
	if (d.size() < 2)
		return ;

	bool hasStraggler = (d.size() % 2 == 1);
	int straggler = 0;
	if (hasStraggler)
		straggler = d.back();
	size_t limit = d.size() - (hasStraggler ? 1 : 0);

	std::deque<int> larges;
	std::deque<int> smalls;
	for (size_t i = 0; i < limit; i += 2)
	{
		if (d[i] > d[i + 1])
		{
			larges.push_back(d[i]);
			smalls.push_back(d[i + 1]);
		}
		else
		{
			larges.push_back(d[i + 1]);
			smalls.push_back(d[i]);
		}
	}

	sortDeque(larges);

	std::deque<int> result = larges;

	std::vector<size_t> order = jacobsthalOrder(smalls.size());
	for (size_t i = 0; i < order.size(); i++)
	{
		int value = smalls[order[i]];
		std::deque<int>::iterator pos = std::lower_bound(result.begin(), result.end(), value);
		result.insert(pos, value);
	}

	if (hasStraggler)
	{
		std::deque<int>::iterator pos = std::lower_bound(result.begin(), result.end(), straggler);
		result.insert(pos, straggler);
	}

	d = result;
}

// --- Mostrar resultados y medir tiempos ---

void PmergeMe::sortAndDisplay()
{
	// Imprimimos la secuencia original (Before)
	std::cout << "Before:";
	for (size_t i = 0; i < _vector.size(); i++)
		std::cout << " " << _vector[i];
	std::cout << std::endl;

	// Medimos el tiempo de ordenar con vector
	clock_t startV = clock();
	sortVector(_vector);
	clock_t endV = clock();

	// Medimos el tiempo de ordenar con deque
	clock_t startD = clock();
	sortDeque(_deque);
	clock_t endD = clock();

	// Imprimimos la secuencia ya ordenada (After)
	std::cout << "After:";
	for (size_t i = 0; i < _vector.size(); i++)
		std::cout << " " << _vector[i];
	std::cout << std::endl;

	// Convertimos los tiempos a microsegundos
	double timeV = static_cast<double>(endV - startV) / CLOCKS_PER_SEC * 1000000;
	double timeD = static_cast<double>(endD - startD) / CLOCKS_PER_SEC * 1000000;

	std::cout << "Time to process a range of " << _vector.size()
		<< " elements with std::vector : " << timeV << " us" << std::endl;
	std::cout << "Time to process a range of " << _deque.size()
		<< " elements with std::deque : " << timeD << " us" << std::endl;
}
