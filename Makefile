NAME 			= rubik
CC 				= c++
FLAGS 			= -Wall -Wextra -Werror -std=c++23
VALGRIND 		= valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -q

SRC_DIR 		= src
OBJ_DIR 		= obj
TEST_DIR 		= tests
TEST_OBJ_DIR 	= obj/tests

SRC 			= $(wildcard $(SRC_DIR)/*.cpp)
OBJ 			= $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

INCLUDE_FILES 	= $(wildcard include/*.hpp)
INCLUDE_FLAG 	= -Iinclude

TEST_SRC 			= $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJ 			= $(TEST_SRC:$(TEST_DIR)/%.cpp=$(TEST_OBJ_DIR)/%.o)
TEST_BIN 			= run_tests
CATCH_HEADER	= $(TEST_DIR)/catch_amalgamated.hpp

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(INCLUDE_FILES) | $(OBJ_DIR)
	$(CC) $(FLAGS) $(INCLUDE_FLAG) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(TEST_OBJ_DIR):
	mkdir -p $(TEST_OBJ_DIR)

clean:
	rm -rf $(NAME) $(TEST_BIN) $(OBJ_DIR)

fclean: clean

re: fclean all

test: $(CATCH_HEADER) $(TEST_BIN)
	@echo "Executando testes..."
	@./$(TEST_BIN)

$(TEST_OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp $(INCLUDE_FILES) | $(TEST_OBJ_DIR)
	$(CC) $(FLAGS) $(INCLUDE_FLAG) -c $< -o $@

$(CATCH_HEADER):
	curl -sSL https://raw.githubusercontent.com/catchorg/Catch2/v2.x/single_include/catch2/catch.hpp -o $(CATCH_HEADER)

$(TEST_BIN): $(OBJ) $(TEST_OBJ) $(INCLUDE_FILES) $(CATCH_HEADER) | $(TEST_OBJ_DIR)
	$(CC) $(FLAGS) $(filter-out $(OBJ_DIR)/main.o, $(OBJ)) $(TEST_OBJ) -o $(TEST_BIN)

run: $(NAME)
	./$(NAME) "$(ARGS)"

val: $(NAME)
	$(VALGRIND) ./$(NAME) "$(ARGS)"

.PHONY: all clean fclean re test run val
