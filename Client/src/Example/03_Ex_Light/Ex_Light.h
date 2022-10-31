#pragma once

#include "Example\IExample.h"

#include "Graphics/RenderSystem.h"
#include "Graphics/IMesh.h"
#include "Graphics/IMaterial.h"
#include "Graphics/IVertex.h"
#include "Graphics\ICamera.h"
#include "Graphics\ILight.h"

#include "AjwCommon\Input.h"

#include "Helper\Transform.h"

class ajwCommon::Input;
class Ex_Light : public IExample
{
public:

	// IExample을(를) 통해 상속됨
	virtual void Init() override;
	virtual void UnInit() override;
	virtual void Update() override;

	ajwCommon::Input* input;

	TL_Graphics::IMesh* mesh;
	TL_Graphics::IMaterial* material;
	TL_Graphics::VertexSet vertexAttribute;


	TL_Graphics::ICamera* camera;
	Transform camT;
	void CameraMove();

	Transform boxT;
	TL_Graphics::IConstantBuffer* worldBuffer;
	void TransformMove();

	TL_Graphics::DirectionalLight directionalLight;
	TL_Graphics::IConstantBuffer* directionalLightBuffer;
};
