#include "pch_dx_11.h"
#include "Camera.h"

constexpr float pi  = 3.141592f;

Camera::Camera(ID3D11DeviceContext* dc, Resources* resources, Pipeline* pipeline, float fov, UINT screenWidth, UINT screenHeight, float frustumNear, float frustumFar)
	:data{}
	, view{}
	, proj{}
	,fov(80)
	, screenWidth(screenWidth)
	, screenHeight(screenHeight)
	,frustumNear(frustumNear)
	,frustumFar(frustumFar)
{
	fovInRadian = pi / 180.0f * fov;

	transform = new Transform(dc, resources, pipeline);

	view = XMMatrixInverse(nullptr, transform->GetWorldMatrix());
	proj = XMMatrixPerspectiveFovLH(fovInRadian, screenWidth / (float)screenHeight, frustumNear, frustumFar);

	data.view = view;
	data.proj = proj;
	data.camPos = transform->pos;

	viewprojBuffer = new ConstantBuffer(dc, resources, pipeline, 0, &data, sizeof(Data));
}

Camera::~Camera()
{
	SAFE_DELETE(viewprojBuffer);
	SAFE_DELETE(transform);
}

void Camera::Set()
{
	viewprojBuffer->Set();
}

void Camera::Update(float pos[3], float rot[3])
{
	transform->pos.x = pos[0];
	transform->pos.y = pos[1];
	transform->pos.z = pos[2];

	transform->rot.x = rot[0];
	transform->rot.y = rot[1];
	transform->rot.z = rot[2];

	transform->UpdateWorld();
	view = XMMatrixInverse(nullptr, transform->GetWorldMatrix());

	data.camPos = transform->pos;
	data.view = view;

	viewprojBuffer->Update(&data, sizeof(Data));
}

void Camera::Update()
{
	transform->UpdateWorld();
	data.camPos = transform->pos;
	view = XMMatrixInverse(nullptr, transform->GetWorldMatrix());

	data.view = view;

	viewprojBuffer->Update(&data, sizeof(Data));
}

void Camera::OnResize(UINT height, UINT width)
{
	screenWidth = width;
	screenHeight = height;

	proj = XMMatrixPerspectiveFovLH(fovInRadian, width / (float)height, frustumNear, frustumFar);

	data.proj = proj;
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

