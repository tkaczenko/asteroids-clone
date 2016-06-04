#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "../include/Project.h"
#include "Drawable.h"

class GameObject : public Drawable
{
public:
    inline float* getVelocity() { return velocity; }
    inline SDL_Point getPosition() { return position; }
    SDL_Point baseFormula(const int& a, const int& b, const int& c, const int& d);
    int** readConfig(const std::string& filename);
protected:
    SDL_Point prevPosition;
    SDL_Point position;

    float angle = 0.0;
    float velocity[2];

    float cosA = 0.0;
    float sinA = 0.0;
};
