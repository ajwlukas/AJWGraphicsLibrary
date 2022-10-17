#pragma once

#include <string>
#include <d3d11.h>

#include "typedef.h"
#include "Resources.h"
#include "Export.h"

/// <summary>
/// Material 생성하는 2가지 방법,
/// 1. MaterialDesc에 데이터를 작성해서 Material 생성자에 넣어줘서 생성
/// 2. Material을 생성후 Set함수들로 데이터 입력
/// 
/// written by Ssreppa 22.06.22
/// </summary>

struct AJW_GRAPHICS_DLLEXPORT MaterialDesc
{
	MaterialDesc()
		:pixelShaderName(L"Triangle.hlsl"), diffuseFileName(L""),samplerDesc{}
	{
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	}

	float4 ambient = { 0.8f, 0.8f, 0.8f, 1.0f };
	float4 diffuse;
	float4 specular;

	std::wstring pixelShaderName;
	std::wstring diffuseFileName;
	std::wstring normalFileName;
	D3D11_SAMPLER_DESC samplerDesc;
};

class AJW_GRAPHICS_DLLEXPORT Material
{
public:
	Material(ID3D11DeviceContext* deviceContext, Resources* resources, const MaterialDesc& desc = MaterialDesc());
	~Material();

	void Set();

	void SetShader(std::wstring fileName);

	void SetDiffuseMap(std::wstring fileName);
	void SetNormalMap(std::wstring fileName);
	void SetSpecularMap(std::wstring fileName);


	void SetSamplerState(D3D11_SAMPLER_DESC samplerDesc);

	struct Data
	{
		float4 ambient;
		float4 diffuse;
		float4 specular;
	}data;

	std::wstring pixelShaderName;
private:
	ID3D11DeviceContext* dc;
	Resources* resources;

	ID3D11PixelShader* pixelShader;
	Resource<ID3D11ShaderResourceView> diffuse;
	Resource<ID3D11ShaderResourceView> normal;
	Resource<ID3D11ShaderResourceView> specular;
	Resource<ID3D11SamplerState> samplerState;


	Resource<ID3D11Buffer> buffer;
};
