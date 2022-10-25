#pragma once

#include "Export.h"

namespace TL_Graphics
{
	class AJW_GRAPHICS_DLLEXPORT ICamera
	{
	public:
		virtual void Set() = 0;
		virtual void Update(float pos[3], float rot[3]) = 0;
	};
}