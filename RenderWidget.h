#ifndef RENDERWIDGET_H
#define RENDERWIDGET_H
#include <QGLWidget>
#include <GL/glu.h>

class RenderWidget : public QGLWidget
{
    Q_OBJECT

public:
    RenderWidget(QWidget *parent = 0);
    ~RenderWidget();

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
};

#endif // RENDERWIDGET_H
