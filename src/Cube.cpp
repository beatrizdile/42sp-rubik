#include "Cube.hpp"

Cube::Cube() : corners{{
                   CornerData(URF),  // 0 esse -> 3
                   CornerData(UFL),  // 1
                   CornerData(ULB),  // 2
                   CornerData(UBR),  // 3 esse -> 7
                   CornerData(DFR),  // 4 esse -> 3
                   CornerData(DLF),  // 5
                   CornerData(DBL),  // 6
                   CornerData(DRB),  // 7 esse -> 4
               }},
               edges{{
                   EdgeData(UR),  // 0 esse -> 11
                   EdgeData(UF),  // 1
                   EdgeData(UL),  // 2
                   EdgeData(UB),  // 3
                   EdgeData(DR),  // 4 esse -> 8
                   EdgeData(DF),  // 5
                   EdgeData(DL),  // 6
                   EdgeData(DB),  // 7
                   EdgeData(FR),  // 8 esse -> 0
                   EdgeData(FL),  // 9
                   EdgeData(BL),  // 10
                   EdgeData(BR),  // 11 esse -> 4
               }} {}

Cube::~Cube() {}

std::ostream& operator<<(std::ostream& os, const Cube& cube) {
  os << "Corners:" << std::endl;
  for (size_t i = 0; i < cube.corners.size(); i++) {
    os << "[" << i << "] = " << cube.corners[i] << std::endl;
  }
  os << std::endl;

  os << "Edges:" << std::endl;
  for (size_t i = 0; i < cube.edges.size(); i++) {
    os << "[" << i << "] = " << cube.edges[i] << std::endl;
  }
  return os;
}

void Cube::rotate(Movement movement) {
  int quantity = movement.type;
  for (int i = 0; i < quantity; i++) {
    switch (movement.move) {
      case FRONT:
        rotate_front();
        break;
      case BACK:
        rotate_back();
        break;
      case UP:
        rotate_up();
        break;
      case DOWN:
        rotate_down();
        break;
      case LEFT:
        rotate_left();
        break;
      case RIGHT:
        rotate_right();
        break;
    }
  }
}

void Cube::rotate_front() {
  CornerData corner_temp = corners[URF];
  corners[URF] = corners[UFL];
  corners[UFL] = corners[DLF];
  corners[DLF] = corners[DFR];
  corners[DFR] = corner_temp;

  EdgeData edge_temp = edges[FR];
  edges[FR] = edges[UF];
  edges[UF] = edges[FL];
  edges[FL] = edges[DF];
  edges[DF] = edge_temp;
}

void Cube::rotate_back() {
  CornerData corner_temp = corners[DRB];
  corners[DRB] = corners[DBL];
  corners[DBL] = corners[ULB];
  corners[ULB] = corners[UBR];
  corners[UBR] = corner_temp;

  EdgeData edge_temp = edges[BR];
  edges[BR] = edges[DB];
  edges[DB] = edges[BL];
  edges[BL] = edges[UB];
  edges[UB] = edge_temp;
}

void Cube::rotate_up() {
  CornerData corner_temp = corners[URF];
  corners[URF] = corners[UFL];
  corners[UFL] = corners[ULB];
  corners[ULB] = corners[UBR];
  corners[UBR] = corner_temp;

  EdgeData edge_temp = edges[UR];
  edges[UR] = edges[UF];
  edges[UF] = edges[UL];
  edges[UL] = edges[UB];
  edges[UB] = edge_temp;
}

void Cube::rotate_down() {
  CornerData corner_temp = corners[DRB];
  corners[DRB] = corners[DBL];
  corners[DBL] = corners[DLF];
  corners[DLF] = corners[DFR];
  corners[DFR] = corner_temp;

  EdgeData edge_temp = edges[DB];
  edges[DB] = edges[DL];
  edges[DL] = edges[DF];
  edges[DF] = edges[DR];
  edges[DR] = edge_temp;
}

void Cube::rotate_left() {
  CornerData corner_temp = corners[UFL];
  corners[UFL] = corners[ULB];
  corners[ULB] = corners[DBL];
  corners[DBL] = corners[DLF];
  corners[DLF] = corner_temp;

  EdgeData edge_temp = edges[FL];
  edges[FL] = edges[UL];
  edges[UL] = edges[BL];
  edges[BL] = edges[DL];
  edges[DL] = edge_temp;
}

void Cube::rotate_right() {
  CornerData corner_temp = corners[UBR];
  corners[UBR] = corners[URF];
  corners[URF] = corners[DFR];
  corners[DFR] = corners[DRB];
  corners[DRB] = corner_temp;

  EdgeData edge_temp = edges[BR];
  edges[BR] = edges[UR];
  edges[UR] = edges[FR];
  edges[FR] = edges[DR];
  edges[DR] = edge_temp;
}

bool Cube::operator==(const Cube& other) const {
  for (size_t i = 0; i < corners.size(); i++) {
    if (!(corners[i] == other.corners[i])) {
      return false;
    }
  }

  for (size_t i = 0; i < edges.size(); i++) {
    if (!(edges[i] == other.edges[i])) {
      return false;
    }
  }

  return true;
}

bool Cube::is_solved() const {
  for (size_t i = 0; i < corners.size(); i++) {
    if (corners[i].corner != static_cast<Corner>(i) || corners[i].ori != CORNER_ORI_0) {
      return false;
    }
  }

  for (size_t i = 0; i < edges.size(); i++) {
    if (edges[i].edge != static_cast<Edge>(i) || edges[i].ori != EDGE_ORI_0) {
      return false;
    }
  }

  return true;
}
