#include "pch_dx_11.h"
#include "Instants.h"
//https://docs.microsoft.com/en-us/windows/win32/direct3d11/overviews-direct3d-11-devices-downlevel-intro
//텍스쳐당 최대 크기 내용 있는 것으로 유추? Max Texture Dimension, 에 따라 좀 더 보완 할 예정
//Instants::Instants(InstancingObject* proto) : proto(proto), count(0)
//{
//	//약간 오브젝트 풀처럼 사용할 예정, 
//	for(UINT i = 0; i < MAX_INSTANTS_SIZE; i++)
//		instants.emplace_back(new Instance());
//
//	instanceBuffers.emplace_back(new InstancingBuffer<World, 10>());
//}
//
//Instants::~Instants()
//{
//	for (UINT i = 0; i < MAX_INSTANTS_SIZE; i++)
//		SAFE_DELETE(instants[i]);
//
//	for (IInstancingBuffer* buffer : instanceBuffers)
//		SAFE_DELETE(buffer);
//}
//
//
//void Instants::Update()
//{
//	for (UINT i = 0; i < count; i++)
//		instants[i]->Update();
//
//	for (UINT i = 0; i < instanceBuffers.size(); i++)
//	{
//		for (UINT j = 0; j < count; j++)
//		{
//			instanceBuffers[i]->UpdateData(j, instants[j]->dataAddress[i]);
//		}
//	}
//
//}
//
//void Instants::Render()
//{
//	for(UINT i = 0; i < instanceBuffers.size(); i++)
//		instanceBuffers[i]->Set();
//}
//
//void Instants::Clear()
//{
//	for (UINT i = 0; i < count; i++)
//		instants[i]->dataAddress.clear();
//
//	count = 0;
//}
//
//Instance* Instants::CreateInstance()
//{
//	//world Transform
//	instants[count]->instanceNum = count;
//
//	instants[count]->transform.pos = proto->transform.pos;
//	instants[count]->transform.scale = proto->transform.scale;
//	instants[count]->transform.rot = proto->transform.rot;
//
//	instants[count]->dataAddress.push_back(instants[count]->transform.World());
//
//	return instants[count++];
//}
//
//void Instants::DeleteInstance(const UINT instanceNum)
//{
//	if (count == 0) return;
//
//	Instance* temp = instants[instanceNum];
//
//	instants[instanceNum] = instants[count - 1];
//	instants[count - 1] = temp;
//	instants[count - 1]->dataAddress.clear();
//
//	UINT numTemp = instants[instanceNum]->instanceNum;
//	instants[instanceNum]->instanceNum = instants[count - 1]->instanceNum;
//	instants[count - 1]->instanceNum = numTemp;
//
//	count--;
//}
//
//void Instants::DeleteInstance(const Transform* t)
//{
//	for (UINT i = 0; i < count; i++)
//	{
//		if (instants[i]->transform.parent == t)
//		{
//			DeleteInstance(instants[i]->instanceNum);
//			break;
//		}
//	}
//}
//
//void Instants::SetCurrentAnimation(const UINT instanceNum, string clipName)
//{
//	Instance* temp = instants[instanceNum];
//
//	if(temp->animator != nullptr)
//		temp->animator->SetCurrentClip(clipName);
//}
//
//UINT Instants::GetCorrespondingInstanceNum(const Transform* t)
//{
//	for (UINT i = 0; i < count; i++)
//	{
//		if (instants[i]->transform.parent == t)
//		{
//			return instants[i]->instanceNum;
//		}
//	}
//}
