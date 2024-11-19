#include "Bullet.h"
#include "Collision.h"
#include "nohaGame.h"

//Debug
#include <iostream>


Bullet::Bullet(): GameObject(), speed(200.0f), direction(glm::vec2(0.0f, 1.0f)), start(false)
{
	tag = Tag::BulletTag;
}

Bullet::Bullet(glm::vec2 pos, Texture2D sprite, glm::vec2 direction, glm::vec3 color): 
	GameObject(pos, glm::vec2(20.0f, 20.0f), sprite, color), direction(direction), speed(200.0f), start(false)
{
	tag = Tag::BulletTag;
}

void Bullet::Update(float dt)
{
	if (!start) return;

	float velocity = speed * dt;
	Position += velocity * direction;

	GameObject* other = new GameObject();
	if (CheckCollisionWithWorld(*other))
	{
		if (other->tag == EnemyTag)
		{
			Destroyed = true;
			notify(other, Event::DESTROYSGAMEOBJECT);
			notify(this, Event::DESTROYSGAMEOBJECT);
		}
	}

	if (Position.x < 0.0f || Position.x > SCREEN_WIDTH || Position.y < 150.0f || Position.y > SCREEN_HEIGHT) {
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

bool Bullet::CheckCollisionWithWorld(GameObject& other_)
{
	for (int i = 0; i < world->NumberOfGameObjects; i++) {
		if (world->gameObjects[i]) {
			GameObject* other = world->gameObjects[i];
			if (other->ID != this->ID && !other->Destroyed) {
				if (CheckCollision(*this, *other)) {
					other_ = *world->gameObjects[i];
					return true;
				}
			}
		}
	}
	return false;
}

void Bullet::AddWorld(nohaGame* world)
{
	this->world = world;
}