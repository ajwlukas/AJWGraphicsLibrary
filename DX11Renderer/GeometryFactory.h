#pragma once
/// <summary>
/// filename을 통해 원형을 생성해주고, 미리 생성된 원형을 통해 InstancedObject를 Transform에 연결 시켜주는 클래스
/// 
/// 220801 written by Ssreppa
/// </summary>
/// 
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include "Transform.h"
#include "ASELoader.h"
#include "Proto.h"

#include "PointLightsBuffer.h"

class Sphere;
class Box;
class Capsule;


class GeoMetryFactory
{
//public:
//	GeoMetryFactory();
//	~GeoMetryFactory();
//
//	void CreateGeo(std::string fileName, Transform* transform, Vector3 posOffset, Vector3 rotOffset);
//	void CreateGeo(std::string fileName, Transform* transform);
//	void DeleteGeo(std::string fileName, const Transform* transform);
//	void SetCurrentAnimation(std::string fileName, const Transform* transform, std::string clipName);
//
//	void CreateSphere(Transform* transform);
//	void DeleteSphere(const Transform* transform);
//
//	void CreateBox(Transform* transform);
//	void DeleteBox(const Transform* transform);
//
//	void CreateCapsule(Transform* transform, float radius, float height);
//	void DeleteCapsule(const Transform* transform);
//
//	void AddPointLight(float x, float y, float z, float r, float g, float b, float range, float intensity = 2.0f);
//	void SubAllPointLights();
//
//	//void CreateCanvas(wstring fileName, float posLeftRatio, float posTopRatio, float widthRatio, float heightRatio);
//
//	void BakeProto(std::string fileName);
//
//	void Update();
//	void Render();
//
//	void Clear();
//
//private:
//	ASELoader aseLoader;
//	std::unordered_map<std::string, Proto*> protoss;//원형이 되는 GeoObject들
//
//	Sphere* sphereProto;
//	Box* boxProto;
//	std::vector<Capsule*> capsules;
//
//	PointLightsBuffer* pointLights;
//
//	bool renderCollider =false;
};