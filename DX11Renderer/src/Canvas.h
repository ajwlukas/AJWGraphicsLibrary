#pragma once

#include "CanvasManager.h"

/// <summary>
/// 뷰포트에 대한 비율, 예시, 0.5 , 0.0 , 0.5, 0.5 하면 화면 오른쪽 상단 4분의 1 차지하게,
///  uv 좌표와 동일
/// 
/// written by Ssreppa 22 06 18
/// </summary>
class Canvas : public Object//todo : 추후 layer 나눌 수 있게 추가 할 것
{
public:
	Canvas(float posLeftRatio, float posTopRatio, float widthRatio, float heightRatio, UINT layer = 0);
	~Canvas();

	virtual void Update() override;
	virtual void Render() override;

	void ReSizeCanvas(float in_posLeftRatio, float in_posTopRatio, float in_widthRatio, float in_heightRatio);
	void SetSRV(Resource<ID3D11ShaderResourceView>* srvResource) { srv = srvResource; }

	Resource<ID3D11ShaderResourceView>* srv;

private:

	UINT layer ;

	float posLeftRatio, posTopRatio, widthRatio, heightRatio;
	void CreateCanvas();
	void ReCreateCanvas();

public:
	static CanvasManager manager;
};