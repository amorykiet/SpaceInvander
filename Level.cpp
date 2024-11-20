#include "Level.h"

#include "ResourceManager.h"
#include <fstream>
#include <sstream>
#include <iostream>

#include <iterator>

Level::Level(): GameObject(), numberOfEnemies(0)
{
}

void Level::Update(float dt)
{
    if (timeCount > 0.0f) {
        timeCount -= dt;
    }
    else {
        timeCount = timeToFire;
        if (numberOfEnemies != 0) {

            auto enemy = inGameEnemies.begin();
            std::advance(enemy, rand() % inGameEnemies.size());
        
            enemy->second->Fire();
        }
    }
}

void Level::Init()
{
    AddObserver(world);
    timeToFire = 1.5f;
    timeCount = timeToFire;
}

void Level::Load(const char* file, unsigned int levelWidth, unsigned int levelHeight)
{
    // clear old data
    this->enemies.clear();
    // load from file
    unsigned int tileCode;
    std::string line;
    std::ifstream fstream(file);
    std::vector<std::vector<unsigned int>> tileData;
    if (fstream)
    {
        while (std::getline(fstream, line)) // read each line from level file
        {
            std::istringstream sstream(line);
            std::vector<unsigned int> row;
            while (sstream >> tileCode) // read each word separated by spaces
                row.push_back(tileCode);
            tileData.push_back(row);
        }
        if (tileData.size() > 0)
            this->CreateEnemies(tileData, levelWidth, levelHeight);
    }
}

void Level::CreateEnemies(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth, unsigned int levelHeight)
{
    // calculate dimensions
    unsigned int height = tileData.size();
    unsigned int width = tileData[0].size(); // note we can index vector at [0] since this function is only called if height > 0
    float unit_width = levelWidth / static_cast<float>(width), unit_height = levelHeight / height;
    // initialize level tiles based on tileData		
    for (unsigned int y = 0; y < height; ++y)
    {
        for (unsigned int x = 0; x < width; ++x)
        {
            glm::vec3 color = glm::vec3(1.0f); // original: white

            if (tileData[y][x] == 2)
                color = glm::vec3(0.2f, 0.6f, 1.0f);
            else if (tileData[y][x] == 3)
                color = glm::vec3(0.0f, 0.7f, 0.0f);
            else if (tileData[y][x] == 4)
                color = glm::vec3(0.8f, 0.8f, 0.4f);
            else if (tileData[y][x] == 5)
                color = glm::vec3(1.0f, 0.5f, 0.0f);

            glm::vec2 pos(unit_width * x, unit_height * y);
            Enemy* enemy = new Enemy(pos + glm::vec2(80.0f, 200.0f), ResourceManager::GetTexture("face"), color);
            this->enemies.push_back(enemy);
        }
    }
}

void Level::Spawn()
{
    for (Enemy* enemy: enemies)
    {
        enemy->AddWorld(world);
        world->AddGameObject(enemy);
        numberOfEnemies++;
        inGameEnemies[enemy->ID] = enemy;
    }
}

void Level::RemoveEnemy(int ID)
{
    inGameEnemies.erase(ID);
    numberOfEnemies--;
    if (numberOfEnemies == 0) {
        notify(this, PLAYERWIN);
    }
}

void Level::AddWorld(nohaGame* world)
{
    this->world = world;
}
