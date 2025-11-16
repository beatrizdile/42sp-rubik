PROJECT_NAME 	= rubik
CXX						= c++
CXXFLAGS			= -Wall -Wextra -Werror -std=c++20
OPTFLAGS			= -O3
DEBUGFLAGS		= -g -DDEBUG
INCLUDE_FLAGS	= -Iinclude
LDLIBS				= -lGL -lGLU -lglut -lm

SRC_DIR 		= src
OBJ_DIR 		= obj
INC_DIR			= include
TEST_DIR 		= tests
TEST_OBJ_DIR 	= obj/tests

SRC 			= $(wildcard $(SRC_DIR)/*.cpp)
OBJ 			= $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
INCLUDE_FILES 	= $(wildcard $(INC_DIR)/*.hpp)

TEST_SRC 		= $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJ 		= $(TEST_SRC:$(TEST_DIR)/%.cpp=$(TEST_OBJ_DIR)/%.o)
TEST_BIN 		= run_tests
CATCH_HEADER	= $(TEST_DIR)/catch_amalgamated.hpp
TEST_SAFE_OBJ	= $(filter-out $(OBJ_DIR)/main.o $(OBJ_DIR)/Draw.o, $(OBJ))

.PHONY: all clean fclean re test run debug

all: $(PROJECT_NAME)

$(PROJECT_NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OPTFLAGS) $^ -o $@ $(LDLIBS)

debug: CXXFLAGS += $(DEBUGFLAGS)
debug: OPTFLAGS = 
debug: re

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(INCLUDE_FILES) | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(OPTFLAGS) $(INCLUDE_FLAGS) -c $< -o $@

$(TEST_OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp $(INCLUDE_FILES) | $(TEST_OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(OPTFLAGS) $(INCLUDE_FLAGS) -c $< -o $@

test: $(CATCH_HEADER) $(TEST_BIN)
	@./$(TEST_BIN)

$(TEST_BIN): $(OBJ) $(TEST_OBJ) $(INCLUDE_FILES) $(CATCH_HEADER) | $(TEST_OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(OPTFLAGS) $(TEST_SAFE_OBJ) $(TEST_OBJ) -o $@

$(CATCH_HEADER):
	@echo "Baixando Catch2..."
	@curl -sSL https://raw.githubusercontent.com/catchorg/Catch2/v2.x/single_include/catch2/catch.hpp -o $@

run: $(PROJECT_NAME)
	@./$(PROJECT_NAME) "$(ARGS)"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(TEST_OBJ_DIR):
	@mkdir -p $(TEST_OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(PROJECT_NAME) $(TEST_BIN)

re: fclean all
