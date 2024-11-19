#pragma once

#include "Observer.h"
#include "Constants.h"
#include <algorithm>
#include <vector>

class Subject
{
public:
	~Subject();

	void AddObserver(Observer* observer);
	void RemoveObserver(Observer* observer);

protected:

	void notify(GameObject* entity, Event event);

private:
	std::vector<Observer*> observers;
};