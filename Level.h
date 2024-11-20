#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>


#include "nohaGame.h"
#include "GameObject.h"
#include "Enemy.h"

class Level : public GameObject {

public:
    Level();

    void Update(float dt) override;
    void Init() override;
    void Load(const char* file, unsigned int levelWidth, unsigned int levelHeight);
    void CreateEnemies(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth, unsigned int levelHeight);
    void Spawn();
    virtual void AddWorld(nohaGame* world);

private:

    std::vector<Enemy*> enemies;
    nohaGame* world;
};