cc = g++
src = main.cpp
inc_sdl = -IC:/SDL2/SDL2/i686-w64-mingw32/include/SDL2
inc_img = -IC:/SDL2/SDL2_image/i686-w64-mingw32/include/SDL2
inc_mix = -IC:/SDL2/SDL2_mixer/i686-w64-mingw32/include/SDL2
inc_ttf = -IC:/SDL2/SDL2_ttf/i686-w64-mingw32/include/SDL2
inc_dir = $(inc_sdl) $(inc_img) $(inc_mix) $(inc_ttf)
flags = -w
realse = -mwindows
lib_sdl = -LC:/SDL2/SDL2/i686-w64-mingw32/lib
lib_img = -LC:/SDL2/SDL2_image/i686-w64-mingw32/lib
lib_mix = -LC:/SDL2/SDL2_mixer/i686-w64-mingw32/lib
lib_ttf = -LC:/SDL2/SDL2_ttf/i686-w64-mingw32/lib
lib_dir = $(lib_sdl) $(lib_img) $(lib_mix) $(lib_ttf)
libs = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
cc_flags = $(inc_dir) $(flags)
lnk_flags = $(lib_dir) $(libs)
obj = bin/aplication
debug:
	$(cc) $(src) $(cc_flags) $(lnk_flags) -o $(obj)
realse:
	$(cc) $(src) $(cc_flags) $(lnk_flags) $(realse) -o $(obj)