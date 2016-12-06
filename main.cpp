#include <SDL.h> // Libreria Simple DirectiveMedia Layer (para graficos)
#include <SDL_image.h> // Extension de SDL para multiples formatos de imagen
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <math.h>
#include <vector>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define FPS 10

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
	SDL_Texture* textureTileset = SDL_CreateTextureFromSurface(render, playerImg);

	// Player
	class Player
	{
	public:
		double x = SCREEN_WIDTH / 2;
		double y = SCREEN_HEIGHT / 2;
		double angle = 0.0f;
		double aceleracion = 0.1f; // pixels / seg^2
		void update(){
			//SDL_Log("player.x: %i",this->x);
			//SDL_Log("player.y: %i",this->y);
			//SDL_Log("player.angle: %0.10lf",this->angle);
			double incx = this->aceleracion * cos(this->angle * 0.0174533);
			double incy = this->aceleracion * sin(this->angle * 0.0174533);
			//SDL_Log("aceleracion: %0.10lf", this->aceleracion);
			//SDL_Log("incremento en x: %0.10lf",incx);
			//SDL_Log("incremento en y: %0.10lf",incy);
			this->x += incx;
			this->y += incy;
		}
	} player;

	class Gun
	{
	public:
		double t = 0, x, y, ang, acel = 70.0f;
		Gun(double init_x, double init_y, double init_a){
			this->t = SDL_GetTicks();
			this->ang =  init_a;
			double incx = 20 * cos(this->ang * 0.0174533);
			double incy = 20 * sin(this->ang * 0.0174533);
			this->x = init_x + incx;
			this->y =  init_y + incy;
		}
		void update(){
			double incx = this->acel * cos(this->ang * 0.0174533);
			double incy = this->acel * sin(this->ang * 0.0174533);
			this->x += incx;
			this->y += incy;
			if (this->x <= 0){
				this->x = SCREEN_WIDTH;
			} else if (this->x >= SCREEN_WIDTH){
				this->x = 0;
			}
			if (this->y <= 0){
				this->y = SCREEN_HEIGHT;
			} else if (this->y >= SCREEN_HEIGHT){
				this->y = 0;
			}
			//SDL_Log("gun1.x: %0.10lf, gun1.y: %0.10lf", this->x, this->y);	
		}
	};// gun1(300,150, 45);

	std::vector<Gun> bullets;

	bool quit = false; // Variable para el ciclo del juego
	SDL_Event e; // Variable para eventos
	// Ciclo del juego
	while(!quit){
		// Iniciar el conteo de tiempo para maximo de FPS
		auto timerFps = SDL_GetTicks();

		if(SDL_PollEvent(&e) != 0){
			if(e.type == SDL_QUIT){
				quit = true;
			} else if (e.type == SDL_KEYUP || e.type == SDL_KEYDOWN) {
				const Uint8 *state = SDL_GetKeyboardState(NULL);
				if (state[SDL_SCANCODE_UP])
				{
					if (player.aceleracion < 2.5)
					{
						player.aceleracion = 2.5;
					}
					if (player.aceleracion < 50.0 - player.aceleracion * 0.75)
					{
						player.aceleracion += player.aceleracion * 0.75;
					}
					if (player.angle <= 0)
					{
						player.angle = 0.2;
					}
					if (state[SDL_SCANCODE_LEFT]) {
					    //SDL_Log("Left and Up Keys Pressed.\n");
					    player.angle -= 15;
					} else if (state[SDL_SCANCODE_RIGHT]) {
					    //SDL_Log("Right and Up Keys Pressed.\n");
					    player.angle += 15;
					}

				}
				if (state[SDL_SCANCODE_SPACE]) {
					//SDL_Log("<SPACE> is pressed.\n");
					bullets.push_back(Gun(player.x,player.y,player.angle));
				}
				if (player.angle <= 0)
					{
						player.angle = 0.2;
					}
				if (state[SDL_SCANCODE_LEFT]) {
				    //SDL_Log("Left Key Pressed.\n");
				    player.angle -= 15;
				}
				if (state[SDL_SCANCODE_RIGHT]) {
				    //SDL_Log("Right Key Pressed.\n");
				    player.angle += 15;
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
				if (player.x <= 1)
				{
					player.x = SCREEN_WIDTH - 1;
				}
				if (player.x > SCREEN_WIDTH - 1)
				{
					player.x = 1;
				}
				if (player.y <= 1)
				{
					player.y = SCREEN_HEIGHT - 1;
				}
				if (player.y > SCREEN_HEIGHT - 1)
				{
					player.y = 1;
				}
			}
		} else {
			if (player.aceleracion > 0)
			{
				player.aceleracion -= player.aceleracion * 0.25;
				//SDL_Log("des aceleracion: %0.10lf", player.aceleracion);
			} else {
				player.aceleracion = 0;
			}
		}
		// Update Objects
		player.update();
		// asteroids.update();
		for (int i = 0; i < bullets.size(); ++i)
		{
			if (bullets[i].t <= SDL_GetTicks() - 800)
			{
				bullets.erase(bullets.begin());
			} else {
				bullets[i].update();
			}
		}

		// Mostrar en pantalla
		// Player
	    // Copiar la imagen en la surface de la ventana
	    SDL_Point centerPlayer = {25,25};
	    SDL_Rect srcRectPlayer = {168,156,209-168,193-156};
	    SDL_Rect dstRectPlayer = {player.x-25,player.y-25,50,50}; // Coordenadas y dimensiones en pantalla
	    // Cuatro copias para las fronteras
	    SDL_Rect dstRectPlayerC1 = {player.x-25 - SCREEN_WIDTH,player.y-25,50,50};
	    SDL_Rect dstRectPlayerC2 = {player.x-25 + SCREEN_WIDTH,player.y-25,50,50};
	    SDL_Rect dstRectPlayerC3 = {player.x-25,player.y-25 - SCREEN_HEIGHT,50,50};
	    SDL_Rect dstRectPlayerC4 = {player.x-25,player.y-25 + SCREEN_HEIGHT,50,50};
		SDL_RenderCopyEx(render, textureTileset, &srcRectPlayer, &dstRectPlayer, player.angle + 90, &centerPlayer, SDL_FLIP_NONE);
		SDL_RenderCopyEx(render, textureTileset, &srcRectPlayer, &dstRectPlayerC1, player.angle + 90, &centerPlayer, SDL_FLIP_NONE);
		SDL_RenderCopyEx(render, textureTileset, &srcRectPlayer, &dstRectPlayerC2, player.angle + 90, &centerPlayer, SDL_FLIP_NONE);
		SDL_RenderCopyEx(render, textureTileset, &srcRectPlayer, &dstRectPlayerC3, player.angle + 90, &centerPlayer, SDL_FLIP_NONE);
		SDL_RenderCopyEx(render, textureTileset, &srcRectPlayer, &dstRectPlayerC4, player.angle + 90, &centerPlayer, SDL_FLIP_NONE);

		// Bullets
		SDL_Point centerGun1 = {4,9};
		SDL_Rect srcRectGun1 = {140,255,148-140,274-255};
		for (int i = 0; i < bullets.size(); ++i)
		{
			Gun* gun1 = &bullets[i];
		    SDL_Rect dstRectGun1 = {gun1->x-4,gun1->y-9,8,19}; // Coordenadas y dimensiones en pantalla
			SDL_Rect dstRectGunC1 = {gun1->x-4 - SCREEN_WIDTH,gun1->y-9,8,19};
		    SDL_Rect dstRectGunC2 = {gun1->x-4 + SCREEN_WIDTH,gun1->y-9,8,19};
		    SDL_Rect dstRectGunC3 = {gun1->x-4,gun1->y-9 - SCREEN_HEIGHT,8,19};
		    SDL_Rect dstRectGunC4 = {gun1->x-4,gun1->y-9 + SCREEN_HEIGHT,8,19};
			SDL_RenderCopyEx(render, textureTileset, &srcRectGun1, &dstRectGun1, gun1->ang + 90, &centerGun1, SDL_FLIP_NONE);
			SDL_RenderCopyEx(render, textureTileset, &srcRectGun1, &dstRectGunC1, gun1->ang + 90, &centerGun1, SDL_FLIP_NONE);
			SDL_RenderCopyEx(render, textureTileset, &srcRectGun1, &dstRectGunC2, gun1->ang + 90, &centerGun1, SDL_FLIP_NONE);
			SDL_RenderCopyEx(render, textureTileset, &srcRectGun1, &dstRectGunC3, gun1->ang + 90, &centerGun1, SDL_FLIP_NONE);
			SDL_RenderCopyEx(render, textureTileset, &srcRectGun1, &dstRectGunC4, gun1->ang + 90, &centerGun1, SDL_FLIP_NONE);
		}

		// Renderizar (redibujar la pantalla) y limpiar (el render no la pantalla)
		SDL_RenderPresent(render);
		SDL_RenderClear(render);

		timerFps = SDL_GetTicks() - timerFps;
	    if (timerFps < 1000 / FPS) {
	        SDL_Delay((1000 / FPS) - timerFps);
	    }
	}
	//SDL_Delay(1000);
	// Limpar memoria dinamica y SDL
	SDL_DestroyTexture(textureTileset);
	textureTileset = NULL;
	SDL_FreeSurface(surface);
	surface = NULL;
	SDL_DestroyRenderer(render);
	render = NULL;
	SDL_DestroyWindow(window);
	window = NULL;
    SDL_Quit();
	return 0;
}