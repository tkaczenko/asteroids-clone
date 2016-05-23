#include "../include/App.h"

App::App()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0 ) {
        nextFrameTime = SDL_GetTicks();
    }
}

App::~App()
{
    delete game;
    SDL_Quit();
}

int App::execute()
{
    game = new GameEngine();
    while (this->isRunning()) {
        if (SDL_GetTicks() > dataOutputTimer + 1000) {
            dataOutputTimer = SDL_GetTicks();
        }

        if (SDL_GetTicks() > rockSpawnTimer + 15000) {
            game->spawnRock(BIG_ROCK, 1);
            rockSpawnTimer = SDL_GetTicks();
        }

        this->inputs();

        loops = 0;
        deltaTime = float(SDL_GetTicks() - prevFrameTime) / 1000.0f;

        while (SDL_GetTicks() > nextFrameTime && loops < maxFrameSkip) {
            game->updatePositions(deltaTime);

            nextFrameTime += singleFrameTimeInMS;
            prevFrameTime = SDL_GetTicks();
            loops++;
        }

        interpolation = float(SDL_GetTicks() + singleFrameTimeInMS - nextFrameTime) / float(singleFrameTimeInMS);
        int ip = int(interpolation * 10);

        game->collisions();

        if (true) {
            game->interpolate(deltaTime, interpolation);
            prevIntpol = ip;
            game->draw();
        }
    }
    return 0;
}

void App::inputs()
{
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            this->exit();
        } else if (event.type == SDL_WINDOWEVENT) {
            if (event.window.event == SDL_WINDOWEVENT_FOCUS_LOST) {
                SDL_Event focus;
                focus.type = SDL_WINDOWEVENT;
                focus.window.event = SDL_WINDOWEVENT_FOCUS_GAINED;
                SDL_WaitEvent(&focus);
            }
        }
        if (game->player.isAlive()) {
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.scancode == SDL_SCANCODE_UP) {
                    game->player.thrusting(true);
                }
                if (event.key.keysym.scancode == SDL_SCANCODE_LEFT) {
                    game->player.rotate(Ship::LEFT);
                } else if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
                    game->player.rotate(Ship::RIGHT);
                }
                if (event.key.keysym.scancode == SDL_SCANCODE_SPACE) {
                    if (game->player.isLoaded()) {
                        game->player.fire();
                        game->player.loaded(false);
                    }
                }
            }
        }
        if (event.type == SDL_KEYUP) {
            if (event.key.keysym.scancode == SDL_SCANCODE_UP) {
                game->player.thrusting(false);
            }
            if (event.key.keysym.scancode == SDL_SCANCODE_LEFT ||
                event.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
                game->player.rotate(Ship::NONE);
            }
            if (event.key.keysym.scancode == SDL_SCANCODE_A) {
                game->player.setAlive(true);
            }
            if (event.key.keysym.scancode == SDL_SCANCODE_SPACE) {
                game->player.loaded(true);
            }
        }
    }
}
