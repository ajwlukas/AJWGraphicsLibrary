﻿#include "pch_dx_11.h"

#include "DX11Renderer.h"

#include "Transform.h"
#include "Camera.h"

#include "PostProcessor.h"

DX11Renderer* DX11Renderer::instance = nullptr;

DX11Renderer::DX11Renderer()
    :device(nullptr), dc(nullptr), hWnd(0), windowInfo{}, swapChain(nullptr), rtv{}, depthStencilBuffer{},
    depthStencilView{}, rasterState{}, width(0), height(0)
{
}

DX11Renderer::~DX11Renderer()
{
    for (int i = 0; i < 3; i++)
    {
        SAFE_DELETE( rtts[i]);
    }

    TestDestructor();

    SAFE_DELETE(font);

    depthStencilState.Return();
    noDepthStencilState.Return();

    SAFE_DELETE(skyboxRTT);
    SAFE_DELETE(postProcessor);
    SAFE_DELETE(defferedRenderer);
    SAFE_DELETE(resources);
    SAFE_RELEASE(device);
    SAFE_RELEASE(dc);
    SAFE_RELEASE(swapChain);
}

HRESULT DX11Renderer::Init()
{
    hWnd = GetActiveWindow();
    GetWindowInfo(hWnd, &windowInfo);

    OnResize();

    HRESULT hr = S_OK;

    hr = CreateDeviceAndSwapChain();
    if (hr != S_OK) return hr;

    resources = new Resources();

    hr = CreateRtv();
    if (hr != S_OK) return hr;

    hr = CreateAndSetDepthStencilView();
    if (hr != S_OK) return hr;

    hr = CreateAndSetRasterizerState();
    if (hr != S_OK) return hr;

    hr = CreateBlendState();
    if (hr != S_OK) return hr;

    SetViewPort();


    return hr;
}

HRESULT DX11Renderer::CreateDeviceAndSwapChain()
{
    DXGI_SWAP_CHAIN_DESC swapChainDesc;
    ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
    swapChainDesc.BufferCount = 1;
    swapChainDesc.BufferDesc.Width = width;
    swapChainDesc.BufferDesc.Height = height;
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
    swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.OutputWindow = hWnd;
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.SampleDesc.Quality = 0;
    swapChainDesc.Windowed = TRUE;//창모드 변경

    swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    swapChainDesc.Flags = 0;

    D3D_FEATURE_LEVEL FeatureLevels = D3D_FEATURE_LEVEL_11_0;

    HRESULT hr = S_OK;
    D3D_FEATURE_LEVEL FeatureLevel;

    if (FAILED(hr = D3D11CreateDeviceAndSwapChain(NULL,
        D3D_DRIVER_TYPE_HARDWARE,
        NULL,
        0,
        &FeatureLevels,
        1,
        D3D11_SDK_VERSION,
        &swapChainDesc,
        &swapChain,
        &device,
        &FeatureLevel,
        &dc)))
    {
        return hr;
    }

    return hr;
}

HRESULT DX11Renderer::CreateRtv()
{
    HRESULT hr = S_OK;

    rtv.Return();

    ID3D11Texture2D* backBuffer = nullptr;
    swapChain->ResizeBuffers(1, width, height, DXGI_FORMAT_R8G8B8A8_UNORM, 0);
    if (FAILED(hr = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer)))
    {
        return hr;
    }

    resources->rtvs->CreateDefault(rtv, backBuffer);

    backBuffer->Release();
    backBuffer = nullptr;

    return hr;
}

HRESULT DX11Renderer::CreateAndSetDepthStencilView()
{
    HRESULT hr = S_OK;

    D3D11_TEXTURE2D_DESC depthBufferDesc;
    ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));


    depthBufferDesc.Width = width;
    depthBufferDesc.Height = height;
    depthBufferDesc.MipLevels = 1;
    depthBufferDesc.ArraySize = 1;
    depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthBufferDesc.SampleDesc.Count = 1;
    depthBufferDesc.SampleDesc.Quality = 0;
    depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    depthBufferDesc.CPUAccessFlags = 0;
    depthBufferDesc.MiscFlags = 0;


    resources->texture2Ds->Create(depthStencilBuffer, depthBufferDesc);

    resources->depthStencilStates->GetDefault(depthStencilState);

    D3D11_DEPTH_STENCIL_DESC desc = {};

    desc.DepthEnable = false;
    desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    desc.DepthFunc = D3D11_COMPARISON_LESS;

    desc.StencilEnable = true;
    desc.StencilReadMask = 0xFF;
    desc.StencilWriteMask = 0xFF;

    desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
    desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
    desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
    desc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

    desc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
    desc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
    desc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
    desc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

    resources->depthStencilStates->Get(noDepthStencilState,desc);

    dc->OMSetDepthStencilState(noDepthStencilState, 1);

    resources->depthStencilViews->CreateDefault(depthStencilView, depthStencilBuffer);

    dc->OMSetRenderTargets(1, rtv, depthStencilView);//todo : 여기
    return hr;
}

HRESULT DX11Renderer::CreateAndSetRasterizerState()
{
    HRESULT hr = S_OK;

    resources->rasterStates->GetDefault(rasterState);

    dc->RSSetState(rasterState);

    return hr;
}

HRESULT DX11Renderer::CreateBlendState()
{
    HRESULT hr = S_OK;

    resources->blendStates->GetDefault(blendState);

    DC->OMSetBlendState(blendState, NULL, 0xFF);

    return hr;
}

void DX11Renderer::SetViewPort()
{
    D3D11_VIEWPORT viewPort = {};
    viewPort.Width = (float)width;
    viewPort.Height = (float)height;
    viewPort.MinDepth = 0.0f;
    viewPort.MaxDepth = 1.0f;
    viewPort.TopLeftX = 0.0f;
    viewPort.TopLeftY = 0.0f;

    dc->RSSetViewports(1, &viewPort);
}

void DX11Renderer::OnResize()
{
    if (this == nullptr) return;

    GetWindowInfo(hWnd, &windowInfo);
        width = windowInfo.rcClient.right - windowInfo.rcClient.left;
        height = windowInfo.rcClient.bottom - windowInfo.rcClient.top;

        if (width == 0 && height == 0) return;

    if (dc != nullptr)
    {
        //CreateRtv();
     
        CreateAndSetDepthStencilView();

        defferedRenderer->OnResize();

        postProcessor->OnResize();

        SetRTTasBackBuffer(postProcessor->GetLastRTT());

        skyboxRTT->OnResize();

        SetViewPort();
    }
    if (cam != nullptr)
        cam->OnResize(height, width);
}

void DX11Renderer::SetRTTasBackBuffer(RenderTargetTexutre* rtt)
{
    rtt->rtv.Return();


    ID3D11Texture2D* backBuffer = nullptr;
    swapChain->ResizeBuffers(1, width, height, DXGI_FORMAT_R8G8B8A8_UNORM, 0);
    swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer);

    resources->rtvs->CreateDefault(rtt->rtv, backBuffer);

    backBuffer->Release();
    backBuffer = nullptr;

    rtv = rtt->rtv;
}

void DX11Renderer::BeginRender()
{
    float color[4] = { 0.0f, 0.7f, 1.0f, 1.0f };
    float transparent[4] = { 0.0f,0.0f,0.0f,0.0f };//todo: 구차나서 일단 이렇게 해놓음
    float white[4] = { 1.0f,1.0f,1.0f,1.0f };//todo: 구차나서 일단 이렇게 해놓음



    defferedRenderer->ClearRenderTargetView();

    dc->ClearRenderTargetView(rtv, transparent);

    dc->ClearRenderTargetView(skyboxRTT->rtv, transparent);

    postProcessor->ClearRenderTargets();

    dc->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void DX11Renderer::BeginRenderT()
{
    float color[4] = { 0.0f, 0.7f, 1.0f, 1.0f };
    float transparent[4] = { 0.0f,0.0f,0.0f,0.0f };//todo: 구차나서 일단 이렇게 해놓음
    float white[4] = { 1.0f,1.0f,1.0f,1.0f };//todo: 구차나서 일단 이렇게 해놓음



    //defferedRenderer->ClearRenderTargetView();

    dc->ClearRenderTargetView(rtv, color);

    //dc->ClearRenderTargetView(skyboxRTT->rtv, transparent);

    //postProcessor->ClearRenderTargets();

    dc->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void DX11Renderer::TestInit()
{
    cam = new Camera(); 

    skyBox = new Skybox(cam);


    grid = new Grid(cam);
}

void DX11Renderer::TestDestructor()
{
    SAFE_DELETE(cam);
    SAFE_DELETE(skyBox);
    SAFE_DELETE(canvas);
    SAFE_DELETE(normalCanvas);
    SAFE_DELETE(albedoCanvas);
    SAFE_DELETE(grid);

}

void DX11Renderer::TestUpdate()
{

    cam->Update();
    skyBox->Update();
    //canvas->Update();
    /*normalCanvas->Update();
    albedoCanvas->Update();*/
    defferedRenderer->Update();
    grid->Update();

    //factory->Update();

}

void DX11Renderer::PreRender()
{
    cam->Render();

    //foward Rendering
    //defferedRenderer->SetRenderTargets();//디퍼드에 필요한 렌더 타겟들 세팅
    
    dc->OMSetDepthStencilState(depthStencilState, 1);

    //factory->Render();//디퍼드 준비물들 준비 == 포워드 렌더링
}

/// 이 사이에 오브젝트 그리기 호출
/// 현재는  factory->Render(); 가 그역할 하는 중

void DX11Renderer::SetSwapchainRenderTarget()
{
    dc->OMSetRenderTargets(1, skyboxRTT->rtv, depthStencilView);//depthStencilView를 다른걸 쓰긴 해야할듯, 옵션도 다르게 줘야할까?
}


void DX11Renderer::PostRender()
{
    dc->OMSetDepthStencilState(noDepthStencilState, 1);
    //Post Render(DefferedRender)
    skyBox->Render();
    grid->Render();

    defferedRenderer->Render();

    postProcessor->Render();

    Canvas::manager.Render();

    //DebugFont();
}
//
//void DX11Renderer::DebugFont()
//{
//    font->DrawTest();
//
//    wstring fps = to_wstring(TIME->FPS());
//    font->DrawTextColor(50, 50, XMFLOAT4(0, 1, 0, 1), (TCHAR*)fps.c_str());
//
//    fps = L"Mouse Delta X : ";
//    font->DrawTextColor(50, 560, XMFLOAT4(0, 1, 0, 1), (TCHAR*)fps.c_str());
//    fps = L"Mouse Delta Y : ";
//    font->DrawTextColor(50, 590, XMFLOAT4(0, 1, 0, 1), (TCHAR*)fps.c_str());
//
//    fps = to_wstring(KeyBoard::Get()->mouseDx);
//    font->DrawTextColor(150, 560, XMFLOAT4(0, 1, 0, 1), (TCHAR*)fps.c_str());
//    fps = to_wstring(KeyBoard::Get()->mouseDy);
//    font->DrawTextColor(150, 590, XMFLOAT4(0, 1, 0, 1), (TCHAR*)fps.c_str());
//
//    fps = L"Rot X : ";
//    font->DrawTextColor(50, 660, XMFLOAT4(0, 1, 0, 1), (TCHAR*)fps.c_str());
//    fps = L"Rot Y : ";
//    font->DrawTextColor(50, 690, XMFLOAT4(0, 1, 0, 1), (TCHAR*)fps.c_str());
//    fps = L"Rot Z : ";
//    font->DrawTextColor(50, 720, XMFLOAT4(0, 1, 0, 1), (TCHAR*)fps.c_str());
//
//    fps = to_wstring(cam->transform.worldRot.x);
//    font->DrawTextColor(120, 660, XMFLOAT4(0, 1, 0, 1), (TCHAR*)fps.c_str());
//    fps = to_wstring(cam->transform.worldRot.y);
//    font->DrawTextColor(120, 690, XMFLOAT4(0, 1, 0, 1), (TCHAR*)fps.c_str());
//    fps = to_wstring(cam->transform.worldRot.z);
//    font->DrawTextColor(120, 720, XMFLOAT4(0, 1, 0, 1), (TCHAR*)fps.c_str());
//
//    fps = L"CamPos X : ";
//    font->DrawTextColor(50, 760, XMFLOAT4(0, 1, 0, 1), (TCHAR*)fps.c_str());
//    fps = L"CamPos Y : ";
//    font->DrawTextColor(50, 790, XMFLOAT4(0, 1, 0, 1), (TCHAR*)fps.c_str());
//    fps = L"CamPos Z : ";
//    font->DrawTextColor(50, 820, XMFLOAT4(0, 1, 0, 1), (TCHAR*)fps.c_str());
//
//    fps = to_wstring(cam->transform.pos.x);
//    font->DrawTextColor(120, 760, XMFLOAT4(0, 1, 0, 1), (TCHAR*)fps.c_str());
//    fps = to_wstring(cam->transform.pos.y);
//    font->DrawTextColor(120, 790, XMFLOAT4(0, 1, 0, 1), (TCHAR*)fps.c_str());
//    fps = to_wstring(cam->transform.pos.z);
//    font->DrawTextColor(120, 820, XMFLOAT4(0, 1, 0, 1), (TCHAR*)fps.c_str());
//}

void DX11Renderer::EndRender()
{
    swapChain->Present(0, 0);
}