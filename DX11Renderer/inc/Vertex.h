#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "Export.h"

class ShaderNameFinder
{
public:
	ShaderNameFinder()
	{
		shaderNames["_POSITION"] = L"PosVS.hlsl";
		shaderNames["_POSITION_NORMAL"] = L"LightVertex.hlsl";
		shaderNames["_POSITION_UV_NORMAL_TANGENT"] = L"UVLightNormalMapVertex.hlsl";
		shaderNames["_POSITION_UV_NORMAL"] = L"UVLightVertex.hlsl";//todo : �ӽ� �ڵ�
		shaderNames["_POSITION_UV_NORMAL_REFINDEX_WEIGHT"] = L"SkinningAnimationVertex.hlsl";
		shaderNames["_POSITION_UV_NORMAL_TANGENT_REFINDEX_WEIGHT"] = L"SkinningTangentAnimationVertex.hlsl";
	}

	std::wstring Find(std::string semanticString) { return shaderNames.at(semanticString); }

private:
	std::unordered_map<std::string, std::wstring> shaderNames;
};

 enum class AJW_GRAPHICS_DLLEXPORT DataType
{
	FLOAT,
	UINT
};

 class AJW_GRAPHICS_DLLEXPORT VertexSet//������ ����� ���ؽ� ����� �׽�Ʈ ����
{
public:
	VertexSet()
		:memIndex(0), stride(0), semanticString("")
	{

	}
	void AddElementToDesc(UINT dataSize, DataType type,
		LPCSTR  SemanticName, int SemanticIndex = 0,	
		int inputSlot = 0, int InstanceDataStepRate = 0);
	//���� : Element ���� ������ �����͸� �־��־����

	void AddData(void* data, UINT dataSize);
	//���� : 4����Ʈ¥�� ������ �¸� �־�� ��!! ex)float, int, float3, float4 ���, bool, long, short ����x
	// ������ �ð�ȭ ���� : vertex0.pos.x | vertex0.pos.y | vertex0.pos.z | vertex0.uv.u | vertex0.uv.v | vertex1.pos.x ...

	void* GetVerticesData() { return verticesData.data(); }
	UINT GetVerticesSize() { return verticesData.size() * sizeof(DWORD); }
	UINT GetVertexSize() { return stride; }

	D3D11_INPUT_ELEMENT_DESC* GetDescsData() { return descs.data(); }
	UINT GetDescsSize() { return descs.size(); }

	std::wstring GetCorrespondingShaderFileName() { return shaderFinder.Find(semanticString); }
private:
	std::vector<DWORD> verticesData;//���� ���ؽ����� ������
	UINT memIndex;

	std::vector<D3D11_INPUT_ELEMENT_DESC> descs;
	UINT stride;//���ؽ� �ϳ��� ũ��

	std::string semanticString;
	static ShaderNameFinder shaderFinder;//��ǲ ���п� ���� �˸��� �⺻ ���̴��� �̸��� �ְ�
};