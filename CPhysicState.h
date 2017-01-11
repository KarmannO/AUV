#ifndef CPHYSICSTATE_H
#define CPHYSICSTATE_H
#include "CPhysicPoint.h"
#include "PhysicMatrixOperations.h"

class CPhysicState
{
public:
    // Discrete point properties.
    int points_num;
    CPhysicPoint *points;

    // Rigid body static properties.
    double weight;      // Mass.
    double inv_weight;  // Inverse mass.
    mat3d M;            // Mass vector.
    mat3d W;            // Inverse mass vector.
    mat3d Ibody;        // Inertia tensor in AUV part coordinate system.
    mat3d IbodyInv;     // Inverse inertia tensor in AUV part coordinate system.
    mat3d I;            // Inertia tensor.
    mat3d Iinv;         // Inverse inertia tensor.

    // Rigid body dynamic properties.
    mat3d R;            // Current rotation matrix.
    vec4d q;            // Current rotation quaternion.
    vec3d x;            // Center of mass position.
    vec3d r;            // Rotation axe.
    vec3d v;            // Velocity of center of mass.
    vec3d w;            // Angular velocity.
    vec3d P;            // Linear moment.
    vec3d L;            // Angular moment.

    vec3d F;            // Summary force applied to rigid body.
    vec3d T;            // Torque;

    CPhysicState();
    void ZeroState();
    void UpdateWeight();
    void ComputeTensors();
    void GetTransformMatrix(mat4d M);
    void GetTransformMatrixT(mat4d M);
    void VectorToObject(vec3d wv, vec3d ov);
    void VectorFromObject(vec3d ov, vec3d wv);
    void VelocityFromWC(vec3d wc, double *vel, double* local_pos = nullptr);
    void VelocityFromLC(vec3d lc, double *vel);
    void ZeroForces();
    void ComputeForceAndTorque();
    void ComputeMotion(double dt);
    void UpdatePointsInfo();
    void Move(double dx, double dy, double dz);
    void Rotate(double ang, double ux, double uy, double uz);
    void Rotate(double ang, double ux, double uy, double uz, vec3d rot_c);
    void GetState(vec3d sx, vec4d sq);
    void SetState(vec3d sx, vec4d sq);
};

#endif // CPHYSICSTATE_H
