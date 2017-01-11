#ifndef PHYSMATRIXOPERATIONS
#define PHYSMATRIXOPERATIONS

#include "Vectors.h"
#include "math.h"

void BuildTransformMatrix(double x, double y, double z, double b, double d, double c, mat3_4d M);
void BuildTransformMatrix2(double x, double y, double z, double b, double d, double c, mat3_4d M);
void BuildTransformMatrix3(double x, double y, double z, double b, double d, double c, mat3_4d M);

void RotationMatrixFromAxis(vec3d r, mat3d R);
void RotationMatrixFromAxisAngle(double a, vec3d u, mat3d R);
void MultiQuaternions(vec4d a, vec4d b, vec3d res);
void NormalizeQuaternion(vec4d q);
void GetNormalizedQuaternion(vec4d q, vec4d rq);
void AxisToQuaternion(vec3d u, double a, vec4d q);
void AxisToQuaternion(vec3d axis, vec4d q);
void AxisFromQuaternion(vec4d q, vec3d axis);
void MatrixToQuaternion(mat3d M, vec4d q);
void MatrixFromQuaternion(vec4d q, mat3d M);

void CrossSkewSymm(vec3d a, mat3d SM);
void CrossSkewSymm_minus(vec3d a, mat3d SM);

void MultiMatrix(const mat4d M1, const mat4d M2, mat4d R);
void MatTranspose(const mat4d M, mat4d MT);



#endif // PHYSMATRIXOPERATIONS

