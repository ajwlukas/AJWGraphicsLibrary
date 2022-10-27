#include "Camera.h"

constexpr float pi = 3.141592f;

Camera::Camera(UINT screenWidth, UINT screenHeight, float fov, float frustumNear , float frustumFar )
	:screenWidth(screenWidth)
	, screenHeight(screenHeight)
	, fov(fov)
	,frustumNear(frustumNear)
	,frustumFar(frustumFar)
{
	fovInRadian = pi / 180.0f * fov;

	data.view = DirectX::XMMatrixInverse(nullptr, transform.GetWorldMatrix());
	data.proj = DirectX::XMMatrixPerspectiveFovLH(fovInRadian, screenWidth / (float)screenHeight, frustumNear, frustumFar);
	data.camPos = transform.Pos();
}

Camera::~Camera()
{
}

void Camera::Update()
{
	transform.UpdateWorld();

	data.camPos = transform.Pos();
	data.view = DirectX::XMMatrixInverse(nullptr, transform.GetWorldMatrix());
}

//void Camera::Update(float m[4][4])
//{
//	//transform.UpdateWorld(); 없애고
//
//	//data.camPos = transform.Pos(); 없애지말자.
//	data.view = DirectX::XMMatrixInverse(nullptr, transform.GetWorldMatrix());
//}
//
//void OnResize()
//{
//
//}
