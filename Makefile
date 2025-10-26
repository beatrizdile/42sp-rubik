NAME 			= rubik
CC 				= c++
FLAGS 			= -Wall -Wextra -Werror
VALGRIND 		= valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

SRC 			= $(wildcard src/*.cpp)
INCLUDE_FILES 	= $(wildcard inc/*.hpp)
INCLUDE_FLAG 	= -Iinc

all: $(NAME)

$(NAME): $(SRC) $(INCLUDE_FILES)
	$(CC) $(FLAGS) $(INCLUDE_FLAG) $(SRC) -o $(NAME)

clean:
	rm -rf $(NAME)

fclean: clean

re: fclean all

valgrind: all
	@$(VALGRIND)

v: valgrind