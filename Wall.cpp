#include "Wall.h"

Wall::Wall(): GameObject()
{
}

Wall::Wall(glm::vec2 pos, Texture2D sprite, glm::vec3 color):
	GameObject(pos, glm::vec2(70.0f, 50.0f), sprite, color), health(3)
{
	tag = WALL;
}

void Wall::Update(float dt)
{
}

void Wall::Draw(SpriteRenderer& renderer)
{
	GameObject::Draw(renderer);
}

void Wall::Init()
{
}


void Wall::AddWorld(nohaGame* world)
{
	this->world = world;
}
