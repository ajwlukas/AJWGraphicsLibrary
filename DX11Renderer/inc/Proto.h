#pragma once

struct Instantiateds
{
	vector<Instance*> partInstances;
	vector<Instance*> boneInstances;
};
/// <summary>
/// 
/// InstancingObject 여러개 가지고 있는 애들, ex) 겐지 4파트
/// Bone또한 InstancingObject
/// 
/// 이녀석의 정보를 이용해 새로운 애를 찍어준다.
/// 
/// </summary>

class Proto
{
public:
	Proto();
	~Proto();

	void Update();
	void Render();

	string name;

	vector<InstancingObject*> parts;
	vector<InstancingObject*> bones;

	UINT FindIDByTransform(const Transform* t);

	void DeleteInstance(const Transform* t);

	void SetCurrentAnimation(const Transform* t, string clipName);

	vector<int> parentInfo;
	// parentInfo.size() == parts.size() + bones.size(), 
	//ex) parts size == 2, bones size == 1;
	//parentInfo[0] = 2 이면 , part[0]의 부모가 bones[0]
	//parentInfo[2] = 1 이면,  bones[0]의 부모가 parts[1]

	void Create(Transform* transform);//todo : 지우는거 코드 만들어 줘야 함
	void Create(Transform* transform, Vector3 posOffset, Vector3 rotOffset);//todo : 지우는거 코드 만들어 줘야 함
	//testCode
	vector<Instantiateds*> instantiateds;

	vector<Transform*> ts;


	void Clear();
};

