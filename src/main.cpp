#include <iostream>
#include <sstream>
#include <string>

#include "Cube.hpp"
#include "Movement.hpp"

int main(int argc, char** argv) {
	if (argc != 2) {
		std::cerr << "Invalid arguments" << std::endl;
		return (1);
	}

    std::stringstream ss(argv[1]);
    std::string word;

    while (ss >> word) {
		try {
			Movement movement(word);
		} catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;
			return 1;
		}
	}
}
