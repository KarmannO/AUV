#include "CModel.h"

CModel::CModel(C3DSReader *reader)
{
    this->reader = reader;
    is_avalible = false;
}

CModel::~CModel()
{
    mesh_data.Free();
}

bool CModel::LoadFrom3DS(const char *filename)
{
    is_avalible = reader->Load(filename);
    qDebug() << "Is avalible: " << is_avalible;
    mesh_data = reader->MeshData();
}

void CModel::Update(float dt)
{

}

void CModel::Draw()
{
    if(is_avalible)
        mesh_data.Draw();
}
