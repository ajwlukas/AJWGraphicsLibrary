#include "pch_dx_11.h"
#include "Skinner.h"
//
//Skinner::Skinner(InstancingObject* object)
//	:bones{}
//{
//	//애니메이션용 본 버퍼
//	D3D11_BUFFER_DESC cbd;
//	cbd.Usage = D3D11_USAGE_DEFAULT;
//	cbd.ByteWidth = sizeof(Data);
//	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
//	cbd.CPUAccessFlags = 0;
//	cbd.MiscFlags = 0;
//	cbd.StructureByteStride = 0;// sizeof(XMFLOAT4X4); todo : 여기??
//	D3D11_SUBRESOURCE_DATA initData;
//	initData.pSysMem = &bones;
//	RESOURCES->buffers->Create(animBuffer, cbd, &initData);
//
//	/*refBones = &object->belongsTo->bones;
//
//	skinWorldTMInv.resize(refBones->size());
//
//	for (UINT i = 0; i < refBones->size(); i++)
//	{
//		(*refBones)[i]->transform.UpdateWorld();
//		skinWorldTMInv[i] = XMMatrixInverse(nullptr, *(*refBones)[i]->transform.World());
//	}*/
//}
//
//Skinner::Skinner()
//	:bones{}
//{
//	//애니메이션용 본 버퍼
//	D3D11_BUFFER_DESC cbd;
//	cbd.Usage = D3D11_USAGE_DEFAULT;
//	cbd.ByteWidth = sizeof(Data);
//	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
//	cbd.CPUAccessFlags = 0;
//	cbd.MiscFlags = 0;
//	cbd.StructureByteStride = 0;// sizeof(XMFLOAT4X4); todo : 여기??
//	D3D11_SUBRESOURCE_DATA initData;
//	initData.pSysMem = &bones;
//	RESOURCES->buffers->Create(animBuffer, cbd, &initData);
//}
//
//Skinner::~Skinner()
//{
//}
//
//void Skinner::Update()
//{
//	for (UINT i = 0; i < refInsts->size(); i++)
//	{
//		Matrix finalBoneTM;
//
//		finalBoneTM = skinWorldTMInv[i] * *((*refInsts)[i]->transform.World());
//
//		bones.data[i] = finalBoneTM;
//	}
//}
//
//void Skinner::ConnectRefBones(vector<Instance*>* bones)
//{
//	refInsts = bones;
//
//	skinWorldTMInv.resize(refInsts->size());
//
//	for (UINT i = 0; i < refInsts->size(); i++)
//	{
//		(*refInsts)[i]->transform.UpdateWorld();
//		skinWorldTMInv[i] = DirectX::XMMatrixInverse(nullptr, *(*refInsts)[i]->transform.World());
//	}
//}

