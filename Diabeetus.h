#include <SDL2/SDL.h>

class Diabeetus {
public:
	Diabeetus();
	void init();
	void input();
	void render();
	void drawRect(int x, int y, int w, int h, SDL_Texture *texture, SDL_Rect *crop);
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
	SDL_Texture *backgroundTexture;
	SDL_Texture *kyleTexture;
	SDL_Texture *insulinTexture;
	SDL_Texture *startButtonTexture;
	SDL_Texture *exitButtonTexture;
	SDL_Texture *titleScreenTexture;
	SDL_Texture *winScreenTexture;
	SDL_Texture *countDownTexture;
	SDL_Texture *timeTitleTexture;
	SDL_Texture *timeBarTexture;
	SDL_Texture *bottlesLeftTexture;
	SDL_Texture *loseScreenTexture;
	SDL_Rect kyleRect;
	SDL_Rect insulinRect;
	SDL_Rect textRect;
	SDL_Rect startRect;
	SDL_Rect exitRect;
	SDL_Rect bottlesCrop;
	SDL_Rect kyleCrop;
	SDL_Rect countDownCrop;

	inline int nextInsX();
	inline int nextInsY();
};
