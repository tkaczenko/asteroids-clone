#pragma once

/*
 * For Windows:
 * Change search directories for the SDL2, SDl2_image, SDL2_ttf, SDL2-mixer
 * set Linker settings:
 * Project->Properties->Project's build options->Linker settings
 * Other Linker options: -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
*/
#include <SDL.h>
/**
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
**/
/*
 * For Linux:
 * Set up SDL2, SDL2_image, SDL2_ttf, SDL2-mixer
 * set Linker settings:
 * Project->Properties->Project's build options->Linker settings
 * Other Linker options: -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
*/
<<<<<<< HEAD
//#include <SDL2/SDL.h>
=======
#include <SDL.h>
>>>>>>> b8245c0d82ab7a6ad6468890e448e0fc80d083ce


