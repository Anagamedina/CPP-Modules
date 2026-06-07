#ifndef STARTING_WITH_CPP_RPN_HPP
#define STARTING_WITH_CPP_RPN_HPP

#include <string>

namespace utils
{
	const std::string errorInvalidOperands = "Error: Insufficient operands.";
	const std::string errorDivisionByZero= "Error: Division by zero.";
	const std::string errorInvalidCharacters= "Error: Invalid Characters.";
	const std::string errorInvalidExpression="Error: Incomplete expression";
}

class RPN
{
public:
	RPN();
	RPN(const RPN& other);
	RPN& operator=(const RPN& other);
	~RPN();

	static int calculate(const std::string& expression, bool visualize);

private:
	static bool isOperator(char c);
	static int performOperation(int a, int b, char operation);
};

#endif //STARTING_WITH_CPP_RPN_HPP
