#include <GL/freeglut.h>
#include <GL/glut.h>

#include <cmath>

#include "Config.hpp"
#include "Corner.hpp"
#include "Cube.hpp"
#include "Draw.hpp"
#include "Edge.hpp"

CameraState cameraState;
AnimationState animationState;
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

  Move currentMove = animationState.currentMove;
  float currentAngle = animationState.currentAngle;
  glPushMatrix();
  for (size_t i = 0; i < cube.corners.size(); ++i) {
    drawCorner(static_cast<Corner>(i), cube.corners[i], RubikConfig::CUBE_SIZE, currentMove, currentAngle);
  }
  for (size_t i = 0; i < cube.edges.size(); ++i) {
    drawEdge(static_cast<Edge>(i), cube.edges[i], RubikConfig::CUBE_SIZE, currentMove, currentAngle);
  }
  for (int i = 0; i < 6; ++i) {
    drawCenter(static_cast<Face>(i), RubikConfig::CUBE_SIZE, currentMove, currentAngle);
  }
  glPopMatrix();

  drawHelpText(RubikConfig::WINDOW_WIDTH, RubikConfig::WINDOW_HEIGHT);
  glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
  (void)x;
  (void)y;

  if (animationState.isAnimating) {
    return;
  }

  switch (key) {
    case 'f':
      animationState.startAnimation(Move::MOVE_FRONT, MoveType::CLOCK_WISE);
      break;
    case 'b':
      animationState.startAnimation(Move::MOVE_BACK, MoveType::CLOCK_WISE);
      break;
    case 'r':
      animationState.startAnimation(Move::MOVE_RIGHT, MoveType::CLOCK_WISE);
      break;
    case 'l':
      animationState.startAnimation(Move::MOVE_LEFT, MoveType::CLOCK_WISE);
      break;
    case 'u':
      animationState.startAnimation(Move::MOVE_UP, MoveType::CLOCK_WISE);
      break;
    case 'd':
      animationState.startAnimation(Move::MOVE_DOWN, MoveType::CLOCK_WISE);
      break;

    case 'F':
      animationState.startAnimation(Move::MOVE_FRONT, MoveType::ANTI_CLOCK_WISE);
      break;
    case 'B':
      animationState.startAnimation(Move::MOVE_BACK, MoveType::ANTI_CLOCK_WISE);
      break;
    case 'R':
      animationState.startAnimation(Move::MOVE_RIGHT, MoveType::ANTI_CLOCK_WISE);
      break;
    case 'L':
      animationState.startAnimation(Move::MOVE_LEFT, MoveType::ANTI_CLOCK_WISE);
      break;
    case 'U':
      animationState.startAnimation(Move::MOVE_UP, MoveType::ANTI_CLOCK_WISE);
      break;
    case 'D':
      animationState.startAnimation(Move::MOVE_DOWN, MoveType::ANTI_CLOCK_WISE);
      break;

    case 27:  // ESC
      glutLeaveMainLoop();
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

  if (animationState.isAnimating) {
    animationState.updateAnimation();
    if (!animationState.isAnimating) {
      cube.rotate(Movement(animationState.currentMove, animationState.currentType));
    }
    glutPostRedisplay();
  }

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
