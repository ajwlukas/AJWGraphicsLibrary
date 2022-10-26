#pragma once

#include "ConstantBuffer.h"
#include "DXTK/SimpleMath.h"

class Transform
{
public:
	Transform(ID3D11DeviceContext* dc, Resources* resources, Pipeline* pipeline);
	~Transform();

	void UpdateWorld();//외부용, 패런트가 없는 애들만 호출 의미 있음 자식들 순회하며 업데이트하기위해

	SimpleMath::Matrix GetWorldMatrix() { return world.data; }

private:
	SimpleMath::Matrix local, S, R, T;
	Transform* parent;

	struct Data
	{
		Data()
		{
			data = XMMatrixIdentity();
		}
		SimpleMath::Matrix data;
	}world;

	ConstantBuffer* worldBuffer;

public:
	SimpleMath::Vector3 up, right, forward;


	static SimpleMath::Vector3 WorldUp, WorldRight, WorldForward;
	SimpleMath::Vector3& Up() {
		XMStoreFloat3(&up, XMVector3Transform(WorldUp, world.data));
		up.Normalize();
		return  up;
	}
	SimpleMath::Vector3& Right() {
		XMStoreFloat3(&right, XMVector4Transform(WorldRight, world.data));
		right.Normalize();
		return  right;
	}
	SimpleMath::Vector3& Forward() {
		XMStoreFloat3(&forward, XMVector4Transform(WorldForward, world.data));
		forward.Normalize();
		return  forward;
	}

	SimpleMath::Vector3 pos;
	SimpleMath::Vector3 rot;
	SimpleMath::Vector3 scale;

	SimpleMath::Vector3 posW;
	SimpleMath::Vector3 rotW;
	SimpleMath::Quaternion quatW;
	SimpleMath::Vector3 scaleW;

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