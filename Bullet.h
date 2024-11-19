#ifndef BULLET_H
#define BULLET_H


#include "nohaGame.h"
#include "GameObject.h"
#include "Subject.h"

class Bullet : public GameObject, public Subject {


public:

    // constructor(s)
    Bullet();
    Bullet(glm::vec2 pos, Texture2D sprite, glm::vec2 direction, glm::vec3 color = glm::vec3(1.0f));

    void Update(float dt) override;
    void Init() override;
    void Spawn();
    bool CheckCollisionWithWorld(GameObject& other);
    virtual void AddWorld(nohaGame* world);

private:
    
    nohaGame* world;
    bool start;
    float speed;
    glm::vec2 direction;
};

#endif // !BULLET_H