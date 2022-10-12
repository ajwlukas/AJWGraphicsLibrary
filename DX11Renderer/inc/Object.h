#pragma once

/// <summary>
/// �Ϲ������� ���� �ʴ� ������Ʈ�� ����� �� ����Ͽ� ���
/// ���� ��� ó) Camera, Canvas, Grid, SkyBox
/// 
/// ������������ �Ϻ��� �ֵ��� Object��� �θ�, Mesh, Material �� �� ��� Object��� �� �� ���� ex) ī�޶�
/// </summary>
class Object
{
public:
	Object();
	virtual ~Object();

	virtual void Update();
	virtual void Render();

	void SetPipeLine();
	void Draw();

	string name;

	Mesh* mesh;
	Material* material;

	Transform transform;
};