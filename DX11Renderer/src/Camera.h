#pragma once

#include "ConstantBuffer.h"
#include "Transform.h"

class Camera
{
public:
	Camera(ID3D11DeviceContext* dc, Resources* resources, Pipeline* pipeline, float fov = 80.0f, UINT screenWidth = 100, UINT screenHeight = 100, float frustumNear = 1.0f, float frustumFar = 2000.0f);
	~Camera();
	
	void Set();
	void Update();

	void Update(float pos[3], float rot[3]);

	void OnResize(UINT height, UINT width);

	//void ScreenPointToRay(IN UINT screenX, UINT screenY, OUT Vector3& rayPos, OUT Vector3& dir);

private:
	struct Data
	{
		Matrix view;
		Matrix proj;
		float3 camPos;
	}viewproj;

	ConstantBuffer* viewprojBuffer;

	Transform transform;
	Matrix view, proj;

	float fov;//½Ã¾ß°¢
	float fovInRadian;
	UINT screenWidth;
	UINT screenHeight;
	float frustumNear;
	float frustumFar;
};