#include "pch_dx_11.h"
#include "FbxLoader.h"
//
////FbxLoader::FbxLoader()
////{
////	manager = FbxManager::Create();
////
////	ios = FbxIOSettings::Create(manager, IOSROOT);
////	manager->SetIOSettings(ios);
////}
//
//FbxLoader::~FbxLoader()
//{
//	/*ios->Destroy();
//	manager->Destroy();*/
//}
//
//Mesh* FbxLoader::CreateMeshFromFBX(string fileName)//받는 애 꼭 동적할당 해제 해줄 것 빼뜨려먹기 딱 좋은 형태이다.
//{
//	//FbxImporter* importer = FbxImporter::Create(manager, "");
//
//	//bool status = importer->Initialize(fileName.c_str(), -1, manager->GetIOSettings());
//	//if (!status) 
//	//{ 
//	//	printf("Call to FbxImporter::Initialize() failed.\n");
//	//	printf("Error returned: %s\n\n", importer->GetStatus().GetErrorString());
// //}
//
//
//	//scene = FbxScene::Create(manager, "Scene");
//
//	//importer->Import(scene);
//	//importer->Destroy();
//
//	//fbxsdk::FbxNode* rootNode = scene->GetRootNode();
//
//	//fbxsdk::FbxAxisSystem sceneAxisSystem = scene->GetGlobalSettings().GetAxisSystem();
//	////fbxsdk::FbxAxisSystem::DirectX.ConvertScene(scene);
//
//	//FbxGeometryConverter geometryConverter(manager);
//	//geometryConverter.Triangulate(scene, true);
//
//	//FbxMesh* mesh = nullptr;
//	//FindMeshNode(rootNode, &mesh);
//
//
//	//return CreateMesh(mesh);
//	return nullptr;
//}
//
//void FbxLoader::FindMeshNode(FbxNode* node, FbxMesh** mesh)
//{
//	/*fbxsdk::FbxNodeAttribute* nodeAttribute = node->GetNodeAttribute();
//
//	if (nodeAttribute)
//	{
//		if (nodeAttribute->GetAttributeType() == fbxsdk::FbxNodeAttribute::eMesh)
//		{
//			*mesh = node->GetMesh();
//			return;
//		}
//	}
//
//	UINT childCount = node->GetChildCount();
//	for (UINT i = 0; i < childCount; i++)
//		FindMeshNode(node->GetChild(i), mesh);*/
//}
//
//Mesh* FbxLoader::CreateMesh(FbxMesh* mesh)
//{
////	unsigned int count = mesh->GetControlPointsCount();
////
////	vector<VertexUVNormal> vertices(count);
////
////	bool hasUV = false;
////	FbxGeometryElementUV* vertexUV = nullptr;
////	FbxLayerElement::EMappingMode mappingModeUV;
////	FbxLayerElement::EReferenceMode refModeUV;
////	if (mesh->GetElementUVCount() > 0)
////	{
////		vertexUV = mesh->GetElementUV(0);
////		mappingModeUV = vertexUV->GetMappingMode();
////		refModeUV = vertexUV->GetReferenceMode();
////		hasUV = true;
////	}
////
////
////	bool hasNormal = false;
////	FbxGeometryElementNormal* vertexNormal = nullptr;
////	FbxLayerElement::EMappingMode mappingModeNormal;
////	FbxLayerElement::EReferenceMode refModeNormal;
////	if (mesh->GetElementNormalCount() > 0)
////	{
////		vertexNormal = mesh->GetElementNormal(0);
////		mappingModeNormal = vertexNormal->GetMappingMode();
////		refModeNormal = vertexNormal->GetReferenceMode();
////		hasNormal = true;
////	}
////
////
////	for (unsigned int i = 0; i < count; i++)
////	{
////		vertices[i].position.x = static_cast<float>(mesh->GetControlPointAt(i).mData[0]);//control Point = 버텍스
////		vertices[i].position.y = static_cast<float>(mesh->GetControlPointAt(i).mData[1]);
////		vertices[i].position.z = static_cast<float>(mesh->GetControlPointAt(i).mData[2]);
////
////		//FbxGeometryElementUV* uv = mesh->GetElementUV(0);
////		if (hasUV && mappingModeUV == FbxGeometryElement::eByControlPoint)
////		{
////			if (refModeUV == FbxGeometryElement::eDirect)
////			{
////				vertices[i].uv.x = static_cast<float>(vertexUV->GetDirectArray().GetAt(i).mData[0]);
////				vertices[i].uv.y = static_cast<float>(vertexUV->GetDirectArray().GetAt(i).mData[1]);
////			}
////			else if (refModeUV == FbxGeometryElement::eIndexToDirect)
////			{
////				int index = vertexUV->GetIndexArray().GetAt(i);
////				vertices[i].uv.x = static_cast<float>(vertexUV->GetDirectArray().GetAt(index).mData[0]);
////				vertices[i].uv.y = static_cast<float>(vertexUV->GetDirectArray().GetAt(index).mData[1]);
////			}
////		}
////		if (hasNormal && mappingModeNormal == FbxGeometryElement::eByControlPoint)
////		{
////			if (refModeNormal == FbxGeometryElement::eDirect)
////			{
////				vertices[i].normal.x = static_cast<float>(vertexNormal->GetDirectArray().GetAt(i).mData[0]);
////				vertices[i].normal.y = static_cast<float>(vertexNormal->GetDirectArray().GetAt(i).mData[1]);
////				vertices[i].normal.z = static_cast<float>(vertexNormal->GetDirectArray().GetAt(i).mData[2]);
////			}
////			else if (refModeNormal == FbxGeometryElement::eIndexToDirect)
////			{
////				int index = vertexNormal->GetIndexArray().GetAt(i);
////				vertices[i].normal.x = static_cast<float>(vertexNormal->GetDirectArray().GetAt(index).mData[0]);
////				vertices[i].normal.y = static_cast<float>(vertexNormal->GetDirectArray().GetAt(index).mData[1]);
////				vertices[i].normal.z = static_cast<float>(vertexNormal->GetDirectArray().GetAt(index).mData[2]);
////			}
////		}
////	}
////
////
////	
////	set<unsigned int> splitCounter;
////	unsigned int indexCount = mesh->GetPolygonCount();
////	vector<UINT> indices(indexCount * 3);
////	unsigned int indexIndex = 0;
////	for (unsigned int i = 0; i < mesh->GetPolygonCount(); i++)
////	{
////		for (unsigned int j = 0; j < 3; j++, indexIndex++)
////		{
////			int vertexIndex = mesh->GetPolygonVertex(i, j);
////
////			bool splitCondition = (hasUV && mappingModeUV == FbxGeometryElement::eByPolygonVertex) || (hasNormal && mappingModeNormal == FbxGeometryElement::eByPolygonVertex);
////
////			if ((splitCounter.find(vertexIndex) != splitCounter.end()) && splitCondition)
////			{
////				vertices.emplace_back(VertexUVNormal(vertices[vertexIndex]));
////				vertexIndex = vertices.size() - 1;
////			}
////			splitCounter.insert(vertexIndex);
////
////			indices[indexIndex] = vertexIndex;//i번째 삼각형의 j번째 정점의 인덱스vertices[i].position.x = static_cast<float>(mesh->GetControlPointAt(i).mData[0]);//control Point = 버텍스
////
////			if (hasUV && mappingModeUV == FbxGeometryElement::eByPolygonVertex)
////			{
////				if (refModeUV == FbxGeometryElement::eDirect)
////				{
////					vertices[vertexIndex].uv.x = static_cast<float>(vertexUV->GetDirectArray().GetAt(indexIndex).mData[0]);
////					vertices[vertexIndex].uv.y = static_cast<float>(vertexUV->GetDirectArray().GetAt(indexIndex).mData[1]);
////				}
////				else if (refModeUV == FbxGeometryElement::eIndexToDirect)
////				{
////					int index = vertexUV->GetIndexArray().GetAt(indexIndex);
////					vertices[vertexIndex].uv.x = (vertexUV->GetDirectArray().GetAt(index)[0]);
////					vertices[vertexIndex].uv.y = 1 - (vertexUV->GetDirectArray().GetAt(index)[1]);
////				}
////			}
////			
////			if (hasNormal && mappingModeNormal == FbxGeometryElement::eByPolygonVertex)
////			{
////				if (refModeNormal == FbxGeometryElement::eDirect)
////				{
////					vertices[vertexIndex].normal.x = static_cast<float>(vertexNormal->GetDirectArray().GetAt(indexIndex).mData[0]);
////					vertices[vertexIndex].normal.y = static_cast<float>(vertexNormal->GetDirectArray().GetAt(indexIndex).mData[1]);
////					vertices[vertexIndex].normal.z = static_cast<float>(vertexNormal->GetDirectArray().GetAt(indexIndex).mData[2]);
////				}
////				else if (refModeNormal == FbxGeometryElement::eIndexToDirect)
////				{
////					int index = vertexNormal->GetIndexArray().GetAt(indexIndex);
////					vertices[vertexIndex].normal.x = (vertexNormal->GetDirectArray().GetAt(index)[0]);
////					vertices[vertexIndex].normal.y = (vertexNormal->GetDirectArray().GetAt(index)[1]);
////					vertices[vertexIndex].normal.z = (vertexNormal->GetDirectArray().GetAt(index)[2]);
////				}
////			}
////		}
////	}
////
////	return new Mesh(vertices.data(), sizeof(VertexUVNormal), vertices.size(), indices.data(), indices.size());
//return nullptr;
//}
