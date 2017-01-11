#ifndef CMODEL_H
#define CMODEL_H
#include <QDebug>
#include "C3DSReader.h"
#include "CMeshData.h"

class CModel
{
private:
    CMeshData mesh_data;
    C3DSReader *reader;

    bool is_avalible;
public:
    CModel(C3DSReader *reader);
    ~CModel();

    bool LoadFrom3DS(const char * filename);
    void Update(float dt);
    void Draw();
};

#endif // CMODEL_H
