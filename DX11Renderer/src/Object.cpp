#include "pch_dx_11.h"

Object::Object(Proto* belongsTo)
	:belongsTo(belongsTo), animator(nullptr), mesh(nullptr), material(nullptr), skinner(nullptr)
{
	instants = new Instants(this);
	if (belongsTo != nullptr)
	{
		this->name = belongsTo->name;
		//this->transform.parent = &(belongsTo->transform);
	}
}

Object::Object()
	:belongsTo(nullptr), animator(nullptr), mesh(nullptr), material(nullptr), skinner(nullptr)
{
	instants = new Instants(this);
}

Object::~Object()
{
	delete instants;

	if (mesh != nullptr)
		delete mesh;
	if (material != nullptr)
		delete material;
	if (animator != nullptr)
		delete animator;
	if (skinner != nullptr)
		delete skinner;
}

void Object::Update()
{

	if (belongsTo != nullptr && belongsTo->name == "genji")
		instants->Update();
	else
	{

	/*	if (animator != nullptr)
			animator->Update();
		if (skinner != nullptr)
			skinner->Update();*/
		transform.UpdateWorld();
	}

}

void Object::Render()
{
	if (mesh == nullptr) return;

	//skinningBuffer
	if (skinner != nullptr)
	{
		DC->UpdateSubresource(*skinner->AnimBuffer(), 0, 0, skinner->Matrixes(), 0, 0);
		DC->VSSetConstantBuffers(2, 1, skinner->AnimBuffer());
	}

	mesh->Set();//setVertexBuffer; indexBuffer;

	//worldBuffer
	if (belongsTo != nullptr && belongsTo->name == "genji")
	instants->Update();
	else
	{
		DC->UpdateSubresource(*transform.WorldBuffer(), 0, 0, transform.World(), 0, 0);
		DC->VSSetConstantBuffers(0, 1, transform.WorldBuffer());
	}

	//PS
	material->Set();

	if (belongsTo != nullptr && belongsTo->name == "genji")
	DC->DrawIndexedInstanced(mesh->GetIndexCount(), instants->count,0, 0,0);
	else
	DC->DrawIndexed(mesh->GetIndexCount(), 0, 0);
}
