#pragma once

#include "Export.h"

#include "IMesh.h"
#include "IMaterial.h"
#include "IVertex.h"

#include "IConstantBuffer.h"
#include "ICamera.h"


namespace TL_Graphics
{
	class AJW_GRAPHICS_DLLEXPORT RenderSystem
	{
	public:
		static void Create();
		static void Delete();
		static RenderSystem* Get();

		virtual HRESULT Init() = 0;

		virtual void Clear() = 0;
		virtual void Draw() = 0;
		virtual void Present() = 0;

		virtual IMesh* CreateMesh(TL_Graphics::VertexSet& vertexSet, UINT indexData[], UINT indexCount, std::wstring fileName) = 0;

		virtual IMaterial* CreateMaterial(std::wstring fileName, const MaterialDesc& desc = MaterialDesc()) = 0;

		virtual IConstantBuffer* CreateConstantBuffer(UINT slot, void* data, size_t dataSize) = 0;

		virtual ICamera* CreateCamera() = 0;
	};
}