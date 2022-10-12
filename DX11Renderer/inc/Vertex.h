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
		shaderNames["_POSITION_UV_NORMAL"] = L"UVLightVertex.hlsl";//todo : 임시 코드
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

 class AJW_GRAPHICS_DLLEXPORT VertexSet//저절로 만드는 버텍스 만드는 테스트 구조
{
public:
	VertexSet()
		:memIndex(0), stride(0), semanticString("")
	{

	}
	void AddElementToDesc(UINT dataSize, DataType type,
		LPCSTR  SemanticName, int SemanticIndex = 0,	
		int inputSlot = 0, int InstanceDataStepRate = 0);
	//주의 : Element 넣은 순서로 데이터를 넣어주어야함

	void AddData(void* data, UINT dataSize);
	//주의 : 4바이트짜리 데이터 셋만 넣어야 함!! ex)float, int, float3, float4 등등, bool, long, short 지원x
	// 데이터 시각화 예시 : vertex0.pos.x | vertex0.pos.y | vertex0.pos.z | vertex0.uv.u | vertex0.uv.v | vertex1.pos.x ...

	void* GetVerticesData() { return verticesData.data(); }
	UINT GetVerticesSize() { return verticesData.size() * sizeof(DWORD); }
	UINT GetVertexSize() { return stride; }

	D3D11_INPUT_ELEMENT_DESC* GetDescsData() { return descs.data(); }
	UINT GetDescsSize() { return descs.size(); }

	std::wstring GetCorrespondingShaderFileName() { return shaderFinder.Find(semanticString); }
private:
	std::vector<DWORD> verticesData;//실제 버텍스들의 데이터
	UINT memIndex;

	std::vector<D3D11_INPUT_ELEMENT_DESC> descs;
	UINT stride;//버텍스 하나의 크기

	std::string semanticString;
	static ShaderNameFinder shaderFinder;//인풋 성분에 따라 알맞은 기본 쉐이더의 이름을 주게
};