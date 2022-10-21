#include "pch_dx_11.h"
#include "Sphere.h"
//
//Sphere::Sphere()
//    :sectorCount(10), stackCount(10)
//{
//	name = "Sphere";
//
//	RESOURCES->rasterStates->GetWireMode(wireFrame);
//	RESOURCES->rasterStates->GetDefault(defaultRasterizerState);
//    Create();
//}
//
//Sphere::~Sphere()
//{
//}
//
//void Sphere::Update()
//{
//    __super::Update();
//}
//
//void Sphere::Render()
//{
//	__super::SetPipeLine();
//
//	DC->RSSetState(wireFrame);
//
//	__super::Draw();
//
//	DC->RSSetState(defaultRasterizerState);
//}
//
//#define PI 3.141592f
//void Sphere::Create()
//{
//    VertexSet vertexSet;
//
//    vertexSet.AddElementToDesc(sizeof(float) * 3, DataType::FLOAT, "POSITION");
//
//	float radius = 1.f;
//
//	std::vector<UINT> indices;
//
//	struct TempVertex
//	{
//		float _position[3];
//	};
//	TempVertex topVertex;
//	TempVertex bottomVertex;
//
//	topVertex._position[0] = 0.f;
//	topVertex._position[1] = radius;
//	topVertex._position[2] = 0.f;
//
//	bottomVertex._position[0] = 0.f;
//	bottomVertex._position[1] = -radius;
//	bottomVertex._position[2] =  0.f;
//
//	vertexSet.AddData(topVertex._position, sizeof(topVertex._position));
//
//	//vertices.push_back(topVertex);
//
//	UINT stackCount = 50;
//	UINT sliceCount = 50;
//
//	float phiStep = PI / stackCount;
//	float thetaStep = 2.0f * PI / sliceCount;
//
//	// Compute vertices for each stack ring (do not count the poles as rings).
//	for (UINT i = 1; i <= stackCount - 1; ++i)
//	{
//		float phi = i * phiStep;
//
//		// Vertices of ring.
//		for (UINT j = 0; j <= sliceCount; ++j)
//		{
//			float theta = j * thetaStep;
//
//			TempVertex v;
//
//			// spherical to cartesian
//			v._position[0] = radius * sinf(phi) * cosf(theta);
//			v._position[1] = radius * cosf(phi);
//			v._position[2] = radius * sinf(phi) * sinf(theta);
//
//
//			vertexSet.AddData(v._position, sizeof(v._position));
//		}
//	}
//	vertexSet.AddData(bottomVertex._position, sizeof(bottomVertex._position));
//
//	for (UINT i = 1; i <= sliceCount; ++i)
//	{
//		indices.push_back(0);
//		indices.push_back(i + 1);
//		indices.push_back(i);
//	}
//
//	UINT baseIndex = 1;
//	UINT ringVertexCount = sliceCount + 1;
//	for (UINT i = 0; i < stackCount - 2; ++i)
//	{
//		for (UINT j = 0; j < sliceCount; ++j)
//		{
//			indices.push_back(baseIndex + i * ringVertexCount + j);
//			indices.push_back(baseIndex + i * ringVertexCount + j + 1);
//			indices.push_back(baseIndex + (i + 1) * ringVertexCount + j);
//			indices.push_back(baseIndex + (i + 1) * ringVertexCount + j);
//			indices.push_back(baseIndex + i * ringVertexCount + j + 1);
//			indices.push_back(baseIndex + (i + 1) * ringVertexCount + j + 1);
//		}
//	}
//
//	// South pole vertex was added last.
//	UINT southPoleIndex = (UINT)(
//		(stackCount + 1) * (sliceCount + 1) + 1);
//
//	// Offset the indices to the index of the first vertex in the last ring.
//	baseIndex = southPoleIndex - ringVertexCount;
//
//	for (UINT i = 0; i < sliceCount; ++i)
//	{
//		indices.push_back(southPoleIndex);
//		indices.push_back(baseIndex + i);
//		indices.push_back(baseIndex + i + 1);
//	}
//
//	mesh = new Mesh(vertexSet, indices.data(), indices.size(), L"PosVS_Instanced.hlsl", D3D_PRIMITIVE_TOPOLOGY_LINELIST);
//
//    MaterialDesc matDesc;
//    matDesc.pixelShaderName = L"PosPS.hlsl";
//
//    material = new Material(matDesc);
//}
