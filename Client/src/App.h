#pragma once

class App
{
public:
	App();
	~App();

	void Update();

	class IExample* example;
};