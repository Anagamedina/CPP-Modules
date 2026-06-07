#include "RPN.hpp"
#include <iostream>

int main(int argc, char** argv)
{
	// El programa necesita exactamente 1 argumento: la expresion
	if (argc != 2)
	{
		std::cerr << "Error" << std::endl;
		return (1);
	}

	RPN rpn;
	try
	{
		// Evaluamos la expresion y mostramos el resultado
		int result = rpn.evaluate(argv[1]);
		std::cout << result << std::endl;
	}
	catch (const std::exception& e)
	{
		// Si algo falla, mostramos el error por cerr
		std::cerr << e.what() << std::endl;
		return (1);
	}
	return (0);
}
