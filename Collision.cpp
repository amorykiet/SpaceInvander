#include "Collision.h"

bool CheckCollision(GameObject& one, GameObject& two) // AABB - AABB collision
{
    // collision x-axis?
    bool collisionX = one.Position.x + one.Size.x/2 >= two.Position.x - two.Size.x/2 &&
        two.Position.x + two.Size.x/2 >= one.Position.x - one.Size.x/2;
    // collision y-axis?
    bool collisionY = one.Position.y + one.Size.y/2 >= two.Position.y - two.Size.y/2 &&
        two.Position.y + two.Size.y/2 >= one.Position.y - one.Size.y/2;
    // collision only if on both axes
    return collisionX && collisionY;
}
