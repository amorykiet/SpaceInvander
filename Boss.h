#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "nohaGame.h"
#include "GameObject.h"
#include "Subject.h"

enum BossMoveState
{
    BOSS_MOVE_RIGHT,
    BOSS_MOVE_LEFT
};

class Boss : public GameObject{

public:
    Boss(Texture2D sprite, glm::vec3 color = glm::vec3(1.0f, 0.0f, 0.0f));

    void Init() override;
    void Update(float dt) override;
    virtual void AddWorld(nohaGame* world);

private:

    float           speed;
    float           timeCount;

    nohaGame*       world;
    BossMoveState   moveState;

    void ChangeDirection();
};