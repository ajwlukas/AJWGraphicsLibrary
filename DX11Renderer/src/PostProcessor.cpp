#include "pch_dx_11.h"
#include "PostProcessor.h"

#include "Pass_GaussianBlur.h"
#include "Pass_DownSampler.h"
#include "Pass_Bloom.h"

PostProcessor::PostProcessor(RenderTargetTexutre* inputRTT, RenderTargetTexutre* finalAccumulationRTT)
{
	startRTT = inputRTT;
	lastRTT = inputRTT;

	//AddPass(L"Pass_Test.hlsl");
	//AddPass(L"Pass_Test(2).hlsl");
	
	//AddPass(L"GaussianBlur_X.hlsl");
	//AddPass(L"GaussianBlur_Y.hlsl");
	
	Pass_Bloom* bloomPass = new Pass_Bloom();
	bloomPass->SetSRV(&inputRTT->srv);
	passes.push_back(bloomPass);
	bloomPass->SetSkyBoxRTT(finalAccumulationRTT);


	//Pass_DownSampler* downSamplePass = new Pass_DownSampler();
	//downSamplePass->SetSRV(&inputRTT->srv);
	//passes.push_back(downSamplePass);

	//Pass_GaussianBlur* gaussianPass = new Pass_GaussianBlur();
	////gaussianPass->SetSRV(&inputRTT->srv);
	//gaussianPass->SetSRV(downSamplePass->GetSRV());
	//passes.push_back(gaussianPass);


	lastRTT = passes.back()->GetRTT();
	DX->SetRTTasBackBuffer(lastRTT);

	BuildWinSizeBuffer();
	DC->PSSetConstantBuffers(1, 1, buffer);
}

PostProcessor::~PostProcessor()
{
	for (IPass* pass : passes)
		SAFE_DELETE(pass);
}

void PostProcessor::OnResize()
{
	for (IPass* p : passes)
		p->OnResize();

	data.winSizeX = DX->width;
	data.winSizeY = DX->height;

	data.winSizeXInv = 1 / (float)data.winSizeX;
	data.winSizeYInv = 1 / (float)data.winSizeY;


	D3D11_MAPPED_SUBRESOURCE mappedResource;
	ZeroMemory(&mappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));

	DC->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	// Copy Resource Data..
	memcpy(mappedResource.pData, &data, sizeof(data));

	// GPU Access UnLock Buffer Data..
	DC->Unmap(buffer, 0);

	//DC->UpdateSubresource(buffer, 0, 0, &data, 0, 0);
}

void PostProcessor::ClearRenderTargets()
{
	for (IPass* p : passes)
		p->ClearRenderTarget();
}

void PostProcessor::Render()
{
	for (IPass* p : passes)
		p->Draw();
}

//todo : SetNext 느낌으로
//void PostProcessor::AddPass(wstring psShaderName)
//{
//	passes.emplace_back(new IPass());
//	
//	passes.back()->SetShader(psShaderName);
//
//	if (passes.size() > 1)//두번째부터 앞의 출력값을 이용
//	{
//		passes.back()->SetMainSRV((*(passes.end() - 2))->GetSRV());
//		(*(passes.end() - 2))->isLast = false;
//
//		//rtv 새로 생성
//		(*(passes.end() - 2))->GetRTT()->OnResize();
//	}
//	else//첫번째 추가인 경우
//		passes.back()->SetMainSRV(&startRTT->srv);
//
//	passes.back()->isLast = true;
//
//
//
//	lastRTT = passes.back()->GetRTT();
//	DX->SetRTTasBackBuffer(lastRTT);
//}

void PostProcessor::BuildWinSizeBuffer()
{
	D3D11_BUFFER_DESC cbd;
	cbd.Usage = D3D11_USAGE_DYNAMIC;
	cbd.ByteWidth = sizeof(Data);
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbd.MiscFlags = 0;
	cbd.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA initData;
	initData.pSysMem = &data;
	RESOURCES->buffers->Create(buffer, cbd, &initData);

}
