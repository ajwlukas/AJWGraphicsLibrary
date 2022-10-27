#pragma once

#include "DXTK/SimpleMath.h"
#include "Transform.h"

class Camera
{
public:
	Camera(UINT screenWidth = 100, UINT screenHeight = 100, float fov = 80.0f, float frustumNear = 1.0f, float frustumFar = 2000.0f);
	~Camera();

	void Update();


private:
	__declspec(align(16)) struct Data
	{
		DirectX::SimpleMath::Matrix view;
		DirectX::SimpleMath::Matrix  proj;
		DirectX::SimpleMath::Vector3 camPos;
	};


	float fov;//시야각
	float fovInRadian;
	UINT screenWidth;
	UINT screenHeight;
	float frustumNear;
	float frustumFar;

	//보류
	void OnResize(UINT height, UINT width);

public:
	Transform transform;
	Data data; 
};