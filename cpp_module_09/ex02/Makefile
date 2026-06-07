CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -g

NAME = PmergeMe
SRCS = main.cpp PmergeMe.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

%.o: %.cpp PmergeMe.hpp Makefile
	$(CXX) $(CXXFLAGS) -c $< -o $@

test:
	@$(MAKE) -C tests all
	@./tests/run_tests

clean:
	rm -f $(OBJS)
	@make -C tests clean

fclean: clean
	rm -f $(NAME)
	@make -C tests fclean

re: fclean all

.PHONY: all clean fclean re test
