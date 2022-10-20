#pragma once

#include "IPass.h"

class PostProcessor
{
public:
	//보통 인풋은 디퍼드 라이팅된 텍스쳐
	PostProcessor(RenderTargetTexutre* inputRTT, RenderTargetTexutre* finalAccumulationRTT);
	~PostProcessor();

	void OnResize();

	void ClearRenderTargets();

	void Render();

	RenderTargetTexutre* GetLastRTT() { return lastRTT; }

	//template<typename T>
	//void AddPass();

	////todo
	//template<typename T>
	//void SubPass();

private:
	RenderTargetTexutre* startRTT;

	vector<IPass*> passes;

	RenderTargetTexutre* lastRTT;

	void BuildWinSizeBuffer();

	//windowSize;
	Resource<ID3D11Buffer> buffer;

	struct Data
	{
		Data() : winSizeX(DX->width), winSizeY(DX->height)
		{
			winSizeXInv = 1 / (float)winSizeX;
			winSizeYInv = 1 / (float)winSizeY;
		}

		UINT winSizeX;
		UINT winSizeY;
		float winSizeXInv;
		float winSizeYInv;
	}data;
};
