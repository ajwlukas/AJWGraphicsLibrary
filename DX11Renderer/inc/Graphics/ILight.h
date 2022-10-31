#pragma once

#include "Export.h"

namespace TL_Graphics
{
	__declspec(align(16)) struct AJW_GRAPHICS_DLLEXPORT DirectionalLight
	{
		float direction[3];
	};
	__declspec(align(16)) struct AJW_GRAPHICS_DLLEXPORT PointLight
	{
		float position[3];
		float range;

		float attenuation[3];
	};
	__declspec(align(16)) struct AJW_GRAPHICS_DLLEXPORT SpotLight
	{
		float position[3];
		float range;

		float direction[3];
		float spot;

		float attenuation[3];
	};


}