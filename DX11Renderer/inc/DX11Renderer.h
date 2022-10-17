#pragma once

#include "Export.h"

#include <d3d11.h>
#include <vector>

#include "Resource.h"
#include "Resources.h"

#include "Mesh.h"
#include "Material.h"

class AJW_GRAPHICS_DLLEXPORT DX11Renderer
{
public:
	static void Create() { instance = nullptr ? instance : new DX11Renderer(); }
	static void Delete() { delete instance; }
	static DX11Renderer* Get() { return instance; }
	HRESULT Init();

	void BeginRender();
	void PreRender();
	void PostRender();
	void EndRender();

	Mesh* CreateMesh(VertexSet& vertexSet, UINT indexData[], UINT indexCount,
		std::wstring vsFileName = L"UVLightVertex.hlsl", D3D_PRIMITIVE_TOPOLOGY topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	Material* CreateMaterial(const MaterialDesc& desc = MaterialDesc());

private:
	DX11Renderer();
	~DX11Renderer();
	static DX11Renderer* instance;

	HWND hWnd;
	WINDOWINFO windowInfo;
	UINT width, height;

	ID3D11Device* device;
	ID3D11DeviceContext* dc;
	IDXGISwapChain* swapChain;

	void OnResize();

	class Resources* resources;

	Resource<ID3D11DepthStencilView> depthStencilView;
	Resource<ID3D11RenderTargetView> rtv;
	Resource<ID3D11Texture2D> depthStencilBuffer;
	Resource<ID3D11DepthStencilState> depthStencilState;
	Resource<ID3D11DepthStencilState> noDepthStencilState;
	Resource<ID3D11RasterizerState> rasterState;
	Resource<ID3D11BlendState> blendState;

	HRESULT CreateDeviceAndSwapChain();
	HRESULT CreateRtv();
	HRESULT CreateAndSetDepthStencilView();
	HRESULT CreateAndSetRasterizerState();
	HRESULT CreateBlendState();
	void SetViewPort();
};
