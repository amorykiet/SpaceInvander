#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <map>


#include "nohaGame.h"
#include "GameObject.h"
#include "Enemy.h"
#include "Subject.h"

class Level : public GameObject, public Subject{

public:
    Level();

    void Update(float dt) override;
    void Init() override;
    void Load(const char* file, unsigned int levelWidth, unsigned int levelHeight);
    void CreateEnemies(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth, unsigned int levelHeight);
    void Spawn();
    void RemoveEnemy(int ID);

    virtual void AddWorld(nohaGame* world);

    std::vector<Enemy*> enemies;
    std::map<int, Enemy*>  inGameEnemies;
    float numberOfEnemies;

private:

    float timeCount;
    float timeToFire;
    nohaGame* world;
};