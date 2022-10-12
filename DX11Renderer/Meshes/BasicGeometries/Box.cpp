#include "pch_dx_11.h"
#include "Box.h"

#include "PathDefine.h"

Box::Box()
{
	/*vertices.emplace_back(VertexColored({-1.0f, -1.0f, -1.0f}));
	vertices.emplace_back(VertexColored({-1.0f, +1.0f, -1.0f }));
	vertices.emplace_back(VertexColored({+1.0f, +1.0f, -1.0f }));
	vertices.emplace_back(VertexColored({+1.0f, -1.0f, -1.0f }));
	vertices.emplace_back(VertexColored({-1.0f, -1.0f, +1.0f }));
	vertices.emplace_back(VertexColored({-1.0f, +1.0f, +1.0f }));
	vertices.emplace_back(VertexColored({+1.0f, +1.0f, +1.0f }));
	vertices.emplace_back(VertexColored({ +1.0f, -1.0f, +1.0f }));*/
	/*vertices.emplace_back(VertexColored({-100.0f, -100.0f, -100.0f}));
	vertices.emplace_back(VertexColored({-100.0f, +100.0f, -100.0f }));
	vertices.emplace_back(VertexColored({+100.0f, +100.0f, -100.0f }));
	vertices.emplace_back(VertexColored({+100.0f, -100.0f, -100.0f }));
	vertices.emplace_back(VertexColored({-100.0f, -100.0f, 100.0f }));
	vertices.emplace_back(VertexColored({-100.0f, +100.0f, 100.0f }));
	vertices.emplace_back(VertexColored({+100.0f, +100.0f, 100.0f }));
	vertices.emplace_back(VertexColored({ +100.0f, -100.0f, 100.0f }));*/
	vertices.emplace_back(VertexUVNormal());
	/*
	indices =
	{
		// front face
		0, 1, 2,
		0, 2, 3,

		// back face
		4, 6, 5,
		4, 7, 6,

		// left face
		4, 5, 1,
		4, 1, 0,

		// right face
		3, 2, 6,
		3, 6, 7,

		// top face
		1, 5, 6,
		1, 6, 2,

		// bottom face
		4, 0, 3,
		4, 3, 7
	};
	*///박스 예전 데이터

	//mesh = new Mesh(vertices.data(), sizeof(VertexColored), vertices.size(), indices.data(), indices.size());

	ASELoader aseLoader;

	//D3D11_SAMPLER_DESC desc;
	//ZeroMemory(&desc, sizeof(D3D11_SAMPLER_DESC));
	//desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	//desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;//U
	//desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;//U
	//desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;//U
	//if (FAILED(DEVICE->CreateSamplerState(&desc, &sampleState)))
	//{
	//	assert(false);
	//}
	//

	//aseLoader.CreateMeshAndMaterialFromASE("03IK-Joe_onlymesh.ASE", &mesh, nullptr);

	//mesh = loader.CreateMeshFromFBX("Ch14_nonPBR.fbx");
	//mesh = aseLoader.CreateMeshFromFBX("box.ASE");
	//mesh = aseLoader.CreateMeshFromASE("teapot.ASE");
	////mesh = aseLoader.CreateMeshFromFBX("genji_max.ASE");
	//diffuseMapName = aseLoader.GetDiffuseMapName();
	wstring wstr(diffuseMapName.begin(), diffuseMapName.end());
	MaterialDesc matDesc;
	matDesc.pixelShaderName = L"PixelUVLight.hlsl";
	matDesc.diffuseFileName =	TEXTUREPATH(wstr);
	matDesc.addressMode = D3D11_TEXTURE_ADDRESS_WRAP;

	material = new Material(matDesc);


	//SRV생성

	//CreateWICTextureFromFile(DEVICE, L"Ch14_nonPBR.fbm/Ch14_1001_Diffuse.png", &res, &diffuse);
	//CreateDDSTextureFromFile(DEVICE, L"Textures/WoodCrate01.dds", &res, &diffuse);
	//CreateDDSTextureFromFile(DEVICE, L"Textures/000000002476.dds", &res, &diffuse);
	//CreateDDSTextureFromFile(DEVICE, L"Textures/teapot.dds", &res, &diffuse);
	//CreateDDSTextureFromFile(DEVICE, L"Textures/000000002405.dds", &res, &diffuse);

	/*D3D11_TEXTURE2D_DESC texturedesc;
	ZeroMemory(&texturedesc, sizeof(texturedesc));


	texturedesc.Width = 256;
	texturedesc.Height = 256;
	texturedesc.MipLevels = 1;
	texturedesc.ArraySize = 1;
	texturedesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	texturedesc.SampleDesc.Count = 1;
	texturedesc.Usage = D3D11_USAGE_DEFAULT;
	texturedesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	
	

	ID3D11Texture2D* texture = nullptr;
	DEVICE->CreateTexture2D(&texturedesc, NULL,&texture);

	D3D11_RENDER_TARGET_VIEW_DESC rtDesc;
	rtDesc.Format = texturedesc.Format;
	rtDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	rtDesc.Texture2D.MipSlice = 0;

	ID3D11RenderTargetView* rtv = nullptr;
	DEVICE->CreateRenderTargetView(texture, &rtDesc, &rtv);

	D3D11_TEXTURE2D_DESC;
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	DEVICE->CreateShaderResourceView(texture, &srvDesc, &diffuse);*/
}

Box::~Box()
{
	delete mesh;
	delete material;
}

void Box::Render()
{

	//if (KeyBoard::Get()->Press(VK_RIGHT))
		//t.pos += 0.01f;

	t.UpdateWorld();


	//set worldviewproj

	//IA
	DC->IASetInputLayout(RESOURCES->inputLayouts->Get(&(vertices[0]), L"VertexUVLight.hlsl"));
	DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	mesh->Set();//setVertexBuffer; indexBuffer;

	//VS
	DC->UpdateSubresource(t.WorldBuffer(), 0, 0, t.World(), 0, 0);
	DC->VSSetConstantBuffers(0, 1, &(t.WorldBuffer()));
	DC->VSSetShader(RESOURCES->vertexShaders->Get(L"VertexUVLight.hlsl"),0, 0);

	//PS
	/*DC->PSSetShaderResources(0, 1, RESOURCES->srvs->Get(L"Textures/teapot.dds"));
	DC->PSSetSamplers(0, 1, RESOURCES->samplerStates->Get(D3D11_TEXTURE_ADDRESS_WRAP));*/
	//DC->PSSetShader(RESOURCES->pixelShaders->Get(L"PixelNormalAsColor.hlsl"), 0, 0);
	//DC->PSSetShader(RESOURCES->pixelShaders->Get(L"PixelUVLight.hlsl"), 0, 0);
	material->Set();


	DC->DrawIndexed(mesh->indexCount, 0, 0);
}
