#pragma once

#include "RenderSystem.h"
#include "IMesh.h"
#include "IMaterial.h"
#include "IVertex.h"

typedef DX11Renderer RenderEngine;//todo : typedef CUSTOM_ENGINE engine
class App
{
public:
	App();
	~App();

	void Update();

	TL_Graphics::IMesh* mesh;
	TL_Graphics::IMaterial* material;
	TL_Graphics::VertexSet vertexAttribute;
	//RenderEngine* renderEngine;
};