CXX = c++

CPP_FLAGS = -Wall -Wextra -Werror -std=c++98 -O2 -MMD -fsanitize=address \
	-DRESETT="\"\\033[0m\"" \
	-DRED="\"\\033[31m\"" \
	-DGREEN="\"\\033[32m\"" \
	-DYELLOW="\"\\033[33m\"" \
	-DBLUE="\"\\033[34m\"" \
	-DMAGENTA="\"\\033[35m\"" \
	-DCYAN="\"\\033[36m\"" \
	-DWHITE="\"\\033[37m\""

NAME = btc

SRCS = main.cpp BitcoinExchange.cpp

OBJS = $(SRCS:.cpp=.o)
DEPENDS = $(OBJS:.o=.d)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CPP_FLAGS) -o $(NAME) $(OBJS)

%.o: %.cpp Makefile
	$(CXX) $(CPP_FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS) $(DEPENDS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

-include $(DEPENDS)
test:
	@$(CXX) $(CPP_FLAGS) -I. tests/unit_tests.cpp BitcoinExchange.cpp -o unit_test_run
	@./unit_test_run
	@rm -f unit_test_run

.PHONY: all clean fclean re test
