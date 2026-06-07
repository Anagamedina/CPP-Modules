#include "PmergeMe.hpp"
#include <iostream>

int main(int argc, char** argv)
{
	PmergeMe sorter;
	try
	{
		// Leemos y validamos los numeros que vienen por argumentos
		sorter.parseArguments(argc, argv);
		// Ordenamos e imprimimos los resultados
		sorter.sortAndDisplay();
	}
	catch (const std::exception& e)
	{
		// Si hay algun numero invalido, mostramos el error
		std::cerr << e.what() << std::endl;
		return (1);
	}
	return (0);
}
