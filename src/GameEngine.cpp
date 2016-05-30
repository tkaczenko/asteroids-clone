#include "../include/GameEngine.h"

GameEngine::GameEngine()
{
    this->spawnRock(BIG_ROCK, 3);
}

GameEngine::~GameEngine()
{

}

void GameEngine::actionShip(const int& action, bool down)
{
    if (down) {
        if (player.isAlive()) {
            switch (action) {
            case GameEngine::UP:
                player.thrusting(true);
                break;
            case GameEngine::LEFT:
                player.rotate(Ship::LEFT);
                break;
            case GameEngine::RIGHT:
                player.rotate(Ship::RIGHT);
                break;
            case GameEngine::FIRE:
                if (player.isLoaded()) {
                    player.fire();
                    player.loaded(false);
                }
                break;
            }
        }
    } else {
        switch (action) {
        case GameEngine::UP:
            player.thrusting(false);
            break;
        case GameEngine::LEFT:
            player.rotate(Ship::NONE);
            break;
        case GameEngine::RIGHT:
            player.rotate(Ship::NONE);
            break;
        case GameEngine::FIRE:
            player.loaded(true);
            break;
        case GameEngine::ALIVE:
            player.setAlive(true);
            break;
        }
    }
}

void GameEngine::spawnRock(const int& type, const int& number, const float& x, const float& y)
{
    for (int numRocks = 0; numRocks != number; numRocks++) {
        SDL_Point tempPos;
        if (x == 0.0 && y == 00) {
            tempPos = {rand() % 700 + 100, rand() % 500 + 100};
            if (tempPos.x < player.getPosition().x + 100 || tempPos.x > player.getPosition().x - 100 ||
                tempPos.y < player.getPosition().y + 100 || tempPos.y > player.getPosition().y - 100) {
                tempPos.x += 200;
                tempPos.y -= 200;
            }
        } else {
            tempPos = {int(x), int(y)};
        }
        float tempVel[2];
        if (rand() % 2 + 1 == 2) {
            tempVel[0] = rand() % 25 + 15;
        } else {
            tempVel[0] = (rand()%25 + 15) * -1;
        }
        if (rand() % 2 + 1 == 2) {
            tempVel[1] = rand() % 25 + 15;
        } else {
            tempVel[1] = (rand() % 25 + 15) * -1;
        }

        std::stringstream number;
        number << rockNum;
        std::string name = "rock" + number.str();
        Rock tempRock = {tempPos, tempVel[0], tempVel[1], type, rockNum};

        rocks.insert(std::pair<std::string, Rock>(name, tempRock));
        rockNum++;
    }
}

void GameEngine::collisions()
{
    for (int i=0; i != 3; i++) {
        for (auto rock_it = rocks.begin(); rock_it != rocks.end(); rock_it++) {
            for(int j=0; j != 9; j++) {
                if ( SDL_IntersectRectAndLine(&player.colPoints[i],
                                                &rock_it->second.getLines()[j].x,
                                                &rock_it->second.getLines()[j].y,
                                                &rock_it->second.getLines()[j+1].x,
                                                &rock_it->second.getLines()[j+1].y)) {
                    player.setAlive(false);
                }
            }
        }
    }
    BEGIN_MISSILE_COLLISION:
    for (auto bul_it = player.bullets.begin(); bul_it != player.bullets.end(); bul_it++) {
        SDL_Rect bul = {bul_it->second.getPosition().x, bul_it->second.getPosition().y, 10, 10};
        for (auto rock_it = rocks.begin(); rock_it != rocks.end(); rock_it++) {
            for(int j=0; j != 9; j++) {
                if ( SDL_IntersectRectAndLine(&bul,
                                                &rock_it->second.getLines()[j].x,
                                                &rock_it->second.getLines()[j].y,
                                                &rock_it->second.getLines()[j+1].x,
                                                &rock_it->second.getLines()[j+1].y) ) {
                    rocks.erase(rock_it);
                    player.bullets.erase(bul_it++);

                    if (rock_it->second.getType() == BIG_ROCK) {
                        this->spawnRock(MED_ROCK, 4, rock_it->second.getPosition().x, rock_it->second.getPosition().y);
                    } else if (rock_it->second.getType() == MED_ROCK) {
                        this->spawnRock(SMALL_ROCK, 2, rock_it->second.getPosition().x, rock_it->second.getPosition().y);
                    } else if (rock_it->second.getType() == SMALL_ROCK) {

                    }
                    goto BEGIN_MISSILE_COLLISION;
                }
            }
        }
    }
}

void GameEngine::updatePositions(const float& deltaTime)
{
    player.updatePosition(deltaTime);

    for (auto rock = rocks.begin(); rock != rocks.end(); rock++) {
        Rock& currentRock = rock->second;
        currentRock.updatePosition(deltaTime);
    }
}

void GameEngine::interpolate(const float& deltaTime, const float& interpolation)
{
    player.interpolate(deltaTime, interpolation);

    for (auto rock = rocks.begin(); rock != rocks.end(); rock++) {
        Rock& currentRock = rock->second;
        currentRock.interpolate(deltaTime, interpolation);
    }
}

void GameEngine::draw(Renderer *rend)
{
    rend->clear();
    player.draw(rend->getRend());

    for (auto rock = rocks.begin(); rock != rocks.end(); rock++) {
        Rock& currentRock = rock->second;
        currentRock.draw(rend->getRend());
    }

    rend->present();
}
