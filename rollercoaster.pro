#-------------------------------------------------
#
# Project created by QtCreator 2011-12-01T15:39:20
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = rollercoaster
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ui/Canvas3D.cpp \
    ui/SupportCanvas3D.cpp \
    camera/CamtransCamera.cpp \
    ui/Settings.cpp \
    scenegraph/Scene.cpp \
    scenegraph/OpenGLScene.cpp \
    math/CS123Vector.inl \
    math/CS123Matrix.inl \
    math/CS123Matrix.cpp \
    scenegraph/GameScene.cpp

HEADERS  += mainwindow.h \
    ui/Canvas3D.h \
    ui/SupportCanvas3D.h \
    camera/CamtransCamera.h \
    camera/Camera.h \
    ui/Settings.h \
    scenegraph/Scene.h \
    scenegraph/OpenGLScene.h \
    math/CS123Vector.h \
    math/CS123Matrix.h \
    math/CS123Algebra.h \
    scenegraph/GameScene.h

INCLUDEPATH += lib math camera scenegraph ui

FORMS    += mainwindow.ui
