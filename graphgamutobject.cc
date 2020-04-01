#include "graphgamutobject.h"
#include "cieobserver.h"

#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>

#include <iostream>
#include <cmath>

GraphGamutObject::GraphGamutObject() {
  m_program[0] = new QOpenGLShaderProgram;
  m_program[0]->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/vertexShaderGamut2D.vs");
  m_program[0]->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/fragmentShaderGamut.fs");
  m_program[0]->bindAttributeLocation("position", 0);
  m_program[0]->link();

  m_program[0]->bind();
  m_mvpMatrixLoc[0] = m_program[0]->uniformLocation("mvpMatrix");
  m_colorMatrixLoc[0] = m_program[0]->uniformLocation("colorMatrix");
  m_gammaLoc[0] = m_program[0]->uniformLocation("gamma");
  m_program[0]->release();

  m_mode[0] = GL_TRIANGLE_FAN;

  m_program[1] = new QOpenGLShaderProgram;
  m_program[1]->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/vertexShaderGamut3D.vs");
  m_program[1]->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/fragmentShaderGamut.fs");
  m_program[1]->bindAttributeLocation("position", 0);
  m_program[1]->link();

  m_program[1]->bind();
  m_mvpMatrixLoc[1] = m_program[1]->uniformLocation("mvpMatrix");
  m_colorMatrixLoc[1] = m_program[1]->uniformLocation("colorMatrix");
  m_gammaLoc[1] = m_program[1]->uniformLocation("gamma");
  m_program[1]->release();

  m_mode[1] = GL_TRIANGLES;

  m_observer = 0;
  m_illuminant = 0;
  m_axes = 0;
  m_min_lambda = 360;
  m_max_lambda = 780;

  setWorkingSpace(0);
  setGamma(2.2);

  QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
  m_vao.create();
  m_vao.bind();
  m_vbo.create();
  m_vbo.bind();

  f->glEnableVertexAttribArray(0);
  f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);

  m_vbo.release();
  m_vao.release();

  genData();
}

GraphGamutObject::~GraphGamutObject() {
  for (size_t i {}; i < 2; i++) {
    delete m_program[i];
    m_program[i] = nullptr;
  }

  m_vao.destroy();
  m_vbo.destroy();
}

void GraphGamutObject::draw(const QMatrix4x4 &mvp) {
  QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();

  m_vao.bind();
  m_vbo.bind();
  m_program[m_axes]->bind();
  m_program[m_axes]->setUniformValue(m_mvpMatrixLoc[m_axes], mvp);
  m_program[m_axes]->setUniformValue(m_colorMatrixLoc[m_axes], m_colorMatrix);
  m_program[m_axes]->setUniformValue(m_gammaLoc[m_axes], m_gamma);
  f->glDrawArrays(m_mode[m_axes], 0, m_vbo.size() / (3 * sizeof (GLfloat)));
  m_program[m_axes]->release();

  m_vbo.release();
  m_vao.release();
}

void GraphGamutObject::genData() {
  QVector<float> gamut_vertices {};

  int lambda_diff = m_max_lambda - m_min_lambda;

  if (m_axes == 0) {
    float lambda_step = 1.f;
    size_t N = lambda_diff / lambda_step + 1;
    for (size_t i = 0; i < N; i++) {
      float lambda = m_min_lambda + i * lambda_step;

      float X, Y, Z;
      getCIEXYZ(lambda, m_observer, X, Y, Z);
      float sum = X + Y + Z;
      gamut_vertices << X / sum << Y / sum << Y;
    }
  }
  else {
    float lambda_step = 5.f;
    size_t N = lambda_diff / lambda_step + 1;
    std::vector<std::vector<std::array<float, 3>>> points_hill(N);
    std::vector<std::vector<std::array<float, 3>>> points_valley(N);

    for (size_t k = 1; k < N; k++) {
      for (size_t i = 0; i < N - k; i++) {
        float lambda1 = m_min_lambda + i * lambda_step;
        float lambda2 = m_min_lambda + (i + k) * lambda_step;

        float sum_x[2] {};
        float sum_y[2] {};
        float sum_z[2] {};
        float sum_w {};
        for (size_t j {}; j < N; j++) {
          float lambda = j * lambda_step + m_min_lambda;

          float Lw = getIlluminant(lambda, m_illuminant);

          float x_bar, y_bar, z_bar;
          getCIEXYZ(lambda, m_observer, x_bar, y_bar, z_bar);

          if (lambda > lambda1 && lambda < lambda2) {
            sum_x[0] += Lw * x_bar;
            sum_y[0] += Lw * y_bar;
            sum_z[0] += Lw * z_bar;
          }
          if (lambda <= lambda1 || lambda >= lambda2) {
            sum_x[1] += Lw * x_bar;
            sum_y[1] += Lw * y_bar;
            sum_z[1] += Lw * z_bar;
          }

          sum_w += Lw * y_bar;
        }

        float X {}, Y {}, Z {}, sum {};

        X = sum_x[0] / sum_w;
        Y = sum_y[0] / sum_w;
        Z = sum_z[0] / sum_w;

        sum = X + Y + Z;
        points_hill[k].push_back({X / sum, Y / sum, Y});

        X = sum_x[1] / sum_w;
        Y = sum_y[1] / sum_w;
        Z = sum_z[1] / sum_w;

        sum = X + Y + Z;
        points_valley[k].push_back({X / sum, Y / sum, Y});
      }
    }

    for (size_t k = 1; k < N - 1; k++) {
      for (size_t i {}; i < N - k - 1; i++) {
        gamut_vertices << points_hill[k][i][0]     << points_hill[k][i][1]     << points_hill[k][i][2];
        gamut_vertices << points_hill[k + 1][i][0] << points_hill[k + 1][i][1] << points_hill[k + 1][i][2];
        gamut_vertices << points_hill[k][i + 1][0] << points_hill[k][i + 1][1] << points_hill[k][i + 1][2];
      }
      for (size_t i {}; i < N - k - 2; i++) {
        gamut_vertices << points_hill[k + 1][i][0]     << points_hill[k + 1][i][1]     << points_hill[k + 1][i][2];
        gamut_vertices << points_hill[k + 1][i + 1][0] << points_hill[k + 1][i + 1][1] << points_hill[k + 1][i + 1][2];
        gamut_vertices << points_hill[k][i + 1][0]     << points_hill[k][i + 1][1]     << points_hill[k][i + 1][2];
      }
      for (size_t i {}; i < N - k - 1; i++) {
        gamut_vertices << points_valley[k][i][0]     << points_valley[k][i][1]     << points_valley[k][i][2];
        gamut_vertices << points_valley[k + 1][i][0] << points_valley[k + 1][i][1] << points_valley[k + 1][i][2];
        gamut_vertices << points_valley[k][i + 1][0] << points_valley[k][i + 1][1] << points_valley[k][i + 1][2];
      }
      for (size_t i {}; i < N - k - 2; i++) {
        gamut_vertices << points_valley[k + 1][i][0]     << points_valley[k + 1][i][1]     << points_valley[k + 1][i][2];
        gamut_vertices << points_valley[k + 1][i + 1][0] << points_valley[k + 1][i + 1][1] << points_valley[k + 1][i + 1][2];
        gamut_vertices << points_valley[k][i + 1][0]     << points_valley[k][i + 1][1]     << points_valley[k][i + 1][2];
      }

      //sew hill and valley together
      gamut_vertices << points_hill[k    ][N - k - 1][0] << points_hill[k    ][N - k - 1][1] << points_hill[k    ][N - k - 1][2];
      gamut_vertices << points_hill[k + 1][N - k - 2][0] << points_hill[k + 1][N - k - 2][1] << points_hill[k + 1][N - k - 2][2];
      gamut_vertices << points_valley[N - k][0][0]       << points_valley[N - k][0][1]       << points_valley[N - k][0][2];

      gamut_vertices << points_hill[k + 1][N - k - 2][0] << points_hill[k + 1][N - k - 2][1] << points_hill[k + 1][N - k - 2][2];
      gamut_vertices << points_valley[N - k][0][0]       << points_valley[N - k][0][1]       << points_valley[N - k][0][2];
      gamut_vertices << points_valley[N - k - 1][0][0]   << points_valley[N - k - 1][0][1]   << points_valley[N - k - 1][0][2];

      gamut_vertices << points_valley[k    ][N - k - 1][0] << points_valley[k    ][N - k - 1][1] << points_valley[k    ][N - k - 1][2];
      gamut_vertices << points_valley[k + 1][N - k - 2][0] << points_valley[k + 1][N - k - 2][1] << points_valley[k + 1][N - k - 2][2];
      gamut_vertices << points_hill[N - k][0][0]           << points_hill[N - k][0][1]           << points_hill[N - k][0][2];

      gamut_vertices << points_valley[k + 1][N - k - 2][0] << points_valley[k + 1][N - k - 2][1] << points_valley[k + 1][N - k - 2][2];
      gamut_vertices << points_hill[N - k][0][0]           << points_hill[N - k][0][1]           << points_hill[N - k][0][2];
      gamut_vertices << points_hill[N - k - 1][0][0]       << points_hill[N - k - 1][0][1]       << points_hill[N - k - 1][0][2];
    }
  }

  m_vao.bind();
  m_vbo.bind();
  m_vbo.allocate(gamut_vertices.data(), gamut_vertices.size() * sizeof(float));
  m_vbo.release();
  m_vao.release();
}

void GraphGamutObject::setObserver(int observer) {
  m_observer = observer;
  genData();
}

void GraphGamutObject::setWorkingSpace(int space) {
  const float AdobeRGB[] = {
     2.0413690, -0.5649464, -0.3446944,
    -0.9692660,  1.8760108,  0.0415560,
     0.0134474, -0.1183897,  1.0154096,
  };

  const float CIERGB[] = {
     2.3706743, -0.9000405, -0.4706338,
    -0.5138850,  1.4253036,  0.0885814,
     0.0052982, -0.0146949,  1.0093968,
  };

  const float sRGB[] = {
     3.2404542, -1.5371385, -0.4985314,
    -0.9692660,  1.8760108,  0.0415560,
     0.0556434, -0.2040259,  1.0572252,
  };

  switch(space) {
  case 0:
    m_colorMatrix = QMatrix3x3(sRGB);
    break;

  case 1:
    m_colorMatrix = QMatrix3x3(AdobeRGB);
    break;

  case 2:
    m_colorMatrix = QMatrix3x3(CIERGB);
    break;

  default:
    break;
  };
}

void GraphGamutObject::setGamma(float gamma) {
  m_gamma = gamma;
}

void GraphGamutObject::setIlluminant(int illuminant) {
  m_illuminant = illuminant;
  genData();
}

void GraphGamutObject::setAxes(int axes) {
  m_axes = axes;
  genData();
}

void GraphGamutObject::setMinLambda(int lambda) {
  m_min_lambda = lambda;
  genData();
}

void GraphGamutObject::setMaxLambda(int lambda) {
  m_max_lambda = lambda;
  genData();
}
