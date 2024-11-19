#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "nohaGame.h"
#include "GameObject.h"
#include "Subject.h"

class Enemy : public GameObject, public Subject {

public:
    Enemy();
    Enemy(glm::vec2 pos, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f, 0.0f, 0.0f));

    void Update(float dt) override;
    void Init() override;
    void Fire();
    virtual void AddWorld(nohaGame* world);

private:

    nohaGame* world;
};