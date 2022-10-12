#pragma once

#define MAX_POINT_LIGHT_SIZE 100

class PointLightsBuffer
{
public:
	PointLightsBuffer();
	~PointLightsBuffer();

	struct LightPreInfo//constant Bufferø° ≤»¿ª ≥‡ºÆ
	{
		UINT pointLightNum;
		float dummy0;
		float dummy1;
		float dummy2;
	}lightPreInfo;

	Resource<ID3D11Buffer> lightPreInfoBuffer;

	void CreateLightPreInfoBuffer();
	void CreateLightInfosBuffer();
	void AddLightInfo(float3 pos, float intensity, float3 color, float range);

	void SubAllLights();

	struct LightInfo
	{
		float4 posXYZ_intensity;//{pos.x, pos.y, pos.z, intensity}
		float4 color_range;////{color.r, color.g, color.b, range}
	};

	LightInfo* lightInfos;
	Resource<ID3D11Buffer> lightsInfoBuffer;
	Resource<ID3D11ShaderResourceView> lightsInfoSRV;//bufferøÕ π≠ø©¿÷¥Ÿ
};