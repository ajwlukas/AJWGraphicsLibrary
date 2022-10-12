#include "pch_dx_11.h"
#include "AimCanvas.h"

AimCanvas::AimCanvas()
	:Canvas(0,0,1.0f,1.0f)
{
	material->SetShader(L"AimCanvas.hlsl");

	D3D11_BUFFER_DESC cbd;
	cbd.Usage = D3D11_USAGE_DYNAMIC;
	cbd.ByteWidth = sizeof(Data);
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbd.MiscFlags = 0;
	cbd.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA initData;
	initData.pSysMem = &data;
	RESOURCES->buffers->Create(buffer, cbd, &initData);
}

AimCanvas::~AimCanvas()
{
}

void AimCanvas::Update()
{
	__super::Update();

}

void AimCanvas::Render()
{
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	ZeroMemory(&mappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));

	DC->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	// Copy Resource Data..
	memcpy(mappedResource.pData, &data, sizeof(data));

	// GPU Access UnLock Buffer Data..
	DC->Unmap(buffer, 0);

	DC->PSSetConstantBuffers(2, 1, buffer);

	__super::Render();
}
