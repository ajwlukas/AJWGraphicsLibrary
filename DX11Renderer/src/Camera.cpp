#include "pch_dx_11.h"
#include "Camera.h"

constexpr float pi  = 3.141592f;

Camera::Camera(ID3D11DeviceContext* dc, Resources* resources, Pipeline* pipeline, float fov, UINT screenWidth, UINT screenHeight, float frustumNear, float frustumFar)
	:data{}
	,fov(fov)
	, screenWidth(screenWidth)
	, screenHeight(screenHeight)
	,frustumNear(frustumNear)
	,frustumFar(frustumFar)
{
	fovInRadian = pi / 180.0f * fov;

	data.view = XMMatrixInverse(nullptr, XMMatrixIdentity());
	data.proj = XMMatrixPerspectiveFovLH(fovInRadian, screenWidth / (float)screenHeight, frustumNear, frustumFar);

	data.camPos = { 0,0,0 };

	viewprojBuffer = new ConstantBuffer(dc, resources, pipeline, 0, &data, sizeof(Data));
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

void Camera::OnResize(UINT height, UINT width)
{
	screenWidth = width;
	screenHeight = height;

	data.proj = XMMatrixPerspectiveFovLH(fovInRadian, width / (float)height, frustumNear, frustumFar);
}


//
//void Camera::ScreenPointToRay(IN UINT screenX, UINT screenY, OUT Vector3& rayPos, OUT Vector3& dir)
//{
//	struct Float2
//	{
//		float x;
//		float y;
//	};
//
//	Float2 point;
//
//	point.x = ((2 * screenX) / (float)DX->width) - 1.0f;
//	point.y = (((2 * screenY) /(float) DX->height) - 1.0f) * -1.0f;
//
//
//	point.x /= proj.r[0].m128_f32[0];
//	point.y /= proj.r[1].m128_f32[1];
//
//	rayPos = transform.worldPos;
//
//	Matrix invView = *transform.World();
//
//	XMVECTOR tempPos = { point.x, point.y, 1.0f };
//
//	XMStoreFloat4(dir, XMVector3TransformNormal(tempPos, invView));
//	dir.Normalize();
//}

