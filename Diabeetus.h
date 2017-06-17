#include <SDL/SDL.h>

class Diabeetus {
public:
	Diabeetus();
	void init();
	void input();
	void render();
	void drawRect(int x, int y, int w, int h, SDL_Surface *source, SDL_Rect *crop, SDL_Surface *destination);
	void fillRect(double x, double y, double w, double h, Uint32 colour);
	void update();
	void clean();
	bool collision(SDL_Rect *rect1, SDL_Rect *rect2);
	bool isDone();
	SDL_Rect setRect(int x, int y, int w, int h);

private:
	bool done;
	int dstX;
	int dstY;
	int width;
	int height;
	Uint32 colour;
	int quantity;
	int insX;
	int insY;
	int insWidth;
	int insHeight;
	int sWidth;
	int sHeight;
	int sBits;
	int countDown;
	int state;
	bool collected;
	double timeWidth;
	int U;
	int D;
	int L;
	int R;
	const int FPS = 30;
	Uint32 start;
	bool keys[323];
	SDL_Surface *screen;
	SDL_Surface *background;
	SDL_Surface *kyle;
	SDL_Surface *insulin;
	SDL_Surface *startButton;
	SDL_Surface *exitButton;
	SDL_Surface *titleScreen;
	SDL_Surface *winScreen;
	SDL_Surface *countDownSurface;
	SDL_Surface *timeTitle;
	SDL_Surface *timeBar;
	SDL_Surface *bottlesLeft;
	SDL_Surface *loseScreen;
	SDL_Rect kyleRect;
	SDL_Rect insulinRect;
	SDL_Rect textRect;
	SDL_Rect startRect;
	SDL_Rect exitRect;
	SDL_Rect bottlesCrop;
	SDL_Rect kyleCrop;
	SDL_Rect countDownCrop;
};
