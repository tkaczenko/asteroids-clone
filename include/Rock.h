#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <map>

#include "Project.h"
#include "RockSettings.h"
#include "Globals.h"
#include "GameObject.h"

class Rock : public GameObject
{
public:
    Rock(SDL_Point p, const float& vX, const float& vY, const int& t, const int& n);
    ~Rock();

    virtual void trace();
    virtual void updatePosition(const float& dT);
    virtual void interpolate(const float& dT, const float& i);
    virtual void draw(SDL_Renderer *r);

    inline SDL_Point* getLines() { return lines; }
    void setType(int type) { this->type = type; }
    int getType() { return type; }
private:
    void generate(int radius, double rotAngle);
    void generateDeviation();

    int life = 0;
    int num = 0;
    int type;
    SDL_Color color;

    double deviation[ROCK_PARTS + 1];

    float angleVel = 0.0;

    SDL_Point lines[ROCK_PARTS + 1];
};
