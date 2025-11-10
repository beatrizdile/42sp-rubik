#pragma once

#include <iostream>

enum Edge {
  UR = 0,   // Up-Right edge
  UF = 1,   // Up-Front edge
  UL = 2,   // Up-Left edge
  UB = 3,   // Up-Back edge
  DR = 4,   // Down-Right edge
  DF = 5,   // Down-Front edge
  DL = 6,   // Down-Left edge
  DB = 7,   // Down-Back edge
  FR = 8,   // Front-Right edge
  FL = 9,   // Front-Left edge
  BL = 10,  // Back-Left edge
  BR = 11,  // Back-Right edge
};

enum EdgeOrientation {
  EDGE_ORI_0 = 0,  // Not flipped (Default)
  EDGE_ORI_1 = 1,  // Flipped
};

struct EdgeData {
  Edge edge;
  EdgeOrientation ori;

  EdgeData(Edge e);
  bool operator==(const EdgeData& other) const;
  friend std::ostream& operator<<(std::ostream& os, const EdgeData& edge);
};

std::ostream& operator<<(std::ostream& os, Edge edge);
std::ostream& operator<<(std::ostream& os, EdgeOrientation ori);
