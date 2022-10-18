#include "pch_dx_11.h"
#include "Pipeline.h"

Pipeline::Pipeline(ID3D11DeviceContext* dc)
	:dc(dc), lastMaterial(nullptr), lastMesh(nullptr)
{
}

Pipeline::~Pipeline()
{
}

void Pipeline::SetMesh(Mesh* mesh)
{
	lastMesh = mesh;
}

void Pipeline::SetMaterial(Material* material)
{
	lastMaterial = material;
}

void Pipeline::Draw()
{
	dc->DrawIndexed(lastMesh->GetIndexCount(), 0, 0);
}
