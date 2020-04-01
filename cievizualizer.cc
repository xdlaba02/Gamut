#include "cievizualizer.h"

#include <QMouseEvent>
#include <QOpenGLShaderProgram>
#include <QCoreApplication>
#include <QPainter>

#include <cmath>
#include <iostream>

CIEVizualizer::CIEVizualizer(QWidget *parent): QOpenGLWidget{parent}, m_xRot{}, m_yRot{}, m_zRot{}, m_diagram{} {}

CIEVizualizer::~CIEVizualizer() {
  makeCurrent();
  delete m_diagram;
  doneCurrent();
}

QSize CIEVizualizer::minimumSizeHint() const {
  return QSize(50, 50);
}

QSize CIEVizualizer::sizeHint() const {
  return QSize(400, 400);
}

static void qNormalizeAngle(int &angle) {
  while (angle < 0)
    angle += 360 * 16;
  while (angle > 360 * 16)
    angle -= 360 * 16;
}

void CIEVizualizer::setXRotation(int angle) {
  qNormalizeAngle(angle);
  if (angle != m_xRot) {
    m_xRot = angle;
    emit xRotationChanged(angle);
  }
}

void CIEVizualizer::setYRotation(int angle) {
  qNormalizeAngle(angle);
  if (angle != m_yRot) {
    m_yRot = angle;
    emit yRotationChanged(angle);
  }
}

void CIEVizualizer::setZRotation(int angle) {
  qNormalizeAngle(angle);
  if (angle != m_zRot) {
    m_zRot = angle;
    emit zRotationChanged(angle);
  }
}

void CIEVizualizer::initializeGL() {
  initializeOpenGLFunctions();
  QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
  f->glClearColor(0, 0, 0, 1);

  m_diagram = new ChromaDiagram();

  m_camera.setToIdentity();
  m_camera.translate(0, 0, -2);
}

void CIEVizualizer::setObserver(int observer) {
  m_diagram->setObserver(observer);
  update();
}

void CIEVizualizer::setWorkingSpace(int space) {
  m_diagram->setWorkingSpace(space);
  update();
}

void CIEVizualizer::setGamma(float gamma) {
  m_diagram->setGamma(gamma);
  update();
}

void CIEVizualizer::setIlluminant(int illuminant) {
  m_diagram->setIlluminant(illuminant);
  update();
}

void CIEVizualizer::setAxes(int axes) {
  m_diagram->setAxes(axes);
  update();
}

void CIEVizualizer::setMinLambda(int lambda) {
  m_diagram->setMinLambda(lambda);
  update();
}

void CIEVizualizer::setMaxLambda(int lambda) {
  m_diagram->setMaxLambda(lambda);
  update();
}

void CIEVizualizer::setRotation(float x, float y, float z) {
  m_xRot = x;
  m_yRot = y;
  m_zRot = z;
  update();
}

void CIEVizualizer::paintGL() {
  QPainter painter(this);

  m_world.setToIdentity();
  m_world.rotate(m_xRot / 16.0f, 1, 0, 0);
  m_world.rotate(m_yRot / 16.0f, 0, 1, 0);
  m_world.rotate(m_zRot / 16.0f, 0, 0, 1);
  m_world.translate(QVector3D(-.5, -.5, -.5));

  painter.beginNativePainting();
  QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
  f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  f->glEnable(GL_DEPTH_TEST);
  f->glEnable(GL_PROGRAM_POINT_SIZE);

  m_diagram->draw(m_proj * m_camera * m_world);

  f->glDisable(GL_DEPTH_TEST);
  painter.endNativePainting();

  m_diagram->draw(m_camera * m_world, m_proj, painter);

  painter.end();
}

void CIEVizualizer::resizeGL(int w, int h) {
  m_proj.setToIdentity();
  float A = static_cast<float>(w) / h;
  if (A > 1) {
    m_proj.ortho(-A, A, -1, 1, 0.01f, 100.0f);
  } else {
    m_proj.ortho(-1, 1, -1/A, 1/A, 0.01f, 100.0f);
  }
}

void CIEVizualizer::mousePressEvent(QMouseEvent *event) {
  m_lastPos = event->pos();
  update();
}

void CIEVizualizer::mouseMoveEvent(QMouseEvent *event) {
  int dx = event->x() - m_lastPos.x();
  int dy = event->y() - m_lastPos.y();

  if (event->buttons() & Qt::LeftButton) {
    setXRotation(m_xRot + 8 * dy);
    setYRotation(m_yRot + 8 * dx);
    update();
  }

  m_lastPos = event->pos();
}
