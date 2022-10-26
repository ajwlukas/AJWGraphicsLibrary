#include "Ex_BoxCamera.h"

void Ex_BoxCamera::Init()
{
	TL_Graphics::RenderSystem::Create();
	TL_Graphics::RenderSystem::Get()->Init();

	input = new ajwCommon::Input();

	struct Vertex
	{
		float position[3];
	}
	vertices[8]
	{
		//¾Õ¸é
	{-0.5f,        +0.5f,      -0.5f},
	{+0.5f,        +0.5f,      -0.5f},
	{-0.5f,        -0.5f,      -0.5f},
	{+0.5f,        -0.5f,      -0.5f},

	//µÞ¸é
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

	mesh = TL_Graphics::RenderSystem::Get()->CreateMesh(vertexAttribute, indicies, sizeof(indicies) / sizeof(indicies[0]), L"BoxCameraVS.hlsl");

	material = TL_Graphics::RenderSystem::Get()->CreateMaterial(L"BoxCameraPS.hlsl");

	/* 
	struct World
	{
		float world[4][4];
	}world
		=
	{
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};

	constantBuffer = TL_Graphics::RenderSystem::Get()->CreateConstantBuffer(1, &world, sizeof(World));
	*/
	constantBuffer = TL_Graphics::RenderSystem::Get()->CreateConstantBuffer(1, &(t.GetWorldMatrix()), sizeof(t.GetWorldMatrix()));

	camera = TL_Graphics::RenderSystem::Get()->CreateCamera();
}

void Ex_BoxCamera::UnInit()
{
	TL_Graphics::RenderSystem::Delete();

	delete input;
}

void Ex_BoxCamera::Update()
{
	TL_Graphics::RenderSystem::Get()->Clear();

	input->Update();

	material->Set();

	mesh->Set();

	constantBuffer->Set();

	TransformMove();

	t.UpdateWorld();

	constantBuffer->Update(&(t.GetWorldMatrix()), sizeof(t.GetWorldMatrix()));

	CameraMove();

	camera->Update(camInfo.pos, camInfo.rot);
		
	camera->Set();

	TL_Graphics::RenderSystem::Get()->Draw();

	TL_Graphics::RenderSystem::Get()->Present();
}

void Ex_BoxCamera::CameraMove()
{
	if (input->Press(VK_LBUTTON))
	{
		camInfo.rot[1] += input->MouseDiff().x * 0.01f;
		camInfo.rot[0] += input->MouseDiff().y * 0.01f;
	}

	if (input->Press('W'))
		camInfo.pos[2] += 0.01f;
	if (input->Press('S'))
		camInfo.pos[2] -= 0.01f;
	if (input->Press('A'))
		camInfo.pos[0] -= 0.01f;
	if (input->Press('D'))
		camInfo.pos[0] += 0.01f;
}

void Ex_BoxCamera::TransformMove()
{
	if (input->Press(VK_UP))
		t.Pos().y += 0.01f;
	if (input->Press(VK_DOWN))
		t.Pos().y -= 0.01f;
	if (input->Press(VK_RIGHT))
		t.Pos().x += 0.01f;
	if (input->Press(VK_LEFT))
		t.Pos().x -= 0.01f;
}
