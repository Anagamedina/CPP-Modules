/**
 * @file pmergeme_test.cpp
 * @brief GoogleTest suite for PmergeMe (Ford-Johnson sort).
 *
 * Build:  cd tests && make setup && make && ./run_tests
 * Or:     cd ex02 && make test
 *
 * GoogleTest lives in ../extern/googletest (downloaded by tests/Makefile).
 *
 * Test categories:
 *   1. Basic cases       — 1, 2, 3 elements
 *   2. Input validation  — invalid chars, already sorted (custom rule)
 *   3. Large sort        — 100 unique numbers (compare with std::sort)
 *
 * Each test follows Arrange / Act / Assert (Given / When / Then).
 */

#include <gtest/gtest.h>
#include "../PmergeMe.hpp"

#include <algorithm>
#include <list>
#include <random>
#include <sstream>
#include <vector>

//  Helpers

/** Suppresses std::cout output for the duration of its lifetime. */
struct SuppressStdout
{
	std::streambuf* old_;

	SuppressStdout() : old_(std::cout.rdbuf(nullptr))
	{
	}

	~SuppressStdout() { std::cout.rdbuf(old_); }
};

/** Suppresses std::cerr output for the duration of its lifetime. */
struct SuppressStderr
{
	std::streambuf* old_;

	SuppressStderr() : old_(std::cerr.rdbuf(nullptr))
	{
	}

	~SuppressStderr() { std::cerr.rdbuf(old_); }
};

/**
 * Converts a vector<int> into the argv-style buffers that processSequence needs.
 * @param nums      source integers
 * @param strBuf    keeps the std::string objects alive
 * @param argvBuf   keeps the char* pointers alive
 */
static void buildArgs(const std::vector<int>& nums,
					std::vector<std::string>& strBuf,
					std::vector<char*>& argvBuf)
{
	strBuf.clear();
	argvBuf.clear();
	for (size_t i = 0; i < nums.size(); ++i)
	{
		std::ostringstream oss;
		oss << nums[i];
		strBuf.push_back(oss.str());
	}
	for (size_t i = 0; i < strBuf.size(); ++i)
		argvBuf.push_back(&strBuf[i][0]);
}

/** Returns true when a std::vector<int> is sorted in non-decreasing order. */
static bool isSorted(const std::vector<int>& v)
{
	for (size_t i = 1; i < v.size(); ++i)
		if (v[i] < v[i - 1])
			return false;
	return true;
}

/** Converts std::list<int> to std::vector<int> for EXPECT_EQ with vector result. */
static std::vector<int> listToVector(const std::list<int>& l)
{
	return std::vector<int>(l.begin(), l.end());
}

/**
 * Runs parse + sort like the real program, without printing to the terminal.
 */
static bool parseAndRun(PmergeMe& pm, int argc, char** argv)
{
	SuppressStdout suppressOut;
	SuppressStderr suppressErr;
	if (!pm.parseArguments(argc, argv))
		return false;
	pm.run();
	return true;
}

/**
 * N enteros positivos UNICOS en orden aleatorio (barajado).
 *
 * @param count   cuantos numeros (ej. 200)
 * @param seed    semilla fija → mismo "random" en cada ejecucion (util para depurar).
 *                Cambia seed (ej. time) si quieres distinto cada vez.
 *
 * Cumple parseArguments: sin duplicados y casi nunca ya ordenado.
 */
static std::vector<int> makeRandomUniqueInput(size_t count, unsigned int seed = 42U)
{
	std::vector<int> nums;
	nums.reserve(count);
	for (size_t i = 1; i <= count; ++i)
		nums.push_back(static_cast<int>(i));

	std::mt19937 rng(seed);
	std::shuffle(nums.begin(), nums.end(), rng);
	return nums;
}

/**
 * N enteros UNICOS elegidos al azar entre [minVal, maxVal] (estilo shuf del subject).
 * Requiere (maxVal - minVal + 1) >= count.
 */
static std::vector<int> makeRandomUniqueInRange(size_t count, int minVal, int maxVal,
												unsigned int seed = 42U)
{
	std::vector<int> pool;
	for (int v = minVal; v <= maxVal; ++v)
		pool.push_back(v);

	if (pool.size() < count)
		return std::vector<int>();

	std::mt19937 rng(seed);
	std::shuffle(pool.begin(), pool.end(), rng);
	pool.resize(count);
	return pool;
}

// -----------------------------------------------------------------------------
//  Large sort — 100 numbers
// -----------------------------------------------------------------------------

/**
 * Fixture: shared buffers for argv-style arguments.
 * Junior tip: strBuf_ must live while the test runs (char* point into strings).
 */
class PmergeMeSort100Test : public ::testing::Test
{
protected:
	PmergeMe pm_;
	std::vector<std::string> strBuf_;
	std::vector<char*> argvBuf_;

	void runSort(const std::vector<int>& input)
	{
		buildArgs(input, strBuf_, argvBuf_);
		ASSERT_TRUE(parseAndRun(
			pm_, static_cast<int>(argvBuf_.size()), argvBuf_.data()));
	}
};

TEST_F(PmergeMeSort100Test, Sorts100UniqueNumbersLikeStdSort)
{
	// Arrange — 100 unicos barajados (1..100 mezclados)
	const size_t count = 100;
	std::vector<int> input = makeRandomUniqueInput(count, 42U);
	// utils::printContainer(input, "CASE 100");
	std::vector<int> expected = input;
	std::sort(expected.begin(), expected.end());

	// Act — same path as ./PmergeMe n1 n2 ...
	runSort(input);

	// Assert
	const std::vector<int>& result = pm_.getSortedVector();
	ASSERT_EQ(result.size(), count);
	EXPECT_TRUE(isSorted(result));
	EXPECT_EQ(result, expected);
	EXPECT_EQ(listToVector(pm_.getSortedList()), expected);
	EXPECT_EQ(listToVector(pm_.getSortedList()), result);
}

TEST_F(PmergeMeSort100Test, Sorts200UniqueRandomNumbersLikeStdSort)
{
	// Arrange — 200 numeros unicos barajados (equivalente a orden aleatorio)
	const size_t count = 200;
	const unsigned int seed = 12345U; // fija: reproducible; cambia para otra permutacion

	// Valores aleatorios entre 1 y 100000 (similar a: shuf -i 1-100000 -n 200)
	std::vector<int> input = makeRandomUniqueInRange(count, 1, 100000, seed);
	ASSERT_FALSE(input.empty());

	std::vector<int> expected = input;
	std::sort(expected.begin(), expected.end());

	// Act
	runSort(input);

	// Assert
	const std::vector<int>& result = pm_.getSortedVector();
	ASSERT_EQ(result.size(), count);
	EXPECT_TRUE(isSorted(result));
	EXPECT_EQ(result, expected);
	EXPECT_EQ(listToVector(pm_.getSortedList()), expected);
	EXPECT_EQ(listToVector(pm_.getSortedList()), result);
}

// -----------------------------------------------------------------------------
//  Basic & validation
// -----------------------------------------------------------------------------

// 1. One element (caso base)
TEST(PmergeMeBasic, OneElement)
{
	// ARRANGE
	PmergeMe pm;
	char* argv[] = {(char*)"42"};

	// Act
	ASSERT_TRUE(parseAndRun(pm, 1, argv));

	// Assert
	const std::vector<int>& result = pm.getSortedVector();

	EXPECT_EQ(result.size(), 1u);
	EXPECT_EQ(result[0], 42);
}

// 2. Two elements (swap básico)
TEST(PmergeMeBasic, TwoElements)
{
	// ARRANGE
	PmergeMe pm;
	char* argv[] = {(char*)"9", (char*)"1"};

	// Act
	ASSERT_TRUE(parseAndRun(pm, 2, argv));

	// Assert
	const std::vector<int>& result = pm.getSortedVector();
	ASSERT_EQ(result.size(), 2u);
	EXPECT_EQ(result[0], 1);
	EXPECT_EQ(result[1], 9);
	EXPECT_EQ(listToVector(pm.getSortedList()), result);
}


// 3. Three elements (caso impar)
TEST(PmergeMeBasic, ThreeElements)
{
	// ARRANGE
	PmergeMe pm;
	char* argv[] = {(char*)"5", (char*)"1", (char*)"3"};

	// Act
	ASSERT_TRUE(parseAndRun(pm, 3, argv));

	// Assert
	const std::vector<int>& result = pm.getSortedVector();
	EXPECT_TRUE(isSorted(result));
	EXPECT_EQ(result[0], 1);
	EXPECT_EQ(result[1], 3);
	EXPECT_EQ(result[2], 5);
	EXPECT_EQ(listToVector(pm.getSortedList()), result);
}

// -----------------------------
// 4. Invalid input (carácter)
// -----------------------------

TEST(PmergeMeValidation, InvalidCharacter)
{
	// ARRANGE
	PmergeMe pm;
	char* argv[] = {(char*)"5", (char*)"a", (char*)"3"};

	// WHEN
	// SuppressStdout ss;
	// SuppressStderr se;

	bool ok = pm.parseArguments(3, argv);

	// THEN
	EXPECT_FALSE(ok);
}


// ─────────────────────────────────────────────
// 5. Already sorted input rejected
// ─────────────────────────────────────────────
TEST(PmergeMeValidation, AlreadySorted)
{
	// ARRANGE
	PmergeMe pm;
	char* argv[] = {(char*)"1", (char*)"2", (char*)"3", (char*)"4"};

	// WHEN
	SuppressStdout ss;
	SuppressStderr se;

	bool ok = pm.parseArguments(4, argv);

	// THEN
	EXPECT_FALSE(ok);
}

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
