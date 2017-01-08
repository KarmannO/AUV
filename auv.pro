#-------------------------------------------------
#
# Project created by QtCreator 2017-01-06T14:50:09
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = auv
TEMPLATE = app


SOURCES += main.cpp\
        RenderWidget.cpp \
    CCamera.cpp

HEADERS  += RenderWidget.h \
    CCamera.h \
    Vectors.h

LIBS += -lopengl32 -lGLU32
