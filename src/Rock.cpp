#include "../include/Rock.h"

Rock::Rock(SDL_Point p, const float& vX, const float& vY, const int& t, const int& n)
: num(n), type(t)
{
    position = {p.x, p.y};
    prevPosition = {p.x, p.y};
    rNum = rand() % 4;

    angle = (rand() % 314) / 100;
    if (num % 2 == 0) {
      angleVel = .01;
    } else {
      angleVel = -.01;
    }

    velocity[0] = vX;
    velocity[1] = vY;
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
    SDL_SetRenderDrawColor(r, 255, 255, 0, 1.0);
    SDL_RenderDrawLines(r, lines, 10);
    SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
}

void Rock::trace()
{
    cosA = cos(angle);
    sinA = sin(angle);
    switch (type) {
    case BIG_ROCK: {
        if (rNum == 0) {
            lines[0] = {int(cosA * (position.x - position.x) - sinA * (position.y-50 - position.y) + position.x),
                    int(sinA * (position.x - position.x) + cosA * (position.y-50 - position.y) + position.y)};


            lines[1] = {int(cosA * (position.x+30 - position.x) - sinA * (position.y-40 - position.y) + position.x),
                    int(sinA * (position.x+30 - position.x) + cosA * (position.y-40 - position.y) + position.y)};

            lines[2] = {int(cosA * (position.x+50 - position.x) - sinA * (position.y-10 - position.y) + position.x),
                    int(sinA * (position.x+50 - position.x) + cosA * (position.y-10 - position.y) + position.y)};

            lines[3] = {int(cosA * (position.x+35 - position.x) - sinA * (position.y+20 - position.y) + position.x),
                    int(sinA * (position.x+35 - position.x) + cosA * (position.y+20 - position.y) + position.y)};

            lines[4] = {int(cosA * (position.x+15 - position.x) - sinA * (position.y+50 - position.y) + position.x),
                    int(sinA * (position.x+15 - position.x) + cosA * (position.y+50 - position.y) + position.y)};

            lines[5] = {int(cosA * (position.x-10 - position.x) - sinA * (position.y+45 - position.y) + position.x),
                    int(sinA * (position.x-10 - position.x) + cosA * (position.y+45 - position.y) + position.y)};

            lines[6] = {int(cosA * (position.x-40 - position.x) - sinA * (position.y+40 - position.y) + position.x),
                    int(sinA * (position.x-40 - position.x) + cosA * (position.y+40 - position.y) + position.y)};

            lines[7] = {int(cosA * (position.x-30 - position.x) - sinA * (position.y-10 - position.y) + position.x),
                    int(sinA * (position.x-30 - position.x) + cosA * (position.y-10 - position.y) + position.y)};

            lines[8] = {int(cosA * (position.x-10 - position.x) - sinA * (position.y-15 - position.y) + position.x),
                    int(sinA * (position.x-10 - position.x) + cosA * (position.y-15 - position.y) + position.y)};

            lines[9] = {int(cosA * (position.x - position.x) - sinA * (position.y-50 - position.y) + position.x),
                    int(sinA * (position.x - position.x) + cosA * (position.y-50 - position.y) + position.y)};
        } else if (rNum == 1) {
            lines[0] = {int(cosA * (position.x - position.x) - sinA * (position.y-50 - position.y) + position.x),
                    int(sinA * (position.x - position.x) + cosA * (position.y-50 - position.y) + position.y)};

            lines[1] = {int(cosA * (position.x+30 - position.x) - sinA * (position.y-45 - position.y) + position.x),
                    int(sinA * (position.x+30 - position.x) + cosA * (position.y-45 - position.y) + position.y)};

            lines[2] = {int(cosA * (position.x+25 - position.x) - sinA * (position.y-10 - position.y) + position.x),
                    int(sinA * (position.x+25 - position.x) + cosA * (position.y-10 - position.y) + position.y)};

            lines[3] = {int(cosA * (position.x+50 - position.x) - sinA * (position.y+25 - position.y) + position.x),
                    int(sinA * (position.x+50 - position.x) + cosA * (position.y+25 - position.y) + position.y)};

            lines[4] = {int(cosA * (position.x+15 - position.x) - sinA * (position.y+50 - position.y) + position.x),
                    int(sinA * (position.x+15 - position.x) + cosA * (position.y+50 - position.y) + position.y)};

            lines[5] = {int(cosA * (position.x - position.x) - sinA * (position.y+45 - position.y) + position.x),
                    int(sinA * (position.x - position.x) + cosA * (position.y+45 - position.y) + position.y)};

            lines[6] = {int(cosA * (position.x-40 - position.x) - sinA * (position.y+50 - position.y) + position.x),
                    int(sinA * (position.x-40 - position.x) + cosA * (position.y+50 - position.y) + position.y)};

            lines[7] = {int(cosA * (position.x-40 - position.x) - sinA * (position.y-10 - position.y) + position.x),
                    int(sinA * (position.x-40 - position.x) + cosA * (position.y-10 - position.y) + position.y)};

            lines[8] = {int(cosA * (position.x-10 - position.x) - sinA * (position.y-15 - position.y) + position.x),
                    int(sinA * (position.x-10 - position.x) + cosA * (position.y-15 - position.y) + position.y)};

            lines[9] = {int(cosA * (position.x - position.x) - sinA * (position.y-50 - position.y) + position.x),
                    int(sinA * (position.x - position.x) + cosA * (position.y-50 - position.y) + position.y)};
        } else if ( rNum == 2) {
            lines[0] = {int(cosA * (position.x - position.x) - sinA * (position.y-50 - position.y) + position.x),
                    int(sinA * (position.x - position.x) + cosA * (position.y-50 - position.y) + position.y)};

            lines[1] = {int(cosA * (position.x+30 - position.x) - sinA * (position.y-40 - position.y) + position.x),
                    int(sinA * (position.x+30 - position.x) + cosA * (position.y-40 - position.y) + position.y)};

            lines[2] = {int(cosA * (position.x+50 - position.x) - sinA * (position.y-10 - position.y) + position.x),
                    int(sinA * (position.x+50 - position.x) + cosA * (position.y-10 - position.y) + position.y)};

            lines[3] = {int(cosA * (position.x+50 - position.x) - sinA * (position.y+20 - position.y) + position.x),
                    int(sinA * (position.x+50 - position.x) + cosA * (position.y+20 - position.y) + position.y)};

            lines[4] = {int(cosA * (position.x+15 - position.x) - sinA * (position.y+20 - position.y) + position.x),
                    int(sinA * (position.x+15 - position.x) + cosA * (position.y+20 - position.y) + position.y)};

            lines[5] = {int(cosA * (position.x - position.x) - sinA * (position.y+50 - position.y) + position.x),
                    int(sinA * (position.x - position.x) + cosA * (position.y+50 - position.y) + position.y)};

            lines[6] = {int(cosA * (position.x-40 - position.x) - sinA * (position.y+40 - position.y) + position.x),
                    int(sinA * (position.x-40 - position.x) + cosA * (position.y+40 - position.y) + position.y)};

            lines[7] = {int(cosA * (position.x-40 - position.x) - sinA * (position.y-10 - position.y) + position.x),
                    int(sinA * (position.x-40 - position.x) + cosA * (position.y-10 - position.y) + position.y)};

            lines[8] = {int(cosA * (position.x-10 - position.x) - sinA * (position.y-15 - position.y) + position.x),
                    int(sinA * (position.x-10 - position.x) + cosA * (position.y-15 - position.y) + position.y)};

            lines[9] = {int(cosA * (position.x - position.x) - sinA * (position.y-50 - position.y) + position.x),
                    int(sinA * (position.x - position.x) + cosA * (position.y-50 - position.y) + position.y)};
        } else if (rNum == 3) {
            lines[0] = {int(cosA * (position.x - position.x) - sinA * (position.y-50 - position.y) + position.x),
                    int(sinA * (position.x - position.x) + cosA * (position.y-50 - position.y) + position.y)};

            lines[1] = {int(cosA * (position.x+30 - position.x) - sinA * (position.y-40 - position.y) + position.x),
                    int(sinA * (position.x+30 - position.x) + cosA * (position.y-40 - position.y) + position.y)};

            lines[2] = {int(cosA * (position.x+50 - position.x) - sinA * (position.y-30 - position.y) + position.x),
                    int(sinA * (position.x+50 - position.x) + cosA * (position.y-30 - position.y) + position.y)};

            lines[3] = {int(cosA * (position.x+35 - position.x) - sinA * (position.y+20 - position.y) + position.x),
                    int(sinA * (position.x+35 - position.x) + cosA * (position.y+20 - position.y) + position.y)};

            lines[4] = {int(cosA * (position.x+50 - position.x) - sinA * (position.y+50 - position.y) + position.x),
                    int(sinA * (position.x+50 - position.x) + cosA * (position.y+50 - position.y) + position.y)};

            lines[5] = {int(cosA * (position.x-10 - position.x) - sinA * (position.y+45 - position.y) + position.x),
                    int(sinA * (position.x-10 - position.x) + cosA * (position.y+45 - position.y) + position.y)};

            lines[6] = {int(cosA * (position.x-40 - position.x) - sinA * (position.y+40 - position.y) + position.x),
                    int(sinA * (position.x-40 - position.x) + cosA * (position.y+40 - position.y) + position.y)};

            lines[7] = {int(cosA * (position.x-30 - position.x) - sinA * (position.y-10 - position.y) + position.x),
                    int(sinA * (position.x-30 - position.x) + cosA * (position.y-10 - position.y) + position.y)};

            lines[8] = {int(cosA * (position.x-50 - position.x) - sinA * (position.y-15 - position.y) + position.x),
                    int(sinA * (position.x-50 - position.x) + cosA * (position.y-15 - position.y) + position.y)};

            lines[9] = {int(cosA * (position.x - position.x) - sinA * (position.y-50 - position.y) + position.x),
                    int(sinA * (position.x - position.x) + cosA * (position.y-50 - position.y) + position.y)};
        }
        break;
    }
    case MED_ROCK: {
        if (rNum == 0) {
            lines[0] = {int(cosA * (position.x - position.x) - sinA * (position.y-25 - position.y) + position.x),
                    int(sinA * (position.x - position.x) + cosA * (position.y-25 - position.y) + position.y)};

            lines[1] = {int(cosA * (position.x+20 - position.x) - sinA * (position.y-40 - position.y) + position.x),
                    int(sinA * (position.x+20 - position.x) + cosA * (position.y-40 - position.y) + position.y)};

            lines[2] = {int(cosA * (position.x+30 - position.x) - sinA * (position.y-10 - position.y) + position.x),
                    int(sinA * (position.x+30 - position.x) + cosA * (position.y-10 - position.y) + position.y)};

            lines[3] = {int(cosA * (position.x+30 - position.x) - sinA * (position.y+15 - position.y) + position.x),
                    int(sinA * (position.x+30 - position.x) + cosA * (position.y+15 - position.y) + position.y)};

            lines[4] = {int(cosA * (position.x+15 - position.x) - sinA * (position.y+30 - position.y) + position.x),
                    int(sinA * (position.x+15 - position.x) + cosA * (position.y+30 - position.y) + position.y)};

            lines[5] = {int(cosA * (position.x-10 - position.x) - sinA * (position.y+25 - position.y) + position.x),
                    int(sinA * (position.x-10 - position.x) + cosA * (position.y+25 - position.y) + position.y)};

            lines[6] = {int(cosA * (position.x-25 - position.x) - sinA * (position.y+25 - position.y) + position.x),
                    int(sinA * (position.x-25 - position.x) + cosA * (position.y+25 - position.y) + position.y)};

            lines[7] = {int(cosA * (position.x-25 - position.x) - sinA * (position.y-10 - position.y) + position.x),
                    int(sinA * (position.x-25 - position.x) + cosA * (position.y-10 - position.y) + position.y)};

            lines[8] = {int(cosA * (position.x-10 - position.x) - sinA * (position.y-15 - position.y) + position.x),
                  int(sinA * (position.x-10 - position.x) + cosA * (position.y-15 - position.y) + position.y)};

            lines[9] = {int(cosA * (position.x - position.x) - sinA * (position.y-25 - position.y) + position.x),
                    int(sinA * (position.x - position.x) + cosA * (position.y-25 - position.y) + position.y)};
        } else if ( rNum == 1) {
            lines[0] = {int(cosA * (position.x - position.x) - sinA * (position.y-25 - position.y) + position.x),
                    int(sinA * (position.x - position.x) + cosA * (position.y-25 - position.y) + position.y)};

            lines[1] = {int(cosA * (position.x+15 - position.x) - sinA * (position.y-30 - position.y) + position.x),
                    int(sinA * (position.x+15 - position.x) + cosA * (position.y-30 - position.y) + position.y)};

            lines[2] = {int(cosA * (position.x+35 - position.x) - sinA * (position.y-15 - position.y) + position.x),
                    int(sinA * (position.x+35 - position.x) + cosA * (position.y-15 - position.y) + position.y)};

            lines[3] = {int(cosA * (position.x+15 - position.x) - sinA * (position.y+20 - position.y) + position.x),
                    int(sinA * (position.x+15 - position.x) + cosA * (position.y+20 - position.y) + position.y)};

            lines[4] = {int(cosA * (position.x+20 - position.x) - sinA * (position.y+30 - position.y) + position.x),
                    int(sinA * (position.x+20 - position.x) + cosA * (position.y+30 - position.y) + position.y)};

            lines[5] = {int(cosA * (position.x-15 - position.x) - sinA * (position.y+20 - position.y) + position.x),
                    int(sinA * (position.x-15 - position.x) + cosA * (position.y+20 - position.y) + position.y)};

            lines[6] = {int(cosA * (position.x-20 - position.x) - sinA * (position.y+25 - position.y) + position.x),
                    int(sinA * (position.x-20 - position.x) + cosA * (position.y+25 - position.y) + position.y)};

            lines[7] = {int(cosA * (position.x-25 - position.x) - sinA * (position.y-15 - position.y) + position.x),
                    int(sinA * (position.x-25 - position.x) + cosA * (position.y-15 - position.y) + position.y)};

            lines[8] = {int(cosA * (position.x-20 - position.x) - sinA * (position.y-5 - position.y) + position.x),
                    int(sinA * (position.x-20 - position.x) + cosA * (position.y-5 - position.y) + position.y)};

            lines[9] = {int(cosA * (position.x - position.x) - sinA * (position.y-25 - position.y) + position.x),
                    int(sinA * (position.x - position.x) + cosA * (position.y-25 - position.y) + position.y)};
        } else if (rNum == 2) {
            lines[0] = {int(cosA * (position.x - position.x) - sinA * (position.y-25 - position.y) + position.x),
                    int(sinA * (position.x - position.x) + cosA * (position.y-25 - position.y) + position.y)};

            lines[1] = {int(cosA * (position.x+30 - position.x) - sinA * (position.y-25 - position.y) + position.x),
                    int(sinA * (position.x+30 - position.x) + cosA * (position.y-25 - position.y) + position.y)};

            lines[2] = {int(cosA * (position.x+15 - position.x) - sinA * (position.y-20 - position.y) + position.x),
                    int(sinA * (position.x+15 - position.x) + cosA * (position.y-20 - position.y) + position.y)};

            lines[3] = {int(cosA * (position.x+25 - position.x) - sinA * (position.y+10 - position.y) + position.x),
                    int(sinA * (position.x+25 - position.x) + cosA * (position.y+10 - position.y) + position.y)};

            lines[4] = {int(cosA * (position.x+20 - position.x) - sinA * (position.y+35 - position.y) + position.x),
                    int(sinA * (position.x+20 - position.x) + cosA * (position.y+35 - position.y) + position.y)};

            lines[5] = {int(cosA * (position.x-15 - position.x) - sinA * (position.y+20 - position.y) + position.x),
                    int(sinA * (position.x-15 - position.x) + cosA * (position.y+20 - position.y) + position.y)};

            lines[6] = {int(cosA * (position.x-20 - position.x) - sinA * (position.y+30 - position.y) + position.x),
                    int(sinA * (position.x-20 - position.x) + cosA * (position.y+30 - position.y) + position.y)};

            lines[7] = {int(cosA * (position.x-25 - position.x) - sinA * (position.y-15 - position.y) + position.x),
                    int(sinA * (position.x-25 - position.x) + cosA * (position.y-15 - position.y) + position.y)};

            lines[8] = {int(cosA * (position.x-15 - position.x) - sinA * (position.y-10 - position.y) + position.x),
                    int(sinA * (position.x-15 - position.x) + cosA * (position.y-10 - position.y) + position.y)};

            lines[9] = {int(cosA * (position.x - position.x) - sinA * (position.y-25 - position.y) + position.x),
                    int(sinA * (position.x - position.x) + cosA * (position.y-25 - position.y) + position.y)};
        } else if (rNum == 3) {
                lines[0] = {int(cosA * (position.x - position.x) - sinA * (position.y-25 - position.y) + position.x),
                        int(sinA * (position.x - position.x) + cosA * (position.y-25 - position.y) + position.y)};

                lines[1] = {int(cosA * (position.x+10 - position.x) - sinA * (position.y-35 - position.y) + position.x),
                        int(sinA * (position.x+10 - position.x) + cosA * (position.y-35 - position.y) + position.y)};

            lines[2] = {int(cosA * (position.x+30 - position.x) - sinA * (position.y-20 - position.y) + position.x),
                    int(sinA * (position.x+30 - position.x) + cosA * (position.y-20 - position.y) + position.y)};

            lines[3] = {int(cosA * (position.x+25 - position.x) - sinA * (position.y+15 - position.y) + position.x),
                    int(sinA * (position.x+25 - position.x) + cosA * (position.y+15 - position.y) + position.y)};

            lines[4] = {int(cosA * (position.x+15 - position.x) - sinA * (position.y+15 - position.y) + position.x),
                    int(sinA * (position.x+15 - position.x) + cosA * (position.y+15 - position.y) + position.y)};

            lines[5] = {int(cosA * (position.x-10 - position.x) - sinA * (position.y+25 - position.y) + position.x),
                    int(sinA * (position.x-10 - position.x) + cosA * (position.y+25 - position.y) + position.y)};

            lines[6] = {int(cosA * (position.x-15 - position.x) - sinA * (position.y+25 - position.y) + position.x),
                    int(sinA * (position.x-15 - position.x) + cosA * (position.y+25 - position.y) + position.y)};

            lines[7] = {int(cosA * (position.x-25 - position.x) - sinA * (position.y-15 - position.y) + position.x),
                    int(sinA * (position.x-25 - position.x) + cosA * (position.y-15 - position.y) + position.y)};

            lines[8] = {int(cosA * (position.x-10 - position.x) - sinA * (position.y-15 - position.y) + position.x),
                    int(sinA * (position.x-10 - position.x) + cosA * (position.y-15 - position.y) + position.y)};

            lines[9] = {int(cosA * (position.x - position.x) - sinA * (position.y-25 - position.y) + position.x),
                    int(sinA * (position.x - position.x) + cosA * (position.y-25 - position.y) + position.y)};
        }
        break;
        }
        case SMALL_ROCK: {
            if (rNum == 0) {
                lines[0] = {int(cosA * (position.x - position.x) - sinA * (position.y-10 - position.y) + position.x),
                        int(sinA * (position.x - position.x) + cosA * (position.y-10 - position.y) + position.y)};

                lines[1] = {int(cosA * (position.x+8 - position.x) - sinA * (position.y-3 - position.y) + position.x),
                        int(sinA * (position.x+8 - position.x) + cosA * (position.y-3 - position.y) + position.y)};

        lines[2] = {int(cosA * (position.x+3 - position.x) - sinA * (position.y-0 - position.y) + position.x),
                  int(sinA * (position.x+3 - position.x) + cosA * (position.y-0 - position.y) + position.y)};

        lines[3] = {int(cosA * (position.x+5 - position.x) - sinA * (position.y+8 - position.y) + position.x),
                  int(sinA * (position.x+5 - position.x) + cosA * (position.y+8 - position.y) + position.y)};

        lines[4] = {int(cosA * (position.x+8 - position.x) - sinA * (position.y+13 - position.y) + position.x),
                  int(sinA * (position.x+8 - position.x) + cosA * (position.y+13 - position.y) + position.y)};

        lines[5] = {int(cosA * (position.x-8 - position.x) - sinA * (position.y+18 - position.y) + position.x),
                  int(sinA * (position.x-8 - position.x) + cosA * (position.y+18 - position.y) + position.y)};

        lines[6] = {int(cosA * (position.x-13 - position.x) - sinA * (position.y+3 - position.y) + position.x),
                  int(sinA * (position.x-13 - position.x) + cosA * (position.y+3 - position.y) + position.y)};

        lines[7] = {int(cosA * (position.x-8 - position.x) - sinA * (position.y-3 - position.y) + position.x),
                  int(sinA * (position.x-8 - position.x) + cosA * (position.y-3 - position.y) + position.y)};

        lines[8] = {int(cosA * (position.x-0 - position.x) - sinA * (position.y-8 - position.y) + position.x),
                  int(sinA * (position.x-0 - position.x) + cosA * (position.y-8 - position.y) + position.y)};

        lines[9] = {int(cosA * (position.x - position.x) - sinA * (position.y-10 - position.y) + position.x),
                  int(sinA * (position.x - position.x) + cosA * (position.y-10 - position.y) + position.y)};
      }
      else if ( rNum == 1)
      {
        lines[0] = {int(cosA * (position.x - position.x) - sinA * (position.y-10 - position.y) + position.x),
                  int(sinA * (position.x - position.x) + cosA * (position.y-10 - position.y) + position.y)};

        lines[1] = {int(cosA * (position.x+6 - position.x) - sinA * (position.y-3 - position.y) + position.x),
                  int(sinA * (position.x+6 - position.x) + cosA * (position.y-3 - position.y) + position.y)};

        lines[2] = {int(cosA * (position.x+3 - position.x) - sinA * (position.y-0 - position.y) + position.x),
                  int(sinA * (position.x+3 - position.x) + cosA * (position.y-0 - position.y) + position.y)};

        lines[3] = {int(cosA * (position.x+5 - position.x) - sinA * (position.y+8 - position.y) + position.x),
                  int(sinA * (position.x+5 - position.x) + cosA * (position.y+8 - position.y) + position.y)};

        lines[4] = {int(cosA * (position.x+0 - position.x) - sinA * (position.y+13 - position.y) + position.x),
                  int(sinA * (position.x+0 - position.x) + cosA * (position.y+13 - position.y) + position.y)};

        lines[5] = {int(cosA * (position.x-8 - position.x) - sinA * (position.y+8 - position.y) + position.x),
                  int(sinA * (position.x-8 - position.x) + cosA * (position.y+8 - position.y) + position.y)};

        lines[6] = {int(cosA * (position.x-3 - position.x) - sinA * (position.y+3 - position.y) + position.x),
                  int(sinA * (position.x-3 - position.x) + cosA * (position.y+3 - position.y) + position.y)};

        lines[7] = {int(cosA * (position.x-8 - position.x) - sinA * (position.y-3 - position.y) + position.x),
                  int(sinA * (position.x-8 - position.x) + cosA * (position.y-3 - position.y) + position.y)};

        lines[8] = {int(cosA * (position.x-0 - position.x) - sinA * (position.y-8 - position.y) + position.x),
                  int(sinA * (position.x-0 - position.x) + cosA * (position.y-8 - position.y) + position.y)};

        lines[9] = {int(cosA * (position.x - position.x) - sinA * (position.y-10 - position.y) + position.x),
                  int(sinA * (position.x - position.x) + cosA * (position.y-10 - position.y) + position.y)};
      }
      else if ( rNum == 2)
      {
        lines[0] = {int(cosA * (position.x - position.x) - sinA * (position.y-10 - position.y) + position.x),
                  int(sinA * (position.x - position.x) + cosA * (position.y-10 - position.y) + position.y)};

        lines[1] = {int(cosA * (position.x+8 - position.x) - sinA * (position.y-8 - position.y) + position.x),
                  int(sinA * (position.x+8 - position.x) + cosA * (position.y-8 - position.y) + position.y)};

        lines[2] = {int(cosA * (position.x+3 - position.x) - sinA * (position.y-3 - position.y) + position.x),
                  int(sinA * (position.x+3 - position.x) + cosA * (position.y-3 - position.y) + position.y)};

        lines[3] = {int(cosA * (position.x+5 - position.x) - sinA * (position.y-0 - position.y) + position.x),
                  int(sinA * (position.x+5 - position.x) + cosA * (position.y-0 - position.y) + position.y)};

        lines[4] = {int(cosA * (position.x+8 - position.x) - sinA * (position.y+13 - position.y) + position.x),
                  int(sinA * (position.x+8 - position.x) + cosA * (position.y+13 - position.y) + position.y)};

        lines[5] = {int(cosA * (position.x-8 - position.x) - sinA * (position.y+8 - position.y) + position.x),
                  int(sinA * (position.x-8 - position.x) + cosA * (position.y+8 - position.y) + position.y)};

        lines[6] = {int(cosA * (position.x-13 - position.x) - sinA * (position.y+3 - position.y) + position.x),
                  int(sinA * (position.x-13 - position.x) + cosA * (position.y+3 - position.y) + position.y)};

        lines[7] = {int(cosA * (position.x-8 - position.x) - sinA * (position.y-13 - position.y) + position.x),
                  int(sinA * (position.x-8 - position.x) + cosA * (position.y-13 - position.y) + position.y)};

        lines[8] = {int(cosA * (position.x-0 - position.x) - sinA * (position.y-3 - position.y) + position.x),
                  int(sinA * (position.x-0 - position.x) + cosA * (position.y-3 - position.y) + position.y)};

        lines[9] = {int(cosA * (position.x - position.x) - sinA * (position.y-10 - position.y) + position.x),
                  int(sinA * (position.x - position.x) + cosA * (position.y-10 - position.y) + position.y)};
      }
      else if (rNum == 3)
      {
        lines[0] = {int(cosA * (position.x - position.x) - sinA * (position.y-8 - position.y) + position.x),
                  int(sinA * (position.x - position.x) + cosA * (position.y-8 - position.y) + position.y)};

        lines[1] = {int(cosA * (position.x+5 - position.x) - sinA * (position.y-3 - position.y) + position.x),
                  int(sinA * (position.x+5 - position.x) + cosA * (position.y-3 - position.y) + position.y)};

        lines[2] = {int(cosA * (position.x+3 - position.x) - sinA * (position.y-2 - position.y) + position.x),
                  int(sinA * (position.x+3 - position.x) + cosA * (position.y-2 - position.y) + position.y)};

        lines[3] = {int(cosA * (position.x+5 - position.x) - sinA * (position.y+5 - position.y) + position.x),
                  int(sinA * (position.x+5 - position.x) + cosA * (position.y+5 - position.y) + position.y)};

        lines[4] = {int(cosA * (position.x+8 - position.x) - sinA * (position.y+13 - position.y) + position.x),
                  int(sinA * (position.x+8 - position.x) + cosA * (position.y+13 - position.y) + position.y)};

        lines[5] = {int(cosA * (position.x-5 - position.x) - sinA * (position.y+18 - position.y) + position.x),
                  int(sinA * (position.x-5 - position.x) + cosA * (position.y+18 - position.y) + position.y)};

        lines[6] = {int(cosA * (position.x-13 - position.x) - sinA * (position.y+3 - position.y) + position.x),
                  int(sinA * (position.x-13 - position.x) + cosA * (position.y+3 - position.y) + position.y)};

        lines[7] = {int(cosA * (position.x-8 - position.x) - sinA * (position.y-3 - position.y) + position.x),
                  int(sinA * (position.x-8 - position.x) + cosA * (position.y-3 - position.y) + position.y)};

        lines[8] = {int(cosA * (position.x-2 - position.x) - sinA * (position.y-5 - position.y) + position.x),
                  int(sinA * (position.x-2 - position.x) + cosA * (position.y-5 - position.y) + position.y)};

        lines[9] = {int(cosA * (position.x - position.x) - sinA * (position.y-8 - position.y) + position.x),
                  int(sinA * (position.x - position.x) + cosA * (position.y-8 - position.y) + position.y)};
      }
      break;
    }

  }
}
