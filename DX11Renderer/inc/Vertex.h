#pragma once

#include "IVertex.h"

class TL_Graphics::VertexSet::Impl
{
public:
	void* GetVerticesData() { return verticesData.data(); }
	UINT GetVerticesSize() { return verticesData.size() * sizeof(DWORD); }
	UINT GetVertexSize() { return stride; }

	D3D11_INPUT_ELEMENT_DESC* GetDescsData() { return descs.data(); }
	UINT GetDescsSize() { return descs.size(); }

private:
	friend class TL_Graphics::VertexSet;
	std::vector<DWORD> verticesData;//실제 버텍스들의 데이터
	UINT memIndex;

	std::vector<D3D11_INPUT_ELEMENT_DESC> descs;
	UINT stride;//버텍스 하나의 크기

	std::string semanticString;
	//static ShaderNameFinder shaderFinder;//인풋 성분에 따라 알맞은 기본 쉐이더의 이름을 주게
};
