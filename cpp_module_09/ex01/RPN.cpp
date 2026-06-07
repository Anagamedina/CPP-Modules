#include "RPN.hpp"

#include <iomanip>
#include <iostream>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <vector>

#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define CYAN    "\033[36m"
#define YELLOW  "\033[33m"
#define GREEN   "\033[32m"
#define MAGENTA "\033[35m"
#define RED     "\033[31m"

RPN::RPN()
{
}

RPN::RPN(const RPN& other) { *this = other; }

RPN& RPN::operator=(const RPN& other)
{
	if (this != &other)
	{
	}
	return *this;
}

RPN::~RPN()
{
}

bool RPN::isOperator(char c)
{
	return (c == '+' || c == '-' || c == '*' || c == '/');
}

int RPN::performOperation(int a, int b, char operation)
{
	if (operation == '+')
		return a + b;
	if (operation == '-')
		return a - b;
	if (operation == '*')
		return a * b;
	if (operation == '/')
	{
		if (b == 0)
			throw std::runtime_error(utils::errorDivisionByZero);
		return (a / b);
	}
	throw std::runtime_error("Error");
}

static void printStackVisual(size_t step, char token,
							const std::stack<int>& stk,
							bool isOperation = false, int a = 0, int b = 0)
{
	std::cout << BOLD << CYAN << "Step " << std::setw(2) << step << RESET
		<< " | ";

	if (std::isdigit(token))
	{
		std::cout << GREEN << "Token: '" << token << "'" << RESET;
	}
	else
	{
		std::cout << YELLOW << "Token: '" << token << "'" << RESET;
	}

	std::cout << "  →  Stack: " << BOLD << "[" << RESET;

	if (stk.empty())
	{
		std::cout << RED << " empty " << RESET;
	}
	else
	{
		std::stack<int> temp = stk;
		std::vector<int> elements;
		while (!temp.empty())
		{
			elements.push_back(temp.top());
			temp.pop();
		}
		for (int i = static_cast<int>(elements.size()) - 1; i >= 0; --i)
		{
			std::cout << " " << GREEN << elements[i] << RESET;
			if (i > 0)
				std::cout << MAGENTA << "," << RESET;
		}
		std::cout << " ";
	}
	std::cout << BOLD << "]" << RESET << "\n";

	// new line
	if (isOperation)
	{
		std::cout << "          "
			<< GREEN << a << RESET
			<< YELLOW << " " << token << " " << RESET
			<< GREEN << b << RESET
			<< "   →   "
			<< GREEN << stk.top() << RESET
			<< "\n\n";
	}
}

int RPN::calculate(const std::string& expression, bool visualize)
{
	std::stack<int> stk;
	size_t step = 0;

	if (visualize)
	{
		std::cout << GREEN << "=== RPN VISUALIZER START ===\n" << RESET;
		std::cout << CYAN << "Expression: \"" << expression << RESET <<
			"\"\n\n";
	}

	for (size_t i = 0; i < expression.length(); ++i)
	{
		char c = expression[i];

		if (std::isspace(c))
			continue;

		++step;

		if (std::isdigit(c))
		{
			stk.push(c - '0');
			if (visualize)
				printStackVisual(step, c, stk);
		}
		else if (isOperator(c))
		{
			if (stk.size() < 2)
				throw std::runtime_error(utils::errorInvalidOperands);

			int b = stk.top();
			stk.pop();
			int a = stk.top();
			stk.pop();

			int result = performOperation(a, b, c);
			stk.push(result);

			if (visualize)
			{
				printStackVisual(step, c, stk, true, a, b);
			}
		}
		else
		{
			throw std::runtime_error(utils::errorInvalidCharacters);
		}
	}

	if (stk.size() != 1)
		throw std::runtime_error(utils::errorInvalidExpression);

	if (visualize)
		std::cout << "\n=== FINAL RESULT: " << stk.top() << " ===\n";

	return stk.top();
}
