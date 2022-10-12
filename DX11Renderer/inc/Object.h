#pragma once

/// <summary>
/// 일반적으로 찍어내지 않는 오브젝트를 사용할 때 상속하여 사용
/// 예시 사용 처) Camera, Canvas, Grid, SkyBox
/// 
/// 파이프라인의 일부인 애들을 Object라고 부름, Mesh, Material 등 이 없어도 Object라고 할 수 있음 ex) 카메라
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