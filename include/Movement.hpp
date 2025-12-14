#pragma once

#include <iostream>
#include <sstream>
#include <vector>

#include "Corner.hpp"
#include "Edge.hpp"
#include "Movement.hpp"

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
  bool operator==(const Movement& other) const;
  Movement reverse() const;
};

std::vector<Movement> parseMovements(const std::string& input);
float getMoveAngle(MoveType type);
bool isPieceOnMove(Move move, Corner corner);
bool isPieceOnMove(Move move, Edge edge);
bool isPieceOnMove(Move move, Face face);
Movement randomMovement();
std::vector<Movement> optimizeMovements(const std::vector<Movement>& movements);
