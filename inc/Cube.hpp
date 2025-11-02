#pragma once

#include <iostream>
#include <array>

#include "Movement.hpp"

enum Corner {
	URF,
	UFL,
	ULB,
	UBR,
	DFR,
	DLF,
	DBL,
	DRB,
};

enum Edge {
	UR,
	UF,
	UL,
	UB,
	DR,
	DF,
	DL,
	DB,
	FR,
	FL,
	BL,
	BR,
};

enum Orientation {
	DEFAULT,	// front matching, right 
	CLOCKWISE,
	ANTI_CLOCKWISE,
};

std::ostream& operator<<(std::ostream& os, Corner corner) {
    switch (corner) {
        case URF: return os << "URF";
        case UFL: return os << "UFL";
        case ULB: return os << "ULB";
        case UBR: return os << "UBR";
        case DFR: return os << "DFR";
        case DLF: return os << "DLF";
        case DBL: return os << "DBL";
        case DRB: return os << "DRB";
    }
    return os << "UnknownCorner";
}

std::ostream& operator<<(std::ostream& os, Edge edge) {
    switch (edge) {
        case UR: return os << "UR";
        case UF: return os << "UF";
        case UL: return os << "UL";
        case UB: return os << "UB";
        case DR: return os << "DR";
        case DF: return os << "DF";
        case DL: return os << "DL";
        case DB: return os << "DB";
        case FR: return os << "FR";
        case FL: return os << "FL";
        case BL: return os << "BL";
        case BR: return os << "BR";
    }
    return os << "UnknownEdge";
}

std::ostream& operator<<(std::ostream& os, Orientation ori) {
    switch (ori) {
        case DEFAULT:        return os << "DEFAULT";
        case CLOCKWISE:      return os << "CLOCKWISE";
        case ANTI_CLOCKWISE: return os << "ANTI_CLOCKWISE";
    }
    return os << "UnknownOrientation";
}

struct CornerData {
	Corner corner;
	Orientation ori;

	CornerData(Corner c) : corner(c), ori(DEFAULT) {}

	friend std::ostream& operator<<(std::ostream& os, const CornerData& corner) {
		os << "{ corner: " << corner.corner << ", ori: " <<  corner.ori << " }";
		return os;
	}
};

struct EdgeData {
	Edge edge;
	Orientation ori;

	EdgeData(Edge e) : edge(e), ori(DEFAULT) {}
	

	friend std::ostream& operator<<(std::ostream& os, const EdgeData& edge) {
		os << "{ edge: " << edge.edge << ", ori: " <<  edge.ori << " }";
		return os;
	}
};

class Cube {
	public:
	 std::array<CornerData, 8> corners;
     std::array<EdgeData, 12> edges;

  Cube() : corners{{
            CornerData(URF), // 0 esse -> 3
            CornerData(UFL), // 1
            CornerData(ULB), // 2
            CornerData(UBR), // 3 esse -> 7
            CornerData(DFR), // 4 esse -> 3
            CornerData(DLF), // 5
            CornerData(DBL), // 6
            CornerData(DRB), // 7 esse -> 4
        }},
          edges{{
            EdgeData(UR), // 0 esse -> 11
            EdgeData(UF), // 1
            EdgeData(UL), // 2
            EdgeData(UB), // 3
            EdgeData(DR), // 4 esse -> 8
            EdgeData(DF), // 5
            EdgeData(DL), // 6
            EdgeData(DB), // 7
            EdgeData(FR), // 8 esse -> 0
            EdgeData(FL), // 9
            EdgeData(BL), // 10
            EdgeData(BR), // 11 esse -> 4
        }}
	{}

  ~Cube() {}

  	friend std::ostream& operator<<(std::ostream& os, const Cube& cube) {
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

  void rotate(Movement movement) {
	int quantity = movement.type;

	for (int i = 0; i < quantity; i++) {
		switch (movement.move) {
			case FRONT:
				rotate_front();
			case BACK:
				rotate_back();
			case UP:
				rotate_up();
			case DOWN:
				rotate_down();
			case LEFT:
				rotate_left();
			case RIGHT:
				rotate_right();

		}
	}
  }

  private:
	void rotate_front() {
		CornerData corner_temp = corners[0];
		corners[0] = corners[1];
		corners[1] = corners[5];
		corners[5] = corners[4];
		corners[4] = corner_temp;

		EdgeData edge_temp = edges[8];
		edges[8] = edges[1];
		edges[1] = edges[9];
		edges[9] = edges[5];
		edges[5] = edge_temp;
	}

	void rotate_back() {
		CornerData corner_temp = corners[7];
		corners[7] = corners[6];
		corners[6] = corners[2];
		corners[2] = corners[3];
		corners[3] = corner_temp;

		EdgeData edge_temp = edges[11];
		edges[11] = edges[7];
		edges[7] = edges[10];
		edges[10] = edges[3];
		edges[3] = edge_temp;
	}

	void rotate_up() {
		CornerData corner_temp = corners[0];
		corners[0] = corners[1];
		corners[1] = corners[2];
		corners[2] = corners[3];
		corners[3] = corner_temp;

		EdgeData edge_temp = edges[0];
		edges[0] = edges[1];
		edges[1] = edges[2];
		edges[2] = edges[3];
		edges[3] = edge_temp;
	}

	void rotate_down() {
		CornerData corner_temp = corners[7];
		corners[7] = corners[6];
		corners[6] = corners[5];
		corners[5] = corners[4];
		corners[4] = corner_temp;

		EdgeData edge_temp = edges[7];
		edges[7] = edges[6];
		edges[6] = edges[5];
		edges[5] = edges[4];
		edges[4] = edge_temp;
	}

	void rotate_left() {
		CornerData corner_temp = corners[1];
		corners[1] = corners[2];
		corners[2] = corners[6];
		corners[6] = corners[5];
		corners[5] = corner_temp;

		EdgeData edge_temp = edges[9];
		edges[9] = edges[2];
		edges[2] = edges[10];
		edges[10] = edges[6];
		edges[6] = edge_temp;
	}

	void rotate_right() {
		CornerData corner_temp = corners[3];
		corners[3] = corners[0];
		corners[0] = corners[4];
		corners[4] = corners[7];
		corners[7] = corner_temp;

		EdgeData edge_temp = edges[11];
		edges[11] = edges[0];
		edges[0] = edges[8];
		edges[8] = edges[4];
		edges[4] = edge_temp;
	}
};
