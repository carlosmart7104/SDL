class Asteroid
{
public:
	char* type = "a";
	double x, y, acel, ang, giro, sentido; 
	Asteroid(){
		this->init();
	}
	Asteroid(char* ty){
		this->type = ty;
		this->init();
	}
	void init(){
		this->x = rand() % SCREEN_WIDTH;
		this->y = rand() % SCREEN_HEIGHT;
		this->acel = rand() % 25 + 5;
		this->ang = rand() % 360;
		this->sentido = rand() % 2;
	}
	void update(){
		if (sentido == 1)
		{
			this->giro += rand() % 5;
		} else {
			this->giro -= rand() % 5;
		}	
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