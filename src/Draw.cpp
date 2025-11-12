#include "Draw.hpp"

#include "Config.hpp"

void initGL(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(RubikConfig::WINDOW_WIDTH, RubikConfig::WINDOW_HEIGHT);
  glutInitWindowPosition(100, 100);
  glutCreateWindow(RubikConfig::WINDOW_TITLE);

  glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
  glShadeModel(GL_SMOOTH);
  setupLighting();
  glutReshapeFunc(reshape);
}

void reshape(int w, int h) {
  if (h == 0) h = 1;
  float aspect = static_cast<float>(w) / static_cast<float>(h);

  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(RubikConfig::FOV, aspect, RubikConfig::NEAR_PLANE, RubikConfig::FAR_PLANE);
  glMatrixMode(GL_MODELVIEW);
}

void drawCube(std::map<Face, float[3]> face_colors, float cube_size) {
  const float half_size = cube_size / 2.0f;

  glBegin(GL_QUADS);
  glColor3f(0.1f, 0.1f, 0.1f);
  glVertex3f(-half_size, -half_size, half_size);
  glVertex3f(half_size, -half_size, half_size);
  glVertex3f(half_size, half_size, half_size);
  glVertex3f(-half_size, half_size, half_size);

  glVertex3f(-half_size, -half_size, -half_size);
  glVertex3f(-half_size, half_size, -half_size);
  glVertex3f(half_size, half_size, -half_size);
  glVertex3f(half_size, -half_size, -half_size);

  glVertex3f(-half_size, half_size, -half_size);
  glVertex3f(-half_size, half_size, half_size);
  glVertex3f(half_size, half_size, half_size);
  glVertex3f(half_size, half_size, -half_size);

  glVertex3f(-half_size, -half_size, -half_size);
  glVertex3f(half_size, -half_size, -half_size);
  glVertex3f(half_size, -half_size, half_size);
  glVertex3f(-half_size, -half_size, half_size);

  glVertex3f(half_size, -half_size, -half_size);
  glVertex3f(half_size, half_size, -half_size);
  glVertex3f(half_size, half_size, half_size);
  glVertex3f(half_size, -half_size, half_size);

  glVertex3f(-half_size, -half_size, -half_size);
  glVertex3f(-half_size, -half_size, half_size);
  glVertex3f(-half_size, half_size, half_size);
  glVertex3f(-half_size, half_size, -half_size);
  glEnd();

  float small_size = half_size * RubikConfig::FACE_SCALE;
  glBegin(GL_QUADS);
  if (face_colors.find(FRONT) != face_colors.end()) {
    glColor3f(face_colors[FRONT][0], face_colors[FRONT][1], face_colors[FRONT][2]);
    glVertex3f(-small_size, -small_size, half_size + RubikConfig::FACE_OFFSET);
    glVertex3f(small_size, -small_size, half_size + RubikConfig::FACE_OFFSET);
    glVertex3f(small_size, small_size, half_size + RubikConfig::FACE_OFFSET);
    glVertex3f(-small_size, small_size, half_size + RubikConfig::FACE_OFFSET);
  }
  if (face_colors.find(BACK) != face_colors.end()) {
    glColor3f(face_colors[BACK][0], face_colors[BACK][1], face_colors[BACK][2]);
    glVertex3f(-small_size, -small_size, -(half_size + RubikConfig::FACE_OFFSET));
    glVertex3f(-small_size, small_size, -(half_size + RubikConfig::FACE_OFFSET));
    glVertex3f(small_size, small_size, -(half_size + RubikConfig::FACE_OFFSET));
    glVertex3f(small_size, -small_size, -(half_size + RubikConfig::FACE_OFFSET));
  }
  if (face_colors.find(UP) != face_colors.end()) {
    glColor3f(face_colors[UP][0], face_colors[UP][1], face_colors[UP][2]);
    glVertex3f(-small_size, half_size + RubikConfig::FACE_OFFSET, -small_size);
    glVertex3f(-small_size, half_size + RubikConfig::FACE_OFFSET, small_size);
    glVertex3f(small_size, half_size + RubikConfig::FACE_OFFSET, small_size);
    glVertex3f(small_size, half_size + RubikConfig::FACE_OFFSET, -small_size);
  }
  if (face_colors.find(DOWN) != face_colors.end()) {
    glColor3f(face_colors[DOWN][0], face_colors[DOWN][1], face_colors[DOWN][2]);
    glVertex3f(-small_size, -(half_size + RubikConfig::FACE_OFFSET), -small_size);
    glVertex3f(small_size, -(half_size + RubikConfig::FACE_OFFSET), -small_size);
    glVertex3f(small_size, -(half_size + RubikConfig::FACE_OFFSET), small_size);
    glVertex3f(-small_size, -(half_size + RubikConfig::FACE_OFFSET), small_size);
  }
  if (face_colors.find(RIGHT) != face_colors.end()) {
    glColor3f(face_colors[RIGHT][0], face_colors[RIGHT][1], face_colors[RIGHT][2]);
    glVertex3f(half_size + RubikConfig::FACE_OFFSET, -small_size, -small_size);
    glVertex3f(half_size + RubikConfig::FACE_OFFSET, small_size, -small_size);
    glVertex3f(half_size + RubikConfig::FACE_OFFSET, small_size, small_size);
    glVertex3f(half_size + RubikConfig::FACE_OFFSET, -small_size, small_size);
  }
  if (face_colors.find(LEFT) != face_colors.end()) {
    glColor3f(face_colors[LEFT][0], face_colors[LEFT][1], face_colors[LEFT][2]);
    glVertex3f(-(half_size + RubikConfig::FACE_OFFSET), -small_size, -small_size);
    glVertex3f(-(half_size + RubikConfig::FACE_OFFSET), -small_size, small_size);
    glVertex3f(-(half_size + RubikConfig::FACE_OFFSET), small_size, small_size);
    glVertex3f(-(half_size + RubikConfig::FACE_OFFSET), small_size, -small_size);
  }
  glEnd();
}

void drawCorner(Corner position, CornerData corner, float cube_size, Move animMove, float animAngle) {
  float x, y, z;
  getCornerPositionCoordinates(position, x, y, z);

  glPushMatrix();
  if (isPieceOnMove(animMove, position)) {
    float axisX = 0.0f, axisY = 0.0f, axisZ = 0.0f;
    getRotationAxisAndCenter(animMove, axisX, axisY, axisZ);
    float angle = animAngle;
    if (animMove == MOVE_BACK || animMove == MOVE_DOWN || animMove == MOVE_RIGHT) {
      angle = -animAngle;
    }
    glRotatef(angle, axisX, axisY, axisZ);
  }

  glTranslatef(x * cube_size, y * cube_size, z * cube_size);
  std::map<Face, float[3]> face_colors = corner.getFaceColors(position);
  drawCube(face_colors, cube_size);
  glPopMatrix();
}

void drawEdge(Edge position, EdgeData edge, float cube_size, Move animMove, float animAngle) {
  float x, y, z;
  getEdgePositionCoordinates(position, x, y, z);

  glPushMatrix();
  if (isPieceOnMove(animMove, position)) {
    float axisX = 0.0f, axisY = 0.0f, axisZ = 0.0f;
    getRotationAxisAndCenter(animMove, axisX, axisY, axisZ);
    float angle = animAngle;
    if (animMove == MOVE_BACK || animMove == MOVE_DOWN || animMove == MOVE_RIGHT) {
      angle = -animAngle;
    }
    glRotatef(angle, axisX, axisY, axisZ);
  }

  glTranslatef(x * cube_size, y * cube_size, z * cube_size);
  std::map<Face, float[3]> face_colors = edge.getFaceColors(position);
  drawCube(face_colors, cube_size);
  glPopMatrix();
}

void drawCenter(Face face, float cube_size, Move animMove, float animAngle) {
  float x, y, z;
  getFacePositionCoordinates(face, x, y, z);

  glPushMatrix();
  if (isPieceOnMove(animMove, face)) {
    float axisX = 0.0f, axisY = 0.0f, axisZ = 0.0f;
    getRotationAxisAndCenter(animMove, axisX, axisY, axisZ);
    float angle = animAngle;
    if (animMove == MOVE_BACK || animMove == MOVE_DOWN || animMove == MOVE_RIGHT) {
      angle = -animAngle;
    }
    glRotatef(angle, axisX, axisY, axisZ);
  }

  glTranslatef(x * cube_size, y * cube_size, z * cube_size);
  std::map<Face, float[3]> face_colors = {};
  float color[3];
  getFaceColor(face, color);
  face_colors[face][0] = color[0];
  face_colors[face][1] = color[1];
  face_colors[face][2] = color[2];
  drawCube(face_colors, cube_size);
  glPopMatrix();
}

void drawHelpText(int window_width, int window_height) {
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glOrtho(0, window_width, 0, window_height, -1, 1);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();
  glPushAttrib(GL_ENABLE_BIT | GL_LIGHTING_BIT | GL_DEPTH_BUFFER_BIT);
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_LIGHTING);

  glColor3f(0.0f, 0.0f, 0.0f);
  float y_pos = window_height - 30.0f;
  float x_pos = 20.0f;
  const char* help_lines[] = {
      "Controles:",
      "Setas: Gira câmera",
      "F/B/L/R/U/D: Gira faces do cubo",
      "ESC: Sair"};

  for (int i = 0; i < 4; i++) {
    glRasterPos2f(x_pos, y_pos - (i * 30.0f));
    const char* text = help_lines[i];
    while (*text) {
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *text);
      text++;
    }
  }

  glPopAttrib();
  glPopMatrix();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
}

void setupLighting() {
  glEnable(GL_LIGHTING);
  glEnable(GL_COLOR_MATERIAL);
  glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

  glEnable(GL_LIGHT0);
  glLightfv(GL_LIGHT0, GL_AMBIENT, RubikConfig::LIGHT_AMBIENT);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, RubikConfig::LIGHT_DIFFUSE);
  glEnable(GL_LIGHT1);
  glLightfv(GL_LIGHT0, GL_AMBIENT, RubikConfig::LIGHT1_AMBIENT);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, RubikConfig::LIGHT1_DIFFUSE);
}

void updateLightPosition() {
  glLightfv(GL_LIGHT0, GL_POSITION, RubikConfig::LIGHT0_POSITION);
  glLightfv(GL_LIGHT1, GL_POSITION, RubikConfig::LIGHT1_POSITION);
}

void getRotationAxisAndCenter(Move move, float& axisX, float& axisY, float& axisZ) {
  axisX = 0.0f;
  axisY = 0.0f;
  axisZ = 0.0f;

  switch (move) {
    case MOVE_FRONT:
    case MOVE_BACK:
      axisZ = -1.0f;
      break;
    case MOVE_UP:
    case MOVE_DOWN:
      axisY = -1.0f;
      break;
    case MOVE_LEFT:
    case MOVE_RIGHT:
      axisX = 1.0f;
      break;
  }
}
