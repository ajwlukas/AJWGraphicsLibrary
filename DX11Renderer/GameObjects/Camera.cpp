#include "pch_dx_11.h"
#include "Camera.h"

constexpr float pi  = 3.141592f;

Camera::Camera()
	:viewproj{}, view{}, proj{}, fovInDegree(80), bMovable(true), camMovSpeed(100.0f), camRotSpeed(0.01f)
{
	fov = pi / 180.0f * fovInDegree;

	view = XMMatrixInverse(nullptr, *(transform.World()));
	proj = XMMatrixPerspectiveFovLH(fov, ((float)DX->width / (float)DX->height),1.0f, 2000.0f);

	viewproj.view = view;
	viewproj.proj = proj;

	transform.pos = { 0,100, -50 };
	viewproj.camPos = transform.pos;

	D3D11_BUFFER_DESC cbd = {};
	cbd.Usage = D3D11_USAGE_DYNAMIC;
	cbd.ByteWidth = sizeof(Data);
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbd.MiscFlags = 0;
	cbd.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA initData;
	ZeroMemory(&initData, sizeof(D3D11_SUBRESOURCE_DATA));
	initData.pSysMem = &viewproj;
	HRESULT hr = DEVICE->CreateBuffer(&cbd, &initData, &viewprojBuffer);

	DC->VSSetConstantBuffers(1, 1, &viewprojBuffer);
}

Camera::~Camera()
{
}

void Camera::Update()
{
	//if (bMovable)
	//	Move();

	transform.UpdateWorld();
	viewproj.camPos = transform.pos;
	view = XMMatrixInverse(nullptr, *(transform.World()));
	viewproj.view = view;
}

void Camera::Render()
{


	D3D11_MAPPED_SUBRESOURCE mappedResource;
	ZeroMemory(&mappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));

	DC->Map(viewprojBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	// Copy Resource Data..
	memcpy(mappedResource.pData, &viewproj, sizeof(viewproj));

	// GPU Access UnLock Buffer Data..
	DC->Unmap(viewprojBuffer, 0);



	DC->VSSetConstantBuffers(1, 1, &viewprojBuffer);
}

void Camera::OnResize(UINT height, UINT width)
{
	proj = XMMatrixPerspectiveFovLH(fov, width / (float)height, 1.0f, 1000.0f);

	viewproj.proj = proj;
}

void Camera::Move()
{
	if (KeyBoard::Get()->Press(VK_LSHIFT))
	{
		if (KeyBoard::Get()->Press(VK_LBUTTON))
		{
			transform.rot.y += KeyBoard::Get()->mouseDx * camRotSpeed;
			transform.rot.x += KeyBoard::Get()->mouseDy * camRotSpeed;
		}

		Vector3 way;
		way.w = 0.0f;
	
		if (KeyBoard::Get()->Press('D'))
			way.x += camMovSpeed;
		if (KeyBoard::Get()->Press('A'))
			way.x -= camMovSpeed;
		if (KeyBoard::Get()->Press('W'))
			way.z += camMovSpeed;
		if (KeyBoard::Get()->Press('S'))
			way.z -= camMovSpeed;
		if (KeyBoard::Get()->Press('E'))
			way.y += camMovSpeed;
		if (KeyBoard::Get()->Press('Q'))
			way.y -= camMovSpeed;

		transform.pos += way * *(transform.World()) * TIME->Delta();
	}
}

void Camera::ScreenPointToRay(IN UINT screenX, UINT screenY, OUT Vector3& rayPos, OUT Vector3& dir)
{
	struct Float2
	{
		float x;
		float y;
	};

	Float2 point;

	point.x = ((2 * screenX) / (float)DX->width) - 1.0f;
	point.y = (((2 * screenY) /(float) DX->height) - 1.0f) * -1.0f;


	point.x /= proj.r[0].m128_f32[0];
	point.y /= proj.r[1].m128_f32[1];

	rayPos = transform.worldPos;

	Matrix invView = *transform.World();

	XMVECTOR tempPos = { point.x, point.y, 1.0f };

	XMStoreFloat4(dir, XMVector3TransformNormal(tempPos, invView));
	dir.Normalize();
}

