#include <SDL2/SDL.h>

class Diabeetus {
public:
	Diabeetus();
	void init();
	void input();
	void render();
	void drawRect(int x, int y, int w, int h, SDL_Texture *source, SDL_Rect *crop);
	void fillRect(double x, double y, double w, double h, Uint32 colour);
	void update();
	void clean();
	bool collision(SDL_Rect *rect1, SDL_Rect *rect2);
	bool isDone();
	SDL_Rect setRect(int x, int y, int w, int h);

private:
	SDL_Window* win;
	SDL_Renderer* ren;
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
	int FPS;
	Uint64 start;
	bool keys[SDL_NUM_SCANCODES];
	// SDL_Surface *screen;
	SDL_Texture *background;
	SDL_Texture *kyle;
	SDL_Texture *insulin;
	SDL_Texture *startButton;
	SDL_Texture *exitButton;
	SDL_Texture *titleScreen;
	SDL_Texture *winScreen;
	SDL_Texture *countDownTexture;
	SDL_Texture *timeTitle;
	SDL_Texture *timeBar;
	SDL_Texture *bottlesLeft;
	SDL_Texture *loseScreen;
	SDL_Rect kyleRect;
	SDL_Rect insulinRect;
	SDL_Rect textRect;
	SDL_Rect startRect;
	SDL_Rect exitRect;
	SDL_Rect bottlesCrop;
	SDL_Rect kyleCrop;
	SDL_Rect countDownCrop;
};
