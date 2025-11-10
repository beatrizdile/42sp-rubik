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

  try {
    std::vector<Movement> movements = parseMovements(argv[1]);
    Cube cube;

    return (EXIT_SUCCESS);
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    return (EXIT_FAILURE);
  }
}
