#include "../include/GameEngine.h"

GameEngine::GameEngine()
{
    win = new Window("Asteroids");
    rend = new Renderer(win->getWin());
    nextFrameTime = SDL_GetTicks();

    srand(time(NULL));
    this->spawnRock(BIG_ROCK, 3);
    this->mainLoop();
}

GameEngine::~GameEngine()
{
    delete win;
    delete rend;
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

void GameEngine::mainLoop()
{
    std::cout << "Frames Drawn\tDelta\t\tInterpolation\n";
    while (app.isRunning()) {
        if (SDL_GetTicks() > dataOutputTimer + 1000) {
            std::cout << drawCount << "\t\t" << deltaTime << "\t\t" << interpolation << "\n";
            drawCount = 0;
            dataOutputTimer = SDL_GetTicks();
        }

        if (SDL_GetTicks() > rockSpawnTimer + 15000) {
            this->spawnRock(BIG_ROCK, 1);
            rockSpawnTimer = SDL_GetTicks();
        }

        this->inputs();

        loops = 0;
        deltaTime = float(SDL_GetTicks() - prevFrameTime) / 1000.0f;

        while (SDL_GetTicks() > nextFrameTime && loops < maxFrameSkip) {
            this->updatePositions();

            nextFrameTime += singleFrameTimeInMS;
            prevFrameTime = SDL_GetTicks();
            loops++;
        }

        interpolation = float(SDL_GetTicks() + singleFrameTimeInMS - nextFrameTime) / float(singleFrameTimeInMS);
        int ip = int(interpolation * 10);

        this->collisions();

        if (true) {
            this->interpolate();
            prevIntpol = ip;
            this->draw();
        }
    }
}

void GameEngine::inputs()
{
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            app.exit();
        } else if (event.type == SDL_WINDOWEVENT) {
            if (event.window.event == SDL_WINDOWEVENT_FOCUS_LOST) {
                SDL_Event focus;
                focus.type = SDL_WINDOWEVENT;
                focus.window.event = SDL_WINDOWEVENT_FOCUS_GAINED;
                SDL_WaitEvent(&focus);
            }
        }
        if (player.isAlive()) {
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.scancode == SDL_SCANCODE_UP) {
                    player.thrusting(true);
                }
                if (event.key.keysym.scancode == SDL_SCANCODE_LEFT) {
                    player.rotate(Ship::LEFT);
                } else if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
                    player.rotate(Ship::RIGHT);
                }
                if (event.key.keysym.scancode == SDL_SCANCODE_SPACE) {
                    if (player.isLoaded()) {
                        player.fire();
                        player.loaded(false);
                    }
                }
            }
        }
        if (event.type == SDL_KEYUP) {
            if (event.key.keysym.scancode == SDL_SCANCODE_UP) {
                player.thrusting(false);
            }
            if (event.key.keysym.scancode == SDL_SCANCODE_LEFT ||
                event.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
                player.rotate(Ship::NONE);
            }
            if (event.key.keysym.scancode == SDL_SCANCODE_A) {
                player.setAlive(true);
            }
            if (event.key.keysym.scancode == SDL_SCANCODE_SPACE) {
                player.loaded(true);
            }
        }
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

                    if (rock_it->second.type == BIG_ROCK) {
                        this->spawnRock(MED_ROCK, 4, rock_it->second.getPosition().x, rock_it->second.getPosition().y);
                    } else if (rock_it->second.type == MED_ROCK) {
                        this->spawnRock(SMALL_ROCK, 2, rock_it->second.getPosition().x, rock_it->second.getPosition().y);
                    } else if (rock_it->second.type == SMALL_ROCK) {

                    }
                    goto BEGIN_MISSILE_COLLISION;
                }
            }
        }
    }
}

void GameEngine::updatePositions()
{
    player.updatePosition(deltaTime);

    for (auto rock = rocks.begin(); rock != rocks.end(); rock++) {
        Rock& currentRock = rock->second;
        currentRock.updatePosition(deltaTime);
    }
}

void GameEngine::interpolate()
{
    player.interpolate(deltaTime, interpolation);

    for (auto rock = rocks.begin(); rock != rocks.end(); rock++) {
        Rock& currentRock = rock->second;
        currentRock.interpolate(deltaTime, interpolation);
    }
}

void GameEngine::draw()
{
    rend->clear();
    player.draw(rend->getRend());

    for (auto rock = rocks.begin(); rock != rocks.end(); rock++) {
        Rock& currentRock = rock->second;
        currentRock.draw(rend->getRend());
    }

    rend->present();
    drawCount++;
}
