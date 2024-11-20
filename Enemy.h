#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "nohaGame.h"
#include "GameObject.h"
#include "Subject.h"

enum EnemyMoveState
{
    ENEMY_MOVE_RIGHT,
    ENEMY_MOVE_RIGHT_DOWN,
    ENEMY_MOVE_LEFT,
    ENEMY_MOVE_LEFT_DOWN,
};

class Enemy : public GameObject, public Subject {

public:
    Enemy();
    Enemy(glm::vec2 pos, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f, 0.0f, 0.0f));

    void Update(float dt) override;
    void Init() override;
    void Fire();
    virtual void AddWorld(nohaGame* world);

private:

    float       timeCount;
    float       timeMove;
    float       stepLength;
    int         stepCount;
    nohaGame*   world;

    EnemyMoveState moveState;
};