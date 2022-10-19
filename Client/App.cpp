#include "App.h"

App::App()
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
    vertexAttribute.AddElementToDesc(sizeof(float) * 2, TL_Graphics::DataType::FLOAT,"POSITION");
    vertexAttribute.AddData(vertices, sizeof(vertices));
    UINT indicies[]
        =
    {
        0,2,1
    };

    mesh = TL_Graphics::RenderSystem::Get()->CreateMesh(vertexAttribute, indicies, 3, L"Triangle.hlsl");

    material = TL_Graphics::RenderSystem::Get()->CreateMaterial();
}

App::~App()
{
     TL_Graphics::RenderSystem::Delete();
}

void App::Update()
{
    TL_Graphics::RenderSystem::Get()->Clear();

    material->Set();

    mesh->Set();

    TL_Graphics::RenderSystem::Get()->Draw();

    TL_Graphics::RenderSystem::Get()->Present();
}
