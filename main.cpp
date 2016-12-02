#include <SDL.h> // Libreria Simple DirectiveMedia Layer (para graficos)
#include <SDL_image.h> // Extension de SDL para multiples formatos de imagen
//#include <SDL_mixer.h>
//#include <SDL_ttf.h>

int main(int argc, char **argv)
{
	// Iniciar SDL y variables principales
	// Iniciar video y audio
	SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO);
	// Crear ventana
	SDL_Window* window = SDL_CreateWindow("Hola mundo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
	// Crear el render, en la ventna "window", en el index "-1" (por default), sin flags
	SDL_Renderer* render = SDL_CreateRenderer(window, -1, 0);
	// Obtener la superficie de la ventana
	SDL_Surface* surface = SDL_GetWindowSurface(window);
	// Obtener la imagen como una superficie
	SDL_Surface* image = IMG_Load("hola_mundo.png");
	// Crear una textura en base a la superficie de la imagen (solo se puede renderizar texturas)
	SDL_Texture* texture = SDL_CreateTextureFromSurface(render, image);

	// Mostrar en pantalla
    // Copiar la imagen en la surface de la ventana
    SDL_Rect dstRect = {200,100,400,400}; // Coordenadas y dimensiones en pantalla
	SDL_RenderCopy(render, texture, NULL, &dstRect);

	// Renderizar (redibujar la pantalla) y limpiar (el render no la pantalla)
	SDL_RenderPresent(render);
	SDL_RenderClear(render);

	SDL_Delay(1000);
	// Limpar memoria dinamica y SDL
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(window);
    SDL_Quit();
	return 0;
}