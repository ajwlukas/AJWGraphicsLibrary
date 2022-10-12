#include "pch_dx_11.h"
#include "Proto.h"

Proto::Proto()
	:name("")
{
}

Proto::~Proto()
{
	for (InstancingObject* part : parts)
		SAFE_DELETE(part);
	for (InstancingObject* bone : bones)
		SAFE_DELETE(bone);
}

void Proto::Update()
{
	for (InstancingObject* bone : bones)
		bone->Update();
	for (InstancingObject* part : parts)
		part->Update();
}

void Proto::Render()
{
	/*
	for (InstancingObject* bone : bones)
		bone->Render();*/
	for (InstancingObject* part : parts)
		part->Render();
}

UINT Proto::FindIDByTransform(const Transform* t)
{
	for (UINT i = 0; i < ts.size(); i++)
	{
		if(ts[i]->parent == t)
			return i;
	}

	return 0;
}

void Proto::DeleteInstance(const Transform* t)
{
	UINT id = FindIDByTransform(t);


	for (auto p : parts)
		p->DeleteInstance(id);

	for (auto b : bones)
		b->DeleteInstance(id);

	SAFE_DELETE(instantiateds[id]);
	instantiateds[id] = instantiateds.back();
	instantiateds.pop_back();

	SAFE_DELETE(ts[id]);
	ts[id] = ts.back();
	ts.pop_back();
}

void Proto::SetCurrentAnimation(const Transform* t, string clipName)
{
	UINT id = FindIDByTransform(t);

	for (auto p : parts)
		p->SetCurrentAnimation(id, clipName);

	for (auto b : bones)
		b->SetCurrentAnimation(id, clipName);
}

void Proto::Create(Transform* transform)
{
	Transform* ret = new Transform();

	instantiateds.emplace_back(new Instantiateds());
	Instantiateds* object = instantiateds.back();
	object->partInstances.reserve(parts.size());
	object->boneInstances.reserve(bones.size());

	for (UINT i = 0; i < parts.size(); i++)
		object->partInstances.emplace_back(parts[i]->CreateInstance());

	for (UINT i = 0; i < bones.size(); i++)
		object->boneInstances.emplace_back(bones[i]->CreateInstance());

	int partsSize = object->partInstances.size();
	int boneSize = object->boneInstances.size();

	for (UINT i = 0; i < partsSize; i++)//파트들을 돌며
	{
		int parentIndex = parentInfo[i];
		if (parentIndex == -1)//부모가 없다면 == 헤드라면
		{
			object->partInstances[i]->transform.parent = ret;
			continue;
		}

		if (parentIndex < partsSize)//부모가 파츠중 하나라면
			object->partInstances[i]->transform.parent = &object->partInstances[parentIndex]->transform;
		else//본이 부모라면, 이런경우가 있나 싶지만..
			object->partInstances[i]->transform.parent = &object->boneInstances[parentIndex - partsSize]->transform;
	}

	for (UINT i = 0; i < boneSize; i++)//본들을 돌며
	{
		int parentIndex = parentInfo[i + partsSize];
		if (parentIndex == -1)//부모가 없다면 == 헤드라면
		{
			object->boneInstances[i]->transform.parent = ret;
			continue;
		}

		if (parentIndex < partsSize)//부모가 파츠중 하나라면, 이런경우가 있나 싶지만..
			object->boneInstances[i]->transform.parent = &object->partInstances[parentIndex]->transform;
		else//본이 부모라면
			object->boneInstances[i]->transform.parent = &object->boneInstances[parentIndex - partsSize]->transform;
	}

	for (UINT i = 0; i < partsSize; i++)
	{
		if (object->partInstances[i]->skinner != nullptr)
		{
			object->partInstances[i]->transform.parent = nullptr;//피부는 본을 따라가기에
			object->partInstances[i]->skinner->ConnectRefBones(&object->boneInstances);
		}
	}

	ret->parent = transform;
	ts.push_back(ret);
}

void Proto::Create(Transform* transform, Vector3 posOffset, Vector3 rotOffset)
{
	Transform* ret = new Transform();

	instantiateds.emplace_back(new Instantiateds());
	Instantiateds* object = instantiateds.back();
	object->partInstances.reserve(parts.size());
	object->boneInstances.reserve(bones.size());

	for (UINT i = 0; i < parts.size(); i++)
		object->partInstances.emplace_back(parts[i]->CreateInstance());

	for (UINT i = 0; i < bones.size(); i++)
		object->boneInstances.emplace_back(bones[i]->CreateInstance());

	int partsSize = object->partInstances.size();
	int boneSize = object->boneInstances.size();

	for (UINT i = 0; i < partsSize; i++)//파트들을 돌며
	{
		int parentIndex = parentInfo[i];
		if (parentIndex == -1)//부모가 없다면 == 헤드라면
		{
			object->partInstances[i]->transform.parent = ret;
			continue;
		}

		if (parentIndex < partsSize)//부모가 파츠중 하나라면
			object->partInstances[i]->transform.parent = &object->partInstances[parentIndex]->transform;
		else//본이 부모라면, 이런경우가 있나 싶지만..
			object->partInstances[i]->transform.parent = &object->boneInstances[parentIndex - partsSize]->transform;
	}

	for (UINT i = 0; i < boneSize; i++)//본들을 돌며
	{
		int parentIndex = parentInfo[i + partsSize];
		if (parentIndex == -1)//부모가 없다면 == 헤드라면
		{
			object->boneInstances[i]->transform.parent = ret;
			continue;
		}

		if (parentIndex < partsSize)//부모가 파츠중 하나라면, 이런경우가 있나 싶지만..
			object->boneInstances[i]->transform.parent = &object->partInstances[parentIndex]->transform;
		else//본이 부모라면
			object->boneInstances[i]->transform.parent = &object->boneInstances[parentIndex - partsSize]->transform;
	}

	for (UINT i = 0; i < partsSize; i++)
	{
		if (object->partInstances[i]->skinner != nullptr)
		{
			object->partInstances[i]->transform.parent = nullptr;//피부는 본을 따라가기에
			object->partInstances[i]->skinner->ConnectRefBones(&object->boneInstances);
		}
	}

	ret->pos += posOffset;
	ret->rot += rotOffset;
	ret->parent = transform;
	ts.push_back(ret);
}

void Proto::Clear()
{
	for (auto inst : instantiateds)
		SAFE_DELETE(inst);

	for (auto t : ts)
		SAFE_DELETE(t);

	for (InstancingObject* bone : bones)
		bone->ClearInstants();

	for (InstancingObject* part : parts)
		part->ClearInstants();
}
