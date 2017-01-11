#include "CPhysicState.h"

CPhysicState::CPhysicState()
{
    points_num = 0;
    points = nullptr;
    ZeroState();
}

void CPhysicState::ZeroState()
{
    x[0] = 0.0;
    x[1] = 0.0;
    x[2] = 0.0;
    r[0] = 0.0;
    r[1] = 0.0;
    r[2] = 0.0;
    AxisToQuaternion(r, q);
    MatrixFromQuaternion(q, R);
    v[0] = 0.0;
    v[1] = 0.0;
    v[2] = 0.0;
    w[0] = 0.0;
    w[1] = 0.0;
    w[2] = 0.0;
    P[0] = 0.0;
    P[1] = 0.0;
    P[2] = 0.0;
    L[0] = 0.0;
    L[1] = 0.0;
    L[2] = 0.0;
    UpdatePointsInfo();
}

void CPhysicState::UpdateWeight()
{
    weight = 0.0f;
    for(int i = 0; i < points_num; i++)
        weight += points[i].weight;
    inv_weight = 1 / weight;

    memset(M, 0, sizeof(mat3d));
    memset(W, 0, sizeof(mat3d));

    for(int i = 0; i < 3; i++)
    {
        M[i][i] = weight;
        W[i][i] = inv_weight;
    }

    memset(Ibody, 0, sizeof(mat3d));
    mat3d E = {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}};
    mat3d mbuf;
    double kd;

    for(int i = 0; i < points_num; i++)
    {
        kd = dot(points[i].v, points[i].v);
        mbuf[0][0] = points[i].v[0] * points[i].v[0]; mbuf[0][1] = points[i].v[0] * points[i].v[1]; mbuf[0][2] = points[i].v[0] * points[i].v[2];
        mbuf[1][0] = points[i].v[1] * points[i].v[0]; mbuf[1][1] = points[i].v[1] * points[i].v[1]; mbuf[1][2] = points[i].v[1] * points[i].v[2];
        mbuf[2][0] = points[i].v[2] * points[i].v[0]; mbuf[2][1] = points[i].v[2] * points[i].v[1]; mbuf[2][2] = points[i].v[2] * points[i].v[2];
        for(int k = 0; k < 3; k++)
            for(int j = 0; j < 3; j++)
                Ibody[k][j] += points[i].weight * (E[k][j] * kd - mbuf[k][j]);
    }
    MatInverse(Ibody, IbodyInv);
    ComputeTensors();
}

void CPhysicState::ComputeTensors()
{
    mat3d buf;
    MultiMatrix(R, Ibody, buf);
    mat3d RT;
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            RT[i][j] = R[j][i];
    MultiMatrix(R, IbodyInv, buf);
    MultiMatrix(buf, RT, Iinv);
}

void CPhysicState::GetTransformMatrix(mat4d M)
{
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            M[i][j] = R[i][j];
    M[0][3] = x[0];
    M[1][3] = x[1];
    M[2][3] = x[2];
    M[3][0] = 0.0;
    M[3][1] = 0.0;
    M[3][2] = 0.0;
    M[3][3] = 1.0;
}

void CPhysicState::GetTransformMatrixT(mat4d M)
{
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            M[i][j] = R[j][i];
    M[3][0] = x[0];
    M[3][1] = x[1];
    M[3][2] = x[2];
    M[3][0] = 0.0;
    M[1][3] = 0.0;
    M[2][3] = 0.0;
    M[3][3] = 1.0;
}

void CPhysicState::VectorToObject(vec3d wv, vec3d ov)
{
    mat3d RT;
    vec3d TT;
    MatTranspose(R, RT);
    MultiVector(RT, x, TT);

    for(int i = 0; i < 3; i++)
        ov[i] = RT[i][0] * wv[0] + RT[i][1] * wv[1] + RT[i][2] * wv[2] - TT[i];
}

void CPhysicState::VectorFromObject(vec3d ov, vec3d wv)
{
    vec3d buf;
    MultiVector(R, ov, buf);
    wv[0] = buf[0] + x[0];
    wv[1] = buf[1] + x[1];
    wv[2] = buf[2] + x[2];
}

void CPhysicState::VelocityFromWC(vec3d wc, double *vel, double *local_pos)
{
    vec3d lc;
    VectorToObject(wc, lc);
    if(local_pos)
    {
        local_pos[0] = lc[0];
        local_pos[1] = lc[1];
        local_pos[2] = lc[2];
    }
    vec3d pr;
    MultiVector(R, lc, pr);
    vec3d pv;
    cross(w, pr, pv);
    vel[0] = pv[0] + v[0];
    vel[1] = pv[1] + v[1];
    vel[2] = pv[2] + v[2];
}

void CPhysicState::VelocityFromLC(vec3d lc, double *vel)
{
    vec3d pr;
    MultiVector(R, lc, pr);
    vec3d pv;
    cross(w, pr, pv);
    vel[0] = pv[0] + v[0];
    vel[1] = pv[1] + v[1];
    vel[2] = pv[2] + v[2];
}

void CPhysicState::ZeroForces()
{
    for(int i = 0; i < 3; i++)
    {
        F[i] = 0.0;
        T[i] = 0.0;
    }
}

void CPhysicState::ComputeForceAndTorque()
{
    vec3d arm;
    ZeroForces();
    vec3d torq;

    for(int i = 0; i < points_num; i++)
    {
        arm[0] = points[i].x[0] - x[0];
        arm[1] = points[i].x[1] - x[1];
        arm[2] = points[i].x[2] - x[2];
        cross(arm, points[i].F, torq);
        T[0] += torq[0];
        T[1] += torq[1];
        T[2] += torq[2];
        F[0] += points[i].F[0];
        F[1] += points[i].F[1];
        F[2] += points[i].F[2];
    }
}

void CPhysicState::ComputeMotion(double dt)
{
    P[0] += dt * F[0];
    P[1] += dt * F[1];
    P[2] += dt * F[2];

    L[0] += dt * T[0];
    L[1] += dt * T[1];
    L[2] += dt * T[2];

    v[0] = P[0] * W[0][0];
    v[1] = P[1] * W[1][1];
    v[2] = P[2] * W[2][2];

    MultiVector(Iinv, L, w);

    x[0] += v[0] * dt;
    x[1] += v[1] * dt;
    x[2] += v[2] * dt;

    vec4d dq;
    vec4d wq;
    wq[0] = w[0];
    wq[1] = w[1];
    wq[2] = w[2];
    wq[3] = 0.0;
    MultiQuaternions(wq, q, dq);
    q[0] = 0.5 * dq[0] * dt;
    q[1] = 0.5 * dq[1] * dt;
    q[2] = 0.5 * dq[2] * dt;
    q[3] = 0.5 * dq[3] * dt;
    NormalizeQuaternion(q);
    AxisFromQuaternion(q, r);
    MatrixFromQuaternion(q, R);

    ComputeTensors();
    UpdatePointsInfo();
}

void CPhysicState::UpdatePointsInfo()
{
    vec3d pr;
    for(int i = 0; i < points_num; i++)
    {
        MultiVector(R, points[i].n, points[i].N);
        MultiVector(R, points[i].v, pr);
        points[i].x[0] = pr[0] + x[0];
        points[i].x[1] = pr[1] + x[1];
        points[i].x[2] = pr[2] + x[2];
        cross(w, pr, points[i].vel);
        points[i].vel[0] += v[0];
        points[i].vel[1] += v[1];
        points[i].vel[2] += v[2];
    }
}

void CPhysicState::Move(double dx, double dy, double dz)
{
    x[0] += dx;
    x[1] += dy;
    x[2] += dz;
    UpdatePointsInfo();
}

void CPhysicState::Rotate(double ang, double ux, double uy, double uz)
{
    mat3d dR;
    vec3d u;
    u[0] = ux;
    u[1] = uy;
    u[2] = uz;

    RotationMatrixFromAxisAngle(ang, u, dR);
    mat3d curR;
    CopyMatrix(curR, R);
    MultiMatrix(dR, curR, R);
    MatrixToQuaternion(R, q);
    AxisFromQuaternion(q, r);
    UpdatePointsInfo();
}

void CPhysicState::Rotate(double ang, double ux, double uy, double uz, vec3d rot_c)
{
    vec3d TV = {rot_c[0] - x[0], rot_c[1] - x[1], rot_c[2] - x[2]};
    mat3d dR;
    vec3d u;
    u[0] = ux;
    u[1] = uy;
    u[2] = uz;

    RotationMatrixFromAxisAngle(ang, u, dR);
    vec3d RTV;
    MultiVector(dR, TV, RTV);

    mat3d curR;
    CopyMatrix(curR, R);
    MultiMatrix(dR, curR, R);
    MatrixToQuaternion(R, q);
    AxisFromQuaternion(q, r);

    x[0] = x[0] + TV[0] - RTV[0];
    x[1] = x[1] + TV[1] - RTV[1];
    x[2] = x[2] + TV[2] - RTV[2];

    UpdatePointsInfo();
}

void CPhysicState::GetState(vec3d sx, vec4d sq)
{
    sx[0] = x[0];
    sx[1] = x[1];
    sx[2] = x[2];
    sq[0] = q[0];
    sq[1] = q[1];
    sq[2] = q[2];
    sq[3] = q[3];
}

void CPhysicState::SetState(vec3d sx, vec4d sq)
{
    x[0] = sx[0];
    x[1] = sx[1];
    x[2] = sx[2];
    q[0] = sq[0];
    q[1] = sq[1];
    q[2] = sq[2];
    q[3] = sq[3];

    MatrixFromQuaternion(q, R);
    AxisFromQuaternion(q, r);

    UpdatePointsInfo();
}














