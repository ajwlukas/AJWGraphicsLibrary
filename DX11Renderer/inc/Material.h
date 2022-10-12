#pragma once
/// <summary>
/// Material 생성하는 2가지 방법,
/// 1. MaterialDesc에 데이터를 작성해서 Material 생성자에 넣어줘서 생성
/// 2. Material을 생성후 Set함수들로 데이터 입력
/// 
/// written by Ssreppa 22.06.22
/// </summary>
struct MaterialDesc
{
	MaterialDesc()
		:pixelShaderName(L"LightPixel.hlsl"), diffuseFileName(L""),samplerDesc{}
	{
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	}

	float4 ambient = { 0.8f, 0.8f, 0.8f, 1.0f };
	float4 diffuse;
	float4 specular;

	wstring pixelShaderName;
	wstring diffuseFileName;
	wstring normalFileName;
	D3D11_SAMPLER_DESC samplerDesc;
};

class Material
{
public:
	Material(const MaterialDesc& desc = MaterialDesc());
	~Material();

	void Set();

	void SetShader(wstring fileName);

	void SetDiffuseMap(wstring fileName);
	void SetNormalMap(wstring fileName);
	void SetSpecularMap(wstring fileName);


	void SetSamplerState(D3D11_SAMPLER_DESC samplerDesc);

	struct Data
	{
		float4 ambient;
		float4 diffuse;
		float4 specular;
	}data;

	wstring pixelShaderName;
private:
	ID3D11PixelShader* pixelShader;
	Resource<ID3D11ShaderResourceView> diffuse;
	Resource<ID3D11ShaderResourceView> normal;
	Resource<ID3D11ShaderResourceView> specular;
	Resource<ID3D11SamplerState> samplerState;


	Resource<ID3D11Buffer> buffer;
};
