#include "Ex_Light.h"

void Ex_Light::Init()
{
	input = new ajwCommon::Input();

	struct Vertex
	{
		float position[3];
	}
	vertices[8]
	{
		//앞면
	{-0.5f,        +0.5f,      -0.5f},
	{+0.5f,        +0.5f,      -0.5f},
	{-0.5f,        -0.5f,      -0.5f},
	{+0.5f,        -0.5f,      -0.5f},

	//뒷면
	{-0.5f,         +0.5f,     +0.5f},
	{+0.5f,         +0.5f,     +0.5f},
	{-0.5f,         -0.5f,     +0.5f},
	{+0.5f,         -0.5f,     +0.5f}
	};

	vertexAttribute.AddElementToDesc(sizeof(Vertex::position), TL_Graphics::DataType::FLOAT, "POSITION");

	vertexAttribute.AddData(vertices, sizeof(vertices));

	UINT indicies[]
		=
	{
		//front
		0,1,2,
		1,3,2,
		//back
		5,4,7,
		4,6,7,

		//up
		4,5,0,
		5,1,0,
		//down
		2,3,6,
		3,7,6,

		//left
		4,0,6,
		0,2,6,
		//right
		1,5,3,
		5,7,3
	};

	mesh = TL_Graphics::RenderSystem::Get()->CreateMesh(vertexAttribute, indicies, sizeof(indicies) / sizeof(indicies[0]), L"LightVS.hlsl");

	material = TL_Graphics::RenderSystem::Get()->CreateMaterial(L"LightPS.hlsl");

	worldBuffer = TL_Graphics::RenderSystem::Get()->CreateConstantBuffer(1, &(boxT.GetWorldMatrix()), sizeof(boxT.GetWorldMatrix()));

	camera = TL_Graphics::RenderSystem::Get()->CreateCamera();


	directionalLight = { { 1,2,3 } };


	directionalLightBuffer = TL_Graphics::RenderSystem::Get()->CreateConstantBuffer(2, &directionalLight, sizeof(directionalLight));



}

void Ex_Light::UnInit()
{
	TL_Graphics::RenderSystem::Delete();

	delete input;
}

void Ex_Light::Update()
{
	TL_Graphics::RenderSystem::Get()->Clear();//화면을 지우고

	{
		input->Update();//키보드 마우스 업데이트

		CameraMove();//카메라 포지션 무브

		camT.UpdateWorld();

		camera->Update(camT.GetWorldMatrix());

		camera->Set();

		directionalLightBuffer->Set();

		{//파이프라인을 채운다
			material->Set();

			mesh->Set();

			TransformMove();

			boxT.UpdateWorld();

			worldBuffer->Update(&(boxT.GetWorldMatrix()), sizeof(boxT.GetWorldMatrix()));

			worldBuffer->Set();

			TL_Graphics::RenderSystem::Get()->Draw();//파이프 라인의 내용을 이행(렌더타겟에 Draw)
		}
	}

	TL_Graphics::RenderSystem::Get()->Present();//그려놓은 렌더타겟을 출현 시킴
}

void Ex_Light::CameraMove()
{
	if (input->Press(VK_LBUTTON))
	{
		camT.Rot().y += input->MouseDiff().x * 0.01f;
		camT.Rot().x += input->MouseDiff().y * 0.01f;
	}

	if (input->Press('W'))
		camT.Pos() += camT.Forward() * 0.01f;
	if (input->Press('S'))
		camT.Pos() -= camT.Forward() * 0.01f;
	if (input->Press('A'))
		camT.Pos() -= camT.Right() * 0.01f;
	if (input->Press('D'))
		camT.Pos() += camT.Right() * 0.01f;
	if (input->Press('Q'))
		camT.Pos() -= camT.Up() * 0.01f;
	if (input->Press('E'))
		camT.Pos() += camT.Up() * 0.01f;
}

void Ex_Light::TransformMove()
{
	if (input->Press(VK_UP))
		boxT.Pos().y += 0.01f;
	if (input->Press(VK_DOWN))
		boxT.Pos().y -= 0.01f;
	if (input->Press(VK_RIGHT))
		boxT.Pos().x += 0.01f;
	if (input->Press(VK_LEFT))
		boxT.Pos().x -= 0.01f;
}
