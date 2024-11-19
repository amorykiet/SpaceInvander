#include "Bullet.h"
#include <iostream>

Bullet::Bullet(): GameObject(), speed(200.0f), direction(glm::vec2(0.0f, 1.0f)), start(false)
{
}

Bullet::Bullet(glm::vec2 pos, Texture2D sprite, glm::vec2 direction, glm::vec3 color): 
	GameObject(pos, glm::vec2(20.0f, 20.0f), sprite, color), direction(direction), speed(200.0f), start(false)
{
}

void Bullet::Update(float dt)
{
	if (!start) return;

	float velocity = speed * dt;
	Position += velocity * direction;

	if (Position.x < 0.0f || Position.x > SCREEN_WIDTH || Position.y < 0.0f || Position.y > SCREEN_HEIGHT) {
		Destroyed = true;
		notify(this, Event::DESTROYSGAMEOBJECT);
	}
}

void Bullet::Init()
{
	AddObserver(world);
}

void Bullet::Spawn()
{
	start = true;
}

void Bullet::AddWorld(nohaGame* world)
{
	this->world = world;
}
