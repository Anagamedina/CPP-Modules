#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <vector>
# include <deque>
# include <cstddef>

// Clase que ordena una secuencia de enteros positivos con el
// algoritmo Ford-Johnson, una vez con std::vector y otra con std::deque.
class PmergeMe
{
	public:
		// Forma Canonica Ortodoxa
		PmergeMe();
		PmergeMe(const PmergeMe& other);
		PmergeMe& operator=(const PmergeMe& other);
		~PmergeMe();

		// Lee los argumentos, los valida y los guarda en los dos contenedores
		void parseArguments(int argc, char** argv);

		// Ordena con vector y con deque, e imprime Before / After / tiempos
		void sortAndDisplay();

	private:
		std::vector<int> _vector;
		std::deque<int> _deque;

		// Ford-Johnson para vector (recursivo)
		void sortVector(std::vector<int>& v);
		// Ford-Johnson para deque (recursivo, identico pero con deque)
		void sortDeque(std::deque<int>& d);

		// Orden de insercion segun los numeros de Jacobsthal
		std::vector<size_t> jacobsthalOrder(size_t n);
};

#endif
