#pragma once

#include "ICamera.h"

#include "OnResize.h"

#include "DXTK/SimpleMath.h"
#include "Transform.h"
#include "ConstantBuffer.h"

class Camera : public TL_Graphics::ICamera, public OnResize_Observer
{
public:
	Camera(ID3D11DeviceContext* dc, Resources* resources, Pipeline* pipeline, OnResizeNotice* resizeNotice, float fov = 80.0f, UINT screenWidth = 100, UINT screenHeight = 100, float frustumNear = 1.0f, float frustumFar = 2000.0f);
	~Camera();
	
	virtual void Set() override;
	virtual void Update(SimpleMath::Vector3 pos, SimpleMath::Vector3 rot) override;
	virtual void Update(SimpleMath::Matrix m) override;

private:

	__declspec(align(16)) struct Data
	{
		SimpleMath::Matrix view;
		SimpleMath::Matrix  proj;
		SimpleMath::Vector3 camPos;
	}data;

	ConstantBuffer* viewprojBuffer;

	float fov;//시야각
	float fovInRadian;
	UINT screenWidth;
	UINT screenHeight;
	float frustumNear;
	float frustumFar;

	//보류
	virtual void OnResize(UINT width, UINT height) override;
};