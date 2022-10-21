#include "pch_dx_11.h"
#include "PointLightsBuffer.h"

PointLightsBuffer::PointLightsBuffer()
{
	CreateLightPreInfoBuffer();
	CreateLightInfosBuffer();
}

PointLightsBuffer::~PointLightsBuffer()
{
}

void PointLightsBuffer::CreateLightPreInfoBuffer()
{
	D3D11_BUFFER_DESC cbd;
	cbd.Usage = D3D11_USAGE_DYNAMIC;
	cbd.ByteWidth = sizeof(LightPreInfo);
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbd.MiscFlags = 0;
	cbd.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA initData;
	initData.pSysMem = &lightPreInfo;
	RESOURCES->buffers->Create(lightPreInfoBuffer, cbd, &initData);

	DC->PSSetConstantBuffers(4, 1, lightPreInfoBuffer);
}

void PointLightsBuffer::CreateLightInfosBuffer()
{
	lightInfos = new LightInfo[MAX_POINT_LIGHT_SIZE];

	D3D11_BUFFER_DESC desc = {};
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.ByteWidth = sizeof(LightInfo) * MAX_POINT_LIGHT_SIZE;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA initData;
	initData.pSysMem = lightInfos;

	RESOURCES->buffers->Create(lightsInfoBuffer, desc, &initData);

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
	srvDesc.Buffer.FirstElement = 0;
	srvDesc.Buffer.NumElements = MAX_POINT_LIGHT_SIZE * sizeof(LightInfo) / sizeof(float4);

	RESOURCES->srvs->Create(lightsInfoSRV, srvDesc, lightsInfoBuffer);

	DC->PSSetShaderResources(22, 1, lightsInfoSRV);
}

void PointLightsBuffer::AddLightInfo(float3 pos, float intensity, float3 color, float range)
{

	lightInfos[lightPreInfo.pointLightNum].posXYZ_intensity.x = pos.x;
	lightInfos[lightPreInfo.pointLightNum].posXYZ_intensity.y = pos.y;
	lightInfos[lightPreInfo.pointLightNum].posXYZ_intensity.z = pos.z;
	lightInfos[lightPreInfo.pointLightNum].posXYZ_intensity.w = intensity;

	lightInfos[lightPreInfo.pointLightNum].color_range.x = color.x;
	lightInfos[lightPreInfo.pointLightNum].color_range.y = color.y;
	lightInfos[lightPreInfo.pointLightNum].color_range.z = color.z;

	lightInfos[lightPreInfo.pointLightNum].color_range.w = range;

	lightPreInfo.pointLightNum++;

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	ZeroMemory(&mappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));

	DC->Map(lightPreInfoBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	// Copy Resource Data..
	memcpy(mappedResource.pData, &lightPreInfo, sizeof(lightPreInfo));

	// GPU Access UnLock Buffer Data..
	DC->Unmap(lightPreInfoBuffer, 0);


	ZeroMemory(&mappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));

	DC->Map(lightsInfoBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	// Copy Resource Data..
	memcpy(mappedResource.pData, lightInfos, sizeof(LightInfo) * MAX_POINT_LIGHT_SIZE);

	// GPU Access UnLock Buffer Data..
	DC->Unmap(lightsInfoBuffer, 0);
}

void PointLightsBuffer::SubAllLights()
{ 
	lightPreInfo.pointLightNum = 0;
	
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	ZeroMemory(&mappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));

	DC->Map(lightPreInfoBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	// Copy Resource Data..
	memcpy(mappedResource.pData, &lightPreInfo, sizeof(lightPreInfo));

	// GPU Access UnLock Buffer Data..
	DC->Unmap(lightPreInfoBuffer, 0);

}
