#include "pch_dx_11.h"
#include "Object.h"

Object::Object()
	:mesh(nullptr), material(nullptr)
{
}

Object::~Object()
{

	if (mesh != nullptr)
		delete mesh;
	if (material != nullptr)
		delete material;
}

void Object::Update()
{
	transform.UpdateWorld();
}

void Object::Render()
{
	if (mesh == nullptr) return;

	SetPipeLine();
	Draw();
}

void Object::SetPipeLine()
{
	mesh->Set();//setVertexBuffer; indexBuffer;

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
}

void Object::Draw()
{
	DC->DrawIndexed(mesh->GetIndexCount(), 0, 0);
}
