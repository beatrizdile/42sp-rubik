#include <iostream>
#include <sstream>
#include <string>

#include "Cube.hpp"
#include "Movement.hpp"

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cerr << "Invalid number of arguments" << std::endl;
    return (1);
  }

  std::stringstream ss(argv[1]);
  std::string word;

  std::vector<Movement> movements;
  while (ss >> word) {
    try {
      Movement movement(word);
      movements.push_back(movement);
    } catch (const std::exception& e) {
      std::cerr << e.what() << std::endl;
      return (EXIT_FAILURE);
    }
  }

  Cube cube;

  std::cout << cube << std::endl << std::endl;

  std::cout << "Movements: ";
  for (const auto& movement : movements) {
    std::cout << movement << " ";
	cube.rotate(movement);
  }
  std::cout << std::endl << std::endl;

  std::cout << cube << std::endl;

  return (EXIT_SUCCESS);
}
