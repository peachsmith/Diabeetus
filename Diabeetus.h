#include <SDL/SDL.h>

class Diabeetus {
public:
	Diabeetus();
	void Init();
	void Input();
	void Render();
	void drawBackground(int x, int y, SDL_Surface *source, SDL_Rect *crop, SDL_Surface *destination);
	void drawInsulin(int x, int y, SDL_Surface *source, SDL_Surface *destination);
	void drawSprite(int x, int y, int w, int h, SDL_Surface *source, SDL_Rect *crop, SDL_Surface *destination);
	void drawRect(double x, double y, double w, double h, Uint32 colour);
	void Update();
	void Clean();
	bool collision(SDL_Rect *rect1, SDL_Rect *rect2);
	bool Done();
	SDL_Rect gameSetRect(int x, int y, int w, int h);

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
	SDL_Surface *text;
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
