#pragma once

#include <iostream>

constexpr float WHITE[3] = {1.0f, 1.0f, 1.0f};
constexpr float YELLOW[3] = {1.0f, 1.0f, 0.0f};
constexpr float RED[3] = {1.0f, 0.0f, 0.0f};
constexpr float ORANGE[3] = {1.0f, 0.5f, 0.0f};
constexpr float GREEN[3] = {0.0f, 1.0f, 0.0f};
constexpr float BLUE[3] = {0.0f, 0.0f, 1.0f};

constexpr float corner_base_colors[8][3][3] = {
    // URF: Up(YELLOW), Right(ORANGE), Front(GREEN)
    {{YELLOW[0], YELLOW[1], YELLOW[2]}, {ORANGE[0], ORANGE[1], ORANGE[2]}, {GREEN[0], GREEN[1], GREEN[2]}},
    // UFL: Up(YELLOW), Front(GREEN), Left(RED)
    {{YELLOW[0], YELLOW[1], YELLOW[2]}, {GREEN[0], GREEN[1], GREEN[2]}, {RED[0], RED[1], RED[2]}},
    // ULB: Up(YELLOW), Left(RED), Back(BLUE)
    {{YELLOW[0], YELLOW[1], YELLOW[2]}, {RED[0], RED[1], RED[2]}, {BLUE[0], BLUE[1], BLUE[2]}},
    // UBR: Up(YELLOW), Back(BLUE), Right(ORANGE)
    {{YELLOW[0], YELLOW[1], YELLOW[2]}, {BLUE[0], BLUE[1], BLUE[2]}, {ORANGE[0], ORANGE[1], ORANGE[2]}},
    // DFR: Down(WHITE), Front(GREEN), Right(ORANGE)
    {{WHITE[0], WHITE[1], WHITE[2]}, {GREEN[0], GREEN[1], GREEN[2]}, {ORANGE[0], ORANGE[1], ORANGE[2]}},
    // DLF: Down(WHITE), Left(RED), Front(GREEN)
    {{WHITE[0], WHITE[1], WHITE[2]}, {RED[0], RED[1], RED[2]}, {GREEN[0], GREEN[1], GREEN[2]}},
    // DBL: Down(WHITE), Back(BLUE), Left(RED)
    {{WHITE[0], WHITE[1], WHITE[2]}, {BLUE[0], BLUE[1], BLUE[2]}, {RED[0], RED[1], RED[2]}},
    // DRB: Down(WHITE), Right(ORANGE), Back(BLUE)
    {{WHITE[0], WHITE[1], WHITE[2]}, {ORANGE[0], ORANGE[1], ORANGE[2]}, {BLUE[0], BLUE[1], BLUE[2]}}};

constexpr float edge_base_colors[12][2][3] = {
    // UR = 0: Up(YELLOW), Right(ORANGE)
    {{YELLOW[0], YELLOW[1], YELLOW[2]}, {ORANGE[0], ORANGE[1], ORANGE[2]}},
    // UF = 1: Up(YELLOW), Front(GREEN)
    {{YELLOW[0], YELLOW[1], YELLOW[2]}, {GREEN[0], GREEN[1], GREEN[2]}},
    // UL = 2: Up(YELLOW), Left(RED)
    {{YELLOW[0], YELLOW[1], YELLOW[2]}, {RED[0], RED[1], RED[2]}},
    // UB = 3: Up(YELLOW), Back(BLUE)
    {{YELLOW[0], YELLOW[1], YELLOW[2]}, {BLUE[0], BLUE[1], BLUE[2]}},
    // DR = 4: Down(WHITE), Right(ORANGE)
    {{WHITE[0], WHITE[1], WHITE[2]}, {ORANGE[0], ORANGE[1], ORANGE[2]}},
    // DF = 5: Down(WHITE), Front(GREEN)
    {{WHITE[0], WHITE[1], WHITE[2]}, {GREEN[0], GREEN[1], GREEN[2]}},
    // DL = 6: Down(WHITE), Left(RED)
    {{WHITE[0], WHITE[1], WHITE[2]}, {RED[0], RED[1], RED[2]}},
    // DB = 7: Down(WHITE), Back(BLUE)
    {{WHITE[0], WHITE[1], WHITE[2]}, {BLUE[0], BLUE[1], BLUE[2]}},
    // FR = 8: Front(GREEN), Right(ORANGE)
    {{GREEN[0], GREEN[1], GREEN[2]}, {ORANGE[0], ORANGE[1], ORANGE[2]}},
    // FL = 9: Front(GREEN), Left(RED)
    {{GREEN[0], GREEN[1], GREEN[2]}, {RED[0], RED[1], RED[2]}},
    // BL = 10: Back(BLUE), Left(RED)
    {{BLUE[0], BLUE[1], BLUE[2]}, {RED[0], RED[1], RED[2]}},
    // BR = 11: Back(BLUE), Right(ORANGE)
    {{BLUE[0], BLUE[1], BLUE[2]}, {ORANGE[0], ORANGE[1], ORANGE[2]}}};

enum Face {
  UP = 0,
  DOWN = 1,
  LEFT = 2,
  RIGHT = 3,
  FRONT = 4,
  BACK = 5,
};

std::ostream& operator<<(std::ostream& os, Face face);
void getFaceColor(Face face, float color[3]);
void getFacePositionCoordinates(Face face, float& x, float& y, float& z);
