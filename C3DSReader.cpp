#include "C3DSReader.h"

C3DSReader::C3DSReader()
{
    vn = fn = 0;
    v = nullptr;
    n = nullptr;
    t = nullptr;
    f = nullptr;
}

void C3DSReader::CalculateNormals()
{
    struct nbuf_data
    {
        vec3 v;
        vec3 n;
    };
    nbuf_data *nbuf = new nbuf_data[vn];
    nbuf_data **vptr = new nbuf_data*[vn];

    int id = 0;
    float min_d = 1E-16;
    for(int i = 0; i < vn; i++)
    {
        bool added = false;
        for(int j = 0; j < id; j++)
        {
            if((nbuf[j].v[0] - v[i][0]) * (nbuf[j].v[0] - v[i][0]) +
                    (nbuf[j].v[1] - v[i][1]) * (nbuf[j].v[1] - v[i][1]) +
                    (nbuf[j].v[2] - v[i][2]) * (nbuf[j].v[2] - v[i][2]) < min_d)
            {
                vptr[i] = &nbuf[j];
                added = true;
                break;
            }
        }
        if(!added)
        {
            vptr[i] = &nbuf[id];
            nbuf[id].v[0] = v[i][0];
            nbuf[id].v[1] = v[i][1];
            nbuf[id].v[2] = v[i][2];
            nbuf[id].n[0] = nbuf[id].n[1] = nbuf[id].n[2] = 0.0f;
            id++;
        }
    }

    n = new vec3[vn];
    vec3 v1, v2, fn;
    for(int i = 0; i < this->fn; i++)
    {
        v1[0] = v[f[i][1]][0] - v[f[i][0]][0];
        v1[1] = v[f[i][1]][1] - v[f[i][0]][1];
        v1[2] = v[f[i][1]][2] - v[f[i][0]][2];

        v2[0] = v[f[i][2]][0] - v[f[i][0]][0];
        v2[1] = v[f[i][2]][1] - v[f[i][0]][1];
        v2[2] = v[f[i][2]][2] - v[f[i][0]][2];

        cross(v1, v2, fn);
        normalize(fn);

        for(int k = 0; k < 3; k++)
        {
            vptr[f[i][0]]->n[k] += fn[k];
            vptr[f[i][1]]->n[k] += fn[k];
            vptr[f[i][2]]->n[k] += fn[k];
        }
    }
    for(int i = 0; i < id; i++)
        normalize(nbuf[i].n);
    for(int i = 0; i < vn; i++)
    {
        n[i][0] = vptr[i]->n[0];
        n[i][1] = vptr[i]->n[1];
        n[i][2] = vptr[i]->n[2];
    }

    delete[] nbuf;
    delete[] vptr;
}

void C3DSReader::ReadVerts(FILE *file)
{
    fseek(file, 4, SEEK_CUR);
    fread(&vn, 2, 1, file);
    v = new vec3[vn];
    fread(v, sizeof(vec3) * vn, 1, file);
}

void C3DSReader::ReadFaces(FILE *file)
{
    fseek(file, 4, SEEK_CUR);
    fread(&fn, 2, 1, file);
    f = new vec3us[fn];
    for(int i = 0; i < fn; i++)
    {
        fread(f[i], sizeof(vec3us), 1, file);
        fseek(file, 2, SEEK_CUR);
    }
}

void C3DSReader::ReadTexCoords(FILE *file)
{
    fseek(file, 4, SEEK_CUR);
    fread(&vn, 2, 1, file);
    t = new vec2[vn];
    fread(t, sizeof(vec2) * vn, 1, file);
}

void C3DSReader::ZeroTexCoords()
{
    t = new vec2[vn];
    memset(t, 0, sizeof(vec2) * vn);
}

bool C3DSReader::FindBlock(FILE *file, unsigned short block_id, unsigned int ss)
{
    unsigned short cur_id;
    unsigned int cur_len;
    unsigned int cur_pos = ftell(file);
    while(ss >= 6)
    {
        fread(&cur_id, 2, 1, file);
        if(cur_id == block_id)
            return true;
        fread(&cur_len, 4, 1, file);
        ss -= cur_len;
        fseek(file, cur_len - 6, SEEK_CUR);
    }
    fseek(file, cur_pos, SEEK_SET);
    return false;
}

void C3DSReader::ReadModelName(FILE *file)
{
    int id = 0;
    do
    {
        fread(&model_name[id], 1, 1, file);
        id++;
    }
    while(model_name[id - 1] != 0);
}

bool C3DSReader::Load(const char *filename)
{
    Free();
    FILE *F = fopen(filename, "rb");
    if(!F)
        return false;
    unsigned int len;
    unsigned short bid;
    fread(&bid, 2, 1, F);
    if(bid != 0x4d4d)
        return false;
    fread(&len, 4, 1, F);
    if(!FindBlock(F, 0x3d3d, len - 6))
        return false;
    fread(&len, 4, 1, F);
    if(!FindBlock(F, 0x4000, len - 6))
        return false;
    fread(&len, 4, 1, F);
    ReadModelName(F);
    if(!FindBlock(F, 0x4100, len - 6))
        return false;
    fread(&len, 4, 1, F);
    unsigned int model_pos = ftell(F);
    if(!FindBlock(F, 0x4110, len - 6))
        return false;
    ReadVerts(F);
    fseek(F, model_pos, SEEK_SET);
    if(!FindBlock(F, 0x4140, len - 6))
        ZeroTexCoords();
    ReadTexCoords(F);
    fseek(F, model_pos, SEEK_SET);
    if(!FindBlock(F, 0x4120, len - 6))
        return false;
    ReadFaces(F);
    fclose(F);

    CalculateNormals();

    mesh_data.vertexN = vn;
    mesh_data.facesN = fn;
    mesh_data.verts = v;
    mesh_data.normals = n;
    mesh_data.tex_coords = t;
    mesh_data.faces = f;

    vn = 0;
    fn = 0;
    v = nullptr;
    n = nullptr;
    t = nullptr;
    f = nullptr;

    return true;
}

void C3DSReader::Free()
{
    vn = 0;
    fn = 0;
    delete[] v;
    delete[] n;
    delete[] f;
    delete[] t;
    v = nullptr;
    n = nullptr;
    t = nullptr;
    f = nullptr;
}

C3DSReader::~C3DSReader()
{
    Free();
}
