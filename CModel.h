#ifndef CMODEL_H
#define CMODEL_H
#include <QDebug>
#include "C3DSReader.h"
#include "CMeshData.h"
#include "CPhysicState.h"

class CModel
{
protected:
    CMeshData mesh_data;
    C3DSReader *reader;
    CPhysicState physic_state;
    bool is_avalible;

public:
    CModel();
    CModel(C3DSReader *reader);
    ~CModel();

    bool LoadFrom3DS(const char * filename);
    virtual void Update(float dt) = 0;
    void Draw();
};

#endif // CMODEL_H
