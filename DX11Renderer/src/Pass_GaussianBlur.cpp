#include "pch_dx_11.h"
#include "Pass_GaussianBlur.h"

Pass_GaussianBlur::Pass_GaussianBlur()
{
	gausianXShader = RESOURCES->pixelShaders->Get(L"GaussianBlur_X.hlsl");
	gausianYShader = RESOURCES->pixelShaders->Get(L"GaussianBlur_Y.hlsl");
}

Pass_GaussianBlur::~Pass_GaussianBlur()
{
}

void Pass_GaussianBlur::SetSRV(Resource<ID3D11ShaderResourceView>* srv)
{
	this->srv = srv;
}

void Pass_GaussianBlur::Draw()
{
	GaussianX();
	GaussianY();
}

void Pass_GaussianBlur::GaussianX()
{
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

	DC->PSSetShader(gausianXShader, 0, 0);

	DC->DrawIndexed(6, 0, 0);// == (mesh.GetIndexCount(), 0, 0);
}

void Pass_GaussianBlur::GaussianY()
{
	DC->OMSetRenderTargets(1, rttforGuasY.rtv, NULL);

	DC->PSSetShaderResources(20, 1, rtt.srv);

	mesh.Set();

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	ZeroMemory(&mappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));

	DC->Map(*transform.WorldBuffer(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	// Copy Resource Data..
	memcpy(mappedResource.pData, transform.World(), sizeof(*transform.World()));

	// GPU Access UnLock Buffer Data..
	DC->Unmap(*transform.WorldBuffer(), 0);
	DC->VSSetConstantBuffers(0, 1, transform.WorldBuffer());

	DC->PSSetShader(gausianYShader, 0, 0);

	DC->DrawIndexed(6, 0, 0);// == (mesh.GetIndexCount(), 0, 0);
}
