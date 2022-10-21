#pragma once

class IExample
{
public:
	IExample() {}
	virtual ~IExample() {}

	virtual void Init() = 0;
	virtual void UnInit() = 0;
	virtual void Update() = 0;
};