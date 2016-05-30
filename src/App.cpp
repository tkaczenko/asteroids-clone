#include "../include/App.h"

App::App()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0 ) {
        std::cout << "Unable initialize SDL: " << SDL_GetError();
        return;
    }
    win = new Window("Asteroids");
    rend = new Renderer(win->getWin());

    nextFrameTime = SDL_GetTicks();
    srand(time(NULL));

    game = new GameEngine();
}

App::~App()
{
    delete win;
    delete rend;
    delete game;
    SDL_Quit();
}

int App::execute()
{
    while (running) {
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
            game->draw(rend);
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
        if (game->getShip()->isAlive()) {
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.scancode == SDL_SCANCODE_UP) {
                    game->getShip()->thrusting(true);
                }
                if (event.key.keysym.scancode == SDL_SCANCODE_LEFT) {
                    game->getShip()->rotate(Ship::LEFT);
                } else if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
                    game->getShip()->rotate(Ship::RIGHT);
                }
                if (event.key.keysym.scancode == SDL_SCANCODE_SPACE) {
                    if (game->getShip()->isLoaded()) {
                        game->getShip()->fire();
                        game->getShip()->loaded(false);
                    }
                }
            }
        }
        if (event.type == SDL_KEYUP) {
            if (event.key.keysym.scancode == SDL_SCANCODE_UP) {
                game->getShip()->thrusting(false);
            }
            if (event.key.keysym.scancode == SDL_SCANCODE_LEFT ||
                event.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
                game->getShip()->rotate(Ship::NONE);
            }
            if (event.key.keysym.scancode == SDL_SCANCODE_A) {
                game->getShip()->setAlive(true);
            }
            if (event.key.keysym.scancode == SDL_SCANCODE_SPACE) {
                game->getShip()->loaded(true);
            }
        }
    }
}
