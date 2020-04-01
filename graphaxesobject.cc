#include "graphaxesobject.h"

#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include <QPainter>
#include <QCursor>

GraphAxesObject::GraphAxesObject() {
  m_program = new QOpenGLShaderProgram;
  m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/vertexShaderAxes.vs");
  m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/fragmentShaderAxes.fs");
  m_program->bindAttributeLocation("position", 0);
  m_program->link();

  m_program->bind();
  m_mvpMatrixLoc = m_program->uniformLocation("mvpMatrix");
  m_program->release();

  QVector<float> vertices {};

  for (size_t i {}; i < 3; i++) {
    for (size_t j {}; j < 10; j++) {
      for (size_t k {}; k < 2; k++) {
        QVector3D p {};
        p[i] = j / 10.f;
        vertices << p[0] << p[1] << p[2];
        p[(i + 1 + k) % 3] = 1.f;
        vertices << p[0] << p[1] << p[2];
      }
    }
  }

  m_vao.create();
  m_vao.bind();

  m_vbo.create();
  m_vbo.bind();

  m_vbo.allocate(vertices.data(), vertices.size() * sizeof(GLfloat));

  QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
  f->glEnableVertexAttribArray(0);
  f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

  m_vbo.release();
  m_vao.release();

  m_axes = 0;
}

GraphAxesObject::~GraphAxesObject() {
  delete m_program;
  m_program = nullptr;
  m_vao.destroy();
  m_vbo.destroy();
}

void GraphAxesObject::draw(const QMatrix4x4 &mvp) {
  m_program->bind();
  m_vao.bind();
  m_vbo.bind();
  m_program->setUniformValue(m_mvpMatrixLoc, mvp);
  QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
  f->glDrawArrays(GL_LINES, 0, m_vbo.size() / (3 * sizeof (GLfloat)));
  m_vbo.release();
  m_vao.release();
  m_program->release();
}

#include <iostream>

void GraphAxesObject::draw(const QMatrix4x4 &mv, const QMatrix4x4 &p, QPainter &painter) {
  painter.setPen(Qt::white);
  painter.setFont(QFont("Courier New", 10));

  size_t width = painter.device()->width();
  size_t height = painter.device()->height();

  QVector3D pos {};

  for (size_t j = 1; j < 10; j++) {
    pos = QVector3D(j / 10.f, 1.04f, -0.04f);
    pos = pos.project(mv, p, QRect(0, 0, width, height));
    painter.drawText(pos[0] - 50, height - pos[1] - 50, 100, 100, Qt::AlignCenter, QString::number(j / 10.f));
  }

  pos = QVector3D(.5f, 1.09f, -0.09f);
  pos = pos.project(mv, p, QRect(0, 0, width, height));
  painter.drawText(pos[0] - 50, height - pos[1] - 50, 100, 100, Qt::AlignCenter, "x");

  for (size_t j = 1; j < 10; j++) {
    pos = QVector3D(-0.06f, j / 10.f, 1.06f);
    pos = pos.project(mv, p, QRect(0, 0, width, height));
    painter.drawText(pos[0] - 50, height - pos[1] - 50, 100, 100, Qt::AlignCenter, QString::number(j / 10.f));
  }

  pos = QVector3D(-0.14f, .5f, 1.14f);
  pos = pos.project(mv, p, QRect(0, 0, width, height));
  painter.drawText(pos[0] - 50, height - pos[1] - 50, 100, 100, Qt::AlignCenter, "y");

  for (size_t j = 1; j < 10; j++) {
    pos = QVector3D(1.06f, -0.04f, j / 10.f);
    pos = pos.project(mv, p, QRect(0, 0, width, height));
    painter.drawText(pos[0] - 50, height - pos[1] - 50, 100, 100, Qt::AlignCenter, QString::number(j / 10.f));
  }

  pos = QVector3D(1.14f, -0.09f, .5f);
  pos = pos.project(mv, p, QRect(0, 0, width, height));

  if (m_axes == 0) {
    painter.drawText(pos[0] - 50, height - pos[1] - 50, 100, 100, Qt::AlignCenter, "z");
  }
  else {
    painter.drawText(pos[0] - 50, height - pos[1] - 50, 100, 100, Qt::AlignCenter, "Y");
  }
}

void GraphAxesObject::setAxes(int axes) {
  m_axes = axes;
}
