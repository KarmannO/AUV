#include "CTimer.h"

CTimer::CTimer(QWidget *w)
{
    timer_coef = 0.03f;
    timer_id = -1;
    timed_widget = w;
}

void CTimer::Start()
{
    timer_id = timed_widget->startTimer((int)(timer_coef * 1000.0f), Qt::PreciseTimer);
}

void CTimer::Kill()
{
    timed_widget->killTimer(timer_id);
}

float CTimer::getTimerCoef()
{
    return timer_coef;
}

int CTimer::getTimerId()
{
    return timer_id;
}
