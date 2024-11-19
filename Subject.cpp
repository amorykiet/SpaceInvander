#include "Subject.h"

Subject::~Subject()
{
	for (Observer* observer : observers) {
		delete observer;
	}
}

void Subject::AddObserver(Observer* observer)
{
	observers.push_back(observer);
}

void Subject::RemoveObserver(Observer* observer)
{
	//not good
	observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void Subject::notify(GameObject* entity, Event event)
{
	for (Observer* observer: observers)
	{
		observer->onNotify(entity, event);
	}
}
