#pragma once
/// <summary>
/// Material �����ϴ� 2���� ���,
/// 1. MaterialDesc�� �����͸� �ۼ��ؼ� Material �����ڿ� �־��༭ ����
/// 2. Material�� ������ Set�Լ���� ������ �Է�
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