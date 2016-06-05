#pragma once

#include "Project.h"

class Renderer
{
public:
    Renderer(SDL_Window* win) { hwRend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED); }
    ~Renderer() { SDL_DestroyRenderer(hwRend); }

    void clear()
    {
        SDL_SetRenderDrawColor(hwRend, 0, 0, 0, 255);
        SDL_RenderClear(hwRend);
    }
    void present() { SDL_RenderPresent(hwRend); }
    SDL_Renderer* getRend() const { return this->hwRend; }
private:
    SDL_Renderer* hwRend = NULL;
};
