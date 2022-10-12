#include "pch_dx_11.h"
#include "Box.h"

Box::Box()
{
	name = "Box";

    RESOURCES->rasterStates->GetWireMode(wireFrame);
    RESOURCES->rasterStates->GetDefault(defaultRasterizerState);

	Create();
}

Box::~Box()
{
}

void Box::Update()
{
	__super::Update();
}

void Box::Render()
{
    __super::SetPipeLine();

    DC->RSSetState(wireFrame);

	__super::Draw();

    DC->RSSetState(defaultRasterizerState);
}

void Box::Create()
{
    VertexSet vertexSet;

    vertexSet.AddElementToDesc(sizeof(float) * 3, DataType::FLOAT, "POSITION");

    float3 position[8] = {
        //¾Õ¸é
    float3(-0.5f,        +0.5f,      -0.5f),
    float3(+0.5f,        +0.5f,      -0.5f),
    float3(-0.5f,        -0.5f,      -0.5f),
    float3(+0.5f,        -0.5f,      -0.5f),

    //µÞ¸é
    float3(-0.5f,         +0.5f,     +0.5f),
    float3(+0.5f,         +0.5f,     +0.5f),
    float3(-0.5f,         -0.5f,     +0.5f),
    float3(+0.5f,         -0.5f,     +0.5f)
    };

    vertexSet.AddData(position, sizeof(position));

    vector<UINT> indices =
    {
        //front
        0,1,2,
        1,3,2,
        //back
        5,4,7,
        4,6,7,

        //up
        4,5,0,
        5,1,0,
        //down
        2,3,6,
        3,7,6,

        //left
        4,0,6,
        0,2,6,
        //right
        1,5,3,
        5,7,3
    };

    mesh = new Mesh(vertexSet, indices.data(), indices.size(), L"PosVS_Instanced.hlsl");

    MaterialDesc matDesc;
    matDesc.pixelShaderName = L"PosPS.hlsl";
    material = new Material(matDesc);
}
