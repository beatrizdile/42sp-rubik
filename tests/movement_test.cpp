#define CATCH_CONFIG_MAIN
#include "Movement.hpp"
#include "catch_amalgamated.hpp"

TEST_CASE("Movement parser - Movimentos básicos", "[movement][parser]") {
  SECTION("Front move") {
    Movement move("F");
    REQUIRE(move.move == MOVE_FRONT);
    REQUIRE(move.type == CLOCK_WISE);
  }

  SECTION("Back move") {
    Movement move("B");
    REQUIRE(move.move == MOVE_BACK);
    REQUIRE(move.type == CLOCK_WISE);
  }

  SECTION("Up move") {
    Movement move("U");
    REQUIRE(move.move == MOVE_UP);
    REQUIRE(move.type == CLOCK_WISE);
  }

  SECTION("Down move") {
    Movement move("D");
    REQUIRE(move.move == MOVE_DOWN);
    REQUIRE(move.type == CLOCK_WISE);
  }

  SECTION("Left move") {
    Movement move("L");
    REQUIRE(move.move == MOVE_LEFT);
    REQUIRE(move.type == CLOCK_WISE);
  }

  SECTION("Right move") {
    Movement move("R");
    REQUIRE(move.move == MOVE_RIGHT);
    REQUIRE(move.type == CLOCK_WISE);
  }
}

TEST_CASE("Movement parser - Movimentos anti-horário", "[movement][parser]") {
  SECTION("Front counter-clockwise") {
    Movement move("F'");
    REQUIRE(move.move == MOVE_FRONT);
    REQUIRE(move.type == ANTI_CLOCK_WISE);
  }

  SECTION("Back counter-clockwise") {
    Movement move("B'");
    REQUIRE(move.move == MOVE_BACK);
    REQUIRE(move.type == ANTI_CLOCK_WISE);
  }

  SECTION("Up counter-clockwise") {
    Movement move("U'");
    REQUIRE(move.move == MOVE_UP);
    REQUIRE(move.type == ANTI_CLOCK_WISE);
  }

  SECTION("Down counter-clockwise") {
    Movement move("D'");
    REQUIRE(move.move == MOVE_DOWN);
    REQUIRE(move.type == ANTI_CLOCK_WISE);
  }

  SECTION("Left counter-clockwise") {
    Movement move("L'");
    REQUIRE(move.move == MOVE_LEFT);
    REQUIRE(move.type == ANTI_CLOCK_WISE);
  }

  SECTION("Right counter-clockwise") {
    Movement move("R'");
    REQUIRE(move.move == MOVE_RIGHT);
    REQUIRE(move.type == ANTI_CLOCK_WISE);
  }
}

TEST_CASE("Movement parser - Movimentos duplos", "[movement][parser]") {
  SECTION("Front double") {
    Movement move("F2");
    REQUIRE(move.move == MOVE_FRONT);
    REQUIRE(move.type == TWICE);
  }

  SECTION("Back double") {
    Movement move("B2");
    REQUIRE(move.move == MOVE_BACK);
    REQUIRE(move.type == TWICE);
  }

  SECTION("Up double") {
    Movement move("U2");
    REQUIRE(move.move == MOVE_UP);
    REQUIRE(move.type == TWICE);
  }

  SECTION("Down double") {
    Movement move("D2");
    REQUIRE(move.move == MOVE_DOWN);
    REQUIRE(move.type == TWICE);
  }

  SECTION("Left double") {
    Movement move("L2");
    REQUIRE(move.move == MOVE_LEFT);
    REQUIRE(move.type == TWICE);
  }

  SECTION("Right double") {
    Movement move("R2");
    REQUIRE(move.move == MOVE_RIGHT);
    REQUIRE(move.type == TWICE);
  }
}

TEST_CASE("Movement parser - Construtor padrão", "[movement][constructor]") {
  Movement move;
  REQUIRE(move.move == MOVE_FRONT);
  REQUIRE(move.type == CLOCK_WISE);
}

TEST_CASE("Movement parser - Construtor parametrizado", "[movement][constructor]") {
  Movement move(MOVE_LEFT, TWICE);
  REQUIRE(move.move == MOVE_LEFT);
  REQUIRE(move.type == TWICE);
}

TEST_CASE("Movement parser - Construtor de cópia", "[movement][constructor]") {
  Movement original(MOVE_RIGHT, ANTI_CLOCK_WISE);
  Movement copy(original);

  REQUIRE(copy.move == MOVE_RIGHT);
  REQUIRE(copy.type == ANTI_CLOCK_WISE);
}

TEST_CASE("Movement parser - Operador de atribuição", "[movement][operator]") {
  Movement move1(MOVE_UP, TWICE);
  Movement move2;

  move2 = move1;

  REQUIRE(move2.move == MOVE_UP);
  REQUIRE(move2.type == TWICE);
}

TEST_CASE("Movement parser - Casos de erro", "[movement][parser][error]") {
  SECTION("String vazia") {
    REQUIRE_THROWS_AS(Movement(""), std::invalid_argument);
  }

  SECTION("String muito longa") {
    REQUIRE_THROWS_AS(Movement("F2'"), std::invalid_argument);
    REQUIRE_THROWS_AS(Movement("ABC"), std::invalid_argument);
  }

  SECTION("Movimento inválido") {
    REQUIRE_THROWS_AS(Movement("X"), std::invalid_argument);
    REQUIRE_THROWS_AS(Movement("Z"), std::invalid_argument);
    REQUIRE_THROWS_AS(Movement("1"), std::invalid_argument);
  }

  SECTION("Modificador inválido") {
    REQUIRE_THROWS_AS(Movement("F3"), std::invalid_argument);
    REQUIRE_THROWS_AS(Movement("F#"), std::invalid_argument);
    REQUIRE_THROWS_AS(Movement("Fx"), std::invalid_argument);
  }
}

TEST_CASE("Movement parser - Operador de saída", "[movement][output]") {
  SECTION("Movimentos horários") {
    std::ostringstream oss;
    oss << Movement("F");
    REQUIRE(oss.str() == "F");

    oss.str("");
    oss << Movement("R");
    REQUIRE(oss.str() == "R");
  }

  SECTION("Movimentos anti-horários") {
    std::ostringstream oss;
    oss << Movement("F'");
    REQUIRE(oss.str() == "F'");

    oss.str("");
    oss << Movement("L'");
    REQUIRE(oss.str() == "L'");
  }

  SECTION("Movimentos duplos") {
    std::ostringstream oss;
    oss << Movement("U2");
    REQUIRE(oss.str() == "U2");

    oss.str("");
    oss << Movement("D2");
    REQUIRE(oss.str() == "D2");
  }
}
