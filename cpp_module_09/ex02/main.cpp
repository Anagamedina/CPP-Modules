#include "PmergeMe.hpp"
#include <iostream>

int main(int argc, char** argv)
{
	if (argc <= 2)
	{
		std::cerr << utils::DefaultMessage << std::endl;
		std::cout.flush();
		return 1;
	}
	try
	{
		PmergeMe mergeInsertionSort;
		if (!mergeInsertionSort.parseArguments(argc - 1, &argv[1]))
			return 1;

		mergeInsertionSort.run();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}
	return 0;
}
