#include "Ex_BoxCamera.h"

Ex_BoxCamera::Ex_BoxCamera()
{
    TL_Graphics::RenderSystem::Create();
    TL_Graphics::RenderSystem::Get()->Init();

    struct Vertex
    {
        float position[2];
    }
    vertices[3]
    {
        {0.0f, 0.5f}
        ,{-0.5f, -0.5f}
        ,{0.5f, -0.5f}
    };
    vertexAttribute.AddElementToDesc(sizeof(float) * 2, TL_Graphics::DataType::FLOAT, "POSITION");
    vertexAttribute.AddData(vertices, sizeof(vertices));
    UINT indicies[]
        =
    {
        0,2,1
    };

    mesh = TL_Graphics::RenderSystem::Get()->CreateMesh(vertexAttribute, indicies, 3, L"TriangleColorVS.hlsl");

    material = TL_Graphics::RenderSystem::Get()->CreateMaterial(L"TriangleColorPS.hlsl");

    struct Color
    {
        float rgba[4];
    }color{ 1,0,1,1 };

    constantBuffer = TL_Graphics::RenderSystem::Get()->CreateConstantBuffer(0, &color, sizeof(Color));
}

Ex_BoxCamera::~Ex_BoxCamera()
{
}

void Ex_BoxCamera::Init()
{
}

void Ex_BoxCamera::UnInit()
{
}

void Ex_BoxCamera::Update()
{
}
