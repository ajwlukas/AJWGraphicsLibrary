#pragma once

#include "IPass.h"

class Pass_GaussianBlur : public IPass
{
public:
	Pass_GaussianBlur();
	~Pass_GaussianBlur();

	void SetSRV(Resource<ID3D11ShaderResourceView>* srv);

	virtual Resource<ID3D11ShaderResourceView>* GetSRV() override{ return &rttforGuasY.srv; }


	virtual RenderTargetTexutre* GetRTT() override { return &rttforGuasY; }

	virtual void Draw() override;

private:

	Resource<ID3D11ShaderResourceView>* srv;

	ID3D11PixelShader* gausianXShader;
	ID3D11PixelShader* gausianYShader;

	void GaussianX();
	void GaussianY();


	RenderTargetTexutre rttforGuasY;
};