#pragma once

#include <GL/freeglut.h>
#include <GL/glut.h>

#include <chrono>
#include <cmath>
#include <iostream>
#include <string>

#include "Config.hpp"
#include "Corner.hpp"
#include "Cube.hpp"
#include "Draw.hpp"
#include "Edge.hpp"

extern CameraState cameraState;
extern AnimationState animationState;
extern Cube cube;
extern std::vector<Movement> movements;
extern std::vector<Movement> solution;

void specialKeys(int key, int x, int y);
void timer(int value);
void keyboard(unsigned char key, int x, int y);
void display();
void updateCamera() noexcept;
