#pragma once

#include <array>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>

#include "Corner.hpp"
#include "Cube.hpp"
#include "Edge.hpp"
#include "Movement.hpp"

class Solver {
 private:
  struct Data {
    uint8_t moves[50];
    uint8_t length;
  };
  std::map<int64_t, Data> database;

 public:
  Solver() {};
  ~Solver() {};

  void save_to_file(std::string filename) const;
  void bfs(std::vector<Movement> valid_moves, Cube::HashType hash_type);
  static std::vector<Movement> get_solve(std::string filename, int64_t id);

 private:
  static std::vector<Movement> decodeMoves(const uint8_t* moves, uint8_t length);
  static std::vector<uint8_t> encodeMoves(const std::vector<Movement>& movements);
};
