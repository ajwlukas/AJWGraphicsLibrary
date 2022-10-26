#include "App.h"

#include "Example\Ex_Triagle\Ex_Triangle.h"
#include "Example\Ex_TriangleColor\Ex_TriangleColor.h"
#include "Example\Ex_BoxCamera\Ex_BoxCamera.h"

App::App()
{
	//example = new Ex_Triangle();
	//example = new Ex_TriangleColor();
	example = new Ex_BoxCamera();


	example->Init();
}

App::~App()
{
	example->UnInit();
}

void App::Update()
{
	example->Update();
}
