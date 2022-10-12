#include "pch_dx_11.h"
#include "IPass.h"

IPass::IPass()
{
}

IPass::~IPass()
{
}

void IPass::OnResize()
{
	rtt.OnResize();
}

void IPass::ClearRenderTarget()
{
	float color[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	DC->ClearRenderTargetView(rtt.rtv, color);
}

//void IPass::SetMainSRV(Resource<ID3D11ShaderResourceView>* srv)
//{
//	mainSRV = srv;
//}
//
//void IPass::Draw()
//{
//	float color[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
//
//	if(!isLast)
//		DC->ClearRenderTargetView(rtt.rtv, color);
//
//	DC->OMSetRenderTargets(1, rtt.rtv, NULL);
//
//	DC->PSSetShaderResources(20, 1, (*mainSRV));
//
//	mesh.Set();
//
//	DC->UpdateSubresource(*transform.WorldBuffer(), 0, 0, transform.World(), 0, 0);
//	DC->VSSetConstantBuffers(0, 1, transform.WorldBuffer());
//
//	DC->PSSetShader(pixelShader, 0, 0);
//
//	DC->DrawIndexed(6, 0, 0);// == (mesh.GetIndexCount(), 0, 0);
//}
//
//void IPass::SetShader(wstring psShaderName)
//{
//	pixelShader = RESOURCES->pixelShaders->Get(psShaderName);
//}
//
