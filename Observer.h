#pragma once

#include "GameObject.h"

enum Event {
	DESTROYSGAMEOBJECT
};

class Observer
{
public:
	virtual ~Observer() {}
	virtual void onNotify(GameObject* entity, Event event) = 0;
};