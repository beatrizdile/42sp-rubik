#include "Movement.hpp"

Movement::Movement() : move(MOVE_FRONT), type(CLOCK_WISE) {}

Movement::Movement(Move move) : move(move), type(CLOCK_WISE) {}

Movement::Movement(Move move, MoveType type) : move(move), type(type) {}

Movement::Movement(Movement const& other) : move(other.move), type(other.type) {}

Movement::Movement(std::string movement) {
  if (movement.size() == 0) {
    throw std::invalid_argument("Empty movement");
  }

  if (movement.size() > 2) {
    throw std::invalid_argument("Invalid movement: " + movement);
  }

  switch (movement[0]) {
    case 'F':
      move = MOVE_FRONT;
      break;
    case 'B':
      move = MOVE_BACK;
      break;
    case 'U':
      move = MOVE_UP;
      break;
    case 'D':
      move = MOVE_DOWN;
      break;
    case 'L':
      move = MOVE_LEFT;
      break;
    case 'R':
      move = MOVE_RIGHT;
      break;
    default:
      throw std::invalid_argument("Invalid movement: " + movement);
  }

  type = CLOCK_WISE;
  if (movement.size() == 2) {
    switch (movement[1]) {
      case '\'':
        type = ANTI_CLOCK_WISE;
        break;
      case '2':
        type = TWICE;
        break;
      default:
        throw std::invalid_argument("Invalid movement: " + movement);
    }
  }
}

Movement& Movement::operator=(Movement const& other) {
  if (this != &other) {
    move = other.move;
    type = other.type;
  }
  return *this;
}

std::ostream& operator<<(std::ostream& os, const Movement& movement) {
  switch (movement.move) {
    case MOVE_FRONT:
      os << "F";
      break;
    case MOVE_BACK:
      os << "B";
      break;
    case MOVE_UP:
      os << "U";
      break;
    case MOVE_DOWN:
      os << "D";
      break;
    case MOVE_LEFT:
      os << "L";
      break;
    case MOVE_RIGHT:
      os << "R";
      break;
  }

  switch (movement.type) {
    case CLOCK_WISE:
      break;
    case ANTI_CLOCK_WISE:
      os << "'";
      break;
    case TWICE:
      os << "2";
      break;
  }

  return os;
}

std::vector<Movement> parseMovements(const std::string& input) {
  std::stringstream ss(input);
  std::string word;
  std::vector<Movement> movements;

  while (ss >> word) {
    Movement movement(word);
    movements.push_back(movement);
  }

  return movements;
}

float getMoveAngle(MoveType type) {
  switch (type) {
    case MoveType::CLOCK_WISE:
      return 90.0f;
    case MoveType::TWICE:
      return 180.0f;
    case MoveType::ANTI_CLOCK_WISE:
      return -90.0f;
  }

  return 0.0f;
}

Movement Movement::reverse() const {
  MoveType reversedType = CLOCK_WISE;
  switch (type) {
    case CLOCK_WISE:
      reversedType = ANTI_CLOCK_WISE;
      break;
    case ANTI_CLOCK_WISE:
      reversedType = CLOCK_WISE;
      break;
    case TWICE:
      reversedType = TWICE;
      break;
  }
  return Movement(move, reversedType);
}

bool isPieceOnMove(Move move, Corner corner) {
  switch (move) {
    case MOVE_FRONT:
      return corner == URF || corner == UFL || corner == DLF || corner == DFR;
    case MOVE_BACK:
      return corner == UBR || corner == ULB || corner == DBL || corner == DRB;
    case MOVE_UP:
      return corner == URF || corner == UFL || corner == ULB || corner == UBR;
    case MOVE_DOWN:
      return corner == DFR || corner == DLF || corner == DBL || corner == DRB;
    case MOVE_LEFT:
      return corner == UFL || corner == ULB || corner == DBL || corner == DLF;
    case MOVE_RIGHT:
      return corner == URF || corner == UBR || corner == DRB || corner == DFR;
  }
  return false;
}

bool isPieceOnMove(Move move, Edge edge) {
  switch (move) {
    case MOVE_FRONT:
      return edge == UF || edge == FR || edge == DF || edge == FL;
    case MOVE_BACK:
      return edge == UB || edge == BR || edge == DB || edge == BL;
    case MOVE_UP:
      return edge == UR || edge == UF || edge == UL || edge == UB;
    case MOVE_DOWN:
      return edge == DR || edge == DF || edge == DL || edge == DB;
    case MOVE_LEFT:
      return edge == UL || edge == FL || edge == DL || edge == BL;
    case MOVE_RIGHT:
      return edge == UR || edge == FR || edge == DR || edge == BR;
  }
  return false;
}

bool isPieceOnMove(Move move, Face face) {
  switch (move) {
    case MOVE_FRONT:
      return face == FRONT;
    case MOVE_BACK:
      return face == BACK;
    case MOVE_UP:
      return face == UP;
    case MOVE_DOWN:
      return face == DOWN;
    case MOVE_LEFT:
      return face == LEFT;
    case MOVE_RIGHT:
      return face == RIGHT;
  }
  return false;
}

Movement randomMovement() {
  Move moves[] = {MOVE_FRONT, MOVE_BACK, MOVE_UP, MOVE_DOWN, MOVE_LEFT, MOVE_RIGHT};
  MoveType types[] = {CLOCK_WISE, TWICE, ANTI_CLOCK_WISE};

  Move randomMove = moves[rand() % 6];
  MoveType randomType = types[rand() % 3];

  return Movement(randomMove, randomType);
}
