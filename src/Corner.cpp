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
