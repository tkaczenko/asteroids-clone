#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <cstdlib>
#include <ctime>

#include "../include/Globals.h"
#include "../include/App.h"
#include "../include/Window.h"
#include "../include/Renderer.h"
#include "../include/Ship.h"
#include "../include/Rock.h"

class GameEngine
{
public:
    GameEngine();
    ~GameEngine();

    void spawnRock(const int& type, const int& number, const float& x = 0.0, const float& y = 0.0);
    void mainLoop();
    void inputs();

    void collisions();
    void updatePositions();
    void interpolate();
    void draw();

    float deltaTime = 0;
    float interpolation = 0;
private:
    App app;
    Window* win = nullptr;
    Renderer* rend = nullptr;
    SDL_Event event;

    const int updatesPerSecond = 30;
    const int singleFrameTimeInMS = 1000 / updatesPerSecond;
    const int maxFrameSkip = 5;
    int loops = 0;

    Uint32 nextFrameTime = 0;
    Uint32 prevFrameTime = 0;

    int prevIntpol = -1;
    Uint32 dataOutputTimer = 0;
    Uint32 drawCount = 0;

    std::map<std::string, Rock> rocks;
    int rockNum = 0;
    Ship player;

    Uint32 rockSpawnTimer = 0;
};
