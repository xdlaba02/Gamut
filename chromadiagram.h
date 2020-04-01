#ifndef GRAPHCHROMADIAGRAM_H
#define GRAPHCHROMADIAGRAM_H

class QMatrix4x4;
class GraphGamutObject;
class GraphAxesObject;
class QPainter;
class QPoint;

class ChromaDiagram {
public:
  ChromaDiagram();
  ~ChromaDiagram();

  void draw(const QMatrix4x4 &mvp);
  void draw(const QMatrix4x4 &mv, const QMatrix4x4 &p, QPainter &painter);

  void setObserver(int observer);
  void setWorkingSpace(int space);
  void setGamma(float gamma);
  void setIlluminant(int illuminant);
  void setAxes(int axes);
  void setMinLambda(int lambda);
  void setMaxLambda(int lambda);

private:
  GraphGamutObject *m_gamut;
  GraphAxesObject  *m_axes;
};

#endif // GRAPHCHROMADIAGRAM_H
