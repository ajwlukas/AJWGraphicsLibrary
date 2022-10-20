#pragma once

#include "IPass.h"
#include "Pass_DownSampler.h"
#include "Pass_GaussianBlur.h"

class Pass_Bloom : public IPass
{
public:
	Pass_Bloom();
	~Pass_Bloom();

	void SetSRV(Resource<ID3D11ShaderResourceView>* srv);

	virtual void OnResize() override;

	virtual void Draw() override;

	virtual void ClearRenderTarget() override;

	void SetSkyBoxRTT(RenderTargetTexutre* rtt) { finalAccumulationRTT = rtt; }

private:
	struct Data
	{
		Data() : texSizeX(DX->width), texSizeY(DX->height)
		{
			texSizeXInv = 1 / (float)texSizeX;
			texSizeYInv = 1 / (float)texSizeY;
		}

		UINT texSizeX;
		UINT texSizeY;
		float texSizeXInv;
		float texSizeYInv;
	}data;

	void CreateTextureSizeBuffer();

	void UpdateTexSizeBuffer(UINT texSizeX, UINT texSizeY);

	RenderTargetTexutre* finalAccumulationRTT;

	//texSize;
	Resource<ID3D11Buffer> buffer; 
	Resource<ID3D11SamplerState> sampler;

	Pass_DownSampler downSampler2;
	Pass_DownSampler downSampler4;
	Pass_DownSampler downSampler8;//1/8 배율 텍스쳐

	RenderTargetTexutre blur8;
	RenderTargetTexutre blur4;
	RenderTargetTexutre blur2;
	RenderTargetTexutre blur1;

	RenderTargetTexutre accumulate48;
	RenderTargetTexutre accumulate24;
	RenderTargetTexutre accumulate12;

	RenderTargetTexutre blurred8;
	RenderTargetTexutre blurred4;
	RenderTargetTexutre blurred2;
	RenderTargetTexutre blurred1;

	Resource<ID3D11ShaderResourceView>* srv;

	void PrePareDownSampledRTT();

	void GaussianBlur8();
	void UpSample48();
	void GaussianBlur4();
	void UpSample24();
	void GaussianBlur2();
	void UpSample12();
	void GaussianBlur1();
	void AccumulateFinal();


	ID3D11PixelShader* accumulator;


	ID3D11PixelShader* gausianXShader;
	ID3D11PixelShader* gausianYShader;


};