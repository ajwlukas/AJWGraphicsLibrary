#pragma once

#include "QuadMesh.h"

class IPass
{
public:
	IPass();
	~IPass();

	virtual void OnResize();

	//포스트 프로세싱할 srv, 디퍼드 렌더된 텍스쳐 or 디퍼드 렌더된 텍스쳐 후처리 된 텍스쳐, 화면에 해당하는 SRV
	//void SetMainSRV(Resource<ID3D11ShaderResourceView>* srv);

	virtual void ClearRenderTarget();

	//실제 작업이 이루어지는 곳
	virtual void Draw() = 0;

	//포스트 프로세싱 된 srv
	virtual Resource<ID3D11ShaderResourceView>* GetSRV() { return &rtt.srv; }

	virtual RenderTargetTexutre* GetRTT() { return &rtt; }


protected:
	Transform transform;//실제로 출력할 것 아니면 의미 없음

	//Resource<ID3D11ShaderResourceView>* mainSRV;

	RenderTargetTexutre rtt;

	QuadMesh mesh;

	ID3D11PixelShader* pixelShader;
};