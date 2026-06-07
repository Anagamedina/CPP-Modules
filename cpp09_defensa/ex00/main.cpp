#include "BitcoinExchange.hpp"
#include <iostream>

int main(int argc, char** argv)
{
	// El programa necesita exactamente 1 argumento: el archivo de entrada
	if (argc != 2)
	{
		std::cerr << "Error: could not open file." << std::endl;
		return (1);
	}

	BitcoinExchange exchange;
	// Cargamos primero la base de datos de precios
	exchange.loadDatabase("data.csv");
	// Procesamos el archivo que nos pasa el usuario
	exchange.processInput(argv[1]);
	return (0);
}
