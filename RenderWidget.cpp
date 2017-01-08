#include "RenderWidget.h"

RenderWidget::RenderWidget(QWidget *parent)
    : QGLWidget(parent)
{
}

RenderWidget::~RenderWidget()
{

}

void RenderWidget::initializeGL()
{
    glClearColor(0.7,0.7,1.0,1.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
}

void RenderWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0f,(float)w/(float)h,0.5f,1000.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void RenderWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
}
