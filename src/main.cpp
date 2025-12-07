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
#include "Solver.hpp"

CameraState cameraState;
AnimationState animationState;
Cube cube;
std::vector<Movement> movements;
std::vector<Movement> solution;

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
    if (key == 27) {
      glutLeaveMainLoop();
    }
    return;
  }

  switch (key) {
    case 's':
      if (!animationState.isAnimating && movements.empty() && solution.empty()) {
        srand(time(nullptr));
        cube.randomize(20);
      }
      break;

    // Movimentos manuais (minúsculas = horário)
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

    // Movimentos manuais (maiúsculas = anti-horário)
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

    // Movimentos duplos (números)
    case '1':  // F2
      animationState.startAnimation(Move::MOVE_FRONT, MoveType::TWICE);
      break;
    case '2':  // B2
      animationState.startAnimation(Move::MOVE_BACK, MoveType::TWICE);
      break;
    case '3':  // R2
      animationState.startAnimation(Move::MOVE_RIGHT, MoveType::TWICE);
      break;
    case '4':  // L2
      animationState.startAnimation(Move::MOVE_LEFT, MoveType::TWICE);
      break;
    case '5':  // U2
      animationState.startAnimation(Move::MOVE_UP, MoveType::TWICE);
      break;
    case '6':  // D2
      animationState.startAnimation(Move::MOVE_DOWN, MoveType::TWICE);
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
  } else {
    static auto lastMoveTime = std::chrono::steady_clock::now();
    auto currentTime = std::chrono::steady_clock::now();
    auto timeSinceLastMove = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastMoveTime).count();

    if (timeSinceLastMove >= RubikConfig::DELAY_BETWEEN_MOVEMENTS) {
      if (!movements.empty()) {
        Movement nextMove = movements.front();
        movements.erase(movements.begin());
        animationState.startAnimation(nextMove.move, nextMove.type);
        lastMoveTime = currentTime;
      } else if (!solution.empty()) {
        Movement nextMove = solution.front();
        solution.erase(solution.begin());
        animationState.startAnimation(nextMove.move, nextMove.type);
        lastMoveTime = currentTime;
      }
      glutPostRedisplay();
    }
  }

  glutTimerFunc(RubikConfig::FRAME_TIME, timer, 0);
}

int main(int argc, char** argv) {
  if (argc == 1) {
    std::vector<Movement> step_one_movements{
        Movement(MOVE_FRONT, CLOCK_WISE),
        Movement(MOVE_FRONT, TWICE),
        Movement(MOVE_FRONT, ANTI_CLOCK_WISE),
        Movement(MOVE_BACK, CLOCK_WISE),
        Movement(MOVE_BACK, TWICE),
        Movement(MOVE_BACK, ANTI_CLOCK_WISE),
        Movement(MOVE_UP, CLOCK_WISE),
        Movement(MOVE_UP, TWICE),
        Movement(MOVE_UP, ANTI_CLOCK_WISE),
        Movement(MOVE_DOWN, CLOCK_WISE),
        Movement(MOVE_DOWN, TWICE),
        Movement(MOVE_DOWN, ANTI_CLOCK_WISE),
        Movement(MOVE_LEFT, CLOCK_WISE),
        Movement(MOVE_LEFT, TWICE),
        Movement(MOVE_LEFT, ANTI_CLOCK_WISE),
        Movement(MOVE_RIGHT, CLOCK_WISE),
        Movement(MOVE_RIGHT, TWICE),
        Movement(MOVE_RIGHT, ANTI_CLOCK_WISE),
    };

    std::vector<Movement> step_two_movements{
        Movement(MOVE_FRONT, TWICE),
        Movement(MOVE_BACK, TWICE),
        Movement(MOVE_UP, CLOCK_WISE),
        Movement(MOVE_UP, TWICE),
        Movement(MOVE_UP, ANTI_CLOCK_WISE),
        Movement(MOVE_DOWN, CLOCK_WISE),
        Movement(MOVE_DOWN, TWICE),
        Movement(MOVE_DOWN, ANTI_CLOCK_WISE),
        Movement(MOVE_LEFT, CLOCK_WISE),
        Movement(MOVE_LEFT, TWICE),
        Movement(MOVE_LEFT, ANTI_CLOCK_WISE),
        Movement(MOVE_RIGHT, CLOCK_WISE),
        Movement(MOVE_RIGHT, TWICE),
        Movement(MOVE_RIGHT, ANTI_CLOCK_WISE),
    };

    std::vector<Movement> step_third_movements{
        Movement(MOVE_FRONT, TWICE),
        Movement(MOVE_BACK, TWICE),
        Movement(MOVE_UP, CLOCK_WISE),
        Movement(MOVE_UP, TWICE),
        Movement(MOVE_UP, ANTI_CLOCK_WISE),
        Movement(MOVE_DOWN, CLOCK_WISE),
        Movement(MOVE_DOWN, TWICE),
        Movement(MOVE_DOWN, ANTI_CLOCK_WISE),
        Movement(MOVE_LEFT, TWICE),
        Movement(MOVE_RIGHT, TWICE),
    };

    std::vector<Movement> step_fourth_movements{
        Movement(MOVE_FRONT, TWICE),
        Movement(MOVE_BACK, TWICE),
        Movement(MOVE_UP, TWICE),
        Movement(MOVE_DOWN, TWICE),
        Movement(MOVE_LEFT, TWICE),
        Movement(MOVE_RIGHT, TWICE),
    };

    Solver solver_first;
    solver_first.bfs(step_one_movements, Cube::FIRST_STEP);
    solver_first.save_to_file("step_one.bin");

    Solver solver_second;
    solver_second.bfs(step_two_movements, Cube::SECOND_STEP);
    solver_second.save_to_file("step_two.bin");

    Solver solver_third;
    solver_third.bfs(step_third_movements, Cube::THIRD_STEP);
    solver_third.save_to_file("step_third.bin");

    Solver solver_fourth;
    solver_fourth.bfs(step_fourth_movements, Cube::FOURTH_STEP);
    solver_fourth.save_to_file("step_fourth.bin");

    return EXIT_SUCCESS;
  }

  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " \"<movements>\"" << std::endl;
    return (EXIT_FAILURE);
  }

  std::stringstream ss(argv[1]);
  std::string word;
  Cube cube;
  while (ss >> word) {
    try {
      Movement movement(word);
      movements.push_back(movement);
      cube.rotate(movement);
    } catch (const std::exception& e) {
      std::cerr << e.what() << std::endl;
      return (EXIT_FAILURE);
    }
  }

  if (movements.empty()) {
    std::cerr << "No valid movements provided." << std::endl;
    return (EXIT_FAILURE);
  }

  std::cout << cube << std::endl;
  std::cout << "Calculating solution..." << std::endl;
  auto start = std::chrono::high_resolution_clock::now();

  if (!cube.is_solved()) {
    Solver solver_one("step_one.bin");
    solution = solver_one.get_solve(cube.get_id(Cube::FIRST_STEP));
    for (const auto& move : solution) {
      cube.rotate(move);
    }
  }

  if (!cube.is_solved()) {
    Solver solver_two("step_two.bin");
    auto step_two = solver_two.get_solve(cube.get_id(Cube::SECOND_STEP));
    for (const auto& move : step_two) {
      cube.rotate(move);
    }
    solution.insert(solution.end(), step_two.begin(), step_two.end());
  }

  if (!cube.is_solved()) {
    Solver solver_third("step_third.bin");
    auto step_three = solver_third.get_solve(cube.get_id(Cube::THIRD_STEP));
    for (const auto& move : step_three) {
      cube.rotate(move);
    }
    solution.insert(solution.end(), step_three.begin(), step_three.end());
  }

  if (!cube.is_solved()) {
    Solver solver_fourth("step_fourth.bin");
    auto step_four = solver_fourth.get_solve(cube.get_id(Cube::FOURTH_STEP));
    for (const auto& move : step_four) {
      cube.rotate(move);
    }
    solution.insert(solution.end(), step_four.begin(), step_four.end());
  }

  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
  for (const auto& move : solution) {
    std::cout << move << " ";
  }
  std::cout << std::endl;
  std::cout << "Time spent calculating solution: " << duration.count() << " ns" << std::endl;

  std::cout << cube << std::endl;
  return (EXIT_SUCCESS);

  initGL(argc, argv);
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(specialKeys);
  glutTimerFunc(RubikConfig::FRAME_TIME, timer, 0);

  glutMainLoop();
  return (EXIT_SUCCESS);
}
