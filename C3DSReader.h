#ifndef C3DSREADER_H
#define C3DSREADER_H
#include "CMeshData.h"
#include "stdio.h"
#include "string.h"

class C3DSReader
{
private:
    unsigned short vn;
    unsigned short fn;
    char model_name[255];
    vec3 *v;
    vec3 *n;
    vec2 *t;
    vec3us *f;
    CMeshData mesh_data;

    void ReadModelName(FILE *file);
    void ReadVerts(FILE *file);
    void ReadFaces(FILE *file);
    void ReadTexCoords(FILE *file);
    void ZeroTexCoords();
    void CalculateNormals();
    bool FindBlock(FILE *file, unsigned short block_id, unsigned int ss);
public:
    C3DSReader();

    bool Load(const char *filename);
    CMeshData &MeshData() { return mesh_data; }
    CMeshData *MeshDataPtr() { return &mesh_data; }
    void Free();

    ~C3DSReader();
};

#endif // C3DSREADER_H
