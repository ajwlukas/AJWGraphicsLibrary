#include "pch_dx_11.h"
#include "Canvas.h"

CanvasManager  Canvas::manager;
Canvas::Canvas(float posLeftRatio, float posTopRatio, float widthRatio, float heightRatio, UINT layer)
	:posLeftRatio(posLeftRatio), posTopRatio(posTopRatio), widthRatio(widthRatio), heightRatio(heightRatio), layer(layer)
{
	transform.pos.x = -(1.0f - widthRatio) + posLeftRatio * 2.0f;
	transform.pos.y = (1.0f - heightRatio) - posTopRatio * 2.0f;
	//transform.pos.z += 0.1f;

	transform.scale.x = widthRatio;
	transform.scale.y = heightRatio;
	CreateCanvas();
}

Canvas::~Canvas()
{
}

void Canvas::Update()
{
	__super::Update();
}

void Canvas::Render()
{
	function<void()> rend = [&]()
	{
		if (mesh == nullptr) return;

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

		if (srv != nullptr)
			DC->PSSetShaderResources(0, 1, *srv);

		DC->DrawIndexed(mesh->GetIndexCount(), 0, 0);
	};


	manager.Reserve(make_pair(layer, rend));
}

void Canvas::ReSizeCanvas(float in_posLeftRatio, float in_posTopRatio, float in_widthRatio, float in_heightRatio)
{
	posLeftRatio = in_posLeftRatio;
	posTopRatio = in_posTopRatio;
	widthRatio = in_widthRatio;
	heightRatio = in_heightRatio;

	transform.pos.x = -(1.0f - widthRatio) + posLeftRatio * 2.0f;
	transform.pos.y = (1.0f - heightRatio) - posTopRatio * 2.0f;

	transform.scale.x = widthRatio;
	transform.scale.y = heightRatio;

	ReCreateCanvas();
}

void Canvas::CreateCanvas()
{
	name = "Canvas";

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
	matDesc.pixelShaderName = L"CanvasPS.hlsl";
	matDesc.diffuseFileName = L"WoodCrate01.dds";
	material = new Material(matDesc);
}

void Canvas::ReCreateCanvas()
{
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

	SAFE_DELETE(mesh);
	mesh = new Mesh(vertexSet, indices.data(), indices.size(), L"CanvasVS.hlsl");

	MaterialDesc matDesc;
	matDesc.pixelShaderName = L"CanvasPS.hlsl";
	matDesc.diffuseFileName = L"WoodCrate01.dds";
	SAFE_DELETE(material);
	material = new Material(matDesc);
}