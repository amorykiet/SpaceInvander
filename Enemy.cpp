#include "Enemy.h"
#include "Bullet.h"
#include <iostream>

Enemy::Enemy() : GameObject()
{
	tag = Tag::EnemyTag;
}

Enemy::Enemy(glm::vec2 pos, Texture2D sprite, glm::vec3 color) :
	GameObject(pos, glm::vec2(50.0f, 50.0f), sprite, color), timeMove(0.5f), stepLength(10.0f)
{
	tag = EnemyTag;
}


void Enemy::Init()
{
	timeCount = timeMove;
	stepCount = 0;
	moveState = ENEMY_MOVE_RIGHT;
	AddObserver(world);
}

void Enemy::Fire()
{
	if (Destroyed) {
		std::cout << "Destroyed" << std::endl;
		return;
	}
	std::cout << "Fired" << std::endl;
	Bullet* bullet = new Bullet(Position + glm::vec2(0.0f, 20.0f), Sprite, glm::vec2(0.0f, 1.0f), BulletFromEnemyTag);

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
	if (timeCount > 0.0f)
	{
		timeCount -= dt;
	}
	else {
		timeCount = timeMove;
		stepCount += 1;

		if (stepCount < 4) {

			switch (moveState)
			{
			case ENEMY_MOVE_RIGHT:
				Position.x += stepLength*1.5;
				break;
			case ENEMY_MOVE_RIGHT_DOWN:
				Position.y += stepLength;
				break;
			case ENEMY_MOVE_LEFT:
				Position.x -= stepLength*1.5;
				break;
			case ENEMY_MOVE_LEFT_DOWN:
				Position.y += stepLength;
				break;
			}
		}
		else
		{
			stepCount = 0; 
			switch (moveState)
			{
			case ENEMY_MOVE_RIGHT:
				moveState = ENEMY_MOVE_RIGHT_DOWN;
				break;
			case ENEMY_MOVE_RIGHT_DOWN:
				moveState = ENEMY_MOVE_LEFT;
				break;
			case ENEMY_MOVE_LEFT:
				moveState = ENEMY_MOVE_LEFT_DOWN;
				break;
			case ENEMY_MOVE_LEFT_DOWN:
				moveState = ENEMY_MOVE_RIGHT;
				break;
			}
		}
	}
}

