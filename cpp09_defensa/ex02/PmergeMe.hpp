#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <deque>
#include <vector>

class PmergeMe
{
public:
	// Canonical Orthodox Form: constructor, copy constructor, assignment operator, and destructor.
	PmergeMe();
	PmergeMe(const PmergeMe& other);
	PmergeMe& operator=(const PmergeMe& other);
	~PmergeMe();

	// Validates input arguments and stores them in the vector.
	bool parseArguments(int argc, char** argv);
	
	// Orchestrates the sorting process and prints results and timing.
	void run();

private:
	std::vector<int> vectorInteger_;
	std::deque<int> dequeInteger_;
	double timeVector_;
	double timeDeque_;
	unsigned int sizeSequence_;

	// Measures and executes sorting for std::vector.
	void sortVector();
	
	// Measures and executes sorting for std::deque.
	void sortDeque();

	// Determines the optimal order for inserting elements using Jacobsthal numbers.
	std::vector<int> buildJacobsthalInsertionOrder(const std::vector<int>& jacobSequence, int sizePendientList);
	
	// Creates pairs of elements, ensuring the larger one is 'first'.
	std::vector<std::pair<int, int> > createOrderedPairs(const std::vector<int>& sequence);
	
	// Realigns the smaller elements with their sorted larger counterparts.
	void reorderBNumbersAndPairs(const std::vector<int>& ANumbers, std::vector<int>& BNumbers, std::vector<std::pair<int, int> >& pairs);
	
	// Extracts the larger elements from each pair.
	std::vector<int> extractA(const std::vector<std::pair<int, int> >& pairs);
	
	// Extracts the smaller elements from each pair.
	std::vector<int> extractB(const std::vector<std::pair<int, int> >& pairs);
	
	// Checks if the sequence is already sorted.
	bool isSorted(const std::vector<int>& sequence) const;
	
	// Generates the mathematical Jacobsthal sequence.
	std::vector<int> createJacobsthalSequence(int sizePendientList);

	// Binary search to find the correct insertion position in a sorted range.
	template <typename Iterator>
	Iterator binarySearchInsertPos(Iterator begin, Iterator end, int value);

	// Generic implementation of the Ford-Johnson (merge-insertion) algorithm.
	template <typename Container>
	void mergeInsertSort(Container& sequence);
};

#endif
