#ifndef STARTING_WITH_CPP_BITCOINEXCHANGE_HPP
#define STARTING_WITH_CPP_BITCOINEXCHANGE_HPP

#include <map>
#include <string>

namespace btc
{
	const std::string extensionTxt = ".txt";
	const std::string extensionCsv = ".csv";

	// const std::string dataBaseFile = "data.csv";
	const std::string dataBaseFile = "/home/daruuu/CLionProjects/OOP-with-C-Plus-PLus-98/cpp_module_09/ex00/data.csv";

	const std::string errorCannotOpenFile= "Error: Cannot open input file: ";
	const std::string errorCannotOpenDatabase="Error: Cannot open database file: ";
	const std::string errorPositiveNumber = "Error: not a positive number. ";
	const std::string errorBadInput = "Error: bad input => ";
	const std::string errorTooLargeNumber = "Error: too large a number. ";
	const std::string errorDateIsOlder= "Error: date is older than database records. ";
	const std::string errorValidations = "Error: invalid permissions file OR extension file.";
	const std::string pipeChar = " | ";
	const int maxCharsInDate = 10;
}

class BitcoinExchange
{
	friend class UnitTest;
public:
	BitcoinExchange();
	BitcoinExchange(const BitcoinExchange& other);
	BitcoinExchange& operator=(const BitcoinExchange& other);
	~BitcoinExchange();

	void processInputFile(const std::string& filename);

private:
	std::map<std::string, float> database_;

	void loadDatabase();
	bool isValidDate(const std::string& date) const;
	bool isValidValue(const std::string& valueStr) const;
};

#endif //STARTING_WITH_CPP_BITCOINEXCHANGE_HPP
