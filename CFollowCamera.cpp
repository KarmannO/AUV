#include "CFollowCamera.h"

CFollowCamera::CFollowCamera()
{
    zero_target[0] = 0.0;
    zero_target[1] = 0.0;
    zero_target[2] = 0.0;
    dist = 5.0;
    zAngle = 0.0;
    xyAngle = 25.0;
    target = zero_target;
    CFollowCamera::ComputeVectors();
}

void CFollowCamera::ComputeVectors()
{
    d[0] = angCosf(rZ) * angCosf(rXY);
    d[1] = angSinf(rZ) * angCosf(rXY);
    d[2] = angSinf(rXY);

    p[0] = -d[0] * dist + target[0];
    p[1] = -d[1] * dist + target[1];
    p[2] = -d[2] * dist + target[2];

    u[0] = -angCosf(rZ) * angSinf(rXY);
    u[1] = -angSinf(rZ) * angSinf(rXY);
    u[2] = angCosf(rXY);

    cross(d, u, s);
}

void CFollowCamera::Move(float dx)
{
    dist -= dx;
    if(dist > 100.0)
        dist = 100.0;
    if(dist < 1.0)
        dist = 1.0;
    ComputeVectors();
}

void CFollowCamera::SetTarget(double *t)
{
    if(!t)
        target = zero_target;
    else
        target = t;
}

