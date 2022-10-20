#pragma once

#include "Vertex.h"

class ASELoader
{
/// general Code
private:
	/// datas starts here
	struct DiffuseMap
	{
		string fileName;
	};
	struct NormalMap
	{
		string fileName;
	};

	struct ASEMat
	{
		string name;
		float4 ambient;
		float4 diffuse;
		float4 specular;
		DiffuseMap diffuseMap;

		NormalMap normalMap;
	};
	vector<ASEMat> aseMats;
	UINT matCount;

	struct AseTransform
	{
		float3 row0, row1, row2, row3;
		float3 pos, rotAxis, scale, scaleAxis;
		float rotAngle, scaleAxisAngle;
	};

	struct TVert
	{
		float u, v, w;
	};


	struct ASEMeshWeight
	{
		UINT index;
		float weight;
	};

	struct ASEMesh
	{
		float timeValue;

		UINT numVertex;
		vector<float3> vertexList;

		UINT numFaces;
		vector<vector<UINT>> faceList;

		UINT numTVertex;
		vector<TVert> tVertList;

		UINT numTFaces;
		vector<vector<UINT>> TFaceList;

		vector<vector<float3>> normals;

		vector<Vector3> tangents;//ASE에 들어있는 정보는 아니다.

	};

	struct AnimClipPos
	{
		vector<float> time;
		vector<float3> controlPos;
	};
	
	struct AnimClipRot
	{
		vector<float> time;
		vector<float4> controlRot;//axis float3 + rot flaot
	};

	struct ASEAnimClip
	{
		string name;
		AnimClipPos posClip;
		AnimClipRot rotClip;
	};

	enum class ObjectType
	{
		NONE,
		HELPER,
		GEO,
	};


	struct ASEObject
	{
		ObjectType type;
		string name;
		string parentName;
		AseTransform transform;
		vector<ASEAnimClip*> animClip;
		ASEMesh mesh;

		int matRef = -1;
		vector<string> boneList;
		vector<vector<ASEMeshWeight>> weights;//weights[vertexIndex][weightIndex]
	};
	vector<ASEObject*> aseObjects;
	vector<ASEObject*> aseBones;
	/// data ends here

	
public:
	void LoadASE(string fileName);
private:
	void InitVariables();

private:
	string fileName;

	void ReadHelperObject();

	void ReadMaterials();
	void ReadMaterial();
	void ReadDiffuseMap(UINT curMatIndex);
	void ReadNormalMap(UINT curMatIndex);


	void ReadGeoObject();
	void ReadTransform(AseTransform& trans);

	void ReadAnimClip(ASEAnimClip* anim);

	//mesh
	void ReadMesh(ASEMesh& mesh);
	void ReadVertexList(vector<float3>& v);
	void ReadFaceList(vector<vector<UINT>>& f);

	//texture
	void ReadTVertList(vector<TVert>& tV);
	void ReadTFaceList(vector<vector<UINT>>& tF);

	//normal
	void ReadMeshNormals(vector<vector<float3>>& fN);

	//weight
	void ReadBones(vector<string>& bones);
	void ReadBone(string& bone);
	void ReadWeights(vector<vector<ASEMeshWeight>>& weights);
	void ReadWeight(vector<ASEMeshWeight>& weight);
public:
	ASELoader();
	~ASELoader();

	private:
	char tokenString[256] = {};
	class ASELexer* aseLexer;

public:
	///custom Code

	//수업때 짠 함수
	void CreateObject(Proto& object);

	//RadioNight만을 위한 함수
	void CreateObjectTest(Proto& object);
	void CreateGeometryTest(InstancingObject* dest, ASEObject* src);
	void CreateMaterialTest(InstancingObject* dest, ASEObject* src);
	void CreateTangentsTest(ASEObject* src);
	void CreateAnimClipTest(InstancingObject* dest, ASEObject* src);

private:
	void ParseName(InstancingObject* dest, ASEObject* src);
	
	void MatrixCorrection(ASEObject* src);

	void CreateGeometry(InstancingObject* dest, ASEObject* src);
	void CreateMaterial(InstancingObject* dest, ASEObject* src);
	void CreateTangents(ASEObject* src);
	void CreateInputElementDesc(ASEObject* src, VertexSet& vertexSet);
	void CreateMesh(InstancingObject* dest, ASEObject* src,VertexSet& vertexSet);

	void ConnectParentInfo(InstancingObject* dest, ASEObject* src);
	void TestConnectParentInfo(Proto& object);
	void CreateTransform(InstancingObject* dest, ASEObject* src);
	void CreateAnimClip(InstancingObject* dest, ASEObject* src);

	//skinning animation
	void CreateSkinner(Proto& objects, unordered_map<string, InstancingObject*>& objPtrByName);

	//임시 작업 공간
	unordered_map<string, InstancingObject*> objPtrByName;//transform parent purpose
	unordered_map<string, Matrix> allMatrix;
	unordered_map<string, bool> determinants;
};