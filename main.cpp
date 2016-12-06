#include <SDL.h> // Libreria Simple DirectiveMedia Layer (para graficos)
#include <SDL_image.h> // Extension de SDL para multiples formatos de imagen
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <math.h>
#include <vector>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define FPS 10

void drawText(SDL_Renderer* render, char* f, char* text, int size, SDL_Color color, SDL_Rect dstRect){
	TTF_Font* font = TTF_OpenFont(f, size);
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, color);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(render, textSurface);
	SDL_RenderCopy(render, textTexture, NULL, &dstRect);
	SDL_FreeSurface(textSurface);
	textSurface = NULL;
	TTF_CloseFont(font);
	font = NULL;
}

int main(int argc, char **argv)
{
	// Iniciar SDL y variables principales
	// Iniciar video y audio
	SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO);
	// Iniciar la libreria de Sonidos
	Mix_Init(MIX_INIT_FLAC|MIX_INIT_MOD|MIX_INIT_MP3|MIX_INIT_OGG);
	// Iniciar el modo de audio en modo por defecto
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
	// Cargar el audio para el disparo
	Mix_Chunk* laserSound = Mix_LoadWAV("laser1.wav");
	// Establecer el volumen del disparo en 25%
	Mix_VolumeChunk(laserSound, MIX_MAX_VOLUME/4);
	// Cargar el audio para el soundtrack
	Mix_Chunk* soundtrack = Mix_LoadWAV("space.mp3");
	// Establecer el volumen del soundtrack en 50%
	Mix_VolumeChunk(soundtrack, MIX_MAX_VOLUME/2);
	// Comenzar la reproducción del soundtrack
	Mix_PlayChannel(-1, soundtrack, -1);
	// Iniciar la libreria de Fuentes TTF
	TTF_Init();
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

	class Bullet
	{
	public:
		double t = 0, x, y, ang, acel = 70.0f;
		Bullet(double init_x, double init_y, double init_a){
			this->t = SDL_GetTicks();
			this->ang =  init_a;
			double incx = 25 * cos(this->ang * 0.0174533);
			double incy = 25 * sin(this->ang * 0.0174533);
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
			//SDL_Log("Bullet1.x: %0.10lf, Bullet1.y: %0.10lf", this->x, this->y);	
		}
	};// Bullet1(300,150, 45);

	std::vector<Bullet> bullets;

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
					bullets.push_back(Bullet(player.x,player.y,player.angle));
					Mix_PlayChannel(-1, laserSound, 0);
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
		SDL_Point centerBullet1 = {4,9};
		SDL_Rect srcRectBullet1 = {140,255,148-140,274-255};
		for (int i = 0; i < bullets.size(); ++i)
		{
			Bullet* Bullet1 = &bullets[i];
		    SDL_Rect dstRectBullet1 = {Bullet1->x-4,Bullet1->y-9,8,19}; // Coordenadas y dimensiones en pantalla
			SDL_Rect dstRectBulletC1 = {Bullet1->x-4 - SCREEN_WIDTH,Bullet1->y-9,8,19};
		    SDL_Rect dstRectBulletC2 = {Bullet1->x-4 + SCREEN_WIDTH,Bullet1->y-9,8,19};
		    SDL_Rect dstRectBulletC3 = {Bullet1->x-4,Bullet1->y-9 - SCREEN_HEIGHT,8,19};
		    SDL_Rect dstRectBulletC4 = {Bullet1->x-4,Bullet1->y-9 + SCREEN_HEIGHT,8,19};
			SDL_RenderCopyEx(render, textureTileset, &srcRectBullet1, &dstRectBullet1, Bullet1->ang + 90, &centerBullet1, SDL_FLIP_NONE);
			SDL_RenderCopyEx(render, textureTileset, &srcRectBullet1, &dstRectBulletC1, Bullet1->ang + 90, &centerBullet1, SDL_FLIP_NONE);
			SDL_RenderCopyEx(render, textureTileset, &srcRectBullet1, &dstRectBulletC2, Bullet1->ang + 90, &centerBullet1, SDL_FLIP_NONE);
			SDL_RenderCopyEx(render, textureTileset, &srcRectBullet1, &dstRectBulletC3, Bullet1->ang + 90, &centerBullet1, SDL_FLIP_NONE);
			SDL_RenderCopyEx(render, textureTileset, &srcRectBullet1, &dstRectBulletC4, Bullet1->ang + 90, &centerBullet1, SDL_FLIP_NONE);
		}

		// Renderizar texto
		SDL_Rect dstRect = {10,10,100,20};
		SDL_Color color = {250,250,250};
		drawText(render, "font.ttf", "Score: ", 10, color, dstRect); // renderer, font, text, size, x, y, w, h;

		// Renderizar (redibujar la pantalla) y limpiar (el render no la pantalla)
		SDL_RenderPresent(render);
		SDL_RenderClear(render);

		timerFps = SDL_GetTicks() - timerFps;
	    if (timerFps < 1000 / FPS) {
	        SDL_Delay((1000 / FPS) - timerFps);
	    }
	}

	SDL_DestroyTexture(textureTileset);
	textureTileset = NULL;
	SDL_FreeSurface(surface);
	surface = NULL;
	SDL_DestroyRenderer(render);
	render = NULL;
	SDL_DestroyWindow(window);
	window = NULL;
	Mix_FreeChunk(laserSound);
	Mix_FreeChunk(soundtrack);
	Mix_CloseAudio();
	Mix_Quit();
	TTF_Quit();
    IMG_Quit();
    SDL_Quit();
	return 0;
}