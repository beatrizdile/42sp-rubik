#include "Draw.hpp"

#include <cmath>

#include "Config.hpp"

void initGL(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
  glEnable(GL_MULTISAMPLE);
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

inline void vertexInPlane(Plane plane, float u, float v, float w) {
  switch (plane) {
    case XY:
      glVertex3f(u, v, w);
      break;
    case XZ:
      glVertex3f(u, w, v);
      break;
    case YZ:
      glVertex3f(w, u, v);
      break;
  }
}

void drawRoundedQuad(Plane plane, float u1, float v1, float w, float u2, float v2, float radius, int segments = 6) {
  float minU = fmin(u1, u2);
  float maxU = fmax(u1, u2);
  float minV = fmin(v1, v2);
  float maxV = fmax(v1, v2);

  float width = maxU - minU;
  float height = maxV - minV;
  float maxRadius = fmin(width, height) * 0.5f;
  if (radius > maxRadius) radius = maxRadius;

  glBegin(GL_QUADS);
  vertexInPlane(plane, minU + radius, minV, w);
  vertexInPlane(plane, maxU - radius, minV, w);
  vertexInPlane(plane, maxU - radius, maxV, w);
  vertexInPlane(plane, minU + radius, maxV, w);
  glEnd();

  glBegin(GL_QUADS);
  vertexInPlane(plane, minU, minV + radius, w);
  vertexInPlane(plane, minU + radius, minV + radius, w);
  vertexInPlane(plane, minU + radius, maxV - radius, w);
  vertexInPlane(plane, minU, maxV - radius, w);
  glEnd();

  glBegin(GL_QUADS);
  vertexInPlane(plane, maxU - radius, minV + radius, w);
  vertexInPlane(plane, maxU, minV + radius, w);
  vertexInPlane(plane, maxU, maxV - radius, w);
  vertexInPlane(plane, maxU - radius, maxV - radius, w);
  glEnd();

  float angleStep = (M_PI * 0.5f) / segments;
  CornerDraw corners[4] = {
      {minU + radius, minV + radius, M_PI},
      {maxU - radius, minV + radius, M_PI * 1.5f},
      {maxU - radius, maxV - radius, 0.0f},
      {minU + radius, maxV - radius, M_PI * 0.5f}};

  for (const auto& corner : corners) {
    glBegin(GL_TRIANGLE_FAN);
    vertexInPlane(plane, corner.centerU, corner.centerV, w);
    for (int i = 0; i <= segments; i++) {
      float angle = corner.startAngle + i * angleStep;
      float u = corner.centerU + radius * cos(angle);
      float v = corner.centerV + radius * sin(angle);
      vertexInPlane(plane, u, v, w);
    }
    glEnd();
  }
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
  float radius = RubikConfig::ROUNDED_CORNER_RADIUS * half_size;
  float offset = half_size + RubikConfig::FACE_OFFSET;
  FaceParams faceParams[] = {
      {FRONT, XY, -small_size, -small_size, offset, small_size, small_size},
      {BACK, XY, -small_size, -small_size, -offset, small_size, small_size},
      {UP, XZ, -small_size, -small_size, offset, small_size, small_size},
      {DOWN, XZ, -small_size, -small_size, -offset, small_size, small_size},
      {RIGHT, YZ, -small_size, -small_size, offset, small_size, small_size},
      {LEFT, YZ, -small_size, -small_size, -offset, small_size, small_size}};

  for (const auto& params : faceParams) {
    auto it = face_colors.find(params.face);
    if (it != face_colors.end()) {
      glColor3f(it->second[0], it->second[1], it->second[2]);
      drawRoundedQuad(params.plane, params.u1, params.v1, params.w,
                      params.u2, params.v2, radius);
    }
  }
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
  float y_pos = window_height - 20.0f;
  float x_pos = 10.0f;
  const char* help_lines[] = {
      "Controles:",
      "Numeros (1-6): Rotacao dupla (F2,B2,R2,L2,U2,D2)",
      "Maiusculas (F,B,R,L,U,D): Rotacao anti-horaria",
      "Minusculas (f,b,r,l,u,d): Rotacao horaria",
      "Setas: Gira camera",
      "ESC: Sair"};

  for (int i = 0; i < 6; i++) {
    glRasterPos2f(x_pos, y_pos - (i * 20.0f));
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
