#include "BitcoinExchange.hpp"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cctype>

// --- Forma Canonica Ortodoxa ---

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
{
	// Copiamos el map de la otra instancia
	_database = other._database;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
	// Evitamos la auto-asignacion
	if (this != &other)
		_database = other._database;
	return (*this);
}

BitcoinExchange::~BitcoinExchange()
{
}

// --- Carga de la base de datos ---

void BitcoinExchange::loadDatabase(const std::string& dbFile)
{
	std::ifstream file(dbFile.c_str());
	if (!file.is_open())
	{
		std::cerr << "Error: could not open database." << std::endl;
		return ;
	}

	std::string line;
	std::getline(file, line); // Saltamos la cabecera "date,exchange_rate"
	while (std::getline(file, line))
	{
		// En el CSV el separador es una coma
		std::size_t comma = line.find(',');
		if (comma == std::string::npos)
			continue ;
		std::string date = line.substr(0, comma);
		std::string priceStr = line.substr(comma + 1);
		// Guardamos en el map: fecha -> precio
		_database[date] = std::atof(priceStr.c_str());
	}
	file.close();
}

// --- Validacion de fecha ---

bool BitcoinExchange::isValidDate(const std::string& date) const
{
	// El formato debe ser YYYY-MM-DD (10 caracteres)
	if (date.size() != 10)
		return (false);
	if (date[4] != '-' || date[7] != '-')
		return (false);

	// Todos los demas caracteres deben ser digitos
	for (std::size_t i = 0; i < date.size(); i++)
	{
		if (i == 4 || i == 7)
			continue ;
		if (!std::isdigit(date[i]))
			return (false);
	}

	// Comprobamos rangos basicos de mes y dia
	int month = std::atoi(date.substr(5, 2).c_str());
	int day = std::atoi(date.substr(8, 2).c_str());
	if (month < 1 || month > 12)
		return (false);
	if (day < 1 || day > 31)
		return (false);
	return (true);
}

// --- Buscar el precio de una fecha ---

double BitcoinExchange::getPrice(const std::string& date) const
{
	// lower_bound nos da el primer elemento con fecha >= date
	std::map<std::string, double>::const_iterator it;
	it = _database.lower_bound(date);

	// Si la fecha exacta esta, la usamos directamente
	if (it != _database.end() && it->first == date)
		return (it->second);

	// Si no hay ninguna fecha anterior, no podemos calcular
	if (it == _database.begin())
		return (-1.0);

	// Retrocedemos uno para coger la fecha anterior mas cercana
	--it;
	return (it->second);
}

// --- Procesar el archivo de entrada ---

void BitcoinExchange::processInput(const std::string& inputFile)
{
	std::ifstream file(inputFile.c_str());
	if (!file.is_open())
	{
		std::cerr << "Error: could not open file." << std::endl;
		return ;
	}

	std::string line;
	std::getline(file, line); // Saltamos la cabecera "date | value"
	while (std::getline(file, line))
	{
		if (line.empty())
			continue ;

		// El separador de entrada es " | "
		std::size_t sep = line.find(" | ");
		if (sep == std::string::npos)
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue ;
		}

		std::string date = line.substr(0, sep);
		std::string valueStr = line.substr(sep + 3);

		// Validamos que la fecha tenga el formato correcto
		if (!isValidDate(date))
		{
			std::cerr << "Error: bad input => " << date << std::endl;
			continue ;
		}

		// Convertimos el valor a numero
		char* end;
		double value = std::strtod(valueStr.c_str(), &end);

		// Si no se pudo convertir o sobra texto raro, es entrada mala
		if (end == valueStr.c_str() || *end != '\0')
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue ;
		}

		// Validamos el rango: 0 a 1000
		if (value < 0)
		{
			std::cerr << "Error: not a positive number." << std::endl;
			continue ;
		}
		if (value > 1000)
		{
			std::cerr << "Error: too large a number." << std::endl;
			continue ;
		}

		// Buscamos el precio del Bitcoin en esa fecha
		double price = getPrice(date);
		if (price < 0)
		{
			std::cerr << "Error: bad input => " << date << std::endl;
			continue ;
		}

		// Mostramos el resultado: valor * precio
		std::cout << date << " => " << value << " = " << value * price << std::endl;
	}
	file.close();
}
