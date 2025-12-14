#include "Solver.hpp"

#include <cstring>
#include <fstream>

void Solver::save_to_file(std::string filename) const {
  std::ofstream out(filename, std::ios::binary);

  size_t database_size = database.size();
  out.write((char*)&database_size, sizeof(database_size));

  for (const auto& pair : database) {
    out.write((char*)&pair.first, sizeof(pair.first));
    out.write((char*)&pair.second.length, sizeof(pair.second.length));
    out.write((char*)pair.second.moves, pair.second.length);
  }

  out.close();
};

std::vector<Movement> Solver::get_solve(std::string filename, int64_t id) {
  std::ifstream in(filename, std::ios::binary);

  size_t database_size;
  in.read((char*)&database_size, sizeof(database_size));

  for (size_t i = 0; i < database_size; ++i) {
    int64_t current_id;
    Data data;
    in.read((char*)&current_id, sizeof(current_id));
    in.read((char*)&data.length, sizeof(data.length));
    in.read((char*)data.moves, data.length);

    if (current_id == id) {
      in.close();
      return decodeMoves(data.moves, data.length);
    }
  }

  in.close();
  return std::vector<Movement>();
}

std::vector<Movement> Solver::decodeMoves(const uint8_t* moves, uint8_t length) {
  std::vector<Movement> result;
  for (uint8_t i = 0; i < length; ++i) {
    uint8_t encoded = moves[i];
    Move move_type = static_cast<Move>(encoded / 3);
    MoveType rotation = static_cast<MoveType>(encoded % 3 + 1);
    result.emplace_back(move_type, rotation);
  }
  return result;
}

std::vector<uint8_t> Solver::encodeMoves(const std::vector<Movement>& movements) {
  std::vector<uint8_t> encoded;
  for (const auto& move : movements) {
    uint8_t encoded_move = static_cast<uint8_t>(move.move) * 3 + (static_cast<uint8_t>(move.type) - 1);
    encoded.push_back(encoded_move);
  }
  return encoded;
}

std::vector<Movement> getSolutionMoves(const Cube& cube) {
  std::vector<Movement> solution;
  for (auto it = cube.movement_set.rbegin(); it != cube.movement_set.rend(); ++it) {
    solution.push_back(it->reverse());
  }
  return solution;
}

void Solver::bfs(std::vector<Movement> valid_moves, Cube::HashType hash_type) {
  std::queue<Cube> cubes;
  cubes.push(Cube());

  while (!cubes.empty()) {
    Cube cube = cubes.front();
    cubes.pop();
    for (Movement move : valid_moves) {
      if (!cube.movement_set.empty()) {
        Movement last_move = cube.movement_set.back();
        if (move == last_move) continue;
      }

      Cube current(cube);
      current.rotate(move);
      int64_t id = current.get_id(hash_type);
      if (database.find(id) != database.end()) continue;

      auto solution_moves = getSolutionMoves(current);
      auto encoded_moves = encodeMoves(solution_moves);
      Data data{};
      data.length = static_cast<uint8_t>(encoded_moves.size());
      std::memcpy(data.moves, encoded_moves.data(), encoded_moves.size());
      database[id] = data;
      cubes.push(current);
    }
  }

  std::cout << "Final database size: " << database.size() << std::endl;
};
