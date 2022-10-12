#pragma once

#include "IPass.h"

class Pass_DownSampler : public IPass
{
public:
	Pass_DownSampler();
	~Pass_DownSampler();

	void SetSRV(Resource<ID3D11ShaderResourceView>* srv);

	virtual void OnResize() override;

	virtual void Draw() override;

	void SetDownRatio(UINT ratio) { this->ratio = ratio; OnResize(); }//줄일 비율 2,4,8

private:

	Resource<ID3D11ShaderResourceView>* srv;
	UINT ratio;
};