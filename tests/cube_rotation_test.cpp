#include "Cube.hpp"
#include "Movement.hpp"
#include "catch_amalgamated.hpp"

TEST_CASE("Cube rotation - Estado inicial", "[cube][rotation]") {
  Cube cube;

  SECTION("Cubo deve estar resolvido inicialmente") {
    REQUIRE(cube.is_solved());
  }

  SECTION("Corners devem estar nas posições corretas") {
    REQUIRE(cube.corners[URF].corner == URF);
    REQUIRE(cube.corners[UFL].corner == UFL);
    REQUIRE(cube.corners[ULB].corner == ULB);
    REQUIRE(cube.corners[UBR].corner == UBR);
    REQUIRE(cube.corners[DFR].corner == DFR);
    REQUIRE(cube.corners[DLF].corner == DLF);
    REQUIRE(cube.corners[DBL].corner == DBL);
    REQUIRE(cube.corners[DRB].corner == DRB);
  }

  SECTION("Edges devem estar nas posições corretas") {
    REQUIRE(cube.edges[UR].edge == UR);
    REQUIRE(cube.edges[UF].edge == UF);
    REQUIRE(cube.edges[UL].edge == UL);
    REQUIRE(cube.edges[UB].edge == UB);
    REQUIRE(cube.edges[DR].edge == DR);
    REQUIRE(cube.edges[DF].edge == DF);
    REQUIRE(cube.edges[DL].edge == DL);
    REQUIRE(cube.edges[DB].edge == DB);
    REQUIRE(cube.edges[FR].edge == FR);
    REQUIRE(cube.edges[FL].edge == FL);
    REQUIRE(cube.edges[BL].edge == BL);
    REQUIRE(cube.edges[BR].edge == BR);
  }
}

TEST_CASE("Cube rotation - Rotação F (Front)", "[cube][rotation][front]") {
  Cube cube;

  SECTION("Uma rotação F") {
    Movement move_f("F");
    cube.rotate(move_f);

    // Verificar corners afetados pela rotação F
    REQUIRE(cube.corners[URF].corner == UFL);
    REQUIRE(cube.corners[UFL].corner == DLF);
    REQUIRE(cube.corners[DLF].corner == DFR);
    REQUIRE(cube.corners[DFR].corner == URF);

    // Verificar edges afetados pela rotação F
    REQUIRE(cube.edges[FR].edge == UF);
    REQUIRE(cube.edges[UF].edge == FL);
    REQUIRE(cube.edges[FL].edge == DF);
    REQUIRE(cube.edges[DF].edge == FR);

    // Cubo não deve estar resolvido após uma rotação
    REQUIRE_FALSE(cube.is_solved());
  }

  SECTION("Quatro rotações F devem retornar ao estado inicial") {
    Cube original_cube = cube;

    for (int i = 0; i < 4; i++) {
      Movement move_f("F");
      cube.rotate(move_f);
    }

    REQUIRE(cube == original_cube);
    REQUIRE(cube.is_solved());
  }
}

TEST_CASE("Cube rotation - Rotação R (Right)", "[cube][rotation][right]") {
  Cube cube;

  SECTION("Uma rotação R") {
    Movement move_r("R");
    cube.rotate(move_r);

    // Verificar corners afetados pela rotação R
    REQUIRE(cube.corners[UBR].corner == URF);
    REQUIRE(cube.corners[URF].corner == DFR);
    REQUIRE(cube.corners[DFR].corner == DRB);
    REQUIRE(cube.corners[DRB].corner == UBR);

    // Verificar edges afetados pela rotação R
    REQUIRE(cube.edges[BR].edge == UR);
    REQUIRE(cube.edges[UR].edge == FR);
    REQUIRE(cube.edges[FR].edge == DR);
    REQUIRE(cube.edges[DR].edge == BR);

    REQUIRE_FALSE(cube.is_solved());
  }

  SECTION("Quatro rotações R devem retornar ao estado inicial") {
    Cube original_cube = cube;

    for (int i = 0; i < 4; i++) {
      Movement move_r("R");
      cube.rotate(move_r);
    }

    REQUIRE(cube == original_cube);
    REQUIRE(cube.is_solved());
  }
}

TEST_CASE("Cube rotation - Rotação U (Up)", "[cube][rotation][up]") {
  Cube cube;

  SECTION("Uma rotação U") {
    Movement move_u("U");
    cube.rotate(move_u);

    // Verificar corners afetados pela rotação U
    REQUIRE(cube.corners[URF].corner == UFL);
    REQUIRE(cube.corners[UFL].corner == ULB);
    REQUIRE(cube.corners[ULB].corner == UBR);
    REQUIRE(cube.corners[UBR].corner == URF);

    // Verificar edges afetados pela rotação U
    REQUIRE(cube.edges[UR].edge == UF);
    REQUIRE(cube.edges[UF].edge == UL);
    REQUIRE(cube.edges[UL].edge == UB);
    REQUIRE(cube.edges[UB].edge == UR);

    REQUIRE_FALSE(cube.is_solved());
  }

  SECTION("Quatro rotações U devem retornar ao estado inicial") {
    Cube original_cube = cube;

    for (int i = 0; i < 4; i++) {
      Movement move_u("U");
      cube.rotate(move_u);
    }

    REQUIRE(cube == original_cube);
    REQUIRE(cube.is_solved());
  }
}

TEST_CASE("Cube rotation - Rotação D (Down)", "[cube][rotation][down]") {
  Cube cube;

  SECTION("Uma rotação D") {
    Movement move_d("D");
    cube.rotate(move_d);

    // Verificar corners afetados pela rotação D
    REQUIRE(cube.corners[DRB].corner == DBL);
    REQUIRE(cube.corners[DBL].corner == DLF);
    REQUIRE(cube.corners[DLF].corner == DFR);
    REQUIRE(cube.corners[DFR].corner == DRB);

    // Verificar edges afetados pela rotação D
    REQUIRE(cube.edges[DB].edge == DL);
    REQUIRE(cube.edges[DL].edge == DF);
    REQUIRE(cube.edges[DF].edge == DR);
    REQUIRE(cube.edges[DR].edge == DB);

    REQUIRE_FALSE(cube.is_solved());
  }

  SECTION("Quatro rotações D devem retornar ao estado inicial") {
    Cube original_cube = cube;

    for (int i = 0; i < 4; i++) {
      Movement move_d("D");
      cube.rotate(move_d);
    }

    REQUIRE(cube == original_cube);
    REQUIRE(cube.is_solved());
  }
}

TEST_CASE("Cube rotation - Rotação L (Left)", "[cube][rotation][left]") {
  Cube cube;

  SECTION("Uma rotação L") {
    Movement move_l("L");
    cube.rotate(move_l);

    // Verificar corners afetados pela rotação L
    REQUIRE(cube.corners[UFL].corner == ULB);
    REQUIRE(cube.corners[ULB].corner == DBL);
    REQUIRE(cube.corners[DBL].corner == DLF);
    REQUIRE(cube.corners[DLF].corner == UFL);

    // Verificar edges afetados pela rotação L
    REQUIRE(cube.edges[FL].edge == UL);
    REQUIRE(cube.edges[UL].edge == BL);
    REQUIRE(cube.edges[BL].edge == DL);
    REQUIRE(cube.edges[DL].edge == FL);

    REQUIRE_FALSE(cube.is_solved());
  }

  SECTION("Quatro rotações L devem retornar ao estado inicial") {
    Cube original_cube = cube;

    for (int i = 0; i < 4; i++) {
      Movement move_l("L");
      cube.rotate(move_l);
    }

    REQUIRE(cube == original_cube);
    REQUIRE(cube.is_solved());
  }
}

TEST_CASE("Cube rotation - Rotação B (Back)", "[cube][rotation][back]") {
  Cube cube;

  SECTION("Uma rotação B") {
    Movement move_b("B");
    cube.rotate(move_b);

    // Verificar corners afetados pela rotação B
    REQUIRE(cube.corners[DRB].corner == DBL);
    REQUIRE(cube.corners[DBL].corner == ULB);
    REQUIRE(cube.corners[ULB].corner == UBR);
    REQUIRE(cube.corners[UBR].corner == DRB);

    // Verificar edges afetados pela rotação B
    REQUIRE(cube.edges[BR].edge == DB);
    REQUIRE(cube.edges[DB].edge == BL);
    REQUIRE(cube.edges[BL].edge == UB);
    REQUIRE(cube.edges[UB].edge == BR);

    REQUIRE_FALSE(cube.is_solved());
  }

  SECTION("Quatro rotações B devem retornar ao estado inicial") {
    Cube original_cube = cube;

    for (int i = 0; i < 4; i++) {
      Movement move_b("B");
      cube.rotate(move_b);
    }

    REQUIRE(cube == original_cube);
    REQUIRE(cube.is_solved());
  }
}

TEST_CASE("Cube rotation - Rotações duplas", "[cube][rotation][double]") {
  Cube cube;

  SECTION("F2 equivale a duas rotações F") {
    Cube cube1 = cube;
    Cube cube2 = cube;

    Movement move_f2("F2");
    cube1.rotate(move_f2);

    Movement move_f("F");
    cube2.rotate(move_f);
    cube2.rotate(move_f);

    REQUIRE(cube1 == cube2);
  }

  SECTION("R2 equivale a duas rotações R") {
    Cube cube1 = cube;
    Cube cube2 = cube;

    Movement move_r2("R2");
    cube1.rotate(move_r2);

    Movement move_r("R");
    cube2.rotate(move_r);
    cube2.rotate(move_r);

    REQUIRE(cube1 == cube2);
  }
}

TEST_CASE("Cube rotation - Rotações anti-horárias", "[cube][rotation][counter]") {
  Cube cube;

  SECTION("F' + F deve retornar ao estado inicial") {
    Cube original_cube = cube;

    Movement move_f_prime("F'");
    Movement move_f("F");

    cube.rotate(move_f_prime);
    cube.rotate(move_f);

    REQUIRE(cube == original_cube);
    REQUIRE(cube.is_solved());
  }

  SECTION("R' equivale a três rotações R") {
    Cube cube1 = cube;
    Cube cube2 = cube;

    Movement move_r_prime("R'");
    cube1.rotate(move_r_prime);

    Movement move_r("R");
    for (int i = 0; i < 3; i++) {
      cube2.rotate(move_r);
    }

    REQUIRE(cube1 == cube2);
  }
}

TEST_CASE("Cube rotation - Sequências complexas", "[cube][rotation][sequence]") {
  Cube cube;

  SECTION("Algoritmo R U R' U' deve ser reversível") {
    Cube original_cube = cube;

    // Aplicar algoritmo 6 vezes (período do algoritmo)
    for (int cycle = 0; cycle < 6; cycle++) {
      Movement r("R");
      Movement u("U");
      Movement r_prime("R'");
      Movement u_prime("U'");

      cube.rotate(r);
      cube.rotate(u);
      cube.rotate(r_prime);
      cube.rotate(u_prime);
    }

    REQUIRE(cube == original_cube);
    REQUIRE(cube.is_solved());
  }

  SECTION("Scramble e solução") {
    Cube original_cube = cube;
    std::vector<std::string> scramble = {"R", "U", "R'", "F", "R", "F'"};
    std::vector<std::string> solution = {"F", "R'", "F'", "R", "U'", "R'"};

    // Aplicar scramble
    for (const auto& move_str : scramble) {
      Movement move(move_str);
      cube.rotate(move);
    }

    REQUIRE_FALSE(cube.is_solved());

    // Aplicar solução
    for (const auto& move_str : solution) {
      Movement move(move_str);
      cube.rotate(move);
    }

    REQUIRE(cube == original_cube);
    REQUIRE(cube.is_solved());
  }
}

TEST_CASE("Cube rotation - Teste de igualdade", "[cube][equality]") {
  Cube cube1;
  Cube cube2;

  SECTION("Cubos idênticos devem ser iguais") {
    REQUIRE(cube1 == cube2);
  }

  SECTION("Cubos diferentes devem ser diferentes") {
    Movement move("R");
    cube2.rotate(move);

    REQUIRE_FALSE(cube1 == cube2);
  }

  SECTION("Mesmo scramble produz cubos iguais") {
    std::vector<std::string> moves = {"R", "U", "F'", "D2", "L", "B'"};

    for (const auto& move_str : moves) {
      Movement move(move_str);
      cube1.rotate(move);
      cube2.rotate(move);
    }

    REQUIRE(cube1 == cube2);
  }
}