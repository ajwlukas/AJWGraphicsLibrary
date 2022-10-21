#pragma once

class Capsule : public Object
{
public:
	Capsule(float radius, float height);
	~Capsule();

	virtual void Update();
	virtual void Render();

	void Create();

	float radius, height;

	Resource<ID3D11RasterizerState> wireFrame;
	Resource<ID3D11RasterizerState> defaultRasterizerState;

	UINT sectorCount, stackCount;
};