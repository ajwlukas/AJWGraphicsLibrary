#pragma once

#include "RenderSystem.h"
#include "IMesh.h"
#include "IMaterial.h"

#include "Mesh.h"
#include "Material.h"
#include "Vertex.h"

typedef DX11Renderer RenderEngine;//todo : typedef CUSTOM_ENGINE engine
class App
{
public:
	App();
	~App();

	void Update();

	TL_Graphics::IMesh* mesh;
	TL_Graphics::IMaterial* material;
	VertexSet vertexAttribute;
	//RenderEngine* renderEngine;
};