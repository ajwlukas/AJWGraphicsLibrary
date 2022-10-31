#pragma once

#include <stdint.h>
#include <vector>

class OnResize_Observer
{
private:
	friend class OnResizeNotice;
	virtual void OnResize(uint32_t width, uint32_t height) = 0;
};

class OnResizeNotice
{
	using Observer = OnResize_Observer;
public:
	void AddObserver(Observer* observer)
	{
		observers.push_back(observer);
	}

	void SubObserver(Observer* observer)
	{
		observers.erase(find(observers.begin(), observers.end(), observer));
	}

	void Update(uint32_t width, uint32_t height)
	{
		if (this->width != width || this->height != height)
		{
			this->width = width;
			this->height = height;

			OccurEvent();
		}
	}

private:

	void OccurEvent()
	{
		for (Observer* ob : observers)
			ob->OnResize(width, height);
	}

	uint32_t width , height;

	std::vector<Observer*> observers;
};
