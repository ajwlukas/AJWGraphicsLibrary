#include "pch_dx_11.h"
#include "Capsule.h"

Capsule::Capsule(float radius, float height)
	:sectorCount(10), stackCount(10), radius(radius), height(height)
{
	name = "Capsule";

	RESOURCES->rasterStates->GetWireMode(wireFrame);
	RESOURCES->rasterStates->GetDefault(defaultRasterizerState);
	Create();
}

Capsule::~Capsule()
{
}

void Capsule::Update()
{
	__super::Update();
}

void Capsule::Render()
{
	__super::SetPipeLine();

	DC->RSSetState(wireFrame);

	__super::Draw();

	DC->RSSetState(defaultRasterizerState);
}

void Capsule::Create()
{
	float phiStep = XM_PI / stackCount;
	float thetaStep = XM_2PI / sectorCount;
	VertexSet vertexSet;
	vertexSet.AddElementToDesc(sizeof(float) * 3, DataType::FLOAT, "POSITION");

	struct TempVertex
	{
		float position[3];

	};


	for (UINT i = 0; i <= stackCount; i++)
	{
		float phi = i * phiStep;

		for (UINT j = 0; j <= sectorCount; j++)
		{
			float theta = j * thetaStep;

			TempVertex vertex;

			vertex.position[0] = sin(phi) * cos(theta) * radius;
			vertex.position[1] = cos(phi) * radius;
			vertex.position[2] = sin(phi) * sin(theta) * radius;

			if (vertex.position[1] > 0)
			{
				vertex.position[1] += height * 0.5f;
			}
			else
			{
				vertex.position[1] -= height * 0.5f;
			}


			vertexSet.AddData(vertex.position, sizeof(vertex.position));
		}
	}

	std::vector<UINT> indices;

	for (UINT i = 0; i < stackCount; i++)
	{
		for (UINT j = 0; j < sectorCount; j++)
		{
			indices.emplace_back((sectorCount + 1) * i + j);//0
			indices.emplace_back((sectorCount + 1) * i + j + 1);//1

			indices.emplace_back((sectorCount + 1) * i + j);//0
			indices.emplace_back((sectorCount + 1) * (i + 1) + j);//1
		}
	}

	mesh = new Mesh(vertexSet,
		indices.data(), indices.size(), L"PosVS.hlsl", D3D_PRIMITIVE_TOPOLOGY_LINELIST);

	MaterialDesc matDesc;
	matDesc.pixelShaderName = L"PosPS.hlsl";

	material = new Material(matDesc);
}
