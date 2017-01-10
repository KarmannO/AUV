#include "RenderWidget.h"

RenderWidget::RenderWidget(QWidget *parent)
    : QGLWidget(parent)
{
    setFocusPolicy(Qt::StrongFocus);
    setMouseTracking(true);

    timer = new CTimer(this);

    simulate = false;
    current_camera = &global_cam;
}

RenderWidget::~RenderWidget()
{
    timer->Kill();
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

    timer->Start();
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
    current_camera->SetView();

    paintGrid();
}

void RenderWidget::paintGrid()
{
    glLineWidth(1.0f);
    glColor3f(1.0,0.874,0.568);

   glBegin(GL_LINES);
   for(int i=-500; i<=500; i++)
   {
       glVertex3f((float)i,-500.0f,0.01);
       glVertex3f((float)i, 500.0f,0.01);
       glVertex3f(-500.0f,(float)i, 0.01);
       glVertex3f( 500.0f,(float)i, 0.01);
   }
   glEnd();
}

void RenderWidget::mouseMoveEvent(QMouseEvent *event)
{
    int x = event->x();
    int y = event->y();
    if(control_state.old_mx != -100 && control_state.old_my != -100)
    {
        float dx = (float)(x - control_state.old_mx);
        float dy = (float)(y - control_state.old_my);
        if(control_state.lm_btn)
        {
            current_camera->RotZ(180.0f * dx / (float)width());
            current_camera->RotXY(180.0f * dy / (float)height());
        }
    }
    control_state.old_mx = x;
    control_state.old_my = y;
}

void RenderWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
        control_state.lm_btn = true;
    if(event->button() == Qt::RightButton)
        control_state.rm_btn = true;
}

void RenderWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
        control_state.lm_btn = false;
    if(event->button() == Qt::RightButton)
        control_state.rm_btn = false;
}

void RenderWidget::wheelEvent(QWheelEvent *event)
{
    float dang = (float)event->angleDelta().y() / 8.0f;
    current_camera->Move(dang / 30.0f);
}

void RenderWidget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Left)
        control_state.left_btn = true;
    if(event->key() == Qt::Key_Right)
        control_state.right_btn = true;
    if(event->key() == Qt::Key_Up)
        control_state.up_btn = true;
    if(event->key() == Qt::Key_Down)
        control_state.down_btn = true;
    if(event->key() == Qt::Key_Z)
        control_state.z_btn = true;
    if(event->key() == Qt::Key_X)
        control_state.x_btn = true;

    if(event->key() == Qt::Key_Space)
        simulate = false;
    if(event->key()==Qt::Key_C)
    {
        // Change camera.
    }
}

void RenderWidget::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Left)
        control_state.left_btn = false;
    if(event->key() == Qt::Key_Right)
        control_state.right_btn = false;
    if(event->key() == Qt::Key_Up)
        control_state.up_btn = false;
    if(event->key() == Qt::Key_Down)
        control_state.down_btn = false;
    if(event->key() == Qt::Key_Z)
        control_state.z_btn = false;
    if(event->key() == Qt::Key_X)
        control_state.x_btn = false;
}

void RenderWidget::timerEvent(QTimerEvent *event)
{
    if(simulate)
    {

    }
    updateGL();
}
