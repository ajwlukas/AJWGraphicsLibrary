#pragma once

#include "RenderSystem.h"

#include <d3d11.h>
#include <vector>

#include "OnResize.h"

#include "Resource.h"
#include "Resources.h"

#include "Mesh.h"
#include "Material.h"
#include "ConstantBuffer.h"
#include "Camera.h"

#include "Pipeline.h"


class  DX11Renderer : public TL_Graphics::RenderSystem, public OnResize_Observer
{
public:
	DX11Renderer();
	virtual ~DX11Renderer();

	virtual HRESULT Init() override;

	virtual void Clear()override;
	virtual void Draw() override;
	virtual void Present()override;

	virtual Mesh* CreateMesh(TL_Graphics::VertexSet& vertexSet, UINT indexData[], UINT indexCount, std::wstring fileName) override;

	virtual Material* CreateMaterial(std::wstring fileName, const TL_Graphics::MaterialDesc& desc = TL_Graphics::MaterialDesc()) override;

	virtual ConstantBuffer* CreateConstantBuffer(UINT slot, void* data, size_t dataSize) override;

	virtual Camera* CreateCamera() override;

	virtual void UpdateWindowSize(UINT width, UINT height) override;

private:
	HWND hWnd;
	WINDOWINFO windowInfo;
	UINT width, height;

	ID3D11Device* device;
	ID3D11DeviceContext* dc;
	IDXGISwapChain* swapChain;

	OnResizeNotice onResizeNotice;
	virtual void OnResize(uint32_t _width, uint32_t _height) override;

	Resources* resources;

	Resource<ID3D11DepthStencilView> depthStencilView;
	Resource<ID3D11RenderTargetView> rtv;
	Resource<ID3D11Texture2D> depthStencilBuffer;
	Resource<ID3D11DepthStencilState> depthStencilState;
	Resource<ID3D11DepthStencilState> noDepthStencilState;
	Resource<ID3D11RasterizerState> rasterState;
	Resource<ID3D11BlendState> blendState;

	Pipeline* pipeline;

	HRESULT CreateDeviceAndSwapChain();
	HRESULT CreateRtv();
	HRESULT CreateAndSetDepthStencilView();
	HRESULT CreateAndSetRasterizerState();
	HRESULT CreateBlendState();
	void SetViewPort();

};
