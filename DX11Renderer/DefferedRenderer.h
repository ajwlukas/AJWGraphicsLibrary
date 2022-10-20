#pragma once

#include <Canvas.h>

/// <summary>
/// UsingShader CanvasVS, DefferedRenderPS
/// numRTT = PixelHeader에 렌더 타겟 갯수를 본다.
/// 
//float4 albedo : SV_Target0;
//float4 normal : SV_Target1;
//float4 worldPos : SV_Target2;
//float4 setting0 : SV_Target3;//x = defferedRenderer doLight
//float4 ambient : SV_Target4;
//float4 diffuse : SV_Target5;
//float4 specular : SV_Target6;
//float4 emissive : SV_Target7;
/// 
/// </summary>
class DefferedRenderer : public Object
{
public:
	DefferedRenderer();
	~DefferedRenderer();

	virtual void Update() override;
	virtual void Render() override;

	/// 그릴곳을 세팅 (재료준비, 캔버스 세팅?), ex) albedomap, normalMap, 세팅
	//void SetRenderTargets() {	DC->OMSetRenderTargets(renderTargets.size(), renderTargets.data(), DX->depthStencilView);	}

	void OnResize();

	void SetRenderTarget(RenderTargetTexutre* preRenderedTexture)
	{
		this->preRenderedTexture = preRenderedTexture;
	}

	void ClearRenderTargetView();

private:
	const UINT numRTT;

public:
	vector< RenderTargetTexutre*> rtts;

private:
	RenderTargetTexutre* preRenderedTexture;

	vector< ID3D11ShaderResourceView*> srvs;
	vector< ID3D11RenderTargetView*> renderTargets;

	void CreateCanvas();

	vector<Canvas*> canvases;

public:
	RenderTargetTexutre rtt;
};