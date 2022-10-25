#pragma once

#include "Example\IExample.h"

#include "Graphics/RenderSystem.h"

class Ex_BoxCamera : public IExample
{
public:
	Ex_BoxCamera();
	~Ex_BoxCamera();


	// IExample을(를) 통해 상속됨
	virtual void Init() override;
	virtual void UnInit() override;
	virtual void Update() override;

	TL_Graphics::IMesh* mesh;
	TL_Graphics::IMaterial* material;
	TL_Graphics::IConstantBuffer* constantBuffer;
	TL_Graphics::VertexSet vertexAttribute;
};