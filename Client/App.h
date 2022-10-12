#pragma once

#include "DX11Renderer.h"
#include "Mesh.h"
//#include "Material.h"
#include "Vertex.h"

typedef DX11Renderer RenderEngine;//todo : typedef CUSTOM_ENGINE engine
class App
{
public:
	App();
	~App();

	void Update();

	Mesh* mesh;
	//Material* material;
	VertexSet vertexAttribute;
	//RenderEngine* renderEngine;
};