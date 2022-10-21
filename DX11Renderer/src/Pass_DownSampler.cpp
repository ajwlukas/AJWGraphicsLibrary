#include "pch_dx_11.h"
#include "Pass_DownSampler.h"

Pass_DownSampler::Pass_DownSampler()
	:ratio(1)
{
	pixelShader = RESOURCES->pixelShaders->Get(L"Pass_Sampler.hlsl");

	rtt.Resize(DX->width / ratio, DX->height / ratio);
}

Pass_DownSampler::~Pass_DownSampler()
{
}

void Pass_DownSampler::SetSRV(Resource<ID3D11ShaderResourceView>* srv)
{
	this->srv = srv;
}

void Pass_DownSampler::OnResize()
{
	rtt.Resize(DX->width / ratio, DX->height / ratio);
}

void Pass_DownSampler::Draw()
{
	D3D11_VIEWPORT viewPort = {};
	viewPort.Width = (float)(DX->width / ratio);
	viewPort.Height = (float)(DX->height / ratio);
	viewPort.MinDepth = 0.0f;
	viewPort.MaxDepth = 1.0f;
	viewPort.TopLeftX = 0.0f;
	viewPort.TopLeftY = 0.0f;

	DC->RSSetViewports(1, &viewPort);

	DC->OMSetRenderTargets(1, rtt.rtv, NULL);

	DC->PSSetShaderResources(20, 1, (*srv));

	mesh.Set();

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	ZeroMemory(&mappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));

	DC->Map(*transform.WorldBuffer(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	// Copy Resource Data..
	memcpy(mappedResource.pData, transform.World(), sizeof(*transform.World()));

	// GPU Access UnLock Buffer Data..
	DC->Unmap(*transform.WorldBuffer(), 0);
	DC->VSSetConstantBuffers(0, 1, transform.WorldBuffer());

	DC->PSSetShader(pixelShader, 0, 0);

	DC->DrawIndexed(6, 0, 0);
	
	viewPort = {};
	viewPort.Width = DX->width ;
	viewPort.Height =DX->height;
	viewPort.MinDepth = 0.0f;
	viewPort.MaxDepth = 1.0f;
	viewPort.TopLeftX = 0.0f;
	viewPort.TopLeftY = 0.0f;

	DC->RSSetViewports(1, &viewPort);
}
