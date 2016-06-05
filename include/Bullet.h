#pragma once

#include <iostream>
#include <string>
#include <map>

#include "Project.h"
#include "Globals.h"
#include "GameObject.h"

class Bullet : public GameObject
{
public:
    Bullet(SDL_Point p, const float& vX, const float& vY, const int& t, const int& n);
    ~Bullet();

    virtual void trace() { };
    virtual void updatePosition(const float& dT) { };
    virtual void interpolate(const float& dT, const float& i);
    virtual void draw(SDL_Renderer *r);

    bool isDead() const;
    void updatePosition(const float& dT, std::map<std::string, Bullet>& m);
private:
    int life = 0;
    int num = 0;
    int rNum = 0;
    int type;
    bool dead;
};
