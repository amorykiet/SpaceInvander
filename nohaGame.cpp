#include <iostream>
#include <imgui.h>

#include "nohaGame.h"
#include "Player.h"
#include "ResourceManager.h"
#include "Enemy.h"
#include "Level.h"
#include "Input.h"
#include "Wall.h"
#include "Boss.h"

Boss* boss;
Level* level;
std::vector<Wall*> walls;
int score;
int hiScore;

nohaGame::nohaGame(unsigned int width, unsigned int height)
    : State(GAME_ACTIVE), Width(width), Height(height), NumberOfGameObjects(0)
{
}

nohaGame::~nohaGame()
{
    delete Renderer;
    Clear();
}

void nohaGame::Init()
{
    score = 0;
    hiScore = 0;
    State = GAME_MENU;
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

    InitThing();
}

void nohaGame::Update(float dt)
{
    switch (State)
    {
    case GAME_ACTIVE:
        for (int i = 0; i < NumberOfGameObjects; i++) {
            if (gameObjects[i]) {
                if (!gameObjects[i]->Destroyed) {
                    gameObjects[i]->Update(dt);
                }
            }
        }
        break;
    }
}

void nohaGame::ProcessInput(float dt)
{
    switch (State)
    {
    case GAME_ACTIVE:
        break;
    case GAME_MENU:
        if (Input::IsPressed(GLFW_KEY_SPACE)) {
            Clear();
            InitThing();
            State = GAME_ACTIVE;
        }
        break;
    case GAME_WIN:
        if (Input::IsPressed(GLFW_KEY_SPACE)) {
            Clear();
            InitThing();
            State = GAME_ACTIVE;
        }
        break;
    default:
        break;
    }

}

void nohaGame::Render()
{
    ImGui::SetNextWindowPos(ImVec2(SCREEN_WIDTH/2 - 60.0f, 0), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(200, 80), ImGuiCond_Always);

    ImGui::Begin("SMILE INVANDER", nullptr, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);

    ImGui::Text("Score: %i", score);
    ImGui::Text("High Score: %i", hiScore);

    ImGui::End();

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
}

void nohaGame::RemoveGameObject(GameObject* gameObject)
{
    gameObjects.erase(gameObject->ID);
    EmptySlotsOfGameObjects.insert(gameObject->ID);
    if (gameObject->tag == EnemyTag)
    {
        level->RemoveEnemy(gameObject->ID);
    }

    //LOSE
    if (gameObject->tag == PlayerTag && State == GAME_ACTIVE) {
        State = GAME_MENU;
    }
    delete gameObject;
}

void nohaGame::Clear()
{
    for (int i = 0; i < NumberOfGameObjects; i++) {
        if (gameObjects[i])
        {
            RemoveGameObject(gameObjects[i]);
        }
    }

    walls.clear();

}

void nohaGame::InitThing()
{
    score = 0;
    //Create things
    Player* faceMan = new Player(glm::vec2(Width / 2, Height - 50.0f), ResourceManager::GetTexture("face"));
    faceMan->AddWorld(this);
    AddGameObject(faceMan);

    Wall* wallLeft = new Wall(glm::vec2(Width / 2 - 150.0f, Height - 150.0f), ResourceManager::GetTexture("face"));
    wallLeft->AddWorld(this);
    walls.push_back(wallLeft);
    AddGameObject(wallLeft);

    Wall* wallRight = new Wall(glm::vec2(Width / 2 + 150.0f, Height - 150.0f), ResourceManager::GetTexture("face"));
    wallRight->AddWorld(this);
    walls.push_back(wallRight);
    AddGameObject(wallRight);

    boss = new Boss(ResourceManager::GetTexture("face"));
    boss->AddWorld(this);
    AddGameObject(boss);

    level = new Level();
    level->Load("Squad.lvl", Width * 4 / 5, Height / 4);
    level->AddWorld(this);
    level->Spawn();

    AddGameObject(level);


    // Init all things
    for (int i = 0; i < NumberOfGameObjects; i++) {
        if (gameObjects[i])
        {
            gameObjects[i]->Init();
        }
    }
}

void nohaGame::onNotify(GameObject* entity, Event event)
{
    switch (event)
    {
    case Event::DESTROYSGAMEOBJECT:
        entity->Destroyed = true;
        RemoveGameObject(entity);
        break;

    case PLAYERWIN:
        State = GAME_WIN;
        break;

    case PLAYERLOSE:
        State = GAME_MENU;
        break;
    case WALLHIT:

        for (Wall* wall : walls) {
            if (!wall) continue;
            if (wall->ID == entity->ID) {
                wall->health--;
                if (wall->health <= 0) {
                    wall->Destroyed = true;
                    RemoveGameObject(wall);
                }
            }
        }
        break;
    case ENEMYHIT:
        score += 2;
        if (hiScore < score) hiScore = score;
        break;
    case BOSSHIT:
        score += 10;
        if (hiScore < score) hiScore = score;
        break;
    }
}

