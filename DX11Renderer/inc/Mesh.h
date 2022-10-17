#pragma once

#include <d3d11.h>
#include <string>

#include "Export.h"
#include "Resources.h"
#include "Vertex.h"
/// <summary>
/// 버텍스, 인덱스, 인풋레이아웃 정보를 가지고 있는 오브젝트
/// 
/// written by Ssreppa 22.06.22
/// </summary>

 struct AJW_GRAPHICS_DLLEXPORT Mesh
{
public:
	Mesh(ID3D11DeviceContext* deviceContext, Resources* resources, VertexSet& vertexSet, UINT indexData[], UINT indexCount,
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
	ID3D11DeviceContext* dc;

	std::wstring vsFileName;
	Resource<ID3D11InputLayout> inputLayout;
	D3D_PRIMITIVE_TOPOLOGY topology;

	UINT vertexDataSize;
	UINT indexCount;
	UINT offset = 0;
	Resource<ID3D11Buffer> vertexBuffer;
	Resource<ID3D11Buffer> indexBuffer;
	ID3D11VertexShader* shader;

	D3D11_INPUT_ELEMENT_DESC* desc;
	UINT descSize;
};