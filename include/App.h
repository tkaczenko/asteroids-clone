#pragma once

#include "../include/Project.h"
#include "../include/Window.h"
#include "../include/Renderer.h"
#include "../include/GameEngine.h"

class App
{
public:
    App();
    ~App();

    int execute();
    void exit() { running = false; }
private:
    void inputs();

    Window *win = nullptr;
    Renderer *rend = nullptr;
    GameEngine game;

    bool running = true;
    SDL_Event event;

    float deltaTime = 0;
    float interpolation = 0;

    const int updatesPerSecond = 30;
    const int singleFrameTimeInMS = 1000 / updatesPerSecond;
    const int maxFrameSkip = 5;
    int loops = 0;

    Uint32 nextFrameTime = 0;
    Uint32 prevFrameTime = 0;

    Uint32 dataOutputTimer = 0;

    Uint32 rockSpawnTimer = 0;
};
