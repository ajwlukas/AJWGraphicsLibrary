#include "App.h"

#include "Example\00_Ex_Triagle\Ex_Triangle.h"
#include "Example\01_Ex_TriangleColor\Ex_TriangleColor.h"
#include "Example\02_Ex_BoxCamera\Ex_BoxCamera.h"
#include "Example\03_Ex_Light\Ex_Light.h"

App::App()
{
	//example = new Ex_Triangle();
	//example = new Ex_TriangleColor();
	//example = new Ex_BoxCamera();
	example = new Ex_Light();


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
