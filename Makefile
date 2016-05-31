OBJS = src/App.cpp src/Bullet.cpp src/GameEngine.cpp src/Rock.cpp src/Ship.cpp src/main.cpp

CC = g++

COMPILER_FLAGS = -Wall -std=c++11

LINKER_FLAGS = -lSDL2

OBJ_NAME = Asteroids

all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

clean :
	rm -rf Asteroids

