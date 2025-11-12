#pragma once

namespace RubikConfig {
// Janela
constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;
constexpr const char* WINDOW_TITLE = "Cubo Rubik 42";

// Cubo
constexpr float CUBE_SIZE = 1.0f;
constexpr float CUBE_ROTATION_SPEED = 2.0f;

// Câmera
constexpr float CAMERA_DISTANCE = 8.0f;
constexpr float CAMERA_ROTATION_SPEED = 5.0f;
constexpr float CAMERA_MIN_ELEVATION = -95.0f;
constexpr float CAMERA_MAX_ELEVATION = 95.0f;

// Projeção
constexpr float FOV = 45.0f;
constexpr float NEAR_PLANE = 0.1f;
constexpr float FAR_PLANE = 100.0f;

// Renderização
constexpr int FPS = 60;
constexpr int FRAME_TIME = 1000 / FPS;

// Desenho
constexpr float FACE_OFFSET = 0.01f;
constexpr float FACE_SCALE = 0.85f;

// Coordenadas
constexpr float AXIS_LENGTH = 2.0f;
constexpr float ARROW_SIZE = 0.2f;
}
