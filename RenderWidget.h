#ifndef RENDERWIDGET_H
#define RENDERWIDGET_H
#include <QGLWidget>
#include <GL/glu.h>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QWheelEvent>
#include <QTimerEvent>

#include "CCamera.h"
#include "CTimer.h"
#include "CControlButtonState.h"
#include "C3DSReader.h"
#include "CModel.h"

class RenderWidget : public QGLWidget
{
    Q_OBJECT

    CControlButtonState control_state;
    CCamera *current_camera;
    CCamera global_cam;
    CTimer *timer;
    C3DSReader *reader;
    CModel *model;

    bool simulate;
public:
    RenderWidget(QWidget *parent = 0);
    ~RenderWidget();

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void paintGrid();

    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void wheelEvent(QWheelEvent *event);
    void timerEvent(QTimerEvent *event);
};

#endif // RENDERWIDGET_H
