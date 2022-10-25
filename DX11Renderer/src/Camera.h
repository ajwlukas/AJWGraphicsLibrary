#pragma once

#include "ICamera.h"

#include "DXTK/SimpleMath.h"
#include "Transform.h"
#include "ConstantBuffer.h"

class Camera : public TL_Graphics::ICamera
{
public:
	Camera(ID3D11DeviceContext* dc, Resources* resources, Pipeline* pipeline, float fov = 80.0f, UINT screenWidth = 100, UINT screenHeight = 100, float frustumNear = 1.0f, float frustumFar = 2000.0f);
	~Camera();
	
	virtual void Set() override;
	virtual void Update(float pos[3], float rot[3]) override;

private:
	struct Data
	{
		SimpleMath::Matrix view;
		SimpleMath::Matrix  proj;
		SimpleMath::Vector3 camPos;
	}data;

	ConstantBuffer* viewprojBuffer;

	Transform* transform;
	SimpleMath::Matrix view, proj;

	float fov;//시야각
	float fovInRadian;
	UINT screenWidth;
	UINT screenHeight;
	float frustumNear;
	float frustumFar;

	//보류
	void Update();
	void OnResize(UINT height, UINT width);

	//void ScreenPointToRay(IN UINT screenX, UINT screenY, OUT Vector3& rayPos, OUT Vector3& dir);
};