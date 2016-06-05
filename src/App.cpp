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
}

App::~App()
{
    delete win;
    delete rend;

    SDL_Quit();
}

int App::execute()
{
    while (running) {
        if (SDL_GetTicks() > dataOutputTimer + 1000) {
            dataOutputTimer = SDL_GetTicks();
        }

        if (SDL_GetTicks() > rockSpawnTimer + 15000) {
            game.spawnRock(BIG_ROCK, 1);
            rockSpawnTimer = SDL_GetTicks();
        }

        this->inputs();

        loops = 0;
        deltaTime = float(SDL_GetTicks() - prevFrameTime) / 1000.0f;

        while (SDL_GetTicks() > nextFrameTime && loops < maxFrameSkip) {
            game.updatePositions(deltaTime);

            nextFrameTime += singleFrameTimeInMS;
            prevFrameTime = SDL_GetTicks();
            loops++;
        }
        interpolation = float(SDL_GetTicks() + singleFrameTimeInMS - nextFrameTime) / float(singleFrameTimeInMS);
        game.collisions();
        if (true) {
            game.interpolate(deltaTime, interpolation);
            game.draw(rend);
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
        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.scancode == SDL_SCANCODE_UP ||
                event.key.keysym.scancode == SDL_SCANCODE_W) {
                game.actionShip(GameEngine::UP, true);
            }
            if (event.key.keysym.scancode == SDL_SCANCODE_LEFT ||
                event.key.keysym.scancode == SDL_SCANCODE_A) {
                game.actionShip(GameEngine::LEFT, true);
            } else if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT ||
                        event.key.keysym.scancode == SDL_SCANCODE_D) {
                game.actionShip(GameEngine::RIGHT, true);
            }
            if (event.key.keysym.scancode == SDL_SCANCODE_SPACE) {
                game.actionShip(GameEngine::FIRE, true);
            }
        }
        if (event.type == SDL_KEYUP) {
            if (event.key.keysym.scancode == SDL_SCANCODE_UP ||
                event.key.keysym.scancode == SDL_SCANCODE_W) {
                game.actionShip(GameEngine::UP, false);
            }
            if (event.key.keysym.scancode == SDL_SCANCODE_LEFT ||
                event.key.keysym.scancode == SDL_SCANCODE_RIGHT ||
                event.key.keysym.scancode == SDL_SCANCODE_A ||
                event.key.keysym.scancode == SDL_SCANCODE_D) {
                game.actionShip(GameEngine::LEFT, false);
            }
            if (event.key.keysym.scancode == SDL_SCANCODE_R) {
                game.actionShip(GameEngine::ALIVE, false);
            }
            if (event.key.keysym.scancode == SDL_SCANCODE_SPACE) {
                game.actionShip(GameEngine::FIRE, false);
            }
        }
    }
}
