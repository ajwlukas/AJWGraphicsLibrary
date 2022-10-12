#include "pch_dx_11.h"
#include "DefferedRenderer.h"

DefferedRenderer::DefferedRenderer()
	:numRTT(8)
{
	transform.pos.x = 0.0f;
	transform.pos.y = 0.0f;

	transform.scale.x = 1.0f;
	transform.scale.y = 1.0f;
	CreateCanvas();

	/// multi rtt for deffered Render;
	for (UINT i = 0; i < numRTT; i++)
		rtts.emplace_back(new RenderTargetTexutre());


	for (UINT i = 0; i < numRTT; i++)
	{
		canvases.emplace_back(new Canvas(i / (float)numRTT, (numRTT - 1) / (float)numRTT, 1 / (float)numRTT, 1 / (float)numRTT));
		canvases[i]->SetSRV(&rtts[i]->srv);
	}

}

DefferedRenderer::~DefferedRenderer()
{
	for (UINT i = 0; i < numRTT; i++)
		SAFE_DELETE(canvases[i]);
}

void DefferedRenderer::Update()
{
	__super::Update();

	srvs.resize(rtts.size());
	renderTargets.resize(rtts.size());
	for (UINT i = 0; i < rtts.size(); i++)
	{
		srvs[i] = rtts[i]->srv;
		renderTargets[i] = rtts[i]->rtv;
	}
	for (UINT i = 0; i < numRTT; i++)
		canvases[i]->Update();

}

void DefferedRenderer::Render()
{
	if (mesh == nullptr) return;

	DC->OMSetRenderTargets(1, preRenderedTexture->rtv, NULL);

	mesh->Set();//setVertexBuffer; indexBuffer;

	//worldBuffer
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	ZeroMemory(&mappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));

	DC->Map(*transform.WorldBuffer(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	// Copy Resource Data..
	memcpy(mappedResource.pData, transform.World(), sizeof(*transform.World()));

	// GPU Access UnLock Buffer Data..
	DC->Unmap(*transform.WorldBuffer(), 0);

	DC->VSSetConstantBuffers(0, 1, transform.WorldBuffer());

	//PS
	material->Set();

	DC->PSSetShaderResources(0, srvs.size(), srvs.data());

	DC->DrawIndexed(mesh->GetIndexCount(), 0, 0);


	if (mesh == nullptr) return;

	DC->OMSetRenderTargets(1, rtt.rtv, NULL);

	mesh->Set();//setVertexBuffer; indexBuffer;

	//worldBuffer
	ZeroMemory(&mappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));

	DC->Map(*transform.WorldBuffer(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	// Copy Resource Data..
	memcpy(mappedResource.pData, transform.World(), sizeof(*transform.World()));

	// GPU Access UnLock Buffer Data..
	DC->Unmap(*transform.WorldBuffer(), 0);

	DC->VSSetConstantBuffers(0, 1, transform.WorldBuffer());

	//PS
	material->Set();

	DC->PSSetShaderResources(0, srvs.size(), srvs.data());

	DC->DrawIndexed(mesh->GetIndexCount(), 0, 0);

	static bool temp_flag = false;


	//if (KeyBoard::Get()->Down(VK_F1))
	//	temp_flag = !temp_flag;

	if(temp_flag)
	for (UINT i = 0; i < numRTT; i++)
		canvases[i]->Render();
}

void DefferedRenderer::OnResize()
{
	for (UINT i = 0; i < numRTT; i++)
		rtts[i]->OnResize();

	rtt.OnResize();
}

void DefferedRenderer::ClearRenderTargetView()
{
	float transparent[4] = { 0.0f,0.0f,0.0f,0.0f };//todo: 구차나서 일단 이렇게 해놓음
	float white[4] = { 1.0f,1.0f,1.0f,1.0f };//todo: 구차나서 일단 이렇게 해놓음

	for (UINT i = 1; i < numRTT; i++)
		DC->ClearRenderTargetView(rtts[i]->rtv, white);

	DC->ClearRenderTargetView(rtts[0]->rtv, transparent);
	DC->ClearRenderTargetView(rtts[3]->rtv, transparent);
	DC->ClearRenderTargetView(rtts[7]->rtv, transparent);


	DC->ClearRenderTargetView(rtt.rtv, transparent);
}

void DefferedRenderer::CreateCanvas()
{
	name = "DefferedRenderTexture";

	VertexSet vertexSet;

	vertexSet.AddElementToDesc(sizeof(float) * 3, DataType::FLOAT, "POSITION");
	vertexSet.AddElementToDesc(sizeof(float) * 2, DataType::FLOAT, "UV");

	struct temp
	{
		float3 pos;
		float2 uv;
	};

	temp v1[4];

	v1[0].pos = float3(-1, +1, 0.0f);
	v1[0].uv = float2(0, 0);

	v1[1].pos = float3(+1, +1, 0.0f);
	v1[1].uv = float2(+1, 0);

	v1[2].pos = float3(-1, -1, 0.0f);
	v1[2].uv = float2(0, +1);

	v1[3].pos = float3(+1, -1, 0.0f);
	v1[3].uv = float2(+1, +1);

	vertexSet.AddData(v1, sizeof(v1));

	vector<UINT> indices =
	{
		0,1,2,
		2,1,3
	};

	mesh = new Mesh(vertexSet, indices.data(), indices.size(), L"CanvasVS.hlsl");


	MaterialDesc matDesc;
	matDesc.pixelShaderName = L"DefferedRenderPS.hlsl";
	matDesc.diffuseFileName = L"WoodCrate01.dds";
	material = new Material(matDesc);
}
