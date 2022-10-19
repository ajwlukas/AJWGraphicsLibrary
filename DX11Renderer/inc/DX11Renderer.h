#pragma once

#include "RenderSystem.h"

#include <d3d11.h>
#include <vector>

#include "Resource.h"
#include "Resources.h"

#include "Mesh.h"
#include "Material.h"
#include "Pipeline.h"

class  DX11Renderer : public TL_Graphics::RenderSystem
{
public:
	DX11Renderer();
	virtual ~DX11Renderer();
	/*static void Create() { instance = nullptr ? instance : new DX11Renderer(); }
	static void Delete() { delete instance; }
	static DX11Renderer* Get() { return instance; }*/
	virtual HRESULT Init() override;

	virtual void Clear()override;
	virtual void Draw() override;
	virtual void Present()override;

	virtual Mesh* CreateMesh(TL_Graphics::VertexSet& vertexSet, UINT indexData[], UINT indexCount,
		std::wstring vsFileName = L"UVLightVertex.hlsl", D3D_PRIMITIVE_TOPOLOGY topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST) override;

	//이후할것 example
	// Mesh* CreateAnimatingMesh();

	virtual Material* CreateMaterial(const TL_Graphics::MaterialDesc& desc = TL_Graphics::MaterialDesc()) override;


private:
	//static DX11Renderer* instance;

	HWND hWnd;
	WINDOWINFO windowInfo;
	UINT width, height;

	ID3D11Device* device;
	ID3D11DeviceContext* dc;
	IDXGISwapChain* swapChain;

	void OnResize();

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
