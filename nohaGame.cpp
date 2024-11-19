#include <iostream>

#include "nohaGame.h"
#include "Player.h"
#include "ResourceManager.h"
#include "Enemy.h"


nohaGame::nohaGame(unsigned int width, unsigned int height)
    : State(GAME_ACTIVE), Width(width), Height(height), NumberOfGameObjects(0)
{

}

nohaGame::~nohaGame()
{
    delete Renderer;

    for (int i = 0; i < NumberOfGameObjects; i++) {
        if (gameObjects[i])
        {
            delete gameObjects[i];
        }
    }
}

void nohaGame::Init()
{
    // load shaders==============================================================
    ResourceManager::LoadShader("sprite.vert", "sprite.frag", nullptr, "sprite");
    // configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width),
        static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
    // set render-specific controls
    Shader spriteShader = ResourceManager::GetShader("sprite");
    Renderer = new SpriteRenderer(spriteShader);
    //===========================================================================


    // load textures
    ResourceManager::LoadTexture("face.png", true, "face");

    //Create things
    Player* faceMan = new Player(glm::vec2(Width/2, Height - 50.0f), ResourceManager::GetTexture("face"));
    faceMan->AddWorld(this);
    AddGameObject(faceMan);

    Enemy* faceEnemy = new Enemy(glm::vec2(Width / 2, 200.0f), ResourceManager::GetTexture("face"));
    faceEnemy->AddWorld(this);
    AddGameObject(faceEnemy);


    // Init all things
    for (int i = 0; i < NumberOfGameObjects; i++) {
        if (gameObjects[i])
        {
            gameObjects[i]->Init();
        }
    }
}

void nohaGame::Update(float dt)
{

    for (int i = 0; i < NumberOfGameObjects; i++) {
        if (gameObjects[i]) {
            if (!gameObjects[i]->Destroyed) {
                gameObjects[i]->Update(dt);
            }
        }
    }
}

void nohaGame::ProcessInput(float dt)
{

}

void nohaGame::Render()
{
    for (int i = 0; i < NumberOfGameObjects; i++) {
        if (gameObjects[i]) {
            if (!gameObjects[i]->Destroyed) {
                gameObjects[i]->Draw(*Renderer);
            }
        }
    }
}

void nohaGame::AddGameObject(GameObject* gameObject)
{
    if (EmptySlotsOfGameObjects.empty())
    {
        gameObject->ID = NumberOfGameObjects;
        NumberOfGameObjects++;
    }
    else {

        gameObject->ID = *EmptySlotsOfGameObjects.begin();
        EmptySlotsOfGameObjects.erase(gameObject->ID);
    }


    gameObjects[gameObject->ID] = gameObject;
    std::cout << "ID: " << gameObject->ID << std::endl;
}

void nohaGame::RemoveGameObject(GameObject* gameObject)
{
    gameObjects.erase(gameObject->ID);
    EmptySlotsOfGameObjects.insert(gameObject->ID);
    delete gameObject;
}

void nohaGame::onNotify(GameObject* entity, Event event)
{
    switch (event)
    {
    case Event::DESTROYSGAMEOBJECT:
        RemoveGameObject(entity);
    }
}

