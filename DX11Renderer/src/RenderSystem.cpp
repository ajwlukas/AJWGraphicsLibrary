#include "pch_dx_11.h"
#include "RenderSystem.h"

#include "DX11Renderer.h"

namespace TL_Graphics
{
	DX11Renderer* instance;

	void RenderSystem::Create()
	{
		instance = new DX11Renderer();
	}

	void RenderSystem::Delete()
	{
		SAFE_DELETE(instance);
	}

	RenderSystem* RenderSystem::Get()
	{
		return instance;
	}
}