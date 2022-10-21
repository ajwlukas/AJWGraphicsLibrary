#include "pch_dx_11.h"
#include "Transform.h"

#include "JWMath.h"
//#include <directxmath.h>

Vector3 Transform::WorldUp = { 0,1,0,0 };
Vector3 Transform::WorldRight = { 1,0,0,0 };
Vector3 Transform::WorldForward = { 0,0,1,0 };
Vector3 Transform::W = { 0,0,0,1 };

Transform::Transform()
	:pos({ 0,0,0 }), rot({ 0,0,0 }), scale({ 1,1,1 }), S(XMMatrixIdentity()), R(XMMatrixIdentity()), T(XMMatrixIdentity()),
	parent(nullptr), local(XMMatrixIdentity()), relateS(true), relateR(true), relateT(true)
{
	D3D11_BUFFER_DESC cbd;
	cbd.Usage = D3D11_USAGE_DYNAMIC;
	cbd.ByteWidth = sizeof(Data);
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbd.MiscFlags = 0;
	cbd.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA initData;
	initData.pSysMem = &world;
	RESOURCES->buffers->Create(worldBuffer, cbd, &initData);
}

Transform::~Transform()
{
}

void Transform::UpdateWorld()
{
	S = XMMatrixScalingFromVector(XMLoadFloat4(scale));
	R = XMMatrixRotationRollPitchYawFromVector(XMLoadFloat4(rot));
	T = XMMatrixTranslationFromVector(XMLoadFloat4(pos));

	worldRotQuat = XMQuaternionRotationRollPitchYawFromVector(rot);


	local = S * R * T;

	world.data = local ;

	////todo: 임시로 막아 둠
	Transform* child = this;
	Transform* p = parent;
	while (p != nullptr)
	{
		p->UpdateWorld();

		if(child->relateS)
			world.data *= p->S;
		if(child->relateR)
			world.data *= p->R;
		if(child->relateT)
			world.data *= p->T;

		child = p;
		p = p->parent;
	}
	SaveWorldIngredient();
}

void Transform::SaveWorldIngredient()
{
	DecomposeMatrix(world.data, worldPos, worldRot, worldScale);
}

void Transform::DecomposeMatrix(Matrix& m,OUT Vector3& pos, OUT Vector3& rot,OUT Vector3& scale)
{
	XMVECTOR p, r, s;
	XMMatrixDecompose(&s, &r,
		&p, m);

	XMStoreFloat4(pos, p);
	JWMath::QuatToEuler(rot.x, rot.y, rot.z, move(r.m128_f32[0]), move(r.m128_f32[1]), move(r.m128_f32[2]), move(r.m128_f32[3]));
	XMStoreFloat4(scale, s);
}

void Transform::DecomposeMatrix(Matrix& m, OUT Vector3& pos, OUT SimpleMath::Quaternion& rot, OUT Vector3& scale)
{
	XMVECTOR p, r, s;
	XMMatrixDecompose(&s, &r,
		&p, m);


	XMStoreFloat4(pos, p);
	XMStoreFloat4(&rot, r);
	XMStoreFloat4(scale, s);
}

void Transform::SetWorldPos(Vector3 pos)
{
	worldPos = pos;

	UpdateWorldTransform();
}
void Transform::SetWorldPos(Vector3 pos, Vector3 offset)
{
	worldPos = pos;

	UpdateWorldTransform(offset);
}

void Transform::SetWorldRot(DirectX::SimpleMath::Quaternion quat)
{
	worldRotQuat = quat;

	JWMath::QuatToEuler(worldRot.x, worldRot.y, worldRot.z, move(worldRotQuat.x), move(worldRotQuat.y), move(worldRotQuat.z), move(worldRotQuat.w));

	UpdateWorldTransform();
}

void Transform::UpdateWorldTransform()
{
	scale = worldScale;
	rot = worldRot;
	pos = worldPos;

	if (parent == nullptr) return;

	Matrix worldS = XMMatrixScalingFromVector(XMLoadFloat4(worldScale));
	Matrix worldR = XMMatrixRotationQuaternion(worldRot);
	Matrix worldT = XMMatrixTranslationFromVector(XMLoadFloat4(worldPos));

	Matrix worldTM = worldS * worldR * worldT;

	Matrix parentTMInv = XMMatrixInverse (nullptr, *parent->World());

	Matrix localTM = worldTM * parentTMInv;
	DecomposeMatrix(localTM, pos, rot, scale);
}

void Transform::UpdateWorldTransform(Vector3 offset)
{
	if (parent == nullptr)
	{
		scale = worldScale;
		rot = worldRot;
		pos = worldPos - offset;

		return;
	}
	else
	{
		Matrix worldS = XMMatrixScalingFromVector(XMLoadFloat4(worldScale));
		Matrix worldR = XMMatrixRotationQuaternion(worldRot);
		Matrix worldT = XMMatrixTranslationFromVector(XMLoadFloat4(worldPos));

		Matrix worldTM = worldS * worldR * worldT;

		Matrix parentTMInv = XMMatrixInverse (nullptr, *parent->World());

		Matrix localTM = worldTM * parentTMInv;
		DecomposeMatrix(localTM, pos, rot, scale);

		pos -= offset;
	}

}

void Transform::LookAtOnlyY(Vector3 TargetPos)
{
	double temp_angle = atan2(pos.x - TargetPos.x, pos.z - TargetPos.z) * (180.0 / XM_PI);
	temp_angle += 180;
	float temp_rotation = (float)temp_angle * 0.0174532925f;
	
	rot.y = temp_rotation;
}