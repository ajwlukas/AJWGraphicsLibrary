#pragma once

#include "DXTK\SimpleMath.h"
#include <DirectXMath.h>

class Transform
{
public:
	Transform();
	~Transform();

	void UpdateWorld();

	DirectX::SimpleMath::Matrix& GetWorldMatrix();

	DirectX::SimpleMath::Vector3& Pos();
	DirectX::SimpleMath::Vector3& Rot();
	DirectX::SimpleMath::Vector3& Scale();

	const DirectX::SimpleMath::Vector3& PosW();
	const DirectX::SimpleMath::Vector3& RotW();
	const DirectX::SimpleMath::Vector3& ScaleW();

	const DirectX::SimpleMath::Vector3& Up();
	const DirectX::SimpleMath::Vector3& Right();
	const DirectX::SimpleMath::Vector3& Forward();
private:
	DirectX::SimpleMath::Vector3 pos, rot, scale;

	DirectX::SimpleMath::Vector3 posW, rotW, scaleW;
	DirectX::SimpleMath::Quaternion quatW;

	DirectX::SimpleMath::Vector3 up, right, forward;

	DirectX::SimpleMath::Matrix local, S, R, T;
	DirectX::SimpleMath::Matrix world;

	Transform* parent;

	const static DirectX::SimpleMath::Vector3 WorldUp, WorldRight, WorldForward;
};

inline DirectX::SimpleMath::Matrix& Transform::GetWorldMatrix()
{ 
	 return world; 
}

inline DirectX::SimpleMath::Vector3& Transform::Pos()
{
	return pos;
}
inline DirectX::SimpleMath::Vector3& Transform::Rot()
{
	return rot;
}
inline DirectX::SimpleMath::Vector3& Transform::Scale()
{
	return scale;
}

inline const DirectX::SimpleMath::Vector3& Transform::PosW()
{
	return posW;
}

inline const DirectX::SimpleMath::Vector3& Transform::RotW()
{
	return rotW;
}

inline const DirectX::SimpleMath::Vector3& Transform::ScaleW()
{
	return scaleW;
}

inline const DirectX::SimpleMath::Vector3& Transform::Up()
{
	XMStoreFloat3(&up, XMVector4Transform(WorldUp, world));
	up.Normalize();
	return  up;
}

inline const DirectX::SimpleMath::Vector3& Transform::Right()
{
	XMStoreFloat3(&right, XMVector4Transform(WorldRight, world));
	right.Normalize();
	return  right;
}

inline const DirectX::SimpleMath::Vector3& Transform::Forward()
{
	XMStoreFloat3(&forward, XMVector4Transform(WorldForward, world));
	forward.Normalize();
	return  forward;
}