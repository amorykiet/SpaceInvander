#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H


#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>

#include "SpriteRenderer.h"

enum Tag {
    EnemyTag,
    PlayerTag,
    BulletFromPlayerTag,
    BulletFromEnemyTag,
    WALL,
    BossTag
};

// Container object for holding all state relevant for a single
// game object entity. Each object in the game likely needs the
// minimal of state as described within GameObject.
class GameObject
{
public:
    // object state

    int ID;
    Tag tag;
    glm::vec2   Position, Size;
    glm::vec3   Color;
    float       Rotation;
    bool        Destroyed;
    // render state
    Texture2D   Sprite;
    // constructor(s)
    GameObject();
    GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f));
    // draw sprite
    virtual void Draw(SpriteRenderer& renderer);
    virtual void Update(float dt);
    virtual void Init();

protected:

};

#endif // !GAME_OBJECT_H