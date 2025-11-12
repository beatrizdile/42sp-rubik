#include "Face.hpp"

std::ostream& operator<<(std::ostream& os, Face face) {
  switch (face) {
    case UP:
      return os << "UP";
    case DOWN:
      return os << "DOWN";
    case LEFT:
      return os << "LEFT";
    case RIGHT:
      return os << "RIGHT";
    case FRONT:
      return os << "FRONT";
    case BACK:
      return os << "BACK";
  }
  return os << "UnknownFace";
}

void getFaceColor(Face face, float color[3]) {
  switch (face) {
    case UP:
      color[0] = YELLOW[0];
      color[1] = YELLOW[1];
      color[2] = YELLOW[2];
      break;
    case DOWN:
      color[0] = WHITE[0];
      color[1] = WHITE[1];
      color[2] = WHITE[2];
      break;
    case LEFT:
      color[0] = RED[0];
      color[1] = RED[1];
      color[2] = RED[2];
      break;
    case RIGHT:
      color[0] = ORANGE[0];
      color[1] = ORANGE[1];
      color[2] = ORANGE[2];
      break;
    case FRONT:
      color[0] = GREEN[0];
      color[1] = GREEN[1];
      color[2] = GREEN[2];
      break;
    case BACK:
      color[0] = BLUE[0];
      color[1] = BLUE[1];
      color[2] = BLUE[2];
      break;
  }
}

void getFacePositionCoordinates(Face face, float& x, float& y, float& z) {
  float coord = 1.0f;
  switch (face) {
    case UP:
      x = 0.0f;
      y = coord;
      z = 0.0f;
      break;
    case DOWN:
      x = 0.0f;
      y = -coord;
      z = 0.0f;
      break;
    case LEFT:
      x = -coord;
      y = 0.0f;
      z = 0.0f;
      break;
    case RIGHT:
      x = coord;
      y = 0.0f;
      z = 0.0f;
      break;
    case FRONT:
      x = 0.0f;
      y = 0.0f;
      z = coord;
      break;
    case BACK:
      x = 0.0f;
      y = 0.0f;
      z = -coord;
      break;
  }
}
