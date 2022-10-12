#pragma once
#define MAX_INSTANTS_SIZE 100
#define MAX_BONE_SIZE 100
/// <summary>
/// 오브젝트마다 Instants를 가지도록 했다.
/// CreateInstance를 통해 Instance*를 리턴받아 조작할 수 있게끔 만들었다.
/// SRV에 데이터를 넣어 사용한다.
/// </summary>
//인스턴스의 실 데이터


class IInstancingBuffer abstract
{
public:
	void UpdateData(UINT instanceID, void* src)
	{
		memcpy(reinterpret_cast<char*>(data) + instanceID * dataSize, src, dataSize);
	}
	
	
	Resource<ID3D11Buffer>& Buffer() { return buffer; }
	Resource<ID3D11ShaderResourceView>& SrvBuffer() { return srvBuffer; }

	void Set()
	{


		D3D11_MAPPED_SUBRESOURCE mappedResource;
		ZeroMemory(&mappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));

		DC->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

		// Copy Resource Data..
		memcpy(mappedResource.pData, data, dataSize * 100);

		// GPU Access UnLock Buffer Data..
		DC->Unmap(buffer, 0);

		//DC->UpdateSubresource(buffer, 0, 0, data, 0, 0);
		DC->VSSetShaderResources(slot, 1, srvBuffer);
	}

protected:
	void* data;//따로 생성한 이유, 메모리에 연속적으로 위치시키기 위해서
	size_t dataSize;
	UINT slot;
	Resource<ID3D11Buffer> buffer;//업데이트용
	Resource<ID3D11ShaderResourceView> srvBuffer;//buffer와 묶여있다
};

template<typename T, UINT SLOT>
class InstancingBuffer : public IInstancingBuffer
{
public:
	InstancingBuffer()
	{
		data = new T[MAX_INSTANTS_SIZE];

		slot = SLOT;
		dataSize = sizeof(T);

		D3D11_BUFFER_DESC desc = {};
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.ByteWidth = sizeof(T) * MAX_INSTANTS_SIZE;
		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		desc.MiscFlags = 0;
		desc.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA initData;
		initData.pSysMem = data;

		RESOURCES->buffers->Create(buffer, desc, &initData);

		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
		srvDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
		srvDesc.Buffer.FirstElement = 0;
		srvDesc.Buffer.NumElements = sizeof(T) * MAX_INSTANTS_SIZE / 16;//1엘레멘트당 크기 = sizeof(float4) = 16

		RESOURCES->srvs->Create(srvBuffer, srvDesc, buffer);
	}
	~InstancingBuffer()
	{
		delete[] data;
	}

};

struct World
{
	World() : world(XMMatrixIdentity())
	{

	}
	Matrix world;
};

struct Bones
{
	Bones() : bones{}
	{

	}
	Matrix bones[MAX_BONE_SIZE];
};

//인스턴스 하나의 정보
class Instance
{
public:
	Instance() : instanceNum(0), animator(nullptr), skinner(nullptr)
	{}
	~Instance() 
	{
		if (animator != nullptr) delete animator;
		if (skinner != nullptr) delete skinner;
	}

	void Update()
	{
		if (animator != nullptr)//원형이 animator를 가지고 있다면
			animator->Update();

		if (skinner != nullptr)//todo: 조건 달아줄 것, skinning쓰는 애들만 쓰도록
			skinner->Update();

		transform.UpdateWorld();
	}

	Transform transform;
	UINT instanceNum;

	Animator* animator;
	Skinner* skinner;

	vector<void*> dataAddress;
};

//인스턴스들의 모음, 인스턴스들의 데이터를 관리한다.
class Instants
{
public:
	Instants(InstancingObject* proto);
	~Instants();

	void Update();
	void Render();

	void Clear();

	Instance* CreateInstance();

	void DeleteInstance(const UINT instanceNum);
	void DeleteInstance(const Transform* t);// todo : 말도 안되는 코드지만... 일단 프로젝트 해야하니...
	void SetCurrentAnimation(const UINT instanceNum, string clipName);


	UINT GetCorrespondingInstanceNum(const Transform* t);

	template<typename T, UINT SLOT>
	void AddBuffer();

private:
	InstancingObject* proto;

	vector<Instance*> instants;

public:

	vector<IInstancingBuffer*> instanceBuffers;

	UINT count;
};

template<typename T, UINT SLOT>
inline void Instants::AddBuffer()
{
	instanceBuffers.emplace_back(new InstancingBuffer<T, SLOT>());
}

