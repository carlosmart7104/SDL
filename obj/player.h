class Player
	{
	public:
		double x = SCREEN_WIDTH / 2;
		double y = SCREEN_HEIGHT / 2;
		double angle = 270.0f;
		double aceleracion = 0.1f; // pixels / seg^2
		void update(){
			double incx = this->aceleracion * cos(this->angle * 0.0174533);
			double incy = this->aceleracion * sin(this->angle * 0.0174533);
			this->x += incx;
			this->y += incy;
		}
	} player;