#include "GameObject.h"

GameObject::GameObject()
    : Position(0.0f, 0.0f), Size(1.0f, 1.0f), Color(1.0f), Rotation(0.0f), Sprite(), Destroyed(false) {
}

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color)
    : Position(pos), Size(size), Color(color), Rotation(0.0f), Sprite(sprite), Destroyed(false) {
}

void GameObject::Draw(SpriteRenderer& renderer)
{
    renderer.DrawSprite(this->Sprite, this->Position, this->Size, this->Rotation, this->Color);
}

void GameObject::Update(float dt)
{

}

void GameObject::Init()
{
}
