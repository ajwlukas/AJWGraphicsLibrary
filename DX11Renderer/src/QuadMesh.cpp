#include "pch_dx_11.h"
#include "QuadMesh.h"

VertexSet Create();
VertexSet QuadMesh::quadVertexSet = Create();
UINT QuadMesh::quadIndicies[6] =
{
	0,1,2,
	2,1,3
};
QuadMesh::QuadMesh()
	:Mesh(quadVertexSet, quadIndicies,  sizeof(quadIndicies) / sizeof(quadIndicies[0]), L"CanvasVS.hlsl")
{
}

QuadMesh::~QuadMesh()
{
}

VertexSet Create()
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

	return vertexSet;
}