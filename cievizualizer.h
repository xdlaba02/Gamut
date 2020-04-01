#ifndef CIEVIZUALIZER_H
#define CIEVIZUALIZER_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QMatrix4x4>

#include "chromadiagram.h"

QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)

class CIEVizualizer: public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT

public:
    CIEVizualizer(QWidget *parent = nullptr);
    ~CIEVizualizer();

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;

public slots:
    void setObserver(int observer);
    void setWorkingSpace(int space);
    void setGamma(float gamma);
    void setIlluminant(int illuminant);
    void setAxes(int axes);
    void setMinLambda(int lambda);
    void setMaxLambda(int lambda);
    void setRotation(float x, float y, float z);
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);

signals:
    void observerChanged(int i);
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    void setupVertexAttribs();

    QPoint m_lastPos;
    int m_xRot;
    int m_yRot;
    int m_zRot;

    QMatrix4x4 m_proj;
    QMatrix4x4 m_camera;
    QMatrix4x4 m_world;

    ChromaDiagram *m_diagram;
};

#endif // CIEVIZUALIZER_H
