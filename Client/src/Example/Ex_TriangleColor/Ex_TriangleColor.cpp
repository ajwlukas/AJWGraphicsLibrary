#include "Ex_TriangleColor.h"

void Ex_TriangleColor::Init()
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
    }color{1,0,1,1};

    constantBuffer = TL_Graphics::RenderSystem::Get()->CreateConstantBuffer(0, &color, sizeof(Color));
}

void Ex_TriangleColor::UnInit()
{
    TL_Graphics::RenderSystem::Delete();
}

void Ex_TriangleColor::Update()
{
    TL_Graphics::RenderSystem::Get()->Clear();

    material->Set();

    mesh->Set();

    constantBuffer->Set();

    TL_Graphics::RenderSystem::Get()->Draw();

    TL_Graphics::RenderSystem::Get()->Present();
}
