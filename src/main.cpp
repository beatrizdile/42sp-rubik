#include <GL/freeglut.h>
#include <GL/glut.h>

#include <cmath>

#include "Config.hpp"
#include "Corner.hpp"
#include "Cube.hpp"
#include "Draw.hpp"
#include "Edge.hpp"

CameraState cameraState;
Cube cube;

void updateCamera() noexcept {
  const float azimuthRad = cameraState.cameraAzimuth * M_PI / 180.0f;
  const float elevationRad = cameraState.cameraElevation * M_PI / 180.0f;
  const float camX = RubikConfig::CAMERA_DISTANCE * cos(elevationRad) * cos(azimuthRad);
  const float camY = RubikConfig::CAMERA_DISTANCE * sin(elevationRad);
  const float camZ = RubikConfig::CAMERA_DISTANCE * cos(elevationRad) * sin(azimuthRad);

  gluLookAt(camX, camY, camZ,
            0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f);
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  updateCamera();
  updateLightPosition();

  glPushMatrix();
  for (size_t i = 0; i < cube.corners.size(); i++) {
    drawCorner(static_cast<Corner>(i), cube.corners[i], RubikConfig::CUBE_SIZE);
  }

  for (size_t i = 0; i < cube.edges.size(); i++) {
    drawEdge(static_cast<Edge>(i), cube.edges[i], RubikConfig::CUBE_SIZE);
  }

  for (int i = 0; i < 6; i++) {
    drawCenter(static_cast<Face>(i), RubikConfig::CUBE_SIZE);
  }

  drawCoordinateAxes();
  glPopMatrix();

  drawHelpText(RubikConfig::WINDOW_WIDTH, RubikConfig::WINDOW_HEIGHT);
  glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
  (void)x;
  (void)y;

  switch (key) {
    case 27:  // ESC
      glutLeaveMainLoop();
      break;
    case 'f':
    case 'F':
      cube.rotate(Movement(Move::MOVE_FRONT));
      break;
    case 'b':
    case 'B':
      cube.rotate(Movement(Move::MOVE_BACK));
      break;
    case 'r':
    case 'R':
      cube.rotate(Movement(Move::MOVE_RIGHT));
      break;
    case 'l':
    case 'L':
      cube.rotate(Movement(Move::MOVE_LEFT));
      break;
    case 'u':
    case 'U':
      cube.rotate(Movement(Move::MOVE_UP));
      break;
    case 'd':
    case 'D':
      cube.rotate(Movement(Move::MOVE_DOWN));
      break;
    default:
      return;
  }

  glutPostRedisplay();
}

void specialKeys(int key, int x, int y) {
  (void)x;
  (void)y;

  switch (key) {
    case GLUT_KEY_LEFT:
      cameraState.cameraAzimuth -= RubikConfig::CAMERA_ROTATION_SPEED;
      break;
    case GLUT_KEY_RIGHT:
      cameraState.cameraAzimuth += RubikConfig::CAMERA_ROTATION_SPEED;
      break;
    case GLUT_KEY_UP:
      cameraState.cameraElevation += RubikConfig::CAMERA_ROTATION_SPEED;
      cameraState.cameraElevation = std::min(cameraState.cameraElevation,
                                             RubikConfig::CAMERA_MAX_ELEVATION);
      break;
    case GLUT_KEY_DOWN:
      cameraState.cameraElevation -= RubikConfig::CAMERA_ROTATION_SPEED;
      cameraState.cameraElevation = std::max(cameraState.cameraElevation,
                                             RubikConfig::CAMERA_MIN_ELEVATION);
      break;
    default:
      return;
  }
  glutPostRedisplay();
}

void timer(int value) {
  (void)value;

  glutTimerFunc(RubikConfig::FRAME_TIME, timer, 0);
}

int main(int argc, char** argv) {
  initGL(argc, argv);

  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(specialKeys);
  glutTimerFunc(RubikConfig::FRAME_TIME, timer, 0);

  glutMainLoop();
  return 0;
}
