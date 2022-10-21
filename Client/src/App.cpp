#include "App.h"

#include "Example\Ex_Triagle\Ex_Triangle.h"

App::App()
{
	example = new Ex_Triangle();


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
