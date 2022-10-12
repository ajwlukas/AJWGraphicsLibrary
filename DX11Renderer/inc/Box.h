#pragma once

#include "GameObjects\InstancingObject.h"

class Box : public InstancingObject
{
public:
	Box();
	~Box();

	virtual void Update();
	virtual void Render();

	void Create();

	float radius;

	Resource<ID3D11RasterizerState> wireFrame;
	Resource<ID3D11RasterizerState> defaultRasterizerState;

};