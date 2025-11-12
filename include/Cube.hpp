#include <array>
#include <iostream>

#include "Corner.hpp"
#include "Edge.hpp"
#include "Movement.hpp"

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
  std::vector<Movement> solve();

 private:
  void rotate_front();
  void rotate_back();
  void rotate_up();
  void rotate_down();
  void rotate_left();
  void rotate_right();
};
