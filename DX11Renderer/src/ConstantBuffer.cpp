#include "pch_dx_11.h"
#include "ConstantBuffer.h"

ConstantBuffer::ConstantBuffer(ID3D11DeviceContext* dc, Resources* resources, Pipeline* pipeline, UINT slot, void* data, size_t dataSize)
	:dc(dc)
	,resources(resources)
	,slot(slot)
{
	D3D11_BUFFER_DESC desc = {};
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.ByteWidth = dataSize;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA initData;
	ZeroMemory(&initData, sizeof(D3D11_SUBRESOURCE_DATA));
	initData.pSysMem = data;

	resources->buffers->Create(buffer, desc, &initData);
}

ConstantBuffer::~ConstantBuffer()
{
}

void ConstantBuffer::Set()
{
	dc->VSSetConstantBuffers( slot, 1, buffer);

	//pipeline->SetConstantBuffer(this);
}

void ConstantBuffer::Update(void* data, size_t dataSize)
{
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	ZeroMemory(&mappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));

	dc->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	// Copy Resource Data..
	memcpy(mappedResource.pData, data, dataSize);

	// GPU Access UnLock Buffer Data..
	dc->Unmap(buffer, 0);


}
