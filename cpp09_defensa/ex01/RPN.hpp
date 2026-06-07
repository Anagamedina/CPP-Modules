#ifndef RPN_HPP
# define RPN_HPP

# include <string>
# include <stack>

// Clase que evalua una expresion en Notacion Polaca Inversa (RPN).
class RPN
{
	public:
		// Forma Canonica Ortodoxa
		RPN();
		RPN(const RPN& other);
		RPN& operator=(const RPN& other);
		~RPN();

		// Recibe la expresion (ej: "3 4 +") y devuelve el resultado.
		// Lanza una excepcion si la expresion no es valida.
		int evaluate(const std::string& expression);

	private:
		// La pila guarda los numeros mientras procesamos la expresion
		std::stack<int> _stack;
};

#endif
