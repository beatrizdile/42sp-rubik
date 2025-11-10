#pragma once

#include <iostream>

enum Corner {
  URF = 0,  // Up-Right-Front corner
  UFL = 1,  // Up-Front-Left corner
  ULB = 2,  // Up-Left-Back corner
  UBR = 3,  // Up-Back-Right corner
  DFR = 4,  // Down-Front-Right corner
  DLF = 5,  // Down-Left-Front corner
  DBL = 6,  // Down-Back-Left corner
  DRB = 7,  // Down-Right-Back corner
};

enum CornerOrientation {
  CORNER_ORI_0 = 0,  // 0-degree twist (Default)
  CORNER_ORI_1 = 1,  // 120-degree twist (e.g., URF -> FLU)
  CORNER_ORI_2 = 2,  // 240-degree twist (e.g., URF -> RFU)
};

std::ostream& operator<<(std::ostream& os, Corner corner);
std::ostream& operator<<(std::ostream& os, CornerOrientation ori);

struct CornerData {
  Corner corner;
  CornerOrientation ori;

  CornerData(Corner c);
  bool operator==(const CornerData& other) const;
  friend std::ostream& operator<<(std::ostream& os, const CornerData& corner);
};
