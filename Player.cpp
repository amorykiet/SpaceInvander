#include "Player.h"
#include "Input.h"
#include "Bullet.h"

Player::Player(): GameObject(), speed(200.0f), reloadTime(1.0f)
{

}

Player::Player(glm::vec2 pos, Texture2D sprite, glm::vec3 color): 
	GameObject(pos, glm::vec2(50.0f, 50.0f), sprite, color), speed(200.0f), reloadTime(1.0f)
{

}


void Player::Init()
{
	AddObserver(world);
}

void Player::Fire()
{
	Bullet* bullet = new Bullet(Position + glm::vec2(0.0f, -10.0f), Sprite, glm::vec2(0.0f, -1.0f));

	//NOT GOOD
	bullet->AddWorld(world);
	bullet->Init();
	bullet->Spawn();
	world->AddGameObject(bullet);

	countTime = reloadTime;
	canFire = false;
}

void Player::AddWorld(nohaGame* world)
{
	this->world = world;
}


void Player::Update(float dt) {

	float velocity = speed * dt;
	if (countTime > 0.0f) {
		countTime -= dt;
	}
	else {
		countTime = 0.0f;
		canFire = true;
	}

	if (Input::IsPressed(GLFW_KEY_RIGHT))
	{
		Position.x += velocity;
	}

	if (Input::IsPressed(GLFW_KEY_LEFT)) {
		Position.x -= velocity;
	}

	if (Input::IsPressed(GLFW_KEY_SPACE) && canFire) {
		Fire();
	}

	Position.x = glm::clamp(Position.x, 0.0f, static_cast<float>(SCREEN_WIDTH));

}



