#ifndef CPHYSICMODEL_H
#define CPHYSICMODEL_H
#include "CModel.h"

class CPhysicModel: public CModel
{
protected:
    int points_num;
    CPhysicPoint *points;
    CPhysicState physic_state;
    float weight;

    vec3d CM;   // Current center of mass position.

    mat4d M;    // Shell transformation matrix.
    mat4d MT;   // Transposed shell transformation matrix.
public:
    CPhysicModel(C3DSReader *reader);

    void SetPointData(CPhysicPoint &point_data, float w, vec3 p0, vec3 p1, vec3 p2);
    void UpdatePoints();
    void ComputeForces();

    void Update(float dt);

    void SetWeight(float weight);
};

#endif // CPHYSICMODEL_H
