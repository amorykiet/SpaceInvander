#ifndef PLAYER_H
#define PLAYER_H


#include <glad/glad.h>
#include <glm/glm.hpp>

#include "nohaGame.h"
#include "GameObject.h"
#include "Subject.h"

class Player : public GameObject, public Subject {
	
public:
    Player();
    Player(glm::vec2 pos, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f));

    void Update(float dt) override;
    void Init() override;
    void Fire();
    virtual void AddWorld(nohaGame* world);

private:

    nohaGame* world;
    float speed;
    float reloadTime;
    float countTime;
    bool canFire;
};

#endif