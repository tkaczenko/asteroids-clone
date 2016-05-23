#pragma once

#include <iostream>
#include <map>
#include <string>
#include <sstream>

#include "../include/Project.h"
#include "Bullet.h"
#include "Globals.h"
#include "GameObject.h"

class Ship : public GameObject
{
public:
    SDL_Rect *colPoints = NULL;
    std::map<std::string, Bullet> bullets;
    enum rotateDir {LEFT = 1, RIGHT = 2, NONE = 0};

    Ship();
    ~Ship();

    inline bool isAlive() { return alive; }
    inline bool isLoaded() { return load; }

    void thrusting(const bool& val) { thrust = val; }
    void setAlive(const bool& val) { alive = val; }
    void rotate(const int& val) { rot = val; }
    void loaded(const int& val) { load = val; }

    void fire();
    void deadAnim();

    virtual void trace() override;
    virtual void updatePosition(const float& dT) override;
    virtual void interpolate(const float& dT, const float& i) override;
    virtual void draw(SDL_Renderer* r) override;
private:
    SDL_Point *ship = NULL;
    SDL_Point *thruster = NULL;

    int rot = NONE;
    float speed = 0.0;

    bool alive = true;
    bool thrust = false;
    bool load = true;

    int bulletNum = 0;
};
