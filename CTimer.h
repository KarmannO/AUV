#ifndef CTIMER_H
#define CTIMER_H
#include <QGLWidget>

class CTimer
{
private:
    float timer_coef;
    int timer_id;

    QWidget *timed_widget;
public:
    CTimer(QWidget *w);
    void Start();
    void Kill();

    float getTimerCoef();
    int getTimerId();
};

#endif // CTIMER_H
