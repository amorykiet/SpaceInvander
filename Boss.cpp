#include "Boss.h"
#include <random>


const float MIN = 10;
const float MAX = 20;

float GenRandom(float min, float max) {

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(min, max);

	// Generate random number in the range [min, max]
	return distrib(gen);
}

Boss::Boss(Texture2D sprite, glm::vec3 color):
	GameObject(glm::vec2(SCREEN_WIDTH + 50.0f, 150.0f), glm::vec2(50.0f, 50.0f), sprite, color), speed(50.0f)
{
	tag = BossTag;
	timeCount = GenRandom(MIN, MAX);
}

void Boss::Init()
{
	this->moveState = BOSS_MOVE_LEFT;
}

void Boss::Update(float dt)
{
	if (timeCount > 0.0f)
	{
		timeCount -= dt;
		return;
	}

	float velocity = speed * dt;
	switch (moveState)
	{
	case BOSS_MOVE_RIGHT:
		Position.x += velocity;
		if (Position.x > SCREEN_WIDTH + 50.0f) {
			ChangeDirection();
		}
		break;
	case BOSS_MOVE_LEFT:
		Position.x -= velocity;
		if (Position.x < -50.0f) {
			ChangeDirection();
		}
		break;
	default:
		break;
	}

}

void Boss::AddWorld(nohaGame* world)
{
	this->world = world;
}

void Boss::ChangeDirection()
{
	if (rand() % 2 == 1) {
		moveState = BOSS_MOVE_LEFT;
		Position.x = SCREEN_WIDTH + Size.x;
	}
	else {
		moveState = BOSS_MOVE_RIGHT;
		Position.x = -Size.x;
	}
	timeCount = GenRandom(MIN, MAX);

}
