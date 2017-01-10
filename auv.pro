#-------------------------------------------------
#
# Project created by QtCreator 2017-01-06T14:50:09
#
#-------------------------------------------------
CONFIG   += c++11
QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = auv
TEMPLATE = app


SOURCES += main.cpp\
        RenderWidget.cpp \
    CCamera.cpp \
    CFollowCamera.cpp \
    CControlButtonState.cpp \
    CTimer.cpp \
    ImageLoader.cpp \
    CBaseModel.cpp \
    CMeshData.cpp

HEADERS  += RenderWidget.h \
    CCamera.h \
    Vectors.h \
    CFollowCamera.h \
    CControlButtonState.h \
    CTimer.h \
    CBaseModel.h \
    CMeshData.h


win32: LIBS += -L$$PWD/./ -lFreeImage -lopengl32 -lGLU32

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.
