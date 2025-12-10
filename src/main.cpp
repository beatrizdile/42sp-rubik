#include <cstring>

#include "Solver.hpp"
#include "animation.hpp"

struct StepConfig {
  std::vector<Movement> movements;
  std::string filename;
  Cube::HashType hashType;
  std::string stepName;
};

void generateDatabase() {
  std::vector<StepConfig> steps = {
      {{
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
       },
       "./database/step_one.bin",
       Cube::FIRST_STEP,
       "G0→G1: Orient all edges"},
      {{
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
       },
       "./database/step_two.bin",
       Cube::SECOND_STEP,
       "G1→G2: Orient corners + position E-slice edges"},
      {{
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
       },
       "./database/step_third.bin",
       Cube::THIRD_STEP,
       "G2→G3: Solve E-slice + position corners"},
      {{
           Movement(MOVE_FRONT, TWICE),
           Movement(MOVE_BACK, TWICE),
           Movement(MOVE_UP, TWICE),
           Movement(MOVE_DOWN, TWICE),
           Movement(MOVE_LEFT, TWICE),
           Movement(MOVE_RIGHT, TWICE),
       },
       "./database/step_fourth.bin",
       Cube::FOURTH_STEP,
       "G3→G4: Solve completely"}};

  std::cout << "Generating Thistlethwaite database..." << std::endl;
  for (const auto& step : steps) {
    std::cout << "Computing " << step.stepName << "..." << std::endl;
    Solver solver;
    solver.bfs(step.movements, step.hashType);
    solver.save_to_file(step.filename);
    std::cout << "Saved to " << step.filename << std::endl;
  }
  std::cout << "Database generation complete!" << std::endl;
}

struct SolveStep {
  std::string filename;
  Cube::HashType hashType;
  std::string stepName;
};

void solveCube(Cube& cube, bool showSteps = false) {
  std::vector<SolveStep> steps = {
      {"./database/step_one.bin", Cube::FIRST_STEP, "G0→G1: Orient all edges"},
      {"./database/step_two.bin", Cube::SECOND_STEP, "G1→G2: Orient corners + position E-slice edges"},
      {"./database/step_third.bin", Cube::THIRD_STEP, "G2→G3: Solve E-slice + position corners"},
      {"./database/step_fourth.bin", Cube::FOURTH_STEP, "G3→G4: Solve completely"}};

  for (const auto& step : steps) {
    if (!cube.is_solved()) {
      if (showSteps) {
        std::cout << "\nStep: " << step.stepName << std::endl;
      }

      Solver solver(step.filename);
      auto stepSolution = solver.get_solve(cube.get_id(step.hashType));

      if (showSteps) {
        std::cout << "Moves in this step: ";
        for (const auto& move : stepSolution) {
          std::cout << move << " ";
        }
        std::cout << "(" << stepSolution.size() << " moves)" << std::endl;
      }

      for (const auto& move : stepSolution) {
        cube.rotate(move);
      }

      if (showSteps) {
        std::cout << "Cube state after this step:" << std::endl;
        std::cout << cube << std::endl;
      }
      solution.insert(solution.end(), stepSolution.begin(), stepSolution.end());
    }
  }
}

void printUsage(const char* programName) {
  std::cout << "Usage: " << programName << " [options] [\"<movements>\"]" << std::endl;
  std::cout << "Options:" << std::endl;
  std::cout << "  -d              Display graphical interface" << std::endl;
  std::cout << "  -r              Use a random scrambled cube" << std::endl;
  std::cout << "  -c              Calculate and save database files" << std::endl;
  std::cout << "  -g              Show step-by-step group solving process" << std::endl;
  std::cout << "  -h, --help      Show this help message" << std::endl;
  std::cout << std::endl;
  std::cout << "Examples:" << std::endl;
  std::cout << "  " << programName << " -c                   # Generate database" << std::endl;
  std::cout << "  " << programName << " \"F R U R'\"           # Solve specific moves" << std::endl;
  std::cout << "  " << programName << " -r -g                # Random cube with step details" << std::endl;
  std::cout << "  " << programName << " -d \"F R U R'\"        # Show graphical interface" << std::endl;
}

int main(int argc, char** argv) {
  bool showDisplay = false;
  bool useRandom = false;
  bool calculateDatabase = false;
  bool showSteps = false;
  std::string movements_str = "";

  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-d") == 0) {
      showDisplay = true;
    } else if (strcmp(argv[i], "-r") == 0) {
      useRandom = true;
    } else if (strcmp(argv[i], "-c") == 0) {
      calculateDatabase = true;
    } else if (strcmp(argv[i], "-g") == 0) {
      showSteps = true;
    } else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
      printUsage(argv[0]);
      return EXIT_SUCCESS;
    } else if (argv[i][0] != '-') {
      movements_str = argv[i];
    } else {
      std::cerr << "Unknown option: " << argv[i] << std::endl;
      printUsage(argv[0]);
      return EXIT_FAILURE;
    }
  }

  if (calculateDatabase) {
    generateDatabase();
    return EXIT_SUCCESS;
  }

  Cube cube;
  if (useRandom) {
    srand(time(nullptr));
    cube.randomize(20);
    std::cout << "Generated random cube with 20 moves." << std::endl;
  } else if (!movements_str.empty()) {
    std::stringstream ss(movements_str);
    std::string word;
    while (ss >> word) {
      try {
        Movement movement(word);
        movements.push_back(movement);
        cube.rotate(movement);
      } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
      }
    }

    if (movements.empty()) {
      std::cerr << "No valid movements provided." << std::endl;
      return EXIT_FAILURE;
    }
  } else {
    std::cout << "No cube state specified. Use -r for random cube or provide movement string." << std::endl;
    printUsage(argv[0]);
    return EXIT_FAILURE;
  }

  if (showSteps) {
    std::cout << "Initial cube state:" << std::endl
              << cube << std::endl;
  }

  if (cube.is_solved()) {
    std::cout << "Cube is already solved!" << std::endl;
    if (showDisplay) {
      initGL(argc, argv);
      glutDisplayFunc(display);
      glutKeyboardFunc(keyboard);
      glutSpecialFunc(specialKeys);
      glutTimerFunc(RubikConfig::FRAME_TIME, timer, 0);
      glutMainLoop();
    }
    return EXIT_SUCCESS;
  }

  auto start = std::chrono::high_resolution_clock::now();
  solveCube(cube, showSteps);
  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

  std::cout << "\nSolution: ";
  for (const auto& move : solution) {
    std::cout << move << " ";
  }
  std::cout << "(" << solution.size() << " moves)" << std::endl;

  auto ns = duration.count();
  double total_seconds = ns / 1e9;
  std::cout << "Time spent calculating solution: "
            << total_seconds << "s" << std::endl;

  if (cube.is_solved()) {
    std::cout << "Cube is solved!" << std::endl;
  } else {
    std::cout << "Cube is not solved." << std::endl;
  }

  if (showDisplay) {
    initGL(argc, argv);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    glutTimerFunc(RubikConfig::FRAME_TIME, timer, 0);
    glutMainLoop();
  }

  return EXIT_SUCCESS;
}
