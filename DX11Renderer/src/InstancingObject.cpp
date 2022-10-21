#include "pch_dx_11.h"
//
//InstancingObject::InstancingObject()
//	:animator(nullptr), mesh(nullptr), material(nullptr), skinner(nullptr)
//{
//	instants = new Instants(this);
//}
//
//InstancingObject::~InstancingObject()
//{
//	delete instants;
//
//	if (mesh != nullptr)
//		delete mesh;
//	if (material != nullptr)
//		delete material;
//}
//
//void InstancingObject::Update()
//{
//		instants->Update();
//}
//
//void InstancingObject::Render()
//{
//	if (mesh == nullptr) return;
//
//	SetPipeLine();
//	Draw();
//}
//
//void InstancingObject::SetPipeLine()
//{
//	mesh->Set();//setVertexBuffer; indexBuffer;
//
//	//worldBuffer
//	instants->Render();
//
//	//PS
//	material->Set();
//}
//
//void InstancingObject::Draw()
//{
//	DC->DrawIndexedInstanced(mesh->GetIndexCount(), instants->count, 0, 0, 0);
//}
//
//Instance* InstancingObject::CreateInstance()
//{
//	Instance* ret = instants->CreateInstance();
//
//	if (animator != nullptr)//원형이 animator를 가지고 있다면
//	{
//		ret->animator = new Animator(*animator);
//		ret->animator->SetTransform(&ret->transform);
//	}
//	if (skinner != nullptr)
//	{
//		ret->skinner = new Skinner(*skinner);
//		ret->dataAddress.push_back(ret->skinner->Matrixes());
//	}
//
//	return ret;
//}
//
//void InstancingObject::DeleteInstance(const Transform* t)
//{
//	for (UINT i = 0; i < instants->count; i++)
//	{
//		instants->DeleteInstance(t);
//	}
//}
