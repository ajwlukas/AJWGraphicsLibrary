#pragma once

#include "Export.h"

#include "IMesh.h"
#include "IMaterial.h"
#include "Mesh.h"
#include "Material.h"

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

		virtual IMesh* CreateMesh(TL_Graphics::VertexSet& vertexSet, UINT indexData[], UINT indexCount,
			std::wstring vsFileName = L"UVLightVertex.hlsl", D3D_PRIMITIVE_TOPOLOGY topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST) = 0;

		virtual IMaterial* CreateMaterial(const MaterialDesc& desc = MaterialDesc()) = 0;
	};
}