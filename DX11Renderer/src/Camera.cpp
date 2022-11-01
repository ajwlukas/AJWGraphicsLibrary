#include "pch_dx_11.h"
#include "Camera.h"

constexpr float pi  = 3.141592f;

Camera::Camera(ID3D11DeviceContext* dc, Resources* resources, Pipeline* pipeline, OnResizeNotice* resizeNotice, float fov, UINT screenWidth, UINT screenHeight, float frustumNear, float frustumFar)
	:data{}
	,fov(fov)
	, screenWidth(screenWidth)
	, screenHeight(screenHeight)
	,frustumNear(frustumNear)
	,frustumFar(frustumFar)
{
	fovInRadian = pi / 180.0f * fov;
	
	resizeNotice->AddObserver(this);

	data.view = XMMatrixInverse(nullptr, XMMatrixIdentity());
	data.proj = XMMatrixPerspectiveFovLH(fovInRadian, screenWidth / (float)screenHeight, frustumNear, frustumFar);

	data.camPos = { 0,0,0 };

	viewprojBuffer = new ConstantBuffer(dc, resources, pipeline, 0, TL_Graphics::E_SHADER_TYPE::VS, &data, sizeof(Data));
}

Camera::~Camera()
{
	SAFE_DELETE(viewprojBuffer);
}

void Camera::Set()
{
	viewprojBuffer->Set();
}

void Camera::Update(SimpleMath::Vector3 pos, SimpleMath::Vector3 rot)
{
	SimpleMath::Matrix R = DirectX::XMMatrixRotationRollPitchYawFromVector(rot);
	SimpleMath::Matrix T = DirectX::XMMatrixTranslationFromVector(pos);

	SimpleMath::Matrix m = XMMatrixIdentity();

	m *= R;
	m *= T;

	data.view = XMMatrixInverse(nullptr, m);

	data.camPos = pos;

	viewprojBuffer->Update(&data, sizeof(Data));
}

void Camera::Update(SimpleMath::Matrix m)
{
	data.view = XMMatrixInverse(nullptr, m);

	XMVECTOR p, r, s;

	XMMatrixDecompose(&s, &r, &p, m);

	XMStoreFloat3(&data.camPos, p);

	viewprojBuffer->Update(&data, sizeof(Data));
}

void Camera::OnResize(UINT width, UINT height)
{
	screenWidth = width;
	screenHeight = height;

	data.proj = XMMatrixPerspectiveFovLH(fovInRadian, width / (float)height, frustumNear, frustumFar);

	viewprojBuffer->Update(&data, sizeof(Data));
}

