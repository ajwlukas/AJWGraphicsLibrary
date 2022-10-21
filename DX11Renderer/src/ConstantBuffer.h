#pragma once

#include <d3d11.h>

#include "Resources.h"

#include "IConstantBuffer.h"

class Pipeline;

class ConstantBuffer : public TL_Graphics::IConstantBuffer
{
public:
	ConstantBuffer(ID3D11DeviceContext* dc,Resources* resources, Pipeline* pipeline, UINT slot, void* data, size_t dataSize);
	virtual ~ConstantBuffer();

	virtual void Set() override;
	virtual void Update(void* data, size_t dataSize) override;
	

private:
	ID3D11DeviceContext* dc;
	Resources* resources;
	Pipeline* pipeline;

	Resource<ID3D11Buffer> buffer;
	UINT slot;
};