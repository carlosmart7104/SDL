#En este ejemplo las librerias SDL_image, SDL_mixer y SDL_ttf han sido descomprimidas en SDL2
CC = g++
SRC = main.cpp
FLAGS = -w -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
INC = -IC:\SDL2\x86_64-w64-mingw32\include\SDL2
LIB = -LC:\SDL2\x86_64-w64-mingw32\lib
OBJ = bin/aplication

debug:
	$(CC) $(SRC) $(FLAGS) $(INC) $(LIB) -o $(OBJ) && cd bin && aplication && cd ..

realse:
	$(CC) $(SRC) $(FLAGS) -mwindows $(INC) $(LIB) -o $(OBJ)