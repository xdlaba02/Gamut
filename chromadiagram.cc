#include "chromadiagram.h"

#include "graphaxesobject.h"
#include "graphgamutobject.h"

ChromaDiagram::ChromaDiagram() {
  m_axes = new GraphAxesObject();
  m_gamut = new GraphGamutObject();
}

ChromaDiagram::~ChromaDiagram() {
  delete m_axes;
  delete m_gamut;
}

void ChromaDiagram::draw(const QMatrix4x4 &mvp) {
  m_axes->draw(mvp);
  m_gamut->draw(mvp);
}

void ChromaDiagram::draw(const QMatrix4x4 &mv, const QMatrix4x4 &p, QPainter &painter) {
  m_axes->draw(mv, p, painter);
}

void ChromaDiagram::setObserver(int observer) {
  m_gamut->setObserver(observer);
}

void ChromaDiagram::setWorkingSpace(int space) {
  m_gamut->setWorkingSpace(space);
}

void ChromaDiagram::setGamma(float gamma) {
  m_gamut->setGamma(gamma);
}

void ChromaDiagram::setIlluminant(int illuminant) {
  m_gamut->setIlluminant(illuminant);
}

void ChromaDiagram::setAxes(int axes) {
  m_gamut->setAxes(axes);
  m_axes->setAxes(axes);
}

void ChromaDiagram::setMinLambda(int lambda) {
  m_gamut->setMinLambda(lambda);
}

void ChromaDiagram::setMaxLambda(int lambda) {
  m_gamut->setMaxLambda(lambda);
}
