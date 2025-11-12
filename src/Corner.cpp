#include "Corner.hpp"

std::ostream& operator<<(std::ostream& os, Corner corner) {
  switch (corner) {
    case URF:
      return os << "URF";
    case UFL:
      return os << "UFL";
    case ULB:
      return os << "ULB";
    case UBR:
      return os << "UBR";
    case DFR:
      return os << "DFR";
    case DLF:
      return os << "DLF";
    case DBL:
      return os << "DBL";
    case DRB:
      return os << "DRB";
  }
  return os << "UnknownCorner";
}

std::ostream& operator<<(std::ostream& os, CornerOrientation ori) {
  switch (ori) {
    case CORNER_ORI_0:
      return os << "CORNER_ORI_0";
    case CORNER_ORI_1:
      return os << "CORNER_ORI_1";
    case CORNER_ORI_2:
      return os << "CORNER_ORI_2";
  }
  return os << "UNKNOWN_CORNER_ORIENTATION";
}

CornerData::CornerData(Corner c) : corner(c), ori(CORNER_ORI_0) {}

bool CornerData::operator==(const CornerData& other) const {
  return corner == other.corner && ori == other.ori;
}

std::ostream& operator<<(std::ostream& os, const CornerData& corner) {
  os << "{ corner: " << corner.corner << ", ori: " << corner.ori << " }";
  return os;
}

void getCornerPositionCoordinates(Corner corner, float& x, float& y, float& z) {
  const float coord = 1.0f;
  switch (corner) {
    case URF:
      x = coord;
      y = coord;
      z = coord;
      break;
    case UFL:
      x = -coord;
      y = coord;
      z = coord;
      break;
    case ULB:
      x = -coord;
      y = coord;
      z = -coord;
      break;
    case UBR:
      x = coord;
      y = coord;
      z = -coord;
      break;
    case DFR:
      x = coord;
      y = -coord;
      z = coord;
      break;
    case DLF:
      x = -coord;
      y = -coord;
      z = coord;
      break;
    case DBL:
      x = -coord;
      y = -coord;
      z = -coord;
      break;
    case DRB:
      x = coord;
      y = -coord;
      z = -coord;
      break;
  }
}

void getFaces(Corner corner, Face faces[3]) {
  switch (corner) {
    case URF:
      faces[0] = UP;
      faces[1] = RIGHT;
      faces[2] = FRONT;
      break;
    case UFL:
      faces[0] = UP;
      faces[1] = FRONT;
      faces[2] = LEFT;
      break;
    case ULB:
      faces[0] = UP;
      faces[1] = LEFT;
      faces[2] = BACK;
      break;
    case UBR:
      faces[0] = UP;
      faces[1] = BACK;
      faces[2] = RIGHT;
      break;
    case DFR:
      faces[0] = DOWN;
      faces[1] = FRONT;
      faces[2] = RIGHT;
      break;
    case DLF:
      faces[0] = DOWN;
      faces[1] = LEFT;
      faces[2] = FRONT;
      break;
    case DBL:
      faces[0] = DOWN;
      faces[1] = BACK;
      faces[2] = LEFT;
      break;
    case DRB:
      faces[0] = DOWN;
      faces[1] = RIGHT;
      faces[2] = BACK;
      break;
  }
}

std::map<Face, float[3]> CornerData::getFaceColors(Corner position) const {
  std::map<Face, float[3]> face_colors;
  Face faces[3];
  getFaces(position, faces);
  int base_index = static_cast<int>(this->corner);
  for (int i = 0; i < 3; i++) {
    int rotated_index = (i + 3 - static_cast<int>(ori)) % 3;
    for (int j = 0; j < 3; j++) {
      face_colors[faces[i]][j] = corner_base_colors[base_index][rotated_index][j];
    }
  }
  return face_colors;
}
