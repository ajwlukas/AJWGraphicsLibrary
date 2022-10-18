#pragma once

#include <d3d11.h>
#include <string>

#include "IMesh.h"
#include "Resources.h"
#include "Vertex.h"
/// <summary>
/// 버텍스, 인덱스, 인풋레이아웃 정보를 가지고 있는 오브젝트
/// 
/// written by Ssreppa 22.06.22
/// </summary>

class Pipeline;

 class  Mesh : public TL_Graphics::IMesh
{
public:
	Mesh(ID3D11DeviceContext* deviceContext, Resources* resources, Pipeline* pipeline, VertexSet& vertexSet, UINT indexData[], UINT indexCount,
		std::wstring vsFileName = L"UVLightVertex.hlsl", D3D_PRIMITIVE_TOPOLOGY topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	virtual ~Mesh();
	virtual void Set() override;

	const UINT& GetIndexCount() const { return indexCount; }

	void SetShader(std::wstring vsFileName) {
		this->vsFileName = vsFileName;
		resources->inputLayouts->Get(inputLayout, desc, descSize, vsFileName);
		shader = resources->vertexShaders->Get(vsFileName);
	}

private:
	ID3D11DeviceContext* dc;
	Resources* resources;
	Pipeline* pipeline;

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