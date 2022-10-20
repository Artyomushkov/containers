SRC		=	main.cpp tests/utils_test.cpp tests/vector_tests.cpp\
            tests/stack_tests.cpp tests/pair_test.cpp tests/map_tests.cpp tests/set_tests.cpp

HDRS	=	vector/vector.hpp \
			stack/stack.hpp \
			map/map.hpp \
			set/set.hpp \
			utils/utilities.hpp

NAME	=	ft_containers

.PHONY	:	all fclean

all		:	$(NAME)

$(NAME)	:	$(SRC) $(HDRS)
			g++ -Wall -Werror -Wextra -std=c++98 -g $(SRC) -o $(NAME)

fclean	:
			rm -f $(NAME)

re		:	fclean all