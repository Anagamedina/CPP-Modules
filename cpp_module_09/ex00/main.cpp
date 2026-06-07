#include <iostream>
#include <fstream>
#include "BitcoinExchange.hpp"

//	anonymous namespace
namespace
{
	bool validateFileExtension(const std::string& path)
	{
		if (path.size() < 5)
			return false;
		std::string substr= path.substr(path.size() - 4);
		if (substr!= btc::extensionCsv && substr!= btc::extensionTxt)
			return false;

		return true;
	}

	bool validateFilePermissions(const std::string& fileName)
	{
		std::ifstream ifs(fileName.c_str());
		if (!ifs.is_open())
			return false;
		ifs.close();
		return true;
	}
}

int main(int ac, char** av)
{
	if (ac != 2)
	{
		std::cerr << "Error: is necessary 2 arguments" << std::endl;
		return 1;
	}

	if (!validateFilePermissions(av[1]) || !validateFileExtension(av[1]))
	{
		std::cerr << btc::errorValidations << std::endl;
		return 1;
	}
	try
	{
		BitcoinExchange btc;
		
		// Procesar el fichero de entrada pasado por argumento
		btc.processInputFile(av[1]);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;
}
