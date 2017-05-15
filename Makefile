#En este ejemplo las librerias SDL_image, SDL_mixer y SDL_ttf han sido descomprimidas en lib\

CC = g++
SRC = main.cpp
FLAGS = -w -Wall -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

#Version i686 default
INC_SDL = -Ilib\SDL2-2.0.5\i686-w64-mingw32\include\SDL2
INC_SDL_image = -Ilib\SDL2_image-2.0.1\i686-w64-mingw32\include\SDL2
INC_SDL_mixer = -Ilib\SDL2_mixer-2.0.1\i686-w64-mingw32\include\SDL2
INC_SDL_ttf = -Ilib\SDL2_ttf-2.0.14\i686-w64-mingw32\include\SDL2

LIB_SDL = -Llib\SDL2-2.0.5\i686-w64-mingw32\lib
LIB_SDL_image = -Llib\SDL2_image-2.0.1\i686-w64-mingw32\lib
LIB_SDL_mixer = -Llib\SDL2_mixer-2.0.1\i686-w64-mingw32\lib
LIB_SDL_ttf = -Llib\SDL2_ttf-2.0.14\i686-w64-mingw32\lib

INC = $(INC_SDL) $(INC_SDL_image) $(INC_SDL_mixer) $(INC_SDL_ttf)
LIB = $(LIB_SDL) $(LIB_SDL_image) $(LIB_SDL_mixer) $(LIB_SDL_ttf)

#Version x86_64
INC_SDL_x86 = -Ilib\SDL2-2.0.5\x86_64-w64-mingw32\include\SDL2
INC_SDL_image_x86 = -Ilib\SDL2_image-2.0.1\x86_64-w64-mingw32\include\SDL2
INC_SDL_mixer_x86 = -Ilib\SDL2_mixer-2.0.1\x86_64-w64-mingw32\include\SDL2
INC_SDL_ttf_x86 = -Ilib\SDL2_ttf-2.0.14\x86_64-w64-mingw32\include\SDL2

LIB_SDL_x86 = -Llib\SDL2-2.0.5\x86_64-w64-mingw32\lib
LIB_SDL_image_x86 = -Llib\SDL2_image-2.0.1\x86_64-w64-mingw32\lib
LIB_SDL_mixer_x86 = -Llib\SDL2_mixer-2.0.1\x86_64-w64-mingw32\lib
LIB_SDL_ttf_x86 = -Llib\SDL2_ttf-2.0.14\x86_64-w64-mingw32\lib

INC_x86 = $(INC_SDL_x86) $(INC_SDL_image_x86) $(INC_SDL_mixer_x86) $(INC_SDL_ttf_x86)
LIB_x86 = $(LIB_SDL_x86) $(LIB_SDL_image_x86) $(LIB_SDL_mixer_x86) $(LIB_SDL_ttf_x86)

OBJ = bin\aplication

debug:
	$(CC) $(SRC) $(FLAGS) $(INC) $(LIB) -o $(OBJ) && cd bin && aplication && cd ..

realse:
	$(CC) $(SRC) $(FLAGS) -mwindows $(INC) $(LIB) -o $(OBJ)

debug_x86:
	$(CC) $(SRC) $(FLAGS) $(INC_x86) $(LIB_x86) -o $(OBJ) && cd bin && aplication && cd ..

realse_x86:
	$(CC) $(SRC) $(FLAGS) -mwindows $(INC_x86) $(LIB_x86) -o $(OBJ)