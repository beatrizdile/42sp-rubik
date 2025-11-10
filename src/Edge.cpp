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
