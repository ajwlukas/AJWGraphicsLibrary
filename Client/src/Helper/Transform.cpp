#include "Transform.h"

const DirectX::SimpleMath::Vector3 Transform::WorldUp = { 0,1,0 };
const DirectX::SimpleMath::Vector3 Transform::WorldRight = { 1,0,0 };
const DirectX::SimpleMath::Vector3 Transform::WorldForward = { 0,0,1 };

Transform::Transform()
	:pos(0, 0, 0), rot(0, 0, 0), scale(1, 1, 1), S(DirectX::XMMatrixIdentity()), R(DirectX::XMMatrixIdentity()), T(DirectX::XMMatrixIdentity()),
	parent(nullptr), local(DirectX::XMMatrixIdentity())
{

}

Transform::~Transform()
{
}

void Transform::UpdateWorld()
{
	S = DirectX::XMMatrixScalingFromVector(XMLoadFloat3(&scale));
	R = DirectX::XMMatrixRotationRollPitchYawFromVector(XMLoadFloat3(&rot));
	T = DirectX::XMMatrixTranslationFromVector(XMLoadFloat3(&pos));
	quatW = XMQuaternionRotationRollPitchYawFromVector(rot);

	local = S * R * T;

	world = local;

	Transform* p = parent;

	while (p != nullptr)
	{
		p->UpdateWorld();

		world *= p->S;
		world *= p->R;
		world *= p->T;

		p = p->parent;
	}
}