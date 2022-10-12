#pragma once

#include "Mesh.h"

class QuadMesh : public Mesh
{
public:
	QuadMesh();
	~QuadMesh();

	static VertexSet quadVertexSet;
	static UINT quadIndicies[6];
};