#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <map>

#include "Project.h"
#include "Bullet.h"
#include "Globals.h"
#include "GameObject.h"

class Ship : public GameObject
{
public:
    enum rotateDir {LEFT = 1, RIGHT = 2, NONE = 0};

    Ship();
    ~Ship();

    virtual void trace();
    virtual void updatePosition(const float& dT);
    virtual void interpolate(const float& dT, const float& i);
    virtual void draw(SDL_Renderer* r);

    void fire();
    void deadAnimation();

    void thrusting(const bool& val) { thrust = val; }
    void setAlive(const bool& val) { alive = val; }
    void loaded(const bool& val) { load = val; }
    void rotate(const int& val) { rot = val; }

    inline bool isAlive() { return alive; }
    inline bool isLoaded() { return load; }

    SDL_Rect* getColPoints() { return colPoints; }
    std::map<std::string, Bullet>* getBullets() { return &bullets; }
private:
    SDL_Point baseFormula(const int& a, const int& b, const int& c, const int& d);
    int** readConfig(const std::string& filename);

    int** coefArr = nullptr;
    SDL_Rect *colPoints = NULL;
    std::map<std::string, Bullet> bullets;
    SDL_Point *ship = NULL;
    SDL_Point *thruster = NULL;

    int rot = NONE;
    float speed = 0.0;

    bool alive = true;
    bool thrust = false;
    bool load = true;

    int bulletNum = 0;
};
