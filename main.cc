#include "window.h"

#include <QApplication>
#include <QSurfaceFormat>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  QSurfaceFormat fmt;
  fmt.setDepthBufferSize(24);
  fmt.setSamples(4);
  QSurfaceFormat::setDefaultFormat(fmt);

  Window window {};
  window.show();

  return app.exec();
}
