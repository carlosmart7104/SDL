#include <SDL.h> // Libreria Simple DirectiveMedia Layer (para graficos)
#include <SDL_image.h> // Extension de SDL para multiples formatos de imagen
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <math.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main(int argc, char **argv)
{
	// Iniciar SDL y variables principales
	// Iniciar video y audio
	SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO);
	// Crear ventana
	SDL_Window* window = SDL_CreateWindow("Asteroids. by: carlosmart7104", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	// Crear el render, en la ventna "window", en el index "-1" (por default), sin flags
	SDL_Renderer* render = SDL_CreateRenderer(window, -1, 0);
	// Obtener la superficie de la ventana
	SDL_Surface* surface = SDL_GetWindowSurface(window);
	// Obtener la imagen como una superficie
	SDL_Surface* playerImg = IMG_Load("tileset_asteroids.png");
	// Crear una textura en base a la superficie de la imagen (solo se puede renderizar texturas)
	SDL_Texture* texturePlayer = SDL_CreateTextureFromSurface(render, playerImg);

	// Player
	class Player
	{
	public:
		double x = SCREEN_WIDTH / 2;
		double y = SCREEN_HEIGHT / 2;
		double angle = 0.0f;
		double aceleracion = 1;
		void acelerar(){
			SDL_Log("player.x: %i",this->x);
			SDL_Log("player.y: %i",this->y);
			SDL_Log("player.angle: %0.10lf",this->angle);
			double incx = this->aceleracion * cos(this->angle * 0.0174533);
			double incy = this->aceleracion * sin(this->angle * 0.0174533);
			SDL_Log("aceleracion: %0.10lf", this->aceleracion);
			SDL_Log("incremento en x: %0.10lf",incx);
			SDL_Log("incremento en y: %0.10lf",incy);
			this->x += incx;
			this->y += incy;
		}
	} player;

	bool quit = false; // Variable para el ciclo del juego
	SDL_Event e; // Variable para eventos
	// Ciclo del juego
	while(!quit){
		// Detener FPS
		auto timerFps = SDL_GetTicks();
		// Mostrar en pantalla
	    // Copiar la imagen en la surface de la ventana
	    SDL_Point centerPlayer = {25,25};
	    SDL_Rect srcRectPlayer = {168,156,209-168,193-156};
	    SDL_Rect dstRectPlayer = {player.x-25,player.y-25,50,50}; // Coordenadas y dimensiones en pantalla
		SDL_RenderCopyEx(render, texturePlayer, &srcRectPlayer, &dstRectPlayer, player.angle + 90, &centerPlayer, SDL_FLIP_NONE);

		// Renderizar (redibujar la pantalla) y limpiar (el render no la pantalla)
		SDL_RenderPresent(render);
		SDL_RenderClear(render);

		timerFps = SDL_GetTicks() - timerFps;
	    if (timerFps < 1000 / 30) {
	        SDL_Delay((1000 / 30) - timerFps);
	    }

		if(SDL_PollEvent(&e) != 0){
			if(e.type == SDL_QUIT){
				quit = true;
			} else if (e.type == SDL_KEYUP || e.type == SDL_KEYDOWN){
				const Uint8 *state = SDL_GetKeyboardState(NULL);
				if (state[SDL_SCANCODE_LEFT] && state[SDL_SCANCODE_UP]) {
				    //SDL_Log("Left and Up Keys Pressed.\n");
				    player.angle -= 2;
				    player.aceleracion += 1.05;
				    //player.x += player.x * 0.016;
				} else if (state[SDL_SCANCODE_RIGHT] && state[SDL_SCANCODE_UP]) {
				    //SDL_Log("Right and Up Keys Pressed.\n");
				    player.angle += 2;
				    player.aceleracion += 1.05;
				    //player.x += player.x * 0.016;
				} else if (state[SDL_SCANCODE_UP]) {
				    //SDL_Log("Up Key Pressed.\n");
					player.aceleracion += 1.05;
				} else {
					if (player.aceleracion > 0)
					{
						player.aceleracion -= 0.005;
					}
				}
				player.acelerar();
				if (state[SDL_SCANCODE_SPACE]) {
				    //SDL_Log("<SPACE> is pressed.\n");
				}
				if (state[SDL_SCANCODE_LEFT]) {
				    //SDL_Log("Left Key Pressed.\n");
				    player.angle -= 2;
				}
				if (state[SDL_SCANCODE_RIGHT]) {
				    //SDL_Log("Right Key Pressed.\n");
				    player.angle += 2;
				}
				if (state[SDL_SCANCODE_ESCAPE]) {
					//ESC Key Pressed.
					quit = !quit;
				}
				if (player.angle > 360) {
					player.angle = player.angle - 360;
				} else if (player.angle < -360) {
					player.angle = player.angle + 360;
				}
				if (player.angle < 0)
				{
					player.angle = 360 + player.angle;
				}
				//SDL_Log("%0.10lf", player.angle);
				if (player.x < 0)
				{
					player.x = SCREEN_WIDTH;
				}
				if (player.x > SCREEN_WIDTH)
				{
					player.x = 0;
				}
				if (player.y < 0)
				{
					player.y = SCREEN_HEIGHT;
				}
				if (player.y > SCREEN_HEIGHT)
				{
					player.y = 0;
				}
			}
		}
	}
	//SDL_Delay(1000);
	// Limpar memoria dinamica y SDL
	SDL_DestroyTexture(texturePlayer);
	texturePlayer = NULL;
	SDL_FreeSurface(surface);
	surface = NULL;
	SDL_DestroyRenderer(render);
	render = NULL;
	SDL_DestroyWindow(window);
	window = NULL;
    SDL_Quit();
	return 0;
}