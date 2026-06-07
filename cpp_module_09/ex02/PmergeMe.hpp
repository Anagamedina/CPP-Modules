#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include "Utils.hpp"
#include <list>
#include <string>
#include <vector>

class PmergeMe
{
public:
	PmergeMe();
	PmergeMe(const PmergeMe& other);
	PmergeMe& operator=(const PmergeMe& other);
	~PmergeMe();

	// Getters - used by tests to inspect sorted results
	const std::vector<int>& getSortedVector();
	const std::list<int>& getSortedList();

	bool parseArguments(int argc, char** argv);
	void run();

private:
	std::vector<int> vectorInteger_;
	std::list<int> listInteger_;
	double timeVector_;
	double timeList_;
	unsigned int sizeSequence_;

	void sortVector();
	void sortList();

	std::vector<int> buildJacobsthalInsertionOrder(
		const std::vector<int>& jacobSequence,
		int sizePendientList);
	std::vector<std::pair<int, int> > createOrderedPairs(
		const std::vector<int>& sequence);
	void reorderBNumbersAndPairs(const std::vector<int>& ANumbers,
								std::vector<int>& BNumbers,
								std::vector<std::pair<int, int> >& pairs);

	void fordJohnsonVector(std::vector<int>& sequence);
	void fordJohnsonList(std::list<int>& sequence);

	static std::list<int>::iterator listUpperBound(
		std::list<int>::iterator begin,
		std::list<int>::iterator end,
		int value);

	std::vector<int>::iterator binarySearchInsertPos(
		std::vector<int>::iterator begin,
		std::vector<int>::iterator end, int value);
	std::vector<int> createJacobsthalSequence(int sizePendientList);
};

#endif // PMERGEME_HPP
