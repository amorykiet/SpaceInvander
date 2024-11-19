#include "Enemy.h"
#include "Bullet.h"

Enemy::Enemy() : GameObject()
{
	tag = Tag::EnemyTag;
}

Enemy::Enemy(glm::vec2 pos, Texture2D sprite, glm::vec3 color) :
	GameObject(pos, glm::vec2(50.0f, 50.0f), sprite, color)
{
	tag = EnemyTag;
}


void Enemy::Init()
{
	AddObserver(world);
}

void Enemy::Fire()
{
	Bullet* bullet = new Bullet(Position + glm::vec2(0.0f, -10.0f), Sprite, glm::vec2(0.0f, 1.0f));

	//NOT GOOD
	bullet->AddWorld(world);
	bullet->Init();
	bullet->Spawn();
	world->AddGameObject(bullet);

}

void Enemy::AddWorld(nohaGame* world)
{
	this->world = world;
}


void Enemy::Update(float dt) {

}

