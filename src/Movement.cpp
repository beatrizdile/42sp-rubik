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
