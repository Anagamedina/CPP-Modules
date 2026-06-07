#ifndef UTILS_HPP
#define UTILS_HPP
#include <iostream>
#include <vector>

namespace utils
{
	enum { DEBUG = 0 };

	const std::string DefaultMessage=
		"Usage: ./PmergeMe At least 2 integer numbers positives";
	const std::string ErrorInvalidChar =
		"Error: invalid characters in argument '";
	const std::string ErrorNegativeNumber =
		"Error: Only positive integers are allowed (found: ";
	const std::string ErrorOverflowNumber =
		"Error: value overflows integer limit '";
	const std::string ErrorDuplicateNumber =
	"Error: duplicate number '";
	const std::string ErrorAlreadySorted =
	"Error: sequence is already sorted, buen intento. :(";

	template <typename T>
	void printContainer(const T& container, const std::string titleMessage)
	{
		if (!titleMessage.empty())
			std::cout << "*** " << titleMessage << " ***\n";

		typename T::const_iterator it;
		for (it = container.begin(); it != container.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;
	}

	template <typename T>
	void printSequencePairs(const T& container, const std::string& titleString)
	{
		if (!titleString.empty())
			std::cout << "\n" << titleString << "\n";
		typename T::const_iterator it;
		for (it = container.begin(); it != container.end(); ++it)
		{
			std::cout << "(" << it->first << ", " << it->second << ")";
		}
	}

	template <typename TContainer>
	bool isSortedContainer(const TContainer& c)
	{
		if (c.size() <= 1)
			return true;

		typename TContainer::const_iterator prev = c.begin();
		typename TContainer::const_iterator it = c.begin();
		++it;

		for (; it != c.end(); ++it, ++prev)
		{
			if (*it < *prev)
			{
				return false;
			}
		}
		return true;
	}

	// TODO: template with this function
	inline std::vector<int> extractA(const std::vector<std::pair<int,int> >& pairs)
	{
		std::vector<int> A;

		for (size_t i = 0; i < pairs.size(); ++i)
		{
			A.push_back(pairs[i].first);
		}
		return A;
	}

	inline std::vector<int> extractB(const std::vector<std::pair<int,int> >& pairs)
	{
		std::vector<int> B;

		for (size_t i = 0; i < pairs.size(); ++i)
		{
			B.push_back(pairs[i].second);
		}
		return B;
	}

}

#endif //UTILS_HPP
