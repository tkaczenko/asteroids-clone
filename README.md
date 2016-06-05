# asteroids-clone
Simple asteroids clone is written in C++11 with SDL2

![here] (/animation.gif "Animation")

##Settings
* A/W/D/S or arrows to move the ship
* R to spawn the ship
* SPACE to fire

##Requirements
* [SDL2](https://www.libsdl.org/download-2.0.php)

##Installation - Unix
At first check Project.h and uncomment

    #include <SDL2/SDL.h>

To build asteroids-clone from source execute the following:

    make all
##Installation - Windows
At first check Project.h and uncomment

    #include <SDL.h>

Linker options:

    -lmingw32 -lSDL2main -lSDL2

## UML diagrams
* [Class Diagram] (https://raw.githubusercontent.com/tkacz-/asteroids-clone/master/Class%20Diagram.png)
* [Sequance Diagram] (https://raw.githubusercontent.com/tkacz-/asteroids-clone/master/Sequence%20Diagram.png)
