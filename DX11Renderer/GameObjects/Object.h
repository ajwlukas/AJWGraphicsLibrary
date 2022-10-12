#pragma once

class Proto;

class Object
{
public:
	Object(Proto* belongsTo);
	Object();
	virtual ~Object();

	virtual void Update();
	virtual void Render();

	Proto* belongsTo;

	string name;

	Mesh* mesh;
	Material* material;

	Transform transform;

	Instance* CreateInstance() { return instants->CreateInstance(); };
	Instants* instants;

	Animator* animator;
	Skinner* skinner;
};