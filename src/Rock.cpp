#include "../include/Rock.h"

Rock::Rock(SDL_Point p, const float& vX, const float& vY, const int& t, const int& n)
: num(n), type(t)
{
    position = {p.x, p.y};
    prevPosition = {p.x, p.y};
    rNum = rand() % 4;
    angle = (rand() % 314) / 100;
    if (num % 2 == 0) {
      angleVel = 0.01;
    } else {
      angleVel = -0.01;
    }

    velocity[0] = vX;
    velocity[1] = vY;

    generateDeviation();
}

Rock::~Rock()
{

}

void Rock::updatePosition(const float& dT)
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
    } else if (position.x == 0 || position.y == 0) {
        position.x -= 20;
        position.y -= 20;
    }

    angle += angleVel;

    prevPosition.x = position.x;
    prevPosition.y = position.y;
}

void Rock::interpolate(const float& dT, const float& i)
{
    position.x = prevPosition.x - (velocity[0] * dT) * i;
    position.y = prevPosition.y - (velocity[1] * dT) * i;
    this->trace();
}

void Rock::draw(SDL_Renderer* r)
{
    SDL_SetRenderDrawColor(r, 255, 255, 0, 255);
    SDL_RenderDrawLines(r, lines, ROCK_PARTS + 1);
    SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
}

void Rock::trace()
{
    //cosA = cos(angle);
    //sinA = sin(angle);
    switch (type) {
    case BIG_ROCK:
        generate(ROCK_BIG_RADIUS, angle);
        break;
    case MED_ROCK:
        generate(ROCK_MED_RADIUS, angle);
        break;
    case SMALL_ROCK:
        generate(ROCK_SMALL_RADIUS, angle);
        break;
    }
}

void Rock::generate(int radius, double rotAngle) {
    for (int part = 0; part <= ROCK_PARTS; part++) {
        double angle = part * 2 * M_PI / ROCK_PARTS + rotAngle;
        double deviation = this -> deviation[part];
        int px = int(cos(angle) * radius * deviation) + position.x;
        int py = int(sin(angle) * radius * deviation) + position.y;
        lines[part].x = px;
        lines[part].y = py;
    }
}

void Rock::generateDeviation() {
    double deviationDelta = (ROCK_DEVIATION_MAX - ROCK_DEVIATION_MIN);
    for (int part = 0; part < ROCK_PARTS; part++) {
        double deviation = ROCK_DEVIATION_MIN + deviationDelta * ((rand() % 100) / 100.0);
        this -> deviation[part] = deviation;
    }
    this -> deviation[ROCK_PARTS] = deviation[0];
}
