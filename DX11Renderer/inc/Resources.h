#pragma once
#include <unordered_map>
#include <string>
#include "Resource.h"
/// <summary>
/// 가급적이면 생성자나, Init()같은 곳에서 한번만 호출해서 받아서 사용하길 권장(검색 한번만 하도록)
/// Resource<ResourceType>으로 사용, 사용 후 Return() 해줄 것
/// written by Ssreppa 22.06.28
/// 
/// Get()함수와 Create()함수 차이, Get()은 같은 옵션이면 있던거 줌,
/// Create()는 같은 옵션이어도 새로 만들어 줌
/// 더 이상 Return()해줄 필요 없음, 걍 선언하고 맘대로 쓰면 됨, 소멸자 걱정 안해도 됨
/// written by Ssreppa 22.07.01
/// 
/// 
///template <typename T>
///class Resource
///{
///public:
///	operator T* () { return resource; }
///	operator T** () { return &resource; }
///
///	T* resource;
///
///	std::function<void()> Return;
///};
/// </summary>

#ifdef _DEBUG
#define SHADERFLAG D3DCOMPILE_DEBUG | D3DCOMPILE_PACK_MATRIX_COLUMN_MAJOR |\
D3DCOMPILE_PARTIAL_PRECISION | D3DCOMPILE_OPTIMIZATION_LEVEL0

#else
#define SHADERFLAG D3DCOMPILE_PACK_MATRIX_COLUMN_MAJOR |\
D3DCOMPILE_PARTIAL_PRECISION | D3DCOMPILE_OPTIMIZATION_LEVEL3
#endif

class DX11Renderer;

class InputLayoutResources;

class VertexShaderResources;
class PixelShaderResources;

class SRVResources;

class SamplerStateResources;
class RasterizerStateResources;
class DepthStencilStateResources;
class BlendStateResources;

class BufferResources;
class Texture2DResources;
class RenderTargetViewResources;
class DepthStencilViewResources;

//todo : refCount 해서 안쓰는 리소스 자동 해제 하도록 만들 것

class Resources//모든 자원 매니저를 갖고있는 클래스
{
public:
	Resources();
	~Resources();
public:
	VertexShaderResources* vertexShaders;
	InputLayoutResources* inputLayouts;
	PixelShaderResources* pixelShaders;
	SRVResources* srvs;
	SamplerStateResources* samplerStates;
	RasterizerStateResources* rasterStates;
	DepthStencilStateResources* depthStencilStates;
	BlendStateResources* blendStates;
	Texture2DResources* texture2Ds;
	RenderTargetViewResources* rtvs;
	DepthStencilViewResources* depthStencilViews;
	BufferResources* buffers;
};

class VertexShaderResources
{
public:
	ID3D11VertexShader* Get(std::wstring shaderFileName);

	ID3DBlob* GetBlob(std::wstring shaderFileName);

	void Release();

private:
	std::unordered_map<std::wstring, ID3D11VertexShader*> vertexShaders;
	std::unordered_map<std::wstring, ID3DBlob*> vertexShaderBlobs;
	ID3DBlob* error = nullptr;
};

class InputLayoutResources
{
public:
	void Get(Resource< ID3D11InputLayout>& dest, D3D11_INPUT_ELEMENT_DESC* desc, UINT descSize, std::wstring vertexShaderFileName);

private:
	friend class Resources;
	void Release();

	struct Data
	{
		Data() : data(nullptr), refCount(0) {}
		ID3D11InputLayout* data;
		UINT refCount;
	};
	std::unordered_map<std::string, Data> inputLayouts;
} ;

class PixelShaderResources
{
public:
	ID3D11PixelShader* Get(std::wstring shaderFileName);
	ID3DBlob* GetBlob(std::wstring shaderFileName);

	void Release();

private:
	std::unordered_map<std::wstring, ID3D11PixelShader*> pixelShaders;
	std::unordered_map<std::wstring, ID3DBlob*> pixelShaderBlobs;
	ID3DBlob* error;
};

class SRVResources
{
public:
	void Create(Resource<ID3D11ShaderResourceView>& dest, D3D11_SHADER_RESOURCE_VIEW_DESC desc, ID3D11Resource* buffer);
	void GetFromFile(Resource< ID3D11ShaderResourceView>& dest, std::wstring fileName);

private:
	friend class Resources;
	void Release();

	struct Data
	{
		Data() : data(nullptr), refCount(0) {}
		ID3D11ShaderResourceView* data;
		UINT refCount;
	};
	std::unordered_map<ID3D11ShaderResourceView*, Data> srvs;
	std::unordered_map<std::wstring, Data> srvsFromTexture;
};

/// States for DX
class SamplerStateResources
{
public:
	void Get(Resource< ID3D11SamplerState>& dest, D3D11_SAMPLER_DESC desc);

private:
	friend class Resources;
	void Release();

	struct Data
	{
		Data() : data(nullptr), refCount(0) {}
		ID3D11SamplerState* data;
		UINT refCount;
	};
	std::unordered_map<std::string, Data> samplerStates;
};

class RasterizerStateResources
{
public:
	RasterizerStateResources()
	{
		D3D11_RASTERIZER_DESC desc = {};
		desc.AntialiasedLineEnable = false;
		desc.CullMode = D3D11_CULL_BACK;
		desc.DepthBias = 0;
		desc.DepthBiasClamp = 0.0f;
		desc.DepthClipEnable = true;
		desc.FillMode = D3D11_FILL_SOLID;
		//rasterDesc.FillMode = D3D11_FILL_WIREFRAME;
		desc.FrontCounterClockwise = false;
		desc.MultisampleEnable = false;
		desc.ScissorEnable = false;
		desc.SlopeScaledDepthBias = 0.0f;

		SetDefault(desc);

		desc.FillMode =  D3D11_FILL_WIREFRAME;
		wireFrameDesc = desc;
	}

	void Get(Resource< ID3D11RasterizerState>& dest, D3D11_RASTERIZER_DESC desc);

	void GetDefault(Resource< ID3D11RasterizerState>& dest) { Get(dest, defaultDesc); }
	void GetWireMode(Resource< ID3D11RasterizerState>& dest) { Get(dest, wireFrameDesc); }
	void SetDefault(D3D11_RASTERIZER_DESC desc);

private:
	friend class Resources;
	void Release();

	struct Data
	{
		Data() : data(nullptr), refCount(0) {}
		ID3D11RasterizerState* data;
		UINT refCount;
	};
	D3D11_RASTERIZER_DESC defaultDesc;
	D3D11_RASTERIZER_DESC wireFrameDesc;
	std::unordered_map<std::string, Data> rasterizerStates;
};

class DepthStencilStateResources
{
public:
	DepthStencilStateResources()
	{
		D3D11_DEPTH_STENCIL_DESC desc = {};

		desc.DepthEnable = true;
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

		SetDefault(desc);
	}
	void Get(Resource< ID3D11DepthStencilState>& dest,D3D11_DEPTH_STENCIL_DESC desc);

	void GetDefault(Resource< ID3D11DepthStencilState>& dest) { Get(dest, defaultDesc); }
	void SetDefault(D3D11_DEPTH_STENCIL_DESC desc);

private:
	friend class Resources;
	void Release();

	struct Data
	{
		Data() : data(nullptr), refCount(0) {}
		ID3D11DepthStencilState* data;
		UINT refCount;
	};
	D3D11_DEPTH_STENCIL_DESC defaultDesc;
	std::unordered_map<std::string, Data> depthStencilStates;
};

class BlendStateResources
{
public:
	BlendStateResources()
	{
		D3D11_BLEND_DESC desc = {};
		desc.RenderTarget[0].BlendEnable = TRUE;
		desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		desc.RenderTarget[0].RenderTargetWriteMask = 0x0f;

		SetDefault(desc);
	}
	void Get(Resource<ID3D11BlendState>& dest, D3D11_BLEND_DESC desc);

	void GetDefault(Resource<ID3D11BlendState>& dest) { Get(dest, defaultDesc); };
	void SetDefault(D3D11_BLEND_DESC desc);

private:
	friend class Resources;
	void Release();

	struct Data
	{
		Data() : data(nullptr), refCount(0) {}
		ID3D11BlendState* data;
		UINT refCount;
	};
	D3D11_BLEND_DESC defaultDesc;
	std::unordered_map<std::string, Data> blendStates;
};

/////////////////////////////////////////////////////////////// 공유하지 않는 자원들

class Texture2DResources
{
public:
	 void Create(Resource<ID3D11Texture2D>& dest, D3D11_TEXTURE2D_DESC desc,const D3D11_SUBRESOURCE_DATA* pInitData = NULL);

private:
	friend class Resources;
	void Release();

	struct Data
	{
		Data() : data(nullptr), refCount(0) {}
		ID3D11Texture2D* data;
		UINT refCount;
	};
	std::unordered_map<ID3D11Texture2D*, Data> texture2Ds;// leak 안나게 저장하는 용도, 비효율적이지만 다른 방법이 생각이 안남
};

class BufferResources
{
public:
	 void Create(Resource<ID3D11Buffer>& dest, D3D11_BUFFER_DESC desc,const D3D11_SUBRESOURCE_DATA* pInitData = NULL);

private:
	friend class Resources;
	void Release();

	struct Data
	{
		Data() : data(nullptr), refCount(0) {}
		ID3D11Buffer* data;
		UINT refCount;
	};
	std::unordered_map<ID3D11Buffer*, Data> buffers;// leak 안나게 저장하는 용도, 비효율적이지만 다른 방법이 생각이 안남
};

class RenderTargetViewResources
{
public:
	RenderTargetViewResources()
	{
		D3D11_RENDER_TARGET_VIEW_DESC desc = {};
		desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		desc.Texture2D.MipSlice = 0;

		SetDefault(desc);
	}
	void Create(Resource<ID3D11RenderTargetView>& dest,D3D11_RENDER_TARGET_VIEW_DESC desc, ID3D11Resource* buffer);

	void CreateDefault(Resource<ID3D11RenderTargetView>& dest, ID3D11Resource* buffer) { Create(dest, defaultDesc, buffer); };
	void SetDefault(D3D11_RENDER_TARGET_VIEW_DESC desc) {	defaultDesc = desc;};
private:
	friend class Resources;
	void Release();

	struct Data
	{
		Data() : data(nullptr), refCount(0) {}
		ID3D11RenderTargetView* data;
		UINT refCount;
	};
	D3D11_RENDER_TARGET_VIEW_DESC defaultDesc;
	std::unordered_map<ID3D11RenderTargetView*, Data> rtvs;// leak 안나게 저장하는 용도
};


class DepthStencilViewResources
{
public:
	DepthStencilViewResources()
	{
		D3D11_DEPTH_STENCIL_VIEW_DESC desc = {};

		desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		desc.Texture2D.MipSlice = 0;

		SetDefault(desc);
	}
	void Create(Resource<ID3D11DepthStencilView>& dest,D3D11_DEPTH_STENCIL_VIEW_DESC desc, ID3D11Resource* buffer);

	void CreateDefault(Resource<ID3D11DepthStencilView>& dest, ID3D11Resource* buffer) { Create(dest, defaultDesc, buffer); };
	void SetDefault(D3D11_DEPTH_STENCIL_VIEW_DESC desc) {	defaultDesc = desc;};
private:
	friend class Resources;
	void Release();

	struct Data
	{
		Data() : data(nullptr), refCount(0) {}
		ID3D11DepthStencilView* data;
		UINT refCount;
	};
	D3D11_DEPTH_STENCIL_VIEW_DESC defaultDesc;
	std::unordered_map<ID3D11DepthStencilView*, Data> depthStencilViews;// leak 안나게 저장하는 용도
};



