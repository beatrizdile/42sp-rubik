#pragma once

#include <GL/freeglut.h>
#include <GL/glut.h>

#include <map>

#include "Corner.hpp"
#include "Edge.hpp"
#include "Face.hpp"

namespace DrawConfig {
// Renderização
constexpr float FACE_OFFSET = 0.01f;
constexpr float FACE_SCALE = 0.8f;

// Iluminação
constexpr GLfloat LIGHT_AMBIENT[] = {0.5f, 0.5f, 0.5f, 1.0f};
constexpr GLfloat LIGHT_DIFFUSE[] = {0.8f, 0.8f, 0.8f, 1.0f};
constexpr GLfloat LIGHT1_AMBIENT[] = {0.5f, 0.5f, 0.5f, 1.0f};
constexpr GLfloat LIGHT1_DIFFUSE[] = {0.8f, 0.8f, 0.8f, 1.0f};
constexpr GLfloat LIGHT0_POSITION[] = {2.0f, 2.0f, 2.0f, 1.0f};
constexpr GLfloat LIGHT1_POSITION[] = {2.0f, 2.0f, -2.0f, 1.0f};
}  // namespace DrawConfig

struct CameraState {
  float cameraAzimuth = 45.0f;
  float cameraElevation = 30.0f;
};

void drawCube(std::map<Face, float[3]> face_colors, float cube_size);
void drawCorner(Corner position, CornerData corner, float cube_size);
void drawEdge(Edge position, EdgeData edge, float cube_size);
void drawCenter(Face face, float cube_size);
void drawCoordinateAxes();
void drawHelpText(int window_width, int window_height);
void setupLighting();
void updateLightPosition();
void reshape(int w, int h);
void initGL(int argc, char** argv);
