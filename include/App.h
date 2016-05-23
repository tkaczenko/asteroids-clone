#pragma once

#include "../include/Project.h"
#include "../include/GameEngine.h"

class App
{
public:
    App();
    ~App();

    int execute();
    void inputs();
    bool isRunning() { return running; }
    void exit() { running = false; }

    float deltaTime = 0;
    float interpolation = 0;
private:
    GameEngine* game = nullptr;

    bool running = true;
    SDL_Event event;

    const int updatesPerSecond = 30;
    const int singleFrameTimeInMS = 1000 / updatesPerSecond;
    const int maxFrameSkip = 5;
    int loops = 0;

    Uint32 nextFrameTime = 0;
    Uint32 prevFrameTime = 0;

    int prevIntpol = -1;
    Uint32 dataOutputTimer = 0;

    Uint32 rockSpawnTimer = 0;
};
