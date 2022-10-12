#pragma once

#include "Canvas.h"

class AimCanvas : public Canvas
{
public:
	AimCanvas();
	~AimCanvas();

	virtual void Update() override;
	virtual void Render() override;

	struct Data
	{
		/*Data() : color(0.0f, 1.0f, 0.0f, 1.0f) {}
		float4 color;*/
		Data() {}

		float ratio;
		float goodRatio;
		float perfectRatio;
		float failRatio;

		float screenRatio;//맞았을때
		float dummy0;//맞았을때
		float dummy1;//맞았을때
		float dummy2;//맞았을때

	}data;

	void UpdateRatio(float ratio) { data.ratio = ratio; }
	void UpdateRatio_Good(float ratio0) { data.goodRatio = ratio0; }//goodZome
	void UpdateRatio_Perfect(float ratio1) { data.perfectRatio = ratio1; }//goodZome
	void UpdateRatio_Bad(float ratio2) { data.failRatio = ratio2; }//goodZome

	void UpdateRatio_Screen(float ratio) { data.screenRatio = ratio; }//goodZome

	float time;

	Resource<ID3D11Buffer> buffer;
};