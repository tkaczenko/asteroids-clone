#pragma once

#include "../include/Project.h"

class App
{
public:
    App() { if (SDL_Init(SDL_INIT_EVERYTHING) != 0 ) {} }
    ~App() { SDL_Quit(); }
    bool isRunning() { return running; }
    void exit() { running = false; }
private:
    bool running = true;
};
