#pragma once

#include <string>

#include "../include/Project.h"
#include "../include/Globals.h"

class Window
{
public:
    Window(const std::string& title) {
        hwWin = SDL_CreateWindow(title.c_str(),
                        SDL_WINDOWPOS_CENTERED,
                        SDL_WINDOWPOS_CENTERED,
                        WINDOW_WIDTH,
                        WINDOW_HEIGHT,
                        SDL_WINDOW_SHOWN);
    }
    ~Window() {
        SDL_DestroyWindow(hwWin);
        hwWin = NULL;
    }

    SDL_Window* getWin() const { return this->hwWin; }

private:
    SDL_Window *hwWin = NULL;
};
