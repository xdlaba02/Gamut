#ifndef GRAPHAXESOBJECT_H
#define GRAPHAXESOBJECT_H

#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>

class QMatrix4x4;
class QOpenGLShaderProgram;
class QPainter;

class GraphAxesObject {
public:
  GraphAxesObject();
  ~GraphAxesObject();
  void draw(const QMatrix4x4 &mvp);
  void draw(const QMatrix4x4 &mv, const QMatrix4x4 &p, QPainter &painter);

  void setAxes(int axes);

private:
  int m_axes;

  QOpenGLVertexArrayObject m_vao;
  QOpenGLBuffer m_vbo;
  QOpenGLShaderProgram *m_program;

  int m_mvpMatrixLoc;
};

#endif // GRAPHAXESOBJECT_H
