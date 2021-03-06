#ifndef CMESHDATA_H
#define CMESHDATA_H
#include <GL/gl.h>
#include "vectors.h"

class CMeshData
{
public:
    int vertexN;
    int facesN;
    vec3 *verts;
    vec3 *normals;
    vec2 *tex_coords;
    vec3us *faces;

    CMeshData();
    CMeshData(const CMeshData &mesh_data);
    ~CMeshData();

    void Draw();
    void Free();

    CMeshData &operator=(const CMeshData &mesh_data);

private:
    void Copy(const CMeshData &mesh_data);
};

#endif // CMESHDATA_H
