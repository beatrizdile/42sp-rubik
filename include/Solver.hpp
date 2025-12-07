#pragma once

#include <array>
#include <iostream>
#include <queue>
#include <cstring>

#include "Corner.hpp"
#include "Edge.hpp"
#include "Movement.hpp"
#include "Cube.hpp"

class Solver {
 private:
  struct Data {
    int64_t id;
    char move_set[200];
  };
  std::vector<Data> database;

 public:
  Solver() {};
  Solver(std::string filename);

  ~Solver() {};

  void save_to_file(std::string filename) const;
  void bfs(std::vector<Movement> valid_moves, Cube::HashType hash_type);
  std::vector<Movement> get_solve(int64_t id);
};
