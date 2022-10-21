#include "pch_dx_11.h"
#include "Grid.h"

Grid::Grid(Camera* camera)
	:cam(camera)
{
	CreateGrid();

    //transform.parent = &camera->transform;

    
    //transform.relateR = false;
    //transform.relateS = false;
}

void Grid::Update()
{
    ////followCamera
    transform.pos.x = cam->transform.worldPos.x;
    transform.pos.z = cam->transform.worldPos.z;
    //transform.pos.y = cam->transform.pos.y - 10;
    transform.UpdateWorld();
}

void Grid::Render()
{
    __super::Render();
}

void Grid::CreateGrid()
{
    name = "SkyBox";

    VertexSet vertexSet;

    vertexSet.AddElementToDesc(sizeof(float) * 3, DataType::FLOAT, "POSITION");

    float3 position[4] = {
    float3(-1,        0,      -1),
    float3(+1,        0,      -1),
    float3(-1,        0,      +1),
    float3(+1,        0,      +1)
    };

    vertexSet.AddData(position, sizeof(position));

    vector<UINT> indices =
    {
        0,2,1,
        2,3,1
    };

    mesh = new Mesh(vertexSet, indices.data(), indices.size(), L"GridVS.hlsl");

    MaterialDesc matDesc;
    matDesc.pixelShaderName = L"GridPS.hlsl";

    material = new Material(matDesc);

    transform.scale = { 100,1,100 };
}
