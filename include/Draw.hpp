#pragma once

#include <GL/freeglut.h>
#include <GL/glut.h>

#include <map>

#include "Config.hpp"
#include "Corner.hpp"
#include "Edge.hpp"
#include "Face.hpp"

void drawCube(std::map<Face, float[3]> face_colors, float cube_size);
void drawCorner(Corner position, CornerData corner, float cube_size, Move animMove = MOVE_FRONT, float animAngle = 0.0f);
void drawEdge(Edge position, EdgeData edge, float cube_size, Move animMove = MOVE_FRONT, float animAngle = 0.0f);
void drawCenter(Face face, float cube_size, Move animMove = MOVE_FRONT, float animAngle = 0.0f);
void drawHelpText(int window_width, int window_height);
void setupLighting();
void updateLightPosition();
void reshape(int w, int h);
void initGL(int argc, char** argv);
void getRotationAxisAndCenter(Move move, float& axisX, float& axisY, float& axisZ);
