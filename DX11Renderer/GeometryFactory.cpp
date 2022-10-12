#include "pch_dx_11.h"
#include "GeometryFactory.h"

#include "Sphere.h"
#include "Box.h"
#include "Capsule.h"
//
//GeoMetryFactory::GeoMetryFactory()
//{
//	sphereProto = new Sphere();
//	boxProto = new Box();
//
//	pointLights = new PointLightsBuffer();
//}
//
//GeoMetryFactory::~GeoMetryFactory()
//{
//	SAFE_DELETE(pointLights);
//	SAFE_DELETE(boxProto);
//	SAFE_DELETE(sphereProto);
//
//	for (auto proto : protoss)
//		SAFE_DELETE(proto.second);
//}
//
//void GeoMetryFactory::CreateGeo(string fileName, Transform* transform)
//{
//	if (protoss.find(fileName) == protoss.end())//미리 만들어진게 없다면
//	{
//		aseLoader.LoadASE(fileName);
//		
//		protoss[fileName] = new Proto();
//
//		aseLoader.CreateObjectTest(*protoss[fileName]);
//	}
//
//	protoss[fileName]->Create(transform);
//}
//
//void GeoMetryFactory::CreateGeo(string fileName, Transform* transform, Vector3 posOffset, Vector3 rotOffset)
//{
//	if (protoss.find(fileName) == protoss.end())//미리 만들어진게 없다면
//	{
//		aseLoader.LoadASE(fileName);
//
//		protoss[fileName] = new Proto();
//
//		aseLoader.CreateObjectTest(*protoss[fileName]);
//	}
//
//	protoss[fileName]->Create(transform, posOffset, rotOffset);
//}
//
//void GeoMetryFactory::DeleteGeo(string fileName, const Transform* transform)
//{
//	Proto* proto = protoss.at(fileName);
//
//	proto->DeleteInstance(transform);
//}
//
//void GeoMetryFactory::SetCurrentAnimation(string fileName, const Transform* transform, string clipName)
//{
//	Proto* proto = protoss.at(fileName);
//
//	proto->SetCurrentAnimation(transform, clipName);
//}
//
//void GeoMetryFactory::CreateSphere(Transform* transform)
//{
//	Instance* inst = sphereProto->CreateInstance();
//	inst->transform.parent = transform;
//}
//void GeoMetryFactory::DeleteSphere(const Transform* transform)
//{
//	sphereProto->DeleteInstance(transform);
//}
//void GeoMetryFactory::CreateBox(Transform* transform)
//{
//	int a = 120;
//	Instance* inst = boxProto->CreateInstance();
//	inst->transform.parent = transform;
//	//boxProto->
//}
//
//void GeoMetryFactory::DeleteBox(const Transform* transform)
//{
//	boxProto->DeleteInstance(transform);
//}
//
//void GeoMetryFactory::CreateCapsule(Transform* transform, float radius, float height)
//{
//	capsules.emplace_back(new Capsule(radius, height));
//	capsules.back()->transform.parent = transform;
//}
//
//void GeoMetryFactory::DeleteCapsule(const Transform* transform)
//{
//	for (UINT i = 0; i < capsules.size(); i++)
//	{
//		if (capsules[i]->transform.parent == transform)
//		{
//			Capsule* temp = capsules[i];
//			capsules[i] = capsules.back();
//			capsules.back() = temp;
//
//			SAFE_DELETE(temp);
//			capsules.pop_back();
//		}
//	}
//}
//
//void GeoMetryFactory::AddPointLight(float x, float y, float z, float r, float g, float b, float range, float intensity)
//{
//	pointLights->AddLightInfo({ x, y, z }, intensity, { r,g,b },range);
//}
//
//void GeoMetryFactory::SubAllPointLights()
//{
//	pointLights->SubAllLights();
//}
//
//void GeoMetryFactory::BakeProto(string fileName)
//{
//	if (protoss.find(fileName) == protoss.end())//미리 만들어진게 없다면
//	{
//		aseLoader.LoadASE(fileName);
//
//		protoss[fileName] = new Proto();
//
//		aseLoader.CreateObjectTest(*protoss[fileName]);
//	}
//}
//
//void GeoMetryFactory::Update()
//{
//	for (auto proto : protoss)
//		proto.second->Update();
//
//	sphereProto->Update();
//	boxProto->Update();
//	for (Capsule* c : capsules)
//		c->Update();
//}
//
//void GeoMetryFactory::Render()
//{
//	for (auto proto : protoss)
//		proto.second->Render();
//
//
//
//	//if (KeyBoard::Get()->Down(VK_F1))
//	//	renderCollider = !renderCollider;
//
//	if (renderCollider)
//	{
//		sphereProto->Render();
//		boxProto->Render();
//		for (Capsule* c : capsules)
//			c->Render();
//	}
//}
//
//void GeoMetryFactory::Clear()
//{
//	for (auto proto : protoss)
//		proto.second->Clear();
//
//	sphereProto->ClearInstants();
//	boxProto->ClearInstants();
//	for (Capsule* c : capsules)
//		SAFE_DELETE(c);
//}
