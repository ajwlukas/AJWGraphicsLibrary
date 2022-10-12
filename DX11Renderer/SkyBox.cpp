#include "pch_dx_11.h"
#include "Skybox.h"


Skybox::Skybox(Camera* camera)
    : cam(camera), rasterizerState{}
{
    CreateSkyBox();
    CreateRasterState();
    CreateDepthStencilState();


    /*transform.parent = &camera->transform;
    transform.relateR = false;
    transform.relateS = false;*/
}

void Skybox::Update()
{
    //followCamera
    transform.pos = cam->transform.worldPos;
    transform.UpdateWorld();
}

void Skybox::Render()
{
    //customStates
    DC->RSSetState(rasterizerState);
    //DC->OMSetDepthStencilState(depthStencilState, 0);

    mesh->Set();


    D3D11_MAPPED_SUBRESOURCE mappedResource;
    ZeroMemory(&mappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));

    DC->Map(*transform.WorldBuffer(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

    // Copy Resource Data..
    memcpy(mappedResource.pData, transform.World(), sizeof(*transform.World()));

    // GPU Access UnLock Buffer Data..
    DC->Unmap(*transform.WorldBuffer(), 0);
    DC->VSSetConstantBuffers(0, 1, transform.WorldBuffer());

    material->Set();

    DC->PSSetShaderResources(3, 1, srvSkyBox);

    DC->DrawIndexed(mesh->GetIndexCount(), 0, 0);

    //return to default
    DC->RSSetState(defaultRasterizerState);
    //DC->OMSetDepthStencilState(defaultDepthStencilState, 0);
}

void Skybox::CreateSkyBox()
{
    name = "SkyBox";

    VertexSet vertexSet;

    vertexSet.AddElementToDesc(sizeof(float) * 3, DataType::FLOAT, "POSITION");

    float3 position[8] = {
        //앞면
    float3(-1,        +1,      -1),
    float3(+1,        +1,      -1),
    float3(-1,        -1,      -1),
    float3(+1,        -1,      -1),

    //뒷면
    float3(-1,         +1,     +1),
    float3(+1,         +1,     +1),
    float3(-1,         -1,     +1),
    float3(+1,         -1,     +1)
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

    mesh = new Mesh(vertexSet, indices.data(), indices.size(), L"SkyBoxVertex.hlsl");

    MaterialDesc matDesc;
    matDesc.pixelShaderName = L"SkyBoxPixel.hlsl";
    //matDesc.diffuseFileName = L"snowcube1024.dds";
    //matDesc.diffuseFileName = L"grasscube1024.dds";
    material = new Material(matDesc);

    RESOURCES->srvs->GetFromFile(srvSkyBox, L"nightsky_radionight.dds");//todo : 비어있을 때 에러가 안남
    //srvSkyBox = RESOURCES->srvs->Get(L"ColorCube.dds");//todo : 비어있을 때 에러가 안남

    transform.scale = { 100,100,100 };
}

void Skybox::CreateRasterState()
{
    D3D11_RASTERIZER_DESC desc = {};
    desc.AntialiasedLineEnable = true;
    desc.CullMode = D3D11_CULL_BACK; ; // D3D11_CULL_FRONT or D3D11_CULL_NONE D3D11_CULL_BACK
    desc.FillMode = D3D11_FILL_SOLID;
    desc.DepthClipEnable = true;
    desc.FrontCounterClockwise = true;
    desc.MultisampleEnable = true;

    RESOURCES->rasterStates->Get(rasterizerState, desc);
    RESOURCES->rasterStates->GetDefault(defaultRasterizerState);
}

void Skybox::CreateDepthStencilState()
{
    D3D11_DEPTH_STENCIL_DESC desc = {};
    desc.DepthEnable = true;
    desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    desc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;

    RESOURCES->depthStencilStates->Get(depthStencilState,desc);
    RESOURCES->depthStencilStates->GetDefault(defaultDepthStencilState);
}