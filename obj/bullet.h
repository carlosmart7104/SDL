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
		}
	};