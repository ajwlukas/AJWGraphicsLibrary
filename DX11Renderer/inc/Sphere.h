#pragma once

#include "GameObjects\InstancingObject.h"

class Sphere : public InstancingObject
{
public:
	Sphere();
	~Sphere();

	virtual void Update();
	virtual void Render();

	void Create();
	float radius;

	Resource<ID3D11RasterizerState> wireFrame;
	Resource<ID3D11RasterizerState> defaultRasterizerState;

	UINT sectorCount, stackCount;
};