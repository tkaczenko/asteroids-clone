#pragma once

#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>

#include "../include/Project.h"
#include "Globals.h"
#include "GameObject.h"

class Bullet
{
public:
    Bullet();
    Bullet(SDL_Point p, const float& vX, const float& vY, const int& t, const int& n);
    ~Bullet();

    inline float* getVelocity() { return velocity; }
    inline SDL_Point getPosition() { return position; }

    void update(const float& dT, std::map<std::string, Bullet>& m);
    void trace() { };
    void updatePosition(const float& dT) { };
    void interpolate(const float& dT, const float& i);
    void draw(SDL_Renderer *r);

private:
    int type;
    int life = 0;
    int num = 0;
    int rNum = 0;

    SDL_Point position;
    SDL_Point prevPosition;

    float velocity[2];
};
