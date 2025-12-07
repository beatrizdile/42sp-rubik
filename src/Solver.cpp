#include "Solver.hpp"

#include <fstream>

Solver::Solver(std::string filename) {
  std::ifstream in(filename, std::ios::binary);

  uint32_t database_size;
  in.read((char*)&database_size, sizeof(database_size));
  database.resize(database_size);
  in.read((char*)database.data(), database_size * sizeof(Solver::Data));
  in.close();
};

void Solver::save_to_file(std::string filename) const {
  std::ofstream out(filename, std::ios::binary);

  uint32_t database_size = database.size();
  out.write((char*)&database_size, sizeof(database_size));
  out.write((char*)database.data(), database_size * sizeof(Solver::Data));
  out.close();
};

std::vector<Movement> Solver::get_solve(int64_t id) {
  for (auto data : database) {
    if (data.id == id) {
      return parseMovements(data.move_set);
    }
  }

  return std::vector<Movement>();
}

std::string make_string_solution(Cube cube) {
  std::ostringstream oss;
  bool first = true;
  for (auto it = cube.movement_set.rbegin(); it != cube.movement_set.rend(); ++it) {
    auto movement = it->reverse();
    if (!first) oss << ' ';
    first = false;
    oss << movement;
  }

  return oss.str();
}

void Solver::bfs(std::vector<Movement> valid_moves, Cube::HashType hash_type) {
  std::queue<Cube> cubes;
  cubes.push(Cube());

  while (!cubes.empty()) {
    Cube cube = cubes.front();
    cubes.pop();
    for (Movement move : valid_moves) {
      Cube current(cube);
      current.rotate(move);
      int64_t id = current.get_id(hash_type);
      if (get_solve(id).empty()) {
        std::string solution = make_string_solution(current);
        Data data{};
        data.id = id;
        std::strncpy(data.move_set, solution.c_str(), sizeof(data.move_set));
        data.move_set[solution.size()] = '\0';
        database.push_back(data);
        cubes.push(current);
      }
    }
    std::cout << "database: " << database.size() << " cubes: " << cubes.size() << std::endl;
  }
};
