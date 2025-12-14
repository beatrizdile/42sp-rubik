#pragma once

#include <GL/freeglut.h>

#include "Movement.hpp"

namespace RubikConfig {
// Window
constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;
constexpr const char* WINDOW_TITLE = "Cubo Rubik 42";

// Cube
constexpr float CUBE_SIZE = 1.0f;
constexpr float CUBE_ROTATION_SPEED = 2.0f;

// Camera
constexpr float CAMERA_DISTANCE = 8.0f;
constexpr float CAMERA_ROTATION_SPEED = 5.0f;
constexpr float CAMERA_MIN_ELEVATION = -85.0f;
constexpr float CAMERA_MAX_ELEVATION = 85.0f;

// Projection
constexpr float FOV = 45.0f;
constexpr float NEAR_PLANE = 0.1f;
constexpr float FAR_PLANE = 100.0f;

// Frame Rate
constexpr int FPS = 60;
constexpr int FRAME_TIME = 1000 / FPS;

// Animation
constexpr float ANIMATION_SPEED = 90.0f;
constexpr float ANIMATION_DURATION_MS = 350.0f;
constexpr int ANIMATION_STEPS = static_cast<int>(ANIMATION_DURATION_MS / FRAME_TIME);

// Auto Movement
constexpr int DELAY_BETWEEN_MOVEMENTS = 500;

// Drawing
constexpr float FACE_OFFSET = 0.01f;
constexpr float FACE_SCALE = 0.85f;
constexpr float ROUNDED_CORNER_RADIUS = 0.2f;

// Illumination
constexpr GLfloat LIGHT_AMBIENT[] = {0.5f, 0.5f, 0.5f, 1.0f};
constexpr GLfloat LIGHT_DIFFUSE[] = {0.8f, 0.8f, 0.8f, 1.0f};
constexpr GLfloat LIGHT1_AMBIENT[] = {0.5f, 0.5f, 0.5f, 1.0f};
constexpr GLfloat LIGHT1_DIFFUSE[] = {0.8f, 0.8f, 0.8f, 1.0f};
constexpr GLfloat LIGHT0_POSITION[] = {2.0f, 2.0f, 2.0f, 1.0f};
constexpr GLfloat LIGHT1_POSITION[] = {2.0f, 2.0f, -2.0f, 1.0f};
}  // namespace RubikConfig

struct CameraState {
  float cameraAzimuth = 45.0f;
  float cameraElevation = 30.0f;
};

struct AnimationState {
  bool isAnimating = false;
  Move currentMove = Move::MOVE_FRONT;
  MoveType currentType = MoveType::CLOCK_WISE;
  float currentAngle = 0.0f;
  int currentStep = 0;
  int totalSteps = 0;

  void startAnimation(Move move, MoveType type) {
    isAnimating = true;
    currentMove = move;
    currentType = type;
    currentAngle = 0.0f;
    currentStep = 0;
    totalSteps = RubikConfig::ANIMATION_STEPS;
  }

  void updateAnimation() {
    if (!isAnimating) return;

    currentStep++;
    float progress = static_cast<float>(currentStep) / static_cast<float>(totalSteps);

    float targetAngle = getMoveAngle(currentType);
    currentAngle = targetAngle * progress;

    if (currentStep >= totalSteps) {
      finishAnimation();
    }
  }

  void finishAnimation() {
    isAnimating = false;
    currentAngle = 0.0f;
    currentStep = 0;
  }
};
