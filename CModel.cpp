#include "CModel.h"

CModel::CModel()
{

}

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
    mesh_data = reader->MeshData();
}

void CModel::Draw()
{
    if(is_avalible)
        mesh_data.Draw();
}
