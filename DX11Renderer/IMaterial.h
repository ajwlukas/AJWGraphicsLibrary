#pragma once

#include <string>
#include "Export.h"

namespace TL_Graphics
{
	struct AJW_GRAPHICS_DLLEXPORT MaterialDesc
	{
		float ambient[4] = { 0.8f, 0.8f, 0.8f, 1.0f };
		float diffuse[4];
		float specular[4];

		std::wstring diffuseFileName;
		std::wstring normalFileName;
	};

	class AJW_GRAPHICS_DLLEXPORT IMaterial
	{
	public:
		virtual void Set() = 0;
	};
}