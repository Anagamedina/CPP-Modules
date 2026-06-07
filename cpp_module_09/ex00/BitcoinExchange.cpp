#include "BitcoinExchange.hpp"

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>

BitcoinExchange::BitcoinExchange()
{
	loadDatabase();
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
{
	database_ = other.database_;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
	if (this != &other)
	{
		database_ = other.database_;
	}
	return *this;
}

BitcoinExchange::~BitcoinExchange()
{
}

void BitcoinExchange::processInputFile(const std::string& filename)
{
	std::ifstream inputFile(filename.c_str());
	if (!inputFile.is_open())
	{
		std::cerr << btc::errorCannotOpenFile << filename;
		return;
	}

	std::string line;
	// Extraemos la primera línea y validamos que sea exactamente el formato esperado
	if (!std::getline(inputFile, line))
	{
		std::cout << "Error: Empty file." << std::endl;
		inputFile.close();
		return;
	}
	if (line != "date | value")
	{
		std::cout << "Error: Invalid file format. Expected 'date | value' explicitly as first line." << std::endl;
		inputFile.close();
		return;
	}

	while (std::getline(inputFile, line))
	{
		if (line.empty())
		{
			continue;
		}
		size_t pipePosition = line.find(btc::pipeChar);
		if (pipePosition == std::string::npos)
		{
			std::cout << btc::errorBadInput << line << std::endl;
			continue;
		}
		std::string date = line.substr(0, pipePosition);
		if (!isValidDate(date))
		{
			std::cout << btc::errorBadInput << line << std::endl;
			continue;
		}
		std::string valueStr = line.substr(pipePosition + 3);

		// Validamos que el string sea numerico y no tenga caracters invalidos
		if (!isValidValue(valueStr))
		{
			std::cout << btc::errorBadInput << line << std::endl;
			continue;
		}

		float valueFloat = std::strtof(valueStr.c_str(), NULL);
		if (valueFloat < 0)
		{
			std::cout << btc::errorPositiveNumber << line << std::endl;
			continue;
		}
		if (valueFloat > 1000)
		{
			// std::cout << btc::errorTooLargeNumber << line << std::endl;
			std::cout << btc::errorTooLargeNumber << std::endl;
			continue;
		}
		// search in the map the date
		std::map<std::string, float>::iterator itLowerBound = database_.
			lower_bound(date);
		if (itLowerBound != database_.end() && itLowerBound->first == date)
		{
			// database_[date] = valueFloat;
		}
		else if (itLowerBound == database_.begin())
		{
			std::cout << btc::errorDateIsOlder << std::endl;
			continue;
		}
		else
		{
			--itLowerBound;
		}
		float valueInDataBase = itLowerBound->second;
		std::cout << date << " => " << valueStr << " = " << (valueFloat *
			valueInDataBase) << std::endl;
	}
	inputFile.close();
}

void BitcoinExchange::loadDatabase()
{
	std::ifstream file(btc::dataBaseFile.data());

	if (!file.is_open())
	{
		throw std::runtime_error(btc::errorCannotOpenDatabase + btc::dataBaseFile);
		// std::cerr << btc::errorCannotOpenDatabase << btc::dataBaseFile
			// << std::endl;
		return;
	}
	std::string line;

	//	get first line: date | value
	std::getline(file, line);
	while (std::getline(file, line))
	{
		size_t commaPosition = line.find(',');
		if (commaPosition != std::string::npos)
		{
			//	extract line: date, value
			std::string date = line.substr(0, commaPosition);
			std::string valueStr = line.substr(commaPosition + 1);
			// value to float
			std::stringstream ss(valueStr);
			float valueFloat;
			ss >> valueFloat;
			database_[date] = valueFloat;
		}
	}
	file.close();
}

bool BitcoinExchange::isValidDate(const std::string& date) const
{
	// ha de tener longitud 10 (YYYY-MM-DD)
	if (date.length() != btc::maxCharsInDate)
		return false;

	// comprobar que los guiones sean corrector
	if (date[4] != '-' || date[7] != '-')
		return false;

	// 3. Comprobar que el resto sean dígitos
	for (unsigned int i = 0; i < btc::maxCharsInDate; i++)
	{
		if (i == 4 || i == 7)
			continue;
		if (date[i] < '0' || date[i] > '9')
			return false;
	}

	// extraer los year, month , day
	//	Year-Month-Day
	const long year = strtol(date.substr(0, 4).c_str(), NULL, 10);
	const long month = strtol(date.substr(5, 2).c_str(), NULL, 10);
	const long day = strtol(date.substr(8, 2).c_str(), NULL, 10);

	// 5. Validaciones de calendario
	if (year < 2000 || year > 2100)
		return false;
	// Rango meses
	if (month < 1 || month > 12)
		return false;
	if (day < 1 || day > 31)
		return false;

	if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
		return false;
	if (month == 2)
	{
		bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
		if (day > (isLeap ? 29 : 28))
			return false;
	}

	return true;
}

bool BitcoinExchange::isValidValue(const std::string& valueStr) const
{
	if (valueStr.empty())
		return false;
	int dotCount = 0;
	size_t i = 0;

	// Si hay espacio al principio, lo ignoramos, pero según el formato anterior, line.substr ya quita el espacio
	// De todas formas, aquí comprobaremos si toda la cadena son números.

	if (valueStr[0] == '-' || valueStr[0] == '+')
	{
		i++;
	}
	if (i == valueStr.length()) return false; // si solo era un "+", es inválido

	for (; i < valueStr.length(); i++)
	{
		if (valueStr[i] == '.')
		{
			dotCount++;
			if (dotCount > 1) return false;
			// No puede tener más de un punto (ej: 1.2.3)
		}
		else if (valueStr[i] < '0' || valueStr[i] > '9')
		{
			return false; // Alguien nos pasó texto basura o letras
		}
	}
	return true;
}
