#pragma once

#include "Export.h"

#include <d3d11.h>
#include <vector>
#include "Resource.h"
#include "DXTKFont.h"

//#include "AimCanvas.h"


class Camera;
class Instance;
class InstancingObject;
class Proto;
class RenderingObject;
class Skybox;
class Canvas;
class Grid;
class DefferedRenderer;
class RenderTargetTexutre;
class GeoMetryFactory;
class AimCanvas;
class PostProcessor;

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

	void BeginRender();
	void BeginRenderT();

	void SetSwapchainRenderTarget();
	void PreRender();
	void PostRender();

	//////////////////////
	Camera* cam;
	Skybox* skyBox;
	DefferedRenderer* defferedRenderer;
	RenderTargetTexutre* rtts[4];
	Canvas* canvas;
	Canvas* normalCanvas;
	Canvas* albedoCanvas;
	Grid* grid;

	//AimCanvas* aimCanvas;
	
	DXTKFont* font;
	GeoMetryFactory* factory;

	void TestInit();
	void TestDestructor();
	void TestUpdate();

	/////////////////////////

	void DebugFont();

	void EndRender();
private:
	HRESULT CreateDeviceAndSwapChain();
	HRESULT CreateRtv();
	HRESULT CreateAndSetDepthStencilView();
	HRESULT CreateAndSetRasterizerState();
	HRESULT CreateBlendState();
	void SetViewPort();

#pragma region
private:
	HWND hWnd;
	WINDOWINFO windowInfo;
public:
	void OnResize();
	UINT width, height;
#pragma endregion

#pragma region
private:
	ID3D11Device* device;
	ID3D11DeviceContext* dc;
	IDXGISwapChain* swapChain;
public:
	ID3D11Device* GetDevice() { return device; }
	ID3D11DeviceContext* GetDC() { return dc; }
	Camera* GetCamera() { return cam; }
	DXTKFont* GetFont() { return font; }
#pragma endregion

#pragma region
public:
	Resource<ID3D11DepthStencilView> depthStencilView;
private:
	class Resources* resources;

	Resource<ID3D11RenderTargetView> rtv;
	Resource<ID3D11Texture2D> depthStencilBuffer;

	Resource<ID3D11DepthStencilState> depthStencilState;
	Resource<ID3D11DepthStencilState> noDepthStencilState;
	Resource<ID3D11RasterizerState> rasterState;
	Resource<ID3D11BlendState> blendState;

	RenderTargetTexutre* skyboxRTT;
public:
	Resources* GetResources() {return resources;}
#pragma endregion

	//실험적인 코드
	void SetRTTasBackBuffer(RenderTargetTexutre* rtt);//최종 출력을 삼는다는 뜻

	PostProcessor* postProcessor;
};
