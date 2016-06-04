#include "../include/Bullet.h"

Bullet::Bullet(SDL_Point p, const float& vX, const float& vY, const int& t, const int& n)
: num(n), type(t), dead(false)
{
    position = {p.x, p.y};
    prevPosition = {p.x, p.y};
    if (type == BULLET) {

    }

    velocity[0] = vX;
    velocity[1] = vY;
}

Bullet::~Bullet()
{

}

void Bullet::update(const float& dT, std::map<std::string, Bullet>& m)
{
    position.x = prevPosition.x - velocity[0] * dT;
    position.y = prevPosition.y - velocity[1] * dT;

    if (position.x > 800) {
        position.x -= 800;
    } else if (position.x < 0) {
        position.x += 800;
    }
    if (position.y > 600) {
        position.y -= 600;
    } else if (position.y < 0) {
        position.y += 600;
    }

    if (type == BULLET) {
        if (life > 25) {
            dead = true;
        } else {
            life++;
        }
    }

    prevPosition.x = position.x;
    prevPosition.y = position.y;
}

bool Bullet::isDead() const {
    return dead;
}

void Bullet::interpolate(const float& dT, const float& i)
{
    position.x = prevPosition.x - (velocity[0] * dT) * i;
    position.y = prevPosition.y - (velocity[1] * dT) * i;
}

void Bullet::draw(SDL_Renderer* r)
{
    if (type == BULLET) {
        SDL_SetRenderDrawColor(r, 0, 255, 255, 1.0);
        SDL_RenderDrawPoint(r, position.x, position.y);
        SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
    }
}
