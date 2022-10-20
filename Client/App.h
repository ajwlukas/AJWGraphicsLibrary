#pragma once

#include "RenderSystem.h"
#include "IMesh.h"
#include "IMaterial.h"
#include "IVertex.h"


class App
{
public:
	App();
	~App();

	void Update();

	TL_Graphics::IMesh* mesh;
	TL_Graphics::IMaterial* material;
	TL_Graphics::VertexSet vertexAttribute;
};