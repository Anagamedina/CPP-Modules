# =============================================================================
# PmergeMe — unit tests (GoogleTest vendored in ../extern/googletest)
#
# First time:
#   make setup    # downloads googletest into ex02/extern/ (needs git + network)
#   make
#   ./run_tests
#
# From ex02 root:
#   make test
# =============================================================================

CXX			= c++
GTEST_INC = -I$(GTEST_DIR)/googletest/include
CXXFLAGS	= -Wall -Wextra -Werror -std=c++17 -I.. $(GTEST_INC)

NAME		= run_tests
SRCS		= pmergeme_test.cpp ../PmergeMe.cpp
OBJS		= $(SRCS:.cpp=.o)

# --- GoogleTest (local copy, not system -lgtest) -----------------------------
GTEST_VERSION	= v1.14.0
GTEST_DIR		= ../extern/googletest
GTEST_ALL_CC	= $(GTEST_DIR)/googletest/src/gtest-all.cc
GTEST_ALL_OBJ	= gtest-all.o

GTEST_CXXFLAGS	= -Wall -Wextra -Werror -std=c++17 \
				  -I$(GTEST_DIR)/googletest \
				  -I$(GTEST_DIR)/googletest/include

# =============================================================================
# Targets
# =============================================================================

all: $(GTEST_ALL_CC) $(NAME)

$(NAME): $(OBJS) $(GTEST_ALL_OBJ)
	$(CXX) $(CXXFLAGS) $(OBJS) $(GTEST_ALL_OBJ) -pthread -o $(NAME)

# Compile googletest amalgamation (once)
$(GTEST_ALL_OBJ): $(GTEST_ALL_CC)
	$(CXX) $(GTEST_CXXFLAGS) -c $(GTEST_ALL_CC) -o $(GTEST_ALL_OBJ)

# Download googletest only if missing
$(GTEST_ALL_CC):
	@$(MAKE) --no-print-directory setup

setup:
	@mkdir -p ../extern
	@if [ ! -f "$(GTEST_ALL_CC)" ]; then \
		echo ">> Cloning GoogleTest $(GTEST_VERSION) into $(GTEST_DIR)..."; \
		git clone --depth 1 --branch $(GTEST_VERSION) \
			https://github.com/google/googletest.git $(GTEST_DIR); \
	else \
		echo ">> GoogleTest already present at $(GTEST_DIR)"; \
	fi

# Test / production objects
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

../%.o: ../%.cpp ../PmergeMe.hpp ../Utils.hpp Makefile
	$(CXX) $(CXXFLAGS) -c $< -o $@

# =============================================================================
# Clean
# =============================================================================

clean:
	rm -f $(OBJS) $(GTEST_ALL_OBJ)

fclean: clean
	rm -f $(NAME)

# Removes downloaded googletest (optional)
distclean: fclean
	rm -rf $(GTEST_DIR)

re: fclean all

.PHONY: all clean fclean re setup distclean
