#pragma once

#include "DXTK\SimpleMath.h"
#include <DirectXMath.h>

class Transform
{
public:
	Transform();
	~Transform();

	void UpdateWorld();//외부용, 패런트가 없는 애들만 호출 의미 있음 자식들 순회하며 업데이트하기위해

	DirectX::SimpleMath::Matrix GetWorldMatrix() { return world.data; }

private:
	DirectX::SimpleMath::Matrix local, S, R, T;
	Transform* parent;

	struct Data
	{
		Data()
		{
			data = XMMatrixIdentity();
		}
		DirectX::SimpleMath::Matrix data;
	}world;


public:
	DirectX::SimpleMath::Vector3 up, right, forward;


	static DirectX::SimpleMath::Vector3 WorldUp, WorldRight, WorldForward;
	DirectX::SimpleMath::Vector3& Up() {
		XMStoreFloat3(&up, XMVector3Transform(WorldUp, world.data));
		up.Normalize();
		return  up;
	}
	DirectX::SimpleMath::Vector3& Right() {
		XMStoreFloat3(&right, XMVector4Transform(WorldRight, world.data));
		right.Normalize();
		return  right;
	}
	DirectX::SimpleMath::Vector3& Forward() {
		XMStoreFloat3(&forward, XMVector4Transform(WorldForward, world.data));
		forward.Normalize();
		return  forward;
	}

	DirectX::SimpleMath::Vector3 pos;
	DirectX::SimpleMath::Vector3 rot;
	DirectX::SimpleMath::Vector3 scale;

	DirectX::SimpleMath::Vector3 worldPos;
	DirectX::SimpleMath::Vector3 worldRot;
	DirectX::SimpleMath::Quaternion worldRotQuat;
	DirectX::SimpleMath::Vector3 worldScale;

	//void SaveWorldIngredient();

	/*void DecomposeMatrix(SimpleMath::Matrix& m, OUT SimpleMath::Vector3& pos, OUT SimpleMath::Vector3& rot, OUT SimpleMath::Vector3& scale);
	void DecomposeMatrix(SimpleMath::Matrix& m, OUT SimpleMath::Vector3& pos, OUT SimpleMath::Quaternion& rot, OUT SimpleMath::Vector3& scale);*/



	//public:
	//	void SetWorldPos(SimpleMath::Vector3 pos);
	//	void SetWorldPos(SimpleMath::Vector3 pos, SimpleMath::Vector3 offset);//이상한 코드 쓰지 말 것
	//	void SetWorldRot(DirectX::SimpleMath::Quaternion quat);
	//	void LookAtOnlyY(SimpleMath::Vector3 TargetPos);
	//
	//private:
	//	void UpdateWorldTransform();
	//	void UpdateWorldTransform(SimpleMath::Vector3 offset);
};