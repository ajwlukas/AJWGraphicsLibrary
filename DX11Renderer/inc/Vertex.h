#pragma once

#include <Windows.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <d3d11.h>

#include "IVertex.h"

namespace TL_Graphics
{
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
		void AddElementToDesc(UINT dataSize, TL_Graphics::DataType type,
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

		/*std::wstring GetCorrespondingShaderFileName() { return shaderFinder.Find(semanticString); }*/
	private:
		class Impl;
		Impl* pimpl;

		std::vector<DWORD> verticesData;//���� ���ؽ����� ������
		UINT memIndex;

		std::vector<D3D11_INPUT_ELEMENT_DESC> descs;
		UINT stride;//���ؽ� �ϳ��� ũ��

		std::string semanticString;
		//static ShaderNameFinder shaderFinder;//��ǲ ���п� ���� �˸��� �⺻ ���̴��� �̸��� �ְ�
	};

}