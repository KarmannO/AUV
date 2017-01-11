#ifndef CPHYSICPOINT_H
#define CPHYSICPOINT_H
#include "vectors.h"

class CPhysicPoint
{
public:
    vec3d v;    // Point position in local coordinate system with center in mass center.
    vec3d v0;   // Point position in graphic model coordinate system.
    vec3d n;    // Normal.
    vec3d n0;   // Normal in graphic model space.
    double weight;  // Mass.
    double S;       // Point "area".

    vec3d x;    // Current position.
    vec3d N;    // Current normal.
    vec3d vel;  // Point velocity.
    vec3d F;    // Force applied to point.

    CPhysicPoint();
};

#endif // CPHYSICPOINT_H
