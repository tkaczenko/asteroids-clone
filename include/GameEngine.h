#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <cstdlib>
#include <ctime>

#include "../include/Globals.h"
#include "../include/Renderer.h"
#include "../include/Ship.h"
#include "../include/Rock.h"

class GameEngine
{
public:
    enum action { UP = 0, LEFT = 1, RIGHT = 2, FIRE = 3, ALIVE = 4};
    GameEngine();
    ~GameEngine();

    void spawnRock(const int& type, const int& number, const float& x = 0.0, const float& y = 0.0);

    void actionShip(const int& action, bool down);
    void collisions();
    void updatePositions(const float& deltaTime);
    void interpolate(const float& deltaTime, const float& interpolation);
    void draw(Renderer *rend);

    Ship* getShip() { return &player; }

private:
    Ship player;
    std::map<std::string, Rock> rocks;
    int rockNum = 0;
};
