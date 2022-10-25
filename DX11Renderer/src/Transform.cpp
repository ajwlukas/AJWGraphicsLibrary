#include "pch_dx_11.h"
#include "Transform.h"

#include "JWMath.h"

SimpleMath::Vector3 Transform::WorldUp = { 0,1,0 };
SimpleMath::Vector3 Transform::WorldRight = { 1,0,0 };
SimpleMath::Vector3 Transform::WorldForward = { 0,0,1};

Transform::Transform(ID3D11DeviceContext* dc, Resources* resources, Pipeline* pipeline)
	:pos( 0,0,0 ), rot( 0,0,0 ), scale( 1,1,1 ), S(XMMatrixIdentity()), R(XMMatrixIdentity()), T(XMMatrixIdentity()),
	parent(nullptr), local(XMMatrixIdentity())
{
	worldBuffer = new ConstantBuffer(dc, resources, pipeline, 1, &world, sizeof(Data));
}

Transform::~Transform()
{
	SAFE_DELETE(worldBuffer);
}

void Transform::UpdateWorld()
{
	S = XMMatrixScalingFromVector(XMLoadFloat3(&scale));
	R = XMMatrixRotationRollPitchYawFromVector(XMLoadFloat3(&rot));
	T = XMMatrixTranslationFromVector(XMLoadFloat3(&pos));
	worldRotQuat = XMQuaternionRotationRollPitchYawFromVector(rot);

	local = S * R * T;

	world.data = local ;

	Transform* p = parent;

	while (p != nullptr)
	{
		p->UpdateWorld();

		world.data *= p->S;
		world.data *= p->R;
		world.data *= p->T;

		p = p->parent;
	}


	//SaveWorldIngredient();
}

//void Transform::SaveWorldIngredient()
//{
//	DecomposeMatrix(world.data, worldPos, worldRot, worldScale);
//}

//void Transform::DecomposeMatrix(Matrix& m,OUT Vector3& pos, OUT Vector3& rot,OUT Vector3& scale)
//{
//	XMVECTOR p, r, s;
//	XMMatrixDecompose(&s, &r,
//		&p, m);
//
//	XMStoreFloat4(pos, p);
//	JWMath::QuatToEuler(rot.x, rot.y, rot.z, move(r.m128_f32[0]), move(r.m128_f32[1]), move(r.m128_f32[2]), move(r.m128_f32[3]));
//	XMStoreFloat4(scale, s);
//}
//
//void Transform::DecomposeMatrix(Matrix& m, OUT Vector3& pos, OUT SimpleMath::Quaternion& rot, OUT Vector3& scale)
//{
//	XMVECTOR p, r, s;
//	XMMatrixDecompose(&s, &r,
//		&p, m);
//
//
//	XMStoreFloat4(pos, p);
//	XMStoreFloat4(&rot, r);
//	XMStoreFloat4(scale, s);
//}
//
//void Transform::SetWorldPos(Vector3 pos)
//{
//	worldPos = pos;
//
//	UpdateWorldTransform();
//}
//void Transform::SetWorldPos(Vector3 pos, Vector3 offset)
//{
//	worldPos = pos;
//
//	UpdateWorldTransform(offset);
//}
//
//void Transform::SetWorldRot(DirectX::SimpleMath::Quaternion quat)
//{
//	worldRotQuat = quat;
//
//	JWMath::QuatToEuler(worldRot.x, worldRot.y, worldRot.z, move(worldRotQuat.x), move(worldRotQuat.y), move(worldRotQuat.z), move(worldRotQuat.w));
//
//	UpdateWorldTransform();
//}
//
//void Transform::UpdateWorldTransform()
//{
//	scale = worldScale;
//	rot = worldRot;
//	pos = worldPos;
//
//	if (parent == nullptr) return;
//
//	Matrix worldS = XMMatrixScalingFromVector(XMLoadFloat4(worldScale));
//	Matrix worldR = XMMatrixRotationQuaternion(worldRot);
//	Matrix worldT = XMMatrixTranslationFromVector(XMLoadFloat4(worldPos));
//
//	Matrix worldTM = worldS * worldR * worldT;
//
//	Matrix parentTMInv = XMMatrixInverse (nullptr, *parent->World());
//
//	Matrix localTM = worldTM * parentTMInv;
//	DecomposeMatrix(localTM, pos, rot, scale);
//}
//
//void Transform::UpdateWorldTransform(Vector3 offset)
//{
//	if (parent == nullptr)
//	{
//		scale = worldScale;
//		rot = worldRot;
//		pos = worldPos - offset;
//
//		return;
//	}
//	else
//	{
//		Matrix worldS = XMMatrixScalingFromVector(XMLoadFloat4(worldScale));
//		Matrix worldR = XMMatrixRotationQuaternion(worldRot);
//		Matrix worldT = XMMatrixTranslationFromVector(XMLoadFloat4(worldPos));
//
//		Matrix worldTM = worldS * worldR * worldT;
//
//		Matrix parentTMInv = XMMatrixInverse (nullptr, *parent->World());
//
//		Matrix localTM = worldTM * parentTMInv;
//		DecomposeMatrix(localTM, pos, rot, scale);
//
//		pos -= offset;
//	}
//
//}
//
//void Transform::LookAtOnlyY(Vector3 TargetPos)
//{
//	double temp_angle = atan2(pos.x - TargetPos.x, pos.z - TargetPos.z) * (180.0 / XM_PI);
//	temp_angle += 180;
//	float temp_rotation = (float)temp_angle * 0.0174532925f;
//	
//	rot.y = temp_rotation;
//}