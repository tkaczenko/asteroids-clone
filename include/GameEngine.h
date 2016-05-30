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
    GameEngine();
    ~GameEngine();

    void spawnRock(const int& type, const int& number, const float& x = 0.0, const float& y = 0.0);

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
