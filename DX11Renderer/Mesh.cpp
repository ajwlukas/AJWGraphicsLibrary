#include "pch_dx_11.h"
#include "Mesh.h"

#include <functional>

Mesh::Mesh(VertexSet& vertexSet, UINT indexData[], UINT indexCount, wstring vsFileName, D3D_PRIMITIVE_TOPOLOGY topology)
	:vertexDataSize(vertexSet.GetVertexSize()) ,indexCount(indexCount), vsFileName(vsFileName), topology(topology)
{
	desc = vertexSet.GetDescsData();
	descSize = vertexSet.GetDescsSize();

	//inputLayout
	RESOURCES->inputLayouts->Get(inputLayout, desc, descSize, vsFileName);

	//shader
	shader = RESOURCES->vertexShaders->Get(vsFileName);

	//vertexBuffer;
	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = vertexSet.GetVerticesSize();
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	vbd.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA vinitData;
	vinitData.pSysMem = vertexSet.GetVerticesData();
	HRESULT hr = DEVICE->CreateBuffer(&vbd, &vinitData, &vertexBuffer);

	//index Buffer
	D3D11_BUFFER_DESC ibd;
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(UINT) * indexCount;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	ibd.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA iinitData;
	iinitData.pSysMem = indexData;
	hr = DEVICE->CreateBuffer(&ibd, &iinitData, &indexBuffer);
}

Mesh::~Mesh()
{
	vertexBuffer->Release();
	indexBuffer->Release();
}

void Mesh::Set()
{
	DC->IASetInputLayout(inputLayout);
	DC->IASetPrimitiveTopology(topology);//todo : 이거 메쉬로 넣어주자
	DC->IASetVertexBuffers(0, 1, &vertexBuffer, &vertexDataSize, &offset);
	DC->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	DC->VSSetShader(shader, 0, 0);//todo : 이거 메쉬로 넣어주자


	DC->DrawIndexed(GetIndexCount(), 0, 0);
}
