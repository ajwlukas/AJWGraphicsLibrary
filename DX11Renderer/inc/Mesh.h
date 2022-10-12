#pragma once

#include <string>
#include "Vertex.h"
/// <summary>
/// 버텍스, 인덱스, 인풋레이아웃 정보를 가지고 있는 오브젝트
/// 
/// written by Ssreppa 22.06.22
/// </summary>

struct Mesh
{
public:
	Mesh(VertexSet& vertexSet, UINT indexData[], UINT indexCount,
		std::wstring vsFileName = L"UVLightVertex.hlsl", D3D_PRIMITIVE_TOPOLOGY topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	virtual ~Mesh();
	void Set();

	const UINT& GetIndexCount() const { return indexCount; }

	/*void SetShader(wstring vsFileName) {
		this->vsFileName = vsFileName;
		RESOURCES->inputLayouts->Get(inputLayout, desc, descSize, vsFileName);
		shader = RESOURCES->vertexShaders->Get(vsFileName);
	}*/

private:
	std::wstring vsFileName;
	Resource<ID3D11InputLayout> inputLayout;
	D3D_PRIMITIVE_TOPOLOGY topology;

	UINT vertexDataSize;
	UINT indexCount;
	UINT offset = 0;
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;
	ID3D11VertexShader* shader;

	D3D11_INPUT_ELEMENT_DESC* desc;
	UINT descSize;
};