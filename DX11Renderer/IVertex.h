#pragma once

#include <Windows.h>
#include <string>
#include <vector>
#include <unordered_map>

#include "Export.h"

namespace TL_Graphics
{
	enum class AJW_GRAPHICS_DLLEXPORT DataType
	{
		FLOAT,
		UINT
	};

	class AJW_GRAPHICS_DLLEXPORT VertexSet//저절로 만드는 버텍스 만드는 테스트 구조
	{
	public:
		VertexSet();
		~VertexSet();

		void AddElementToDesc(UINT dataSize, TL_Graphics::DataType type,
			LPCSTR  SemanticName, int SemanticIndex = 0,
			int inputSlot = 0, int InstanceDataStepRate = 0);
		//주의 : Element 넣은 순서로 데이터를 넣어주어야함

		void AddData(void* data, UINT dataSize);
		//주의 : 4바이트짜리 데이터 셋만 넣어야 함!! ex)float, int, float3, float4 등등, bool, long, short 지원x
		// 데이터 시각화 예시 : vertex0.pos.x | vertex0.pos.y | vertex0.pos.z | vertex0.uv.u | vertex0.uv.v | vertex1.pos.x ...


#ifdef AJW_GRAPHICS
	public:
#else
	private:
#endif
		class Impl;
		Impl* pimpl;
	};

}