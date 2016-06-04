#include "../include/Ship.h"

Ship::Ship()
{
    prevPosition = {400, 300};
    position = {400, 300};
    ship = new SDL_Point[5];
    thruster = new SDL_Point[3];
    colPoints = new SDL_Rect[3];

    velocity[0] = 0.0;
    velocity[1] = 0.0;

    this->trace();
}

Ship::~Ship()
{
    delete ship;
    delete thruster;
    delete colPoints;
}

void Ship::fire()
{
    SDL_Point p = {int(cosA * (-10) - sinA + position.x),
                    int(sinA * (-10) + cosA + position.y)};

    float vX = velocity[0] + 500 * cosA;
    float vY = velocity[1] + 500 * sinA;

    std::stringstream ss;
    ss << bulletNum;
    std::string name = "bullet" + ss.str();

    Bullet sp = {p, vX, vY, BULLET, bulletNum};

    bullets.insert(std::pair<std::string, Bullet>(name, sp));
    bulletNum++;
}

void Ship::trace()
{
    cosA = cos(angle);
    sinA = sin(angle);

    ship[0] = {int(cosA * (-10) - sinA + position.x),
                int(sinA * (-10) + cosA + position.y)};

    ship[1] = {int(cosA * (+10) - sinA * (-10) + position.x),
                int(sinA * (+10) + cosA * (-10) + position.y)};

    ship[2] = {int(cosA * (+5) - sinA + position.x),
                int(sinA * (+5) + cosA + position.y)};

    ship[3] = {int(cosA * (+10) - sinA * (+10) + position.x),
                int(sinA * (+10) + cosA * (+10) + position.y)};

    ship[4] = {int(cosA * (-10) - sinA + position.x),
                int(sinA * (-10) + cosA + position.y)};

    thruster[0] = {int(cosA * (+8) - sinA * (+5) + position.x),
                    int(sinA * (+8) + cosA * (+5) + position.y)};

    thruster[1] = {int(cosA * (+15) - sinA + position.x),
                    int(sinA * (+15) + cosA + position.y)};

    thruster[2] = {int(cosA * (+8) - sinA * (-5) + position.x),
                    int(sinA * (+8) + cosA * (-5) + position.y)};

    colPoints[0] = {int(cosA * (-10) - sinA + position.x),
                    int(sinA * (-10) + cosA + position.y),
                    2,2};

    colPoints[1] = {int(cosA * (+10) - sinA * (-10) + position.x),
                    int(sinA * (+10) + cosA * (-10) + position.y),
                    2,2};

    colPoints[2] = {int(cosA * (+10) - sinA * (+10) + position.x),
                    int(sinA * (+10) + cosA * (+10) + position.y),
                    2,2};
}

void Ship::deadAnimation()
{
    velocity[0] = 0;
    velocity[1] = 0;
}

void Ship::updatePosition(const float& dt)
{
    if (thrust) {
        speed += 1;
        if (speed > 5) {
            speed = 5;
        }
        velocity[0] += speed * cosA;
        velocity[1] += speed * sinA;
    } else {
        speed = 0;
    }
    switch (rot) {
        case LEFT: {
            angle -= 0.175;
            break;
        }
        case RIGHT: {
            angle += 0.175;
            break;
        }
        case NONE: {
            break;
        }
    }

    position.x = prevPosition.x - velocity[0] * dt;
    position.y = prevPosition.y - velocity[1] * dt;

    if (position.x > 800) {
        position.x -= 800;
    }
    if (position.x < 0) {
        position.x += 800;
    }
    if (position.y > 600) {
        position.y -= 600;
    }
    if (position.y < 0) {
        position.y += 600;
    }
    for (auto i = bullets.begin(); i != bullets.end(); i++) {
        i->second.update(dt, bullets);
    }
    prevPosition.x = position.x;
    prevPosition.y = position.y;
}

void Ship::interpolate(const float& dT, const float& i)
{
    position.x = prevPosition.x - (velocity[0] * dT) * i;
    position.y = prevPosition.y - (velocity[1] * dT) * i;
    if (alive) {
        this->trace();
    } else {
        this->deadAnimation();
    }

    for (auto j = bullets.begin(); j != bullets.end(); j++)
    {
        j->second.interpolate(dT, i);
    }
}

void Ship::draw(SDL_Renderer* r)
{
    SDL_SetRenderDrawColor(r, 255, 255, 255, 255);

    if (alive)
    {
        if (thrust) {
            SDL_RenderDrawLines(r, ship, 5);
            SDL_SetRenderDrawColor(r, 255, 0, 0, 1.0);
            SDL_RenderDrawLines(r, thruster, 3);
        } else {
            SDL_RenderDrawLines(r, ship, 5);
        }
        for (auto i = bullets.begin(); i != bullets.end(); i++) {
            i->second.draw(r);
        }
    }
}
