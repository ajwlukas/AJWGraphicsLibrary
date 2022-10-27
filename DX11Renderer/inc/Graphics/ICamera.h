#pragma once

#include "Export.h"

namespace DirectX
{
	namespace SimpleMath
	{
		struct Vector3;
		struct Matrix;
	}
}

namespace TL_Graphics
{
	class AJW_GRAPHICS_DLLEXPORT ICamera
	{
	public:
		virtual void Set() = 0;
		virtual void Update(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 rot) = 0;
		virtual void Update(DirectX::SimpleMath::Matrix m) = 0;
	};
}