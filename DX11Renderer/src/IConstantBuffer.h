#pragma once

#include "Export.h"

namespace TL_Graphics
{
	class AJW_GRAPHICS_DLLEXPORT IConstantBuffer
	{
	public:
		virtual void Set() = 0;
		virtual void Update(void* data, size_t dataSize) = 0;
	};
}