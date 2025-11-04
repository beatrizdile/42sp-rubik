#include <array>
#include <iostream>

#include "Movement.hpp"

enum Corner {
  URF = 0, // Up-Right-Front corner
  UFL = 1, // Up-Front-Left corner  
  ULB = 2, // Up-Left-Back corner
  UBR = 3, // Up-Back-Right corner
  DFR = 4, // Down-Front-Right corner
  DLF = 5, // Down-Left-Front corner
  DBL = 6, // Down-Back-Left corner
  DRB = 7, // Down-Right-Back corner
};

enum Edge {
  UR = 0, // Up-Right edge
  UF = 1, // Up-Front edge
  UL = 2, // Up-Left edge
  UB = 3, // Up-Back edge
  DR = 4, // Down-Right edge
  DF = 5, // Down-Front edge
  DL = 6, // Down-Left edge
  DB = 7, // Down-Back edge
  FR = 8, // Front-Right edge
  FL = 9, // Front-Left edge
  BL = 10, // Back-Left edge
  BR = 11, // Back-Right edge
};

enum CornerOrientation {
  CORNER_ORI_0 = 0, // 0-degree twist (Default)
  CORNER_ORI_1 = 1, // 120-degree twist (e.g., URF -> FLU)
  CORNER_ORI_2 = 2, // 240-degree twist (e.g., URF -> RFU)
};

enum EdgeOrientation {
  EDGE_ORI_0 = 0, // Not flipped (Default)
  EDGE_ORI_1 = 1, // Flipped
};

std::ostream& operator<<(std::ostream& os, Corner corner);
std::ostream& operator<<(std::ostream& os, Edge edge);
std::ostream& operator<<(std::ostream& os, CornerOrientation ori);
std::ostream& operator<<(std::ostream& os, EdgeOrientation ori);

struct CornerData {
  Corner corner;
  CornerOrientation ori;

  CornerData(Corner c);
  bool operator==(const CornerData& other) const;
  friend std::ostream& operator<<(std::ostream& os, const CornerData& corner);
};

struct EdgeData {
  Edge edge;
  EdgeOrientation ori;

  EdgeData(Edge e);
  bool operator==(const EdgeData& other) const;
  friend std::ostream& operator<<(std::ostream& os, const EdgeData& edge);
};

class Cube {
 public:
  std::array<CornerData, 8> corners;
  std::array<EdgeData, 12> edges;

  Cube();
  ~Cube();

  friend std::ostream& operator<<(std::ostream& os, const Cube& cube);
  void rotate(Movement movement);
  bool operator==(const Cube& other) const;
  bool is_solved() const;

 private:
  void rotate_front();
  void rotate_back();
  void rotate_up();
  void rotate_down();
  void rotate_left();
  void rotate_right();
};
