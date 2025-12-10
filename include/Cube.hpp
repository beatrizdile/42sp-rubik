#pragma once

#include <array>
#include <cstdint>
#include <iostream>

#include "Corner.hpp"
#include "Edge.hpp"
#include "Movement.hpp"

#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define RESET "\033[0m"

class Cube {
 public:
  enum HashType {
    FIRST_STEP,
    SECOND_STEP,
    THIRD_STEP,
    FOURTH_STEP
  };

  std::array<CornerData, 8> corners;
  std::array<EdgeData, 12> edges;
  std::vector<Movement> movement_set;

  Cube();
  Cube(Cube const& other);
  Cube& operator=(Cube const& other);
  ~Cube();

  friend std::ostream& operator<<(std::ostream& os, const Cube& cube);
  void rotate(Movement movement);
  bool operator==(const Cube& other) const;
  bool is_solved() const;
  std::vector<Movement> solve();
  void reset();
  void randomize(int random_moves_count = 20);
  int64_t get_id(HashType type);
  uint8_t getEdgePermutationIndex(uint8_t slice) const;

 private:
  void rotate_front();
  void rotate_back();
  void rotate_up();
  void rotate_down();
  void rotate_left();
  void rotate_right();
};
