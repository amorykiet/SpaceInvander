#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "nohaGame.h"
#include "GameObject.h"

class Wall : public GameObject{

public:
    Wall();
    Wall(glm::vec2 pos, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f, 0.5f, 1.0f));

    void Update(float dt) override;
    void Draw(SpriteRenderer& renderer) override;
    void Init() override;
    virtual void AddWorld(nohaGame* world);

    int         health;

private:

    nohaGame*   world;
};