#ifndef CFOLLOWCAMERA_H
#define CFOLLOWCAMERA_H
#include "CCamera.h"

class CFollowCamera: public CCamera
{
protected:
    vec3d zero_target;
    double *target;
    double dist;
    double zAngle;
    double xyAngle;

    void ComputeVectors();
public:
    CFollowCamera();
    void SetTarget(double *t);
    void Move(float dx);
};

#endif // CFOLLOWCAMERA_H
