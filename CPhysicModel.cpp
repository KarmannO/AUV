#include "CPhysicModel.h"

CPhysicModel::CPhysicModel(C3DSReader *reader) : CModel(reader)
{

}

void CPhysicModel::SetPointData(CPhysicPoint &point_data, float w, vec3 p0, vec3 p1, vec3 p2)
{
    vec3d v1 = {(double)(p1[0] - p0[0]), (double)(p1[1] - p0[1]), (double)(p1[2] - p0[2])};
    vec3d v2 = {(double)(p2[0] - p0[0]), (double)(p2[1] - p0[1]), (double)(p2[2] - p0[2])};
    point_data.weight = w;
    cross(v1, v2, point_data.n0);
    point_data.S = length(point_data.n0);
    point_data.n0[0] /= point_data.S;
    point_data.n0[1] /= point_data.S;
    point_data.n0[2] /= point_data.S;
    point_data.S *= 0.5f;

    point_data.v0[0] = (double)(p0[0] + p1[0] + p2[0]) / 3.0;
    point_data.v0[1] = (double)(p0[1] + p1[1] + p2[1]) / 3.0;
    point_data.v0[2] = (double)(p0[2] + p1[2] + p2[2]) / 3.0;
}

void CPhysicModel::UpdatePoints()
{
    for(int i = 0; i < mesh_data.facesN; i++)
    {
        points[i].v[0] = points[i].v0[0];
        points[i].v[1] = points[i].v0[1];
        points[i].v[2] = points[i].v0[2];
        points[i].n[0] = points[i].n0[0];
        points[i].n[1] = points[i].n0[1];
        points[i].n[2] = points[i].n0[2];
    }

    CM[0] = 0.0;
    CM[1] = 0.0;
    CM[2] = 0.0;
    double W = 0.0;
    for(int i = 0; i < points_num; i++)
    {
        CM[0] += points[i].v[0] * points[i].weight;
        CM[1] += points[i].v[1] * points[i].weight;
        CM[2] += points[i].v[2] * points[i].weight;
        W += points[i].weight;
    }
    CM[0] /= W;
    CM[1] /= W;
    CM[2] /= W;

    for(int i = 0; i < points_num; i++)
    {
        points[i].v[0] -= CM[0];
        points[i].v[1] -= CM[1];
        points[i].v[2] -= CM[2];
    }

    physic_state.UpdatePointsInfo();
    physic_state.UpdateWeight();
}

void CPhysicModel::ComputeForces()
{
    for(int i = 0; i < points_num; i++)
    {
        points[i].F[0] = 0.0;
        points[i].F[1] = 0.0;
        points[i].F[2] = -9.8 * points[i].weight;
    }
}

void CPhysicModel::Update(float dt)
{
    UpdatePoints();
    ComputeForces();
    physic_state.ComputeForceAndTorque();
    physic_state.ComputeMotion(dt);
}

void CPhysicModel::SetWeight(float weight)
{
    this->weight = weight;
    this->points_num = mesh_data.facesN;
    this->points = new CPhysicPoint[points_num];

    float pw = this->weight / (float)mesh_data.facesN;

    for(int i = 0; i < mesh_data.facesN; i++)
    {
        SetPointData(points[i], pw, mesh_data.verts[mesh_data.faces[i][0]],
                mesh_data.verts[mesh_data.faces[i][1]],
                mesh_data.verts[mesh_data.faces[i][2]]);
    }

    UpdatePoints();
}
