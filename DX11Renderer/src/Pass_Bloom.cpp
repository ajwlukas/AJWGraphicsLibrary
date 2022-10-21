#include "pch_dx_11.h"
#include "Pass_Bloom.h"

#define NUM_0 8
#define NUM_1 4
#define NUM_2 2
#define NUM_3 1

Pass_Bloom::Pass_Bloom()
{
	downSampler2.SetDownRatio(2);
	downSampler4.SetDownRatio(NUM_1);
	downSampler8.SetDownRatio(NUM_0);

	accumulate48.Resize(DX->width / NUM_1, DX->height / NUM_1);
	accumulate24.Resize(DX->width / NUM_2, DX->height / NUM_2);
	accumulate12.Resize(DX->width / 1, DX->height / 1);//aka OnResize

	blur8.Resize(DX->width / NUM_0, DX->height / NUM_0);
	blur4.Resize(DX->width / NUM_1, DX->height / NUM_1);
	blur2.Resize(DX->width / NUM_2, DX->height / NUM_2);//aka OnResize
	blur1.Resize(DX->width / NUM_3, DX->height / NUM_3);//aka OnResize

	blurred8.Resize(DX->width / NUM_0, DX->height / NUM_0);
	blurred4.Resize(DX->width / NUM_1, DX->height / NUM_1);
	blurred2.Resize(DX->width / NUM_2, DX->height / NUM_2);
	blurred1.Resize(DX->width / NUM_3, DX->height / NUM_3);

	accumulator = RESOURCES->pixelShaders->Get(L"Pass_Accumulator.hlsl");

	gausianXShader = RESOURCES->pixelShaders->Get(L"GaussianBlur_X.hlsl");
	gausianYShader = RESOURCES->pixelShaders->Get(L"GaussianBlur_Y.hlsl");
	CreateTextureSizeBuffer();

	D3D11_SAMPLER_DESC samplerDesc = {};
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
	samplerDesc.BorderColor[0] = 0.0f;
	samplerDesc.BorderColor[1] = 0.0f;
	samplerDesc.BorderColor[2] = 0.0f;
	samplerDesc.BorderColor[3] = 0.0f;

	RESOURCES->samplerStates->Get(sampler, samplerDesc);
}

Pass_Bloom::~Pass_Bloom()
{
}

void Pass_Bloom::SetSRV(Resource<ID3D11ShaderResourceView>* srv)
{
	this->srv = srv;
	downSampler2.SetSRV(srv);
	downSampler4.SetSRV(srv);
	downSampler8.SetSRV(srv);
}

void Pass_Bloom::OnResize()
{
	downSampler2.OnResize();
	downSampler4.OnResize();
	downSampler8.OnResize();

	accumulate48.Resize(DX->width / NUM_1, DX->height / NUM_1);
	accumulate24.Resize(DX->width / NUM_2, DX->height / NUM_2);
	accumulate12.Resize(DX->width / NUM_3, DX->height / NUM_3);//aka OnResize

	blur8.Resize(DX->width / NUM_0, DX->height / NUM_0);
	blur4.Resize(DX->width / NUM_1, DX->height / NUM_1);
	blur2.Resize(DX->width / NUM_2, DX->height / NUM_2);//aka OnResize
	blur1.Resize(DX->width / NUM_3, DX->height / NUM_3);//aka OnResize

	blurred8.Resize(DX->width / NUM_0, DX->height / NUM_0);
	blurred4.Resize(DX->width / NUM_1, DX->height / NUM_1);
	blurred2.Resize(DX->width / NUM_2, DX->height / NUM_2);
	blurred1.Resize(DX->width / NUM_3, DX->height / NUM_3);
}

void Pass_Bloom::Draw()
{
	DC->PSSetSamplers(1, 1, sampler);

	PrePareDownSampledRTT();

	GaussianBlur8();//blur8를 Blur먹인다.

	UpSample48();//blur4와 합친다.

	GaussianBlur4();//합친걸 Blur 먹인다.

	UpSample24();//blur2와 합친다.

	GaussianBlur2();//합친걸 Blur 먹인다.

	UpSample12();//원래 이미지와 합친다.

	GaussianBlur1();//합친걸 Blur 먹인다.

	AccumulateFinal();//최종본과 합친다.
}

void Pass_Bloom::ClearRenderTarget()
{
	float color[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	DC->ClearRenderTargetView(rtt.rtv, color);

	DC->ClearRenderTargetView(downSampler2.GetRTT()->rtv, color);
	DC->ClearRenderTargetView(downSampler4.GetRTT()->rtv, color);
	DC->ClearRenderTargetView(downSampler8.GetRTT()->rtv, color);

	DC->ClearRenderTargetView(blur8.rtv, color);
	DC->ClearRenderTargetView(blur4.rtv, color);
	DC->ClearRenderTargetView(blur2.rtv, color);
	DC->ClearRenderTargetView(blur1.rtv, color);

	DC->ClearRenderTargetView(accumulate48.rtv, color);
	DC->ClearRenderTargetView(accumulate24.rtv, color);
	DC->ClearRenderTargetView(accumulate12.rtv, color);

	DC->ClearRenderTargetView(blurred8.rtv, color);
	DC->ClearRenderTargetView(blurred4.rtv, color);
	DC->ClearRenderTargetView(blurred2.rtv, color);
	DC->ClearRenderTargetView(blurred1.rtv, color);
}

void Pass_Bloom::CreateTextureSizeBuffer()
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

	DC->PSSetConstantBuffers(3, 1, buffer);
}

void Pass_Bloom::UpdateTexSizeBuffer(UINT texSizeX, UINT texSizeY)
{
	data.texSizeX = texSizeX;
	data.texSizeY = texSizeY;
	data.texSizeXInv = 1 / (float)texSizeX;
	data.texSizeYInv = 1 / (float)texSizeY;


	D3D11_MAPPED_SUBRESOURCE mappedResource;
	ZeroMemory(&mappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));

	DC->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	// Copy Resource Data..
	memcpy(mappedResource.pData, &data, sizeof(data));

	// GPU Access UnLock Buffer Data..
	DC->Unmap(buffer, 0);

	//DC->UpdateSubresource(buffer, 0, 0, &data, 0, 0);

}

void Pass_Bloom::PrePareDownSampledRTT()
{
	downSampler2.Draw();
	downSampler4.Draw();
	downSampler8.Draw();
}

//input == downSampler8
void Pass_Bloom::GaussianBlur8()
{
	D3D11_VIEWPORT viewPort = {};
	viewPort.Width = (float)(DX->width / NUM_0);
	viewPort.Height = (float)(DX->height / NUM_0);
	viewPort.MinDepth = 0.0f;
	viewPort.MaxDepth = 1.0f;
	viewPort.TopLeftX = 0.0f;
	viewPort.TopLeftY = 0.0f;

	UpdateTexSizeBuffer(viewPort.Width, viewPort.Height);

	DC->RSSetViewports(1, &viewPort);

	DC->OMSetRenderTargets(1, blur8.rtv, NULL);

	DC->PSSetShaderResources(20, 1, *downSampler8.GetSRV());

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


	DC->OMSetRenderTargets(1, blurred8.rtv, NULL);

	DC->PSSetShaderResources(20, 1, blur8.srv);

	mesh.Set();

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
//output == blurred8

//input == blurred8, downSampler4
void Pass_Bloom::UpSample48()
{
	D3D11_VIEWPORT viewPort = {};
	viewPort.Width = (float)(DX->width / NUM_1);
	viewPort.Height = (float)(DX->height / NUM_1);
	viewPort.MinDepth = 0.0f;
	viewPort.MaxDepth = 1.0f;
	viewPort.TopLeftX = 0.0f;
	viewPort.TopLeftY = 0.0f;

	DC->RSSetViewports(1, &viewPort);

	DC->OMSetRenderTargets(1, accumulate48.rtv, NULL);

	ID3D11ShaderResourceView* srvs[2] = { (*downSampler4.GetSRV()), blurred8.srv };

	DC->PSSetShaderResources(20, 2, srvs);

	mesh.Set();

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	ZeroMemory(&mappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));

	DC->Map(*transform.WorldBuffer(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	// Copy Resource Data..
	memcpy(mappedResource.pData, transform.World(), sizeof(*transform.World()));

	// GPU Access UnLock Buffer Data..
	DC->Unmap(*transform.WorldBuffer(), 0);
	DC->VSSetConstantBuffers(0, 1, transform.WorldBuffer());

	DC->PSSetShader(accumulator, 0, 0);

	DC->DrawIndexed(6, 0, 0);
}
//output == accumulate48

//input == accumulate48
void Pass_Bloom::GaussianBlur4()
{
	D3D11_VIEWPORT viewPort = {};
	viewPort.Width = (float)(DX->width / NUM_1);
	viewPort.Height = (float)(DX->height / NUM_1);
	viewPort.MinDepth = 0.0f;
	viewPort.MaxDepth = 1.0f;
	viewPort.TopLeftX = 0.0f;
	viewPort.TopLeftY = 0.0f;

	UpdateTexSizeBuffer(viewPort.Width, viewPort.Height);

	DC->RSSetViewports(1, &viewPort);

	DC->OMSetRenderTargets(1, blur4.rtv, NULL);

	DC->PSSetShaderResources(20, 1, accumulate48.srv);

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


	DC->OMSetRenderTargets(1, blurred4.rtv, NULL);

	DC->PSSetShaderResources(20, 1, blur4.srv);

	mesh.Set();

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
//output == blurred4

//input == blurred4, downSampler2
void Pass_Bloom::UpSample24()
{
	D3D11_VIEWPORT viewPort = {};
	viewPort.Width = (float)(DX->width / NUM_2);
	viewPort.Height = (float)(DX->height / NUM_2);
	viewPort.MinDepth = 0.0f;
	viewPort.MaxDepth = 1.0f;
	viewPort.TopLeftX = 0.0f;
	viewPort.TopLeftY = 0.0f;

	DC->RSSetViewports(1, &viewPort);

	DC->OMSetRenderTargets(1, accumulate24.rtv, NULL);

	ID3D11ShaderResourceView* srvs[2] = { (*downSampler2.GetSRV()), blurred4.srv };

	DC->PSSetShaderResources(20, 2, srvs);

	mesh.Set();

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	ZeroMemory(&mappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));

	DC->Map(*transform.WorldBuffer(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	// Copy Resource Data..
	memcpy(mappedResource.pData, transform.World(), sizeof(*transform.World()));

	// GPU Access UnLock Buffer Data..
	DC->Unmap(*transform.WorldBuffer(), 0);
	DC->VSSetConstantBuffers(0, 1, transform.WorldBuffer());

	DC->PSSetShader(accumulator, 0, 0);

	DC->DrawIndexed(6, 0, 0);
}
//output == accumulate24

//input == accumulate24
void Pass_Bloom::GaussianBlur2()
{
	D3D11_VIEWPORT viewPort = {};
	viewPort.Width = (float)(DX->width / NUM_2);
	viewPort.Height = (float)(DX->height / NUM_2);
	viewPort.MinDepth = 0.0f;
	viewPort.MaxDepth = 1.0f;
	viewPort.TopLeftX = 0.0f;
	viewPort.TopLeftY = 0.0f;

	UpdateTexSizeBuffer(viewPort.Width, viewPort.Height);

	DC->RSSetViewports(1, &viewPort);

	DC->OMSetRenderTargets(1, blur2.rtv, NULL);

	DC->PSSetShaderResources(20, 1, accumulate24.srv);

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


	DC->OMSetRenderTargets(1, blurred2.rtv, NULL);

	DC->PSSetShaderResources(20, 1, blur2.srv);

	mesh.Set();

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
//output == blurred2

void Pass_Bloom::UpSample12()
{
	D3D11_VIEWPORT viewPort = {};
	viewPort.Width = (float)(DX->width / 1);
	viewPort.Height = (float)(DX->height / 1);
	viewPort.MinDepth = 0.0f;
	viewPort.MaxDepth = 1.0f;
	viewPort.TopLeftX = 0.0f;
	viewPort.TopLeftY = 0.0f;

	DC->RSSetViewports(1, &viewPort);

	DC->OMSetRenderTargets(1, accumulate12.rtv, NULL);

	ID3D11ShaderResourceView* srvs[2] = { (*srv), blurred2.srv };

	DC->PSSetShaderResources(20, 2, srvs);

	mesh.Set();

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	ZeroMemory(&mappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));

	DC->Map(*transform.WorldBuffer(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	// Copy Resource Data..
	memcpy(mappedResource.pData, transform.World(), sizeof(*transform.World()));

	// GPU Access UnLock Buffer Data..
	DC->Unmap(*transform.WorldBuffer(), 0);
	DC->VSSetConstantBuffers(0, 1, transform.WorldBuffer());

	DC->PSSetShader(accumulator, 0, 0);

	DC->DrawIndexed(6, 0, 0);
}
//output == accumalate12

//input == accumalate12
void Pass_Bloom::GaussianBlur1()
{
	D3D11_VIEWPORT viewPort = {};
	viewPort.Width = (float)(DX->width / 1);
	viewPort.Height = (float)(DX->height / 1);
	viewPort.MinDepth = 0.0f;
	viewPort.MaxDepth = 1.0f;
	viewPort.TopLeftX = 0.0f;
	viewPort.TopLeftY = 0.0f;

	UpdateTexSizeBuffer(viewPort.Width, viewPort.Height);

	DC->RSSetViewports(1, &viewPort);

	DC->OMSetRenderTargets(1, blur1.rtv, NULL);

	DC->PSSetShaderResources(20, 1, accumulate12.srv);

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


	DC->OMSetRenderTargets(1, blurred1.rtv, NULL);

	DC->PSSetShaderResources(20, 1, blur1.srv);

	mesh.Set();

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
//output == blurred1.rtv


void Pass_Bloom::AccumulateFinal()
{
	D3D11_VIEWPORT viewPort = {};
	viewPort.Width = (float)(DX->width / 1);
	viewPort.Height = (float)(DX->height / 1);
	viewPort.MinDepth = 0.0f;
	viewPort.MaxDepth = 1.0f;
	viewPort.TopLeftX = 0.0f;
	viewPort.TopLeftY = 0.0f;

	DC->RSSetViewports(1, &viewPort);

	DC->OMSetRenderTargets(1, rtt.rtv, NULL);

	ID3D11ShaderResourceView* srvs[2] = { finalAccumulationRTT->srv, blurred1.srv };

	DC->PSSetShaderResources(20, 2, srvs);

	mesh.Set();

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	ZeroMemory(&mappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));

	DC->Map(*transform.WorldBuffer(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	// Copy Resource Data..
	memcpy(mappedResource.pData, transform.World(), sizeof(*transform.World()));

	// GPU Access UnLock Buffer Data..
	DC->Unmap(*transform.WorldBuffer(), 0);
	DC->VSSetConstantBuffers(0, 1, transform.WorldBuffer());

	DC->PSSetShader(accumulator, 0, 0);

	DC->DrawIndexed(6, 0, 0);
}
