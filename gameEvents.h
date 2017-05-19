#include <SDL/SDL.h>

class gameEvents{
    public:
        gameEvents();
        void gameInit();
        void gameInput();
        void gameDraw();
        void drawBackground(int x,int y,SDL_Surface *source,SDL_Surface *destination);
        void drawInsulin(int x,int y,SDL_Surface *source,SDL_Surface *destination);
        void drawSprite(int srcX,int srcY,int dstX,int dstY,int width,int height,SDL_Surface *source,SDL_Surface *destination);
        void drawRect(double x,double y,double w,double h,Uint32 colour);
        void gameUpdate();
        void gameClean();
        void OnAnimate();
        void SetFrameRate(int Rate);
        void SetCurrentFrame(int Frame);
        int GetCurrentFrame();
        Uint32 timeLeft();
        bool collision(SDL_Rect *rect1,SDL_Rect *rect2);
        bool gameDone();
        SDL_Rect gameSetRects(int x,int y,int w,int h);

    private:
        bool done;
};
