#include "CMeshData.h"

CMeshData::CMeshData()
{
    vertexN = 0;
    facesN = 0;
    verts = nullptr;
    normals = nullptr;
    tex_coords = nullptr;
    faces = nullptr;
}

void CMeshData::Copy(const CMeshData &mesh_data)
{
    vertexN = mesh_data.vertexN;
    facesN = mesh_data.facesN;
    verts = new vec3[vertexN];
    tex_coords = new vec2[vertexN];
    normals = new vec3[vertexN];
    faces = new vec3us[facesN];
    memcpy(verts, mesh_data.verts, sizeof(vec3) * vertexN);
    memcpy(normals, mesh_data.normals, sizeof(vec3) * vertexN);
    memcpy(tex_coords, mesh_data.tex_coords, sizeof(vec2) * vertexN);
    memcpy(faces, mesh_data.faces, sizeof(vec3us) * facesN);
}

CMeshData::CMeshData(const CMeshData &mesh_data)
{
    Copy(mesh_data);
}

CMeshData &CMeshData::operator=(const CMeshData &mesh_data)
{
    if(this == &mesh_data)
        return *this;
    Free();
    Copy(mesh_data);
    return *this;
}

void CMeshData::Free()
{
    delete[] verts;
    delete[] normals;
    delete[] tex_coords;
    delete[] faces;
    vertexN = 0;
    facesN = 0;
    verts = nullptr;
    normals = nullptr;
    tex_coords = nullptr;
    faces = nullptr;
}

void CMeshData::Draw()
{
    glBegin(GL_TRIANGLES);
        for(int i = 0; i < facesN; i++)
        {
            glTexCoord2fv(tex_coords[faces[i][0]]);
            glNormal3fv(normals[faces[i][0]]);
            glVertex3fv(verts[faces[i][0]]);

            glTexCoord2fv(tex_coords[faces[i][1]]);
            glNormal3fv(normals[faces[i][1]]);
            glVertex3fv(verts[faces[i][1]]);

            glTexCoord2fv(tex_coords[faces[i][2]]);
            glNormal3fv(normals[faces[i][2]]);
            glVertex3fv(verts[faces[i][2]]);
        }
}

CMeshData::~CMeshData()
{
    Free();
}
