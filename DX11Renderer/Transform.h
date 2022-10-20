#pragma once

#include "Vector3.h"
#include "DXTK/SimpleMath.h"

class Vector3;


class Transform
{
public:
	Transform();
	~Transform();

	void UpdateWorld();//�ܺο�, �з�Ʈ�� ���� �ֵ鸸 ȣ�� �ǹ� ���� �ڽĵ� ��ȸ�ϸ� ������Ʈ�ϱ�����
private:
	void UpdateWorldInternal();//���ο�, �ڽ� ������Ʈ ��
public:

	Vector3 pos;
	Vector3 rot;
	Vector3 scale;

	Vector3 worldPos;
	Vector3 worldRot;
	SimpleMath::Quaternion worldRotQuat;
	Vector3 worldScale;

	void SaveWorldIngredient();

	void DecomposeMatrix(Matrix& m, OUT Vector3& pos, OUT Vector3& rot, OUT Vector3& scale);
	void DecomposeMatrix(Matrix& m, OUT Vector3& pos, OUT SimpleMath::Quaternion& rot, OUT Vector3& scale);

	Vector3 up, right, forward;

	Matrix local;//S * R * T

	Transform* parent;

	bool relateS, relateR, relateT;// �θ�� ���� ����� �͵�
private:
	Matrix S, R, T;
	struct Data
	{
		Data()
		{
			data = XMMatrixIdentity();
		}
		Matrix data;
	}world;

	Resource<ID3D11Buffer> worldBuffer;
public:
	Matrix* World() { return &world.data; }
	ID3D11Buffer** WorldBuffer() { return worldBuffer; }


public:
	static Vector3 WorldUp, WorldRight, WorldForward , W;
	Vector3& Up() {
		XMStoreFloat4(&up.data, XMVector4Transform(WorldUp, world.data));
		up.Normalize();
		return  up;
	}
	Vector3& Right() {
		XMStoreFloat4(&right.data, XMVector4Transform(WorldRight, world.data));
		right.Normalize();
		return  right;
	}
	Vector3& Forward() {
		XMStoreFloat4(&forward.data, XMVector4Transform(WorldForward, world.data));
		forward.Normalize();
		return  forward;
	}

public:
	void SetWorldPos(Vector3 pos);
	void SetWorldPos(Vector3 pos, Vector3 offset);//�̻��� �ڵ� ���� �� ��
	void SetWorldRot(DirectX::SimpleMath::Quaternion quat);
	void LookAtOnlyY(Vector3 TargetPos);

private:
	void UpdateWorldTransform();
	void UpdateWorldTransform(Vector3 offset);
}; 