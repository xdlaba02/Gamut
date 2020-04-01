#ifndef GRAPHGAMUTOBJECT_H
#define GRAPHGAMUTOBJECT_H

#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QMatrix3x3>
#include <QPainter>

class QOpenGLShaderProgram;

class GraphGamutObject {
public:
  GraphGamutObject();
  ~GraphGamutObject();
  void draw(const QMatrix4x4 &mvp);
  void genData();

  void setObserver(int observer);
  void setWorkingSpace(int space);
  void setGamma(float gamma);
  void setIlluminant(int illuminant);
  void setAxes(int axes);
  void setMinLambda(int lambda);
  void setMaxLambda(int lambda);

private:
  size_t m_observer;
  size_t m_illuminant;
  size_t m_axes;
  size_t m_min_lambda;
  size_t m_max_lambda;
  float m_gamma;

  QMatrix3x3 m_colorMatrix;

  QOpenGLVertexArrayObject m_vao;
  QOpenGLBuffer m_vbo;

  QOpenGLShaderProgram *m_program[2];
  int m_mvpMatrixLoc[2];
  int m_colorMatrixLoc[2];
  int m_gammaLoc[2];
  GLenum m_mode[2];
};

#endif // GRAPHGAMUTOBJECT_H
