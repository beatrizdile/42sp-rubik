#pragma once

#include <iostream>
#include <vector>
#include <sstream>

enum MoveType {
  CLOCK_WISE = 1,
  TWICE = 2,
  ANTI_CLOCK_WISE = 3,
};

enum Move {
  MOVE_FRONT,
  MOVE_BACK,
  MOVE_UP,
  MOVE_DOWN,
  MOVE_LEFT,
  MOVE_RIGHT,
};

class Movement {
 public:
  Move move;
  MoveType type;

  Movement();
  Movement(Move move);
  Movement(Move move, MoveType type);
  Movement(Movement const& other);
  Movement(std::string movement);

  Movement& operator=(Movement const& other);
  friend std::ostream& operator<<(std::ostream& os, const Movement& movement);
};

std::vector<Movement> parseMovements(const std::string& input);
