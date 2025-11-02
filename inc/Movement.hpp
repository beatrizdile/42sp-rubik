#pragma once

#include <iostream>
#include <vector>

enum MoveType {
  CLOCK_WISE,
  ANTI_CLOCK_WISE,
  TWICE,
};

enum Move {
  FRONT,
  BACK,
  UP,
  DOWN,
  LEFT,
  RIGHT,

};

class Movement {
 public:
  Move move;
  MoveType type;

  Movement() : move(FRONT), type(CLOCK_WISE) {}

  Movement(Move move, MoveType type) : move(move), type(type) {}

  Movement(Movement const& other) : move(other.move), type(other.type) {}

  Movement(std::string movement) {
    if (movement.size() == 0) {
      throw std::invalid_argument("Empty movement");
    }

    if (movement.size() > 2) {
      throw std::invalid_argument("Invalid movement: " + movement);
    }

    switch (movement[0]) {
      case 'F':
        move = FRONT;
        break;
      case 'B':
        move = BACK;
        break;
      case 'U':
        move = UP;
        break;
      case 'D':
        move = DOWN;
        break;
      case 'L':
        move = LEFT;
        break;
      case 'R':
        move = RIGHT;
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

  Movement& operator=(Movement const& other) {
    if (this != &other) {
      move = other.move;
      type = other.type;
    }
    return *this;
  }

	friend std::ostream& operator<<(std::ostream& os, const Movement& movement) {
		switch (movement.move) {
			case FRONT:
				os << "F";
				break;
			case BACK:
				os << "B";
				break;
			case UP:
				os << "U";
				break;
			case DOWN:
				os << "D";
				break;
			case LEFT:
				os << "L";
				break;
			case RIGHT:
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
};
