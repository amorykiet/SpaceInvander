#pragma once

#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <set>
#include <map>

#include "Observer.h"
#include "SpriteRenderer.h"
#include "GameObject.h"
#include "nohaGame.h"

// Represents the current state of the game
enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

// Game holds all game-related state and functionality.
// Combines all game-related data into a single class for
// easy access to each of the components and manageability.
class nohaGame: public Observer
{
public:
    // game state
    GameState               State;
    unsigned int            Width, Height;
    int                     NumberOfGameObjects;
    std::set<int>           EmptySlotsOfGameObjects;

    // constructor/destructor
    nohaGame(unsigned int width, unsigned int height);
    ~nohaGame();
    // initialize game state (load all shaders/textures/levels)
    void Init();
    // game loop
    void ProcessInput(float dt);
    void Update(float dt);
    void Render();
    void AddGameObject(GameObject* gameObject);
    void RemoveGameObject(GameObject* gameObject);
    void onNotify(GameObject* entity, Event event) override;

private:

    // Game-related State data
    SpriteRenderer* Renderer;
    std::map<int, GameObject*> gameObjects;
    
};

#endif