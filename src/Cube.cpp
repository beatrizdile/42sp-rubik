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
  corners[URF].ori = static_cast<CornerOrientation>((static_cast<int>(corners[URF].ori) + 2) % 3);
  corners[UFL].ori = static_cast<CornerOrientation>((static_cast<int>(corners[UFL].ori) + 1) % 3);
  corners[DLF].ori = static_cast<CornerOrientation>((static_cast<int>(corners[DLF].ori) + 2) % 3);
  corners[DFR].ori = static_cast<CornerOrientation>((static_cast<int>(corners[DFR].ori) + 1) % 3);

  edges[FR].ori = static_cast<EdgeOrientation>((static_cast<int>(edges[FR].ori) + 1) % 2);
  edges[UF].ori = static_cast<EdgeOrientation>((static_cast<int>(edges[UF].ori) + 1) % 2);
  edges[FL].ori = static_cast<EdgeOrientation>((static_cast<int>(edges[FL].ori) + 1) % 2);
  edges[DF].ori = static_cast<EdgeOrientation>((static_cast<int>(edges[DF].ori) + 1) % 2);

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
  corners[DRB].ori = static_cast<CornerOrientation>((static_cast<int>(corners[DRB].ori) + 2) % 3);
  corners[DBL].ori = static_cast<CornerOrientation>((static_cast<int>(corners[DBL].ori) + 1) % 3);
  corners[ULB].ori = static_cast<CornerOrientation>((static_cast<int>(corners[ULB].ori) + 2) % 3);
  corners[UBR].ori = static_cast<CornerOrientation>((static_cast<int>(corners[UBR].ori) + 1) % 3);

  edges[BR].ori = static_cast<EdgeOrientation>((static_cast<int>(edges[BR].ori) + 1) % 2);
  edges[DB].ori = static_cast<EdgeOrientation>((static_cast<int>(edges[DB].ori) + 1) % 2);
  edges[BL].ori = static_cast<EdgeOrientation>((static_cast<int>(edges[BL].ori) + 1) % 2);
  edges[UB].ori = static_cast<EdgeOrientation>((static_cast<int>(edges[UB].ori) + 1) % 2);

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
  corners[UFL].ori = static_cast<CornerOrientation>((static_cast<int>(corners[UFL].ori) + 2) % 3);
  corners[DLF].ori = static_cast<CornerOrientation>((static_cast<int>(corners[DLF].ori) + 1) % 3);
  corners[DBL].ori = static_cast<CornerOrientation>((static_cast<int>(corners[DBL].ori) + 2) % 3);
  corners[ULB].ori = static_cast<CornerOrientation>((static_cast<int>(corners[ULB].ori) + 1) % 3);

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
  corners[UBR].ori = static_cast<CornerOrientation>((static_cast<int>(corners[UBR].ori) + 2) % 3);
  corners[URF].ori = static_cast<CornerOrientation>((static_cast<int>(corners[URF].ori) + 1) % 3);
  corners[DFR].ori = static_cast<CornerOrientation>((static_cast<int>(corners[DFR].ori) + 2) % 3);
  corners[DRB].ori = static_cast<CornerOrientation>((static_cast<int>(corners[DRB].ori) + 1) % 3);

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
