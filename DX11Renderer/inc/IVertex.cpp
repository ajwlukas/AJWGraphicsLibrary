#include "pch_dx_11.h"

#include "IVertex.h"

#include <d3d11.h>
#include <assert.h>

#include "Vertex.h"

namespace TL_Graphics
{
	DXGI_FORMAT GetCorrectFormat(UINT dataCount, TL_Graphics::DataType type)
	{
		switch (type)
		{
		case TL_Graphics::DataType::FLOAT:
		{
			switch (dataCount)
			{
			case 1:
				return DXGI_FORMAT_R32_FLOAT;
			case 2:
				return DXGI_FORMAT_R32G32_FLOAT;
			case 3:
				return DXGI_FORMAT_R32G32B32_FLOAT;
			case 4:
				return DXGI_FORMAT_R32G32B32A32_FLOAT;
			default:
				assert(false);
			}
		}
		case TL_Graphics::DataType::UINT:
		{
			switch (dataCount)
			{
			case 1:
				return DXGI_FORMAT_R32_UINT;
			case 2:
				return DXGI_FORMAT_R32G32_UINT;
			case 3:
				return DXGI_FORMAT_R32G32B32_UINT;
			case 4:
				return DXGI_FORMAT_R32G32B32A32_UINT;
			default:
				assert(false);
			}
		}

		default:
			assert(false);
		}
	}

	VertexSet::VertexSet()
	{
		pimpl = new Impl();
	}

	VertexSet::~VertexSet()
	{
		SAFE_DELETE(pimpl);
	}

	void VertexSet::AddElementToDesc(UINT dataSize, TL_Graphics::DataType type, LPCSTR SemanticName, int SemanticIndex,
		int inputSlot, int InstanceDataStepRate)
	{
		UINT dataCount = dataSize / sizeof(DWORD);

		//FillDesc
		D3D11_INPUT_ELEMENT_DESC desc;
		desc.SemanticName = SemanticName;
		desc.SemanticIndex = SemanticIndex;
		desc.Format = GetCorrectFormat(dataCount, type);
		desc.InputSlot = inputSlot;
		desc.AlignedByteOffset = pimpl->stride;
		desc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;//todo : 나중에 수정 가능
		desc.InstanceDataStepRate = InstanceDataStepRate;

		pimpl->descs.emplace_back(desc);

		pimpl->stride += 4 * dataCount;//4바이트 단위 데이터만 받을 거임

		//쉐이더 서치용 Semantic 정보 저장
		pimpl->semanticString += "_";
		pimpl->semanticString += SemanticName;
	}

	void VertexSet::AddData(void* data, UINT dataSize)
	{

		UINT dataCount = dataSize / sizeof(DWORD);
		//FillData
		pimpl->verticesData.resize(pimpl->verticesData.size() + dataCount);
		memcpy(pimpl->verticesData.data() + pimpl->memIndex, data, sizeof(DWORD) * dataCount);

		pimpl->memIndex += dataCount;
	}

}