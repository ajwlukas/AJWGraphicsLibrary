#pragma once

#include <functional>

/// Resource<ResourceType>으로 사용, 사용 후 Return() 해줄 것
/// type 인자로는 ID3D 시리즈, delete가 아닌 Release 쓰는 애만 해줄 것
/// written by Ssreppa 22.06.28
/// 
/// Return() 자동으로 해줌, Leak으로 부터 Free
/// Copy()도 refCount 자동으로 늘려줌
/// 아무렇게나 써도 문제 없을 듯
/// written by Ssreppa 22.07.01

template <typename T>
class Resource
{
public:
	Resource() : resource(nullptr), Ret([]() {}), Copy([]() {}) {}
	~Resource()
	{
		Ret();
	}

	void* operator new(std::size_t size) = delete;//동적할당해서 사용하는 거 막음, 사용자가 delete 까먹을 경우를 대비

	Resource(const Resource& other)
	{
		if (this == &other) return;
		this->Copy = other.Copy;
		this->Ret = other.Ret;
		this->Copy();
		this->resource = other.resource;
	}

	void operator = (const Resource& other)
	{
		if (this == &other) return;
		this->Ret();
		this->Copy = other.Copy;
		this->Ret = other.Ret;
		this->Copy();
		this->resource = other.resource;
	}

	operator T* () { return resource; }
	operator T** () { return &resource; }

	T* resource;

	void Release() = delete;

	void Return()
	{
		Ret();
		Ret = []() {};
		Copy = []() {};
	}

	//이거 숨겨주고 싶은데 friend 걸기 좀 빡세서 미뤄둠, 사용자는 사용하지 말 것 일단.
	std::function<void()> Copy;//ex) shared count increse용
	std::function<void()> Ret;
};
