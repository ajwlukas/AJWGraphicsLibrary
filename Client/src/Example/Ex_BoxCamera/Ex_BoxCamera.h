#pragma once

#include "Example\IExample.h"

#include "Graphics/RenderSystem.h"
#include "Graphics/IMesh.h"
#include "Graphics/IMaterial.h"
#include "Graphics/IVertex.h"
#include "Graphics\ICamera.h"

#include "AjwCommon\Input.h"

#include "Helper\Transform.h"
#include "Helper\Camera.h"

//struct CamInfo
//{
//	float pos[3];
//	float rot[3];
//};
class ajwCommon::Input;
class Ex_BoxCamera : public IExample
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

	
	/*TL_Graphics::ICamera* camera;
	struct CamInfo camInfo;*/
	Camera* cam;
	TL_Graphics::IConstantBuffer* cameraBuffer;
	void CameraMove();

	Transform t;
	TL_Graphics::IConstantBuffer* worldBuffer;
	void TransformMove();
};
