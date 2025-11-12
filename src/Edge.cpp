#include "Edge.hpp"

std::ostream& operator<<(std::ostream& os, Edge edge) {
  switch (edge) {
    case UR:
      return os << "UR";
    case UF:
      return os << "UF";
    case UL:
      return os << "UL";
    case UB:
      return os << "UB";
    case DR:
      return os << "DR";
    case DF:
      return os << "DF";
    case DL:
      return os << "DL";
    case DB:
      return os << "DB";
    case FR:
      return os << "FR";
    case FL:
      return os << "FL";
    case BL:
      return os << "BL";
    case BR:
      return os << "BR";
  }
  return os << "UnknownEdge";
}

std::ostream& operator<<(std::ostream& os, EdgeOrientation ori) {
  switch (ori) {
    case EDGE_ORI_0:
      return os << "EDGE_ORI_0";
    case EDGE_ORI_1:
      return os << "EDGE_ORI_1";
  }
  return os << "UNKNOWN_EDGE_ORIENTATION";
}

EdgeData::EdgeData(Edge e) : edge(e), ori(EDGE_ORI_0) {}

bool EdgeData::operator==(const EdgeData& other) const {
  return edge == other.edge && ori == other.ori;
}

std::ostream& operator<<(std::ostream& os, const EdgeData& edge) {
  os << "{ edge: " << edge.edge << ", ori: " << edge.ori << " }";
  return os;
}

void getEdgePositionCoordinates(Edge edge, float& x, float& y, float& z) {
  const float coord = 1.0f;
  switch (edge) {
    case UR:
      x = coord;
      y = coord;
      z = 0.0f;
      break;
    case UF:
      x = 0.0f;
      y = coord;
      z = coord;
      break;
    case UL:
      x = -coord;
      y = coord;
      z = 0.0f;
      break;
    case UB:
      x = 0.0f;
      y = coord;
      z = -coord;
      break;
    case DR:
      x = coord;
      y = -coord;
      z = 0.0f;
      break;
    case DF:
      x = 0.0f;
      y = -coord;
      z = coord;
      break;
    case DL:
      x = -coord;
      y = -coord;
      z = 0.0f;
      break;
    case DB:
      x = 0.0f;
      y = -coord;
      z = -coord;
      break;
    case FR:
      x = coord;
      y = 0.0f;
      z = coord;
      break;
    case FL:
      x = -coord;
      y = 0.0f;
      z = coord;
      break;
    case BL:
      x = -coord;
      y = 0.0f;
      z = -coord;
      break;
    case BR:
      x = coord;
      y = 0.0f;
      z = -coord;
      break;
  }
}

void getFaces(Edge edge, Face faces[2]) {
  switch (edge) {
    case UR:
      faces[0] = UP;
      faces[1] = RIGHT;
      break;
    case UF:
      faces[0] = UP;
      faces[1] = FRONT;
      break;
    case UL:
      faces[0] = UP;
      faces[1] = LEFT;
      break;
    case UB:
      faces[0] = UP;
      faces[1] = BACK;
      break;
    case DR:
      faces[0] = DOWN;
      faces[1] = RIGHT;
      break;
    case DF:
      faces[0] = DOWN;
      faces[1] = FRONT;
      break;
    case DL:
      faces[0] = DOWN;
      faces[1] = LEFT;
      break;
    case DB:
      faces[0] = DOWN;
      faces[1] = BACK;
      break;
    case FR:
      faces[0] = FRONT;
      faces[1] = RIGHT;
      break;
    case FL:
      faces[0] = FRONT;
      faces[1] = LEFT;
      break;
    case BL:
      faces[0] = BACK;
      faces[1] = LEFT;
      break;
    case BR:
      faces[0] = BACK;
      faces[1] = RIGHT;
      break;
  }
}

std::map<Face, float[3]> EdgeData::getFaceColors(Edge position) const {
  std::map<Face, float[3]> face_colors;
  Face faces[2];
  getFaces(position, faces);
  int base_index = static_cast<int>(edge);
  for (int i = 0; i < 2; i++) {
    int rotated_index = (i + static_cast<int>(ori)) % 2;
    for (int j = 0; j < 3; j++) {
      face_colors[faces[i]][j] = edge_base_colors[base_index][rotated_index][j];
    }
  }
  return face_colors;
}
