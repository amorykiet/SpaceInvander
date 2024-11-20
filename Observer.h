#pragma once

#include "GameObject.h"

enum Event {
	DESTROYSGAMEOBJECT,
	PLAYERWIN,
	PLAYERLOSE,
	WALLHIT
};

class Observer
{
public:
	virtual ~Observer() {}
	virtual void onNotify(GameObject* entity, Event event) = 0;
};