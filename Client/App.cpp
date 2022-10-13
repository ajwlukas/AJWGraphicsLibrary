#include "App.h"

App::App()
{
    RenderEngine::Create();
    HRESULT hr = RenderEngine::Get()->Init();

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
    vertexAttribute.AddElementToDesc(sizeof(float) * 2,DataType::FLOAT,"POSITION");
    vertexAttribute.AddData(vertices, sizeof(vertices));
    UINT indicies[]
        =
    {
        0,2,1
    };
    mesh = new Mesh(vertexAttribute, indicies, 3, L"Triangle.hlsl");

    material = new Material();
    material->SetShader(L"Triangle.hlsl");
}

App::~App()
{
    {
        RenderEngine::Delete();
    }
}

void App::Update()
{
    RenderEngine::Get()->BeginRenderT();

    material->Set();

    mesh->Set();

    RenderEngine::Get()->EndRender();
}
