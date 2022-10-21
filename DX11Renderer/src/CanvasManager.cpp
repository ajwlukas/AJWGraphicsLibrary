#include "pch_dx_11.h"
#include "CanvasManager.h"

CanvasManager::CanvasManager()
{
}

CanvasManager::~CanvasManager()
{
}

void CanvasManager::Reserve(Rend drawCall)
{
	renderQueue.push(drawCall);
}

void CanvasManager::Render()
{
	while (!renderQueue.empty())
	{
		renderQueue.top().second();
		renderQueue.pop();
	}
}
