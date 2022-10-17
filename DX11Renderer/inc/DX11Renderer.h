#pragma once

#include "Export.h"

#include <d3d11.h>
#include <vector>
#include "Resource.h"
#include "Resources.h"

#include "Mesh.h"


class AJW_GRAPHICS_DLLEXPORT DX11Renderer
{
private:
	DX11Renderer();
	~DX11Renderer();
	static DX11Renderer* instance;
public:
	static void Create() { instance = nullptr ? instance : new DX11Renderer(); }
	static void Delete() { delete instance; }
	static DX11Renderer* Get() { return instance; }
	HRESULT Init();

private:
	HRESULT CreateDeviceAndSwapChain();
	HRESULT CreateRtv();
	HRESULT CreateAndSetDepthStencilView();
	HRESULT CreateAndSetRasterizerState();
	HRESULT CreateBlendState();
	void SetViewPort();

public:
	void BeginRender();
	void PreRender();
	void PostRender();
	void EndRender();

private:
	HWND hWnd;
	WINDOWINFO windowInfo;
	void OnResize();
	UINT width, height;
	ID3D11Device* device;
	ID3D11DeviceContext* dc;
	IDXGISwapChain* swapChain;

public:
	ID3D11Device* GetDevice() { return device; }
	ID3D11DeviceContext* GetDC() { return dc; }
	Resources* GetResources() { return resources; }

private:
	class Resources* resources;

	Resource<ID3D11DepthStencilView> depthStencilView;
	Resource<ID3D11RenderTargetView> rtv;
	Resource<ID3D11Texture2D> depthStencilBuffer;

	Resource<ID3D11DepthStencilState> depthStencilState;
	Resource<ID3D11DepthStencilState> noDepthStencilState;
	Resource<ID3D11RasterizerState> rasterState;
	Resource<ID3D11BlendState> blendState;

};
