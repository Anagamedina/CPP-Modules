#include "RPN.hpp"
#include <stdexcept>

// --- Forma Canonica Ortodoxa ---

RPN::RPN()
{
}

RPN::RPN(const RPN& other)
{
	_stack = other._stack;
}

RPN& RPN::operator=(const RPN& other)
{
	if (this != &other)
		_stack = other._stack;
	return (*this);
}

RPN::~RPN()
{
}

// --- Evaluacion de la expresion ---

int RPN::evaluate(const std::string& expression)
{
	// Recorremos cada caracter de la expresion
	for (std::size_t i = 0; i < expression.size(); i++)
	{
		char c = expression[i];

		// Los espacios se ignoran
		if (c == ' ')
			continue ;

		// Si es un digito (numeros de un solo digito, < 10) lo apilamos
		if (c >= '0' && c <= '9')
		{
			_stack.push(c - '0');
			continue ;
		}

		// Si es un operador, necesitamos al menos 2 numeros en la pila
		if (c == '+' || c == '-' || c == '*' || c == '/')
		{
			if (_stack.size() < 2)
				throw std::runtime_error("Error");

			// Sacamos los dos ultimos numeros (ojo al orden)
			int b = _stack.top();
			_stack.pop();
			int a = _stack.top();
			_stack.pop();

			// Aplicamos la operacion y volvemos a apilar el resultado
			if (c == '+')
				_stack.push(a + b);
			else if (c == '-')
				_stack.push(a - b);
			else if (c == '*')
				_stack.push(a * b);
			else
			{
				if (b == 0)
					throw std::runtime_error("Error");
				_stack.push(a / b);
			}
			continue ;
		}

		// Cualquier otro caracter es invalido
		throw std::runtime_error("Error");
	}

	// Al final debe quedar exactamente un numero en la pila
	if (_stack.size() != 1)
		throw std::runtime_error("Error");

	return (_stack.top());
}
