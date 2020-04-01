TEMPLATE = app
TARGET = Gamut

QT += 3dcore 3drender 3dinput 3dextras
QT += core gui widgets

CONFIG += c++2a

SOURCES += \
    chromadiagram.cc \
    cieobserver.cc \
    cievizualizer.cc \
    graphaxesobject.cc \
    graphgamutobject.cc \
    main.cc \
    window.cc

HEADERS += \
    chromadiagram.h \
    cieobserver.h \
    cievizualizer.h \
    graphaxesobject.h \
    graphgamutobject.h \
    window.h

FORMS += \
    window.ui

DISTFILES += \
  fragmentShaderAxes.fs \
  fragmentShaderGamut.fs \
  vertexShaderAxes.vs \
  vertexShaderGamut2D.vs \
  vertexShaderGamut3D.vs

RESOURCES += \
  Resources.qrc
