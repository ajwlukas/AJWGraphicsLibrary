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
    vertexAttribute.AddElementToDesc(sizeof(float),DataType::FLOAT,"POSITION");
    vertexAttribute.AddData(vertices, sizeof(vertices));
    UINT indicies[]
        =
    {
        0,1,2
    };
    mesh = new Mesh(vertexAttribute, indicies, 3, L"Triangle.hlsl");

    //material = new Material();
    //material->SetShader(L"Triangle.hlsl");
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

    mesh->Set();

    //material->Set();

    RenderEngine::Get()->EndRender();
}
